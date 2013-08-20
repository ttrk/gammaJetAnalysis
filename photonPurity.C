// photonPurity.C
// Author: Alex Barbieri
// Cobbled together from code written by Yongsun Kim

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>
#include "commonUtility.h"
#include "uniqueEvents.C"

using namespace std;
//last forward run is 211256

//pp
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pp2013Data_v2.root";
//const TString MC_FILE = "gammaJets_inclusive_dphi7pi8_pA_allQCDPhoton50.root";
//const TString LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";

//PbPb
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_Data.root";
//const TString MC_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_MC_allQCDPhoton50.root";
//const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV";

//pPb
const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pPbData_v2.root";
const TString MC_FILE = "gammaJets_inclusive_dphi7pi8_pA_allQCDPhoton50.root";
const TString LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";

// the bin which holds this value is considered the largest bin when
// computing the purity
const Double_t PURITY_BIN_VAL = 0.00999;
//const Double_t PURITY_BIN_VAL = 0.02699;

// last entry is upper bound on last bin
const Double_t HFBINS[] = {0,1000};//20,30,1000};
const Int_t nHFBINS = sizeof(HFBINS)/sizeof(Double_t) -1;

const Double_t PTBINS[] = {40, 50, 60, 80, 120, 1000};
const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

class fitResult {
public:
  Double_t nSig;
  Double_t nSigErr;
  Double_t purity;
  Double_t chisq;
};

class histFunction2
{ 
public:
  histFunction2(TH1D *h, TH1D *h2);
  ~histFunction2(){ 
    delete histBck;
    delete histSig;
  };
  
  //      Int_t GetBinNumber(Double_t c);
  Double_t evaluate(Double_t *x, Double_t *par);
  TH1D *histSig;
  TH1D *histBck;
  Double_t lowEdge;
  Double_t highEdge;
  Double_t nbin;
};

histFunction2::histFunction2(TH1D *h,TH1D *h2)
{
  histSig=(TH1D*)h->Clone();
  histBck=(TH1D*)h2->Clone();
   
  nbin=h->GetNbinsX();
  lowEdge=h->GetBinLowEdge(1);
  highEdge=h->GetBinLowEdge(nbin+1);
   
  histSig->SetName("hSig");
  histSig->Scale(1./histSig->Integral(1,histSig->GetNbinsX()+1));
  histBck->SetName("hBck");
  histBck->Scale(1./histBck->Integral(1,histBck->GetNbinsX()+1));
}

void mcStyle(TH1* h=0) {
  h->SetLineColor(kPink);
  h->SetFillColor(kOrange+7);
  h->SetFillStyle(3004);
}

void sbStyle(TH1* h=0) {
  h->SetLineColor(kGreen+4);
  h->SetFillColor(kGreen+1);
  h->SetFillStyle(3001);
}

Double_t histFunction2::evaluate(Double_t *x, Double_t *par) {
     
  Double_t xx = x[0];
  Int_t binNum=histSig->FindBin(xx);  //
   
  return par[0]*(histSig->GetBinContent(binNum)*par[1]+histBck->GetBinContent(binNum)*(1-par[1]));
}

fitResult getPurity(TNtuple *dataTuple, TNtuple *mcTuple,
		    TCut dataCandidateCut, TCut sidebandCut,
		    TCut mcSignalCut);

fitResult doFit(TH1D* hSig=0, TH1D* hBkg=0, TH1D* hData1=0,
		Float_t varLow=0.001, Float_t varHigh=0.028,
		Bool_t drawLeg=true);

void photonPurity()
{
  TH1::SetDefaultSumw2();

  TFile *dataFile = TFile::Open(DATA_FILE);
  TNtuple *dataTuple = (TNtuple*)dataFile->Get("gammaJets");
  use_only_unique_events(dataTuple);

  TFile *mcFile = TFile::Open(MC_FILE);
  TNtuple *mcTuple = (TNtuple*)mcFile->Get("gammaJets");
  use_only_unique_events(mcTuple,"jentry"); //private MC has bad event numbers

  TCut etaCut = "(abs(gEta) < 1.479)";
  //TCut etaCut = "(abs(gEta) > 1.479)";
  //TCut etaCut = "";
  TCut sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";
  //TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2";
  TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
  TCut mcIsolation = "genCalIsoDR04<5 && abs(genMomId)<=22";

  TCanvas *cPurity = new TCanvas("c1","c1",1920,1080);
  cPurity->Divide(nPTBINS,nHFBINS,0,0);
  for(Int_t i = 0; i < nPTBINS; ++i) {
    for(Int_t j = 0; j < nHFBINS; ++j) {      
      TString ptCut = Form("(gPt >= %f) && (gPt < %f)",
			   PTBINS[i], PTBINS[i+1]);
      TString hfCut = Form("((HFplusEta4+HFminusEta4) >= %f) && ((HFplusEta4+HFminusEta4) < %f)",
			   HFBINS[j], HFBINS[j+1]);

      TCut dataCandidateCut = etaCut && ptCut && hfCut && sampleIsolation;
      TCut sidebandCut = etaCut && ptCut && hfCut && sidebandIsolation;
      TCut mcSignalCut = dataCandidateCut && mcIsolation;

      // cout << "dataCandidateCut: " << dataCandidateCut << endl;
      // cout << "sidebandCut: " << sidebandCut << endl;
      // cout << "mcSignalCut: " << mcSignalCut << endl;

      // cPurity[i*nHFBINS+j] = new TCanvas(Form("cpurity%d",i*nHFBINS+j),
      // 					 "",500,500);
      cPurity->cd(j*nPTBINS+i+1);
      fitResult fitr = getPurity(dataTuple, mcTuple,
				 dataCandidateCut, sidebandCut,
				 mcSignalCut);

      //drawText("|#eta_{#gamma}| < 1.479",0.5680963,0.9);
      if(nPTBINS != 1)
	drawText(Form("%.0f < p_{T}^{#gamma} < %.0f",PTBINS[i], PTBINS[i+1]),
		 0.57, 0.9);
      if(nHFBINS != 1)
	drawText(Form("%.0f < E_{T}^{HF[|#eta|>4]} < %.0f",
		      HFBINS[j], HFBINS[j+1]),
		 0.57, 0.82);
      drawText(Form("Purity : %.2f", (Float_t)fitr.purity),
      	       0.57, 0.53);
      cout << "pT: " << PTBINS[i] << " : " << fitr.purity << endl;
      // TString savename = Form("purity_pA_barrel_pt%.0f_hf%.0f_plot",
      // 			     PTBINS[i], HFBINS[j]);
      // cPurity[i*nHFBINS+j]->SaveAs(savename+".C");
      // cPurity[i*nHFBINS+j]->SaveAs(savename+".pdf");
      // cPurity[i*nHFBINS+j]->SaveAs(savename+".png");
      
    }
  }
}

fitResult getPurity(TNtuple *dataTuple, TNtuple *mcTuple,
		    TCut dataCandidateCut, TCut sidebandCut,
		    TCut mcSignalCut)
{
  TH1D* hCand = new TH1D("cand","",35,0,0.035);
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");
  TH1D* hSig = (TH1D*)hCand->Clone("sig");

  Int_t dEntries = dataTuple->Project(hCand->GetName(), "sigmaIetaIeta", dataCandidateCut, "");
  Int_t sbEntries = dataTuple->Project(hBkg->GetName(), "sigmaIetaIeta", sidebandCut, "");
  Int_t mcEntries = mcTuple->Project(hSig->GetName(), "sigmaIetaIeta", mcSignalCut, "");

  cout << "# Candidates: " << dEntries << endl;
  cout << "# Sideband: " << sbEntries << endl;
  cout << "# MC Signal: " << mcEntries << endl;

  fitResult fitr = doFit(hSig, hBkg, hCand, 0.005, 0.035, true);

  delete hSig;
  delete hBkg;
  delete hCand;
  
  return fitr;
}


fitResult doFit(TH1D* hSig, TH1D* hBkg, TH1D* hData1,
		Float_t varLow, Float_t varHigh,
		Bool_t drawLeg)
{   
  TH1D* hDatatmp = (TH1D*)hData1->Clone(Form("%s_datatmp",hData1->GetName()));
  Int_t nBins = hDatatmp->GetNbinsX();
  histFunction2 *myFits = new histFunction2(hSig,hBkg);
  TF1 *f = new TF1("f",myFits,&histFunction2::evaluate,varLow,varHigh,2);
  f->SetParameters( hDatatmp->Integral(1,nBins+1), 0.3);
  f->SetParLimits(1,0,1);
  hDatatmp->Fit("f","LL M O Q","",varLow,varHigh);
  hDatatmp->Fit("f","LL M O Q","",varLow,varHigh);

  fitResult res;
  res.nSig =0;
  Double_t nev = f->GetParameter(0);
  Double_t ratio = f->GetParameter(1);
  Double_t ratioErr = f->GetParError(1);
  res.nSig    = nev * ratio;
  res.nSigErr = nev * ratioErr;
  res.chisq = (Double_t)f->GetChisquare()/ f->GetNDF();
   
  TH1F *hSigPdf = (TH1F*)hSig->Clone(Form("%s_tmp",hSig->GetName()));
  hSigPdf->Scale(res.nSig/hSigPdf->Integral(1,nBins+1));

  TH1F *hBckPdf = (TH1F*)hBkg->Clone(Form("%s_tmp",hBkg->GetName()));
  hBckPdf->Scale((nev-res.nSig)/hBckPdf->Integral(1,nBins+1));

  Double_t ss1 = hSigPdf->Integral(1, hSigPdf->FindBin(PURITY_BIN_VAL),"width");
  Double_t bb1 = hBckPdf->Integral(1, hBckPdf->FindBin(PURITY_BIN_VAL),"width");
  //   cout <<"  hte bin = " <<hSigPdf->FindBin(PURITY_BIN_VAL) << endl;
  res.purity = ss1/(ss1+bb1);
  //cout << "purity = " << res.purity << endl;
  hSigPdf->Add(hBckPdf);
  handsomeTH1(hSigPdf);
  mcStyle(hSigPdf);
  sbStyle(hBckPdf);
  cleverRange(hSigPdf,1.5);
  hSigPdf->SetNdivisions(510);

  hSigPdf->SetYTitle("Entries");
  hSigPdf->SetXTitle("#sigma_{#eta #eta}");
  hSigPdf->DrawCopy("hist");
  hBckPdf->DrawCopy("same hist");
  hData1->DrawCopy("same");
  TH1D* temphSigPdf = (TH1D*)hSigPdf->Clone("temp1");
  TH1D* temphBckPdf = (TH1D*)hBckPdf->Clone("temp2");
  if(drawLeg){
    TLegend *t3=new TLegend(0.54, 0.60, 0.92, 0.79);
    //t3->AddEntry(hData1,"Pb+Pb  #sqrt{s}_{_{NN}}=2.76 TeV","pl");
    //t3->AddEntry(hData1,"pp  #sqrt{s}_{_{NN}}=2.76 TeV","pl");
    t3->AddEntry(hData1,LABEL,"pl");
    t3->AddEntry(temphSigPdf,"Signal","lf");
    t3->AddEntry(temphBckPdf,"Background","lf");
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(63);
    t3->SetTextSize(15);
    t3->Draw();
    //drawCMS2011(0.53,0.9,150,16);
  }
   

  //   delete hSigPdf;
  //   delete hBckPdf;
   
//   TFile* hout = new TFile("histo.root","recreate");
//   hSigPdf->Write();
//   hBckPdf->Write();
//   hData1->Write();
//   hout->Close();

   
  return res;

}

int main()
{
  photonPurity();
  return 0;
}

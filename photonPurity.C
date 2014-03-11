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
#include "fitResult.h"
//#include "uniqueEvents.C"

using namespace std;
//last forward run is 211256

// //pp
// const TString DATA_FILE = "gammaJets_pp_Data.root";
// const TString MC_FILE = "gammaJets_pp_MC_PUallQCDPhoton.root";
// const TString LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";
// const TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";

//PbPb
const TString DATA_FILE = "gammaJets_PbPb_Data.root";
const TString MC_FILE = "gammaJets_PbPb_MC_allQCDPhoton.root";
const TString LABEL = "PbPb Data";
const TCut sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";

//pPb
// const TString DATA_FILE = "gammaJets_pA_Data.root";
// const TString MC_FILE = "gammaJets_pA_MC_allQCDPhoton.root";
// const TString LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";
// const TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";


//const Double_t sigShifts[] = {-0.0000989, -0.000131273, -0.00016207, -0.000170555};
const Double_t sigShifts[] = {0, 0, 0, 0};
//const Double_t sigShifts[] = {-0.00015,-0.00015,-0.00015,-0.00015};
const TString SAVENAME = "photonPurity_PbPb_example";

// last entry is upper bound on last bin
const Int_t CENTBINS[] = {0, 12};//, 40};
//const Int_t CENTBINS[] = {0, 100};
const Int_t nCENTBINS = sizeof(CENTBINS)/sizeof(Int_t) -1;

const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
//const Double_t PTBINS[] = {60, 80};
const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

const Double_t ETABINS[] = {-1.44, 1.44};
//const Double_t ETABINS[] = {-1.44, -1, -0.5, 0, 0.5, 1, 1.44};
const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

// the bin which holds this value is considered the largest bin when
// computing the purity
const Double_t PURITY_BIN_VAL = 0.00999;
//const Double_t PURITY_BIN_VAL = 0.02699;

void photonPurity()
{
  TH1::SetDefaultSumw2();

  TFile *dataFile = TFile::Open(DATA_FILE);
  TTree *dataTree = (TTree*)dataFile->Get("photonTree");

  TFile *mcFile = TFile::Open(MC_FILE);
  TTree *mcTree = (TTree*)mcFile->Get("photonTree");

  //TFile *outFile = new TFile("photonPurity_sys_bkgshift.root","RECREATE");

  const TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
  //const TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>5) && (cc4+cr4+ct4PtCut20<10) && hadronicOverEm<0.1";
  const TCut mcIsolation = "genCalIsoDR04<5 && abs(genMomId)<=22";

  //TCanvas *cPurity[nPTBINS];
  //TCanvas *cPurity = new TCanvas("c1","c1",337*nPTBINS,300*nCENTBINS/**2*/);
  TCanvas *cPurity = new TCanvas("c1","c1",400*nPTBINS,400);
  //cPurity->Divide(nPTBINS,2*nCENTBINS,0,0);
  //cPurity->Divide(nPTBINS,nCENTBINS,0,0);
  makeMultiPanelCanvas(cPurity, nPTBINS, nCENTBINS, 0.0, 0.0 , 0.2, 0.15, 0.005);
  for(Int_t i = 0; i < nPTBINS; ++i) {
    //cPurity[i] = new TCanvas(Form("c1_%d",i),"",1920,1000);
    //cPurity[i]->Divide(nETABINS,2,0,0);
    for(Int_t j = 0; j < nCENTBINS; ++j) {
      for(Int_t k = 0; k< nETABINS; ++k) {
	TString ptCut = Form("(corrPt >= %f) && (corrPt < %f)",
			     PTBINS[i], PTBINS[i+1]);
	TString centCut = Form("((hiBin) >= %i) && ((hiBin) < %i)",
			     CENTBINS[j], CENTBINS[j+1]);
	TString etaCut = Form("(eta >= %f) && (eta < %f)",
			      ETABINS[k], ETABINS[k+1]);

	//TString pPbflipetaCut = Form("(eta*((run>211257)*-1+(run<211257)) >=%f) && (eta*((run>211257)*-1+(run<211257)) <%f)",
	//			     ETABINS[k], ETABINS[k+1]);

	TCut dataCandidateCut = sampleIsolation && etaCut && ptCut && centCut;
	TCut sidebandCut =  sidebandIsolation && etaCut && ptCut && centCut;
	TCut mcSignalCut = dataCandidateCut && mcIsolation;

	// if(nETABINS != 1)
	// {
	//   dataCandidateCut = sampleIsolation && pPbflipetaCut && ptCut && centCut;
	//   sidebandCut =  sidebandIsolation && pPbflipetaCut && ptCut && centCut;
	//   mcSignalCut =  sampleIsolation && etaCut && ptCut && centCut && mcIsolation;
	// }

	fitResult fitr = getPurity(dataTree, mcTree,
				   dataCandidateCut, sidebandCut,
				   mcSignalCut, sigShifts[i],
				   0.0, PURITY_BIN_VAL);

	//cPurity[i*nCENTBINS+j] = new TCanvas(Form("cpurity%d",i*nCENTBINS+j),
	// 					 "",500,500);
	cPurity->cd(2*(k+j)*nPTBINS+i+1);
	//cPurity->cd((k+j)*nPTBINS+i+1);
	//cPurity[i]->cd(k+1);

	TH1F *hSigPdf = fitr.sigPdf;
	TH1F *hBckPdf = fitr.bckPdf;
	TH1D *hData1  = fitr.data;
	hSigPdf->Add(hBckPdf);

	TString name = "mcfit_total_ptbin";
	name += i;
	
	// outFile->cd();
	// hSigPdf->SetName(name);
	// hSigPdf->Write();

	
	TH1D *err = (TH1D*)hSigPdf->Clone("error");
	TH1D *tempErr[4];
	err->Reset();
	for(int s = 0; s < 4; s++)
	{
	  if(s == 0)
	    tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_loose.root")->Get(name);
	  else if(s ==1)
	    tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_tight.root")->Get(name);
	  else if(s ==2)
	    tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_sigshift.root")->Get(name);
	  else if(s ==3)
	    tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_bkgshift.root")->Get(name);
	  tempErr[s]->Divide(hSigPdf);
	  for (Int_t l=1; l<=tempErr[s]->GetNbinsX();l++)
	  {
	    tempErr[s]->SetBinContent(l, TMath::Abs(tempErr[s]->GetBinContent(l))-1);
	  }
	}
	for (Int_t l=1; l<=err->GetNbinsX();l++)
	{
	  Double_t errVal = TMath::Sqrt(tempErr[0]->GetBinContent(l)*tempErr[0]->GetBinContent(l) +
					tempErr[1]->GetBinContent(l)*tempErr[1]->GetBinContent(l) +
					tempErr[2]->GetBinContent(l)*tempErr[2]->GetBinContent(l) +
					tempErr[3]->GetBinContent(l)*tempErr[3]->GetBinContent(l)
	    );
	  err->SetBinContent(l, errVal);
	}

	// plot stacked histos
	handsomeTH1(hSigPdf);
	mcStyle(hSigPdf);
	sbStyle(hBckPdf);
	cleverRange(hSigPdf,1.5);
	hSigPdf->SetAxisRange(0.001,0.024,"X");
	hSigPdf->SetNdivisions(505);
	hSigPdf->GetYaxis()->SetTitleOffset(1.75);
	hSigPdf->SetYTitle("Entries");
	hSigPdf->SetXTitle("#sigma_{#eta #eta}");

	hSigPdf->DrawCopy("hist");
	drawSys(hSigPdf, err, kRed, -1, 0.001);
	hBckPdf->DrawCopy("same hist");
	hData1->DrawCopy("same");

	Float_t xpos = 0.44;
	if(2*(k+j)*nPTBINS+i+1 == 1)
	  xpos = 0.54;

	TLegend *t3=new TLegend(xpos, 0.45, 0.92, 0.71);
	t3->AddEntry(hData1,LABEL,"pl");
	t3->AddEntry(hSigPdf,"Signal","lf");
	t3->AddEntry(hBckPdf,"Background","lf");
	t3->SetFillColor(0);
	t3->SetBorderSize(0);
	t3->SetFillStyle(0);
	t3->SetTextFont(43);
	t3->SetTextSize(20);
	//if(i == 0)
	TH1D *dummyHist = new TH1D("dummyHist","",10,0,10);
	dummyHist->Fill(1);
	dummyHist->SetFillColor(kRed);
	dummyHist->SetLineColor(kRed);
	dummyHist->SetFillStyle(1001);
	t3->AddEntry(dummyHist,"MC Sys. Error","f");
	if(i == 0)
	  t3->Draw();

	if(i == 3)
	{
	  drawText("CMS Preliminary", xpos, 0.68,1,20);
	  drawText("PbPb #sqrt{s}_{_{NN}}=2.76 TeV", xpos, 0.60,1,20);
	  drawText("#intL = 150 #mub^{-1}", xpos, 0.50,1,20);
	}
	  
	  

	//drawText("|#eta_{#gamma}| < 1.479",0.5680963,0.9);
	//drawText(Form("%f shift",fitr.sigMeanShift),0.57,0.82);
	//drawText("Background Correction",0.57,0.82);
	//drawText("bkg Tighter",0.57,0.82);
	//if(nPTBINS != 1)
	drawText(Form("%.0f GeV < p_{T}^{#gamma} < %.0f GeV",
		      PTBINS[i], PTBINS[i+1]),
		 xpos, 0.90,1,20);
	// if(/*nCENTBINS != 1 && */i ==0)
	drawText(Form("%.0f - %.0f%c",
		      CENTBINS[j]*100./40., CENTBINS[j+1]*100./40.,'%'),
		 xpos, 0.82,1,20);
	// if(nETABINS != 1)
	//   drawText(Form("%.3f < #eta_{#gamma} < %.3f",
	// 		ETABINS[k], ETABINS[k+1]),
	// 	   xpos, 0.82,1,20);
	drawText(Form("Purity (#sigma_{#eta#eta} < 0.01) : %.2f", (Float_t)fitr.purity),
		 xpos, 0.76,1,20);
	// drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq),
	// 	 xpos, 0.45);
	

	// //plot ratio
	// cPurity->cd((2*(j+k)+1)*nPTBINS+i+1);
	// //cPurity[i]->cd(nETABINS + k+ 1);
	// TH1D* ratio = (TH1D*)hData1->Clone("ratio");
	// ratio->Divide(hData1, hSigPdf, 1, 1);
	// ratio->SetMinimum(0);
	// ratio->SetMaximum(3);
	// ratio->SetXTitle("#sigma_{#eta #eta}");
	// ratio->GetXaxis()->CenterTitle();
	// ratio->SetYTitle("Data/Fit");
	// ratio->GetYaxis()->CenterTitle();
	// ratio->DrawCopy("E");
	// TLine *line = new TLine(0,1,maxSIGMA,1);
	// line->SetLineStyle(2);
	// line->Draw("same");

	// TString savename = Form("purity_pA_barrel_pt%.0f_hf%.0f_plot",
	// 			PTBINS[i], CENTBINS[j]);
	// cPurity[i*nCENTBINS+j]->SaveAs(savename+".C");
	// cPurity[i*nCENTBINS+j]->SaveAs(savename+".pdf");
	// cPurity[i*nCENTBINS+j]->SaveAs(savename+".png");

      }
    }
    //cPurity[i]->SaveAs(Form("pPb_purity_etadep_wshift_ptbin%.0f.png",PTBINS[i]));
    //cPurity[i]->SaveAs(Form("pPb_purity_etadep_noshift_inclusive.png"));
  }
  //cPurity->SaveAs(SAVENAME+".C");
  //cPurity->SaveAs(SAVENAME+".png");
  cPurity->SaveAs(SAVENAME+".pdf");
}

int main()
{
  photonPurity();
  return 0;
}

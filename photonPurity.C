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
#include "uniqueEvents.C"

using namespace std;
//last forward run is 211256

//pp
const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pp2013Data_v2.root";
const TString MC_FILE = "gammaJets_pp_pythia_allQCDPhoton30_ntuple.root";
const TString LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";

//PbPb
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_Data.root";
//const TString MC_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_MC_allQCDPhoton50.root";
//const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV";

//pPb
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pPbData_v2.root";
//const TString MC_FILE = "gammaJets_pA_merged_allQCDPhoton_ntuple_v2.root";
//const TString LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";

// last entry is upper bound on last bin
const Double_t HFBINS[] = {0,1000};//20,30,1000};
const Int_t nHFBINS = sizeof(HFBINS)/sizeof(Double_t) -1;

const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
//const Double_t PTBINS[] = {40, 1000};
const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

const Double_t ETABINS[] = {-1.479, 1.479};
//const Double_t ETABINS[] = {-1.479, -1, -0.5, 0, 0.5, 1, 1.479};
const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

// the bin which holds this value is considered the largest bin when
// computing the purity
const Double_t PURITY_BIN_VAL = 0.00999;
//const Double_t PURITY_BIN_VAL = 0.02699;

const Double_t SHIFTVAL = 0;//-0.00015; //shift signal distribution by this much

void photonPurity()
{
  TH1::SetDefaultSumw2();

  TFile *dataFile = TFile::Open(DATA_FILE);
  TNtuple *dataTuple = (TNtuple*)dataFile->Get("gammaJets");
  use_only_unique_events(dataTuple);

  TFile *mcFile = TFile::Open(MC_FILE);
  TNtuple *mcTuple = (TNtuple*)mcFile->Get("gammaJets");
  use_only_unique_events(mcTuple,"mcid"); //private MC has bad event numbers

  //TCut sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";
  TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
  TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
  TCut mcIsolation = "genCalIsoDR04<5 && abs(genMomId)<=22";

  //TCanvas *cPurity[nPTBINS];  
  TCanvas *cPurity = new TCanvas("c1","c1",1350,600);
  cPurity->Divide(nPTBINS,2,0,0);
  
  for(Int_t i = 0; i < nPTBINS; ++i) {
    //cPurity[i] = new TCanvas(Form("c1_%d",i),"",1920,1000);
    //cPurity[i]->Divide(nETABINS,2,0,0);
    for(Int_t j = 0; j < nHFBINS; ++j) {
      for(Int_t k = 0; k< nETABINS; ++k) {
	TString ptCut = Form("(gPt >= %f) && (gPt < %f)",
			     PTBINS[i], PTBINS[i+1]);
	TString hfCut = Form("((HFplusEta4+HFminusEta4) >= %f) && ((HFplusEta4+HFminusEta4) < %f)",
			     HFBINS[j], HFBINS[j+1]);
	TString etaCut = Form("(gEta >= %f) && (gEta < %f)",
			      ETABINS[k], ETABINS[k+1]);

	TString pPbflipetaCut = Form("(gEta*((run>211257)*-1+(run<211257)) >=%f) && (gEta*((run>211257)*-1+(run<211257)) <%f)",
				     ETABINS[k], ETABINS[k+1]);

	TCut dataCandidateCut = sampleIsolation && etaCut && ptCut && hfCut;
	TCut sidebandCut =  sidebandIsolation && etaCut && ptCut && hfCut;
	TCut mcSignalCut = dataCandidateCut && mcIsolation;
		
	if(nETABINS != 1)
	{
	  dataCandidateCut = sampleIsolation && pPbflipetaCut && ptCut && hfCut;
	  sidebandCut =  sidebandIsolation && pPbflipetaCut && ptCut && hfCut;
	  mcSignalCut =  sampleIsolation && etaCut && ptCut && hfCut && mcIsolation;
	}

	fitResult fitr = getPurity(dataTuple, mcTuple,
				   dataCandidateCut, sidebandCut,
				   mcSignalCut, SHIFTVAL,
				   0.0, PURITY_BIN_VAL);

	//cPurity[i*nHFBINS+j] = new TCanvas(Form("cpurity%d",i*nHFBINS+j),
	// 					 "",500,500);
	cPurity->cd(2*(k+j)*nPTBINS+i+1);
	//cPurity[i]->cd(k+1);

	TH1F *hSigPdf = fitr.sigPdf;
	TH1F *hBckPdf = fitr.bckPdf;
	TH1D *hData1  = fitr.data;

	// plot stacked histos
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
	TLegend *t3=new TLegend(0.54, 0.60, 0.92, 0.79);
	t3->AddEntry(hData1,LABEL,"pl");
	t3->AddEntry(hSigPdf,"Signal","lf");
	t3->AddEntry(hBckPdf,"Background","lf");
	t3->SetFillColor(0);
	t3->SetBorderSize(0);
	t3->SetFillStyle(0);
	t3->SetTextFont(63);
	t3->SetTextSize(15);
	t3->Draw();

	//drawText("|#eta_{#gamma}| < 1.479",0.5680963,0.9);
	drawText(Form("%f shift",SHIFTVAL),0.57,0.82);
	if(nPTBINS != 1)
	  drawText(Form("%.0f < p_{T}^{#gamma} < %.0f",
			PTBINS[i], PTBINS[i+1]),
		   0.57, 0.9);
	if(nHFBINS != 1)
	  drawText(Form("%.0f < E_{T}^{HF[|#eta|>4]} < %.0f",
			HFBINS[j], HFBINS[j+1]),
		   0.57, 0.82);
	if(nETABINS != 1)
	  drawText(Form("%.3f < #eta_{#gamma} < %.3f",
			ETABINS[k], ETABINS[k+1]),
		   0.57, 0.82);		 
	drawText(Form("Purity : %.2f", (Float_t)fitr.purity),
		 0.57, 0.53);
	drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq),
		 0.57, 0.45);

	//plot ratio
	cPurity->cd((2*(j+k)+1)*nPTBINS+i+1);
	//cPurity[i]->cd(nETABINS + k+ 1);
	TH1D* ratio = (TH1D*)hData1->Clone("ratio");
	ratio->Divide(hData1, hSigPdf, 1, 1);
	ratio->SetMinimum(0);
	ratio->SetMaximum(3);
	ratio->SetXTitle("#sigma_{#eta #eta}");
	ratio->GetXaxis()->CenterTitle();      
	ratio->SetYTitle("ratio");
	ratio->GetYaxis()->CenterTitle();
	ratio->DrawCopy("E");
	TLine *line = new TLine(0,1,maxSIGMA,1);
	line->SetLineStyle(2);
	line->Draw("same");

	// TString savename = Form("purity_pA_barrel_pt%.0f_hf%.0f_plot",
	// 			PTBINS[i], HFBINS[j]);
	// cPurity[i*nHFBINS+j]->SaveAs(savename+".C");
	// cPurity[i*nHFBINS+j]->SaveAs(savename+".pdf");
	// cPurity[i*nHFBINS+j]->SaveAs(savename+".png");

      }
    }
    //cPurity[i]->SaveAs(Form("pPb_purity_etadep_wshift_ptbin%.0f.png",PTBINS[i]));
    //cPurity[i]->SaveAs(Form("pPb_purity_etadep_noshift_inclusive.png"));
  }
  //cPurity->SaveAs("pPb_purity_shift.C");
  //cPurity->SaveAs("pPb_purity_shift.png");
  //cPurity->SaveAs("pPb_purity_shift.pdf");
}

int main()
{
  photonPurity();
  return 0;
}

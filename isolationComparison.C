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
#include "uniqueEvents.C"
#include "commonUtility.h"

//pp
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pp2013Data_v2.root";
//const TString MC_FILE = "gammaJets_pp_pythia_allQCDPhoton30_ntuple.root";
//const TString LABEL = "pp #sqrt{s}_{_{NN}}=2.76 TeV";

//PbPb
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_Data.root";
//const TString MC_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_MC_allQCDPhoton50.root";
//const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV";

//pPb
const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pPbData_v2.root";
const TString MC_FILE = "gammaJets_pA_merged_allQCDPhoton_ntuple_v2.root";
const TString LABEL = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";


void isolationComparison()
{
  TFile *mcFile = TFile::Open(MC_FILE);
  TNtuple *mcTuple = (TNtuple*)mcFile->Get("gammaJets");
  use_only_unique_events(mcTuple,"mcid"); //private MC has bad event numbers

  TString stanCut = "(matchedGPt>40)&&(matchedGPt<120)&&(hadronicOverEm<0.1)";
  TString genCut = "(abs(genMomId)<=22)";
  TString stanCut2 = "(gPt>40)&&(gPt<120)&&(hadronicOverEm<0.1)";

  // TCanvas *c1 = new TCanvas("c1","c1");
  // mcTuple->Draw("ecalRecHitSumEtConeDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&(ecalRecHitSumEtConeDR04<10))",
  // 		"colz");
  // mcTuple->Draw("ecalRecHitSumEtConeDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&(ecalRecHitSumEtConeDR04<10))",
  // 		"same prof");
  // c1->SetLogz();

  // TCanvas *c2 = new TCanvas("c2","c2");
  // mcTuple->Draw("hcalTowerSumEtConeDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&(hcalTowerSumEtConeDR04<10))",
  // 		"colz");
  // mcTuple->Draw("hcalTowerSumEtConeDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&(hcalTowerSumEtConeDR04<10))",
  // 		"same prof");
  // c2->SetLogz();

  
  // TCanvas *c3 = new TCanvas("c3","c3");
  // mcTuple->Draw("trkSumPtHollowConeDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&(trkSumPtHollowConeDR04<20))",
  // 		"colz");
  // mcTuple->Draw("trkSumPtHollowConeDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&(trkSumPtHollowConeDR04<20))",
  // 		"same prof");
  // c3->SetLogz();

  
  // TCanvas *c4 = new TCanvas("c4","c4");
  // mcTuple->Draw("genCalIsoDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&"+genCut+"&&(genCalIsoDR04<10))",
  // 		"colz");
  // mcTuple->Draw("genCalIsoDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&"+genCut+"&&(genCalIsoDR04<10))",
  // 		"same prof");
  // c4->SetLogz();

  
  // TCanvas *c5 = new TCanvas("c5","c5");
  // mcTuple->Draw("genTrkIsoDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&"+genCut+"&&(genTrkIsoDR04<10))",
  // 		"colz");
  // mcTuple->Draw("genTrkIsoDR04:matchedGPt",
  // 		"mcweight*("+stanCut+"&&"+genCut+"&&(genTrkIsoDR04<10))",
  // 		"same prof");
  // c5->SetLogz();

  // TCanvas *c6 = new TCanvas("c6","c6");
  // mcTuple->Draw("(cc4+cr4+ct4PtCut20):matchedGPt",
  // 		"mcweight*("+stanCut+"&&((cc4+cr4+ct4PtCut20)<20))",
  // 		"colz");
  // mcTuple->Draw("(cc4+cr4+ct4PtCut20):matchedGPt",
  // 		"mcweight*("+stanCut+"&&((cc4+cr4+ct4PtCut20)<20))",
  // 		"same prof");
  // c6->SetLogz();

  // TCanvas *c1 = new TCanvas("c1","c1");
  // mcTuple->Draw("ecalRecHitSumEtConeDR04:matchedGPt",
  // 		"("+stanCut+"&&(ecalRecHitSumEtConeDR04<10))",
  // 		"colz");
  // mcTuple->Draw("ecalRecHitSumEtConeDR04:matchedGPt",
  // 		"("+stanCut+"&&(ecalRecHitSumEtConeDR04<10))",
  // 		"same prof");
  // c1->SetLogz();

  // TCanvas *c2 = new TCanvas("c2","c2");
  // mcTuple->Draw("hcalTowerSumEtConeDR04:matchedGPt",
  // 		"("+stanCut+"&&(hcalTowerSumEtConeDR04<10))",
  // 		"colz");
  // mcTuple->Draw("hcalTowerSumEtConeDR04:matchedGPt",
  // 		"("+stanCut+"&&(hcalTowerSumEtConeDR04<10))",
  // 		"same prof");
  // c2->SetLogz();

  
  // TCanvas *c3 = new TCanvas("c3","c3");
  // mcTuple->Draw("trkSumPtHollowConeDR04:matchedGPt",
  // 		"("+stanCut+"&&(trkSumPtHollowConeDR04<20))",
  // 		"colz");
  // mcTuple->Draw("trkSumPtHollowConeDR04:matchedGPt",
  // 		"("+stanCut+"&&(trkSumPtHollowConeDR04<20))",
  // 		"same prof");
  // c3->SetLogz();

  
  // TCanvas *c4 = new TCanvas("c4","c4");
  // mcTuple->Draw("genCalIsoDR04:matchedGPt",
  // 		"("+stanCut+"&&"+genCut+"&&(genCalIsoDR04<10))",
  // 		"colz");
  // mcTuple->Draw("genCalIsoDR04:matchedGPt",
  // 		"("+stanCut+"&&"+genCut+"&&(genCalIsoDR04<10))",
  // 		"same prof");
  // c4->SetLogz();

  
  // TCanvas *c5 = new TCanvas("c5","c5");
  // mcTuple->Draw("genTrkIsoDR04:matchedGPt",
  // 		"("+stanCut+"&&"+genCut+"&&(genTrkIsoDR04<10))",
  // 		"colz");
  // mcTuple->Draw("genTrkIsoDR04:matchedGPt",
  // 		"("+stanCut+"&&"+genCut+"&&(genTrkIsoDR04<10))",
  // 		"same prof");
  // c5->SetLogz();

  // TCanvas *c6 = new TCanvas("c6","c6");
  // mcTuple->Draw("(cc4+cr4+ct4PtCut20):matchedGPt",
  // 		"("+stanCut+"&&((cc4+cr4+ct4PtCut20)<20)&&(cc4+cr4+ct4PtCut20)>0)",
  // 		"colz");
  // mcTuple->Draw("(cc4+cr4+ct4PtCut20):matchedGPt",
  // 		"("+stanCut+"&&((cc4+cr4+ct4PtCut20)<20)&&(cc4+cr4+ct4PtCut20)>0)",
  // 		"same prof");
  // c6->SetLogz();


  // TCanvas *c7 = new TCanvas("c7","c7");
  // mcTuple->Draw("ecalRecHitSumEtConeDR04:gPt",
  // 		"("+stanCut2+"&&(ecalRecHitSumEtConeDR04<10))",
  // 		"colz");
  // mcTuple->Draw("ecalRecHitSumEtConeDR04:gPt",
  // 		"("+stanCut2+"&&(ecalRecHitSumEtConeDR04<10))",
  // 		"same prof");
  // c7->SetLogz();

  // TCanvas *c8 = new TCanvas("c8","c8");
  // mcTuple->Draw("hcalTowerSumEtConeDR04:gPt",
  // 		"("+stanCut2+"&&(hcalTowerSumEtConeDR04<10))",
  // 		"colz");
  // mcTuple->Draw("hcalTowerSumEtConeDR04:gPt",
  // 		"("+stanCut2+"&&(hcalTowerSumEtConeDR04<10))",
  // 		"same prof");
  // c8->SetLogz();

  
  // TCanvas *c9 = new TCanvas("c9","c9");
  // mcTuple->Draw("trkSumPtHollowConeDR04:gPt",
  // 		"("+stanCut2+"&&(trkSumPtHollowConeDR04<20))",
  // 		"colz");
  // mcTuple->Draw("trkSumPtHollowConeDR04:gPt",
  // 		"("+stanCut2+"&&(trkSumPtHollowConeDR04<20))",
  // 		"same prof");
  // c9->SetLogz();

  
  // TCanvas *c10 = new TCanvas("c10","c10");
  // mcTuple->Draw("genCalIsoDR04:gPt",
  // 		"("+stanCut2+"&&"+genCut+"&&(genCalIsoDR04<10))",
  // 		"colz");
  // mcTuple->Draw("genCalIsoDR04:gPt",
  // 		"("+stanCut2+"&&"+genCut+"&&(genCalIsoDR04<10))",
  // 		"same prof");
  // c10->SetLogz();

  
  // TCanvas *c11 = new TCanvas("c11","c11");
  // mcTuple->Draw("genTrkIsoDR04:gPt",
  // 		"("+stanCut2+"&&"+genCut+"&&(genTrkIsoDR04<10))",
  // 		"colz");
  // mcTuple->Draw("genTrkIsoDR04:gPt",
  // 		"("+stanCut2+"&&"+genCut+"&&(genTrkIsoDR04<10))",
  // 		"same prof");
  // c11->SetLogz();

  // TCanvas *c12 = new TCanvas("c12","c12");
  // mcTuple->Draw("(cc4+cr4+ct4PtCut20):gPt",
  // 		"("+stanCut2+"&&((cc4+cr4+ct4PtCut20)<20)&&(cc4+cr4+ct4PtCut20)>0)",
  // 		"colz");
  // mcTuple->Draw("(cc4+cr4+ct4PtCut20):gPt",
  // 		"("+stanCut2+"&&((cc4+cr4+ct4PtCut20)<20)&&(cc4+cr4+ct4PtCut20)>0)",
  // 		"same prof");
  // c12->SetLogz();

  const Int_t nSIGMABINS = 100; // number of bins in sigmaIetaIeta dist
  const Double_t maxSIGMA = 0.025; // x-axis max of sigmaIetaIeta dist

  TH1D* hEmpty = new TH1D("hEmpty","",nSIGMABINS,0,maxSIGMA);
  
  const Double_t HFBINS[] = {0,1000};//20,30,1000};
  const Int_t nHFBINS = sizeof(HFBINS)/sizeof(Double_t) -1;

  const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
//const Double_t PTBINS[] = {40, 1000};
  const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

  //const Double_t ETABINS[] = {-1.479, 1.479};
  const Double_t ETABINS[] = {-1.479, -1, -0.5, 0, 0.5, 1, 1.479};
  const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

  for(Int_t i = 0; i < nPTBINS; ++i) {
    for(Int_t j = 0; j < nHFBINS; ++j) {
      for(Int_t k = 0; k< nETABINS; ++k) {
	TString ptCut = Form("(gPt >= %f) && (gPt < %f)",
			     PTBINS[i], PTBINS[i+1]);
	TString hfCut = Form("((HFplusEta4+HFminusEta4) >= %f) && ((HFplusEta4+HFminusEta4) < %f)",
			     HFBINS[j], HFBINS[j+1]);
	TString etaCut = Form("(gEta >= %f) && (gEta < %f)",
			      ETABINS[k], ETABINS[k+1]);
	TCut genMatched = "matchedGPt>0";
	TCut mcSig = "genCalIsoDR04<5 && abs(genMomId)<=22";
	TCut mcBkg = "!(genCalIsoDR04<5 && abs(genMomId)<=22)";

	TCut sig = mcSig && ptCut && hfCut && etaCut && genMatched;
	TCut bkg = mcBkg && ptCut && hfCut && etaCut && genMatched;

	TCanvas *c = new TCanvas(Form("c%d%d%d",i,j,k),"",500,500);
	TH1D *hSig = (TH1D*)hEmpty->Clone(Form("h%d%d%dsig",i,j,k));
	TH1D *hBkg = (TH1D*)hEmpty->Clone(Form("h%d%d%dbkg",i,j,k));

	mcTuple->Project(Form("h%d%d%dsig",i,j,k),"sigmaIetaIeta","mcweight"*sig);
	mcTuple->Project(Form("h%d%d%dbkg",i,j,k),"sigmaIetaIeta","mcweight"*bkg);

	hSig->Draw();
	hBkg->SetMarkerColor(kBlue);
	hBkg->SetLineColor(kBlue);
	hBkg->Draw("same");

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
		   0.57, 0.76);		 


      }
    }
  }

  

}

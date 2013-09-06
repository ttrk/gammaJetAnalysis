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

using namespace std;

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


void isolationEfficiency()
{
  TFile *mcFile = TFile::Open(MC_FILE);
  TNtuple *mcTuple = (TNtuple*)mcFile->Get("gammaJets");
  use_only_unique_events(mcTuple,"mcid"); //private MC has bad event numbers

  // const Int_t nSIGMABINS = 100; // number of bins in sigmaIetaIeta dist
  // const Double_t maxSIGMA = 0.025; // x-axis max of sigmaIetaIeta dist

  // TH1D* hEmpty = new TH1D("hEmpty","",nSIGMABINS,0,maxSIGMA);
  
  const Double_t HFBINS[] = {0,1000};//20,30,1000};
  const Int_t nHFBINS = sizeof(HFBINS)/sizeof(Double_t) -1;

  const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
//const Double_t PTBINS[] = {40, 1000};
  const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

  //const Double_t ETABINS[] = {-1.479, 1.479};
  const Double_t ETABINS[] = {-1.479, -1, -0.5, 0, 0.5, 1, 1.479};
  const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

  const TCut mcIso = "hadroniceOverEm<0.1 && matchedGPt>0 && genCalIsoDR04<5 && abs(genMomId)<=22";
  const TCut dataIso = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";

  for(Int_t i = 0; i < nPTBINS; ++i) {
    for(Int_t j = 0; j < nHFBINS; ++j) {
      for(Int_t k = 0; k< nETABINS; ++k) {
	TString ptCut = Form("(gPt >= %f) && (gPt < %f)",
			     PTBINS[i], PTBINS[i+1]);
	TString hfCut = Form("((HFplusEta4+HFminusEta4) >= %f) && ((HFplusEta4+HFminusEta4) < %f)",
			     HFBINS[j], HFBINS[j+1]);
	TString etaCut = Form("(gEta >= %f) && (gEta < %f)",
			      ETABINS[k], ETABINS[k+1]);

	TCut gen = mcIso && ptCut && hfCut && etaCut;
	TCut data = dataIso && mcIso && ptCut && hfCut && etaCut;

	Long64_t tot = mcTuple->Draw("gPt", gen);
	Long64_t pass = mcTuple->Draw("gPt", data);

	Double_t eff = ((Double_t)pass)/((Double_t)tot);

	cout << "pT: " << PTBINS[i] << " HF: " << HFBINS[j] << " Eta: " << ETABINS[k] << " Eff: " << eff << endl; 

      }
    }
  }

  

}

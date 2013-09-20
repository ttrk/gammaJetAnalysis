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

void isolationEfficiency()
{
  TH1::SetDefaultSumw2();

  TString MC_FILES[3];
  TString LABEL[3];
//pp
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pp2013Data_v2.root";
  MC_FILES[0] = "gammaJets_pp_pythia_allQCDPhoton_ntuple.root";
  LABEL[0] = "pp pythia";

//PbPb
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_PbPb2011_Data.root";
  MC_FILES[1] = "gammaJets_PbPb_pythiaHydjet_allQCDPhoton_ntuple.root";
  LABEL[1] = "PbPb pythia+HYDJET";

//pPb
//const TString DATA_FILE = "gammaJets_inclusive_dphi7pi8_pPbData_v2.root";
  MC_FILES[2] = "gammaJets_pA_merged_allQCDPhoton_ntuple_v2.root";
  LABEL[2] = "pPb pythia+HIJING";

  //const Double_t HFBINS[] = {0,20,30,1000};
  //const Double_t HFBINS[] = {0,1000};
  //const Int_t nHFBINS = sizeof(HFBINS)/sizeof(Double_t) -1;

  //const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
  //const Double_t PTBINS[] = {40, 1000};
  //const Double_t PTBINS[] = {40, 42.5, 45, 47.5, 50, 52.5, 55, 57.5, 60, 62.5, 65, 67.5, 70, 72.5, 75, 77.5, 80};
  //const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

  // const Double_t ptMax = 150;
  // const Double_t ptMin = 40;
  // const Double_t binWidth = 2.5;
  // const Int_t nPTBINS = (Int_t)((ptMax-ptMin)/binWidth);
  const Double_t etaMax = 1.479;
  const Double_t etaMin = -1.479;
  const Int_t nETABINS = 100;
  const TString var = "matchedGEta";
  const TString xlabel = "gen #eta^{#gamma}";
  
    //const Double_t ETABINS[] = {-1.479, 1.479};
  //const Double_t ETABINS[] = {-1.479, -1, -0.5, 0, 0.5, 1, 1.479};
  //const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

  const TCut mcIso = "hadronicOverEm<0.1 && matchedGPt>0 && genCalIsoDR04<5 && abs(genMomId)<=22";
  TCut dataIso[3];
  dataIso[0] = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2";
  dataIso[1] = "cc4 + cr4 + ct4PtCut20 < 1.0";
  dataIso[2] = dataIso[0];
  
  
  TCanvas *c1 = new TCanvas();
  // TH1D *hEmpty = new TH1D("hEmpty","hEmpty",nPTBINS,ptMin,ptMax);
  // hEmpty->SetXTitle("gen p_{T}^{#gamma}");
  TH1D *hEmpty = new TH1D("hEmpty","hEmpty",nETABINS,etaMin,etaMax);
  hEmpty->SetXTitle(xlabel);
  hEmpty->GetXaxis()->CenterTitle();
  hEmpty->SetYTitle("Isolation Efficiency");
  hEmpty->GetYaxis()->CenterTitle();
  //hEmpty->SetMinimum(0.7);
  //hEmpty->SetMaximum(1.0);
  hEmpty->Draw();
  TLegend *leg = new TLegend(0.55,0.45,0.9,0.65);
  leg->SetFillColor(0);
  
  for(int i = 0; i < 3; i++)
  {
    TFile *mcFile = TFile::Open(MC_FILES[i]);
    TNtuple *mcTuple = (TNtuple*)mcFile->Get("gammaJets");
    use_only_unique_events(mcTuple,"mcid"); //private MC has bad event numbers

    TH1D *pass = (TH1D*)hEmpty->Clone("pass");
    TH1D *tot = (TH1D*)hEmpty->Clone("tot");

    mcTuple->Project("tot",var,"mcweight"*mcIso);
    mcTuple->Project("pass",var,"mcweight"*(mcIso&&dataIso[i]));

    TGraphAsymmErrors *eff = new TGraphAsymmErrors(pass,tot,"cl=0.683 b(1,1) mode");
//    eff->BayesDivide(pass,tot);
    eff->SetMarkerColor(i+1);
    eff->DrawClone("same P");
    leg->AddEntry(eff,LABEL[i],"p");
  }
  leg->Draw("same");
  
  
  
  // for(Int_t i = 0; i < nPTBINS; ++i) {
  //   for(Int_t j = 0; j < nHFBINS; ++j) {
  //     for(Int_t k = 0; k< nETABINS; ++k) {
  // 	TString ptCut = Form("(gPt >= %f) && (gPt < %f)",
  // 			     PTBINS[i], PTBINS[i+1]);
  // 	TString hfCut = Form("((HFplusEta4+HFminusEta4) >= %f) && ((HFplusEta4+HFminusEta4) < %f)",
  // 			     HFBINS[j], HFBINS[j+1]);
  // 	TString etaCut = Form("(gEta >= %f) && (gEta < %f)",
  // 			      ETABINS[k], ETABINS[k+1]);

  // 	TCut gen = mcIso && ptCut && hfCut && etaCut;
  // 	TCut data = dataIso && mcIso && ptCut && hfCut && etaCut;

  // 	Long64_t tot = mcTuple->GetEntries(gen);
  // 	Long64_t pass = mcTuple->GetEntries(data);

  // 	Double_t eff = ((Double_t)pass)/((Double_t)tot);

  // 	//cout << "pT: " << PTBINS[i] << " HF: " << HFBINS[j] << " Eta: " << ETABINS[k] << " Eff: " << eff << endl;
  // 	cout << "pT: " << PTBINS[i] << " Eff: " << eff << endl;

  //     }
  //   }
  // }

  

}

int main()
{
  isolationEfficiency();
  return 0;
}

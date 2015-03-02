#include "../../HiForestAnalysis/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>
#include <TStyle.h>


void drawPhotonSpec(){
  


  TH1::SetDefaultSumw2();
  
  TFile* f1 = new TFile("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_DATA_photon30trig_localJEC_v1.root");
  TTree* photon = (TTree*)f1->Get("multiPhotonAnalyzer/photon");
  TTree* hlt    = (TTree*)f1->Get("hltanalysis/HltTree");
  hlt->SetName("hlt");
  photon->AddFriend(hlt);
  
  TH1D* h1 = new TH1D("h1",";p_{T} of photon;Entries (Arb. Norm.)",200,0,200);
  // TCut ccut = "abs(eta)<1.44 && hlt.HLT_PAPhoton20_NoCaloIdVL_v1 && hadronicOverEm<0.1";
  TCut ccut = "abs(eta)<1.44 && hadronicOverEm<0.1";
  photon->Draw("pt>>h1",ccut);
  TH1D* h2 = (TH1D*)h1->Clone("h2");
  photon->Draw("pt>>h2",ccut && "!isEle");

  TCut isocut = "sigmaIetaIeta<0.011 && ecalRecHitSumEtConeDR04<4.2 && hcalTowerSumEtConeDR04< 2.2 && trkSumPtHollowConeDR04 <2";

  TH1D* h3 = (TH1D*)h1->Clone("h3");
  photon->Draw("pt>>h3",ccut && isocut);
  
  TH1D* h4 = (TH1D*)h1->Clone("h4");
  photon->Draw("pt>>h4",ccut && isocut && "!isEle");

  
  handsomeTH1(h1,1);
  handsomeTH1(h2,2);
  handsomeTH1(h3,1);
  handsomeTH1(h4,2);
  

  TCanvas* c1 = new TCanvas("c1","",1000,500);
  c1->Divide(2,1);
  c1->cd(1);
  //h1->SetAxisRange(0.5, 80000,"Y");
  h1->Draw("hist" );
  h2->Draw("same hist");

  TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
  easyLeg(l1,"5.02TeV pA Data");
  l1->SetTextFont(43);
  l1->SetTextSize(16);
  l1->Draw();
  TLegend *l2 = new TLegend(0.6365615,0.4445304,0.9577623,0.646736,NULL,"brNDC");
  easyLeg(l2,"Barrel photons H/E<0.1");
  l2->SetTextFont(43);
  l2->SetTextSize(16);
  l2->AddEntry(h1, "All");
  l2->AddEntry(h2, "Electrons excluded");
  l2->Draw();

  
  c1->cd(2);
  //h3->SetAxisRange(0.5, 2500,"Y");
  h3->Draw("hist");
  h4->Draw("same hist");
  TLegend *l3 = new TLegend(0.6365615,0.4445304,0.9577623,0.646736,NULL,"brNDC");
  easyLeg(l3,"Isolated photons");
  l3->SetTextFont(43);
  l3->SetTextSize(16);
  l3->AddEntry(h3, "All");
  l3->AddEntry(h4, "Electrons excluded");
  l3->Draw();

  
}


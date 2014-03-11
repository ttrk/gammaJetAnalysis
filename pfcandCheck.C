// Author Alex Barbieri
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TMath.h"
#include "TProfile.h"
#include "TChain.h"
#include "TCut.h"
#include "stdio.h"
//#include "../HiForestAnalysis/hiForest.h"

void pfcandCheck()
{
  TChain *rereco = new TChain("pfcandAnalyzer/pfTree");
  // Minbias Hydjet sample
  rereco->Add("/mnt/hadoop/cms/store/user/rkunnawa/rootfiles/PbPb/2011/mc/PbPb_MinBias_Hydjet_STARTHI53_LV1_track8_Jet5_FOREST_6Feb2014_mergedv1.root");
  // pythia 80 sample
  //rereco->Add("/mnt/hadoop/cms/store/user/dgulhan/HIMC/Jet80/Track8_Jet6_STARTHI53_LV1/merged2/HiForest_Pythia_Hydjet_Jet80_Track8_Jet6_STARTHI53_LV1_merged_forest_0.root");

  TChain *old = new TChain("pfcandAnalyzer/pfTree");
  // Minbias Hydjet sample
  old->Add("/mnt/hadoop/cms/store/user/yetkin/MC_Production/HydjetDrum03/HydjetDrum03_HiForest_v05_merged_test02.root");
  // pythia 80 sample
  //old->Add("/mnt/hadoop/cms/store/user/yenjie/HiForest_v27/Dijet80_HydjetDrum_v27_mergedV1.root");

  const TCut photonCut = "pfId==4";
  const TCut ptCut = "pfPt>1";
  const TCut etaCut = "abs(pfEta)<3";

  int rerecoEntries = rereco->GetEntries();
  int oldEntries = old->GetEntries();


  TH1D *pt0 = new TH1D("pt0","pt0;pf p_{T}^{#gamma}",50,0,150);
  TH1D *pt1 = (TH1D*)pt0->Clone("pt1");
  TH1D *eta0 = new TH1D("eta0","eta0;pf #eta^{#gamma}",25, -5, 5);
  TH1D *eta1 = (TH1D*)eta0->Clone("eta1");
  TH1D *phi0 = new TH1D("phi0","phi0;pf #phi^{#gamma}",20, -TMath::Pi(), TMath::Pi());
  TH1D *phi1 = (TH1D*)phi0->Clone("phi1");
  TH2D *map0 = new TH2D("map0","map0;pf #eta;pf #phi",50, -5, 5,150, -TMath::Pi(), TMath::Pi());
  TH2D *map1 = (TH2D*)map0->Clone("map1");

  // TH2D *ptrat0 = new TH2D("ptrat0","ptrat0;pf p_{T}^{gen #gamma};pf p_{T}^{reco #gamma}",50,0,150,50,0,150);
  // TH2D *ptrat1 = (TH2D*)ptrat0->Clone("ptrat1");


  rereco->Project(pt0->GetName(), "pfPt",photonCut&&etaCut);
  old->Project(pt1->GetName(),"pfPt",photonCut&&etaCut);
  rereco->Project(eta0->GetName(),"pfEta",photonCut&&ptCut&&etaCut);
  old->Project(eta1->GetName(),"pfEta",photonCut&&ptCut&&etaCut);
  rereco->Project(phi0->GetName(),"pfPhi",photonCut&&ptCut&&etaCut);
  old->Project(phi1->GetName(),"pfPhi",photonCut&&ptCut&&etaCut);
  rereco->Project(map0->GetName(),"pfPhi:pfEta",photonCut&&ptCut&&etaCut);
  old->Project(map1->GetName(),"pfPhi:pfEta",photonCut&&ptCut&&etaCut);

  // rereco->Project(ptrat0->GetName(),"pt:genMatchedPt");
  // old->Project(ptrat1->GetName(),"pt:genMatchedPt");

  pt0->Scale(1./rerecoEntries);
  pt1->Scale(1./oldEntries);
  eta0->Scale(1./rerecoEntries);
  eta1->Scale(1./oldEntries);
  phi0->Scale(1./rerecoEntries);
  phi1->Scale(1./oldEntries);
  map0->Scale(1./rerecoEntries);
  map1->Scale(1./oldEntries);

  TCanvas *c1 = new TCanvas();
  pt0->SetMaximum(pt0->GetMaximum()*2);
  pt0->Draw();
  pt1->SetMarkerColor(kBlue);
  pt1->SetLineColor(kBlue);
  pt1->Draw("same");
  c1->SetLogy();

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(20);
  leg->AddEntry(pt0,"53X","l");
  leg->AddEntry(pt1,"44X","l");
  leg->AddEntry("", ptCut, "");
  leg->AddEntry("", etaCut, "");
  leg->Draw();

  c1->SaveAs("rereco_pf/temp/pt.pdf");

  TCanvas *c2 = new TCanvas();
  eta0->SetMinimum(0);
  eta0->SetMaximum(eta0->GetMaximum()*2);
  eta0->Draw();
  eta1->SetMarkerColor(kBlue);
  eta1->SetLineColor(kBlue);
  eta1->Draw("same");
  leg->Draw();
  c2->SaveAs("rereco_pf/temp/eta_pt1.pdf");

  TCanvas *c3 = new TCanvas();
  phi0->SetMinimum(0);
  phi0->SetMaximum(phi0->GetMaximum()*2);
  phi0->Draw();
  phi1->SetMarkerColor(kBlue);
  phi1->SetLineColor(kBlue);
  phi1->Draw("same");
  leg->Draw();
  c3->SaveAs("rereco_pf/temp/phi_pt1.pdf");

  TCanvas *c4 = new TCanvas();
  map0->Draw("colz");

  TLegend *newleg = new TLegend(0.6,0.6,0.9,0.9);
  newleg->SetFillColor(0);
  newleg->SetTextFont(43);
  newleg->SetTextSize(20);
  newleg->AddEntry(map0,"53X","");
  newleg->AddEntry("", ptCut, "");
  newleg->AddEntry("", etaCut, "");
  newleg->Draw();
  
  c4->SaveAs("rereco_pf/temp/map_new_pt1.pdf");

  TCanvas *c5 = new TCanvas();
  map1->Draw("colz");

  TLegend *oldleg = new TLegend(0.6,0.6,0.9,0.9);
  oldleg->SetFillColor(0);
  oldleg->SetTextFont(43);
  oldleg->SetTextSize(20);
  oldleg->AddEntry(map1,"44X","");
  oldleg->AddEntry("", ptCut, "");
  oldleg->AddEntry("", etaCut, "");
  oldleg->Draw();

  c5->SaveAs("rereco_pf/temp/map_old_pt1.pdf");

  // TCanvas *c10 = new TCanvas();
  // ptrat0->Draw("colz");
  // ptrat0->ProfileX("prof0")->Draw("same");
  // c10->SetLogz();
  // newleg->Draw();
  // c10->SaveAs("rereco_pf/temp/corr_new_pt1.pdf");

  // TCanvas *c11 = new TCanvas();
  // ptrat1->Draw("colz");
  // ptrat1->ProfileX("prof1")->Draw("same");
  // c11->SetLogz();
  // oldleg->Draw();
  // c11->SaveAs("rereco_pf/temp/corr_old_pt1.pdf");
}

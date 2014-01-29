// Author Alex Barbieri
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TMath.h"
#include "TProfile.h"
#include "stdio.h"
#include "../HiForestAnalysis/hiForest.h"

void rerecoCheck()
{
  TChain *rereco = new TChain("multiPhotonAnalyzer/photon");
  //rereco->Add("/mnt/hadoop/cms/store/user/yilmaz/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/Pythia120_53X_Forest_v07/44131966334d6296dcbf30383a8b4bec/*.root");
  //rereco->Add("/mnt/hadoop/cms/store/user/pkurt/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/HydjetDrum1p8_d20131230_HiForest/1fb4b6329918f381951bdf05deaffbfc/*.root");
  rereco->Add("/mnt/hadoop/cms/store/user/dgulhan/Hydjet1p8_TuneDrum_Quenched_MinBias_27/merged_forest_2/merged_forest_Hydjet1p8_TuneDrum_Quenched_MinBias_27.root");

  TChain *old = new TChain("multiPhotonAnalyzer/photon");
  //old->Add("/mnt/hadoop/cms/store/user/yenjie/HiForest_v28/Dijet120_HydjetDrum_v28_mergedV1.root");
  old->Add("/mnt/hadoop/cms/store/user/yetkin/MC_Production/HydjetDrum03/HydjetDrum03_HiForest_v05_merged_test02.root");

  TH1D *pt0 = new TH1D("pt0","pt0;p_{T}^{#gamma}",50,0,150);
  TH1D *pt1 = (TH1D*)pt0->Clone("pt1");
  TH1D *eta0 = new TH1D("eta0","eta0;#eta^{#gamma}",50, -5, 5);
  TH1D *eta1 = (TH1D*)eta0->Clone("eta1");
  TH1D *phi0 = new TH1D("phi0","phi0;#phi^{#gamma}",50, -TMath::Pi(), TMath::Pi());
  TH1D *phi1 = (TH1D*)phi0->Clone("phi1");
  TH2D *map0 = new TH2D("map0","map0;#eta;#phi",50, -5, 5,150, -TMath::Pi(), TMath::Pi());
  TH2D *map1 = (TH2D*)map0->Clone("map1");

  TH2D *ptrat0 = new TH2D("ptrat0","ptrat0;p_{T}^{gen #gamma};p_{T}^{reco #gamma}",50,0,150,50,0,150);
  TH2D *ptrat1 = (TH2D*)ptrat0->Clone("ptrat1");

  const TCut ptCut = "pt>20";
  const TCut etaCut = "abs(eta)<1.479";

  int rerecoEntries = rereco->GetEntries();
  int oldEntries = old->GetEntries();

  rereco->Project(pt0->GetName(), "pt",etaCut);
  old->Project(pt1->GetName(),"pt",etaCut);
  rereco->Project(eta0->GetName(),"eta",ptCut&&etaCut);
  old->Project(eta1->GetName(),"eta",ptCut&&etaCut);
  rereco->Project(phi0->GetName(),"phi",ptCut&&etaCut);
  old->Project(phi1->GetName(),"phi",ptCut&&etaCut);
  rereco->Project(map0->GetName(),"phi:eta",ptCut&&etaCut);
  old->Project(map1->GetName(),"phi:eta",ptCut&&etaCut);

  rereco->Project(ptrat0->GetName(),"pt:genMatchedPt");
  old->Project(ptrat1->GetName(),"pt:genMatchedPt");


  // pt0->Scale(1./pt0->Integral());
  // pt1->Scale(1./pt1->Integral());
  // eta0->Scale(1./eta0->Integral());
  // eta1->Scale(1./eta1->Integral());
  // phi0->Scale(1./phi0->Integral());
  // phi1->Scale(1./phi1->Integral());
  // map0->Scale(1./map0->Integral());
  // map1->Scale(1./map1->Integral());
  pt0->Scale(1./rerecoEntries);
  pt1->Scale(1./oldEntries);
  eta0->Scale(1./rerecoEntries);
  eta1->Scale(1./oldEntries);
  phi0->Scale(1./rerecoEntries);
  phi1->Scale(1./oldEntries);
  map0->Scale(1./rerecoEntries);
  map1->Scale(1./oldEntries);

  

  TCanvas *c1 = new TCanvas();
  pt0->Draw();
  pt1->SetMarkerColor(kBlue);
  pt1->SetLineColor(kBlue);
  pt1->Draw("same");
  c1->SetLogy();
  c1->SaveAs("rereco/barrel/pt.pdf");

  TCanvas *c2 = new TCanvas();
  eta0->Draw();
  eta1->SetMarkerColor(kBlue);
  eta1->SetLineColor(kBlue);
  eta1->Draw("same");
  c2->SaveAs("rereco/barrel/eta_pt20.pdf");

  TCanvas *c3 = new TCanvas();
  phi0->Draw();
  phi1->SetMarkerColor(kBlue);
  phi1->SetLineColor(kBlue);
  phi1->Draw("same");
  c3->SaveAs("rereco/barrel/phi_pt20.pdf");

  TCanvas *c4 = new TCanvas();
  map0->Draw("colz");
  c4->SaveAs("rereco/barrel/map_new_pt20.pdf");

  TCanvas *c5 = new TCanvas();
  map1->Draw("colz");
  c5->SaveAs("rereco/barrel/map_old_pt20.pdf");

  TCanvas *c10 = new TCanvas();
  ptrat0->Draw("colz");
  ptrat0->ProfileX("prof0")->Draw("same");
  c10->SetLogz();
  c10->SaveAs("rereco/barrel/corr_new_pt20.pdf");

  TCanvas *c11 = new TCanvas();
  ptrat1->Draw("colz");
  ptrat1->ProfileX("prof1")->Draw("same");
  c11->SetLogz();
  c11->SaveAs("rereco/barrel/corr_old_pt20.pdf");

  //isolation vars
  TH1D *cc40 = new TH1D("cc40","cc40;cc4",50,-50, 150);
  TH1D *cc41 = (TH1D*)cc40->Clone("cc41");
  TH1D *cr40 = new TH1D("cr40","cr40;cr4",50,-50,350);
  TH1D *cr41 = (TH1D*)cr40->Clone("cr41");
  TH1D *ct4PtCut200 = new TH1D("ct4PtCut200","ct4PtCut200;ct4PtCut20",50,-50,350);
  TH1D *ct4PtCut201 = (TH1D*)ct4PtCut200->Clone("ct4PtCut201");
  TH1D *genCalIsoDR040 = new TH1D("genCalIsoDR040","genCalIsoDR040;genCalIsoDR04",50,0,500);
  TH1D *genCalIsoDR041 = (TH1D*)genCalIsoDR040->Clone("genCalIsoDR041");
  TH1D *sigmaIetaIeta0 = new TH1D("sigmaIetaIeta0",";#sigma_{#eta#eta}",50, 0, 0.05);
  TH1D *sigmaIetaIeta1 = (TH1D*)sigmaIetaIeta0->Clone("sigmaIetaIeta1");

  rereco->Project(cc40->GetName(),"cc4",ptCut&&etaCut);
  old->Project(cc41->GetName(),"cc4",ptCut&&etaCut);
  rereco->Project(cr40->GetName(),"cr4",ptCut&&etaCut);
  old->Project(cr41->GetName(),"cr4",ptCut&&etaCut);
  rereco->Project(ct4PtCut200->GetName(),"ct4PtCut20",ptCut&&etaCut);
  old->Project(ct4PtCut201->GetName(),"ct4PtCut20",ptCut&&etaCut);
  rereco->Project(genCalIsoDR040->GetName(),"genCalIsoDR04",ptCut&&etaCut);
  old->Project(genCalIsoDR041->GetName(),"genCalIsoDR04",ptCut&&etaCut);
  rereco->Project(sigmaIetaIeta0->GetName(),"sigmaIetaIeta",ptCut&&etaCut);
  old->Project(sigmaIetaIeta1->GetName(),"sigmaIetaIeta",ptCut&&etaCut);

  // cc40->Scale(1./cc40->Integral());
  // cc41->Scale(1./cc41->Integral());
  // cr40->Scale(1./cr40->Integral());
  // cr41->Scale(1./cr41->Integral());
  // ct4PtCut200->Scale(1./ct4PtCut200->Integral());
  // ct4PtCut201->Scale(1./ct4PtCut201->Integral());
  // genCalIsoDR040->Scale(1./genCalIsoDR040->Integral());
  // genCalIsoDR041->Scale(1./genCalIsoDR041->Integral());
  // sigmaIetaIeta0->Scale(1./sigmaIetaIeta0->Integral());
  // sigmaIetaIeta1->Scale(1./sigmaIetaIeta1->Integral());
  cc40->Scale(1./rerecoEntries);
  cc41->Scale(1./oldEntries);
  cr40->Scale(1./rerecoEntries);
  cr41->Scale(1./oldEntries);
  ct4PtCut200->Scale(1./rerecoEntries);
  ct4PtCut201->Scale(1./oldEntries);
  genCalIsoDR040->Scale(1./rerecoEntries);
  genCalIsoDR041->Scale(1./oldEntries);
  sigmaIetaIeta0->Scale(1./rerecoEntries);
  sigmaIetaIeta1->Scale(1./oldEntries);

  TCanvas *c6 = new TCanvas();
  cc40->Draw();
  cc41->SetMarkerColor(kBlue);
  cc41->SetLineColor(kBlue);
  cc41->Draw("same");
  c6->SetLogy();
  c6->SaveAs("rereco/barrel/cc4_pt20.pdf");

  TCanvas *c7 = new TCanvas();
  cr40->Draw();
  cr41->SetMarkerColor(kBlue);
  cr41->SetLineColor(kBlue);
  cr41->Draw("same");
  c7->SetLogy();
  c7->SaveAs("rereco/barrel/cr4_pt20.pdf");
  
  TCanvas *c8 = new TCanvas();
  ct4PtCut200->Draw();
  ct4PtCut201->SetMarkerColor(kBlue);
  ct4PtCut201->SetLineColor(kBlue);
  ct4PtCut201->Draw("same");
  c8->SetLogy();
  c8->SaveAs("rereco/barrel/ct4PtCut20_pt20.pdf");

  TCanvas *c9 = new TCanvas();
  genCalIsoDR040->Draw();
  genCalIsoDR041->SetMarkerColor(kBlue);
  genCalIsoDR041->SetLineColor(kBlue);
  genCalIsoDR041->Draw("same");
  c9->SetLogy();
  c9->SaveAs("rereco/barrel/genCalIsoDR04_pt20.pdf");

  TCanvas *c12 = new TCanvas();
  sigmaIetaIeta0->Draw();
  sigmaIetaIeta1->SetMarkerColor(kBlue);
  sigmaIetaIeta1->SetLineColor(kBlue);
  sigmaIetaIeta1->Draw("same");
  c12->SaveAs("rereco/barrel/sigmaIetaIeta_pt20.pdf");
  

}
  

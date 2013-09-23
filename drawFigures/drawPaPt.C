#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>


void drawPaPt(){
  
  TCanvas* c1 = new TCanvas("c1","",500,500);
 
  TFile* f1 = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr40_to_50_jetPtThr30_20130906.root");
  TH1D* hd1 = (TH1D*)f1->Get("jetPt_icent1_final");
  TFile* f2 = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr50_to_60_jetPtThr30_20130906.root");
  TH1D* hd2 = (TH1D*)f2->Get("jetPt_icent1_final");
  TFile* f3 = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr60_to_80_jetPtThr30_20130906.root");
  TH1D* hd3 = (TH1D*)f3->Get("jetPt_icent1_final");
  TFile* f4 = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr80_to_9999_jetPtThr30_20130906.root");
  TH1D* hd4 = (TH1D*)f4->Get("jetPt_icent1_final");

  TFile* f1m = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbMC_output_photonPtThr40_to_50_jetPtThr30_20130906.root");
  TH1D* hm1 = (TH1D*)f1m->Get("jetPt_icent1_final");
  TFile* f2m = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbMC_output_photonPtThr50_to_60_jetPtThr30_20130906.root");
  TH1D* hm2 = (TH1D*)f2m->Get("jetPt_icent1_final");
  TFile* f3m = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbMC_output_photonPtThr60_to_80_jetPtThr30_20130906.root");
  TH1D* hm3 = (TH1D*)f3m->Get("jetPt_icent1_final");
  TFile* f4m = new TFile("/home/jazzitup/analysis/photonJetAnalysis2013/histogramProducer/ffFiles/photonTrackCorr_ppbMC_output_photonPtThr80_to_9999_jetPtThr30_20130906.root");
  TH1D* hm4 = (TH1D*)f4m->Get("jetPt_icent1_final");

  double ptBinPaDraw[5] = { 40.5 ,49.5, 58.5,  76.5,  123. } ;
  TH1D* hd = new TH1D("ptmeanDAta",";p_{T}^{#gamma}; <p_{T}^{Jet}>",4,ptBinPaDraw);
  hd->SetBinContent(1, hd1->GetMean());
  hd->SetBinContent(2, hd2->GetMean());
  hd->SetBinContent(3, hd3->GetMean());
  hd->SetBinContent(4, hd4->GetMean());
  hd->SetBinError(1, hd1->GetMeanError());
  hd->SetBinError(2, hd2->GetMeanError());
  hd->SetBinError(3, hd3->GetMeanError());
  hd->SetBinError(4, hd4->GetMeanError());

  TH1D* hm = new TH1D("ptmeanDAta",";p_{T}^{#gamma}; <p_{T}^{Jet}>",4,ptBinPaDraw);
  hm->SetBinContent(1, hm1->GetMean());
  hm->SetBinContent(2, hm2->GetMean());
  hm->SetBinContent(3, hm3->GetMean());
  hm->SetBinContent(4, hm4->GetMean());
  hm->SetBinError(1, hm1->GetMeanError());
  hm->SetBinError(2, hm2->GetMeanError());
  hm->SetBinError(3, hm3->GetMeanError());
  hm->SetBinError(4, hm4->GetMeanError());



  handsomeTH1(hd,2);
  handsomeTH1(hm,1);
  hm->SetMarkerStyle(24);
  hd->SetAxisRange(30,95,"Y");
  hm->SetAxisRange(30,95,"Y");
  hm->Draw();
  hd->Draw("same");
  TLegend *l1 = new TLegend(0.2399194,0.7288136,0.7862903,0.9322034,NULL,"brNDC");
  easyLeg(l1,"5.02TeV pPb MinBias");
  l1->AddEntry(hd, "DATA","p");
  l1->AddEntry(hm, "MC","p");
  l1->Draw();

  c1->SaveAs("pT_dependence_jetPt_ppb.pdf");
}


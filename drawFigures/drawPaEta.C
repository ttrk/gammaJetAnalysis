#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawPaEta( bool saveFigures=false) {
  TFile * fData = new TFile("../histogramProducer/ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr40_to_9999_jetPtThr30_20130829.root");
  TH1D* hD1 = (TH1D*)fData->Get("etaJg_icent1_final");
  TH1D* hD2 = (TH1D*)fData->Get("etaJg_icent2_final");
  TH1D* hD3 = (TH1D*)fData->Get("etaJg_icent3_final");

  TFile * fMC = new TFile("../histogramProducer/ffFiles/photonTrackCorr_ppbMC_output_photonPtThr40_to_9999_jetPtThr30_20130829.root");
  TH1D* hM1 = (TH1D*)fMC->Get("etaJg_icent1_final");
  TH1D* hM2 = (TH1D*)fMC->Get("etaJg_icent2_final");
  TH1D* hM3 = (TH1D*)fMC->Get("etaJg_icent3_final");

  TCanvas* c1 = new TCanvas("c1","",500,500);
  handsomeTH1(hD1,1);
  handsomeTH1(hD2,4);
  handsomeTH1(hD3,2);
  hD1->Rebin(10);
  hD2->Rebin(10);
  hD3->Rebin(10);

  hD1->Draw();
  hD2->Draw("same");
  hD3->Draw("same");

  TCanvas* c2 = new TCanvas("c2","",400,400);
  TH1D* hmData = new TH1D("hmData",";HF energy;",nCentBinPa,centBinPa);
  hmData->SetBinContent(1, hD1->GetMean());
  hmData->SetBinContent(2, hD2->GetMean());
  hmData->SetBinContent(3, hD3->GetMean());
  hmData->SetBinError(1, hD1->GetMeanError());
  hmData->SetBinError(2, hD2->GetMeanError());
  hmData->SetBinError(3, hD3->GetMeanError());
  TH1D* hmMc = new TH1D("hmMc",";HF energy;",nCentBinPa,centBinPa);
  hmMc->SetBinContent(1, hM1->GetMean());
  hmMc->SetBinContent(2, hM2->GetMean());
  hmMc->SetBinContent(3, hM3->GetMean());
  hmMc->SetBinError(1, hM1->GetMeanError());
  hmMc->SetBinError(2, hM2->GetMeanError());
  hmMc->SetBinError(3, hM3->GetMeanError());
  handsomeTH1(hmData,2);
  handsomeTH1(hmMc,1);
  hmMc->SetMarkerStyle(24);
  hmMc->Draw();
  hmData->Draw("same");
  

}

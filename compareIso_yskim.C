#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include "commonUtility.h"
//last forward run is 211256


//const Double_t hfBins[] = {0, 20, 30, 1000}; //last entry is upper bound on last bin
//const Int_t nhfBins = 3;

//int returnHFBin(double hf);
void compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut theCut="");
void compareIso_yskim()
{
  TH1::SetDefaultSumw2();

  TFile *inf1 = new TFile("/home/jazzitup/forestFiles/yskimmedFiles/everythingBeforeOct19th/yskim_pA_photonSkimForest_v85.root");
  TTree* t1 = (TTree*)inf1->Get("tgj");
  TFile *inf2 = new TFile("/home/goyeonju/CMS/Files/gammajet/yskimfiles/yskim_pPb_DATA_photon30trig_localJEC_v1_subjet.root");
  TTree* t2 = (TTree*)inf2->Get("tgj");
  
  compareTwo(t1, t2, "run",100, 210400, 212000, "abs(photonEta)<1.44 && photonEt>40");
  compareTwo(t1, t2, "hf4Sum", 20, 0, 150, "abs(photonEta)<1.44 && photonEt>40");
  compareTwo(t1, t2, "hovere", 20, 0, 0.2, "abs(photonEta)<1.44 && photonEt>40");
  compareTwo(t1, t2, "ecalIso", 20,-5,20, "abs(photonEta)<1.44 && photonEt>40");
  compareTwo(t1, t2, "hcalIso", 20,-5,20, "abs(photonEta)<1.44 && photonEt>40");
  compareTwo(t1, t2, "trackIso", 20, -5, 20, "abs(photonEta)<1.44 && photonEt>40");
  compareTwo(t1, t2, "sigmaIetaIeta", 20, 0, 0.025, "abs(photonEta)<1.44 && photonEt>40 && ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2");
  compareTwo(t1, t2, "photonEt", 20, 0, 200,  "abs(photonEta)<1.44 && photonEt>40 && ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2");
  

  
}

void compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut theCut)  {
  TCanvas* c=  new TCanvas(Form("c_%s",var.Data()),"", 400,800);
  c->Divide(1,2);
  c->cd(1);
  TH1D* h1 = new TH1D(Form("h1_%s",var.Data()), Form(";%s;",var.Data()), nBins,xMin,xMax);
  TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s",var.Data()));
  h1->Sumw2();
  h2->Sumw2();
  t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), theCut);
  t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), theCut);
  //  h1->Scale( 1. / h1->Integral());
  //  h2->Scale( 1. / h2->Integral());
  h2->DrawCopy();
  h1->DrawCopy("hist same");
  c->cd(2);
  h2->SetAxisRange(0,3,"Y");
  h2->Divide(h1);
  h2->SetYTitle("New/Old Ratio");
  h2->DrawCopy();
  jumSun(xMin,1,xMax,1);
}

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

//  TFile *inf1 = new TFile("/home/jazzitup/forestFiles/yskimmedFiles/everythingBeforeOct19th/yskim_pA_photonSkimForest_v85.root");
  TFile *inf1 = new TFile("/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco.root");
  TTree* t1 = (TTree*)inf1->Get("tgj");
//  TFile *inf2 = new TFile("/home/goyeonju/CMS/Files/gammajet/yskimfiles/yskim_pPb_DATA_photon30trig_localJEC_v1_subjet.root");
//  TFile *inf2 = new TFile("/export/d00/scratch/tatar/output/yskimmed/yskim_pA_DATA_photonForest_kaya.root");
    TFile *inf2 = new TFile("/export/d00/scratch/tatar/output/yskimmed/yskim_pA_DATA_photonForest_kaya_noDuplicate.root");
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
  //////// Kaya's modificiation ////////
  TH1D* h2_clone=(TH1D*)h2->Clone(h2->GetName());
  h2->SetMarkerStyle(8);
  //////// Kaya's modificiation - END ////////
  h2->DrawCopy();
  h1->DrawCopy("hist same");
  c->cd(2);
  h2->SetAxisRange(0,3,"Y");
  h2->Divide(h1);
  h2->SetYTitle("New/Old Ratio");
  h2->DrawCopy();
  jumSun(xMin,1,xMax,1);

  //////// Kaya's modificiation ////////
  save(h1, h2_clone, c, var);
  //////// Kaya's modificiation - END ////////
}

//////// Kaya's modificiation ////////
void save(TH1D* h1, TH1D* h2, TCanvas* c, TString var)
{
	const char* outDir = "~/output/out_gammaJetAnalysis";
	TFile* out_compareIso_yskim=new TFile(Form("%s/compareIso_yskim_out.root", outDir), "UPDATE");
	out_compareIso_yskim->cd();
	h1->Write();
	h2->Write();
	out_compareIso_yskim->Close();

	c->SaveAs(Form("%s/%s.%s" ,outDir , var.Data(), "pdf"));
}
//////// Kaya's modificiation - END ////////

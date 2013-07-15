// plot photon energy scale/correction and response
// Author: Alex Barbieri
// Date: 2013-07-08

#include <TFile.h>
#include <TH1.h>
#include <TCut.h>
#include <TString.h>
#include <TNtuple.h>
#include <TF1.h>
#include <TCanvas.h>
//#include "../HiForest_V3/hiForest.h"

void FillMeanSigma(Int_t ip, TH1 *h1F, TH1 *hArM, TH1 *hRMS, TH1 *hMean, TH1 *hSigma);

const TString fopt="RQ+";
const Int_t iFit=0;
const Int_t knpx=2000;
const Float_t fitmin=0.00;
const Float_t fitmax=5.00;
const Int_t maxEntry = 5; //if fewer than this number of entries, ignore histogram

const Double_t ptbins[] = {30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,340, 400, 500};
//const Double_t ptbins[] = {30,80,120,180,210,240,270,300,500};
const Int_t nptbins  = sizeof(ptbins)/sizeof(Double_t) - 1;

void photon_JES_JER(bool savePlots)
{
  TH1::SetDefaultSumw2();
  
  TFile *inFile = TFile::Open("gammaJets_inclusive_dphi7pi8_allQCDPhoton280_v3.root");
  TNtuple *inTuple = (TNtuple*)inFile->Get("gammaJets");

  //TCut cut = "(cc4 + cr4 + ct4PtCut20 < 1.0) && (jPt > 30) && (gPt > 50) && (gEta > 1.479) && (sigmaIetaIeta < 0.035)";
  TCut analysisCut = "genMomId==22";

  TH1F *hMean = new TH1F("hMean",";#gamma genPt;mean <reco p_{T}/gen p_{T}>",nptbins,ptbins);
  TH1F *hArM = new TH1F("hArM",";#gamma genPt;hArM <reco p_{T}/gen p_{T}>",nptbins,ptbins);
  TH1F *hSigma = new TH1F("hSigma",";#gamma genPt;#sigma(reco p_{T}/gen p_{T})",nptbins,ptbins);  
  TH1F *hRMS = new TH1F("hRMS",";#gamma genPt;RMS(reco p_{T}/gen p_{T})",nptbins,ptbins);

  TCanvas *d[nptbins];
  for(Int_t i = 0; i < nptbins; ++i)
  {
    TCut ptCut = Form("matchedGPT > %lf && matchedGPT < %lf",ptbins[i],ptbins[i+1]);
    TString hName = Form("reco_over_gen_pt_%d",(Int_t)ptbins[i]);
    TH1F *ratio = new TH1F(hName,Form(";reco/gen pt %d",(Int_t)ptbins[i]),200,fitmin,fitmax);
    inTuple->Project(hName,"gPt/matchedGPT",analysisCut&&ptCut);

    FillMeanSigma(i, ratio, hArM, hRMS, hMean, hSigma);

    d[i] = new TCanvas();
    ratio->DrawClone();
    if(savePlots)
      d[i]->SaveAs(hName+".gif");
  }

  TCanvas *c[4];
  c[0] = new TCanvas();
  hMean->Draw();
  c[1] = new TCanvas();
  hArM->Draw();
  c[2] = new TCanvas();
  hSigma->Draw();
  c[3] = new TCanvas();
  hRMS->Draw();

  if(savePlots)
  {
    c[0]->SaveAs("hMean.gif");
    c[1]->SaveAs("hArM.gif");
    c[2]->SaveAs("hSigma.gif");
    c[3]->SaveAs("hRMS.gif");
  }
}


void FillMeanSigma(Int_t ip,TH1 *h1F,TH1 *hArM,TH1 *hRMS,TH1 *hMean,TH1 *hSigma)
{
  TF1 *f1 = new TF1("f1","(([0]/(2*pi*[1]*[1]))*exp(-1.*((x-[2])*(x-[2])/(2*[1]*[1]))))",0,5);
  f1->SetParameters(1,0.1,1);
  f1->SetParNames("A","#sigma","mean");
  f1->SetParLimits(0,0,20);     //! A
  f1->SetParLimits(1,0.,10.0);  //! Sigma
  f1->SetParLimits(2,fitmin,fitmax); //! Mean
  f1->SetLineWidth(1);
  f1->SetNpx(knpx);
  
  Float_t mm=0,ss=0,p0=0;  
  if(h1F->GetEntries()<maxEntry){
    h1F->Scale(0.);
    hArM  ->SetBinContent(ip+1,-9999);
    hArM  ->SetBinError  (ip+1,0);
    hRMS  ->SetBinContent(ip+1,-9999);
    hRMS  ->SetBinError  (ip+1,0);
  }
  if(h1F->Integral()>0){

    h1F->Scale(1./h1F->Integral());
    if(iFit==0){
      h1F->Fit("gaus",fopt,"",fitmin,fitmax);
      TF1* f2 = (TF1*)h1F->GetFunction("gaus");
      f2->SetLineWidth(1);
      f2->SetLineStyle(2);
      f2->SetNpx(knpx);
      hMean ->SetBinContent(ip+1,f2->GetParameter(1));
      hSigma->SetBinContent(ip+1,f2->GetParameter(2));
      
      if(strcmp(fopt,"MLRQ+")==0){
	hMean ->SetBinError  (ip+1,h1F->GetMeanError());
	hSigma->SetBinError  (ip+1,h1F->GetRMSError());
      }else{
	hMean ->SetBinError(ip+1,f2->GetParError(1));
	hSigma->SetBinError(ip+1,f2->GetParError(2));
      }
    }else{
      mm = h1F->GetMean();
      ss = h1F->GetRMS();
      p0 = h1F->GetMaximum();
      f1->SetParameters(p0,ss,mm);
      f1->SetParLimits(0,0,2*p0);
      f1->SetParLimits(1,0,2*ss);
      f1->SetParLimits(2,fitmin,fitmax);
      //f1->SetParLimits(2,mm-2.5*ss,mm+2.5*ss);
      
      h1F->Fit("f1",fopt,"",fitmin,fitmax);
      hMean ->SetBinContent(ip+1,f1->GetParameter(2));
      hSigma->SetBinContent(ip+1,f1->GetParameter(1));
      
      if(strcmp(fopt,"MLRQ+")==0){
	hMean ->SetBinError  (ip+1,h1F->GetMeanError());
	hSigma->SetBinError  (ip+1,h1F->GetRMSError());
      }else{
	hMean ->SetBinError  (ip+1,f1->GetParError(2));
	hSigma->SetBinError  (ip+1,f1->GetParError(1));
      }
    }
    hArM  ->SetBinContent(ip+1,h1F->GetMean());
    hArM  ->SetBinError  (ip+1,h1F->GetMeanError());
    hRMS  ->SetBinContent(ip+1,h1F->GetRMS());
    hRMS  ->SetBinError  (ip+1,h1F->GetRMSError());
  }
}

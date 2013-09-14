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
#include "commonUtility.h"
#include "fitResult.h"
#include "uniqueEvents.C"

void bkgCorrectionStudy()
{
  const TString inFile = "gammaJets_pp_Pythia_emDijet50.root";
  TH1::SetDefaultSumw2();

  TFile *mcFile = TFile::Open(inFile);
  TNtuple *mcTuple = (TNtuple*)mcFile->Get("gammaJets");
  use_only_unique_events(mcTuple,"mcid");

  const Double_t sumIsoBins[] = {0, 5, 10, 15, 20, 25, 30};
  const Int_t nsumIsoBins = sizeof(sumIsoBins)/sizeof(Double_t) -1;

  const Int_t nSIGMABINS = 25; // number of bins in sigmaIetaIeta dist
  const Double_t maxSIGMA = 0.025; // x-axis max of sigmaIetaIeta dist

  const TCut pt = "gPt > 50";
  const TCut eta = "abs(gEta) < 1.479";
  const TCut hoe = "hadronicOverEm<0.1";
  const TCut iso = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2";

  TH1D* hSig = new TH1D("sig","",nSIGMABINS,0,maxSIGMA);
  mcTuple->Project("sig","sigmaIetaIeta",pt && eta && iso && hoe);
  hSig->Scale(1./hSig->GetEntries());
  hSig->SetYTitle("counts");

  TCanvas *c1 = new TCanvas("c1", "c1", nsumIsoBins*400, 600);
  c1->Divide(nsumIsoBins,2,0,0);
  for(int i = 0; i < nsumIsoBins; ++i)
  {
    TString sumIsoCut = Form("(cc4+cr4+ct4PtCut20 > %lf) && (cc4+cr4+ct4PtCut20 < %lf)",
			     sumIsoBins[i],sumIsoBins[i+1]);
    
    TH1D* hBkg = (TH1D*)hSig->Clone(Form("bkg%i",i));
    mcTuple->Project(Form("bkg%i",i),"sigmaIetaIeta",pt && eta && hoe && sumIsoCut);
    hBkg->Scale(1./hBkg->GetEntries());
    
    //c1[i] = new TCanvas(Form("canv%i",i),"",400,600);
    //c1[i]->Divide(1,2,0,0);
    c1->cd(i+1);
    hSig->DrawClone();
    hBkg->SetMarkerColor(kRed);
    hBkg->SetLineColor(kRed);
    hBkg->DrawClone("same");
    drawText("p_{T}^{#gamma} > 50 GeV",0.57,0.9);
    drawText(Form("%.0lf < sumIso < %.0lf",sumIsoBins[i],sumIsoBins[i+1]), 0.57, 0.82);

    TH1D* hRatio = (TH1D*)hSig->Clone("ratio");
    hRatio->Divide(hSig, hBkg, 1, 1);
    hRatio->SetMinimum(0);
    hRatio->SetMaximum(2);
    c1->cd(i+nsumIsoBins+1);
    hRatio->SetYTitle("ratio");
    hRatio->SetXTitle("#sigma_{#eta #eta}");
    hRatio->DrawClone();
    TF1 *fitfunc = new TF1(Form("fitfunc%i",i),"[1]*x+[0]",0,maxSIGMA);
    hRatio->Fit(Form("fitfunc%i",i),"M Q",0,maxSIGMA);
    TLine *line = new TLine(0,1,maxSIGMA,1);
    line->SetLineStyle(2);
    line->Draw("same");
  }

  c1->SaveAs("fit_vs_sumIso.png");


}

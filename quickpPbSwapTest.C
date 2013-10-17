#include "alexGammaSkim.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1D.h"
#include "stdio.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"

const TString iso = "Sideband";

void quickpPbSwapTest()
{
  TH1::SetDefaultSumw2();
  
  TFile *inFile = TFile::Open("gammaJets_pA_Data.root");
  readGammaSkim(inFile);

  TH1D *xjg[2];
  xjg[0] = new TH1D("xjg_early", ";x_{J #gamma};Relative Probability", 50,0, 5);
  xjg[1] = (TH1D*)xjg[0]->Clone("xjg_late");

  TH1D *sigmaIetaIeta[2];
  sigmaIetaIeta[0] = new TH1D("sieie_early",";" + iso + " #sigma_{#eta #eta};Relative Probability", 25, 0, 0.025);
  sigmaIetaIeta[1] = (TH1D*)sigmaIetaIeta[0]->Clone("sieie_late");

  TH1D *eta[2];
  eta[0] = new TH1D("eta_early",";" + iso + "  #eta;Relative Probability", 20, -1.44, 1.44);
  eta[1] = (TH1D*)eta[0]->Clone("eta_late");

  Long64_t nentries = photonTree_->GetEntries();
  for(Long64_t jentry = 0; jentry < nentries; ++jentry)
  {
    photonTree_->GetEntry(jentry);
    bool selectPhotons = gPt_ > 40 && hadronicOverEm_ < 0.1;
    // selectPhotons = selectPhotons && (ecalRecHitSumEtConeDR04_ < 4.2) &&
    //   (hcalTowerSumEtConeDR04_ < 2.2) &&
    //   (trkSumPtHollowConeDR04_ < 2.0);

    selectPhotons = ((cc4_+cr4_+ct4PtCut20_) > 10.0) &&
      ((cc4_+cr4_+ct4PtCut20_) < 20.0);
    
    if( !selectPhotons) continue;

    if(run_ < 211256)
    {
      sigmaIetaIeta[0]->Fill(sigmaIetaIeta_);
      eta[0]->Fill(gEta_);
    } else {
      sigmaIetaIeta[1]->Fill(sigmaIetaIeta_);
      eta[1]->Fill(gEta_);
    }


    jetTree_->GetEntry(jentry);
    for(int i = 0; i< nJets_; i++)
    {
      if(jPt_[i] < 30 || dPhi_[i] < 7.*TMath::Pi()/8.) continue;

      if(run_ < 211256)
	xjg[0]->Fill(jPt_[i]/gPt_);
      else
	xjg[1]->Fill(jPt_[i]/gPt_);
    }
  }

  TCanvas *c1 = new TCanvas("c1","c1",400,600);
  c1->Divide(1,2,0,0);
  c1->cd(1);
  xjg[0]->Scale(1./xjg[0]->GetEntries());
  xjg[1]->Scale(1./xjg[1]->GetEntries());
  xjg[1]->SetMarkerColor(kBlue);

  xjg[0]->Draw("p E");
  xjg[1]->Draw("p E same");

  TLegend *leg = new TLegend(0.6, 0.5, 0.9, 0.85);
  leg->SetFillColor(0);
  leg->AddEntry(xjg[0], "(pPb) run < 211256", "p");
  leg->AddEntry(xjg[1], "(Pbp) run > 211256", "p");
  leg->Draw();

  c1->cd(2);
  TH1D *xjg_ratio = (TH1D*)xjg[0]->Clone("xjg_ratio");
  xjg_ratio->Divide(xjg[0],xjg[1],1,1);
  xjg_ratio->SetMinimum(0);
  xjg_ratio->SetMaximum(2.5);
  xjg_ratio->SetYTitle("pPb/Pbp");
  xjg_ratio->Draw("e");
  TLine *xjg_line = new TLine(0, 1, 5,1);
  xjg_line->Draw();

  c1->SaveAs("pPb_flip_xjg"+iso+".pdf");
  c1->SaveAs("pPb_flip_xjg"+iso+".png");

  TCanvas *c2 = new TCanvas("c2","c2",400,600);
  c2->Divide(1,2,0,0);
  c2->cd(1);
  sigmaIetaIeta[0]->Scale(1./sigmaIetaIeta[0]->GetEntries());
  sigmaIetaIeta[1]->Scale(1./sigmaIetaIeta[1]->GetEntries());
  sigmaIetaIeta[1]->SetMarkerColor(kBlue);

  sigmaIetaIeta[0]->Draw("p E ");
  sigmaIetaIeta[1]->Draw("p E same");
  leg->Draw();

  c2->cd(2);
  TH1D *sigmaIetaIeta_ratio = (TH1D*)sigmaIetaIeta[0]->Clone("sigmaIetaIeta_ratio");
  sigmaIetaIeta_ratio->Divide(sigmaIetaIeta[0], sigmaIetaIeta[1],1,1);
  sigmaIetaIeta_ratio->SetMinimum(0);
  sigmaIetaIeta_ratio->SetMaximum(2.5);
  sigmaIetaIeta_ratio->SetYTitle("pPb/Pbp");
  sigmaIetaIeta_ratio->Draw("e");
  TLine *sigmaIetaIeta_line = new TLine(0, 1, 0.025,1);
  sigmaIetaIeta_line->Draw();

  c2->SaveAs("pPb_flip_sigmaIetaIeat"+iso+".pdf");
  c2->SaveAs("pPb_flip_sigmaIetaIeat"+iso+".png");

  
  TCanvas *c3 = new TCanvas("c3","c3",400,600);
  c3->Divide(1,2,0,0);
  c3->cd(1);
  eta[0]->Scale(1./eta[0]->GetEntries());
  eta[1]->Scale(1./eta[1]->GetEntries());
  eta[1]->SetMarkerColor(kBlue);

  eta[0]->SetMinimum(0);
  eta[0]->Draw("p E ");
  eta[1]->Draw("p E same");
  leg->Draw();

  c3->cd(2);
  TH1D *eta_ratio = (TH1D*)eta[0]->Clone("eta_ratio");
  eta_ratio->Divide(eta[0], eta[1],1,1);
  eta_ratio->SetMinimum(0);
  eta_ratio->SetMaximum(2.0);
  eta_ratio->SetYTitle("pPb/Pbp");
  eta_ratio->Draw("e");
  TLine *eta_line = new TLine(-1.44, 1, 1.44,1);
  eta_line->Draw();

  c3->SaveAs("pPb_flip_eta"+iso+".pdf");
  c3->SaveAs("pPb_flip_eta"+iso+".png");


}

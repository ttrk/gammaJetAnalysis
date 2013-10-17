#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TLegend.h"

void quickBkgSigma()
{
  TFile *dataFile = TFile::Open("gammaJets_pp_MC_EmEnrichedDijet.root");
  TTree *dataTree = (TTree*)dataFile->Get("photonTree");

  TH1D *signalRegion = new TH1D("signalRegion",";#sigma_{#eta #eta};Relative Probability",25, 0, 0.025);
  signalRegion->GetYaxis()->CenterTitle();
  signalRegion->GetXaxis()->CenterTitle();
  TH1D *bkgRegion = (TH1D*)signalRegion->Clone("bkgRegion");

  dataTree->Project("signalRegion","sigmaIetaIeta","corrPt>40 && abs(eta)<1.44 && hadronicOverEm < 0.1 && ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2");
  dataTree->Project("bkgRegion","sigmaIetaIeta","corrPt>40 && abs(eta)<1.44 && hadronicOverEm < 0.1 && cc4+cr4+ct4PtCut20>10 && cc4+cr4+ct4PtCut20<20");

  signalRegion->Scale(1./signalRegion->GetEntries());
  bkgRegion->Scale(1./bkgRegion->GetEntries());

  signalRegion->SetFillColor(kGreen);
  signalRegion->SetFillStyle(3009);
  signalRegion->Draw("hist");
  bkgRegion->SetMarkerColor(kRed);
  bkgRegion->SetLineColor(kRed);
  bkgRegion->SetFillColor(kRed);
  bkgRegion->SetFillStyle(3001);
  bkgRegion->Draw("same hist");

  TLegend *leg = new TLegend(0.6, 0.5, 0.9, 0.8,"pp Em-Enriched Pythia");
  leg->SetFillColor(0);
  leg->AddEntry(signalRegion,"Isolated Background", "lf");
  leg->AddEntry(bkgRegion,"non-Isolated Background","lf");
  leg->Draw();

}

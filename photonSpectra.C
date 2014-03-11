// Author Alex Barbieri
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "stdio.h"
#include "fitResult.h"

void photonSpectra()
{
  TH1::SetDefaultSumw2();

  const Double_t PTBINS[] = {40, 50, 60, 80, 120, 300};
  const Int_t nPTBINS = 5;

  const TString DATA_FILE = "gammaJets_pA_Data.root";
  const TString MC_FILE = "gammaJets_pA_MC_allQCDPhoton.root";
  TFile *dataFile = TFile::Open(DATA_FILE);
  TTree *dataTree = (TTree*)dataFile->Get("photonTree");
  TFile *mcFile = TFile::Open(MC_FILE);
  TTree *mcTree = (TTree*)mcFile->Get("photonTree");

  TH1D *photonSpectra = new TH1D("photonSpectra","photonSpectra", nPTBINS, PTBINS);
  TH1D *correctedPhotonSpectra = (TH1D*)photonSpectra->Clone("correctedPhotonSpectra");

  const TCut photonEtaCut = "abs(photonTree.eta) < 1.44";
  const TCut isoCut = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
  const TCut genCut = "genCalIsoDR04<5 && abs(genMomId)<=22";
  const TCut sbCut = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
  const TCut candidateCut = "sigmaIetaIeta<0.01";
  const TCut decayCut = "(sigmaIetaIeta>0.011) && (sigmaIetaIeta<0.017)";

  TCut photonPtCut = "photonTree.corrPt>40 && photonTree.corrPt<300";

  dataTree->Project(photonSpectra->GetName(),"corrPt",isoCut && photonEtaCut && photonPtCut && candidateCut);

  for(int i = 0; i<nPTBINS; ++i)
  {
    photonPtCut = Form("photonTree.corrPt>%f && photonTree.corrPt<%f", PTBINS[i], PTBINS[i+1]  );

    TCut dataCandidateCut = isoCut && photonEtaCut && photonPtCut;
    TCut sidebandCut =  sbCut && photonEtaCut && photonPtCut;
    TCut mcSignalCut = dataCandidateCut && genCut;

    fitResult fitr = getPurity(dataTree, mcTree,
  			       dataCandidateCut, sidebandCut,
  			       mcSignalCut);
    Double_t purity = fitr.purity;
    correctedPhotonSpectra->SetBinContent(i+1,photonSpectra->GetBinContent(i+1)*purity);
  }

  // TCanvas *c1 = new TCanvas();
  // photonSpectra->Draw();
  // correctedPhotonSpectra->Draw("same");

  TFile *outFile = new TFile("photonSpectra.root", "RECREATE");
  outFile->cd();
  photonSpectra->Write();
  correctedPhotonSpectra->Write();
  outFile->Close();
}

int main()
{
  photonSpectra();
  return 0;
}

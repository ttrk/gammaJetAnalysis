#include "alexGammaSkim.h"
#include "TFile.h"
#include "TMath.h"
#include "TH1D.h"
#include "stdio.h"

void quickJetEta()
{  
  TFile *inFile = TFile::Open("gammaJets_pA_Data.root");
  readGammaSkim(inFile);

  TH1D *hDphi = new TH1D("","",50, 0, TMath::Pi());

  Long64_t nentries = photonTree_->GetEntries();
  for(Long64_t jentry = 0; jentry < nentries; ++jentry)
  {
    photonTree_->GetEntry(jentry);
    bool selectPhotons = (gPt_ > 40 && hadronicOverEm_ < 0.1 &&
			  ecalRecHitSumEtConeDR04_ < 4.2 &&  hcalTowerSumEtConeDR04_ < 2.2 &&
			  trkSumPtHollowConeDR04_ < 2.0);
    if( !selectPhotons) continue;

    jetTree_->GetEntry(jentry);


    //if( !(nJets_ > 1) ) continue;

    //if(jPt_[0]<30 || jPt_[1]<30) continue;

    Double_t dPhi = TMath::ACos(TMath::Cos(jPhi_[0] - jPhi_[1]));
    hDphi->Fill(dPhi);

    //printf("evt: %d\n",event_);
  }

  hDphi->Draw();
}
				

// Author: Alex Barbieri
#ifndef alexGammaSkim_h
#define alexGammaSkim_h

#include "TTree.h"

enum sampleType {
  kHIDATA, //0
  kHIMC,   //1
  kPPDATA, //2
  kPPMC,   //3
  kPADATA, //4 
  kPAMC    //5
};

TString getSampleName ( sampleType colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}
TString getSampleName ( int colli) {
  if (colli == kHIDATA) return "pbpbDATA";
  if (colli == kHIMC) return "pbpbMC";
  if (colli == kPPDATA) return "ppDATA";
  if (colli == kPPMC) return "ppMC";
  if (colli == kPADATA) return "ppbDATA";
  if (colli == kPAMC) return "ppbMC";
  return "NULL";
}

TTree *photonTree_;
TTree *jetTree_;
TTree *mJetTree_;

// photon tree
Int_t run_;
Int_t event_;
Int_t lumi_;
Float_t gPt_;
Float_t corrGPt_;
Float_t gEta_;
Float_t gPhi_;
Float_t HF_;
Float_t HFplusEta4_;
Float_t HFminusEta4_;
Float_t cc4_;
Float_t cr4_;
Float_t ct4PtCut20_;
Float_t hadronicOverEm_;
Float_t sigmaIetaIeta_;
Float_t r9_;
Float_t ecalRecHitSumEtConeDR04_;
Float_t hcalTowerSumEtConeDR04_;
Float_t trkSumPtHollowConeDR04_;
Int_t hiBin_;


//jet tree
Int_t nJets_;
const int MAXJETS = 504; //got from SetupJetTree.h
Float_t jPt_[MAXJETS];
Float_t jEta_[MAXJETS];
Float_t jPhi_[MAXJETS];
Float_t avgEta_[MAXJETS];
Float_t dPhi_[MAXJETS];
Float_t dR_[MAXJETS];

// MC elements
Int_t genMomId_;
Float_t genCalIsoDR04_;
Float_t genTrkIsoDR04_;
Float_t ptHat_;
Float_t genGPt_;
Float_t genGEta_;
Float_t genGPhi_;
Float_t mcweight_;

Float_t genJPt_[MAXJETS];

// minbias mix elements
int nMjet_;
float mJetPt_[MAXJETS];
float mJetEta_[MAXJETS];
float mJetPhi_[MAXJETS];
float mJetDphi_[MAXJETS];

void initGammaSkim(bool montecarlo)
{
  photonTree_ = new TTree("photonTree","photonTree");
  jetTree_ = new TTree("jetTree","jetTree");
  mJetTree_ = new TTree("mJetTree","mJetTree");

  photonTree_->Branch("run",&run_,"run/I");
  photonTree_->Branch("event",&event_,"event/I");
  photonTree_->Branch("lumi",&lumi_,"lumi/I");
  photonTree_->Branch("pt",&gPt_,"pt/F");
  photonTree_->Branch("corrPt",&corrGPt_,"corrPt/F");
  photonTree_->Branch("eta",&gEta_,"eta/F");
  photonTree_->Branch("phi",&gPhi_,"phi/F");
  photonTree_->Branch("HF",&HF_,"HF/F");
  photonTree_->Branch("HFplusEta4",&HFplusEta4_,"HFplusEta4/F");
  photonTree_->Branch("HFminusEta4",&HFminusEta4_,"HFminusEta4/F");
  photonTree_->Branch("cc4",&cc4_,"cc4/F");
  photonTree_->Branch("cr4",&cr4_,"cr4/F");
  photonTree_->Branch("ct4PtCut20",&ct4PtCut20_,"ct4PtCut20/F");
  photonTree_->Branch("hadronicOverEm",&hadronicOverEm_,"hadronicOverEm/F");
  photonTree_->Branch("sigmaIetaIeta",&sigmaIetaIeta_,"sigmaIetaIeta/F");
  photonTree_->Branch("r9",&r9_,"r9/F");
  photonTree_->Branch("ecalRecHitSumEtConeDR04",&ecalRecHitSumEtConeDR04_,"ecalRecHitSumEtConeDR04/F");
  photonTree_->Branch("hcalTowerSumEtConeDR04",&hcalTowerSumEtConeDR04_,"hcalTowerSumEtConeDR04/F");
  photonTree_->Branch("trkSumPtHollowConeDR04",&trkSumPtHollowConeDR04_,"trkSumPtHollowConeDR04/F");
  photonTree_->Branch("hiBin",&hiBin_,"hiBin/I");

  jetTree_->Branch("nJets",&nJets_,"nJets/I");
  jetTree_->Branch("pt",jPt_,"jPt[nJets]/F");
  jetTree_->Branch("eta",jEta_,"eta[nJets]/F");
  jetTree_->Branch("phi",jPhi_,"phi[nJets]/F");
  jetTree_->Branch("avgEta",avgEta_,"avgEta[nJets]/F");
  jetTree_->Branch("dPhi",dPhi_,"dPhi[nJets]/F");
  jetTree_->Branch("dR",dR_,"dR[nJets]/F");

  if(montecarlo)
  {
    photonTree_->Branch("genMomId",&genMomId_,"genMomId/I");
    photonTree_->Branch("genCalIsoDR04",&genCalIsoDR04_,"genCalIsoDR04/F");
    photonTree_->Branch("genTrkIsoDR04",&genTrkIsoDR04_,"genTrkIsoDR04/F");
    photonTree_->Branch("ptHat",&ptHat_,"ptHat/F");
    photonTree_->Branch("genPt",&genGPt_,"genPt/F");
    photonTree_->Branch("genEta",&genGEta_,"genEta/F");
    photonTree_->Branch("genPhi",&genGPhi_,"genPhi/F");
    photonTree_->Branch("mcweight",&mcweight_,"mcweight/F");

    jetTree_->Branch("genPt",genJPt_,"genJPt[nJets]/F");
  }

  mJetTree_->Branch("nJet",&nMjet_,"nJet/I");
  mJetTree_->Branch("pt",mJetPt_,"pt[nJet]/F");
  mJetTree_->Branch("eta",mJetEta_,"eta[nJet]/F");
  mJetTree_->Branch("phi",mJetPhi_,"phi[nJet]/F");
  mJetTree_->Branch("dPhi", mJetDphi_, "dphi[nJet]/F");
}

#endif

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
#include "TRandom3.h"
#include "../HiForestAnalysis/hiForest.h"
#include "alexGammaSkim.h"

const Double_t gammaEtaCut = 1.44;
const Double_t jetEtaCut = 1.6;

// stuff related to MB mixing
const int nCentBinSkim = 40;
const int nVtxBin = 1;
const TString MinbiasFname = "photonSkimProducer/minbiasSkim_HIMinBias_merged_1_1000.root";
const int vzCut = 15;
const int nMixing1 = 20;

collisionType getCType(sampleType sType);

int makeGammaJetNTuple(const char *inFile, sampleType sType, const char *outName, Float_t mcweight=1)
{
  bool montecarlo = false;
  if(sType == kPPMC || sType == kPAMC || sType == kHIMC)
    montecarlo = true;

  collisionType cType = getCType(sType);

  TFile *outfile = new TFile(outName,"RECREATE");

  // prepares photonTree, jetTree, and mJetTree
  initGammaSkim(montecarlo); //see alexGammaSkim.h
  
  HiForest *c = new HiForest(inFile, "Forest", cType, montecarlo);
  c->InitTree(); //could be redundant, but doesn't hurt
  
  c->LoadNoTrees(); // turns off trees I'm not using: loops faster
  c->hasPhotonTree = true;
  c->hasSkimTree = true; // required for selectEvent()
  c->hasEvtTree = true;

  Jets jetCollection;
  if(sType == kHIDATA || sType == kHIMC || sType == kPADATA || sType == kPAMC)
  {
    c->hasAkPu3JetTree = true;
    jetCollection = c->akPu3PF;
  }
  else
  {
    c->hasAk3JetTree = true;
    jetCollection = c->ak3PF;
  }

  // mix with minbias jets for PbPb only.
  // wholesale imported from Yongsun's code
  //////////////////////////////////////
  int seconds = time(NULL);
  TRandom3 rand(seconds%10000);
  TH1F* hvz = new TH1F("hvz","",nVtxBin,-vzCut,vzCut);
  // Imb = Input MinBias events 
  //EvtSel          evtImb;
  Int_t           nJetImb;
  Float_t         jetPtImb[100];
  Float_t         jetEtaImb[100];
  Float_t         jetPhiImb[100];
  //TBranch        *b_evt;
  TBranch        *b_nJetImb;
  TBranch        *b_jetPtImb;
  TBranch        *b_jetEtaImb;
  TBranch        *b_jetPhiImb; 
 
  int nCentBins =  nCentBinSkim;
  TChain *tjmb[100][nVtxBin+1];
  int nMB[100][nVtxBin+1] ; 
  int mbItr[100][nVtxBin+1];
  if ( sType==kHIDATA ) {
    //cout <<"  Tree initialization for MinBias mixing" << endl;
    for( int icent = 0 ; icent< nCentBins ; icent++) {
      for( int ivz = 1 ; ivz<=nVtxBin ; ivz++) {	
	tjmb[icent][ivz] = new TChain(Form("trkAndJets_first_cBin2icent%d_ivz%d",icent,ivz));
	tjmb[icent][ivz]->Add(MinbiasFname.Data());
	//tjmb[icent][ivz]->SetBranchAddress("evt", &evtImb,&b_evt);
	tjmb[icent][ivz]->SetBranchAddress("nJet",   &nJetImb,   &b_nJetImb);
	tjmb[icent][ivz]->SetBranchAddress("jetPt",  &jetPtImb,  &b_jetPtImb);
	tjmb[icent][ivz]->SetBranchAddress("jetEta", &jetEtaImb, &b_jetEtaImb);
	tjmb[icent][ivz]->SetBranchAddress("jetPhi", &jetPhiImb, &b_jetPhiImb);	
	
	nMB[icent][ivz] = tjmb[icent][ivz]->GetEntries();
	//cout << "number of evetns in (icent = " << icent << ", ivtxZ = "<< ivz << ")  = " << nMB[icent][ivz] << endl;
	int primeSeed = rand.Integer(37324);
	mbItr[icent][ivz] = primeSeed%(nMB[icent][ivz]);
	//cout <<" initial itr = " << mbItr[icent][ivz] << endl;
      }
    }
  }
  ///////////////////////////////////////////////
  
  //loop over events in each file
  Long64_t nentries = c->GetEntries();
  for(Long64_t jentry = 0; jentry<nentries; ++jentry)
  {
    if (jentry % 1000 == 0)  {
      printf("%lld / %lld\n",jentry,nentries);
    }
    
    c->GetEntry(jentry);

    //event selection
    if( !c->selectEvent() )
      continue;

    if(c->photon.nPhotons == 0)
      continue;

    //loop over photons in the event
    //////////////////////////////////////////
    Float_t leadingCorrectedPt = 0;
    Int_t leadingIndex = -1;
    for(Int_t i = 0; i < c->photon.nPhotons; ++i)
    {
      if(
	(TMath::Abs(c->photon.eta[i]) > gammaEtaCut) ||
	(c->isSpike(i)) ||
	(!(c->isLoosePhoton(i)))
	)
	continue;
      
      Float_t correctedPt = c->getCorrEt(i);
      if(correctedPt > leadingCorrectedPt)
      {
	leadingCorrectedPt = correctedPt;
	leadingIndex = i;
      }
    }
      
    if(leadingIndex == -1)
      continue;

    run_ = c->evt.run;
    event_ = c->photon.event;
    lumi_ = c->evt.lumi;
    gPt_ = c->photon.pt[leadingIndex];
    corrGPt_ = leadingCorrectedPt;
    gEta_ = c->photon.eta[leadingIndex];
    gPhi_ = c->photon.phi[leadingIndex];
    HF_ = c->evt.hiHF;
    HFplusEta4_ = c->evt.hiHFplusEta4;
    HFminusEta4_ = c->evt.hiHFminusEta4;
    cc4_ = c->photon.cc4[leadingIndex];
    cr4_ = c->photon.cr4[leadingIndex];
    ct4PtCut20_ = c->photon.ct4PtCut20[leadingIndex];
    hadronicOverEm_ = c->photon.hadronicOverEm[leadingIndex];
    sigmaIetaIeta_ = c->photon.sigmaIetaIeta[leadingIndex];
    r9_ = c->photon.r9[leadingIndex];
    ecalRecHitSumEtConeDR04_ = c->photon.ecalRecHitSumEtConeDR04[leadingIndex];
    hcalTowerSumEtConeDR04_ = c->photon.hcalTowerSumEtConeDR04[leadingIndex];
    trkSumPtHollowConeDR04_ = c->photon.trkSumPtHollowConeDR04[leadingIndex];

    if(montecarlo)
    {
      genMomId_ = c->photon.genMomId[leadingIndex];
      genCalIsoDR04_ = c->photon.genCalIsoDR04[leadingIndex];
      genTrkIsoDR04_ = c->photon.genTrkIsoDR04[leadingIndex];
      ptHat_ = c->photon.ptHat;
      genGPt_ = c->photon.genMatchedPt[leadingIndex];
      genGEta_ = c->photon.genMatchedEta[leadingIndex];
      genGPhi_ = c->photon.genMatchedPhi[leadingIndex];
      mcweight_ = mcweight;
    }
    //////////////////////////////

    //loop over 'away' jets
    ///////////////////////////////////////////
    nJets_ = 0;
    for(Int_t i = 0; i<jetCollection.nref; ++i)
    {
      if( TMath::Abs(jetCollection.jteta[i]) > jetEtaCut)
	continue;

      Float_t deltaPhi = TMath::ACos(TMath::Cos(c->photon.phi[leadingIndex]
						- jetCollection.jtphi[i]));
      Float_t deltaEta = TMath::Abs(c->photon.eta[leadingIndex]
				    - jetCollection.jteta[i]);
      Float_t deltaR = TMath::Sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);

      if(deltaR < 0.3) continue; // avoid finding the photon itself
      
      Float_t averageEta = (c->photon.eta[leadingIndex] + jetCollection.jteta[i])/2.0;

      nJets_++;
      if(nJets_ > MAXJETS)
      {
	printf("ERROR: Jet arrays not large enough.\n");
	return(1);
      }
      jPt_[i] = jetCollection.jtpt[i];
      jEta_[i] = jetCollection.jteta[i];
      jPhi_[i] = jetCollection.jtphi[i];
      avgEta_[i] = averageEta;
      dPhi_[i] = deltaPhi;
      dR_[i] = deltaR;

      if(montecarlo)
	genJPt_[i] = jetCollection.refpt[i];
    }
    //////////////////////////////////////////////

    // for kHIDATA, mix with minbias jets
    ///////////////////////////////////////////////
    nMjet_ = 0;
    if(sType == kHIDATA)
    {
      int nMixing = nMixing1;
      nMjet_ = 0;
      bool noSuchEvent = false;
      int iMix=0;
      int loopCounter=0;
      int cBin = c->evt.hiBin;
      int vzBin = hvz->FindBin(c->evt.vz);
    
      // if ( !(sType==kHIDATA) ) 
      //   iMix = nMixing+1;   // Mixing step will be skipped 
    
      while (iMix<nMixing)  {
	loopCounter++;
	if ( loopCounter > nMB[cBin][vzBin]+1) {
	  iMix = 999999 ;
	  noSuchEvent = true;
	  //cout << " no such event!! :  icent = " << cBin << ",  vzBin = " << vzBin << ",  pBin = " << evt.pBin << endl;
	  continue;
	}
      
	mbItr[cBin][vzBin] = mbItr[cBin][vzBin] + 1;
	if ( mbItr[cBin][vzBin] == nMB[cBin][vzBin] )
	  mbItr[cBin][vzBin] =  mbItr[cBin][vzBin] - nMB[cBin][vzBin];
      
	/// Load the minbias tracks!!
	tjmb[cBin][vzBin]->GetEntry(mbItr[cBin][vzBin]);
      
	// Event plane is out of control for both pA and PbPb Sept 2013
	//    if  ( evt.pBin != evtImb.pBin ) 
	//   continue;
      
	// ok found the event!! ///////////
	loopCounter =0;  // Re-initiate loopCounter

	// Jet mixing 
	for (int it = 0 ; it < nJetImb ; it++) {
	  // if ( jetPtImb[it] < cutjetPtSkim ) 
	  //   continue;
	  if ( TMath::Abs( jetEtaImb[it] ) > jetEtaCut ) 
	    continue;
	
	  mJetPt_[nMjet_]    = jetPtImb[it];
	  mJetEta_[nMjet_]   = jetEtaImb[it];
	  mJetPhi_[nMjet_]   = jetPhiImb[it];
	  if  ( mJetPt_[nMjet_]>0 )
	    mJetDphi_[nMjet_]  =  TMath::ACos(TMath::Cos(c->photon.phi[leadingIndex]
							 - jetEtaImb[it]));
	  else
	    mJetDphi_[nMjet_]=-1;
	
	  nMjet_++; // < == Important! 
	}
      
	iMix++;
      }
      if ( noSuchEvent )
      {
	printf("ERROR: No matching event for mixing.");
	continue;
      }
    }
    //////////////////////////////////////////////

    photonTree_->Fill();
    jetTree_->Fill();
    mJetTree_->Fill();
  }
  
  outfile->cd();
  photonTree_->Write();
  jetTree_->Write();
  mJetTree_->Write();
  outfile->Close();

  printf("Done.\n");
  return(0);
}

collisionType getCType(sampleType sType)
{
  switch (sType)
  {
  case kPPDATA:
  case kPPMC:
    return cPP;
  case kPADATA:
  case kPAMC:
    return cPPb;
  case kHIDATA:
  case kHIMC:
    return cPbPb;
  }
  return cPbPb; //probably a bad guess
}
			
int main(int argc, char *argv[])
{
  if(argc != 4 && argc != 5)
  {
    printf("Usage: makeGammaJetNTuple.exe \"inForest\" sampleType \"outname\" mcweight");
    return(1);
  }
  if(argc == 4)
    return(makeGammaJetNTuple(argv[1], (sampleType)atoi(argv[2]), argv[3]));
  else
    return(makeGammaJetNTuple(argv[1], (sampleType)atoi(argv[2]), argv[3], atof(argv[4])));
}

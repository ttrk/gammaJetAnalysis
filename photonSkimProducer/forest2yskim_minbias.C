///////////////////////////////////////////////////////////////////                                
// forest2yskim.C                                                //                                                 
// Creator : Yongsun Kim (MIT), jazzitup@mit.edu                 //                                                 
// Function : Transform hiForest files into yskim file           //
// yskims for MinBias1, Minbias2 and photon jet skims            //
///////////////////////////////////////////////////////////////////         

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <TMath.h>
#include "../HiForest_V2_thesis/hiForest.h"
#include "CutAndBinCollection2012.h"
#include <time.h>
#include <TRandom3.h>

using namespace std;

static const long MAXTREESIZE = 10000000000;





void forest2yskim_minbias(TString inputFile_="mergedFiles/forest_minbias-HYDJET-START44-V12-Aug29th.root",
			  std::string outname = "skim_trackJet_minbiasTrackJet_mc.root",
			  TString jetAlgo="akPu3PF",			  
			  bool isMC=true
			  )
{ 
  
  
  TString datafname  = "skimmed/yskim_for_dataCentrality_yskim_HiForestPhoton-v7-noDuplicate_nMinBisMixedQuarterPI.root"; // used for centrality reweighting

  
  HiForest *c = new HiForest(inputFile_.Data(),"akPu3PF");
  c->doTrackCorrections = true;
  c->triggerMode = kMB;
  c->InitTree();
  
  // output file
  TFile* newfile_data = new TFile(outname.data(),"recreate");
   
  // Track tree
  int nTrk;
  static const int MAXTRK  = 10000;   // This is very enough.                                                                        
  float trkPt[MAXTRK];
  float trkEta[MAXTRK];
  float trkPhi[MAXTRK];
  float trkWeight[MAXTRK];

  int nJet;
  static const int MAXJET  = 100;   // This is very enough.                                                                        
  float jetPt[MAXJET];
  float jetEta[MAXJET];
  float jetPhi[MAXJET];

  
  const int maxGp = 30000;
  int nGp;
  float gpPt[maxGp];
  float gpEta[maxGp];
  float gpPhi[maxGp];
  int   gpChg[maxGp];
  
  EvtSel evt;
  TTree* newtreeTrkJet[100][nVtxBin+1];
  
  for( int icent = 0 ; icent< nCentBinSkim ; icent++) { 
      for( int ivz = 1 ; ivz<=nVtxBin ; ivz++) {
	newtreeTrkJet[icent][ivz] = new TTree(Form("trackAndGenParticles_first_cBin2icent%d_ivz%d",icent,ivz),"track and jets");
	newtreeTrkJet[icent][ivz]->SetMaxTreeSize(MAXTREESIZE);
	newtreeTrkJet[icent][ivz]->Branch("evt",&evt.run,"run/I:evt:cBin:pBin:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:reweight/F");

	newtreeTrkJet[icent][ivz]->Branch("nTrk",   &nTrk,  "nTrk/I");
	newtreeTrkJet[icent][ivz]->Branch("trkPt",  trkPt,  "trkPt[nTrk]/F");
	newtreeTrkJet[icent][ivz]->Branch("trkEta", trkEta, "trkEta[nTrk]/F");
	newtreeTrkJet[icent][ivz]->Branch("trkPhi", trkPhi, "trkPhi[nTrk]/F");
	newtreeTrkJet[icent][ivz]->Branch("trkWeight", trkWeight, "trkWeight[nTrk]/F");

	newtreeTrkJet[icent][ivz]->Branch("nJet",   &nJet,  "nJet/I");
	newtreeTrkJet[icent][ivz]->Branch("jetPt",  jetPt,  "jetPt[nJet]/F");
	newtreeTrkJet[icent][ivz]->Branch("jetEta", jetEta, "jetEta[nJet]/F");
	newtreeTrkJet[icent][ivz]->Branch("jetPhi", jetPhi, "jetPhi[nJet]/F");

	newtreeTrkJet[icent][ivz]->Branch("nGp",&nGp,  "nGp/I");
	newtreeTrkJet[icent][ivz]->Branch("gpPt", gpPt, "gpPt[nGp]/F");
	newtreeTrkJet[icent][ivz]->Branch("gpEta", gpEta, "gpEta[nGp]/F");
	newtreeTrkJet[icent][ivz]->Branch("gpPhi", gpPhi, "gpPhi[nGp]/F");
	newtreeTrkJet[icent][ivz]->Branch("gpChg", gpChg, "gpChg[nGp]/I");
      }
  }
  
  
  // vertex histogram 
  float vzCut = vtxCutData;
  if ( isMC )  
    vzCut = vtxCutMc;
  
  TH1F* hvz = new TH1F("hvz","",nVtxBin,-vzCut,vzCut);
  
  
  // event plane hitogram
  TH1F* hEvtPlnBin = new TH1F("hEvtPlnBin", "", nPlnBin, -PI/2., PI/2.);
  const int theEvtPlNumber = 21;
  
  // jet algos                                                                                                                                                  
  Jets* theJet;
  theJet = &(c->selectedJet) ;  // made by jetAlgo string!!!!                                                                                                       



  /// LOOP!!
  
  int nentries = c->GetEntries();
  cout << "number of entries = " << nentries << endl;
  int startEntry = 0;
  
  for (Long64_t jentry=startEntry ; jentry<nentries;jentry++) {
    //  for (Long64_t jentry=startEntry ; jentry<2000;jentry++) {
    
    if (jentry% 1000 == 0)  {
      cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;
    }
    c->GetEntry(jentry);
    
    evt.clear();
    evt.run   = c->evt.run;
    evt.evt = c->evt.evt;
    evt.cBin = c->evt.hiBin;
    evt.pBin   = hEvtPlnBin->FindBin( c->evt.hiEvtPlanes[theEvtPlNumber] ) ;
    evt.reweight = 1;
    evt.trig = 0;
    evt.offlSel = (c->skim.pcollisionEventSelection > 0);
    evt.noiseFilt = (c->skim.pHBHENoiseFilter > 0);
    evt.anaEvtSel = c->selectEvent() && evt.trig;
    evt.vz = c->evt.vz;

    if (  (isMC ==0 ) && (evt.offlSel!=1) )
      continue;
    if ( (isMC ==0 ) && (evt.noiseFilt!=1)  )
      continue;

    
    // vertex bin and cut!! 
    
    int vzBin = hvz->FindBin(evt.vz)  ;
    if ( (vzBin<1) || ( vzBin > nVtxBin) ) 
      continue;
    
    int cBin = evt.cBin;  
   
    //////////////////////////////////////////// New collection of tracks
    nTrk = 0; 
    for (int it=0; it < c->track.nTrk; it++ ) { 
      //if ( c->track.trkPt[it] < trkBoundary )   continue;
      if ( c->track.highPurity[it] == 0 )
	continue;   // only high purity high pt tracks and all pixel track
      trkPt[nTrk]  = c->track.trkPt[it];
      trkEta[nTrk] = c->track.trkEta[it];
      trkPhi[nTrk] = c->track.trkPhi[it]; 
      
      if ( trkPt[nTrk] < cuttrkPt ) 
	continue;
      if ( fabs(trkEta[nTrk]) > cuttrkEtaSkim ) 
	continue;
      
      trkWeight[nTrk] = c->getTrackCorrection(it);
      nTrk++;
    }

    //////////////////////////////////////////// New collection of jets
    nJet = 0;
    for (int ij=0; ij< theJet->nref ; ij++) {
      if ( theJet->jtpt[ij] < cutjetPtSkim)
	continue;
      if ( fabs( theJet->jteta[ij] ) > cutjetEta ) //
	continue;
      
      jetPt[nJet] = theJet->jtpt[ij];
      jetEta[nJet] = theJet->jteta[ij];
      jetPhi[nJet] = theJet->jtphi[ij];
      nJet++;
    }
    
    
    
    /// Gen Particle 
    nGp = 0;
    if ( isMC ) {
      for ( int ig = 0 ; ig < c->genparticle.mult ; ig++) {
	if ( c->genparticle.pt[ig] < cuttrkPt )
	  continue;
	if ( fabs( c->genparticle.eta[ig] ) > cuttrkEtaSkim ) 
	  continue;
	if ( c->genparticle.chg[ig] == 0 )
	  continue;
	
	gpChg[nGp] =  c->genparticle.chg[ig] ;
	gpPt[nGp]  = c->genparticle.pt[ig];
	gpEta[nGp] = c->genparticle.eta[ig];
	gpPhi[nGp] = c->genparticle.phi[ig];	
	nGp++;
      }
    }
    
    
    
    newtreeTrkJet[cBin][vzBin]->Fill();
    
    
  }
  
  
  
  
  
  newfile_data->Write();
  cout << " Done! "<< endl;
}




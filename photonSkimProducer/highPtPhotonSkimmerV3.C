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
#include "../hiForestV3/hiForest.h"
#include "CutAndBinCollection2012.h"
#include <time.h>


using namespace std;

static const long MAXTREESIZE = 10000000000;





void highPtPhotonSkimmerV3(TString inputFile_="/home/jazzitup/forestFiles/pA/pA_photonSkimForest_v85.root",
			   TString outname = "testPhotonSkim.root",
			   float photonPtCut=50
			   )
{ 
  // start from here
  // path length histogram
  
  HiForest * t;
  bool isPPb = true;
  if( isPPb) {
    t = new HiForest(inputFile_.Data(),"",cPPb);
  }
  else{
    return;
  }
 
  t->SetOutputFile(outname.Data());
  // LOOP!!
  int nentries = t->GetEntries();
  //  nentries = 5000;
  cout << "number of entries = " << nentries << endl;
  for (Long64_t jentry = 0 ; jentry < nentries; jentry++) {
    if (jentry% 1000 == 0)  {
      cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;
    }
    t->GetEntry(jentry);
    
    bool isHighPtPhoton = false;
    for (int jpho=0;jpho< t->photon.nPhotons;jpho++) {
      if (  ( t->photon.pt[jpho] > photonPtCut ) && ( fabs( t->photon.eta[jpho] ) < 1.5 ) )
	isHighPtPhoton = true;
    }
    
    if (isHighPtPhoton)
      t->FillOutput();
  }
  delete t;
}


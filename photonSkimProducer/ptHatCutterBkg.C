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
#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <time.h>


using namespace std;

static const long MAXTREESIZE = 10000000000;





void ptHatCutterBkg( int ptHatCut1 = 30, int ptHatCut2=50) {
  //collisionType
  collisionType colli = cPPb;
  TString inputFile_="/home/jazzitup/forestFiles/pp/emDijet30_50_80_120_CMSSW538HIp2.root";
  TString outname = Form("/home/jazzitup/forestFiles/pp/emDijet%dto%d_CMSSW538HIp2.root",ptHatCut1, ptHatCut2);
  
  
  // start from here
  // path length histogram
  
  HiForest * t;
  t = new HiForest(inputFile_.Data(),"",colli);
   
  t->SetOutputFile(outname.Data());
  // LOOP!!
  t->InitTree();

  int nentries = t->GetEntries();
  //   nentries = 20000;
  cout << "number of entries = " << nentries << endl;
  for (Long64_t jentry = 0 ; jentry < nentries; jentry++) {
    if (jentry% 10000 == 0)  {
      cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;
    }
    t->GetEntry(jentry);
    
    
    if ( !((t->photon.ptHat > ptHatCut1) && (t->photon.ptHat < ptHatCut2)) )
      continue;
    
    t->FillOutput();
  }
  delete t;
}


///////////////////////////////////////////////////////////////////                        
// cross_section_weight.C                                        //
// Creator : Yongsun Kim (Korea U.), kingmking@gmail.com         //
// Function : Calculate the relative cross-section of each pt hat//
// samples                                                       //
///////////////////////////////////////////////////////////////////                        
///////////////////////////////////////////////////////////////////     

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include "commonUtility.h"
//last forward run is 211256


//const Double_t hfBins[] = {0, 20, 30, 1000}; //last entry is upper bound on last bin
//const Int_t nhfBins = 3;

//int returnHFBin(double hf);

void cross_section_weight( bool isPP=1) 
{
  
  // Variables that will hold the tree information
  int             nPar;
  Float_t         et[500];   //[nPar]
  Float_t         eta[500];   //[nPar]
  Float_t         phi[500];   //[nPar]
  Int_t           id[500];   //[nPar]
  Int_t           momId[500];   //[nPar]
  Int_t           status[500];   //[nPar]
  Float_t         ptHat;
  TBranch        *b_nPar;   //!
  TBranch        *b_et;   //!
  TBranch        *b_eta;   //!
  TBranch        *b_phi;   //!
  TBranch        *b_id;   //!
  TBranch        *b_momId;   //!
  TBranch        *b_status;   //!
  TBranch        *b_ptHat;   //!  ///////////////////////

  TFile *f1[10];
  TTree* t1[10];
  TTree* genp[10];
  double n1[10];
  double n2[10][10];

  TH1::SetDefaultSumw2();
  TH1D* hPhoPt[10];  
  TH1D* hPtHat[10];  

  cout << endl << " Entries : " << endl;
  for ( int i=1 ; i <=3; i++) {
    
    if ( isPP ) { 
      if (i==1)  f1[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pp2760_pythia_allQCDPhoton30_CMSSW538HIp2.root");
      else if (i==2) f1[i]=new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pp2760_pythia_allQCDPhoton50_CMSSW538HIp2.root");
      else if ( i==3 )  f1[i] = new TFile("/home/goyeonju/recent2013/jetAnalysis/files/forest/pp2760_pythia_allQCDPhoton80_CMSSW538HIp2.root");
    }
    else {
      if ( i==1 )  f1[i] = new TFile("/home/jazzitup/forestFiles/pbpb/pbpb/PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root");
      else if ( i==2 )  f1[i] = new TFile("/home/jazzitup/forestFiles/pbpb/pbpb/PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root");
      else if ( i==3 )  f1[i] = new TFile("/home/jazzitup/forestFiles/pbpb/pbpb/PbPb_pythiaHYDJET_forest_AllQCDPhotons80.root");
    }


    hPtHat[i] = new TH1D(Form("ptHat_%d",i),";pt Hat;",400,0,400);
    hPhoPt[i] = new TH1D(Form("h_%d",i),";photon pT;",400,0,400);


    t1[i] = (TTree*)f1[i]->Get("multiPhotonAnalyzer/photon");
    t1[i]->SetBranchAddress("ptHat", &ptHat, &b_ptHat);
    //    n1[i] = t1[i]->GetEntries();
    genp[i] = (TTree*)f1[i]->Get("genpana/photon");
    genp[i]->SetBranchAddress("nPar", &nPar, &b_nPar);
    genp[i]->SetBranchAddress("et", et, &b_et);
    genp[i]->SetBranchAddress("eta", eta, &b_eta);
    genp[i]->SetBranchAddress("phi", phi, &b_phi);
    genp[i]->SetBranchAddress("id", id, &b_id);
    genp[i]->SetBranchAddress("momId", momId, &b_momId);
    genp[i]->SetBranchAddress("status", status, &b_status);
    
    n1[i]=0;
    for ( int j=1 ; j<=3; j++) { 
      n2[i][j] = 0;
    }
    // Loop! 
    for (Long64_t jentry=0; jentry< genp[i]->GetEntries() ; jentry++) {
      genp[i]->GetEntry(jentry);
      t1[i]->GetEntry(jentry);
      
      // find the leading gen photon 
      float maxEt = 0;
      for ( int jpar = 0 ; jpar< nPar ; jpar++) {
	if (  (et[jpar]>maxEt) && (fabs(eta[jpar])<1.44) && (fabs(momId[jpar])<=22) && (status[jpar]==1) && ( id[jpar]==22))
	  maxEt = et[jpar] ;   // "abs(eta)<3 && abs(momId)<=22 && status==1 && id==22"
      }
      if ( maxEt <35 ) 
	continue;
      
      hPtHat[i]->Fill (ptHat);
      hPhoPt[i]->Fill ( maxEt);

      if ( ptHat <50 ) 
	n2[i][1]++; 
      else if ( ptHat <80 )
	n2[i][2]++;
      else
	n2[i][3]++;
      
      n1[i]++;
      
   }
    
    for ( int j=1 ; j<=3; j++) {
      int pt1(0), pt2(0);
      if ( j==1 )  pt1 = 30;   if ( j==2 ) pt1 = 50 ; if ( j==3) pt1=80;
      if ( j==1 )  pt2 = 50;   if ( j==2 ) pt2 = 80 ; if ( j==3) pt2=10000;
      cout << Form("file of %dth,   pt hat : %d - %d : %d", i,  pt1, pt2, (int)n2[i][j]) << endl;
    }
    
  }
  cout << " ===============================" << endl;
  
  double n3[10];
  for ( int j=1 ; j<=3; j++) {
    n3[j] = n2[1][j] + n2[2][j] + n2[3][j];
    int pt1(0), pt2(0);
    if ( j==1 ) pt1 = 30 ;     if ( j==2) pt1 =50 ;     if ( j==3) pt1 =80    ;
    if ( j==1 ) pt2 = 50 ;     if ( j==2) pt2 =80 ;     if ( j==3) pt2 =10000 ;
    cout << Form("Sum :  pt hat : %d - %d : %d",  pt1, pt2, (int)(n3[j]) ) << endl;
  }
  cout << "Before rearrangement : "<< endl;
  for ( int j=1 ; j<=3; j++) {
    float pt1;
    if ( j==1 ) pt1 = 30 ;     if ( j==2) pt1 =50 ;     if ( j==3) pt1 =80    ;
    cout << "  " << pt1 << "GeV : "<< n1[j] << endl;
  }
  
  for ( int i=1 ; i <=3; i++) {	
    hPtHat[i]->Scale(1./n1[i]);
    handsomeTH1(hPtHat[i],i);
    hPhoPt[i]->Scale(1./n1[i]);
    handsomeTH1(hPhoPt[i],i);
  }




  TCanvas *c1 = new TCanvas("c1","",1000,1000);
  c1->Divide(2,2);
  c1->cd(1);
  for ( int i=1 ; i <=3; i++) {
    if ( i==1){
      hPtHat[i]->SetAxisRange(0.00001,0.5,"Y");
      hPtHat[i]->DrawCopy();
    }
    else hPtHat[i]->DrawCopy("same");
  }
  gPad->SetLogy();

  c1->cd(3);
  for ( int i=1 ; i <=3; i++) {
    if ( i==1){
      hPhoPt[i]->SetAxisRange(0.00001,0.5,"Y");
      hPhoPt[i]->DrawCopy();
    }
    else hPhoPt[i]->DrawCopy("same");
  }
  gPad->SetLogy();
  
  double w[10];  
  w[1] = 1;
  w[2] = hPhoPt[1]->Integral(80,400) / hPhoPt[2]->Integral(80,400) ; 
  w[3] = w[2] *  hPhoPt[2]-> Integral(140,400) / hPhoPt[3]->Integral(140,400) ; 
  
  cout << " Relative Cross-section : " << endl;
  cout << " 30GeV : " << w[1] <<endl;
  cout << " 50GeV : " << w[2] <<endl;
  cout << " 80GeV : " << w[3] <<endl;
  cout << " ===============================" << endl;
  cout << " 30 - 50GeV : " << w[1]-w[2] << "/" << n3[1] << "." << endl;
  cout << " 50 - 80GeV : " << w[2]-w[3] << "/" << n3[2] << "." << endl;
  cout << " 80GeV : " << w[3] << "/" << n3[3] << "." << endl;
  //  cout << " 120 - 170GeV : " << w[4]-w[5] << "/" << n3[4] << "." << endl;
  //  cout << " 170GeV : " << w[5] << "/" << n3[5] << "." << endl;

  
  c1->cd(2);
  for ( int i=1 ; i <=3; i++) {
    hPtHat[i]->Scale(w[i]);
    if ( i==1){
      hPtHat[i]->SetAxisRange(0.00001,0.5,"Y");
      hPtHat[i]->DrawCopy();
    }
    else hPtHat[i]->DrawCopy("same");
  }
  gPad->SetLogy();

  c1->cd(4);
  for ( int i=1 ; i <=3; i++) {
    hPhoPt[i]->Scale(w[i]);
    if ( i==1){
      hPhoPt[i]->SetAxisRange(0.00001,0.5,"Y");
      hPhoPt[i]->DrawCopy();
    }
    else hPhoPt[i]->DrawCopy("same");
  }
  gPad->SetLogy();

  

}

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

void cross_section_weight() 
{
  
  TFile *f1[10];
  TTree* t1[10];
  TTree* genp[10];
  double n1[10];
  double n2[10][10];

  cout << endl << " Entries : " << endl;
  for ( int i=1 ; i <=5; i++) {
    if ( i==1 )  f1[i] = new TFile("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root");
    else if ( i==2 )  f1[i] = new TFile("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root");
    else if ( i==3 )  f1[i] = new TFile("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons80.root");
    else if ( i==4 )  f1[i] = new TFile("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons120.root");
    else if ( i==5 )  f1[i] = new TFile("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons170.root");


    t1[i] = (TTree*)f1[i]->Get("multiPhotonAnalyzer/photon");
    n1[i] = t1[i]->GetEntries();
    genp[i] = (TTree*)f1[i]->Get("genpana/photon");
    for ( int j=1 ; j<=5; j++) { 
      
      int pt1(0), pt2(0);
      if ( j==1 ) pt1 = 30 ;     if ( j==2) pt1 =50 ;     if ( j==3) pt1 =80 ;     if ( j==4) pt1 =120 ;     if ( j==5) pt1 = 170 ;
      if ( j==1 ) pt2 = 50 ;     if ( j==2) pt2 =80 ;     if ( j==3) pt2 =120 ;     if ( j==4) pt2 =170 ;     if ( j==5) pt2 = 10000 ;
      n2[i][j] = t1[i]->GetEntries(Form("ptHat>%d && ptHat<%d", pt1, pt2) );

      cout << Form("file of %dth,   pt hat : %d - %d : %d", i,  pt1, pt2, (int)n2[i][j]) << endl;
    }
  }
  cout << " ===============================" << endl;
  
  double n3[10];
  for ( int j=1 ; j<=5; j++) {
    n3[j] = n2[1][j] + n2[2][j] + n2[3][j] + n2[4][j] + n2[5][j] ;
    int pt1(0), pt2(0);
    if ( j==1 ) pt1 = 30 ;     if ( j==2) pt1 =50 ;     if ( j==3) pt1 =80 ;     if ( j==4) pt1 =120 ;     if ( j==5) pt1 = 170 ;
    if ( j==1 ) pt2 = 50 ;     if ( j==2) pt2 =80 ;     if ( j==3) pt2 =120 ;     if ( j==4) pt2 =170 ;     if ( j==5) pt2 = 10000 ;
    
    cout << Form("Sum :  pt hat : %d - %d : %d",  pt1, pt2, (int)(n3[j]) ) << endl;
  }
  
  cout << " 30GeV : " << n1[1] <<endl;
  cout << " 50GeV : " << n1[2] <<endl;
  cout << " 80GeV : " << n1[3] <<endl;
  cout << " 120GeV : " << n1[4] <<endl;
  cout << " 170GeV : " << n1[5] <<endl;
  
  
  TH1::SetDefaultSumw2();
  TFile *f[10]; 
  TTree* t[10];
  TH1D* h[10];
  for ( int i=1 ; i <=5; i++) {	
    h[i] = new TH1D(Form("h_%d",i),"",300,0,300);
    genp[i]->Draw(Form("et>>%s",h[i]->GetName()),"abs(eta)<1.44 && abs(momId)<=22 && status==1 && id==22");
    h[i]->Scale(1./n1[i]);
    handsomeTH1(h[i],i);
  }
  TCanvas *c1 = new TCanvas("c1","",800,400);
  c1->Divide(2);
  c1->cd(1);
  for ( int i=1 ; i <=5; i++) {
    if ( i==1){
      h[i]->SetAxisRange(0.00001,0.5,"Y");
      h[i]->DrawCopy();
    }
    else h[i]->DrawCopy("same");
  }
  gPad->SetLogy();
  
  double w[10];  
  w[1] = 1;
  w[2] = h[1]->Integral(100,300) / h[2]->Integral(100,300) ; 
  w[3] = w[2] *  h[2]->Integral(140,300) / h[3]->Integral(140,300) ; 
  w[4] = w[3] *  h[3]->Integral(180,300) / h[4]->Integral(180,300) ; 
  w[5] = w[4] *  h[4]->Integral(220,300) / h[5]->Integral(220,300) ; 
  
  cout << " Relative Cross-section : " << endl;
  cout << " 30GeV : " << w[1] <<endl;
  cout << " 50GeV : " << w[2] <<endl;
  cout << " 80GeV : " << w[3] <<endl;
  cout << " 120GeV : " << w[4] <<endl;
  cout << " 170GeV : " << w[5] <<endl;
  cout << " ===============================" << endl;
  cout << " 30 - 50GeV : " << w[1]-w[2] << "/" << n3[1] << "." << endl;
  cout << " 50 - 80GeV : " << w[2]-w[3] << "/" << n3[2] << "." << endl;
  cout << " 80 - 120GeV : " << w[3]-w[4] << "/" << n3[3] << "." << endl;
  cout << " 120 - 170GeV : " << w[4]-w[5] << "/" << n3[4] << "." << endl;
  cout << " 170GeV : " << w[5] << "/" << n3[5] << "." << endl;

  

  c1->cd(2);
  for ( int i=1 ; i <=5; i++) {
    h[i]->Scale(w[i]);
    if ( i==1){
      h[i]->SetAxisRange(0.00001,0.5,"Y");
      h[i]->DrawCopy();
    }
    else h[i]->DrawCopy("same");
  }
  gPad->SetLogy();

  

}

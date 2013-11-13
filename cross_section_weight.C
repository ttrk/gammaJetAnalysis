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
  TH1::SetDefaultSumw2();
  TFile *f[10]; 
  TTree* t[10];
  TH1D* h[10];
  double n[10];
  for ( int i=1 ; i <=5; i++) {	
    if ( i==1 )  f[i] = new TFile("yskimmedFiles/pbpb_2013fall/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root");
    else if ( i==2 )  f[i] = new TFile("yskimmedFiles/pbpb_2013fall/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root");
    else if ( i==3 )  f[i] = new TFile("yskimmedFiles/pbpb_2013fall/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons80.root");
    else if ( i==4 )  f[i] = new TFile("yskimmedFiles/pbpb_2013fall/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons120.root");
    else if ( i==5 )  f[i] = new TFile("yskimmedFiles/pbpb_2013fall/yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons170.root");
    
    t[i] = (TTree*)f[i]->Get("tgj");
    n[i] = t[i]->GetEntries();
    h[i] = new TH1D(Form("h_%d",i),"",300,0,300);
    t[i]->Draw(Form("photonEt>>%s",h[i]->GetName()));
    h[i]->Scale(1./n[i]);
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
  cout << " 30 - 50GeV : " << w[1]-w[2] <<endl;
  cout << " 50 - 80GeV : " << w[2]-w[3] <<endl;
  cout << " 80 - 120GeV : " << w[3]-w[4] <<endl;
  cout << " 120 - 170GeV : " << w[4]-w[5] <<endl;
  cout << " 170GeV : " << w[5] <<endl;



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

#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawPP60GeV(TString dirName="nominal", int prodDate=20131021) {
  TH1::SetDefaultSumw2();
  TH1D* hxjg;
  TH1D* hDphi;
  
  TH1D* meanXjg  = new TH1D("meanXjg_pp",";;<x>",1,0,1);
  TH1D* rjg  = new TH1D("meanRjg_pp",";;R",1,0,1);
  TH1D* dphiWidth = new TH1D("dphiWidth",";;width of dphi",1,0,1);

 

  char* fname =  Form("ffFiles/%s/photonTrackCorr_ppDATA_output_photonPtThr60_to_9999_jetPtThr30_%d.root", dirName.Data(), prodDate);
  TFile* histFile = new TFile(fname) ;
  cout << " Reading file : " << fname << endl;
  int icent = 7 ; 
  cout << " Getting histogram : " << Form("xjg_icent%d_final",icent) << endl;
  hxjg =   (TH1D*)histFile->Get(Form("xjg_icent%d_final",icent));
  cout << " Getting histogram : " <<   Form("xjg_icent%d_final",icent) << endl;
  hDphi =  (TH1D*)histFile->Get(Form("jetDphi_icent%d_final",icent));
  
  double rVal, rErr;
  
  rVal = hxjg->IntegralAndError(1, hxjg->GetNbinsX(), rErr, "width");
  printf("pp inclusive (>60GeV)  rval: %lf\n",  rVal);
  rjg->SetBinContent( 1, rVal );
  rjg->SetBinError  ( 1, rErr );
  
  meanXjg->SetBinContent( 1, hxjg->GetMean() );
  meanXjg->SetBinError  ( 1, hxjg->GetMeanError() );
  

  TCanvas* c1 = new TCanvas("c1","",1000,1000);
  c1->Divide(2,2);
  c1->cd(1);
  handsomeTH1(hDphi, 1 );
  hDphi->SetXTitle("#Delta#phi_{J#gamma}");
  hDphi->SetYTitle("Normalized entries");
  hDphi->SetMarkerStyle(24);
  hDphi->Scale(1./hDphi->Integral("width"));       
  hDphi->SetAxisRange(0,3.141592,"X");
  hDphi->SetAxisRange(0.01,30,"Y");
  hDphi->Draw();
  
  TString fitFunc = "(TMath::Pi()/20.0)*exp(-(TMath::Pi()-x)/[0])/([0]*(1-exp(-TMath::Pi()/[0])))";
  TF1* dphiFit = new TF1("fphi",fitFunc.Data(),2.0*TMath::Pi()/3.0,TMath::Pi());
  dphiFit->SetParameter(0,0.3);
  float fitxmin=3.1415926*2./3;
  hDphi->Fit("fphi","0","",fitxmin,3.1415926);   
  cout << "width = " << dphiFit->GetParameter(0) << endl;
  dphiWidth->SetBinContent(1, dphiFit->GetParameter(0) ) ;
  
  c1->cd(2);
  handsomeTH1(hxjg, 1);
  hxjg->SetXTitle("x_{J#gamma}");
  hxjg->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
  hxjg->SetMarkerStyle(24);
  
  hxjg->SetAxisRange(0,2.5,"X");
  hxjg->SetAxisRange(0,3,"Y");
  hxjg->Draw();
  
  c1->cd(3);
  meanXjg->SetYTitle("<x_{J#gamma}>");
  meanXjg->SetAxisRange(0.6,1.2,"Y");
  meanXjg->Draw();

  c1->cd(4);
  rjg->SetYTitle("<R_{J#gamma}>");
  rjg->SetAxisRange(0.4,1,"Y");
  rjg->Draw();

  // Save the final root histogram files
  TFile * fResults =  new TFile("pp60GeV_resultHistograms.root","update");
    
  meanXjg->SetName(Form("meanXjg"));
  meanXjg->Write();
    
  rjg->SetName(Form("meanRjg"));
  rjg->Write();
    
  hxjg->SetName(Form("dNdXjg"));
  hxjg->Write();
  hDphi->SetName(Form("dNdphi"));
  hDphi->Write();	
  dphiWidth->SetName(Form("dphiWidth"));
  dphiWidth->Write();	
  
  fResults->Close();
    
}


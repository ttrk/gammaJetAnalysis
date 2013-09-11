///////////////////////////////////////////////////////////////////                                
// gammaJetHistProducer.C                                        //
// Creator : Yongsun Kim (MIT), jazzitup@mit.edu                 //                                                 
// Function : Make the correlation function between Photon and   //
//            tracks.  Signal and Background are calculated      //
//            separately, and then background subtraction is     //
//            done.  Output histogrmas are saved in output file  //
///////////////////////////////////////////////////////////////////         
#include <TStyle.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <math.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TCut.h>
#include <TClonesArray.h>
#include <TRandom3.h>
#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012_purityOnly.h"
#include "corrFunctionJetTrk.h"

GjSpectra* nullGj;


fitResult getPurity(TString fname="", sampleType collision=kHIDATA, TCut candEvtCut = "", TCut sbEvtCut="", TString ccanvasName="",float photonPtThr=60, float photonPtThrUp=9999, float bkgCorr=30, float sigShift=-0.00006);


void gammaJetPurity(sampleType collision = kPPDATA, float photonPtThr=40, float photonPtThrUp=50, float jetPtThr=30, int icent =4,
		    float bkgCorr = 30, float sigShift =  -0.00007)
{
    TH1::SetDefaultSumw2();
  
  TString stringSampleType = getSampleName(collision); "";
  
  TDatime* date = new TDatime();
  TString  outName=  Form("photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr%d_%d.root",stringSampleType.Data(),(int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr,  date->GetDate());
  delete date;
  
  int lowerCent(0),  upperCent(0); 
  TCut centCut  = "";
  if ( (collision ==kHIDATA) || (collision==kHIMC) )   {
    lowerCent = centBin1[icent-1];
    upperCent = centBin1[icent]-1;
    if ( icent > 9999) {
      lowerCent = ((icent/100)%100)/2.5;
      upperCent =  (icent%100)/2.5 -1;
    }   
    centCut = Form("cBin >= %d && cBin<= %d",lowerCent,upperCent);
  }
  else if (  (collision ==kPPDATA) || (collision==kPPMC)  ){  // if it's pp 
    centCut = "(1==1)";
    icent = 7;
  }
  else { // pPb
    centCut = Form( "hf4Sum > %f && hf4Sum <= %f", (float)centBinPa[icent-1], (float)centBinPa[icent]);
  }
  
  cout <<" centrality : " << centCut.GetTitle() << endl;
      
  ///////// Photon cut //////////////////////////////////////////////////////////////////////////////
  
  cout <<" photon pt >" << photonPtThr << " GeV" << endl;
  TCut ptPhoCut  = Form("photonEt>%.1f && photonEt<%.1f", (float)photonPtThr, (float)photonPtThrUp  );
  TCut caloIso;
  
  if ( (collision==kPPMC) || (collision==kPPDATA) ) 
    caloIso = "(ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2) && hovere<0.1";
  else if ( (collision==kHIMC) || (collision==kHIDATA) )
    caloIso = "(sumIso<1) && hovere<0.1";
  else {
    caloIso = "ecalIso < 4.2  &&  hcalIso < 2.2  &&  trackIso < 2 && hovere<0.1";
  }
  
  TCut sbIso   = "(sumIso>10) && (sumIso<20) && hovere<0.1";
  //  if ( (collision==kPPMC) || (collision==kPPDATA) || (collision==kPAMC) || (collision==kPADATA)  )
  //  sbIso   = "ecalIso < 4.2  &&  hcalIso < 2.2 && trackIso > 2 && trackIso < 5 && hovere<0.1";

  TCut basicPhoCut = centCut && ptPhoCut && caloIso ;
  TCut sbPhoCut    = centCut && ptPhoCut && sbIso   ;
  TCut evtSeltCut = basicPhoCut;
  TCut sbSeltCut  = sbPhoCut;

  TCut phoCandCut   = "sigmaIetaIeta<0.010";
  TCut phoDecayCut  = "(sigmaIetaIeta>0.011) && (sigmaIetaIeta<0.017)";
  if  ( ( collision == kHIMC ) || (collision == kPPMC) ) 
    phoCandCut = phoCandCut && "genIso<5 && abs(genMomId)<=22";
  
  
  TString fname;
  if ( collision == kHIDATA) fname = fnameHIDATA;
  else if ( collision == kPADATA) fname = fnamePADATA;
  else if ( collision == kPPDATA) fname = fnamePPDATA;
  else fname = "";

  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  if (  ( collision == kHIDATA)   || ( collision==kPADATA) || ( collision == kPPDATA) ) {
    tgj->addFile(fname,  "tgj",  evtSeltCut,  1);
  }
  else if ( collision == kPPMC ) {
    tgj->addFile(fnamePPMC_AllQcdPho30to50,    "tgj", evtSeltCut, wPPMC_AllQcdPho30to50 );
    tgj->addFile(fnamePPMC_AllQcdPho50to80,    "tgj", evtSeltCut, wPPMC_AllQcdPho50to80 );
    tgj->addFile(fnamePPMC_AllQcdPho80to120,   "tgj", evtSeltCut, wPPMC_AllQcdPho80to120 );
    tgj->addFile(fnamePPMC_AllQcdPho120to9999, "tgj", evtSeltCut, wPPMC_AllQcdPho120to9999 );
  }
  else if ( collision == kPAMC ) {
    tgj->addFile(fnamePAMC_AllQcdPho30to50,    "tgj", evtSeltCut, wPAMC_AllQcdPho30to50 );
    tgj->addFile(fnamePAMC_AllQcdPho50to80,    "tgj", evtSeltCut, wPAMC_AllQcdPho50to80 );
    tgj->addFile(fnamePAMC_AllQcdPho80to120,   "tgj", evtSeltCut, wPAMC_AllQcdPho80to120 );
    tgj->addFile(fnamePAMC_AllQcdPho120to9999, "tgj", evtSeltCut, wPAMC_AllQcdPho120to9999 );
  }
  else  {    // kHIMC
    tgj->addFile(fnameHIMC_AllQcdPho30to50,    "tgj", evtSeltCut, wHIMC_AllQcdPho30to50 );
    tgj->addFile(fnameHIMC_AllQcdPho50to80,    "tgj", evtSeltCut, wHIMC_AllQcdPho50to80 );
    tgj->addFile(fnameHIMC_AllQcdPho80to9999,  "tgj", evtSeltCut, wHIMC_AllQcdPho80to9999 );
  }
  tgj->AddFriend("yJet");
 
  // get purity with the current jet cut ! 
  float purity(0);
  
  TString canvasName = Form("gifs/purity_%s_output_icent%d_photonPtThr%d-%d_jetPtThr%d", stringSampleType.Data(),  (int)icent, (int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr);
  
  //  if ( (collision==kPPDATA) && (photonPtThr < 50 ) ) {
  //   purity = 0.86 ;   
  //   cout << " !!!!!!!" << endl << endl << " purity is set as  0.86 for this bin because we don't have pp MC low pt sample " << endl;
  //   cout << endl << endl << endl << " !!!!!!" << endl;
  //  }

  if ( (collision==kHIDATA)||(collision==kPPDATA)||(collision==kPADATA) )  {
    fitResult fitr = getPurity(fname, collision, evtSeltCut, sbSeltCut, canvasName, photonPtThr, photonPtThrUp, bkgCorr, sigShift);
    purity = fitr.purity010;
  }
  else  {
    purity = 1;  
    cout << " MC purity = 1" << endl;
  }
  
}



fitResult getPurity(TString fname, sampleType collision, TCut evtSeltCut, TCut sbEvtCut, TString canvasName, float photonPtThr, float photonPtThrUp, float bkgCorr, float sigShift) {
  double purity(0);
  
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  cout <<" 1 " << endl;
  tgj->addFile(fname,  "tgj",  "",  1);
  cout <<" 2 " << endl;
  tgj->AddFriend("yJet");
  if   (collision==kPPDATA) { 
    tgjMC->addFile(fnamePPMC_AllQcdPho30to50,    "tgj", "", wPPMC_AllQcdPho30to50 ); 
    tgjMC->addFile(fnamePPMC_AllQcdPho50to80,    "tgj", "", wPPMC_AllQcdPho50to80 ); 
    tgjMC->addFile(fnamePPMC_AllQcdPho80to120,   "tgj", "", wPPMC_AllQcdPho80to120); 
    tgjMC->addFile(fnamePPMC_AllQcdPho120to9999, "tgj", "", wPPMC_AllQcdPho120to9999); 
  }
  else if (collision==kPADATA)     {
    tgjMC->addFile(fnamePAMC_AllQcdPho30to50,     "tgj","", wPAMC_AllQcdPho30to50);
    tgjMC->addFile(fnamePAMC_AllQcdPho50to80,     "tgj","", wPAMC_AllQcdPho50to80);
    tgjMC->addFile(fnamePAMC_AllQcdPho80to120,    "tgj","", wPAMC_AllQcdPho80to120);
    tgjMC->addFile(fnamePAMC_AllQcdPho120to9999,  "tgj","", wPAMC_AllQcdPho120to9999);
  }
  else if (collision==kHIDATA)  {
    tgjMC->addFile(fnameHIMC_AllQcdPho30to50,     "tgj", "",wHIMC_AllQcdPho30to50);
    tgjMC->addFile(fnameHIMC_AllQcdPho50to80,     "tgj", "",wHIMC_AllQcdPho50to80);
    tgjMC->addFile(fnameHIMC_AllQcdPho80to9999,   "tgj", "",wHIMC_AllQcdPho80to9999);
  }   
  else { 
    cout << " Error: getPurity.  check the type of the collision!  " << endl;
    fitResult fitr0;
    return fitr0;
  }
  
  TH1D* hCand = new TH1D("cand","",25,0,0.025);
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");  TH1D* hSig = (TH1D*)hCand->Clone("sig");
  
  //  tgj->Draw2(   hCand, "sigmaIetaIeta", evtSeltCut, "");
  // tgj->Draw2(   hBkg, "sigmaIetaIeta", sbEvtCut, "");
  tgj->Draw2(   hCand, "sigmaIetaIeta", evtSeltCut , "");
  tgj->Draw2(   hBkg, "sigmaIetaIeta", sbEvtCut , "");
  tgjMC->Draw2( hSig, Form("sigmaIetaIeta + (%f)",(float)sigShift ) , evtSeltCut && "genIso<5 && abs(genMomId)<=22", "");
  handsomeTH1(hCand,1);
  handsomeTH1(hSig,2);
  handsomeTH1(hBkg,4);
  
  // temporary
  
  for ( int ii=1 ; ii<=hBkg->GetNbinsX() ; ii++) {
    float xx = hBkg->GetBinCenter(ii);
    hBkg -> SetBinContent( ii, hBkg->GetBinContent(ii) * ( 1. - bkgCorr*(xx-0.01)) );
  }
  


  TCanvas* cPurity = new TCanvas("cpurity","",400,800);
  fitResult  fitr = doFit ( cPurity,hSig, hBkg, hCand, 0.005, 0.025 );
  cPurity->cd(1);
  drawText(Form("Purity : %.2f", (float)fitr.purity010), 0.5680963,0.429118);
  drawText(Form("p_{T}^{#gamma}: %d-%d GeV", (int)photonPtThr, (int)photonPtThrUp), 0.568,0.529118);
  cPurity->cd(2);
  drawText(Form("Sig corr : %.5f",(float)sigShift),  0.3680963,0.38);
  drawText(Form("Bkg corr : %d", (int)bkgCorr),  0.3680963,0.30);
  drawText(Form("#Chi^{2}/dof : %.2f", (float)fitr.chisq),  0.3680963,0.22);
  cPurity->SaveAs( Form("%s_bkgCorr%d_sigCorr%f.gif",canvasName.Data(),(int)bkgCorr,(float)sigShift ) );
  
  TCanvas* c1 = new TCanvas("c1","",100,100);
  
  
  delete tgj;
  delete tgjMC;
  delete hSig;
  delete hBkg;
  delete hCand;
  
  return fitr;
  
  
}


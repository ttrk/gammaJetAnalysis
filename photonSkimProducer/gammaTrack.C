///////////////////////////////////////////////////////////////////                                
// gammaTrack.C                                                  //                                                 
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
#include "commonUtility.h"
#include <TRandom3.h>
#include "CutAndBinCollection2012.h"
#include "corrFunctionTrk.h"

//void drawDetail(TH1D* corr[4][7]=0, TString mcLabel="", TString fname="",int icent=1, int ipt=1, int cutOpt=1, int iJetPt=1);
GjSpectra* nullGj;

void gammaTrkSingle( 	 GjSpectra* gjSpec_=nullGj,
			 multiTreeUtil* tTrk[3]=0,
			 corrFunctionTrk* corr_=0,
			 float purity=0,
			 int sampleType_=0,
			 TString var_ = "",
			 TCut cut_ ="",
			 TString theWeight="",
			 TCut phoCandCut_="",
			 TCut phoDecayCut_="",
			 TH1D* hTemplate_ =0,
			 TString outName="",
			 bool jetMixing=false);

fitResult getPurity(TString fname="", TCut candEvtCut = "", TCut sbEvtCut="", TCut jetCut="", TString ccanvasName="", bool jetMixing=false);

void gammaTrack(int sampleType = kHIDATA, float photonPtThr=60, float jetPtThr=30, int icent =1, TString jAlgo="akPu2PF", float coneDR=0.3, bool jetMixing=false,  int genLevel=0) {
  TH1::SetDefaultSumw2();
  


  TString stringSampleType = "";
  if ( sampleType == kHIMC )       stringSampleType = "pbpbMC";
  else if ( sampleType == kHIDATA )  stringSampleType = "pbpbDATA";
  else if ( sampleType == kPPDATA )  stringSampleType = "ppDATA";
  
  TDatime* date = new TDatime();
  TString outName=  Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_jetPtThr%d_jAlgo%s_coneDR%.2f_%d_jetMixing%d_genLevel%d.root",stringSampleType.Data(),(int)photonPtThr, (int)jetPtThr, jAlgo.Data(), (float)coneDR, date->GetDate(), (int)jetMixing, (int)genLevel);
  delete date;
    

  
  int lowerCent(0),  upperCent(0); 
  TCut centCut  = "";
  if ( (sampleType ==kHIDATA) || (sampleType==kHIMC) )   {
    lowerCent = centBin1[icent-1];
    upperCent = centBin1[icent]-1;
    centCut = Form("cBin >= %d && cBin<= %d",lowerCent,upperCent);
  }
  else {  // if it's pp 
    centCut = "cBin>27";
    icent = 0;
  }
  
  cout <<" centrality : " << centCut.GetTitle() << endl;
      
  ///////// Photon cut //////////////////////////////////////////////////////////////////////////////
  
  cout <<" photon pt >" << photonPtThr << " GeV" << endl;
  TCut ptPhoCut  = Form("photonEt>%.1f", (float)photonPtThr  );
  TCut caloIso = "(sumIso<1) && hovere<0.1";
  TCut sbIso   = "(sumIso>10) && (sumIso<20) && hovere<0.1";
  TCut basicPhoCut = centCut && ptPhoCut && caloIso ;
  TCut sbPhoCut    = centCut && ptPhoCut && sbIso   ;
  TCut evtSeltCut = basicPhoCut;
  TCut sbSeltCut  = sbPhoCut;

  TCut phoCandCut   = "sigmaIetaIeta<0.010";
  TCut phoDecayCut  = "(sigmaIetaIeta>0.011) && (sigmaIetaIeta<0.017)";
  if  (sampleType == kHIMC )
    phoCandCut = phoCandCut && "genIso<5 && abs(genMomId)<=22";

  
  TString fname;
  if ( jAlgo =="akPu3PF" ) {
    if ( sampleType == kHIMC)              fname = fnameAllQcdPho50Ak3;
    else if ( sampleType == kHIDATA)       fname = fnameDATAPbPbAk3;
    else if ( sampleType == kPPDATA)       fname = fnameDATAppAk3;
  }
  else if ( jAlgo=="akPu2PF" ) {
    if ( sampleType == kHIMC)             fname = fnameAllQcdPho50Ak2;
    else if ( sampleType == kHIDATA)      fname = fnameDATAPbPbAk2;
    else if ( sampleType == kPPDATA)      fname = fnameDATAppAk2;
   
  }
  
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  if (!jetMixing) {
    tgj->addFile(fname,  "tgj",  evtSeltCut,  1);
    tgj->AddFriend("yJet");
  }
  else  {
    tgj->addFile(fname,  "tgjMb",  evtSeltCut,  1);
    tgj->AddFriend("yJetMb");
  }

  // get purity with the current jet cut ! 
  TCut jetCut     =  Form("abs(dphi)>%f && abs(eta)<%f && pt>%f",(float)awayRange, (float)cutjetEta, (float)jetPtThr);
  float purity(0);

  TString canvasName = Form("ffFiles/gifs/purity_%s_output_icent%d_photonPtThr%d_jetPtThr%d_jAlgo%s_coneDR%.2f_jetMixing%d", stringSampleType.Data(),  (int)icent, (int)photonPtThr, (int)jetPtThr, jAlgo.Data(), (float)coneDR, (int)jetMixing);
  
  if ( sampleType == kHIDATA ) {
    fitResult fitr = getPurity(fname, evtSeltCut, sbSeltCut, jetCut, canvasName, jetMixing);
    purity = fitr.purity010;
  }
  else if ( sampleType == kPPDATA) {
    fitResult fitr = getPurity(fname, evtSeltCut, sbSeltCut, jetCut, canvasName, jetMixing);
    purity = fitr.purity010;
  }
  else if ( sampleType == kHIMC) {
    purity = 1;  
    cout << " MC purity = 1" << endl;
  }

  GjSpectra* gjSpec = new GjSpectra();
  gjSpec->init(Form("pho%.0f_jet%.f", (float)photonPtThr, (float)jetPtThr));
  tgj->Draw2(gjSpec->hPtPhoCand,  "pt", phoCandCut && jetCut ,"");
  tgj->Draw2(gjSpec->hPtPhoDecay, "pt", phoDecayCut && jetCut,"");

  GjSpectra* gSpec = new GjSpectra();
  gSpec->init(Form("pho%.0f", (float)photonPtThr));
  tgj->Draw2(gSpec->hPtPhoCand,  "photonEt", phoCandCut, "")  ;
  tgj->Draw2(gSpec->hPtPhoDecay, "photonEt", phoDecayCut, "") ;
  
  
  multiTreeUtil* tJet[3];
  if  ((sampleType == kHIDATA) || (sampleType==kHIMC))  {
    tJet[kJetRaw] = new multiTreeUtil();
    if (!jetMixing) {
      tJet[kJetRaw]->addFile(fname,  "yJet",     basicPhoCut, 1 ) ;  // This is evtSeltCut except the leading jet requirement
      tJet[kJetRaw]->AddFriend("tgj");
    }
    else  {
      tJet[kJetRaw]->addFile(fname,  "yJetMb",     basicPhoCut, 1 ) ;  // This is evtSeltCut except the leading jet requirement
      tJet[kJetRaw]->AddFriend("tgjMb");
    }
    
    //    tJet[kJetBkg] = new multiTreeUtil();
    // tJet[kJetBkg]->addFile(fname,  "yJetMb",   basicPhoCut, 1 ) ;  // This is evtSeltCut except the leading jet requirement
    //   tJet[kJetBkg]->AddFriend("tgjMb");  // VERY IMPORTANT!!!!!
  }
  
  // Jet distribution
  TH1D* hJetPartner = new TH1D(Form("jetPartner_icent%d",icent),";Jet p_{T} (GeV) ;dN/dp_{T}",30,0,300);
  TCut jetCutFF      =  jetCut;
  corrFunctionTrk* cJetPartner = new corrFunctionTrk();
  if  ((sampleType == kHIDATA) || (sampleType==kHIMC)) {
    gammaTrkSingle( gSpec,  tJet, cJetPartner,  purity,  // gSpec is used.. not gjSpec 
		    sampleType, "pt", jetCutFF, "",
		    phoCandCut, phoDecayCut,  hJetPartner, outName,jetMixing);
  }

  /*
    Jet delta phi distribution 
    TH1D* hJetDphi = new TH1D(Form("jetDphi_icent%d",icent),"; #Delta#phi ;",30,0,3.141592);
    corrFunctionTrk* cJetDphi = new corrFunctionTrk();
    TCut jetCutEtaPt    =  Form("abs(eta)<%f && pt>%f", (float)cutjetEta, (float)jetPtThr );
    if ( ((sampleType == kHIDATA) || (sampleType==kHIMC)) && (!jetMixing) ) {
    gammaTrkSingle( gjSpec,  tJet, cJetDphi,  purity, 
    sampleType, "dphi", jetCutEtaPt, "",
    phoCandCut, phoDecayCut,  hJetDphi, outName, jetMixing);
    }
  */
  
  
  /////////// Tracks
  multiTreeUtil* tTrk[3];
  tTrk[kTrkRaw] = new multiTreeUtil();
  tTrk[kTrkBkg] = new multiTreeUtil();
  
  if (!jetMixing) {
    if ( genLevel==0 ) { 
      tTrk[kTrkRaw]->addFile(fname,  "yTrk",  evtSeltCut,  1);
      tTrk[kTrkBkg]->addFile(fname,  "mTrk",  evtSeltCut,  1);
    }
    else if ( genLevel==1) {
      tTrk[kTrkRaw]->addFile(fname,  "gp",  evtSeltCut,  1);
      tTrk[kTrkBkg]->addFile(fname,  "mGp",  evtSeltCut,  1);
    }
    
    tTrk[kTrkRaw]->AddFriend("tgj");
    tTrk[kTrkBkg]->AddFriend("tgj");
    }
  else {
    if ( genLevel==0 ) {
      tTrk[kTrkRaw]->addFile(fname,  "yTrkMb",  evtSeltCut,  1);
      tTrk[kTrkBkg]->addFile(fname,  "mTrkMb",  evtSeltCut,  1);
    }
    else if ( genLevel==1 ) {
      tTrk[kTrkRaw]->addFile(fname,  "gpMb",  evtSeltCut,  1);
      tTrk[kTrkBkg]->addFile(fname,  "mGpMb",  evtSeltCut,  1);
    }
    tTrk[kTrkRaw]->AddFriend("tgjMb");
    tTrk[kTrkBkg]->AddFriend("tgjMb");
  }  
  
  // Fragmentation function
  //  TCut jetCut     =  Form("abs(dphi)>%f && abs(eta)<%f && pt>%f",(float)awayRange, (float)cutjetEta, (float)jetPtThr);
  TCut trkCutFF         = Form("abs(eta)<%.2f && injDr<%.2f && injPt>%.2f && abs(injEta)<%.3f  && abs(injDphi)>%f",(float)cuttrkEtaForAna,(float)coneDR, (float)jetPtThr, (float)cutjetEta, (float)awayRange );
  
  TH1D* hFFPho = new TH1D(Form("ffPhoton_type1_icent%d",icent),";#xi;dN/d#xi",14,0,7);
  corrFunctionTrk* cFFPho = new corrFunctionTrk();
  TString trkVarFF         = Form("-log(pt/photonEt)");
  TString trkWeight = "trkWeight";
  if (genLevel==1)
    trkWeight = "";
  gammaTrkSingle( gjSpec,  tTrk, cFFPho,  purity, 
		  sampleType, trkVarFF, trkCutFF,  trkWeight,
		  phoCandCut, phoDecayCut,  hFFPho, outName, jetMixing);
  
  TH1D* hFFJet = (TH1D*)hFFPho->Clone(Form("ffJet_type1_icent%d",icent));
  corrFunctionTrk* cFFJet = new corrFunctionTrk();
  TString trkVarFFJet         = Form("-log(pt/injPt)");
  gammaTrkSingle( gjSpec,  tTrk, cFFJet,  purity, 
		  sampleType, trkVarFFJet, trkCutFF,  trkWeight,
		  phoCandCut, phoDecayCut,  
		  hFFJet, outName, jetMixing);
  

  const int nTrkPtBins = 12;
  double trkPtBins[nTrkPtBins+1] = {1,2,3,4,5,7,9,12,15,20,25,50,100};
  
  TH1D* hFF_type3 = new TH1D(Form("ff_type3_icent%d",icent),";;",nTrkPtBins,trkPtBins);
  corrFunctionTrk* cFF_type3 = new corrFunctionTrk();
  TString trkVarFF_type3    = Form("pt");
  gammaTrkSingle( gjSpec,  tTrk, cFF_type3,  purity,
                  sampleType, trkVarFF_type3, trkCutFF,  trkWeight,
                  phoCandCut, phoDecayCut,  hFF_type3, outName, jetMixing);
  
  corrFunctionTrk* cFF_type3_sube0 = new corrFunctionTrk();
  TH1D* hFF_type3_sube0 = new TH1D(Form("ff_type3_sube0_icent%d",icent),";;",nTrkPtBins,trkPtBins);
  corrFunctionTrk* cFF_type3_sube1 = new corrFunctionTrk();
  TH1D* hFF_type3_sube1 = new TH1D(Form("ff_type3_sube1_icent%d",icent),";;",nTrkPtBins,trkPtBins);
  if ( genLevel ==1 ) { 
    gammaTrkSingle( gjSpec,  tTrk, cFF_type3_sube0,  purity,
		    sampleType, trkVarFF_type3, trkCutFF && "sube==0",  trkWeight,
		    phoCandCut, phoDecayCut,  hFF_type3_sube0, outName, jetMixing);
    gammaTrkSingle( gjSpec,  tTrk, cFF_type3_sube1,  purity,
		    sampleType, trkVarFF_type3, trkCutFF && "sube!=0",  trkWeight,
		    phoCandCut, phoDecayCut,  hFF_type3_sube1, outName, jetMixing);
  }
  
  return;

  
  // weights!    
  
  TString weightRes         = "trkWeight * pt";//*-cos(dphi)";                                                                               
  
  TH1D* hMedRes03 = new TH1D(Form("medResDr03_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFRes03 = new corrFunctionTrk();
  TCut trkCutRes03            = Form("abs(eta)<%.2f && injDr>0.3",(float)cuttrkEtaForAna);
  TString trkVarRes         = "dphi";

 
  gammaTrkSingle( gjSpec,  tTrk, cFFRes03,  purity, 
		  sampleType, trkVarRes, trkCutRes03, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedRes03, outName, jetMixing);


  TH1D* hMedRes05 = new TH1D(Form("medResDr05_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFRes05 = new corrFunctionTrk();
  TCut trkCutRes05            = Form("abs(eta)<%.2f && injDr>0.5",(float)cuttrkEtaForAna);
  gammaTrkSingle( gjSpec,  tTrk, cFFRes05,  purity, 
		  sampleType, trkVarRes, trkCutRes05, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedRes05, outName, jetMixing);

  TH1D* hMedResInc = new TH1D(Form("medResDrInc_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFResInc = new corrFunctionTrk();
  TCut trkCutResInc            = Form("abs(eta)<%.2f",(float)cuttrkEtaForAna);
  gammaTrkSingle( gjSpec,  tTrk, cFFResInc,  purity, 
		  sampleType, trkVarRes, trkCutResInc, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedResInc, outName, jetMixing);

  TH1D* hMedResIncPtCut2 = new TH1D(Form("medResDrIncPtCut2_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFResIncPtCut2 = new corrFunctionTrk();
  TCut trkCutResIncPtCut2            = Form("abs(eta)<%.2f && pt<2",(float)cuttrkEtaForAna);
  gammaTrkSingle( gjSpec,  tTrk, cFFResIncPtCut2,  purity, 
		  sampleType, trkVarRes, trkCutResIncPtCut2, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedResIncPtCut2, outName, jetMixing);

  TH1D* hMedResIncPtCut4 = new TH1D(Form("medResDrIncPtCut4_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFResIncPtCut4 = new corrFunctionTrk();
  TCut trkCutResIncPtCut4            = Form("abs(eta)<%.2f && pt<4",(float)cuttrkEtaForAna);
  gammaTrkSingle( gjSpec,  tTrk, cFFResIncPtCut4,  purity, 
		  sampleType, trkVarRes, trkCutResIncPtCut4, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedResIncPtCut4, outName, jetMixing);

  TH1D* hMedResIncPtCut8 = new TH1D(Form("medResDrIncPtCut8_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFResIncPtCut8 = new corrFunctionTrk();
  TCut trkCutResIncPtCut8            = Form("abs(eta)<%.2f && pt<8",(float)cuttrkEtaForAna);
  gammaTrkSingle( gjSpec,  tTrk, cFFResIncPtCut8,  purity, 
		  sampleType, trkVarRes, trkCutResIncPtCut8, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedResIncPtCut8, outName, jetMixing);

  TH1D* hMedResIncPtCut16 = new TH1D(Form("medResDrIncPtCut16_icent%d",icent),"; #dphi; ",10,PI/2.,PI);
  corrFunctionTrk* cFFResIncPtCut16 = new corrFunctionTrk();
  TCut trkCutResIncPtCut16            = Form("abs(eta)<%.2f && pt<16",(float)cuttrkEtaForAna);
  gammaTrkSingle( gjSpec,  tTrk, cFFResIncPtCut16,  purity, 
		  sampleType, trkVarRes, trkCutResIncPtCut16, weightRes, 
		  phoCandCut,   phoDecayCut,  hMedResIncPtCut16, outName, jetMixing);


  
}


void gammaTrkSingle(     GjSpectra* gjSpec,  multiTreeUtil* tTrk[3],   corrFunctionTrk* corr, 
			 float purity,       int sampleType, 	     TString var,     
			 TCut cut, 		TString theWeight,	 TCut phoCandCut,   TCut phoDecayCut,
			 TH1D* hTemplate,  TString outfName, bool jetMixing)
{
  TH1::SetDefaultSumw2();
  corr->init(gjSpec, sampleType, purity, hTemplate);
  
  tTrk[kTrkRaw]->Draw2(corr->Func[kPhoCand][kTrkRaw],  var,  phoCandCut  && cut, theWeight);
  if ( tTrk[kTrkBkg]!=0)  
    tTrk[kTrkBkg]->Draw2(corr->Func[kPhoCand][kTrkBkg],  var,  phoCandCut  && cut, theWeight);
  
  
  if ( (sampleType==kHIDATA) || (sampleType==kPPDATA) ) {
    tTrk[kTrkRaw]->Draw2(corr->Func[kPhoDecay][kTrkRaw], var, phoDecayCut && cut,  theWeight);
    if (tTrk[kTrkBkg]!=0)  
      tTrk[kTrkBkg]->Draw2(corr->Func[kPhoDecay][kTrkBkg], var, phoDecayCut && cut,  theWeight);
  }
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkRaw]); 
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkBkg]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkRaw]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkBkg]);
  
  corr->calCorr(jetMixing);
  TFile outf = TFile(outfName.Data(),"update");
  corr->Func[kPhoCand][kTrkRaw]->Write();
  corr->Func[kPhoCand][kTrkBkg]->Write();
  corr->Func[kPhoCand][kTrkSig]->Write();
  corr->Func[kPhoDecay][kTrkRaw]->Write();
  corr->Func[kPhoDecay][kTrkBkg]->Write();
  corr->Func[kPhoDecay][kTrkSig]->Write();
  corr->Func[kPhoSig][kTrkRaw]->Write();
  corr->Func[kPhoSig][kTrkBkg]->Write();
  corr->Func[kPhoSig][kTrkSig]->Write();
  
  outf.Close();  
}



fitResult getPurity(TString fname, TCut evtSeltCut, TCut sbEvtCut, TCut jetCut, TString canvasName, bool jetMixing) {
  double purity(0);
  
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  if ( !jetMixing) {
    tgj->addFile(fname,  "tgj",  "",  1);
    tgj->AddFriend("yJet");
  }
  else { 
    tgj->addFile(fname,  "tgjMb",  "",  1);
    tgj->AddFriend("yJetMb");
  }
  tgjMC->addFile(fnameAllQcdPho30Ak2, "tgj", "", 1);
  
  TH1D* hCand = new TH1D("cand","",25,0,0.025);
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");  TH1D* hSig = (TH1D*)hCand->Clone("sig");

  tgj->Draw2(   hCand, "sigmaIetaIeta", evtSeltCut && jetCut, "");
  tgj->Draw2(   hBkg, "sigmaIetaIeta", sbEvtCut && jetCut, "");
  tgjMC->Draw2( hSig, "sigmaIetaIeta", evtSeltCut && "genIso<5 && abs(genMomId)<=22", "");
  handsomeTH1(hCand,1);
  handsomeTH1(hSig,2);
  handsomeTH1(hBkg,4);

  TCanvas* cPurity = new TCanvas("cpurity","",500,500);
  fitResult fitr = doFit ( hSig, hBkg, hCand, 0.005, 0.025);
  drawText(Form("Purity : %.2f", (float)fitr.purity010), 0.5680963,0.529118);
  claverCanvasSaving(cPurity,canvasName);
  
  TCanvas* c1 = new TCanvas("c1","",100,100);
  
  delete tgj;
  delete tgjMC;
  delete hSig;
  delete hBkg;
  delete hCand;
  
  return fitr;
  
  
}


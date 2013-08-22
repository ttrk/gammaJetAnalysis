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
#include "commonUtility.h"
#include <TRandom3.h>
#include "../CutAndBinCollection2012.h"
#include "corrFunctionJetTrk.h"

GjSpectra* nullGj;

void gammaTrkSingle(     GjSpectra* gjSpec_=nullGj,
			 multiTreeUtil* tObj[3]=0,
			 corrFunctionTrk* corr_=0,
			 float purity=0,
			 sampleType collision_=kHIDATA,
			 TString var_ = "",
			 TCut cut_ ="",
			 TString theWeight="",
			 TCut phoCandCut_="",
			 TCut phoDecayCut_="",
			 TH1D* hTemplate_ =0,
			 TString outName="");

fitResult getPurity(TString fname="", sampleType collision=kHIDATA, TCut candEvtCut = "", TCut sbEvtCut="", TString ccanvasName="",float photonPtThr=60, float photonPtThrUp=9999);


void gammaJetHistProducer(sampleType collision = kPADATA, float photonPtThr=60, float photonPtThrUp=9999, float jetPtThr=30, int icent =1) {
  TH1::SetDefaultSumw2();
  
  TString stringSampleType = getSampleName(collision); "";
  
  TDatime* date = new TDatime();
  TString  outName=  Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr%d_%d.root",stringSampleType.Data(),(int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr,  date->GetDate());
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
  if ( collision == kHIMC)              fname = fnameHIMC_AllQcdPho30; 
  else if ( collision == kHIDATA)       fname = fnameDATAPbPbAk3;
  else if ( collision == kPPMC)         fname = fnameMCppAk3;
  else if ( collision == kPPDATA)         fname = fnameDATAppAk3;
  else if ( collision == kPADATA)         fname = fnameDATApPbAk3;
  else if ( collision == kPAMC)      {
    if       (photonPtThr <45 )
      fname = fnamePAMC_AllQcdPho30;
    else if  (photonPtThr <55 )
      fname = fnamePAMC_AllQcdPho30;
    else if  (photonPtThr <65 ) 
      fname = fnamePAMC_AllQcdPho50;
    else
      fname = fnamePAMC_AllQcdPho50;
 
  }   
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  tgj->addFile(fname,  "tgj",  evtSeltCut,  1);
  tgj->AddFriend("yJet");

  // get purity with the current jet cut ! 
  float purity(0);
  
  TString canvasName = Form("gifs/purity_%s_output_icent%d_photonPtThr%d-%d_jetPtThr%d", stringSampleType.Data(),  (int)icent, (int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr);
  
  if ( (collision==kPPDATA) && (photonPtThr < 50 ) ) {
    purity = 0.86 ;   
    cout << " !!!!!!!" << endl << endl << " purity is set as  0.86 for this bin because we don't have pp MC low pt sample " << endl;
    cout << endl << endl << endl << " !!!!!!" << endl;
  }
  else if ( (collision==kHIDATA)||(collision==kPPDATA)||(collision==kPADATA) )  {
    fitResult fitr = getPurity(fname, collision, evtSeltCut, sbSeltCut, canvasName, photonPtThr, photonPtThrUp);
    purity = fitr.purity010;
  }
  else  {
    purity = 1;  
    cout << " MC purity = 1" << endl;
  }
  

  GjSpectra* gSpec = new GjSpectra();
  gSpec->init(Form("pho%.0f_%.0f", (float)photonPtThr, (float)photonPtThrUp));
  tgj->Draw2(gSpec->hPtPhoCand,  "photonEt", phoCandCut, "")  ;
  tgj->Draw2(gSpec->hPtPhoDecay, "photonEt", phoDecayCut, "") ;
  
  
  // Objects
  multiTreeUtil* tObj[3];
  tObj[kTrkRaw] = new multiTreeUtil();
  tObj[kTrkBkg] = new multiTreeUtil();
  
  tObj[kTrkRaw]->addFile(fname,  "yJet",  evtSeltCut,  1);
  tObj[kTrkBkg]->addFile(fname,  "mJet",  evtSeltCut,  1);
  
  tObj[kTrkRaw]->AddFriend("tgj");
  tObj[kTrkBkg]->AddFriend("tgj");
  TCut jetCut     =  Form("abs(eta)<%f && pt>%f", (float)cutjetEta, (float)jetPtThr );
  TCut jetCutDphi =  jetCut && (TCut)(Form("abs(dphi)>%f",(float)awayRange));
  TCut genJetCut     =  Form("abs(jtEta)<%f && jtPt>%f", (float)cutjetEta, (float)jetPtThr );
  TCut genJetCutDphi =  jetCut && (TCut)(Form("abs(refDphi)>%f",(float)awayRange));
  
  
  TString jetWeight = "";
  
  TH1D* hJetDphi = new TH1D(Form("jetDphi_icent%d",icent),";#Delta#phi_{Jet,#gamma} ;dN/d#Delta#phi",20,0,3.141592);
  corrFunctionTrk* cJetDphi = new corrFunctionTrk();
  TString varJetDphi         = Form("dphi");

  gammaTrkSingle( gSpec,  tObj, cJetDphi,  purity, 
		  collision, varJetDphi, jetCut, jetWeight,
		  phoCandCut, phoDecayCut,  hJetDphi, outName);
  
  TH1D* hJetPt = new TH1D(Form("jetPt_icent%d",icent),";Jet p_{T} (GeV) ;dN/dp_{T} (GeV^{-1})",40,30,230);
  corrFunctionTrk* cJetPt = new corrFunctionTrk();
  TString varJetPt         = Form("pt");
  
  gammaTrkSingle( gSpec,  tObj, cJetPt,  purity, 
		  collision, varJetPt, jetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hJetPt, outName);
  
  
  
  TH1D* hGenJetPt = (TH1D*)hJetPt->Clone(Form("genJetPt_icent%d",icent));
  corrFunctionTrk* cGenJetPt = new corrFunctionTrk();
  TString varGenJetPt         = Form("refPt");
  
  gammaTrkSingle( gSpec,  tObj, cJetPt,  purity, 
		  collision, varGenJetPt, genJetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hGenJetPt, outName);
  
  
  TH1D* hDjetPt = new TH1D(Form("dpt_icent%d",icent),";p_{T}^{#gamma} - p_{T}^{Jet} (GeV) ;dN/dp_{T} (GeV^{-1})",30,-150,150);
  corrFunctionTrk* cDjetPt = new corrFunctionTrk();
  TString varJetDpt         = Form("pt - photonEt");
  gammaTrkSingle( gSpec,  tObj, cDjetPt,  purity, 
		  collision, varJetDpt, jetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hDjetPt, outName);
  
  
  TH1D* hJetXjg = new TH1D(Form("xjg_icent%d",icent),";p_{T}^{Jet}/p_{T}^{#gamma}  ; ",16,0,2);
  corrFunctionTrk* cJetXjg = new corrFunctionTrk();
  TString varJetXjg         = Form("pt/photonEt");
  
  gammaTrkSingle( gSpec,  tObj, cJetXjg,  purity, 
		  collision, varJetXjg, jetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hJetXjg, outName);


  TH1D* hGenJetXjg = new TH1D(Form("xjg_genJet_icent%d",icent),";Gen Jet p_{T}^{Jet}/p_{T}^{#gamma}  ; ",16,0,2);
  corrFunctionTrk* cGenJetXjg = new corrFunctionTrk();
  TString varGenJetXjg         = Form("refPt/photonEt");
  gammaTrkSingle( gSpec,  tObj, cGenJetXjg,  purity, 
		  collision, varGenJetXjg, genJetCutDphi , jetWeight,
		  phoCandCut, phoDecayCut,  hGenJetXjg, outName);

  TH1D* hGenPhotonXjg = new TH1D(Form("xjg_genPho_icent%d",icent),";jet p_{T}^{Jet}/p_{T}^{#gamma}  ; ",16,0,2);
  corrFunctionTrk* cGenPhotonXjg = new corrFunctionTrk();
  TString varGenPhotonXjg         = Form("pt/genPhotonEt");
  gammaTrkSingle( gSpec,  tObj, cGenPhotonXjg,  purity, 
		  collision, varGenPhotonXjg, jetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hGenPhotonXjg, outName);

  TH1D* hGenPhoGenJetXjg = new TH1D(Form("xjg_genPho_genJet_icent%d",icent),";jet p_{T}^{Jet}/p_{T}^{#gamma}  ; ",16,0,2);
  corrFunctionTrk* cGenPhoGenJetXjg = new corrFunctionTrk();
  TString varGenPhoGenJetXjg         = Form("refPt/genPhotonEt");
  gammaTrkSingle( gSpec,  tObj, cGenPhoGenJetXjg,  purity, 
		  collision, varGenPhoGenJetXjg, genJetCutDphi, jetWeight,
		  phoCandCut, phoDecayCut,  hGenPhoGenJetXjg, outName);
  
  
  /*      Eta distribution
	  TH1D* hEtaJg = new TH1D(Form("etaJg_icent%d",icent),";#eta_{J,#gamma} ; ",160,-3,3);
	  corrFunctionTrk* cEtaJg = new corrFunctionTrk();
	  TString varEtaJg         = Form("(photonEta+eta)/2.");
	  
	  gammaTrkSingle( gSpec,  tObj, cEtaJg,  purity, 
	  collision, varEtaJg, jetCutDphi, jetWeight,
	  phoCandCut, phoDecayCut,  hEtaJg, outName);
	  
	  TH1D* hEtaJet = new TH1D(Form("etaJet_icent%d",icent),";#eta_{Jet} ; ",160,-3,3);
	  corrFunctionTrk* cEtaJet = new corrFunctionTrk();
	  TString varEtaJet         = Form("eta");
	  
	  gammaTrkSingle( gSpec,  tObj, cEtaJet,  purity, 
	  collision, varEtaJet, jetCutDphi, jetWeight,
	  phoCandCut, phoDecayCut,  hEtaJet, outName);
	  
	  TH1D* hEtaPhoton = new TH1D(Form("etaPhoton_icent%d",icent),";#eta_{#gamma} ; ",160,-3,3);
	  corrFunctionTrk* cEtaPhoton = new corrFunctionTrk();
	  TString varEtaPhoton         = Form("photonEta");
	  
	  gammaTrkSingle( gSpec,  tObj, cEtaPhoton,  purity, 
	  collision, varEtaPhoton, jetCutDphi, jetWeight,
	  phoCandCut, phoDecayCut,  hEtaPhoton, outName);
		  
  */
  
}


void gammaTrkSingle(     GjSpectra* gSpec,  multiTreeUtil* tObj[3],   corrFunctionTrk* corr, 
			 float purity,       sampleType collision, 	     TString var,     
			 TCut cut, 		TString theWeight,	 TCut phoCandCut,   TCut phoDecayCut,
			 TH1D* hTemplate,  TString outfName)
{
  TH1::SetDefaultSumw2();
  corr->init(gSpec, collision, purity, hTemplate);
  cout << "Filling raw jets" << endl;
  tObj[kTrkRaw]->Draw2(corr->Func[kPhoCand][kTrkRaw],  var,  phoCandCut  && cut, theWeight);
  if ( tObj[kTrkBkg]!=0)   {
  cout << "Filling mixed jets" << endl;
    tObj[kTrkBkg]->Draw2(corr->Func[kPhoCand][kTrkBkg],  var,  phoCandCut  && cut, theWeight);
  }
  
  if ( (collision==kHIDATA) || (collision==kPPDATA) || (collision==kPADATA) ) {
    cout << "Filling decay photon-jet correlation" << endl;
    tObj[kTrkRaw]->Draw2(corr->Func[kPhoDecay][kTrkRaw], var, phoDecayCut && cut,  theWeight);
    if (tObj[kTrkBkg]!=0)   {
      cout << "Filling decay photon- mixed jet correlation" << endl;
      tObj[kTrkBkg]->Draw2(corr->Func[kPhoDecay][kTrkBkg], var, phoDecayCut && cut,  theWeight);
    }
  }
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkRaw]); 
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkBkg]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkRaw]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkBkg]);
  
  corr->calCorr();
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



fitResult getPurity(TString fname, sampleType collision, TCut evtSeltCut, TCut sbEvtCut, TString canvasName, float photonPtThr, float photonPtThrUp) {
  double purity(0);
  
  multiTreeUtil* tgj = new multiTreeUtil();
  multiTreeUtil* tgjMC = new multiTreeUtil();
  cout <<" 1 " << endl;
  tgj->addFile(fname,  "tgj",  "",  1);
  cout <<" 2 " << endl;
  tgj->AddFriend("yJet");
  if   (collision==kPPDATA)
    tgjMC->addFile(fnameMCppAk3, "tgj", "", 1);
  else if (collision==kHIDATA)  {
    if       (photonPtThr <65 )
      tgjMC->addFile(fnameHIMC_AllQcdPho30, "tgj", "", 1);
    else if  (photonPtThr <85 )
      tgjMC->addFile(fnameHIMC_AllQcdPho50, "tgj", "", 1);
    else 
      tgjMC->addFile(fnameHIMC_AllQcdPho80, "tgj", "", 1);
  }
  else if (collision==kPADATA)     {
    if       (photonPtThr <65 )
      tgjMC->addFile(fnamePAMC_AllQcdPho30, "tgj", "", 1);
    else if  (photonPtThr <85 )
      tgjMC->addFile(fnamePAMC_AllQcdPho50, "tgj", "", 1);
    else
      tgjMC->addFile(fnamePAMC_AllQcdPho50, "tgj", "", 1);
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
  tgjMC->Draw2( hSig, "sigmaIetaIeta", evtSeltCut && "genIso<5 && abs(genMomId)<=22", "");
  handsomeTH1(hCand,1);
  handsomeTH1(hSig,2);
  handsomeTH1(hBkg,4);

  TCanvas* cPurity = new TCanvas("cpurity","",500,500);
  fitResult  fitr = doFit ( hSig, hBkg, hCand, 0.005, 0.025);
  drawText(Form("Purity : %.2f", (float)fitr.purity010), 0.5680963,0.429118);
  drawText(Form("p_{T}^{#gamma}: %d-%d GeV", (int)photonPtThr, (int)photonPtThrUp), 0.568,0.529118);
  cleverCanvasSaving(cPurity,canvasName);
  
  TCanvas* c1 = new TCanvas("c1","",100,100);
  
  
  delete tgj;
  delete tgjMC;
  delete hSig;
  delete hBkg;
  delete hCand;
  
  return fitr;
  
  
}


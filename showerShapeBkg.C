///////////////////////////////////////////////////////////////////                                
// gammaJetHistProducer.C                                        //
// Creator : Yongsun Kim (MIT), jazzitup@mit.edu                 //                                                 
// Function : Studies shower shape comparison of the meson-decay //
//            photons in various isolation condition             //
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
#include "../hiForestV3/hiForest.h"
#include "CutAndBinCollection2012.h"

void showerShapeBkg(  sampleType collision = kPPMC)
{
  TH1::SetDefaultSumw2();
  
  TCut bkgPhoCut = "( (abs(genMomId)>22) || (genIso>5) ) && (hovere<0.1)";

  multiTreeUtil* tgj = new multiTreeUtil();
  if ( collision == kPPMC ) {
    tgj->addFile(fnamePPMC_emDijet30to50,   "tgj", bkgPhoCut, wPPMC_emDijet30to50);
    tgj->addFile(fnamePPMC_emDijet50to80,   "tgj", bkgPhoCut, wPPMC_emDijet50to80);
    tgj->addFile(fnamePPMC_emDijet80to120,  "tgj", bkgPhoCut, wPPMC_emDijet80to120);
    tgj->addFile(fnamePPMC_emDijet120to9999,"tgj", bkgPhoCut, wPPMC_emDijet120to9999);
  }
  else { 
    cout << " pA and PbPb MC samples are not ready yet" << endl;
  }


  TH1D* hPtHat = new TH1D("hpthat",";pt hat (GeV);",200,0,200);
  handsomeTH1(hPtHat,1);
  TCanvas* c1 = new TCanvas("c1","",500,500);
  tgj->Draw3(hPtHat,"photonEt",bkgPhoCut,"");
  gPad->SetLogy();

  TCanvas* c2 = new TCanvas("c1","",1100,600);
  makeMultiPanelCanvas(c2,nPtBinPa,2,0.0,0.0,0.2,0.15,0.02);
  c2->cd(1);
  TCut ppIsoCut  = "(ecalIso < 4.2)  &&  (hcalIso < 2.2)  &&  (trackIso < 2)";
  TCut hiIsoCut  = "sumIso < 1";
  TCut ppSbCut   = "(ecalIso < 4.2)  &&  (hcalIso < 2.2)  &&  ( (trackIso>2) && (trackIso<4) )";
  TCut hiSbCut   = "(sumIso > 10) && (sumIso<20)";

  TH1D* sii[5][nPtBinPa+1]; 
  for ( int ipt = 1 ; ipt<=nPtBinPa ; ipt++) {
    for ( int iiso = 1 ; iiso<=4 ; iiso++) {
      sii[iiso][ipt] = new TH1D(Form("sigmaIetaIeta_iso%d_ipt%d",iiso,ipt), ";#sigma_{#eta#eta};Entries", 25,0,0.025);
      handsomeTH1(sii[iiso][ipt],1);
    }
    TCut phoPtCut = Form ( "photonEt>=%f && photonEt<%f", (float)ptBinPa[ipt-1], (float)ptBinPa[ipt]);
    tgj->Draw2(sii[1][ipt], "sigmaIetaIeta",ppIsoCut && phoPtCut, "");
    tgj->Draw2(sii[2][ipt], "sigmaIetaIeta",hiIsoCut && phoPtCut, "");
    tgj->Draw2(sii[3][ipt], "sigmaIetaIeta",ppSbCut && phoPtCut, "");
    tgj->Draw2(sii[4][ipt], "sigmaIetaIeta",hiSbCut && phoPtCut, "");
    scaleInt(sii[1][ipt]);
    scaleInt(sii[2][ipt]);
    scaleInt(sii[3][ipt]);
    scaleInt(sii[4][ipt]);
  }  

  for ( int ipt = 1 ; ipt<=nPtBinPa ; ipt++) {
    c2->cd(ipt);
    TH1D* sii_A = sii[1][ipt];
    TH1D* sii_B = sii[4][ipt];
    handsomeTH1(sii_B,2);
    sii_A->Draw();
    sii_B->Draw("same");
    c2->cd(ipt+nPtBinPa);
    TH1D* hRatio = (TH1D*)sii_A->Clone(Form("hRatio_%s",sii_A->GetName()));
    hRatio->Divide(sii_B);
    hRatio->SetAxisRange(0,4,"Y");
    hRatio->Draw();
    hRatio->Fit("pol1");
    jumSun(0,1,0.025,1);
  }
}


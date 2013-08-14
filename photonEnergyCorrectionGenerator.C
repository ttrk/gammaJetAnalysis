#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void photonEnergyCorrectionGenerator(sampleType collision = kPAMC) {
  TH1::SetDefaultSumw2(); 

  // pA collisions
  const int nCentBin = nCentBinPa;
  double* centBin = centBinPa;
  const int nPtBin = 5;
  double ptBin[nPtBin+1] = {40,50,60,80,120,150};
  
  multiTreeUtil* tgj = new multiTreeUtil();
  if (collision == kPAMC)  { 
    tgj->addFile("forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton30_forestv78.root",  
		 "tgj",  "yPhotonTree.ptHat<50",                          1);
    tgj->addFile("forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton50_forestv78.root",  
		 "tgj",  "yPhotonTree.ptHat>50 && yPhotonTree.ptHat<80",  0.486);
    tgj->addFile("forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton80_forestv78.root",  
		 "tgj",  "yPhotonTree.ptHat>80 && yPhotonTree.ptHat<120", 0.149);
    tgj->addFile("forestFiles/yskimmedFiles/yskim_PA2013_pyquen_allQCDPhoton80_forestv78.root",  
		 "tgj",  "yPhotonTree.ptHat>120",                         0.0349);
  }
  tgj->AddFriend("yPhotonTree");
  
 
  TCanvas* c1 = new TCanvas("c1","",500,500);
  TH1D* hPtHat = new TH1D("hpthat",";p_{T};",200,0,200);
  tgj->Draw2(hPtHat,"photonEt","","");
  hPtHat->Draw();
  
  TCanvas* c2 = new TCanvas("c2","",1200,800);
  makeMultiPanelCanvas(c2,nPtBin,nCentBin,0.0,0.0,0.2,0.15,0.02);
  TH1D* hScale[5][6]; // [centrality][pt] 
  TH1D* hTable[5]; // [centrality]
  for (int icent=1 ; icent<=nCentBin ; icent++) {
    hTable[icent] = new TH1D(Form("hTable_icent%d",icent),";p_{T}^{Reco};scale",nPtBin,ptBin);
    for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
      c2->cd(ipt + nPtBin * (icent-1) );
      hScale[icent][ipt]= new TH1D(Form("hScale_icent%d_ipt%d",icent,ipt),";p_{T}^{Reco}/p_{T}^{GEN};",100,0.8,1.2);
      handsomeTH1(hScale[icent][ipt],1);
      
      TCut r9Cut     = Form("r9>0.94");
      TCut ptPhoCut  = Form("photonEt>%d && photonEt<%d", (int)ptBin[ipt-1], (int)ptBin[ipt]);
      TCut centralityCut;
      if ( collision == kPAMC) 
	centralityCut = Form( "hf4Sum > %f && hf4Sum <= %f", (float)centBinPa[icent-1], (float)centBinPa[icent]);
      
      tgj->Draw2(hScale[icent][ipt],"photonEt/genPhotonEt", ptPhoCut && centralityCut && r9Cut,"");
      TF1* hFit = cleverGaus(hScale[icent][ipt],Form("fitTitle_icent%d_ipt%d",icent,ipt),2);

      hScale[icent][ipt]->Draw();
      hFit->Draw("same");
      gPad->SetLogy();
      
      double theMean  = hFit->GetParameter(1);
      double theSigma = hFit->GetParameter(2);
      hTable[icent]->SetBinContent(ipt, theMean);
      hTable[icent]->SetBinError(ipt, theSigma);
    }
  }
  TCanvas* c3 = new TCanvas("c3","",500,500);
  for (int icent=1 ; icent<=nCentBin ; icent++) {
    handsomeTH1( hTable[icent], ycolor[icent] );
    hTable[icent]->SetAxisRange(0.95,1.05,"Y");
    if (icent ==1 )    hTable[icent]->Draw();
    else hTable[icent]->Draw("same");
  } 
  //  hTable[1]->Fit("pol1");
}

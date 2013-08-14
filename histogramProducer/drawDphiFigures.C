#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawDphiFigures() {
  
  const int nCentBin = nCentBinPa;
  double* centBin = centBinPa;
  const int nPtBin = nPtBinPa; 
  double* ptBin = ptBinPa;
  
  TH1D* hdphi[7][5][6]; // [Collision][centrality][pt]
  TH1D* hdphiWidth[7][5]; // [Collision][centrality]
  TFile* histFile[7][6];  // [Collision][pt]
  for (int ipt=1 ; ipt<=nPtBin ; ipt++) {  
    for (int icoll=0 ; icoll<6 ; icoll++) {  
      TString sampleName = getSampleName( icoll ) ;
      histFile[icoll][ipt] = new TFile(Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130812.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]) );
      if ( histFile[icoll][ipt]->IsZombie()  == false ) {
	for (int icent=1 ; icent<=nCentBin ; icent++) {  
	  hdphi [icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetDphi_icent%d_final",  icent)) ;
	}
      } 
 
    }
  }
  
  for (int icoll=0 ; icoll<6 ; icoll++) {
    for (int icent=1 ; icent<=nCentBin ; icent++) {
      hdphiWidth[icoll][icent] = new TH1D("hdphiWidth_ipt%d_icent%d",";p_{T}^{#gamma}; #sigma(#Delta#phi_{J#gamma})",nPtBin,ptBinPaDraw);
    }
  }
  
  // pPb
  TCanvas* c1 = new TCanvas("c1","",1200,800);
  makeMultiPanelCanvas(c1,nPtBin,nCentBin,0.0,0.0,0.2,0.15,0.02);
  
  TCanvas* c2 = new TCanvas("c2","",1200,800);
  makeMultiPanelCanvas(c2,nPtBin,nCentBin,0.0,0.0,0.2,0.15,0.02);
  
  TString fitFunc = "(TMath::Pi()/20.0)*exp(-(TMath::Pi()-x)/[0])/([0]*(1-exp(-TMath::Pi()/[0])))";
  for (int icent=1;icent<=nCentBin;icent++) {
    for (int ipt=1;ipt<=nPtBin ;ipt++) {
      for (int icoll=4;icoll<=5; icoll++) {
	if ( icoll == 4)  // pPb data
	  c1->cd(ipt + nPtBin * (icent-1) );
	else if ( icoll ==5 ) // pPb mc
	  c2->cd(ipt + nPtBin * (icent-1) );
	
	hdphi[icoll][icent][ipt]->Scale(1./hdphi[icoll][icent][ipt]->Integral("w"));
	TF1 *fdphi = new TF1("fdphi",fitFunc.Data(),2.0*TMath::Pi()/3.0,TMath::Pi());
	fdphi->SetParName(0,"width");
	fdphi->SetParameter("width",0.3);
	float fitxmin=3.1415926*2./3;
	//  hdphi[kppdata13][7]->Fit("fdphi","0llm","",fitxmin,3.1415926);                                                      
	hdphi[icoll][icent][ipt]->Fit("fdphi","0","",fitxmin,3.1415926);
	
	fdphi->SetLineWidth(2);
	fdphi->SetLineStyle(7);
	fdphi->SetLineColor(1);
	hdphi[icoll][icent][ipt]->SetAxisRange(1.00001e-3,1,"Y");
	hdphi[icoll][icent][ipt]->SetStats(0);
	hdphi[icoll][icent][ipt]->SetXTitle("#Delta#phi_{J#gamma}");
	hdphi[icoll][icent][ipt]->SetYTitle("Normalized Entries");
	hdphi[icoll][icent][ipt]->Draw("");
	fdphi->DrawCopy("same");
	gPad->SetLogy();


	float dphiWidth1 = fdphi->GetParameter(0) ;
	float dphiWidtherr1 = fdphi->GetParError(0);
	hdphiWidth[icoll][icent]->SetBinContent(ipt, dphiWidth1);
	hdphiWidth[icoll][icent]->SetBinError  (ipt, dphiWidtherr1);
      }
    }
  }

  TCanvas* c3 = new TCanvas("c3","",900,350);
  makeMultiPanelCanvas(c3,nCentBin,1,0.0,0.0,0.2,0.15,0.02);
  for (int icent=1 ; icent<=nCentBin ; icent++) {
    c3->cd(icent);
    handsomeTH1(hdphiWidth[kPAMC][icent],1);
    hdphiWidth[kPAMC][icent]->SetMarkerStyle(24);
    handsomeTH1(hdphiWidth[kPADATA][icent],1);
    hdphiWidth[kPAMC][icent]->SetAxisRange(0,0.5,"Y");
    hdphiWidth[kPAMC][icent]->Draw();
    hdphiWidth[kPADATA][icent]->Draw("same");
  }
}

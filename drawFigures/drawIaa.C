#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawIaa( bool saveFigures=true) {

    const int nPtBin = 4;
    double ptBin[nPtBin+1] = {40, 50,60,80,9999};
    double ptBinPaDraw[nPtBin+1] = { 40.5 ,49.5, 58.5,  76.5,  123. } ;
    // double AvePtBin[nPtBin+1] = { 45, 54.1479, 67.4204, 99.6956, 9999};
    
    const int nCentBinHI = 2;
    const int centBinHI[nCentBinHI +1] = {-1, 10030, 13099}; 

    TH1D* hJetPt[7][10][6]; // [Collision][centrality][pt]
    TH1D* hIaa[10][6]; // [centrality][pt]
    
    for (int icent=1 ; icent<= 10 ; icent++) {
      for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
	
	hIaa[icent][ipt] = NULL;
	for (int icoll=0 ; icoll<6  ; icoll++) {
	  hJetPt[icoll][icent][ipt] = NULL;
	}
	
      }
    }
    
    TFile* histFile[7][6];  // [Collision][pt]                                                                                          
    for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
      for (int icoll=0 ; icoll<6 ; icoll++) {
	TString sampleName = getSampleName( icoll ) ;
	//		char* fname =  Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130924.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
		char* fname =  Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130924.root",sampleName.Data(), (int)ptBin[ipt-1], 9999);
	histFile[icoll][ipt] = new TFile(fname) ;
	cout << " Reading file : " << fname << endl;
	if ( histFile[icoll][ipt]->IsZombie()  == false ) {
	  cout << " Success." << endl;
	  if ( (icoll == kPPDATA) || (icoll == kPPMC) )   {  //  PP
	    int icent = 7 ; 
	    hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPtForIaa_icent%d_final", icent)) ;
	    cout << " Getting histogram : " << Form("jetPt_icent%d_final", icent) << endl;
	    //	    hJetPt[icoll][7][ipt]->Rebin(10);
	    // hJetPt[icoll][7][ipt]->Scale(1./10);
	    
	  }
	  if ( ( icoll == kHIDATA) ||  (icoll == kHIMC) ) { // PbPb
	    for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
	      hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPtForIaa_icent%d_final", centBinHI[icent] ) );
	      cout << " Getting histogram : " << Form("jetPt_icent%d_final", centBinHI[icent] ) << endl;
	      //	      hJetPt[icoll][icent][ipt]->Rebin(10);
	      //hJetPt[icoll][icent][ipt]->Scale(1/10.);
	    }
	  }
	}
	else  
	  cout << " no such file " << endl;
      }
    }

    // Calculation of IAA
    for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
      for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
	hIaa[icent][ipt] = (TH1D*)hJetPt[kHIDATA][icent][ipt]->Clone(Form("iaa_%s",hJetPt[kHIDATA][icent][ipt]->GetName()));
	hIaa[icent][ipt]->Divide(hJetPt[kPPDATA][7][ipt]);
      }
    }
    
    
    TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",200,10,300);
    
    TCanvas* c2 = new TCanvas("c2","",1000,450);
    makeMultiPanelCanvas(c2,nPtBin,2,0.0,0.0,0.2,0.15,0.02);
    for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {

        c2->cd(ipt);

        // draw pp
        hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
        hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N^{#gamma}}");
        hTempPt->SetAxisRange(30,200,"X");
	//        hTempPt->SetAxisRange(0,0.025,"Y");
	hTempPt->SetAxisRange(0.00007,0.11,"Y");
        handsomeTH1(hTempPt,0);
        hTempPt->DrawCopy();
	gPad->SetLogy();
	

        handsomeTH1(hJetPt[kPPDATA][7][ipt], 1);
        hJetPt[kPPDATA][7][ipt]->SetMarkerStyle(24);
	hJetPt[kPPDATA][7][ipt]->Draw("same");

        // draw pbpb 
        for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
            handsomeTH1(hJetPt[kHIDATA][icent][ipt],kRed);
	    if ( icent == 2 ) hJetPt[kHIDATA][icent][ipt]->SetMarkerStyle(24);
	    hJetPt[kHIDATA][icent][ipt]->Draw("same");
        }
       
        double dx1=0.15;

	drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);
	/*
	  if ( ipt == nPtBin ) 
	  drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);
	  else
	  drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);
	*/
	
        onSun(30,0,200,0);

        c2->cd(ipt + nPtBin);
	hTempPt->SetAxisRange(0,2.5,"Y");
	hTempPt->SetYTitle("Jet I_{AA}");
	handsomeTH1(hTempPt,0);
        hTempPt->DrawCopy();
                                                                                                               
        for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
	  handsomeTH1(hIaa[icent][ipt],kRed);
	  if ( icent == 2 )         hIaa[icent][ipt]->SetMarkerStyle(24);
	  // if ( icent == 1 )   
	    hIaa[icent][ipt]->Draw("same");
	  jumSun(30,1,200,1);
        }
	
	
	
	
    }
    

    c2->cd(1);
    
    TLegend *l2 = new TLegend(0.5933981,0.3877892,0.9981436,0.7857262,NULL,"brNDC");
    easyLeg(l2,"2.76TeV");
    l2->AddEntry(hJetPt[kPPDATA][7][1],"pp", "p");
    l2->AddEntry(hJetPt[kHIDATA][2][1],"PbPb 30-100%", "p");
    l2->AddEntry(hJetPt[kHIDATA][1][1],"PbPb 0-30%", "p");
    l2->Draw();
    if (saveFigures)   c2->SaveAs("figures/pT_dependence_IAA_figure1.pdf");
    if (saveFigures)   c2->SaveAs("figures/pT_dependence_IAA_figure1.gif");

    
    
}

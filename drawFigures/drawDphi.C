#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>
#include <TStyle.h>

void drawDphi(int xNorm = 1) { 

    const int nPt = 5;
    const int nFile = 8; 
    double AvePtBin[nPt+1] = {45.0, 55.0, 70.0, 100.0};
    double PtBinPa[nPt+1] = {40,50,60,80,9999};

    //  TH1D* hxjg[7][1000][20]; // [species][centrality][pt_dependence]
    TH1D* hdphi[7][1000][20];

    valPair meanDphi[7][1000][20];

    TGraphAsymmErrors* gdphi[7][20]; //[species][ptdependence]
    for (int j=1;j<=nFile;j++){
        for (int i=1;i<=7;i++) {   
            gdphi[i][j] = new TGraphAsymmErrors();
            gdphi[i][j]->SetName(Form("gdphi_%d_%d",i,j));
        }   
    }
    TFile* fff[7][1000][20];
    double rError[20];
    int icent =1 ;
    int iSpecies =kPADATA ;
    int iglb = icent + iSpecies*50.;

    fff[iSpecies][iglb][1] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr40_to_50_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][2] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr50_to_60_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][3] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr60_to_80_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][4] = new TFile("ffFiles/photonTrackCorr_ppbDATA_output_photonPtThr80_to_9999_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][5] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr40_to_50_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][6] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr50_to_60_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][7] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr60_to_80_jetPtThr30_20130906.root");
    fff[iSpecies][iglb][8] = new TFile("ffFiles/photonTrackCorr_ppbMC_output_photonPtThr80_to_9999_jetPtThr30_20130906.root");

    for(int j = 1; j <= nFile ; j++){
        hdphi[iSpecies][iglb][j] = (TH1D*)fff[iSpecies][iglb][j]->Get("jetDphi_icent1_final");
    }

    TCanvas* cDphi = new TCanvas("cDphi","",1200,350);
    makeMultiPanelCanvas(cDphi,4,1,0.0,0.0,0.2,0.15,0.02);

    for ( int j = 1 ; j<=nFile ; j++){
        int icent=1;
        int iSpecies = kPADATA;
        int iglb = icent + iSpecies*50.;
           hdphi[iSpecies][iglb][j]->SetXTitle("#Delta#phi_{J,#gamma}");
            hdphi[iSpecies][iglb][j]->Scale(1./hdphi[iSpecies][iglb][j]->Integral("width"));
            hdphi[iSpecies][iglb][j]->SetAxisRange(0.01,30,"Y");
            hdphi[iSpecies][iglb][j]->SetMarkerStyle(20);
            handsomeTH1(hdphi[iSpecies][iglb][j],2);
	    if(j<=4){
	      cDphi->cd(j); 
	      
	      hdphi[iSpecies][iglb][j]->Draw();
	      
	      gPad->SetLogy();
	      float dx1=0.15;
	      if ( j == 4 || j == 8 )
                drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)PtBinPa[j-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
	      else
                drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)PtBinPa[j-1], (int)PtBinPa[j]), 0.12+dx1,0.85,1,15);//yeonju 130823
	    } else {
	      cDphi->cd(j-4); 
	      handsomeTH1(hdphi[iSpecies][iglb][j],2);
	      hdphi[iSpecies][iglb][j]->SetMarkerStyle(24);
	      hdphi[iSpecies][iglb][j]->Draw("same");
	    }
    }
    
    cDphi->cd(1); 
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"5.02TeV (MinBias)");
    l1->AddEntry(hdphi[iSpecies][iglb][1], "p+Pb DATA", "p");
    l1->AddEntry(hdphi[iSpecies][iglb][5], "p+Pb MC", "p");
    l1->Draw();
    cDphi->Update();
}


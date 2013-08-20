#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawPtDependence(bool drawPbPb=1, int xNorm = 0) {
  
  const int nPtBin = 4;
  double ptBin[nPtBin+1] = {40, 50,60,80,9999}; 
  double AvePtBin[nPtBin+1] = { 45, 54.1479, 67.4204, 99.6956, 9999};
  
  TH1D* hxjg[7][1000]; // [species][centrality] 
  TH1D* hxjgNorm[7][1000];
  TH1D* hdpt[7][1000];
  TH1D* hdptNorm[7][1000];
  TH1D* hdphi[7][1000];
  
  valPair meanX[7][1000];
  valPair meanDpt[7][1000];
  valPair rjg[7][1000];
  TGraphAsymmErrors* gr[7];
  TGraphAsymmErrors* gx[7];
  TGraphAsymmErrors* gdpt[7];
  for (int i=0;i<7;i++) {  
    gr[i] = new TGraphAsymmErrors();
    gr[i]->SetName(Form("gr_%d",i));
    gx[i] = new TGraphAsymmErrors();
    gx[i]->SetName(Form("gx_%d",i));
    gdpt[i] = new TGraphAsymmErrors();
    gdpt[i]->SetName(Form("gdpt_%d",i));
  }
  TFile* fff[7][1000];
  
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) { 
    for ( int iSpecies=0 ; iSpecies<=5 ; iSpecies++){ 
      if (  (iSpecies!=kPPDATA)&&(iSpecies!=kHIDATA) ) 
	continue;
      
      int iglb = ipt + iSpecies*50.;
      int icent = -1;
      
      if ( iSpecies == kPPDATA) { 
        icent = 7;
	fff[iSpecies][iglb] = new TFile(Form("ffFiles/photonTrackCorr_ppDATA_output_photonPtThr%d_to_%d_jetPtThr30_20130818.root",(int)ptBin[ipt],(int)ptBin[ipt+1]));
      }
      if ( iSpecies == kHIDATA) { 
	//	icent = 10040;
	//	icent = 14099;
	icent = 10020;
	// 	icent = 12050;
	fff[iSpecies][iglb] = new TFile(Form("ffFiles/photonTrackCorr_pbpbDATA_output_photonPtThr%d_to_%d_jetPtThr30_20130818.root",(int)ptBin[ipt],(int)ptBin[ipt+1]));
      }
      
      hdphi[iSpecies][iglb] = (TH1D*)fff[iSpecies][iglb]->Get(Form("jetDphi_icent%d_final",icent));
      
      hxjg[iSpecies][iglb] = (TH1D*)fff[iSpecies][iglb]->Get(Form("xjg_icent%d_final",icent));
      hxjgNorm[iSpecies][iglb] = (TH1D*)hxjg[iSpecies][iglb]->Clone(Form("norm_%s",hxjg[iSpecies][iglb]->GetName()) );
      meanX[iSpecies][iglb].val = hxjg[iSpecies][iglb]->GetMean();
      meanX[iSpecies][iglb].err = hxjg[iSpecies][iglb]->GetMeanError();
      gx[iSpecies]->SetPoint     (ipt+1, AvePtBin[ipt], meanX[iSpecies][iglb].val);
      gx[iSpecies]->SetPointError(ipt+1, 0.001,0.001, meanX[iSpecies][iglb].err, meanX[iSpecies][iglb].err);

      //hdpt[iSpecies][iglb] = (TH1D*)fff[iSpecies][iglb]->Get(Form("dpt_icent%d_final",icent));
      hdpt[iSpecies][iglb] = (TH1D*)fff[iSpecies][iglb]->Get(Form("jetPt_icent%d_final",icent));
      hdptNorm[iSpecies][iglb] = (TH1D*)hdpt[iSpecies][iglb]->Clone(Form("norm_%s",hdpt[iSpecies][iglb]->GetName()) );
      meanDpt[iSpecies][iglb].val = hdpt[iSpecies][iglb]->GetMean();
      meanDpt[iSpecies][iglb].err = hdpt[iSpecies][iglb]->GetMeanError();
      gdpt[iSpecies]->SetPoint     (ipt+1, AvePtBin[ipt], meanDpt[iSpecies][iglb].val);
      gdpt[iSpecies]->SetPointError(ipt+1, 0.001,0.001, meanDpt[iSpecies][iglb].err, meanDpt[iSpecies][iglb].err);

      
      double rError;
      rjg[iSpecies][iglb].val = hxjg[iSpecies][iglb]->IntegralAndError(1, hxjg[iSpecies][iglb]->GetNbinsX(), rError, "width");
      rjg[iSpecies][iglb].err = rError;
      gr[iSpecies]->SetPoint     (ipt+1, AvePtBin[ipt], rjg[iSpecies][iglb].val);
      gr[iSpecies]->SetPointError(ipt+1, 0.001,0.001, rjg[iSpecies][iglb].err, rjg[iSpecies][iglb].err);

      
    }
  }
  
  TCanvas* c1 = new TCanvas("c1","",900,350);
  makeMultiPanelCanvas(c1,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) {
    
    
    c1->cd(ipt+1);
    
    int iSpecies = kPPDATA;
    int iglb = ipt + iSpecies*50.;
    handsomeTH1(hdptNorm[iSpecies][iglb],1);
    if (xNorm==1) scaleInt(hdptNorm[iSpecies][iglb]);
    hdptNorm[iSpecies][iglb]->SetXTitle("x_{J,#gamma}");
    hdptNorm[iSpecies][iglb]->SetYTitle("#frac{dN}{dx} #frac{1}{N}");
    //    hdptNorm[iSpecies][iglb]->SetAxisRange(-100,100,"X");
    hdptNorm[iSpecies][iglb]->SetAxisRange(0,150,"X");
    if (xNorm==1)     hdptNorm[iSpecies][iglb]->SetAxisRange(-.03,.9,"Y");
    else              hdptNorm[iSpecies][iglb]->SetAxisRange(-.001,.016,"Y");
    hdptNorm[iSpecies][iglb]->SetMarkerStyle(24);
    hdptNorm[iSpecies][iglb]->Draw();

    iSpecies = kHIDATA;
    iglb = ipt + iSpecies*50.;
    if (xNorm==1)  scaleInt(hdptNorm[iSpecies][iglb]);
    handsomeTH1(hdptNorm[iSpecies][iglb],2);
    if (drawPbPb) hdptNorm[iSpecies][iglb]->Draw("same");
    //    onSun(0,0,2,0);

    //    onSun(meanX[iSpecies][iglb].val - meanX[iSpecies][iglb].err, 0, meanX[iSpecies][iglb].val+meanX[iSpecies][iglb].err,0,ycolor[ipt+1],2);
    
    float dx1;    
    (ipt==0)? dx1=0.15 : dx1=0 ;
    
    if ( ipt == nPtBin-1 ) 
      drawText(Form("p_{T}^{#gamma} > %dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt]), 0.12+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.889118,1,15);

      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
    l1->AddEntry(hdptNorm[kPPDATA][ipt + kPPDATA*50],"pp ","p");
    if (drawPbPb)    l1->AddEntry(hdptNorm[kHIDATA][iglb],"PbPb 0-30%","p");
    if ( ipt==0 )   l1->Draw();

  }
  //  c1->SaveAs(Form("gifs/dpt_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));

  TCanvas* cDphi = new TCanvas("cDphi","",900,350);
  makeMultiPanelCanvas(cDphi,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) {
    cDphi->cd(ipt+1);
    
    int iSpecies = kPPDATA;
    int iglb = ipt + iSpecies*50.;
    handsomeTH1(hdphi[iSpecies][iglb],1);
    hdphi[iSpecies][iglb]->SetYTitle("x_{J,#gamma}");
    hdphi[iSpecies][iglb]->SetXTitle("#Delta#phi_{J,#gamma}");
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    hdphi[iSpecies][iglb]->SetAxisRange(0.01,30,"Y");
    hdphi[iSpecies][iglb]->SetMarkerStyle(24);
    hdphi[iSpecies][iglb]->Draw();

    iSpecies = kHIDATA;
    iglb = ipt + iSpecies*50.;
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    handsomeTH1(hdphi[iSpecies][iglb],2);
    if (drawPbPb)     hdphi[iSpecies][iglb]->Draw("same");
    gPad->SetLogy();
    float dx1;    
    (ipt==0)? dx1=0.15 : dx1=0 ;
    
    if ( ipt == nPtBin-1 ) 
      drawText(Form("%dGeV<p_{T}^{#gamma},   p_{T}^{jet}>30GeV", (int)ptBin[ipt]), 0.15+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV<p_{T}^{#gamma}<%dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.15+dx1,0.889118,1,15);
    
      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"2.76TeV");
    l1->AddEntry(hdphi[kPPDATA][ipt + kPPDATA*50],"pp ","p");
    if (drawPbPb)    l1->AddEntry(hdphi[kHIDATA][iglb],"PbPb 0-30%","p");
    if ( ipt==0 )   l1->Draw();

  }

  
  //  cDphi->SaveAs(Form("gifs/dphi_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));
  
  TCanvas* c2 = new TCanvas("c2","",800,400);
  c2->Divide(2,1);
  c2->cd(2);
  TH1D* hr = new TH1D("hr",";p_{T}^{#gamma};r_{J,#gamma}",200,20,180);
  handsomeTH1(hr,0);
  hr->SetAxisRange(0.0,1.3,"Y");
  //  hr->SetNdivisions(5);
  hr->Draw();
  handsomeTGraph(gr[kPPDATA],1);
  handsomeTGraph(gr[kHIDATA],2);
  gr[kPPDATA]->SetMarkerStyle(24);
  gr[kPPDATA]->Draw("same p");
  if (drawPbPb)   gr[kHIDATA]->Draw("same p");
  jumSun(20,1,180,1);


  
  c2->cd(1);
  TH1D* hx = (TH1D*)hr->Clone("hx");
  handsomeTH1(hx,0);
  hx->SetYTitle("<#Deltap_{T}^{J,#gamma}>");
  //  hx->SetAxisRange(-60,10,"Y");
  hx->SetAxisRange(0,100,"Y");
  //  hx->SetNdivisions(5);
  hx->Draw();
  handsomeTGraph(gdpt[kPPDATA],1);
  handsomeTGraph(gdpt[kHIDATA],2);
  gdpt[kPPDATA]->SetMarkerStyle(24);
  gdpt[kPPDATA]->Draw("same p");
  if (drawPbPb)   gdpt[kHIDATA]->Draw("same p");
  jumSun(20,1,180,1);

  TLegend *l1=   new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
  easyLeg(l1,"2.76TeV");
  l1->AddEntry(gr[kPPDATA],"pp ","p");
  if (drawPbPb)     l1->AddEntry(gr[kHIDATA],"PbPb 0-30%","p");
  l1->Draw();

  //  c2->SaveAs(Form("gifs/summaryPlot_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));

}

//  LocalWords:  ipt

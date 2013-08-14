#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawMcClosureTest(int xNorm = 1) { 
  
  const int nCentBin = nCentBinPa;
  double* centBin = centBinPa;
  const int nPtBin = nPtBinPa; 
  double* ptBin = ptBinPa;
  
  TH1D* hxjg[7][5][6][4]; // [Collision][centrality][pt][MC level]
  TH1D* hxjgNorm[7][5][6][4]; // [Collision][centrality][pt][MC level]
  TH1D* meanXjg[7][5][4];      // [Collisi on][centrality][MC level]
  TH1D* rjg[7][5][4];     //  [Collision][centrality][MC level]
  for (int icoll=0 ; icoll<6 ; icoll++) {  
    for (int icent=1 ; icent<=nCentBin ; icent++) {
      for (int imc=0 ; imc<=4 ; imc++) {  
	meanXjg[icoll][icent][imc] = new TH1D( Form("meanXjg_icoll%d_icent%d_imc%d",icoll,icent,imc), ";p_{T}^{#gamma}; <X_{J#gamma}>",nPtBin,ptBinPaDraw);
	rjg[icoll][icent][imc] = new TH1D( Form("meanXjg_icoll%d_icent%d_imc%d",icoll,icent,imc), ";p_{T}^{#gamma}; R_{J#gamma}",nPtBin,ptBinPaDraw);
      }
    }
  }
  TFile* histFile[7][6];  // [Collision][pt]

  for (int ipt=1 ; ipt<=nPtBin ; ipt++) {  
    for (int icoll=0 ; icoll<6 ; icoll++) {  
      TString sampleName = getSampleName( icoll ) ;
      histFile[icoll][ipt] = new TFile(Form("ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130813.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]) );
      if ( histFile[icoll][ipt]->IsZombie()  == false ) {
	for (int icent=1 ; icent<=nCentBin ; icent++) {  
	  for (int imc=0 ; imc <4 ; imc++) {
	    TString mcStr = "";
	    if ( imc == 1 )  mcStr = "_genPho";
	    else if ( imc == 2 )  mcStr = "_genJet";
	    else if ( imc == 3 )  mcStr = "_genPho_genJet";
	    hxjg[icoll][icent][ipt][imc] = (TH1D*)histFile[icoll][ipt]->Get(Form("xjg%s_icent%d_phoCand_rawTrk", mcStr.Data(), icent)) ;
	    hxjgNorm[icoll][icent][ipt][imc] = (TH1D*)hxjg[icoll][icent][ipt][imc]->Clone(Form("%s_norm", hxjg[icoll][icent][ipt][imc]->GetName() ));
	    // Mean xjg and Rjg calculation
	    meanXjg[icoll][icent][imc]->SetBinContent( ipt, hxjg[icoll][icent][ipt][imc]->GetMean() );
	    meanXjg[icoll][icent][imc]->SetBinError  ( ipt, hxjg[icoll][icent][ipt][imc]->GetMeanError() );
	    double rVal, rErr;
	    rVal = hxjg[icoll][icent][ipt][imc]->IntegralAndError(1, hxjg[icoll][icent][ipt][imc]->GetNbinsX(), rErr, "width");                
	    rjg[icoll][icent][imc]->SetBinContent( ipt, rVal );
	    rjg[icoll][icent][imc]->SetBinError  ( ipt, rErr );
	  }
	} 
      }
    }
  }
  
  
  
  
  // pPb
  TCanvas* c1 = new TCanvas("c1","",1200,800);
  makeMultiPanelCanvas(c1,nPtBin,nCentBin,0.0,0.0,0.2,0.15,0.02);
  TH1D* htemp = new TH1D("htempxjg",";x_{J,#gamma};#frac{dN}{dx} #frac{1}{N}",200,0,2);     
  handsomeTH1(htemp,1);
  for (int icent=1;icent<=nCentBin;icent++) {
    for (int ipt=1;ipt<=nPtBin ;ipt++) {
      c1->cd(ipt + nPtBin * (icent-1) );
      htemp->SetAxisRange(-0.05,3,"Y");
      htemp->DrawCopy();
      handsomeTH1(hxjgNorm[kPAMC][icent][ipt][0],1);
      handsomeTH1(hxjgNorm[kPAMC][icent][ipt][1],kBlue);
      handsomeTH1(hxjgNorm[kPAMC][icent][ipt][2],kMagenta);
      handsomeTH1(hxjgNorm[kPAMC][icent][ipt][3],1);
      
      
      for (int imc=3; imc >=0 ;imc--) {
	hxjgNorm[kPAMC][icent][ipt][imc]->Scale ( 1. / hxjgNorm[kPAMC][icent][ipt][imc]->Integral("width") );    
	if ( imc == 3 ) hxjgNorm[kPAMC][icent][ipt][imc]->Draw("same hist");
	else hxjgNorm[kPAMC][icent][ipt][imc]->Draw("same");
      }
    }
  }

  TCanvas *c2 = new TCanvas("c2", "",151,384,909,355);
  makeMultiPanelCanvas(c2,nCentBin,1,0.0,0.0,0.2,0.15,0.02);
  TH1D* htemp2 = new TH1D("htempxjg2",";p_{T}^{#gamma} (GeV); x_{J,#gamma}",200,39,200);
  htemp2->SetAxisRange(0.7,1.1,"Y");
  handsomeTH1(htemp2,0);
  for (int icent=1;icent<=nCentBin;icent++) {
    c2->cd(icent);
    htemp2->DrawCopy();
    handsomeTH1(meanXjg[kPAMC][icent][0],1);
    handsomeTH1(meanXjg[kPAMC][icent][1],kBlue);
    handsomeTH1(meanXjg[kPAMC][icent][2],kMagenta);
    handsomeTH1(meanXjg[kPAMC][icent][3],1);
    for (int imc=3; imc >=0 ;imc--) {
      if ( imc == 3 ) meanXjg[kPAMC][icent][imc]->Draw("same hist");
      else meanXjg[kPAMC][icent][imc]->Draw("same");
    }
    gPad->SetLogx();
  }  

  TCanvas *c3 = new TCanvas("c3", "",151,384,909,355);
  makeMultiPanelCanvas(c3,nCentBin,1,0.0,0.0,0.2,0.15,0.02);
  TH1D* htemp3 = new TH1D("htemprjg3",";p_{T}^{#gamma} (GeV);  R_{J,#gamma}",200,39,200);
  htemp3->SetAxisRange(0.3,1.1,"Y");
  handsomeTH1(htemp3,0);
  for (int icent=1;icent<=nCentBin;icent++) {
    c3->cd(icent);
    htemp3->DrawCopy();
    handsomeTH1(rjg[kPAMC][icent][0],1);
    handsomeTH1(rjg[kPAMC][icent][1],kBlue);
    handsomeTH1(rjg[kPAMC][icent][2],kMagenta);
    handsomeTH1(rjg[kPAMC][icent][3],1);
    for (int imc=3; imc >=0 ;imc--) {
      if ( imc == 3 ) rjg[kPAMC][icent][imc]->Draw("same hist");
      else rjg[kPAMC][icent][imc]->Draw("same");
    }
    gPad->SetLogx();
  }  

}

  
/*  
    OA
    hxjg[iSpecies][iglb] = (TH1D*)fff[iSpecies][iglb]->Get(Form("xjg_icent%d_final",icent));
    hxjgNorm[iSpecies][iglb] = (TH1D*)hxjg[iSpecies][iglb]->Clone(Form("norm_%s",hxjg[iSpecies][iglb]->GetName()) );
    
    meanX[iSpecies][iglb].val = hxjg[iSpecies][iglb]->GetMean();
    meanX[iSpecies][iglb].err = hxjg[iSpecies][iglb]->GetMeanError();
    gx[iSpecies]->SetPoint     (icent, AvePtBin[icent-1], meanX[iSpecies][iglb].val);
    gx[iSpecies]->SetPointError(icent, AvePtBin[icent-1] - centBin[icent-1], centBin[icent] - AvePtBin[icent-1], meanX[iSpecies][iglb].err, meanX[iSpecies][iglb].err);
    
    double rError;
    rjg[iSpecies][iglb].val = hxjg[iSpecies][iglb]->IntegralAndError(1, hxjg[iSpecies][iglb]->GetNbinsX(), rError, "width");
    rjg[iSpecies][iglb].err = rError;
    gr[iSpecies]->SetPoint     (icent, AvePtBin[icent-1], rjg[iSpecies][iglb].val);
    gr[iSpecies]->SetPointError(icent,  AvePtBin[icent-1] - centBin[icent-1], centBin[icent] - AvePtBin[icent-1], rjg[iSpecies][iglb].err, rjg[iSpecies][iglb].err);
    
    
  }
  
  TCanvas* c1 = new TCanvas("c1","",900,700);
  makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.2,0.15,0.02);
  for ( int icent = 1 ; icent<=nCentBin  ; icent++) {
    
    
    c1->cd(icent);
    
    int iSpecies = kPADATA;
    int iglb = icent + iSpecies*50.;
    handsomeTH1(hxjgNorm[iSpecies][iglb],1);
    hxjgNorm[iSpecies][iglb]->Scale(0.1);
    if (xNorm==1) scaleInt(hxjgNorm[iSpecies][iglb]);
    hxjgNorm[iSpecies][iglb]->SetXTitle("x_{J,#gamma}");
    hxjgNorm[iSpecies][iglb]->SetYTitle("#frac{dN}{dx} #frac{1}{N}");
    if (xNorm==1)     hxjgNorm[iSpecies][iglb]->SetAxisRange(-0.015,0.3,"Y");
    else              hxjgNorm[iSpecies][iglb]->SetAxisRange(-0.06,1.5,"Y");
    hxjgNorm[iSpecies][iglb]->SetMarkerStyle(20);
    hxjgNorm[iSpecies][iglb]->Draw();

    
    float dx1;    
    ((icent==1)||(icent==4))? dx1=0.15 : dx1=0 ;
    
    if ( icent == nCentBin ) 
      drawText(Form("E_{T}^{HF|#eta|>4} > %dGeV, ", (int)centBin[icent]), 0.12+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV < E_{T}^{HF|#eta|>4} < %dGeV, ", (int)centBin[icent-1], (int)centBin[icent]), 0.12+dx1,0.889118,1,15);

      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"5.02TeV");
    l1->AddEntry(hxjgNorm[kPADATA][icent + kPADATA*50],"pPb ","p");
    if ( icent==1 )   l1->Draw();
    onSun(0,0,2,0);
    jumSun(1,0,1,1);
  }

  TCanvas* c11 = new TCanvas("c11","",500,500);
  for ( int icent = 1 ; icent<=nCentBin  ; icent++) {
    int iSpecies = kPADATA;
    int iglb = icent + iSpecies*50.;
    handsomeTH1(hxjgNorm[iSpecies][iglb],ycolor[icent]);

    if ( icent == 1 ) hxjgNorm[iSpecies][iglb]->Draw();
    else     hxjgNorm[iSpecies][iglb]->Draw("same");
    onSun(0,0,2,0);
  }


  TCanvas* cDphi = new TCanvas("cDphi","",900,700);
  makeMultiPanelCanvas(cDphi,3,2,0.0,0.0,0.2,0.15,0.02);
  for ( int icent = 1 ; icent<=nCentBin  ; icent++) {
    cDphi->cd(icent);
    
    int iSpecies = kPADATA;
    int iglb = icent + iSpecies*50.;
    handsomeTH1(hdphi[iSpecies][iglb],1);
    hdphi[iSpecies][iglb]->SetXTitle("#Delta#phi_{J,#gamma}");
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    hdphi[iSpecies][iglb]->SetAxisRange(0.01,30,"Y");
    //    hdphi[iSpecies][iglb]->SetMarkerStyle(24);
    handsomeTH1(hdphi[iSpecies][iglb],ycolor[icent]);
    hdphi[iSpecies][iglb]->Draw();

    gPad->SetLogy();
    float dx1;    
    ((icent==1)||(icent==4))? dx1=0.15 : dx1=0 ;
    

    if ( icent == nCentBin )
      drawText(Form("E_{T}^{HF|#eta|>4} > %dGeV", (int)centBin[icent]), 0.32+dx1+0.25,0.889118,1,15);
    else
      drawText(Form("%dGeV < E_{T}^{HF|#eta|>4} < %dGeV", (int)centBin[icent-1], (int)centBin[icent]), 0.32+dx1,0.889118,1,15);
    

  }

  
  TCanvas* c2 = new TCanvas("c2","",800,400);
  c2->Divide(2,1);
  c2->cd(2);
  TH1D* hr = new TH1D("hr",";E_{T}^{HF|#eta|>4} (GeV);r_{J,#gamma}",200,0,100);
  handsomeTH1(hr,1);
  hr->SetAxisRange(0.0,1.1,"Y");
  //  hr->SetNdivisions(5);
  hr->Draw();
  handsomeTGraph(gr[kPADATA],1);
  gr[kPADATA]->SetMarkerStyle(20);
  gr[kPADATA]->Draw("same p");

  jumSun(0,1,100,1);


  
  c2->cd(1);
  TH1D* hx = (TH1D*)hr->Clone("hx");
  handsomeTH1(hx,1);
  hx->SetYTitle("<x_{J,#gamma}>");
  hx->SetAxisRange(0.6,1.05,"Y");
  //  hx->SetNdivisions(5);
  hx->Draw();
  handsomeTGraph(gx[kPADATA],1);
  gx[kPADATA]->SetMarkerStyle(20);
  gx[kPADATA]->Draw("same p");
  jumSun(0,1,100,1);

  TLegend *l1=   new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
  easyLeg(l1,"5.02TeV");
  l1->AddEntry(gr[kPADATA],"pPb ","p");
  l1->Draw();


}
*/

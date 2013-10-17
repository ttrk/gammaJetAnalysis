// Author Alex Barbieri

#include "../HiForestAnalysis/hiForest.h"
#include "commonUtility.h"
#include <TMath.h>
#include <iostream>
#include <fstream>
#include "TGraphErrors.h"
using namespace std;

// //pp
// const TString MC_FILE = "gammaJets_pp_MC_PUallQCDPhoton.root";
// const TString collHistLabel2 = "pythia 2.76TeV";
// const TString coll = "pp";
// const TCut isoCut = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";

//PbPb
const TString MC_FILE = "gammaJets_PbPb_MC_allQCDPhoton.root";
const TString collHistLabel2 = "pythia+HYDJET 2.76TeV";
const TString coll = "PbPb";
const TCut isoCut = "cc4 + cr4 + ct4PtCut20 < 1.0 && hadronicOverEm < 0.1";

// //pPb
// const TString MC_FILE = "gammaJets_pA_MC_allQCDPhoton.root";
// const TString collHistLabel2 = "pythia+HIJING 5.02TeV";
// const TString coll = "pPb";
// const TCut isoCut = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";

//const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
const Double_t PTBINS[] = {40, 45, 50, 55, 60, 70, 80, 120, 200, 1000};
//const Double_t PTBINS[] = {40, 1000};
const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

const Double_t ETABINS[] = {-1.44, 1.44};
//const Double_t ETABINS[] = {-1.44, -1, -0.5, 0, 0.5, 1, 1.44};
const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

const Int_t CENTBINS[] = {0, 12, 40};
//const Int_t CENTBINS[] = {0, 100};
const Int_t nCENTBINS = sizeof(CENTBINS)/sizeof(Int_t) -1;

void photonScaleAndResolution()
{
  // (reco photon pt / gen photon pt) histogram parameters
  Int_t nHistBin = 100;
  Double_t histMin = 0.8;
  Double_t histMax = 1.2;
    
  // fit type for widths
  TString fitStr = "[0]+[1]/sqrt(x)+[2]/x";
  //const Int_t nFitParam = 3;
  //===========================================================

  TFile *mcFile = TFile::Open(MC_FILE);
  TTree *photonTree = (TTree*)mcFile->Get("photonTree"); 
  
  TH1D *recoPtOverGenPt[nCENTBINS][nPTBINS][nETABINS];
  TH1D *meanGenPt[nCENTBINS][nPTBINS][nETABINS];
  //TH1D *widthHist[nCENTBINS][nETABINS];
  //TH1D *scaleHist[nCENTBINS][nETABINS];
  TGraphErrors *widthHist[nCENTBINS][nETABINS];
  TGraphErrors *scaleHist[nCENTBINS][nETABINS];
  for(Int_t i = 0; i < nCENTBINS; ++i){
    for(Int_t k = 0; k < nETABINS; ++k){
      for(Int_t j = 0; j < nPTBINS; ++j){
	TString name1 = "recoOverGenPt";
	name1 += Form("_cent%d_%d",CENTBINS[i],CENTBINS[i+1]);
	name1 += Form("_pt%d_%d",(Int_t)PTBINS[j],(Int_t)PTBINS[j+1]);
	//name1 += Form("_eta%d_%d",(Int_t)ETABINS[k],(Int_t)ETABINS[k+1]);
	recoPtOverGenPt[i][j][k] = new TH1D(name1.Data(),
					    ";photon p_{T}^{reco}/p_{T}^{gen};n photons",
					    nHistBin,histMin,histMax);
	TString name2 = name1 + "meanGenPt";
	meanGenPt[i][j][k] = new TH1D(name2.Data(),
				      "",1000,0,1000);

	TString ptCut = Form("(genPt >= %f) && (genPt < %f)",
			     PTBINS[j], PTBINS[j+1]);
	TString centCut = Form("(hiBin >= %i) && (hiBin < %i)",
			     CENTBINS[i], CENTBINS[i+1]);
	TString etaCut = Form("(eta >= %f) && (eta < %f)",
			      ETABINS[k], ETABINS[k+1]);
	TCut cut = isoCut;
	cut += ptCut;
	cut += etaCut;
	cut += centCut;

	photonTree->Project(name1,"corrPt/genPt","mcweight"*cut);
	photonTree->Project(name2,"genPt","mcweight"*cut);
	
      }
      
      // TString name2 = "widthHist_";
      // name2 += Form("_cent%d_%d",CENTBINS[i],CENTBINS[i+1]);
      // //name2 += Form("_eta%d_%d",(Int_t)ETABINS[k],(Int_t)ETABINS[k+1]);
      // widthHist[i][k] = new TH1D(name2.Data(),";photon p_{T}^{gen};#sigma",nPTBINS,PTBINS);

      // TString name3 = "scaleHist_";
      // name3 += Form("_cent%d_%d",CENTBINS[i],CENTBINS[i+1]);
      // //name3 += Form("_eta%d_%d",(Int_t)ETABINS[k],(Int_t)ETABINS[k+1]);
      // scaleHist[i][k] = new TH1D(name3.Data(),";photon p_{T}^{gen};<p_{T}^{reco}/p_{T}^{gen}>",nPTBINS,PTBINS);
    }
  }

  // plot and fit
  //Double_t minY, maxY; // y range for fit plots
  TCanvas *cphotonPtComp[nCENTBINS];
  for(Int_t iCent = 0; iCent < nCENTBINS; ++iCent){
    cphotonPtComp[iCent] = new TCanvas(
      Form("photonPtCompCentBin%d",iCent),
      Form("photonPtCompCentBin%d",iCent),
      500*nPTBINS,400*nETABINS);
    makeMultiPanelCanvas(cphotonPtComp[iCent],nPTBINS,nETABINS);

    Double_t x[nPTBINS];
    Double_t ex[nPTBINS];
    Double_t ywidth[nPTBINS];
    Double_t eywidth[nPTBINS];
    Double_t yscale[nPTBINS];
    Double_t eyscale[nPTBINS];
    
    for(Int_t i = 0; i < nPTBINS; ++i){
      for(Int_t j = 0; j < nETABINS; ++j){
	cphotonPtComp[iCent]->cd(i + 1 + j*nPTBINS);
                
	// style
	handsomeTH1(recoPtOverGenPt[iCent][i][j],1);
	// recoPtOverGenPt[iCent][i][j]->SetStats(0);
	// recoPtOverGenPt[iCent][i][j]->GetXaxis()->SetTitleSize(0.08);
	// recoPtOverGenPt[iCent][i][j]->GetYaxis()->SetTitleSize(0.08);
	// recoPtOverGenPt[iCent][i][j]->GetXaxis()->SetLabelSize(0.08);
	// recoPtOverGenPt[iCent][i][j]->GetYaxis()->SetLabelSize(0.08);
	recoPtOverGenPt[iCent][i][j]->SetAxisRange(0.0,
						   1.5*recoPtOverGenPt[iCent][i][j]->GetBinContent(
						     recoPtOverGenPt[iCent][i][j]->GetMaximumBin()),"Y");
                
	// draw and fit
	recoPtOverGenPt[iCent][i][j]->Draw();
	recoPtOverGenPt[iCent][i][j]->Fit("gaus");
                
	// vertical dashed line at x=1
	jumSun(1.0,0.0,1.0,1.5*recoPtOverGenPt[iCent][i][j]->GetBinContent(
		 recoPtOverGenPt[iCent][i][j]->GetMaximumBin()));
                
	// draw labels
	if(i == 0 || j == 0) {
	  Float_t xoffset = 0.2*(i==0);
	  TLegend *leg0 = new TLegend(0.0+xoffset,0.62,0.4+xoffset,0.95);
	  leg0->SetFillStyle(0);
	  // leg0->SetBorderSize(0);
	  // leg0->SetTextSize(0.08);
	  if(i==0 && j == 0){
	    TString label = coll;
	    leg0->AddEntry(recoPtOverGenPt[iCent][i][j],label,"");
	    leg0->AddEntry(recoPtOverGenPt[iCent][i][j],collHistLabel2,"");
	    if(nCENTBINS > 1){
	      leg0->AddEntry(recoPtOverGenPt[iCent][i][j],
			     Form("%.0f - %.0f%c",CENTBINS[iCent]*100./40.,CENTBINS[iCent+1]*100./40.,'%'),"");
	    }
	  }
	  // if(i == 0){
	  //   leg0->AddEntry(recoPtOverGenPt[iCent][i][j],
	  // 		   Form("%.1f < |#eta| < %.1f",ETABINS[j],ETABINS[j+1]),"");
	  // }
	  if(j == 0){
	    leg0->AddEntry(recoPtOverGenPt[iCent][i][j],
			   Form("%.1f < p_{T} < %.1f",PTBINS[i],PTBINS[i+1]),"");
	  }
                    
	  leg0->Draw();
	}
                
	// fit
	TF1 *fit = recoPtOverGenPt[iCent][i][j]->GetFunction("gaus");
	x[i] = meanGenPt[iCent][i][j]->GetMean();
	ex[i] = meanGenPt[iCent][i][j]->GetMeanError();
	ywidth[i] = fit->GetParameter(2);
	eywidth[i] = fit->GetParError(2);
	yscale[i] = fit->GetParameter(1);
	eyscale[i] = fit->GetParError(1);
	// widthHist[iCent][j]->SetBinContent(i+1,fit->GetParameter(2));
	// widthHist[iCent][j]->SetBinError(i+1,fit->GetParError(2));
	// scaleHist[iCent][j]->SetBinContent(i+1,fit->GetParameter(1));
	// scaleHist[iCent][j]->SetBinError(i+1,fit->GetParError(1));
      }
    }
    widthHist[iCent][0] = new TGraphErrors(nPTBINS, x, ywidth, ex, eywidth);
    widthHist[iCent][0]->GetXaxis()->SetTitle("photon p_{T}^{gen}");  
    widthHist[iCent][0]->GetXaxis()->CenterTitle();		      
    widthHist[iCent][0]->GetYaxis()->SetTitle("#sigma");	      
    widthHist[iCent][0]->GetYaxis()->CenterTitle();                   
    scaleHist[iCent][0] = new TGraphErrors(nPTBINS, x, yscale, ex, eyscale);
    scaleHist[iCent][0]->GetXaxis()->SetTitle("photon p_{T}^{gen}");  
    scaleHist[iCent][0]->GetXaxis()->CenterTitle();		      
    scaleHist[iCent][0]->GetYaxis()->SetTitle("<p_{T}^{reco}/p_{T}^{gen}>");	      
    scaleHist[iCent][0]->GetYaxis()->CenterTitle();                   
    
    // // get y range
    // maxY = -1;
    // for(Int_t i = 0; i < nETABINS; ++i){
    //   maxY = max(maxY,widthHist[iCent][i]->GetBinContent(widthHist[iCent][i]->GetMaximumBin()));
    // }
        
    // minY = maxY;
    // for(Int_t i = 0; i < nETABINS; ++i){
    //   minY = min(minY,widthHist[iCent][i]->GetBinContent(widthHist[iCent][i]->GetMinimumBin()));
    // }
        
  }
    
  // plot gaussian width and fit to custom function
  TCanvas *cwidth = new TCanvas(Form("%swidth",coll.Data()),
				Form("%swidth",coll.Data()),
				500*nCENTBINS,400*nETABINS);
  TCanvas *cscale = new TCanvas(Form("%sscale",coll.Data()),
				Form("%sscale",coll.Data()),
				500*nCENTBINS,400*nETABINS);
  //makeMultiPanelCanvas(cwidth,nCENTBINS,nETABINS,0.2,0.2);
  //makeMultiPanelCanvas(cscale,nCENTBINS,nETABINS,0.2,0.2);
  cwidth->Divide(nCENTBINS,nETABINS);
  cscale->Divide(nCENTBINS,nETABINS);
  TF1 *widthFit = new TF1("widthFit",fitStr.Data(),PTBINS[0],PTBINS[nPTBINS]);
  //Double_t FitParam[nFitParam][nCENTBINS][nETABINS];
  //Double_t FitParamErr[nFitParam][nCENTBINS][nETABINS];
  for(Int_t i = 0; i < nCENTBINS; ++i){
    for(Int_t j = 0; j < nETABINS; ++j){
      cwidth->cd(i + 1 + j*nCENTBINS);
      //handsomeTH1(widthHist[i][j],1);
      // widthHist[i][j]->SetStats(0);
      // widthHist[i][j]->GetXaxis()->SetTitleSize(0.08);
      // widthHist[i][j]->GetYaxis()->SetTitleSize(0.08);
      // widthHist[i][j]->GetXaxis()->SetLabelSize(0.08);
      // widthHist[i][j]->GetYaxis()->SetLabelSize(0.08);
      //widthHist[i][j]->SetAxisRange(0.9*minY,1.1*maxY,"Y");
      widthHist[i][j]->Draw("A ep");
      widthHist[i][j]->Fit(widthFit);

      // draw labels
      //if(i == 0 || j == 0){
      //Float_t xoffset = 0.1*(i==0 && nCENTBINS>1);
	TLegend *leg0 = new TLegend(0.23,0.7,0.6,0.95);
	leg0->SetFillStyle(0);
	// leg0->SetBorderSize(0);
	// leg0->SetTextSize(0.08);
	if(i == 0 && j == 0){
	  TString label = coll;
	  leg0->AddEntry(widthHist[i][j],label,"");
	  leg0->AddEntry(widthHist[i][j],collHistLabel2,"");
	}
	if(j == 0 && nCENTBINS > 1){
	  leg0->AddEntry(widthHist[i][j],
			 Form("%.0f- %.0f%c",CENTBINS[i]*100./40.,CENTBINS[i+1]*100./40.,'%'),"");
	}
	// if(i == 0){
	//   leg0->AddEntry(widthHist[i][j],
	// 		 Form("%.1f < |#eta| < %.1f",ETABINS[j],ETABINS[j+1]),"");
	// }
                
	leg0->Draw();
	//}
            
      // TF1 *fit = widthHist[i][j]->GetFunction("widthFit");
      // for(Int_t k = 0; k < nFitParam; ++k){
      // 	FitParam[k][i][j] = fit->GetParameter(k);
      // 	FitParamErr[k][i][j] = fit->GetParError(k);
      // }

      cscale->cd(i + 1 + j*nCENTBINS);
      //handsomeTH1(scaleHist[i][j],1);
      scaleHist[i][j]->Draw("A ep");
      leg0->Draw();
    }
  }
  TString savename = Form("photonResolution_%s_",coll.Data());
  cwidth->SaveAs(savename+"widths.pdf");
  cscale->SaveAs(savename+"means.pdf");
   
}


int main()
{
  photonScaleAndResolution();
  return 0;
}

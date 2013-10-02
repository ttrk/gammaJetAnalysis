#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"
#include "Math/BrentMinimizer1D.h"
#include <TH1.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraph.h>
#include <TFile.h>
#include <TCanvas.h>
#include "fitResult.h"
//#include "uniqueEvents.C"
#include "commonUtility.h"
#include <iostream>
using namespace std;

//passing by global variables is awful but I don't have time to figure out
//nested functors
// I need to make sure none of these names collide with those used above
TTree *dtree_;
TTree *mtree_;
TCut dCut_;
TCut sCut_;
TCut mCut_;
Double_t bkg_shift_;
Double_t purityBinVal_;

double minimizerPurity(const double xx)
{
  fitResult fitr = getPurity(dtree_, mtree_,
			     dCut_, sCut_,
			     mCut_, xx,
			     bkg_shift_, purityBinVal_);
  return fitr.chisq;
}

Double_t getBestFitShift(TTree *dataTree, TTree *mcTree,
			 TCut dataCandidateCut, TCut sidebandCut,
			 TCut mcSignalCut,
			 Double_t backgroundShift, Double_t purityBinVal)
{
  dtree_ = dataTree;
  mtree_ = mcTree;
  dCut_ = dataCandidateCut;
  sCut_ = sidebandCut;
  mCut_ = mcSignalCut;
  bkg_shift_ = backgroundShift;
  purityBinVal_ = purityBinVal;

  
  // ROOT::Minuit2::Minuit2Minimizer min ( ROOT::Minuit2::kMigrad );
  // min.SetMaxFunctionCalls(1000000);
  // min.SetMaxIterations(100000);
  // min.SetTolerance(0.00001); 
  // ROOT::Math::Functor f(&minimizerPurity,1); 
  // double step = 0.00001;
  // double variable = 0; 
  // min.SetFunction(f); 
  // // Set the free variables to be minimized!
  // //min.SetLimitedVariable(0,"sigShift",variable, step,-0.0005,0.0005); 
  // min.SetVariable(0,"sigShift",variable, step);
  // min.Minimize();

  ROOT::Math::Functor1D func(&minimizerPurity);
 
  ROOT::Math::BrentMinimizer1D bm;
  bm.SetFunction(func, -0.0005,0.0005);
  bm.Minimize(10);
  
  //cout << "f(" << bm.XMinimum() << ") = " <<bm.FValMinimum() << endl;
   
  //return min.X()[0];
  return bm.XMinimum();
}

void plotChi2(TTree *dataTree, TTree *mcTree,
	      TCut dataCandidateCut, TCut sidebandCut,
	      TCut mcSignalCut,
	      Double_t backgroundShift, Double_t purityBinVal)
{
  dtree_ = dataTree;
  mtree_ = mcTree;
  dCut_ = dataCandidateCut;
  sCut_ = sidebandCut;
  mCut_ = mcSignalCut;
  bkg_shift_ = backgroundShift;
  purityBinVal_ = purityBinVal;

  const int bins = 100;//0.001/0.00001;
  double x[bins];
  double y[bins];
  
  for(int i = 0; i < bins; i++)
  {
    double shift = -0.0005 + 0.001 * ((double)i/bins);
    x[i] = shift;
    y[i] = minimizerPurity(shift);    
  }

  TGraph *plot = new TGraph(bins,x,y);
  plot->GetYaxis()->SetTitle("#chi^2/ndf");
  plot->GetXaxis()->SetTitle("signal distribution shift");
  plot->Draw("AP");
}

void photonChi2Min()
{
  TH1::SetDefaultSumw2();
  
  //pPb
  const TString DATA_FILE = "gammaJets_pA_Data.root";
  const TString MC_FILE = "gammaJets_pA_MC_allQCDPhoton.root";

  //pp
  //const TString DATA_FILE = "gammaJets_pp_Data.root";
  //const TString MC_FILE = "gammaJets_pp_MC_PUallQCDPhoton.root";

  //PbPb
  //const TString DATA_FILE = "gammaJets_PbPb_Data.root";
  //const TString MC_FILE = "gammaJets_PbPb_MC_allQCDPhoton.root";

// last entry is upper bound on last bin
  const Int_t CENTBINS[] = {0,12,40};
  //const Int_t CENTBINS[] = {0,100};
  const Int_t nCENTBINS = sizeof(CENTBINS)/sizeof(Int_t) -1;

  const Double_t PTBINS[] = {40, 50, 60, 80, 1000};
//const Double_t PTBINS[] = {40, 1000};
  const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

  //const Double_t ETABINS[] = {-1.479, 1.479};
  //const Double_t ETABINS[] = {-1.479, -1, -0.5, 0, 0.5, 1, 1.479};
  const Double_t ETABINS[] = {-1.44, 1.44};
  const Int_t nETABINS = sizeof(ETABINS)/sizeof(Double_t) -1;

// the bin which holds this value is considered the largest bin when
// computing the purity
  const Double_t PURITY_BIN_VAL = 0.00999;

  TFile *dataFile = TFile::Open(DATA_FILE);
  TTree *dataTree = (TTree*)dataFile->Get("photonTree");

  TFile *mcFile = TFile::Open(MC_FILE);
  TTree *mcTree = (TTree*)mcFile->Get("photonTree");

  TCut sampleIsolation = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";
  //TCut sampleIsolation = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
  TCut sidebandIsolation = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";
  TCut mcIsolation = "genCalIsoDR04<5 && abs(genMomId)<=22";

  for(Int_t i = 0; i < nPTBINS; ++i) {
    for(Int_t j = 0; j < nCENTBINS; ++j) {
      for(Int_t k = 0; k< nETABINS; ++k) {
	TString ptCut = Form("(pt >= %f) && (pt < %f)",
			     PTBINS[i], PTBINS[i+1]);
	TString centCut = Form("(hiBin >= %i) && (hiBin < %i)",
			     CENTBINS[j], CENTBINS[j+1]);
	TString etaCut = Form("(eta >= %f) && (eta < %f)",
			      ETABINS[k], ETABINS[k+1]);

	TString pPbflipetaCut = Form("(eta*((run>211257)*-1+(run<211257)) >=%f) && (eta*((run>211257)*-1+(run<211257)) <%f)",
				     ETABINS[k], ETABINS[k+1]);

	TCut dataCandidateCut = sampleIsolation && etaCut && ptCut && centCut;
	TCut sidebandCut =  sidebandIsolation && etaCut && ptCut && centCut;
	TCut mcSignalCut = dataCandidateCut && mcIsolation;
		
	if(nETABINS != 1)
	{
	  dataCandidateCut = sampleIsolation && pPbflipetaCut && ptCut && centCut;
	  sidebandCut =  sidebandIsolation && pPbflipetaCut && ptCut && centCut;
	  mcSignalCut =  sampleIsolation && etaCut && ptCut && centCut && mcIsolation;
	}

	Double_t bestFit = getBestFitShift(dataTree, mcTree,
					   dataCandidateCut, sidebandCut,
					   mcSignalCut,
					   0.0, PURITY_BIN_VAL);

	cout << "pT bin: " << PTBINS[i]
	     << " cent: " << CENTBINS[j]
	     << " shiftval: " << bestFit << endl;

	//TCanvas *c1 = new TCanvas();
	// plotChi2(dataTree, mcTree,
	// 	 dataCandidateCut, sidebandCut,
	// 	 mcSignalCut,
	// 	 0.0, PURITY_BIN_VAL);

	// if(nPTBINS != 1)
	//   drawText(Form("%.0f < p_{T}^{#gamma} < %.0f",
	// 		PTBINS[i], PTBINS[i+1]),
	// 	   0.57, 0.9);
	// if(nCENTBINS != 1)
	//   drawText(Form("%.0f < E_{T}^{HF[|#eta|>4]} < %.0f",
	// 		HFBINS[j], HFBINS[j+1]),
	// 	   0.57, 0.82);
	// if(nETABINS != 1)
	//   drawText(Form("%.3f < #eta_{#gamma} < %.3f",
	// 		ETABINS[k], ETABINS[k+1]),
	// 	   0.57, 0.82);		 

	// c1->SaveAs(Form("pPb_chi2_%d%d%d.png",i,j,k));
      }
    }
  }
}

int main()
{
  photonChi2Min();
  return 0;
}

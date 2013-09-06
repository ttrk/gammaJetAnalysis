#include <TH1.h>
#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"
#include <TNtuple.h>
#include <TCut.h>

class fitResult {
public:
  Double_t nSig;
  Double_t nSigErr;
  Double_t purity;
  Double_t chisq;
  Double_t sigMeanShift;

  TH1F *sigPdf;
  TH1F *bckPdf;
  TH1D *data;
};

class histFunction2
{ 
public:
  histFunction2(TH1D *h, TH1D *h2);
  ~histFunction2(){ 
    delete histBck;
    delete histSig;
  };
  
  //      Int_t GetBinNumber(Double_t c);
  Double_t evaluate(Double_t *x, Double_t *par);
  TH1D *histSig;
  TH1D *histBck;
  Double_t lowEdge;
  Double_t highEdge;
  Double_t nbin;
};

histFunction2::histFunction2(TH1D *h,TH1D *h2)
{
  histSig=(TH1D*)h->Clone();
  histBck=(TH1D*)h2->Clone();
   
  nbin=h->GetNbinsX();
  lowEdge=h->GetBinLowEdge(1);
  highEdge=h->GetBinLowEdge(nbin+1);
   
  histSig->SetName("hSig");
  histSig->Scale(1./histSig->Integral(1,histSig->GetNbinsX()+1));
  histBck->SetName("hBck");
  histBck->Scale(1./histBck->Integral(1,histBck->GetNbinsX()+1));
}

Double_t histFunction2::evaluate(Double_t *x, Double_t *par) {
     
  Double_t xx = x[0];
  Int_t binNum=histSig->FindBin(xx);  //
   
  return par[0]*(histSig->GetBinContent(binNum)*par[1]+histBck->GetBinContent(binNum)*(1-par[1]));
}


fitResult doFit(TH1D* hSig=0, TH1D* hBkg=0, TH1D* hData1=0,
		Float_t varLow=0.001, Float_t varHigh=0.028,
		Double_t purityBinVal=0.00999)
{
  TH1D* hDatatmp = (TH1D*)hData1->Clone(Form("%s_datatmp",hData1->GetName()));
  Int_t nBins = hDatatmp->GetNbinsX();
  histFunction2 *myFits = new histFunction2(hSig,hBkg);
  TF1 *f = new TF1("f",myFits,&histFunction2::evaluate,varLow,varHigh,2);
  f->SetParameters( hDatatmp->Integral(1,nBins+1), 0.3);
  f->SetParLimits(1,0,1);
  hDatatmp->Fit("f","LL M O Q","",varLow,varHigh);
  hDatatmp->Fit("f","LL M O Q","",varLow,varHigh);

  fitResult res;
  res.nSig =0;
  Double_t nev = f->GetParameter(0);
  Double_t ratio = f->GetParameter(1);
  Double_t ratioErr = f->GetParError(1);
  res.nSig    = nev * ratio;
  res.nSigErr = nev * ratioErr;
  res.chisq = (Double_t)f->GetChisquare()/ f->GetNDF();
   
  TH1F *hSigPdf = (TH1F*)hSig->Clone(Form("%s_tmp",hSig->GetName()));
  hSigPdf->Scale(res.nSig/hSigPdf->Integral(1,nBins+1));

  TH1F *hBckPdf = (TH1F*)hBkg->Clone(Form("%s_tmp",hBkg->GetName()));
  hBckPdf->Scale((nev-res.nSig)/hBckPdf->Integral(1,nBins+1));

  Double_t ss1 = hSigPdf->Integral(1, hSigPdf->FindBin(purityBinVal),"width");
  Double_t bb1 = hBckPdf->Integral(1, hBckPdf->FindBin(purityBinVal),"width");
  res.purity = ss1/(ss1+bb1);

  res.sigPdf = (TH1F*)hSigPdf->Clone(Form("%s_sig",hSig->GetName()));
  res.bckPdf = (TH1F*)hBckPdf->Clone(Form("%s_bck",hBkg->GetName()));
  res.data = (TH1D*)hData1->Clone(Form("%s_cand",hData1->GetName()));

  return res;
}

void mcStyle(TH1* h=0) {
  h->SetLineColor(kPink);
  h->SetFillColor(kOrange+7);
  h->SetFillStyle(3004);
}

void sbStyle(TH1* h=0) {
  h->SetLineColor(kGreen+4);
  h->SetFillColor(kGreen+1);
  h->SetFillStyle(3001);
}


const Int_t nSIGMABINS = 100; // number of bins in sigmaIetaIeta dist
const Double_t maxSIGMA = 0.025; // x-axis max of sigmaIetaIeta dist

fitResult getPurity(TNtuple *dataTuple, TNtuple *mcTuple,
		    TCut dataCandidateCut, TCut sidebandCut,
		    TCut mcSignalCut, Double_t signalShift,
		    Double_t backgroundShift, Double_t purityBinVal)
{
  TH1D* hCand = new TH1D("cand","",nSIGMABINS,0,maxSIGMA);
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");
  TH1D* hSig = (TH1D*)hCand->Clone("sig");

  TString sigshift = "+";
  sigshift += signalShift;
  TString bkgshift = "+";
  bkgshift += backgroundShift;
  
  Int_t dEntries = dataTuple->Project(hCand->GetName(), "sigmaIetaIeta", dataCandidateCut, "");
  Int_t sbEntries = dataTuple->Project(hBkg->GetName(), "sigmaIetaIeta"+bkgshift, sidebandCut, "");
  Int_t mcEntries = mcTuple->Project(hSig->GetName(), "sigmaIetaIeta"+sigshift, "mcweight"*mcSignalCut, "");

  //cout << "# Candidates: " << dEntries << endl;
  //cout << "# Sideband: " << sbEntries << endl;
  //cout << "# MC Signal: " << mcEntries << endl;

  TCanvas *fakeCanvas = new TCanvas("fake","fake");
  fitResult fitr = doFit(hSig, hBkg, hCand, 0.005, 0.035, purityBinVal);
  delete fakeCanvas;
  
  delete hSig;
  delete hBkg;
  delete hCand;

  fitr.sigMeanShift = signalShift;

  return fitr;
}

//passing by global variables is awful but I don't have time to figure out
//nested functors
// I need to make sure none of these names collide with those used above
TNtuple *dtuple_;
TNtuple *mtuple_;
TCut dCut_;
TCut sCut_;
TCut mCut_;
Double_t bkg_shift_;
Double_t purityBinVal_;

double minimizerPurity(const double *xx)
{
  fitResult fitr = getPurity(dtuple_, mtuple_,
			     dCut_, sCut_,
			     mCut_, xx[0],
			     bkg_shift_, purityBinVal_);
  return fitr.chisq;
}

fitResult getBestFitPurity(TNtuple *dataTuple, TNtuple *mcTuple,
			   TCut dataCandidateCut, TCut sidebandCut,
			   TCut mcSignalCut,
			   Double_t backgroundShift, Double_t purityBinVal)
{
  dtuple_ = dataTuple;
  mtuple_ = mcTuple;
  dCut_ = dataCandidateCut;
  sCut_ = sidebandCut;
  mCut_ = mcSignalCut;
  bkg_shift_ = backgroundShift;
  purityBinVal_ = purityBinVal;

  
  ROOT::Minuit2::Minuit2Minimizer min ( ROOT::Minuit2::kMigrad );
  min.SetMaxFunctionCalls(1000000);
  min.SetMaxIterations(100000);
  min.SetTolerance(0.00001); 
  ROOT::Math::Functor f(&minimizerPurity,1); 
  double step = 0.00001;
  double variable = 0; 
  min.SetFunction(f); 
  // Set the free variables to be minimized!
  min.SetLimitedVariable(0,"sigShift",variable, step,-0.0005,0.0005); 
  min.Minimize(); 

  Double_t bestSigShift = min.X()[0];

  return getPurity(dataTuple, mcTuple,
		   dataCandidateCut, sidebandCut,
		   mcSignalCut, bestSigShift,
		   backgroundShift, purityBinVal);
}

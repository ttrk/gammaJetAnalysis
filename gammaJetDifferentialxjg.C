#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include "TCut.h"
//#include "../HiForest_V3/hiForest.h"

//last forward run is 211256


const Double_t hfBins[] = {0, 20, 30, 1000}; //last entry is upper bound on last bin
const Int_t nhfBins = 3;

//int returnHFBin(double hf);

void gammaJetDifferentialxjg()
{
  TH1::SetDefaultSumw2();

  TFile *inFile = TFile::Open("gammaJets_inclusive_dphi7pi8_pPbData_v2.root");
  TNtuple *inTuple = (TNtuple*)inFile->Get("gammaJets");

  //book histos
  TH1D *gammaJetEta[nhfBins];
  TH1D *x_jg[nhfBins];
  TH1D *hfEnergy[nhfBins];
  Int_t numEvts[nhfBins];
  Int_t numEvtsEtaPlus[nhfBins];
  
  TCanvas *c[4];
  c[0] = new TCanvas();
  c[1] = new TCanvas();
  TLegend *leg = new TLegend(0.65,0.65,0.9,0.9);
  leg->SetFillColor(0);
  
  for(Int_t i = 0; i < nhfBins; ++i)
  {
    TString s_gammaJetEta = "gammaJetEta";
    s_gammaJetEta += i;
    gammaJetEta[i] = new TH1D(s_gammaJetEta,";Avg #eta_{#gamma jet};Event Fraction",14,-3,3);

    TString s_hfEnergy = "hfEnergy";
    s_hfEnergy += i;
    hfEnergy[i] = new TH1D(s_hfEnergy,"",1000,0,1000);

    TString s_x_jg = "x_jg";
    s_x_jg += i;
    x_jg[i] = new TH1D(s_x_jg,";p_{T}^{jet}/p_{T}^{#gamma};Event Fraction",20,0,1.5);

    TCut isolationCut = "(cc4 + cr4 + ct4PtCut20 < 1.0)";
    //TCut etaCut = "(abs(gEta) > 1.479)";
    //TCut showerShapeCut = "(sigmaIetaIeta < 0.035)";
    TCut etaShowerCut = "((abs(gEta) < 1.479) && (sigmaIetaIeta < 0.01) || (abs(gEta) > 1.479) && (sigmaIetaIeta < 0.035))";
    TCut ptCut = "(jPt > 30) && (gPt > 50)";
    TString hfCut = "((HFplusEta4+HFminusEta4) > ";
    hfCut += hfBins[i];
    hfCut += " ) && ( (HFplusEta4+HFminusEta4) < ";
    hfCut += hfBins[i+1];
    hfCut += " )";
    //TCut cut = isolationCut && etaCut && showerShapeCut && ptCut && hfCut;
    TCut cut = isolationCut && etaShowerCut && ptCut && hfCut;
    //printf("cut: %s\n",(const char*)cut);
    TString runFlip = "((run > 211257)*(-1) + (run < 211257))";
    
    numEvts[i] = inTuple->Project(s_gammaJetEta,"avgEta*"+runFlip,cut);
    numEvtsEtaPlus[i] = inTuple->GetEntries(
      cut &&
      "( avgEta*(run < 211257) >0 ) || ( avgEta*(run > 211257) <0 )"
      );
    inTuple->Project(s_hfEnergy,"(HFplusEta4+HFminusEta4)",cut);
    inTuple->Project(s_x_jg,"jPt/gPt",cut);

    gammaJetEta[i]->Scale(1./numEvts[i]);
    gammaJetEta[i]->SetMarkerColor(i+1);
    gammaJetEta[i]->SetLineColor(i+1);

    x_jg[i]->Scale(1./numEvts[i]);
    x_jg[i]->SetMarkerColor(i+1);
    x_jg[i]->SetLineColor(i+1);

    TString label;
    label += hfBins[i];
    label += " < E_{T}^{HF[|#eta|>4]} < ";
    label += hfBins[i+1];
    
    leg->AddEntry(gammaJetEta[i], label, "lp");
    
    if(i==0)
    {
      //TLatex *lnorm = new TLatex(0.2,0.85, "Monte Carlo");
      //lnorm->SetNDC(1);
      //lnorm->SetTextSize(0.05);
     
      gammaJetEta[i]->GetXaxis()->CenterTitle();
      gammaJetEta[i]->GetYaxis()->CenterTitle();
      gammaJetEta[i]->SetMaximum(gammaJetEta[i]->GetMaximum()*1.7);
      x_jg[i]->GetXaxis()->CenterTitle();
      x_jg[i]->GetYaxis()->CenterTitle();
      x_jg[i]->SetMaximum(x_jg[i]->GetMaximum()*1.7);

      c[0]->cd();
      gammaJetEta[i]->Draw("");
      //lnorm->Draw("same");
      c[1]->cd();
      x_jg[i]->Draw("");
      //lnorm->Draw("same");
    }
    else
    {
      c[0]->cd();
      gammaJetEta[i]->Draw("same");
      c[1]->cd();
      x_jg[i]->Draw("same");
    }

    c[0]->cd();
    gammaJetEta[i]->Draw("same Lhist");
    leg->Draw();
    c[1]->cd();
    x_jg[i]->Draw("same Lhist");
    leg->Draw();
  }

  //c[0]->SaveAs("avgeta_gammajet_sumiso1_numevts_v2.gif");


  //";E_{T}^{HF[|#eta|>4]};<#eta_{#gamma jet}>");
  Double_t x[nhfBins];// = {10, 25, 40};
  Double_t y[nhfBins];
  Double_t ye[nhfBins];
  Double_t y2[nhfBins];
  Double_t y2e[nhfBins];
  for(Int_t i = 0; i < nhfBins; i++)
  {
    x[i] = hfEnergy[i]->GetMean();
    y[i] = gammaJetEta[i]->GetMean();
    ye[i]= gammaJetEta[i]->GetMeanError();

    y2[i] = x_jg[i]->GetMean();
    y2e[i] = x_jg[i]->GetMeanError();
  }
  c[2] = new TCanvas();
  TGraphErrors *means = new TGraphErrors(nhfBins,x,y,0,ye);
  means->GetXaxis()->SetTitle("E_{T}^{HF[|#eta|>4]}");
  means->GetXaxis()->CenterTitle();
  means->GetYaxis()->SetTitle("<#eta_{#gamma jet}>");
  means->GetYaxis()->CenterTitle();
  //means->SetMinimum(-0.7);
  means->SetMaximum(0);
  means->Draw("AP");

  c[3] = new TCanvas();
  TGraphErrors *x_jg_means = new TGraphErrors(nhfBins,x,y2,0,y2e);
  x_jg_means->GetXaxis()->SetTitle("E_{T}^{HF[|#eta|>4]}");
  x_jg_means->GetXaxis()->CenterTitle();
  x_jg_means->GetYaxis()->SetTitle("<x_{J #gamma}>");
  x_jg_means->GetYaxis()->CenterTitle();
  x_jg_means->Draw("AP");


}

int main()
{
  gammaJetDifferentialxjg();
  return 0;
}

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TChain.h>
#include <TLine.h>
#include <TMath.h>
#include <TString.h>
#include "../../HiForestAnalysis/hiForest.h"
#include "../CutAndBinCollection2012.h"
//#include "../histogramProducer/corrFunctionJetTrk.h"

void smearCheck()
{
  TH1::SetDefaultSumw2();

  multiTreeUtil* tgjPPsmear[4];
  multiTreeUtil* tgjPbPbpythia = new multiTreeUtil();
  multiTreeUtil* tgjPP = new multiTreeUtil();

  TString PTBINS[5] = {"30", "50", "80", "120", "9999"};
  TString smearBins[4] = {"0010", "1030", "3050", "5099"};

  for(int i = 0; i < 4; i++)
  {
    tgjPPsmear[i] = new multiTreeUtil();
    for(int j = 0; j < 4; j++)
    {
      TString inName = Form("yskim_merged_allQCDPhoton%sto%s_genPhotonPtCut30_CMSSW538HIp2_jetSmearingCent%s.root", PTBINS[j].Data(), PTBINS[j+1].Data(), smearBins[i].Data());
      Double_t weight;
      if(j == 0)
	weight = wPPMC_AllQcdPho30to50;
      else if(j == 1)
	weight = wPPMC_AllQcdPho50to80;
      else if(j == 2)
	weight = wPPMC_AllQcdPho80to120;
      else if(j == 3)
	weight = wPPMC_AllQcdPho120to9999;
      
      tgjPPsmear[i]->addFile(inName, "yJet", "", weight);
    }
    tgjPPsmear[i]->AddFriend("tgj");
  }

  tgjPP->addFile("yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "", wPPMC_AllQcdPho30to50);
  tgjPP->addFile("yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "", wPPMC_AllQcdPho50to80);
  tgjPP->addFile("yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "", wPPMC_AllQcdPho80to120);
  tgjPP->addFile("yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet", "", wPPMC_AllQcdPho120to9999);
  tgjPP->AddFriend("tgj");


  tgjPbPbpythia->addFile("yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", "yJet", "", wHIMC_AllQcdPho30to50);
  tgjPbPbpythia->addFile("yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", "yJet", "", wHIMC_AllQcdPho50to80);
  tgjPbPbpythia->addFile("yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", "yJet", "", wHIMC_AllQcdPho80to9999);
  tgjPbPbpythia->AddFriend("tgj");

  //TString var = "yJet.pt/yJet.refPt";
  TString var = "yJet.pt";
  TCut anaCut = "(photonEt>40)&&(yJet.pt>30)";
  TCut sigdPhi = "(dphi > 7.*TMath::Pi()/8.)";
  TCut bkgdPhi = "(dphi > 0.5 && dphi<2.0)";
  TCut cent[4] = {"cBin < 4","cBin >=4 && cBin < 12",
		  "cBin >=12 && cBin < 20", "cBin >= 20"};

  TH1D *pt_pp[4];
  pt_pp[0] = new TH1D("pt_pp0","pt;p_{T}^{Jet};Count",50,0,200);
  pt_pp[1] = (TH1D*)pt_pp[0]->Clone("pt_pp1");
  pt_pp[2] = (TH1D*)pt_pp[0]->Clone("pt_pp2");
  pt_pp[3] = (TH1D*)pt_pp[0]->Clone("pt_pp3");

  TH1D *pt_pbpb[4];
  pt_pbpb[0] = (TH1D*)pt_pp[0]->Clone("pt_pbpb0");
  pt_pbpb[1] = (TH1D*)pt_pp[0]->Clone("pt_pbpb1");
  pt_pbpb[2] = (TH1D*)pt_pp[0]->Clone("pt_pbpb2");
  pt_pbpb[3] = (TH1D*)pt_pp[0]->Clone("pt_pbpb3");

  TH1D *sub[4];
  sub[0] = (TH1D*)pt_pp[0]->Clone("sub0");
  sub[1] = (TH1D*)pt_pp[0]->Clone("sub1");
  sub[2] = (TH1D*)pt_pp[0]->Clone("sub2");
  sub[3] = (TH1D*)pt_pp[0]->Clone("sub3");

  for(int i = 0; i < 4; i++)
  {
    tgjPPsmear[i]->Draw2(pt_pp[i], var, anaCut && sigdPhi, "1");
    tgjPbPbpythia->Draw2(pt_pbpb[i], var, anaCut && sigdPhi && cent[i], "1");
    tgjPbPbpythia->Draw2(sub[i], var, anaCut && bkgdPhi && cent[i], "1");
    
    sub[i]->Scale(TMath::Pi()/(8.*(2-0.5)));
    pt_pbpb[i]->Add(sub[i],-1);

    pt_pp[i]->Scale(1./pt_pp[i]->Integral());
    pt_pbpb[i]->Scale(1./pt_pbpb[i]->Integral());
  }
    
  TCanvas *c1 = new TCanvas();
  // TH1D *hTemp = (TH1D*)pt_pp[0]->Clone("hTemp");
  // hTemp->SetMarkerColor(0);
  // hTemp->SetLineColor(0);
  // hTemp->Draw();
  for(int i = 0; i < 4; i++)
  {
    pt_pp[i]->SetMarkerColor(i+1);
    pt_pp[i]->SetLineColor(i+1);
    pt_pbpb[i]->SetMarkerColor(i+1);
    pt_pbpb[i]->SetLineColor(i+1);
    pt_pbpb[i]->SetMarkerStyle(24);

    if(i == 0)
      pt_pp[i]->Draw();
    else
      pt_pp[i]->Draw("same");
    pt_pbpb[i]->Draw("same");
  }
  c1->SetLogy();
  c1->SaveAs("smearLog.png");

  // TLegend *leg = new TLegend(0.5, 0.5, 0.8, 0.8);
  // leg->SetFillColor(0);
  // leg->AddEntry(pt[0],"pythia smeared central","p");
  // leg->AddEntry(pt[1],"pythia smeared peripheral", "p");
  // leg->AddEntry(pt[2],"pythia+HYDJET central", "p");
  // leg->AddEntry(pt[3],"pythia+HYDJET peripheral", "p");
  // leg->Draw();

  TCanvas *c2 = new TCanvas();
  TH1D *ratio[4];
  TLegend *leg2 = new TLegend(0.2, 0.6, 0.5, 0.85);
  leg2->SetFillColor(0);  
  for(int i = 0; i < 4; i++)
  {
    TString name = "ratio";
    name += i;
    ratio[i] = (TH1D*)pt_pp[0]->Clone(name);
    ratio[i]->Divide(pt_pp[i],pt_pbpb[i],1,1);
    ratio[i]->SetMarkerColor(i+1);
    ratio[i]->SetLineColor(i+1);
    if(i == 0)
    {
      ratio[i]->SetYTitle("(smeared pythia)/(pythia+HYDJET)");
      ratio[i]->Draw();
    }
    else
      ratio[i]->Draw("same");

    leg2->AddEntry(ratio[i], smearBins[i]+"%", "p");
  }
  
  // ratio[0]->SetYTitle("(smeared pythia)/(pythia+HYDJET)");
  // ratio[0]->SetMinimum(0.5);
  // ratio[0]->SetMaximum(1.5);
  // ratio[0]->Draw();
  // ratio[1]->SetMarkerColor(kBlue);
  // ratio[1]->SetLineColor(kBlue);
  // ratio[1]->Draw("same");

  TLine *line = new TLine(0,1,200,1);
  line->Draw();
  leg2->Draw();
  c2->SaveAs("smearRatio.png");

  // TCanvas *c3 = new TCanvas();
  // for(int i = 0; i <2; i++)
  // {
  //   TString name = "ratio";
  //   name += i+2;
  //   ratio[i+2] = (TH1D*)pt[i]->Clone(name);
  //   ratio[i+2]->Divide(pt[i],pt[4],1,1);
  // }
  
  // ratio[2]->SetYTitle("(smeared pythia)/pythia");
  // ratio[2]->SetMinimum(0.5);
  // ratio[2]->SetMaximum(1.5);
  // ratio[2]->Draw();
  // ratio[3]->SetMarkerColor(kBlue);
  // ratio[3]->SetLineColor(kBlue);
  // ratio[3]->Draw("same");

  // line->Draw();
  // leg2->Draw();

  

  
}

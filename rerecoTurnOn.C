#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "stdio.h"
#include "../HiForestAnalysis/hiForest.h"

void rerecoTurnOn()
{
  TH1::SetDefaultSumw2();

  TH1D *pass[4];
  TH1D *tot[4];
  pass[0] = new TH1D("pass15","",
		     40,0,120);
  pass[1] = (TH1D*)pass[0]->Clone("pass20");
  pass[2] = (TH1D*)pass[0]->Clone("pass30");
  pass[3] = (TH1D*)pass[0]->Clone("pass40");
  tot[0] = (TH1D*)pass[0]->Clone("tot15");
  tot[1] = (TH1D*)pass[0]->Clone("tot20");
  tot[2] = (TH1D*)pass[0]->Clone("tot30");
  tot[3] = (TH1D*)pass[0]->Clone("tot40");

  // pythia 80 sample
  //TString filename = "/mnt/hadoop/cms/store/user/dgulhan/HIMC/Jet80/Track8_Jet6_STARTHI53_LV1/merged2/HiForest_Pythia_Hydjet_Jet80_Track8_Jet6_STARTHI53_LV1_merged_forest_0.root";

  // minbias hydjet sample
  TString filename = "/mnt/hadoop/cms/store/user/rkunnawa/rootfiles/PbPb/2011/mc/PbPb_MinBias_Hydjet_STARTHI53_LV1_track8_Jet5_FOREST_6Feb2014_mergedv1.root";

  TString trigName[4];
  trigName[0] = "HLT_HISinglePhoton15_v5";
  trigName[1] = "HLT_HISinglePhoton20_v6";
  trigName[2] = "HLT_HISinglePhoton30_v6";
  trigName[3] = "HLT_HISinglePhoton40_v6";

  TFile *infile = TFile::Open(filename);

  HiForest *c = new HiForest(filename, "Forest", cPbPb, true);
  c->InitTree();
  c->LoadNoTrees();
  c->hasPhotonTree=true;
  c->hasEvtTree=true;
  c->hasHltTree=true;
  c->hasSkimTree=true;

  // hltTree
  TTree *hltTree = (TTree*)infile->Get("hltanalysis/HltTree");

  Int_t HLT_HISinglePhoton15_v5;
  Int_t HLT_HISinglePhoton20_v6;
  Int_t HLT_HISinglePhoton30_v6;
  Int_t HLT_HISinglePhoton40_v6;

  hltTree->SetBranchAddress("HLT_HISinglePhoton15_v5",&HLT_HISinglePhoton15_v5);
  hltTree->SetBranchAddress("HLT_HISinglePhoton20_v6",&HLT_HISinglePhoton20_v6);
  hltTree->SetBranchAddress("HLT_HISinglePhoton30_v6",&HLT_HISinglePhoton30_v6);
  hltTree->SetBranchAddress("HLT_HISinglePhoton40_v6",&HLT_HISinglePhoton40_v6);



  // photonTree
  //TTree *photonTree = (TTree*)infile->Get("multiPhotonAnalyzer/photon");

  // Int_t nPhotons;
  // Float_t pt[126];

  // photonTree->SetBranchAddress("nPhotons",&nPhotons);
  // photonTree->SetBranchAddress("pt",pt);


  int nentries = c->GetEntries();
  //printf("nentries: %d\n",nentries);
  for(int jentry = 0; jentry<nentries; jentry++)
  {
    if (jentry% 1000 == 0)  {
      printf("%d / %d\n",jentry,nentries);
    }

    hltTree->GetEntry(jentry);
    c->GetEntry(jentry);

    //if( !(c->skim.pHBHENoiseFilter && c->skim.phfPosFilter1 && c->skim.phfNegFilter1 && c->skim.phltPixelClusterShapeFilter && c->skim.pprimaryvertexFilter) )
    //if( !(c->skim.pHBHENoiseFilter && c->skim.phfCoincFilter && c->skim.ppurityFractionFilter) )
    //if( !(c->skim.pHBHENoiseFilter && c->skim.pcollisionEventSelection ) )
    //continue;

    if(c->photon.nPhotons == 0)
      continue;

    Float_t leadingPt = 0;
    Int_t leadingIndex = -1;
    for(int i = 0; i<c->photon.nPhotons; i++)
    {
      if( (c->photon.swissCrx[i] > 0.95) || (TMath::Abs(c->photon.seedTime[i]) > 3) )
	continue;
      if(c->photon.pt[i] > leadingPt)
      {
	leadingPt = c->photon.pt[i];
	leadingIndex = i;
      }
    }
    if(leadingIndex == -1) continue;
    if ( (c->photon.scEta[leadingIndex] < 1.479) && (c->photon.sigmaIetaIeta[leadingIndex] > 0.011) )
      continue;
    if ( (c->photon.scEta[leadingIndex] > 1.479) && (c->photon.sigmaIetaIeta[leadingIndex] > 0.035) )
      continue;
    if( c->photon.hadronicOverEm[leadingIndex] > 0.05 )
      continue;

      //if(HLT_PAZeroBiasPixel_SingleTrack_v5)
    {
      tot[0]->Fill(leadingPt);
      pass[0]->Fill(leadingPt, HLT_HISinglePhoton15_v5);
    }

    //if(HLT_HISinglePhoton15_v5)
    {
      tot[1]->Fill(leadingPt);
      pass[1]->Fill(leadingPt, HLT_HISinglePhoton20_v6);
    }
    //if(HLT_HISinglePhoton20_v6)
    {
      tot[2]->Fill(leadingPt);
      pass[2]->Fill(leadingPt, HLT_HISinglePhoton30_v6);
    }

    //if(HLT_HISinglePhoton30_v6)
    {
      tot[3]->Fill(leadingPt);
      pass[3]->Fill(leadingPt, HLT_HISinglePhoton40_v6);
    }
  }

  TCanvas *c1 = new TCanvas();
  TH1D *hEmpty = (TH1D*)pass[0]->Clone("hEmpty");
  hEmpty->Reset();
  hEmpty->SetXTitle("Reconstructed Photon p_{T} (GeV)");
  hEmpty->SetYTitle("Efficiency");
  hEmpty->Draw();

  TLegend *leg = new TLegend(0.5, 0.2, 0.8, 0.5);
  leg->SetFillColor(0);
  leg->SetTextFont(43);
  leg->SetTextSize(20);

  TGraphAsymmErrors *turnOn[4];
  for(int i = 0; i < 4; i++)
  {
    turnOn[i] = new TGraphAsymmErrors();
    turnOn[i]->BayesDivide(pass[i],tot[i]);
    turnOn[i]->SetMarkerStyle(20);
    turnOn[i]->SetMarkerColor(i+1);
    turnOn[i]->SetLineColor(i+1);

    turnOn[i]->Draw("p same");

    leg->AddEntry(turnOn[i],trigName[i],"p");
  }
  leg->Draw();

  c1->SaveAs("rereco_HLT_turnon.pdf");
}

int main()
{
  rerecoTurnOn();
  return 0;
}

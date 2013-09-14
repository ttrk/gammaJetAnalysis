#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "stdio.h"
#include "../HiForestAnalysis/hiForest.h"

void bkgCorrectionStudy()
{
  //const TString inFile = "/mnt/hadoop/cms/store/user/goyeonju/MC_Production/PYTHIA/pp_2760GeV/forest/emDijet30_CMSSW538HIp2.root";
  const TString inFile = "/mnt/hadoop/cms/store/user/luck/pp_photonSkimForest_v85/pp_photonSKimForest_v85.root";
  
  collisionType cType = cPPb; // cPP loads the wrong track tree.
  bool montecarlo = true;
  HiForest *c = new HiForest(inFile, "Forest", cType, montecarlo);

  TH1D *htrkDEta[3];
  htrkDEta[0] = new TH1D("htrkDEta0-10","",50,0,0.005);
  htrkDEta[1] = (TH1D*)htrkDEta[0]->Clone("htrkDEta10-20");
  htrkDEta[2] = (TH1D*)htrkDEta[0]->Clone("htrkDEta20-30");

  //loop over events in each file
  Long64_t nentries = c->GetEntries();
  for(Long64_t jentry = 0; jentry<100000; ++jentry)
  {
    if (jentry % 1000 == 0)  {
      printf("%lld / %lld\n",jentry,nentries);
    }
    
    c->GetEntry(jentry);

    //event selection
    if( cType != cPbPb &&
	!(
	  (montecarlo || c->skim.pHBHENoiseFilter)
	  && c->skim.phfPosFilter1
	  && c->skim.phfNegFilter1
	  && c->skim.phltPixelClusterShapeFilter
	  && c->skim.pprimaryvertexFilter
	  )
      ) {
      continue;
    } else if ( cType == cPbPb && !montecarlo &&
		!(c->skim.pcollisionEventSelection)){
      continue;
    }

    if(c->photon.nPhotons == 0)
      continue;

    //loop over photons in the event
    Float_t leadingPt = 0;
    Int_t leadingIndex = -1;
    for(Int_t i = 0; i < c->photon.nPhotons; ++i)
    {
      if(c->photon.pt[i] > leadingPt)
      {
	leadingPt = c->photon.pt[i];
	leadingIndex = i;
      }
    }
      
    if(leadingIndex == -1)
      continue;

    Float_t gEta = c->photon.eta[leadingIndex];
    Float_t gPhi = c->photon.phi[leadingIndex];
    
    Float_t cc4 = c->photon.cc4[leadingIndex];
    Float_t cr4 = c->photon.cr4[leadingIndex];
    Float_t ct4PtCut20 = c->photon.ct4PtCut20[leadingIndex];

    Double_t sumIso = cc4 + cr4 + ct4PtCut20;
    Int_t hIndex = -1;
    if(sumIso > 0 && sumIso < 10)
      hIndex = 0;
    else if (sumIso > 10 && sumIso < 20)
      hIndex = 1;
    else if (sumIso > 20 && sumIso < 30)
      hIndex = 2;
    else
      continue;

    //loop over tracks, checking dEta from leading photon
    for(Int_t i = 0; i < c->track.nTrk; i++)
    {
      Float_t trkEta = c->track.trkEta[i];
      Float_t trkPhi = c->track.trkPhi[i];

      if(c->track.trkPt[i] > 4.7)
	htrkDEta[hIndex]->Fill(TMath::Abs(gEta - trkEta));
    }
  }

  TCanvas *c1 = new TCanvas();
  htrkDEta[0]->SetMinimum(0);
  htrkDEta[0]->SetMaximum(htrkDEta[2]->GetMaximum() *1.5);
  htrkDEta[0]->SetYTitle("count");
  htrkDEta[0]->SetXTitle("#Delta #eta_{#gamma trk}");
  htrkDEta[0]->Draw();
  htrkDEta[1]->SetLineColor(kBlue);
  htrkDEta[1]->Draw("same");
  htrkDEta[2]->SetLineColor(kRed);
  htrkDEta[2]->Draw("same");

  TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->AddEntry("htrkDEta0-10","0 < sumIso < 10","l"); 
  leg->AddEntry("htrkDEta10-20","10 < sumIso < 20","l"); 
  leg->AddEntry("htrkDEta20-30","20 < sumIso < 30","l");
  leg->Draw("same");

}

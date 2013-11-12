// Author Alex Barbieri
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "stdio.h"
#include "TRandom3.h"
#include "../HiForestAnalysis/hiForest.h"
#include "alexGammaSkim.h"

const Double_t gammaEtaCut = 1.44;
const Double_t jetEtaCut = 1.6;

// stuff related to MB mixing
const int nCentBinSkim = 40;
const int vzCut = 15;
const int nMixing1 = 20;

void loop(HiForest *forest, TH1D *vertex, TH1I *centBin, int sample, Double_t weight);

void vertexReweightingHisto()
{
  const TString ppDataFileName = "/mnt/hadoop/cms/store/user/luck/pp_photonSkimForest_v85_fromPromptReco/0.root";
  const TString ppMCFileName[] = {"/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",
				  "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",
				  "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",
				  "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root"};
  const Double_t ppMCweight[] = { 29329./29329. ,  8098./87988. ,  1680./96756. ,  438./90972. };

  const TString pPbDataFileName = "/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85/pA_photonSkimForest_v85.root";
  const TString pPbMCFileName[] = {"/mnt/hadoop/cms/store/user/goyeonju/pA/PA2013_pyquen_allQCDPhoton30to50_forestv85.root",
				   "/mnt/hadoop/cms/store/user/goyeonju/pA/PA2013_pyquen_allQCDPhoton50to80_forestv85.root",
				   "/mnt/hadoop/cms/store/user/goyeonju/pA/PA2013_pyquen_allQCDPhoton80to120_forestv85.root",
				   "/mnt/hadoop/cms/store/user/goyeonju/pA/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root"};
  const Double_t pPbMCweight[] = {56669./50385, 41906./114136, 12044./103562, 4481./151511};

  const TString PbPbDataFileName = "/mnt/hadoop/cms/store/user/luck/PbPb2011_photons_Data/HiForestPhoton-v7-noDuplicate.root";

  const TString PbPbMCFileName[] = {"/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton30to50_genPhotonPtCut40_allCent.root",
				    "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton50to80_genPhotonPtCut40_allCent.root",
				    "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root"};
  const Double_t PbPbMCweight[] = {32796./ 32796.,  21470./ 53876. ,  6462. / 58781. };
  
  TFile *outfile = new TFile("vertexReweightingHistogram_pthatweighted.root","RECREATE");

  TH1D *vertexHistoData[3];
  TH1D *vertexHistoMC[3];
  TH1I *centBinHistoData[3];
  TH1I *centBinHistoMC[3];

  vertexHistoData[0] = new TH1D("vertexHistoData_pp","",100,-15,15);
  vertexHistoData[1] = (TH1D*)vertexHistoData[0]->Clone("vertexHistoData_ppb");
  vertexHistoData[2] = (TH1D*)vertexHistoData[0]->Clone("vertexHistoData_pbpb");
  vertexHistoMC[0] = (TH1D*)vertexHistoData[0]->Clone("vertexHistoMC_pp");
  vertexHistoMC[1] = (TH1D*)vertexHistoData[0]->Clone("vertexHistoMC_ppb");
  vertexHistoMC[2] = (TH1D*)vertexHistoData[0]->Clone("vertexHistoMC_pbpb");

  centBinHistoData[0] = new TH1I("centBinHistoData_pp","",40,0,40);
  centBinHistoData[1] = (TH1I*)centBinHistoData[0]->Clone("centBinHistoData_ppb");
  centBinHistoData[2] = (TH1I*)centBinHistoData[0]->Clone("centBinHistoData_pbpb");
  centBinHistoMC[0] = (TH1I*)centBinHistoData[0]->Clone("centBinHistoMC_pp");
  centBinHistoMC[1] = (TH1I*)centBinHistoData[0]->Clone("centBinHistoMC_ppb");
  centBinHistoMC[2] = (TH1I*)centBinHistoData[0]->Clone("centBinHistoMC_pbpb");

  for(int sample = 0; sample<3; sample++)
  {
    HiForest *data;
    HiForest *mc[4];
    int numMC;
    Double_t weight[4];
    if(sample == 0) //pp
    {
      data = new HiForest(ppDataFileName,"ppData", cPP, false);
      numMC = 4;
      for(int i = 0; i<numMC; i++)
      {
	TString name = "ppMC";
	name+=i;
	mc[i] = new HiForest(ppMCFileName[i], name, cPP, true);
	weight[i] = ppMCweight[i];
      }
    }
    else if(sample == 1) //pPb
    {
      data = new HiForest(pPbDataFileName,"pPbData", cPPb, false);
      numMC = 4;
      for(int i = 0; i<numMC; i++)
      {
	TString name = "pPbMC";
	name+=i;
	mc[i] = new HiForest(pPbMCFileName[i], name, cPPb, true);
	weight[i] = pPbMCweight[i];	
      }
    }
    else if(sample == 2) // PbPb
    {
      data = new HiForest(PbPbDataFileName,"PbPbData", cPbPb, false);
      data->GetEnergyScaleTable((char*)"photonEnergyScaleTable_lowPt_v6.root");
      numMC = 3;
      for(int i = 0; i<numMC; i++)
      {
	TString name = "PbPbMC";
	name+=i;
	mc[i] = new HiForest(PbPbMCFileName[i], name, cPbPb, true);
	mc[i]->GetEnergyScaleTable((char*)"photonEnergyScaleTable_lowPt_v6.root");
	weight[i] = PbPbMCweight[i];
      }
    }
  
    data->LoadNoTrees(); // turns off trees I'm not using: loops faster
    data->hasPhotonTree = true;
    data->hasSkimTree = true; // required for selectEvent()
    data->hasEvtTree = true;
    for(int i = 0; i<numMC; i++)
    {
      mc[i]->LoadNoTrees();
      mc[i]->hasPhotonTree = true;
      mc[i]->hasSkimTree = true; // required for selectEvent()
      mc[i]->hasEvtTree = true;
    }

    //loop over events in each file
    loop(data, vertexHistoData[sample], centBinHistoData[sample], sample, 1);
    for(int i = 0; i < numMC; i++)
    {
      loop(mc[i], vertexHistoMC[sample], centBinHistoMC[sample], sample, weight[i]);
    }    
  }

  outfile->cd();
  for(int sample = 0; sample < 3; sample++)
  {
    vertexHistoData[sample]->Write();
    vertexHistoMC[sample]->Write();
    centBinHistoData[sample]->Write();
    centBinHistoMC[sample]->Write();
  }  
}

void loop(HiForest *forest, TH1D *hVertex, TH1I *hcentBin, int sample, Double_t weight)
{
  Long64_t nentries = forest->GetEntries();
  for(Long64_t jentry = 0; jentry<nentries; ++jentry)
  {
    if (jentry % 1000 == 0)  {
      printf("%lld / %lld\n",jentry,nentries);
    }
    
    forest->GetEntry(jentry);

    //event selection
    if( !forest->selectEvent() )
      continue;

    if( TMath::Abs(forest->evt.vz) > vzCut )
      continue;

    if(forest->photon.nPhotons == 0)
      continue;

    //loop over photons in the event
    //////////////////////////////////////////
    Float_t leadingCorrectedPt = 0;
    Int_t leadingIndex = -1;
    for(Int_t i = 0; i < forest->photon.nPhotons; ++i)
    {
      if(
	(TMath::Abs(forest->photon.eta[i]) > gammaEtaCut) ||
	(forest->isSpike(i)) ||
	(!(forest->isLoosePhoton(i)))
	)
	continue;
      
      Float_t correctedPt = forest->getCorrEt(i);
      if(correctedPt > leadingCorrectedPt)
      {
	leadingCorrectedPt = correctedPt;
	leadingIndex = i;
      }
    }
      
    if(leadingIndex == -1)
      continue;

    Float_t corrGPt = leadingCorrectedPt;
    Float_t gEta = forest->photon.eta[leadingIndex];
    //Float_t gPhi = forest->photon.phi[leadingIndex];

    Float_t cc4 = forest->photon.cc4[leadingIndex];
    Float_t cr4 = forest->photon.cr4[leadingIndex];
    Float_t ct4PtCut20 = forest->photon.ct4PtCut20[leadingIndex];
    Float_t hadronicOverEm = forest->photon.hadronicOverEm[leadingIndex];

    //Float_t sigmaIetaIeta = forest->photon.sigmaIetaIeta[leadingIndex];

    Float_t ecalRecHitSumEtConeDR04 = forest->photon.ecalRecHitSumEtConeDR04[leadingIndex];
    Float_t hcalTowerSumEtConeDR04 = forest->photon.hcalTowerSumEtConeDR04[leadingIndex];
    Float_t trkSumPtHollowConeDR04 = forest->photon.trkSumPtHollowConeDR04[leadingIndex];

    Int_t hiBin = forest->evt.hiBin;
    Float_t vz = forest->evt.vz;

    if( corrGPt < 40 || TMath::Abs(gEta) > 1.44 || hadronicOverEm > 0.1 )
      continue;

    if(sample != 2)
    {
      if(ecalRecHitSumEtConeDR04 > 4.2 || hcalTowerSumEtConeDR04 > 2.2 || trkSumPtHollowConeDR04 > 2.0)
      {
	continue;
      }
    } else {
      if(cc4 + cr4 + ct4PtCut20 > 1.0)
	continue;
    }
    hVertex->Fill(vz, weight);
    hcentBin->Fill(hiBin, weight);
  }
  printf("Done Sample.\n");
}


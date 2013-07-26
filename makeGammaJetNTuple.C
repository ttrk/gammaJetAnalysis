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


void makeGammaJetNTuple(TString inFile="/mnt/hadoop/cms/store/user/luck/PbPb2011_photons_MC/qcdAllPhoton50_allCent.root",
			collisionType cType = cPbPb,
			Bool_t montecarlo=true,
			TString outName="gammaJets_inclusive_dphi7pi8_PbPb2011_MC_allQCDPhoton50.root")
{
  TFile *outfile = new TFile(outName,"RECREATE");

  TString varList;
  varList = "gPt:gEta:gPhi:jPt:jEta:jPhi:HF:HFplusEta4:HFminusEta4:avgEta:dPhi:cc4:cr4:ct4PtCut20:hadronicOverEm:sigmaIetaIeta:run:r9:event:ecalRecHitSumEtConeDR04:hcalTowerSumEtConeDR04:trkSumPtHollowConeDR04";
  if(montecarlo)
    varList += ":genMomId:genCalIsoDR04:genTrkIsoDR04:ptHat:matchedGPt:matchedJPt:jentry";
  
  TNtuple *outTuple = new TNtuple("gammaJets","gammaJets",varList);
  
  HiForest *c = new HiForest(inFile, "Forest", cType, montecarlo);
  if(cType != cPbPb) //for some reason only PbPb is init when created
    c->InitTree();

  //loop over events in each file
  Long64_t nentries = c->GetEntries();
  for(Long64_t jentry = 0; jentry<nentries; ++jentry)
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
    for(Int_t i = 0; i<c->photon.nPhotons; ++i)
    {
      if(c->photon.pt[i] > leadingPt)
      {
	leadingPt = c->photon.pt[i];
	leadingIndex = i;
      }
    }
      
    if(leadingIndex == -1) 
      continue;

    //loop over 'away' jets
    for(Int_t i = 0; i<c->akPu3PF.nref; ++i)
    {
      if( TMath::Abs(c->akPu3PF.jteta[i]) > 3.0)
	continue;
	
      Double_t dphi =
	TMath::ACos(TMath::Cos(c->photon.phi[leadingIndex]
			       - c->akPu3PF.jtphi[i]));
      if( dphi < 7.*TMath::Pi()/8. )
	continue;
	
      Float_t gPt = c->photon.pt[leadingIndex];
      Float_t gEta = c->photon.eta[leadingIndex];
      Float_t gPhi = c->photon.phi[leadingIndex];
      Float_t jPt = c->akPu3PF.jtpt[i];
      Float_t jEta = c->akPu3PF.jteta[i];
      Float_t jPhi = c->akPu3PF.jtphi[i];
      Float_t HF = c->evt.hiHF;
      Float_t HFplusEta4 = c->evt.hiHFplusEta4;
      Float_t HFminusEta4 = c->evt.hiHFminusEta4;
      Float_t avgEta = (c->photon.eta[leadingIndex] + c->akPu3PF.jteta[i])/2.0;
      Float_t dPhi = dphi;
      Float_t cc4 = c->photon.cc4[leadingIndex];
      Float_t cr4 = c->photon.cr4[leadingIndex];
      Float_t ct4PtCut20 = c->photon.ct4PtCut20[leadingIndex];
      Float_t hadronicOverEm = c->photon.hadronicOverEm[leadingIndex];
      Float_t sigmaIetaIeta = c->photon.sigmaIetaIeta[leadingIndex];
      Float_t run = c->evt.run;
      Float_t r9 = c->photon.r9[leadingIndex];
      Float_t event = c->photon.event;
      Float_t ecalRecHitSumEtConeDR04 = c->photon.ecalRecHitSumEtConeDR04[leadingIndex];
      Float_t hcalTowerSumEtConeDR04 = c->photon.hcalTowerSumEtConeDR04[leadingIndex];
      Float_t trkSumPtHollowConeDR04 = c->photon.trkSumPtHollowConeDR04[leadingIndex];

      if(!montecarlo)
      {
	Float_t x[] = {gPt,
		       gEta,
		       gPhi,
		       jPt,
		       jEta,
		       jPhi,
		       HF,
		       HFplusEta4,
		       HFminusEta4,
		       avgEta,
		       dPhi,
		       cc4,
		       cr4,
		       ct4PtCut20,
		       hadronicOverEm,
		       sigmaIetaIeta,
		       run,
		       r9,
		       event,
		       ecalRecHitSumEtConeDR04,
		       hcalTowerSumEtConeDR04,
		       trkSumPtHollowConeDR04};
	outTuple->Fill(x);
      }
      else
      {
	Float_t genMomId = c->photon.genMomId[leadingIndex];
	Float_t genCalIsoDR04 = c->photon.genCalIsoDR04[leadingIndex];
	Float_t genTrkIsoDR04 = c->photon.genTrkIsoDR04[leadingIndex];
	Float_t ptHat = c->photon.ptHat;
	Float_t matchedGPt = c->photon.genMatchedPt[leadingIndex];
	Float_t matchedJPt = c->akPu3PF.matchedPt[i];

	Float_t x[] = {gPt,
		       gEta,
		       gPhi,
		       jPt,
		       jEta,
		       jPhi,
		       HF,
		       HFplusEta4,
		       HFminusEta4,
		       avgEta,
		       dPhi,
		       cc4,
		       cr4,
		       ct4PtCut20,
		       hadronicOverEm,
		       sigmaIetaIeta,
		       run,
		       r9,
		       event,
		       ecalRecHitSumEtConeDR04,
		       hcalTowerSumEtConeDR04,
		       trkSumPtHollowConeDR04,
		       // mc stuff
		       genMomId,
		       genCalIsoDR04,
		       genTrkIsoDR04,
		       ptHat,
		       matchedGPt,
		       matchedJPt,
		       jentry};
	outTuple->Fill(x);
      }
    }

  }

  outfile->cd();
  outTuple->Write();
  outfile->Close();

  printf("Done.\n");
}


int main()
{
  makeGammaJetNTuple();
  return 0;
}

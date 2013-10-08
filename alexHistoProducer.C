#include "fitResult.h"
#include "alexGammaSkim.h"
#include "commonUtility.h"
//#include "CutAndBinCollection2012.h"
#include "histogramProducer/corrFunctionJetTrk.h"
#include "TDatime.h"
#include "TFile.h"
#include "TCanvas.h"

GjSpectra* nullGj;

void gammaTrkSingle(     GjSpectra* gjSpec_=nullGj,
			 TTree *dataTree=0,
			 corrFunctionTrk* corr_=0,
			 float purity=0,
			 sampleType collision_=kHIDATA,
			 TString var_ = "",
			 TCut cut_ ="",
			 TString theWeight="",
			 TCut phoCandCut_="",
			 TCut phoDecayCut_="",
			 TH1D* hTemplate_ =0,
			 TString outName="");

void alexHistoProducer(sampleType collision, float photonPtThr=60, float photonPtThrUp=9999, float jetPtThr=30, int icent =1)
{
  TString stringSampleType = getSampleName(collision);  
  TDatime* date = new TDatime();
  TString  outName=  Form("photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr%d_%d.root",stringSampleType.Data(),(int)photonPtThr, (int)photonPtThrUp, (int)jetPtThr,  date->GetDate());
  delete date;

  // define cuts
  const int nCentBin1 = 4;
  double centBin1[nCentBin1+1] = {0,4,12,20,40};
  int lowerCent =0;
  int upperCent =0;
  TCut centCut;
  if ( (collision ==kHIDATA) || (collision==kHIMC) )   {
    lowerCent = centBin1[icent-1];
    upperCent = centBin1[icent]-1;
    if ( icent > 9999) {
      lowerCent = ((icent/100)%100)/2.5;
      upperCent =  (icent%100)/2.5 -1;
    }   
    centCut = Form("hiBin >= %d && hiBin<= %d",lowerCent,upperCent);
  }
  else if (  (collision ==kPPDATA) || (collision==kPPMC)  ){  // if it's pp 
    centCut = "(1==1)";
    //    icent = 7;   // for pp, centrality is set as the smearing 
  }
  else { // pPb
    //centCut = Form( "hf4Sum > %f && hf4Sum <= %f", (float)centBinPa[icent-1], (float)centBinPa[icent]);
    centCut = "(1==1)";
  }

  TCut photonEtaCut = "abs(photonTree.eta) < 1.44";
  TCut jetEtaCut = "abs(jetTree.eta) < 1.6";
  TCut jetPtCut = "jetTree.pt > 30";
  TCut jetCut = jetEtaCut && jetPtCut;
  TCut jetDphiCut = "jetTree.dPhi > 2.74889357189106898"; // 7pi/8
  TCut jetCutDphi = jetCut && jetDphiCut;
  //TString jetWeight = "photonTree.mcweight";
  TString jetWeight = "";
  if  ( ( collision == kHIMC ) || (collision == kPPMC) || (collision == kPAMC))  
    jetWeight = "mcweight";
  TCut photonPtCut = Form("photonTree.corrPt>%f && photonTree.corrPt<%f", photonPtThr, photonPtThrUp  );
  TCut isoCut;
  if ( (collision==kHIMC) || (collision==kHIDATA) ) {
    isoCut = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1";
  } else {
    isoCut = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1";
  }
  
  TCut genCut = "genCalIsoDR04<5 && abs(genMomId)<=22";
  TCut sbCut = "(cc4+cr4+ct4PtCut20>10) && (cc4+cr4+ct4PtCut20<20) && hadronicOverEm<0.1";

  TCut candidateCut = "sigmaIetaIeta<0.01";
  if  ( ( collision == kHIMC ) || (collision == kPPMC) || (collision == kPAMC))  
    candidateCut = candidateCut && "genIso<5 && abs(genMomId)<=22";
  TCut decayCut = "(sigmaIetaIeta>0.011) && (sigmaIetaIeta<0.017)";

  TCut dataCandidateCut = isoCut && photonEtaCut && photonPtCut && centCut;
  TCut sidebandCut =  sbCut && photonEtaCut && photonPtCut && centCut;
  TCut mcSignalCut = dataCandidateCut && genCut;

  
  // load data
  TString DATA_FILE;
  TString MC_FILE;
  if ( collision == kHIDATA)
  {
    DATA_FILE = "gammaJets_PbPb_Data.root";
    MC_FILE = "gammaJets_PbPb_MC_allQCDPhoton.root";
  }
  else if ( collision == kPADATA)
  {
    DATA_FILE = "gammaJets_pA_Data.root";
    MC_FILE = "gammaJets_pA_MC_allQCDPhoton.root";
  }
  else if ( collision == kPPDATA) {
    DATA_FILE = "gammaJets_pp_Data.root";
    MC_FILE = "gammaJets_pp_MC_PUallQCDPhoton.root";
  }
  else if ( collision == kHIMC)
  {
    MC_FILE = "gammaJets_PbPb_MC_allQCDPhoton.root";
    DATA_FILE = MC_FILE;
  }
  else if ( collision == kPAMC)
  {
    MC_FILE = "gammaJets_pA_MC_allQCDPhoton.root";
    DATA_FILE = MC_FILE;
  }
  else if ( collision == kPPMC) {
    MC_FILE = "gammaJets_pp_MC_PUallQCDPhoton.root";
    DATA_FILE = MC_FILE;
  }


  
  TFile *dataFile = TFile::Open(DATA_FILE);
  TTree *dataTree = (TTree*)dataFile->Get("photonTree");
  dataTree->AddFriend("jetTree",DATA_FILE);
  if ( collision == kHIDATA )
  {
    dataTree->AddFriend("mJetTree",DATA_FILE);
  }

  TFile *mcFile = TFile::Open(MC_FILE);
  TTree *mcTree = (TTree*)mcFile->Get("photonTree");

  Float_t purity = 1;
  if ( collision == kHIDATA || collision == kHIDATA || collision == kHIDATA )
  {
    fitResult fitr = getPurity(dataTree, mcTree,
			       dataCandidateCut, sidebandCut,
			       mcSignalCut, 0.0,
			       0.0, 0.00999);
    purity = fitr.purity;
  }

  GjSpectra* gSpec = new GjSpectra();
  gSpec->init(Form("icent%d",(int)icent) );
  dataTree->Project(gSpec->hPtPhoCand->GetName(),  "corrPt", candidateCut, "")  ;
  dataTree->Project(gSpec->hPtPhoDecay->GetName(), "corrPt", decayCut, "") ;
  
  // Obtain background subtracted spectra
  
  float candInt = gSpec->hPtPhoCand->Integral();
  float candDecay = gSpec->hPtPhoDecay->Integral();
  gSpec->hPtPhoSig->Reset();
  gSpec->hPtPhoSig->Add(gSpec->hPtPhoCand);
  gSpec->hPtPhoSig->Add(gSpec->hPtPhoDecay, -(1. - purity) * candInt / candDecay);
  gSpec->hPtPhoSig->Scale(1./purity ) ;
  
  TFile *outf = TFile::Open(Form("ffFiles/%s",outName.Data()),"update");
  gSpec->hPtPhoCand->Write();
  gSpec->hPtPhoDecay->Write();
  gSpec->hPtPhoSig->Write();
  outf->Close();

  TH1D* hJetDphi = new TH1D(Form("jetDphi_icent%d",icent),
			    ";#Delta#phi_{Jet,#gamma} ;dN/d#Delta#phi",20,0,3.141592);
  corrFunctionTrk* cJetDphi = new corrFunctionTrk();
  TString varJetDphi         = Form("dPhi");

  gammaTrkSingle( gSpec,  dataTree, cJetDphi,  purity, 
		  collision, varJetDphi, jetCut, jetWeight,
		  candidateCut, decayCut,  hJetDphi, outName);
  
  TH1D* hJetPt = new TH1D(Form("jetPt_icent%d",icent),
			  ";Jet p_{T} (GeV) ;dN/dp_{T} (GeV^{-1})",280, 20,300);
  corrFunctionTrk* cJetPt = new corrFunctionTrk();
  TString varJetPt         = Form("pt");
  
  gammaTrkSingle( gSpec,  dataTree, cJetPt,  purity, 
		  collision, varJetPt, jetCutDphi, jetWeight,
		  candidateCut, decayCut,  hJetPt, outName);
  
  const int nJetIaaBin = 7;
  double jetIaaBin[nJetIaaBin+1] = {30,40,50,60,80,100,120,200};
  TH1D* hJetPtForIaa = new TH1D(Form("jetPtForIaa_icent%d",icent),
				";Jet p_{T} (GeV) ;dN/dp_{T} (GeV^{-1})",nJetIaaBin, jetIaaBin);
  corrFunctionTrk* cJetIaaPt = new corrFunctionTrk();
  gammaTrkSingle( gSpec,  dataTree, cJetIaaPt,  purity,
                  collision, varJetPt, jetCutDphi, jetWeight,
                  candidateCut, decayCut,  hJetPtForIaa, outName);
  
  TH1D* hJetXjg = new TH1D(Form("xjg_icent%d",icent),
			   ";p_{T}^{Jet}/p_{T}^{#gamma}  ; ",400,0,5);
  corrFunctionTrk* cJetXjg = new corrFunctionTrk();
  TString varJetXjg         = Form("pt/photonTree.pt");
  
  gammaTrkSingle( gSpec,  dataTree, cJetXjg,  purity, 
		  collision, varJetXjg, jetCutDphi, jetWeight,
		  candidateCut, decayCut,  hJetXjg, outName);
  

}


void gammaTrkSingle(GjSpectra* gSpec,  TTree* dataTree,      corrFunctionTrk* corr, 
		    float purity,      sampleType collision, TString var,     
		    TCut cut,          TString theWeight,    TCut candidateCut,   TCut decayCut,
		    TH1D* hTemplate,   TString outfName)
{
  TH1::SetDefaultSumw2();
  
  TCanvas* c1 = new TCanvas(Form("canvas_%s",hTemplate->GetName()),"",800,650);
  makeMultiPanelCanvas(c1,2,2,0.0,0.0,0.2,0.15,0.02);
  c1->cd(1);
  corr->init(gSpec, collision, purity, hTemplate);
  //gamma-jet candidates
  dataTree->Project(corr->Func[kPhoCand][kTrkRaw]->GetName(),
		    "jetTree."+var,  theWeight*(candidateCut  && cut));
  //gamma-jets mixed from MB
  if ( collision == kHIDATA )   {
    dataTree->Project(corr->Func[kPhoCand][kTrkBkg]->GetName(),
		      "mJetTree."+var,  theWeight*(candidateCut  && cut));
  }
  //gamma-jets from decays
  if ( (collision==kHIDATA) || (collision==kPPDATA) || (collision==kPADATA) ) {
    dataTree->Project(corr->Func[kPhoDecay][kTrkRaw]->GetName(),
		      "jetTree."+var, theWeight*(decayCut && cut));
    // gamma-jets mixed from MB and decays
    if ( collision == kHIDATA )   {
      dataTree->Project(corr->Func[kPhoDecay][kTrkBkg]->GetName(),
			"mJetTree."+var, theWeight*(candidateCut  && cut));
    }
  }
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkRaw]); 
  TH1ScaleByWidth( corr->Func[kPhoCand][kTrkBkg]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkRaw]);
  TH1ScaleByWidth( corr->Func[kPhoDecay][kTrkBkg]);
  
  corr->calCorr();
  c1->cd(1); 
  handsomeTH1(corr->Func[kPhoCand][kTrkRaw],1);
  handsomeTH1(corr->Func[kPhoCand][kTrkBkg],1);
  handsomeTH1(corr->Func[kPhoCand][kTrkSig],2);
  corr->Func[kPhoCand][kTrkRaw]->Draw();
  corr->Func[kPhoCand][kTrkBkg]->Draw("same hist");
  corr->Func[kPhoCand][kTrkSig]->Draw("same");
  gPad->SetLogy();

  c1->cd(2); 
  handsomeTH1(corr->Func[kPhoDecay][kTrkRaw],1);
  handsomeTH1(corr->Func[kPhoDecay][kTrkBkg],1);
  handsomeTH1(corr->Func[kPhoDecay][kTrkSig],4);
  corr->Func[kPhoDecay][kTrkRaw]->Draw();
  corr->Func[kPhoDecay][kTrkBkg]->Draw("same hist");
  corr->Func[kPhoDecay][kTrkSig]->Draw("same");
  gPad->SetLogy();
  
  c1->cd(3);
  corr->Func[kPhoCand][kTrkSig]->Draw();
  corr->Func[kPhoDecay][kTrkSig]->Draw("same");

  c1->cd(4);
  handsomeTH1(corr->Func[kPhoSig][kTrkSig],1);
  corr->Func[kPhoSig][kTrkSig]->Draw();
  //c1->SaveAs(Form("gifs/%s_%s.gif",outfName.Data(),c1->GetName()) );
  
  TFile *outf = TFile::Open(Form("ffFiles/%s",outfName.Data()),"update");
  corr->Func[kPhoCand][kTrkRaw]->Write();
  corr->Func[kPhoCand][kTrkBkg]->Write();
  corr->Func[kPhoCand][kTrkSig]->Write();
  corr->Func[kPhoDecay][kTrkRaw]->Write();
  corr->Func[kPhoDecay][kTrkBkg]->Write();
  corr->Func[kPhoDecay][kTrkSig]->Write();
  corr->Func[kPhoSig][kTrkRaw]->Write();
  corr->Func[kPhoSig][kTrkBkg]->Write();
  corr->Func[kPhoSig][kTrkSig]->Write();
  
  outf->Close();  
}

int main(int argc, char *argv[])
{
  if(argc != 6) return 1;
  alexHistoProducer((sampleType)atoi(argv[1]),atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]));
  return 0;
}

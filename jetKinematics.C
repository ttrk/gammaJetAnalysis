#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>
#include "commonUtility.h"

using namespace std;
//last forward run is 211256

void jetKinematics()
{
  TH1::SetDefaultSumw2();
  
  TString DATA_FILE[3];
  TString MC_FILE[3];
  TString LABEL[3];
  TCut anaCut[3];

//pp
  DATA_FILE[0] = "gammaJets_pp_Data.root";
  MC_FILE[0] = "gammaJets_pp_MC_PUallQCDPhoton.root";
  LABEL[0] = "pp #sqrt{s}_{_{NN}}=2.76 TeV";
  anaCut[0] = "ecalRecHitSumEtConeDR04 < 4.2  &&  hcalTowerSumEtConeDR04 < 2.2  &&  trkSumPtHollowConeDR04 < 2 && hadronicOverEm<0.1 && photonTree.pt>40 && jetTree.pt>30";
  

//PbPb
  DATA_FILE[1] = "gammaJets_PbPb_Data.root";
  MC_FILE[1] = "gammaJets_PbPb_MC_allQCDPhoton.root";
  LABEL[1] = "PbPb #sqrt{s}_{_{NN}}=2.76 TeV";
  anaCut[1] = "(cc4+cr4+ct4PtCut20<1) && hadronicOverEm<0.1 && photonTree.pt>40 && jetTree.pt>30";

//pPb
  DATA_FILE[2] = "gammaJets_pA_Data.root";
  MC_FILE[2] = "gammaJets_pA_MC_allQCDPhoton.root";
  LABEL[2] = "pPb #sqrt{s}_{_{NN}}=5.02 TeV";
  anaCut[2] = anaCut[0];

  TString name[3] = {"pp", "ppb", "pbpb"};

  TCanvas *c[3];

  for(int sample = 1; sample<3; sample++)
  {
    TFile *file[2];
    file[0] = TFile::Open(DATA_FILE[sample]);
    file[1] = TFile::Open(MC_FILE[sample]);

    TTree *jet[2];
    jet[0] = (TTree*)file[0]->Get("jetTree");
    jet[0]->AddFriend("photonTree",DATA_FILE[sample].Data());
    jet[1] = (TTree*)file[1]->Get("jetTree");
    jet[1]->AddFriend("photonTree",MC_FILE[sample].Data());

    TH1D *pt[2];
    TH1D *eta[2];
    TH1D *phi[2];

    pt[0] = new TH1D("pt0", ";p_{T}^{jet} (GeV)", 50, 20, 300);
    pt[1] = (TH1D*)pt[0]->Clone("pt1");

    eta[0] = new TH1D("eta0", ";#eta^{jet}", 25, -1.6, 1.6);
    eta[1] = (TH1D*)eta[0]->Clone("eta1");

    phi[0] = new TH1D("phi0", ";#phi^{jet}", 25, -TMath::Pi(), TMath::Pi());
    phi[1] = (TH1D*)phi[0]->Clone("phi1");

    int num;
    num = jet[0]->Project("pt0", "jetTree.pt",anaCut[sample]);
    printf("%d\n", num);
    pt[0]->Scale(1./pt[0]->Integral());
    num = jet[0]->Project("eta0", "jetTree.eta",anaCut[sample]);
    printf("%d\n", num);
    eta[0]->Scale(1./eta[0]->Integral());
    num = jet[0]->Project("phi0", "jetTree.phi",anaCut[sample]);
    printf("%d\n", num);
    phi[0]->Scale(1./phi[0]->Integral());

    
    num = jet[1]->Project("pt1", "jetTree.pt","mcweight"*anaCut[sample]);
    printf("%d\n", num);
    pt[1]->Scale(1./pt[1]->Integral());
    num = jet[1]->Project("eta1", "jetTree.eta","mcweight"*anaCut[sample]);
    printf("%d\n", num);
    eta[1]->Scale(1./eta[1]->Integral());
    num = jet[1]->Project("phi1", "jetTree.phi","mcweight"*anaCut[sample]);
    printf("%d\n", num);
    phi[1]->Scale(1./phi[1]->Integral());


    c[sample] = new TCanvas(name[sample],"",1500,500);
    c[sample]->Divide(3,1);
    c[sample]->cd(1);
    //pt[0]->SetMinimum(0);
    pt[0]->SetMaximum(pt[0]->GetMaximum()*1.5);
    pt[0]->DrawClone("p");
    pt[1]->SetLineColor(kBlue);
    pt[1]->DrawClone("hist same");
    //c[0]->SetLogy();

    TLegend *leg = new TLegend(0.5, 0.75, 0.7, 0.90, LABEL[sample].Data());
    leg->SetFillColor(0);
    leg->SetTextSize(18);
    leg->AddEntry(pt[0],"Data","p");
    leg->AddEntry(pt[1],"MC","l");
    leg->Draw();

    c[sample]->cd(2);
    eta[0]->SetMinimum(0);
    eta[0]->SetMaximum(eta[0]->GetMaximum()*1.5);
    eta[0]->DrawClone("p");
    eta[1]->SetLineColor(kBlue);
    eta[1]->DrawClone("hist same");
    leg->Draw();

    c[sample]->cd(3);
    phi[0]->SetMinimum(0);
    phi[0]->SetMaximum(phi[0]->GetMaximum()*1.5);
    phi[0]->DrawClone("p");
    phi[1]->SetLineColor(kBlue);
    phi[1]->DrawClone("hist same");
    leg->Draw();

    c[sample]->SaveAs("basicKinematics_"+name[sample]+"_jet.pdf");
    
  }

}

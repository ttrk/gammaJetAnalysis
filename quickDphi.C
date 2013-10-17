void quickDphi()
{
  TH1::SetDefaultSumw2();
  
  TFile *pAFile = TFile::Open("gammaJets_pA_Data.root");
  TTree *jets = (TTree*)pAFile->Get("jetTree");
  jets->AddFriend("photonTree","gammaJets_pA_Data.root");

  TH1D *hfp20 = new TH1D("hfp20",";#Delta #phi_{J#gamma}", 50, 0, TMath::Pi());
  TH1D *hfl20 = (TH1D*)hfp20->Clone("hfl20");

  TCut anaCut = "photonTree.hadronicOverEm<0.1 && abs(photonTree.eta)<1.44 && abs(jetTree.eta)<1.6 && jetTree.pt>30 && photonTree.ecalRecHitSumEtConeDR04 <4.2  &&  photonTree.hcalTowerSumEtConeDR04 < 2.2  &&  photonTree.trkSumPtHollowConeDR04 < 2";

  // jets->Project("hfl20","dPhi",anaCut&&"(photonTree.HFplusEta4+photonTree.HFminusEta4 < 20)");
  // jets->Project("hfp20","dPhi",anaCut&&"(photonTree.HFplusEta4+photonTree.HFminusEta4 > 20)");
  jets->Project("hfl20","dPhi",anaCut&&"(photonTree.pt > 40)");
  jets->Project("hfp20","dPhi",anaCut&&"(photonTree.pt > 60)");
  
  hfp20->Scale(1./hfp20->GetEntries());
  hfl20->Scale(1./hfl20->GetEntries());

  TCanvas *c1 = new TCanvas();
  c1->SetLogy();

  // hfp20->Draw();
  // hfp20->GetXaxis()->CenterTitle();
  // hfl20->SetMarkerColor(kBlue);
  // hfl20->SetLineColor(kBlue);
  // hfl20->Draw("same");

  // TLegend *leg = new TLegend(0.15,0.5,0.5,0.8);
  // leg->SetFillColor(0);
  // // leg->AddEntry(hfp20,"E^{HF |#eta|>4} > 20","l");
  // // leg->AddEntry(hfl20,"E^{HF |#eta|>4} < 20","l");
  // leg->AddEntry(hfp20,"#gamma p_{T} > 60GeV","l");
  // leg->AddEntry(hfl20,"#gamma p_{T} > 40GeV","l");
  // leg->Draw();

  TH1D *ratio = (TH1D*)hfp20->Clone("ratio");
  //ratio->SetYTitle("(E^{HF |#eta|>4} > 20)/(E^{HF |#eta|>4} < 20)");
  ratio->Divide(hfp20,hfl20,1,1);
  ratio->Draw();
}

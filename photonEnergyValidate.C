#include "../hiForestV3/hiForest.h"
#include "CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void photonEnergyValidate   (sampleType collision = kHIMC) {
  TH1::SetDefaultSumw2(); 
  
  TFile* f = new TFile("photonEnergyScaleTable_lowPt_v6.root");
  TF1* curve[2][4];  // [ conversion 0 or 1 ] [ centrality bin 1,2,3] 
  for ( int icent = 1 ; icent<=3 ; icent++) {
    curve[0][icent] = (TF1*)f->Get(Form("fit_hscale_r9gt94_%d",icent));   // Not converted
    curve[1][icent] = (TF1*)f->Get(Form("fit_hscale_r9lt94_%d",icent));  // Converted
    curve[1][icent]->SetLineStyle(7);
  }
  TH1D* htemp = new TH1D("htemp",";p_{T}^{#gamma} (GeV); Residual correction",200,35,200);
  
  TCanvas* c1 = new TCanvas("c1","",500,500);

  handsomeTH1(htemp,0);
  htemp->SetAxisRange(0.97,1.12,"Y");
  htemp->DrawCopy();
  
  for (int icent = 1 ;icent<=3 ; icent++) {
    curve[0][icent]->Draw("same");
    curve[1][icent]->Draw("same");
    //    onSun(35,1,200,1);
  }
  TLegend *l0 =  new TLegend(0.4910859,0.5132576,1,0.7102273,NULL,"brNDC");
  easyLeg(l0,"r9 > 0.94 : Not Conv");
  l0->AddEntry(curve[0][1],"0-10%","l");
  l0->AddEntry(curve[0][2],"10-30%","l");
  l0->AddEntry(curve[0][3],"30-100%","l");
  l0->Draw();
  
  TLegend *l1 = new TLegend(0.4910859,0.7443182,1,0.9318182,NULL,"brNDC");
   easyLeg(l1,"r9 < 0.94 : Conv");
  l1->AddEntry(curve[1][1],"0-10%","l");
  l1->AddEntry(curve[1][2],"10-30%","l");
  l1->AddEntry(curve[1][3],"30-100%","l");
  l1->Draw();
  

       

}

#include "../HiForestAnalysis/hiForest.h"
#include "../gammaJetAnalysis/CutAndBinCollection2012.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <iostream>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TCut.h>
#include <TRandom3.h>

void relative_smearing(int fixOpt=1){
    TH1::SetDefaultSumw2();

    gStyle -> SetOptFit(0);
    gStyle -> SetOptStat(0);
    gStyle -> SetTitleYSize(0.065);
    gStyle -> SetTitleXSize(0.065);

    TLegend *l2 = new TLegend(0.111127,0.7241099,0.8205091,0.8773607,NULL,"brNDC");
    if(fixOpt==0) easyLeg(l2,"fixed");
    else easyLeg(l2," NOT fixed");
    //
    // cuts!!!
    //  
    TCut centCut0 = "";//pp
    TCut centCut1 = "cBin > 0 && cBin < 4";//HI 0-10 %
    TCut centCut2 = "cBin >= 4 && cBin < 12"; // HI 10-30 %
    TCut centCut3 = "cBin >= 12 && cBin < 20";// HI 30-50 %
    TCut centCut4 = "cBin >= 20";// HI 50-100 %

    TCut totalCut = "photonEt>40 && abs(genMomId)<=22 && (abs(eta) < 1.6) && (dphi > 7*3.141592/8.0)"; 

    multiTreeUtil* yJetpp = new multiTreeUtil();
    multiTreeUtil* yJetpb = new multiTreeUtil();
    // PbPb
    yJetpb -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", "yJet", totalCut, 32796./32796);
    yJetpb -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", "yJet", totalCut, 21470./53876);
    yJetpb -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", "yJet",totalCut, 6462./58781);
    //pp
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 29329. / 29329.);
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 8098. / 87988.);
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 1680. / 96756.);
    yJetpp -> addFile("/home/jazzitup/forestFiles/yskimmedFiles/yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root", "yJet",totalCut, 438.   / 90972.);

    yJetpb -> AddFriend("tgj");
    yJetpp -> AddFriend("tgj");

    const int nbin = 13;
    double ptbin[nbin];
    ptbin[0]=0.0;
    ptbin[1]=10.0;
    ptbin[2]=20.0;
    ptbin[3]=30.0;
    ptbin[4]=40.0;
    ptbin[5]=50.0;
    ptbin[6]=60.0;
    ptbin[7]=70.0;
    ptbin[8]=80.0;
    ptbin[9]=90.0;
    ptbin[10]=100.0;
    ptbin[11]=140.0;
    ptbin[12]=180.0;
    ptbin[13]=220.0;

//
// gen photon ratio
//
    TCanvas* cphoton = new TCanvas("cphoton", "", 1200,300);
    makeMultiPanelCanvas(cphoton, 5, 1);
    
    TH1D* hphoton[5];
    for(int icoll=0; icoll<5; icoll++){
        hphoton[icoll] = new TH1D(Form("hphoton%d",icoll),"; p_{T}^{#gamma} (GeV) ; Normalized Entries", nbin, ptbin);
    }

    yJetpp -> Draw2(hphoton[0], "tgj.genPhotonEt", "", "");
    yJetpb -> Draw2(hphoton[1], "tgj.genPhotonEt", centCut1, "");
    yJetpb -> Draw2(hphoton[2], "tgj.genPhotonEt", centCut2, "");
    yJetpb -> Draw2(hphoton[3], "tgj.genPhotonEt", centCut3, "");
    yJetpb -> Draw2(hphoton[4], "tgj.genPhotonEt", centCut4, "");

    double norm_pho[5];
    for(int icoll=0; icoll<5; icoll++){
        norm_pho[icoll] = hphoton[icoll]->Integral(); 
        hphoton[icoll] -> Scale(1./norm_pho[icoll]);
        cphoton -> cd(icoll+1);
        hphoton[icoll] -> Draw(); 
    }

    TCanvas* cpho = new TCanvas("cpho", "", 950, 300);
    makeMultiPanelCanvas(cpho, 4, 1);
    TH1D* hpho_ratio[5];
    for(int icoll=0; icoll<5; icoll++){
        hpho_ratio[icoll]= (TH1D*) hphoton[icoll] -> Clone(Form("hpho_ratio%d",icoll));
    }

    for(int icoll=1; icoll<5; icoll++){
        cpho -> cd(icoll);
        hpho_ratio[icoll] -> Divide(hpho_ratio[0]);
        hpho_ratio[icoll] -> SetYTitle("gen photon p_{T}^{PbPb}/p_{T}^{pp}");
        hpho_ratio[icoll] -> SetAxisRange(0.6,1.4,"Y"); 
        hpho_ratio[icoll] -> Draw(); 
        jumSun(0,1,220,1,2);
        jumSun(30,0.6,30,1.4,1);
    }
   
//
// genJet
//

    TCanvas* cGenPt = new TCanvas("cGenPt", "", 900, 300);
    makeMultiPanelCanvas(cGenPt, 4, 1);

    TH1D* hGenPt[5];
    TH1D* hGenPt_ratio[5];
    for(int icoll=0; icoll<5; icoll++){
        hGenPt[icoll] = new TH1D(Form("hGenPt%d",icoll),"; p_{T}^{GenJet} (GeV) ; Normalized Entries", nbin, ptbin);
    }

    yJetpp -> Draw2(hGenPt[0], "refPt", "", "");
    yJetpb -> Draw2(hGenPt[1], "refPt", centCut1, "");
    yJetpb -> Draw2(hGenPt[2], "refPt", centCut2, "");
    yJetpb -> Draw2(hGenPt[3], "refPt", centCut3, "");
    yJetpb -> Draw2(hGenPt[4], "refPt", centCut4, "");

    TLegend* l1 = new TLegend(0.3014874,0.5593653,0.6951945,0.9195046,NULL,"brNDC");
    l1 -> SetFillColor(0);
    l1 -> SetBorderSize(0);    
    cGenPt -> cd(1);
    double norm[5];
    for(int icoll=0; icoll<5; icoll++){
        norm[icoll] = hGenPt[icoll]->Integral(); 
        hGenPt[icoll] -> Scale(1./norm[icoll]);

        handsomeTH1(hGenPt[icoll], icoll+1, 0.5);
        if(icoll==0) {
            hGenPt[icoll] -> Draw();
        } else {
            hGenPt[icoll] -> Draw("same");  
            hGenPt_ratio[icoll] = (TH1D*) hGenPt[icoll] -> Clone(Form("hGenPt_ratio%d",icoll));
        }
    }

    l1 -> AddEntry(hGenPt[0], "pp");
    l1 -> AddEntry(hGenPt[1], "PbPb 0-10%");
    l1 -> AddEntry(hGenPt[2], "PbPb 10-30%");
    l1 -> AddEntry(hGenPt[3], "PbPb 30-50%");
    l1 -> AddEntry(hGenPt[4], "PbPb 50-100%");
    l1 -> Draw();

    for(int icoll=1; icoll<5; icoll++){
        cGenPt -> cd(icoll);
        hGenPt_ratio[icoll] -> Divide(hGenPt[0]);
        hGenPt_ratio[icoll] -> Draw();
        hGenPt_ratio[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{pp}");
        hGenPt_ratio[icoll] -> SetAxisRange(0.4,1.4,"Y");
        jumSun(0,1,220,1,2);
        jumSun(30,0.7,30,1.8,1);
    }

//
//Reco Jet
//

    TCanvas* cRecoPt = new TCanvas("cRecoPt", "", 400, 800);
    cRecoPt -> Divide(1,2);

    TH1D* hRecoPt[5];
    TH1D* hRecoPt_ratio[5];
    for(int icoll=0; icoll<5; icoll++){
        hRecoPt[icoll] = new TH1D(Form("hRecoPt%d", icoll),"; p_{T}^{RecoJet} (GeV) ; Normalized Entries", nbin, ptbin);
    }

    yJetpp -> Draw2(hRecoPt[0], "pt","refPt>0", "");
    yJetpb -> Draw2(hRecoPt[1], "pt","refPt>0" && centCut1, "");
    yJetpb -> Draw2(hRecoPt[2], "pt","refPt>0" && centCut2, "");
    yJetpb -> Draw2(hRecoPt[3], "pt","refPt>0" && centCut3, "");
    yJetpb -> Draw2(hRecoPt[4], "pt","refPt>0" && centCut4, "");

    cRecoPt -> cd(1);
    for(int icoll=0; icoll<5; icoll++){
        handsomeTH1(hRecoPt[icoll], icoll+1, 0.5);
        hRecoPt[icoll] -> Scale(1./norm[icoll]); //hRecoPt[icoll]->Integral());
        hRecoPt[icoll] -> SetLineColor(icoll+1);
        if(icoll==0) {
            hRecoPt[icoll] -> Draw();
        } else {
            hRecoPt[icoll] -> Draw("same");
            hRecoPt_ratio[icoll] = (TH1D*) hRecoPt[icoll] -> Clone(Form("hRecoPt_ratio%d",icoll));
        }
    }
    l1 -> Draw();

    cRecoPt -> cd(2);
    for(int icoll=1; icoll<5; icoll++){
        hRecoPt_ratio[icoll] -> Divide(hRecoPt[0]);
        if(icoll==1){ 
            hRecoPt_ratio[icoll] -> Draw();
            hRecoPt_ratio[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{pp}");
        } else hRecoPt_ratio[icoll] -> Draw("same");
    }
    jumSun(0,1,220,1,2);
    jumSun(30,0.7,30,1.8,1);

//
// reco/gen ratio
//

    TCanvas* crg = new TCanvas("crg", "", 950, 300);
    makeMultiPanelCanvas(crg, 4, 1);
    TH1D* hrg[5];
    for(int icoll=0; icoll<5; icoll++){
        hrg[icoll]= (TH1D*) hRecoPt[icoll] -> Clone(Form("hrg%d",icoll));
    }

    for(int icoll=1; icoll<5; icoll++){
        crg -> cd(icoll);
        hrg[icoll] -> Divide(hRecoPt[0]);
        hrg[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{pp}");
        hrg[icoll] -> SetAxisRange(0.7,1.8,"Y"); 
        hrg[icoll] -> Draw(); 
        jumSun(0,1,220,1,2);
        jumSun(30,0.7,30,1.8,1);
    }
    crg -> cd(1);
    l1 -> Draw();
    
//
//smearing
//
    
    double sigma[5]; 
    double cc[5]; 
    double ss[5]; 
    double nn[5]; 

    cc[0] =0.056762;
    ss[0] =0.808114;
    nn[0] =0.000244992;
    if(fixOpt==0) {
        cc[1] =0.056762;
        ss[1] =0.808114;
        nn[1] =9.6876;
        cc[2] =0.056762;
        ss[2] =0.808114;
        nn[2] =8.21968;
        cc[3] =0.056762;
        ss[3] =0.808114;
        nn[3] =7.02911;
        cc[4] =0.056762;
        ss[4] =0.808114;
        nn[4] =6.10214;
    } else if(fixOpt==1){
        cc[1] =0.0560882;
        ss[1] =1.47838;
        nn[1] =0.115188;
        cc[2] =0.0256674;
        ss[2] =1.40659;
        nn[2] =-0.0341018;
        cc[3] =0.00644361;
        ss[3] = 1.31446;
        nn[3] = -0.0721935;
        cc[4] =0.0170442;
        ss[4] = 1.22837;
        nn[4] = 0.0511498;
    }

    TCanvas* cSmear = new TCanvas("cSmear", "", 350, 900);
    cSmear -> Divide(1,3); 
    cSmear -> SetLeftMargin(0.5);

    TH1D* hSmear[5]; 
    TH1D* hRatio[5]; 
    TH1D* hRatioGen[5]; 
    for(int icoll=0; icoll<5; icoll++){    
        hSmear[icoll] = new TH1D(Form("hSmear%d",icoll), "; p_{T}^{Smeared} (GeV) ; Entries", nbin, ptbin);
    }

    TRandom3 rand(111);

    for(int icoll=1; icoll<5; icoll++){    
        cSmear -> cd(1);
        for(int i=0; i<1000000; i++){
            double pt = hRecoPt[0] -> GetRandom();
            sigma[icoll] = sqrt( (cc[icoll]*cc[icoll]-cc[0]*cc[0]) + (ss[icoll]*ss[icoll]- ss[0]*ss[0])/pt + (nn[icoll]*nn[icoll]-nn[0]*nn[0])/(pt*pt));
            double factor = rand.Gaus(1,sigma[icoll]);
            double newPt = pt*factor;

            //double weight = 1.0; 
            double weight = hGenPt_ratio[icoll]->GetBinContent(hGenPt_ratio[icoll]->FindBin(pt));
            hSmear[icoll] -> Fill(newPt, weight);
        }

        handsomeTH1(hSmear[icoll], icoll+1, 0.5);
        hSmear[icoll] -> Scale(1./hSmear[icoll]->Integral());
        if(icoll==0) hSmear[icoll] -> Draw();
        else hSmear[icoll] -> Draw("same");

        cSmear -> cd(2);
        hRatioGen[icoll] = (TH1D*) hSmear[icoll] -> Clone(Form("hRatioGen%d",icoll));
        hRatioGen[icoll] -> Divide(hRecoPt[icoll]);
        hRatioGen[icoll] -> SetYTitle("p_{T}^{smeared}/p_{T}^{Gen}");
        handsomeTH1(hRatioGen[icoll], icoll+1, 0.5);
        if(icoll==0) hRatioGen[icoll] -> Draw();
        else hRatioGen[icoll] -> Draw("same");
        jumSun(0,1,220,1,2);
        jumSun(30,0.7,30,1.8,1);

        cSmear -> cd(3);
        hRatio[icoll] = (TH1D*) hSmear[icoll] -> Clone(Form("hRatio%d",icoll));
        hRatio[icoll] -> Divide(hRecoPt[icoll]);
        hRatio[icoll] -> SetYTitle("p_{T}^{smeared}/p_{T}^{Reco}");
        handsomeTH1(hRatio[icoll], icoll+1, 0.5);
        if(icoll==0) hRatio[icoll] -> Draw();
        else hRatio[icoll] -> Draw("same");
        jumSun(0,1,220,1,2);
        jumSun(30,0.7,30,1.8,1);

    }
    cSmear -> cd(1);
    l1 -> Draw();
    l2 -> Draw();

//
// reco/smear ratio
//
    TCanvas* cPbPbp = new TCanvas("cPbPbp", "", 950, 300);
    makeMultiPanelCanvas(cPbPbp, 4, 1);
    TH1D* hPbPbp[5];//histogram reco/smear
    for(int icoll=0; icoll<5; icoll++){
        hPbPbp[icoll]= (TH1D*) hRecoPt[icoll] -> Clone(Form("hPbPbp%d",icoll));
    }

    for(int icoll=1; icoll<5; icoll++){
        cPbPbp -> cd(icoll);
        hPbPbp[icoll] -> Divide(hSmear[icoll]);
        hPbPbp[icoll] -> SetYTitle("p_{T}^{PbPb}/p_{T}^{Smeared pp}");
        hPbPbp[icoll] -> SetAxisRange(0.7,1.8,"Y"); 
        hPbPbp[icoll] -> Draw(); 
        jumSun(0,1,220,1,2);
        jumSun(30,0.7,30,1.8,1);

    }
    cPbPbp -> cd(1);
    l1 -> Draw();
    cPbPbp -> cd(2);
    l2 -> Draw();

    cSmear -> SaveAs(Form("smeared_fixOpt%d.pdf",fixOpt));
}


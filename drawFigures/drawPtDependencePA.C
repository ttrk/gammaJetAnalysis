#include "../../hiForestV3/hiForest.h"
#include "../CutAndBinCollection2012.h"
#include <TRandom3.h>
#include <time.h>

void drawPtDependence( bool saveFigures=true) {

    const int nPtBin = 4;
    double ptBin[nPtBin+1] = {40, 50,60,80,9999}; 
    double ptBinPaDraw[nPtBin+1] = { 40.5 ,49.5, 58.5,  76.5,  123. } ;
    // double AvePtBin[nPtBin+1] = { 45, 54.1479, 67.4204, 99.6956, 9999};
    
    const int nCentBinHI = 2;
    const int centBinHI[nCentBinHI +1] = {-1, 10030, 13099}; 

    TH1D* hxjg[7][10][6]; // [Collision][centrality][pt]
    TH1D* hJetPt[7][10][6]; // [Collision][centrality][pt]
    TH1D* hIaa[7][10][6]; // [Collision][centrality][pt]
    TH1D* hDphi[7][10][6]; // [Collision][centrality][pt]
    TH1D* hEta[7][10][6]; // [Collision][centrality][pt]
    TH1D* meanXjg[7][10];      // [Collision][centrality]
    TH1D* meanJetPt[7][10];      // [Collisi on][centrality]

    TH1D* rjg[7][5];     //  [Collision][centrality]
    for (int icoll=0 ; icoll<6  ; icoll++) {
        for (int icent=1 ; icent<= 10 ; icent++) {
            meanXjg[icoll][icent] = new TH1D( Form("meanXjg_icoll%d_icent%d",icoll,icent), ";p_{T}^{#gamma} (GeV); <X_{J#gamma}>",nPtBin,ptBinPaDraw);
            meanJetPt[icoll][icent] = new TH1D( Form("meanJetPt_icoll%d_icent%d",icoll,icent), ";p_{T}^{#gamma} (GeV); <p_{T}^{Jet}>",nPtBin,ptBinPaDraw);
            rjg[icoll][icent] = new TH1D( Form("rjg_icoll%d_icent%d",icoll,icent), ";p_{T}^{#gamma} (GeV); R_{J#gamma}",nPtBin,ptBinPaDraw);

            for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
                hxjg[icoll][icent][ipt] = NULL;
                hJetPt[icoll][icent][ipt] = NULL;
                hIaa[icoll][icent][ipt] = NULL;
                hDphi[icoll][icent][ipt] = NULL;
                hEta[icoll][icent][ipt] = NULL;
            }

        }
    }

    TFile* histFile[7][6];  // [Collision][pt]                                                                                          
    for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
        for (int icoll=0 ; icoll<6 ; icoll++) {
            TString sampleName = getSampleName( icoll ) ;
            char* fname =  Form("../histogramProducer/ffFiles/photonTrackCorr_%s_output_photonPtThr%d_to_%d_jetPtThr30_20130919.root",sampleName.Data(), (int)ptBin[ipt-1], (int)ptBin[ipt]);
            histFile[icoll][ipt] = new TFile(fname) ;
            cout << " Reading file : " << fname << endl;

            if ( histFile[icoll][ipt]->IsZombie()  == false ) {
                cout << " Success." << endl;
                if ( (icoll == kPPDATA) || (icoll == kPPMC) )   {  //  PP
                    int icent = 7 ; 
                    hxjg[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("xjg_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("xjg_icent%d_final", icent) << endl;
                    hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPt_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("jetPt_icent%d_final", icent) << endl;
                    hDphi[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("jetDphi_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("jetDphi_icent%d_final", icent) << endl;
                    hEta[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("etaJg_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("etaJg_icent%d_final", icent) << endl;

                }

		if ( (icoll == kPADATA) || (icoll == kPAMC) )   {  //  PP
                    int icent = 1 ; 
                    hxjg[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("xjg_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("xjg_icent%d_final", icent) << endl;
                    hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPt_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("jetPt_icent%d_final", icent) << endl;
                    hDphi[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("jetDphi_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("jetDphi_icent%d_final", icent) << endl;
                    hEta[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("etaJg_icent%d_final", icent)) ;
                    cout << " Getting histogram : " << Form("etaJg_icent%d_final", icent) << endl;

                }

                if ( ( icoll == kHIDATA) ||  (icoll == kHIMC) ) { // PbPb
                    for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
                        hxjg[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("xjg_icent%d_final", centBinHI[icent] )) ;
                        cout << " Getting histogram : " << Form("xjg_icent%d_final", centBinHI[icent] ) << endl;
                        hJetPt[icoll][icent][ipt] = (TH1D*)histFile[icoll][ipt]->Get(Form("jetPt_icent%d_final", centBinHI[icent] ) );
                        cout << " Getting histogram : " << Form("jetPt_icent%d_final", centBinHI[icent] ) << endl;
                        hDphi[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("jetDphi_icent%d_final", centBinHI[icent] ) ) ;
                        cout << " Getting histogram : " << Form("jetDphi_icent%d_final", icent)<< endl;
                        hEta[icoll][icent][ipt]  = (TH1D*)histFile[icoll][ipt]->Get(Form("etaJg_icent%d_final", centBinHI[icent] ) ) ;
                        cout << " Getting histogram : " << Form("etaJg_icent%d_final", icent)<< endl;
                    }
                }
            }
            else  
                cout << " no such file " << endl;
        }
    }

    for (int ipt=1 ; ipt<=nPtBin ; ipt++) {
        for (int icoll=0 ; icoll<6 ; icoll++) {
            for (int icent=1 ; icent<= 10 ; icent++ ) { 
                if ( hxjg[icoll][icent][ipt] == NULL ) 
                    continue;   // emtpy histogram 
                double rVal, rErr;

                rVal = hxjg[icoll][icent][ipt]->IntegralAndError(1, hxjg[icoll][icent][ipt]->GetNbinsX(), rErr, "width");
                rjg[icoll][icent]->SetBinContent( ipt, rVal );
                rjg[icoll][icent]->SetBinError  ( ipt, rErr );

                meanXjg[icoll][icent]->SetBinContent( ipt, hxjg[icoll][icent][ipt]->GetMean() );
                meanXjg[icoll][icent]->SetBinError  ( ipt, hxjg[icoll][icent][ipt]->GetMeanError() );

                meanJetPt[icoll][icent]->SetBinContent( ipt, hJetPt[icoll][icent][ipt]->GetMean() );
                meanJetPt[icoll][icent]->SetBinError  ( ipt, hJetPt[icoll][icent][ipt]->GetMeanError() );


            }
        }
    }

    TCanvas* c1 = new TCanvas("c1","",1200,350);
    makeMultiPanelCanvas(c1,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
    for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {

        c1->cd(ipt);

        // draw pp
        handsomeTH1(hDphi[kPAMC][1][ipt], 1);
        hDphi[kPAMC][1][ipt]->SetXTitle("#Delta#phi_{J#gamma}");
        hDphi[kPAMC][1][ipt]->SetYTitle("Normalized entries");
        hDphi[kPAMC][1][ipt]->SetMarkerStyle(24);
        hDphi[kPAMC][1][ipt]->Scale(1./hDphi[kPAMC][1][ipt]->Integral("width"));       
        hDphi[kPAMC][1][ipt]->SetAxisRange(0,3.141592,"X");
        hDphi[kPAMC][1][ipt]->SetAxisRange(0.01,30,"Y");
        hDphi[kPAMC][1][ipt]->Draw();

	handsomeTH1(hDphi[kPADATA][1][ipt], kRed);
	hDphi[kPADATA][1][ipt]->Scale(1./hDphi[kPADATA][1][ipt]->Integral("width"));
	hDphi[kPADATA][1][ipt]->Draw("same");
        // // draw pbpb 
        // for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
        //     handsomeTH1(hDphi[kHIDATA][icent][ipt],kRed);
        //     if ( icent == 2 ) hDphi[kHIDATA][icent][ipt]->SetMarkerStyle(24);
        //     hDphi[kHIDATA][icent][ipt]->Scale(1./hDphi[kHIDATA][icent][ipt]->Integral("width"));
        //     hDphi[kHIDATA][icent][ipt]->Draw("same");

        // }

        gPad->SetLogy();
        //    onSun(30,0,200,0);
    }
    c1->cd(1);
    // TLegend *ly = new TLegend(0.4913112,0.6561548,0.9997611,0.9431145,NULL,"brNDC");
    // easyLeg(ly,"2.76TeV");
    // ly->AddEntry(hDphi[kPPDATA][7][1],"pp ","p");
    // ly->AddEntry(hDphi[kHIDATA][2][1],"PbPb 0-30%","p");

    // TLegend *l1 = new TLegend(0.1995968,0.7097458,0.7076613,0.9237288,NULL,"brNDC");
    // easyLeg(l1,"2.76TeV");
    // l1->AddEntry(hDphi[kPPDATA][7][1],"pp ","p");
    // l1->AddEntry(hDphi[kHIDATA][2][1],"PbPb 30-100%","p");
    // l1->AddEntry(hDphi[kHIDATA][1][1],"PbPb 0-30%","p");
    // l1->Draw();

    //if (saveFigures) c1->SaveAs("figures/pT_dependence_dphi_pA_figure1.pdf");
    if (saveFigures) c1->SaveAs("figures/pT_dependence_dphi_pA_figure1.gif");
    
    TLegend *l1 = new TLegend(0.1995968,0.7097458,0.7076613,0.9237288,NULL,"brNDC");
    easyLeg(l1,"5.02TeV");
    l1->AddEntry(hDphi[kPAMC][1][1],"pA pythia+HIJING ","p");
    l1->AddEntry(hDphi[kPADATA][1][1],"pA Data","p");
    l1->Draw();



    TH1D* hTempPt = new TH1D("hTemp",";p_{T}^{#gamma} (GeV);",200,10,300);

    TCanvas* c2 = new TCanvas("c2","",1200,350);
    makeMultiPanelCanvas(c2,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
    for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {

        c2->cd(ipt);

        // draw pp
        hTempPt->SetXTitle("p_{T}^{Jet} (GeV)");
        hTempPt->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
        hTempPt->SetAxisRange(10,150,"X");
	//        hTempPt->SetAxisRange(0,0.025,"Y");
	hTempPt->SetAxisRange(0,0.08,"Y");
        handsomeTH1(hTempPt,0);
        hTempPt->DrawCopy();
	
	hJetPt[kPAMC][1][ipt]->Scale(1./rjg[kPAMC][1]->GetBinContent(ipt)); // rjg normalization                      
		

        handsomeTH1(hJetPt[kPAMC][1][ipt], 1);
        hJetPt[kPAMC][1][ipt]->SetMarkerStyle(24);
	hJetPt[kPAMC][1][ipt]->Draw("same");

        // draw pbpb 
        // for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
        //     handsomeTH1(hJetPt[kHIDATA][icent][ipt],kRed);
	//     hJetPt[kHIDATA][icent][ipt]->Scale(1./rjg[kHIDATA][icent]->GetBinContent(ipt));  // rjg normalization
	//     if ( icent == 2 ) hJetPt[kHIDATA][icent][ipt]->SetMarkerStyle(24);
        //     //      if ( icent == 1 )       hJetPt[kHIDATA][icent][ipt]->Draw("same");
        //     if ( icent == 1 ) hJetPt[kHIDATA][icent][ipt]->Draw("same");
        // }
	handsomeTH1(hJetPt[kPADATA][1][ipt],kRed);
	hJetPt[kPADATA][1][ipt]->Scale(1./rjg[kPADATA][1]->GetBinContent(ipt));
	hJetPt[kPADATA][1][ipt]->Draw("same");
	
       
        double dx1=0.15;
        if ( ipt == nPtBin ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823

        onSun(30,0,200,0);
        /*
           c2->cd(ipt+nPtBin);

        hTempPt->SetYTitle("I_{AA}");
        hTempPt->SetAxisRange(0,3,"Y");
        hTempPt->DrawCopy();
        //    for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
        for ( int icent = 1; icent <= 1 ; icent++ ) {
            hIaa[kHIDATA][icent][ipt] = (TH1D*)hJetPt[kHIDATA][icent][ipt]->Clone(Form("iaa_%s",hJetPt[kHIDATA][icent][ipt]->GetName()) );
            hIaa[kHIDATA][icent][ipt]->Divide(hJetPt[kPPDATA][1][ipt]);
            hIaa[kHIDATA][icent][ipt]->Draw("same");
        }
        jumSun(10,1,150,1);*/
    }
    c2->cd(1);
    l1->Draw();  

    if (saveFigures)   c2->SaveAs("figures/pT_dependence_jetPt_pA_figure1.pdf");
    if (saveFigures)   c2->SaveAs("figures/pT_dependence_jetPt_pA_figure1.gif");

    TLegend *l2 = new TLegend(0.2116935,0.7012712,0.6149194,0.904661,NULL,"brNDC");
    easyLeg(l2,"5.02TeV");
    // l2->AddEntry(hDphi[kPPDATA][7][1],"pp ","p");
    // l2->AddEntry(hDphi[kHIDATA][1][1],"PbPb 30-100%","p");
    // l2->AddEntry(hDphi[kHIDATA][2][1],"PbPb 0-30%","p");

    l2->AddEntry(hDphi[kPAMC][1][1],"pPb pythia+HIJING","p");
    l2->AddEntry(hDphi[kPADATA][1][1],"pPb Data","p");

    
    TCanvas* c21 = new TCanvas("c21","",500,500);
    handsomeTH1(meanJetPt[kPAMC][1], 1);
    meanJetPt[kPAMC][1]->SetYTitle("<p_{T}^{Jet}>  (>30GeV)");
    meanJetPt[kPAMC][1]->SetMarkerStyle(24);
    //  meanJetPt[kPAMC][1]->SetAxisRange(-2,2,"X");
    meanJetPt[kPAMC][1]->SetAxisRange(40,80,"Y");
    meanJetPt[kPAMC][1]->Draw();

    // for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
    //     handsomeTH1(meanJetPt[kHIDATA][icent],kRed);
    //     if ( icent == 2 ) meanJetPt[kHIDATA][icent]->SetMarkerStyle(24);
    //     //if ( icent != 2 ) meanJetPt[kHIDATA][icent]->Draw("same");
    //     meanJetPt[kHIDATA][icent]->Draw("same");
    // }
    handsomeTH1(meanJetPt[kPADATA][1],kRed);
    meanJetPt[kPADATA][1]->Draw("same");
    
    l1 ->Draw();
    if (saveFigures)   c21->SaveAs("figures/pT_dependence_jetPt_pA_figure2.pdf");
    if (saveFigures)   c21->SaveAs("figures/pT_dependence_jetPt_pA_figure2.gif");

    TCanvas* c3 = new TCanvas("c3","",1200,350);
    makeMultiPanelCanvas(c3,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
    for ( int ipt = 1 ; ipt<=nPtBin  ; ipt++) {

        c3->cd(ipt);

        // draw pp                                                                                                                                      
        handsomeTH1(hxjg[kPAMC][1][ipt], 1);
        hxjg[kPAMC][1][ipt]->SetXTitle("x_{J#gamma}");
        hxjg[kPAMC][1][ipt]->SetYTitle("#frac{dN}{dp_{T}} #frac{1}{N}");
        hxjg[kPAMC][1][ipt]->SetAxisRange(0,2,"X");
        hxjg[kPAMC][1][ipt]->SetMarkerStyle(24);

	hxjg[kPAMC][1][ipt]->Scale(1./rjg[kPAMC][1]->GetBinContent(ipt)); // rjg normalization                                         


        hxjg[kPAMC][1][ipt]->SetAxisRange(0,3,"Y");
        hxjg[kPAMC][1][ipt]->Draw();

        // draw pbpb                                                                                                                                    
        // for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
        //     handsomeTH1(hxjg[kHIDATA][icent][ipt],kRed);
	//     hxjg[kHIDATA][icent][ipt]->Scale(1./rjg[kHIDATA][icent]->GetBinContent(ipt)); // rjg normalization                                         
        //     if ( icent == 2 ) hxjg[kHIDATA][icent][ipt]->SetMarkerStyle(24);
	//     //        if ( icent == 1 )       hxjg[kHIDATA][icent][ipt]->Draw("same");                                                                    
        //     if ( icent == 1 ) hxjg[kHIDATA][icent][ipt]->Draw("same");

        // }
	
	handsomeTH1(hxjg[kPADATA][1][ipt],kRed);
	hxjg[kPADATA][1][ipt]->Scale(1./rjg[kPADATA][1]->GetBinContent(ipt)); // rjg normalization
	hxjg[kPADATA][1][ipt]->Draw("same");
	
        double dx1=0.15;
        if ( ipt == nPtBin ) 
            drawText(Form("p_{T}^{#gamma} > %dGeV, ", (int)ptBin[ipt-1]), 0.12+dx1+0.25,0.85,1,15);//yeonju 130823
        else
            drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV, ", (int)ptBin[ipt-1], (int)ptBin[ipt]), 0.12+dx1,0.85,1,15);//yeonju 130823

 
        onSun(30,0,200,0);
    }
    c3->cd(1);
    l1->Draw();  

    if (saveFigures)   c3->SaveAs("figures/pT_dependence_xjg_pA_figure1.pdf");
    if (saveFigures)   c3->SaveAs("figures/pT_dependence_xjg_pA_figure1.gif");

    TCanvas* c31 = new TCanvas("c31","",500,500);
    handsomeTH1(meanXjg[kPAMC][1], 1);
    meanXjg[kPAMC][1]->SetYTitle("<x_{J#gamma}>  (>30GeV)");
    meanXjg[kPAMC][1]->SetMarkerStyle(24);
    //  meanXjg[kPAMC][1]->SetAxisRange(-2,2,"X");
    meanXjg[kPAMC][1]->SetAxisRange(0.6,1.2,"Y");
    meanXjg[kPAMC][1]->Draw();

    // for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
    //     handsomeTH1(meanXjg[kHIDATA][icent],kRed);
    //     if ( icent == 2 ) meanXjg[kHIDATA][icent]->SetMarkerStyle(24);
    //     //if ( icent != 2 ) meanXjg[kHIDATA][icent]->Draw("same");
    // 	meanXjg[kHIDATA][icent]->Draw("same");
    // }
    handsomeTH1(meanXjg[kPADATA][1],kRed);
    meanXjg[kPADATA][1]->Draw("same");
    
    l1->Draw();
    if (saveFigures)   c31->SaveAs("figures/pT_dependence_xjg_pA_figure1.pdf");
    if (saveFigures)   c31->SaveAs("figures/pT_dependence_xjg_pA_figure1.gif");
    

    TCanvas* c_rjg = new TCanvas("c_rjg","",500,500);
    handsomeTH1(rjg[kPAMC][1], 1);
    rjg[kPAMC][1]->SetYTitle("R_{J#gamma}");
    rjg[kPAMC][1]->SetMarkerStyle(24);
    //  rjg[kPAMC][1]->SetAxisRange(-2,2,"X");
    rjg[kPAMC][1]->SetAxisRange(0.0,1.1,"Y");
    rjg[kPAMC][1]->Draw();

    // for ( int icent = 1; icent <= nCentBinHI ; icent++ ) {
    //     handsomeTH1(rjg[kHIDATA][icent],kRed);
    //     if ( icent == 2 ) rjg[kHIDATA][icent]->SetMarkerStyle(24);
    // 	//        if ( icent != 2 ) rjg[kHIDATA][icent]->Draw("same");
    //     rjg[kHIDATA][icent]->Draw("same");
    // }
    handsomeTH1(rjg[kPADATA][1],kRed);
    rjg[kPADATA][1]->Draw("same");

    
    l1->Draw();
    if (saveFigures)   c_rjg->SaveAs("figures/pT_dependence_rjg_pA_figure1.pdf");
    if (saveFigures)   c_rjg->SaveAs("figures/pT_dependence_rjg_pA_figure1.gif");
    }


/*  
  //    onSun(meanX[iSpecies][iglb].val - meanX[iSpecies][iglb].err, 0, meanX[iSpecies][iglb].val+meanX[iSpecies][iglb].err,0,ycolor[ipt+1],2);
    
    float dx1;    
    (ipt==0)? dx1=0.15 : dx1=0 ;
    
    if ( ipt == nPtBin-1 ) 
      drawText(Form("p_{T}^{#gamma} > %dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt]), 0.12+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV < p_{T}^{#gamma} < %dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.12+dx1,0.889118,1,15);

      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"5.02TeV");
    l1->AddEntry(hdptNorm[kPPDATA][ipt + kPPDATA*50],"pp ","p");
    if (drawPbPb)    l1->AddEntry(hdptNorm[kHIDATA][iglb],"PbPb 50-100%","p");
    if ( ipt==0 )   l1->Draw();
    

  }
  c1->SaveAs(Form("gifs/dpt_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));

  TCanvas* cDphi = new TCanvas("cDphi","",900,350);
  makeMultiPanelCanvas(cDphi,nPtBin,1,0.0,0.0,0.2,0.15,0.02);
  for ( int ipt = 0 ; ipt<nPtBin  ; ipt++) {
    cDphi->cd(ipt+1);
    
    int iSpecies = kPPDATA;
    int iglb = ipt + iSpecies*50.;
    handsomeTH1(hdphi[iSpecies][iglb],1);
    hdphi[iSpecies][iglb]->SetYTitle("x_{J,#gamma}");
    hdphi[iSpecies][iglb]->SetXTitle("#Delta#phi_{J,#gamma}");
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    hdphi[iSpecies][iglb]->SetAxisRange(0.01,30,"Y");
    hdphi[iSpecies][iglb]->SetMarkerStyle(24);
    hdphi[iSpecies][iglb]->Draw();

    iSpecies = kHIDATA;
    iglb = ipt + iSpecies*50.;
    hdphi[iSpecies][iglb]->Scale(1./hdphi[iSpecies][iglb]->Integral("width"));
    handsomeTH1(hdphi[iSpecies][iglb],2);
    if (drawPbPb)     hdphi[iSpecies][iglb]->Draw("same");
    gPad->SetLogy();
    float dx1;    
    (ipt==0)? dx1=0.15 : dx1=0 ;
    
    if ( ipt == nPtBin-1 ) 
      drawText(Form("%dGeV<p_{T}^{#gamma},   p_{T}^{jet}>30GeV", (int)ptBin[ipt]), 0.15+dx1+0.25,0.889118,1,15);
    else 
      drawText(Form("%dGeV<p_{T}^{#gamma}<%dGeV,   p_{T}^{jet}>30GeV", (int)ptBin[ipt], (int)ptBin[ipt+1]), 0.15+dx1,0.889118,1,15);
    
      
    TLegend *l1 = new TLegend(0.6365615,0.6445304,0.9577623,0.846736,NULL,"brNDC");
    easyLeg(l1,"5.02TeV");
    l1->AddEntry(hdphi[kPPDATA][ipt + kPPDATA*50],"pp ","p");
    if (drawPbPb)    l1->AddEntry(hdphi[kHIDATA][iglb],"PbPb 0-30%","p");
    if ( ipt==0 )   l1->Draw();

  }

  
  //  cDphi->SaveAs(Form("gifs/dphi_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));
  
  TCanvas* c2 = new TCanvas("c2","",800,400);
  c2->Divide(2,1);
  c2->cd(2);
  TH1D* hr = new TH1D("hr",";p_{T}^{#gamma};r_{J,#gamma}",200,20,120);
  handsomeTH1(hr,0);
  hr->SetAxisRange(0.0,1.3,"Y");
  //  hr->SetNdivisions(5);
  hr->Draw();
  handsomeTGraph(gr[kPPDATA],1);
  handsomeTGraph(gr[kHIDATA],2);
  gr[kPPDATA]->SetMarkerStyle(24);
  gr[kPPDATA]->Draw("same p");
  if (drawPbPb)   gr[kHIDATA]->Draw("same p");
  jumSun(20,1,120,1);


  
  c2->cd(1);
  TH1D* hx = (TH1D*)hr->Clone("hx");
  handsomeTH1(hx,0);
  hx->SetYTitle("<#Deltap_{T}^{J,#gamma}>");
  //  hx->SetAxisRange(-60,10,"Y");
  hx->SetAxisRange(30,100,"Y");
  //  hx->SetNdivisions(5);
  hx->Draw();
  handsomeTGraph(gdpt[kPPDATA],1);
  handsomeTGraph(gdpt[kHIDATA],2);
  gdpt[kPPDATA]->SetMarkerStyle(24);
  gdpt[kPPDATA]->Draw("same p");
  if (drawPbPb)   gdpt[kHIDATA]->Draw("same p");
  jumSun(20,1,120,1);

  TLegend *l1=   new TLegend(0.5226071,0.6300415,0.9597724,0.8332584,NULL,"brNDC");
  easyLeg(l1,"5.02TeV");
  l1->AddEntry(gr[kPPDATA],"pp ","p");
  if (drawPbPb)     l1->AddEntry(gr[kHIDATA],"PbPb 30-100%","p");
  l1->Draw();

  //  c2->SaveAs(Form("gifs/summaryPlot_ptDependence_drawPbPb%d_norm%d.pdf",drawPbPb,xNorm));

}

*/

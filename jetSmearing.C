// Author Aleksey Strelnikov

#include "../HiForest_V3/hiForest.h"
#include "commonUtility.h"
#include <TMath.h>
#include <iostream>
#include <fstream>
using namespace std;

/***************************************************************************//**
 *
 * Get the smearing of distribution of reco jet pt / gen jet pt and fit as 
 * function of pt, centrality, and eta.
 *
 * autosave - true means canvases will automatically be saved as png's, good for
 *            batch mode.
 * collType - 0 uses the pp MC sample(s), 1 uses the PbPb MC sample(s)
 * usePu    - true means use akPu3PF jet algo, false means use ak3PF jet algo
 *
 ******************************************************************************/
void run(bool autosave = false, int collType = 0, bool usePu = true)
{
    //===========================================================
    // INPUTS - Set pt,eta,centrality bins and fit function here.
    // Can edit source file locations ~40 lines below here
    // also ~50 lines below are the centrality bins for PbPb
    const Int_t nPtBin = 5;
    Double_t ptBin[nPtBin+1] = {20,25,30,40,60,100};
    
    const Int_t nAbsEtaBin = 4;
    Double_t absEtaBin[nAbsEtaBin+1] = {0.0,0.4,0.8,1.2,1.6};//,2.0};
    
    // centrality for PbPb case
    Int_t nCentBin = 4;
    Int_t *centBin = new Int_t[nCentBin+1];
    centBin[0] = 0;
    centBin[1] = 10;
    centBin[2] = 30;
    centBin[3] = 50;
    centBin[4] = 100;
    
    // (reco jet pt / gen jet pt) histogram parameters
    Int_t nHistBin = 25;
    Double_t histMin = 0.0;
    Double_t histMax = 2.5;
    
    // fit type for widths
    TString fitStr = "[0]+[1]/sqrt(x)+[2]/x";
    const Int_t nFitParam = 3;
    //===========================================================
    
    // for some reason I can't just use collisionType as a parameter to the function
    collisionType cType;
    if(collType == 0)
        cType = cPP;
    else
        cType = cPbPb;
    
    Int_t nSamples;
    TString *inf_str;
    // collision type / pt hat of samples / mc type + E_com / akPu3PF or ak3PF
    TString coll, collHistLabel1, collHistLabel2, jetAnaLabel;
    
    if(cType == cPP){
        coll = "pp";
        collHistLabel1 = "pthat 40";
        collHistLabel2 = "pythia 2.76TeV";
        
        // source files for pp
        nSamples = 1;
        inf_str = new TString[nSamples];
        inf_str[0] = "/mnt/hadoop/cms/store/user/astrelni/pp_photon_pythia/merged_gammaJet_pp_pt40_2p76_pythia_forest.root";
        //===================
        
        // ignore the centrality specification above
        nCentBin = 1;
        centBin[0] = 0;
        centBin[1] = 100;
    }else if(cType == cPbPb){
        coll = "PbPb";
        collHistLabel1 = "pthat 30+50";
        collHistLabel2 = "hydjet 2.76TeV";  
        
        // source files for PbPb
        nSamples = 2;
        inf_str = new TString[nSamples];
        inf_str[0] = "/net/hidsk0001/d00/scratch/jazzitup/macros/hiPhotonAnaThesis/mergedFiles/forest_loPhoton30-HYDJET-START44-V12-Aug29th.root";
        inf_str[1] = "/net/hidsk0001/d00/scratch/jazzitup/macros/hiPhotonAnaThesis/mergedFiles/forest_loPhoton50-HYDJET-START44-V12-Aug29th.root";
        //======================
    }else{
        cout << "unsupported collision type\n";
        return;
    }
    
    if(usePu == true){
        jetAnaLabel = "akPu3PF";
    }else{
        jetAnaLabel = "ak3PF";
    }
    
    // set up output file
    TFile *out_hist_file = new TFile(Form("%s_jet_smearing_hist.root",coll.Data()),"recreate");
    
    // set up the histograms
    TH1D *recoJetPtOverGenJetPt[(const Int_t)nCentBin][nPtBin][nAbsEtaBin];
    for(Int_t i = 0; i < nCentBin; ++i){
        for(Int_t j = 0; j < nPtBin; ++j){
            for(Int_t k = 0; k < nAbsEtaBin; ++k){
                TString name = "recoOverGenJetPt";
                name += Form("_cent%d_%d",centBin[i],centBin[i+1]);
                name += Form("_pt%d_%d",(Int_t)ptBin[j],(Int_t)ptBin[j+1]);
                name += Form("_absEta%dp%d_%dp%d",(Int_t)(absEtaBin[k]/10),
                    (Int_t)(10*absEtaBin[k])%10,(Int_t)(absEtaBin[k+1]/10),
                    (Int_t)(10*absEtaBin[k+1])%10);
                recoJetPtOverGenJetPt[i][j][k] = new TH1D(name.Data(),
                    ";jet p_{t}^{reco}/p_{t}^{gen};n jets",nHistBin,histMin,histMax);
            }
        }
    }
    TH1D *widthHist[nCentBin][nAbsEtaBin];
    for(Int_t i = 0; i < nCentBin; ++i){
        for(Int_t j = 0; j < nAbsEtaBin; ++j){
            TString name = "widthHist_";
            name += Form("_cent%d_%d",centBin[i],centBin[i+1]);
            name += Form("_absEta%dp%d_%dp%d",(Int_t)(absEtaBin[j]/10),
                    (Int_t)(10*absEtaBin[j])%10,(Int_t)(absEtaBin[j+1]/10),
                    (Int_t)(10*absEtaBin[j+1])%10);
            widthHist[i][j] = new TH1D(name.Data(),";jet pt_{t}^{gen};#sigma",nPtBin,ptBin);
        }
    }
    
    // run over the samples
    for(Int_t iSample = 0; iSample < nSamples; ++iSample){
        HiForest *c = new HiForest(inf_str[iSample].Data(),"forest",cType);
        
        // this will point to the jets being used
        Jets *jetAnalyzer = &c->akPu3PF;
        
        // setup ak3PF since its not in the HiForest class
        TTree *ak3jetTree = NULL;
        Jets ak3PF;
        if(usePu == false){
            ak3jetTree = (TTree*)c->inf->Get("ak3PFJetAnalyzer/t");
            if(ak3jetTree == NULL){
                cout << "ERROR: Sample does not contain ak3PFJetAnalyzer.\n";
                return;
            }
            setupJetTree(ak3jetTree,ak3PF);
            jetAnalyzer = &ak3PF;
        }
        
        Int_t nentries = c->GetEntries();
        cout << "\n\nSample " << iSample+1 << "/" << nSamples << "\nnumber of entries: " << nentries << 
                "\nprogress:\n***************************************************" << endl;
        Int_t step = nentries/50;
        for(Int_t jentry = 0; jentry < nentries; ++jentry){
            c->GetEntry(jentry);
            if(usePu == false){
                ak3jetTree->GetEntry(jentry);
            }
            
            if (jentry % step == 0)
                cout << "*" << flush;
            
            // get leading barrel photon index
            Double_t maxPt = -1;
            Int_t leadingIndex = -1;
            for(Int_t j = 0; j < c->photon.nPhotons; ++j){
                if(abs(c->photon.eta[j]) > 1.44)
                    continue;
                if(c->photon.pt[j] > maxPt){
                    leadingIndex = j;
                    maxPt = c->photon.pt[j];
                }
            }		
            
            // photon cuts
            if(leadingIndex < 0 || c->photon.pt[leadingIndex] < 60 || 
                c->photon.cc4[leadingIndex]+ c->photon.cr4[leadingIndex]+
                c->photon.ct4PtCut20[leadingIndex] > 1)
            {
                continue;
            }
            
            // get centrality bin
            Int_t centrality = -1;
            for(Int_t i = -1; i < nCentBin; ++i){
                if(2.5*c->evt.hiBin < centBin[i+1]){
                    centrality = i;
                    break;
                }
            }
            if(centrality < 0)
                continue;
            
			
            // iterate over jets
            Double_t photonPhi = c->photon.phi[leadingIndex];
            for(Int_t k = 0; k < jetAnalyzer->nref; ++k){
                // jet cuts
                if(jetAnalyzer->refpt[k] < 0 || 
                    acos(cos(jetAnalyzer->jtphi[k] - photonPhi)) < 7*TMath::Pi()/8)
                {
                    continue;
                }
                
                // get eta bin of the gen jet
                Int_t genEtaBin = -1;
                for(Int_t i = -1; i < nAbsEtaBin; ++i){
                    if(abs(jetAnalyzer->refeta[k]) < absEtaBin[i+1]){
                        genEtaBin = i;
                        break;
                    }
                }
                if(genEtaBin < 0)
                    continue;
                
                // get pt bin of the gen jet
                Int_t genPtBin = -1;
                for(Int_t i = -1; i < nPtBin; ++i){
                    if(jetAnalyzer->refpt[k] < ptBin[i+1]){
                        genPtBin = i;
                        break;
                    }
                }
                if(genPtBin < 0)
                    continue;                    
                
                recoJetPtOverGenJetPt[centrality][genPtBin][genEtaBin]->Fill(
                    jetAnalyzer->jtpt[k]/jetAnalyzer->refpt[k]);
            }
        }	
        cout << "\n\n";
    }
    
    // plot and fit
    Double_t minY, maxY; // y range for fit plots
    TCanvas *cjetPtComp[nCentBin];
    for(Int_t iCent = 0; iCent < nCentBin; ++iCent){
        cjetPtComp[iCent] = new TCanvas(
            Form("%s%sjetPtCompCentBin%d",coll.Data(),jetAnaLabel.Data(),iCent),
            Form("%s%sjetPtCompCentBin%d",coll.Data(),jetAnaLabel.Data(),iCent),
            360*nPtBin,250*nAbsEtaBin);
        makeMultiPanelCanvas(cjetPtComp[iCent],nPtBin,nAbsEtaBin);
    
        for(Int_t i = 0; i < nPtBin; ++i){
            for(Int_t j = 0; j < nAbsEtaBin; ++j){
                cjetPtComp[iCent]->cd(i + 1 + j*nPtBin);
                
                // style
                handsomeTH1(recoJetPtOverGenJetPt[iCent][i][j],1);
                recoJetPtOverGenJetPt[iCent][i][j]->SetStats(0);
                recoJetPtOverGenJetPt[iCent][i][j]->GetXaxis()->SetTitleSize(0.08);
                recoJetPtOverGenJetPt[iCent][i][j]->GetYaxis()->SetTitleSize(0.08);
                recoJetPtOverGenJetPt[iCent][i][j]->GetXaxis()->SetLabelSize(0.08);
                recoJetPtOverGenJetPt[iCent][i][j]->GetYaxis()->SetLabelSize(0.08);
                recoJetPtOverGenJetPt[iCent][i][j]->SetAxisRange(0.0,
                    1.5*recoJetPtOverGenJetPt[iCent][i][j]->GetBinContent(
                    recoJetPtOverGenJetPt[iCent][i][j]->GetMaximumBin()),"Y");
                
                // draw and fit
                recoJetPtOverGenJetPt[iCent][i][j]->Draw();
                recoJetPtOverGenJetPt[iCent][i][j]->Fit("gaus");
                
                // vertical dashed line at x=1
                jumSun(1.0,0.0,1.0,1.5*recoJetPtOverGenJetPt[iCent][i][j]->GetBinContent(
                    recoJetPtOverGenJetPt[iCent][i][j]->GetMaximumBin()));
                
                // draw labels
                if(i == 0 || j == 0){
                    Float_t xoffset = 0.2*(i==0);
                    TLegend *leg0 = new TLegend(0.0+xoffset,0.62,0.4+xoffset,0.95);
                    leg0->SetFillStyle(0);
                    leg0->SetBorderSize(0);
                    leg0->SetTextSize(0.08);
                    if(i==0 && j == 0){
                        TString label = coll + " " + jetAnaLabel; + " " + collHistLabel1;
                        leg0->AddEntry(recoJetPtOverGenJetPt[iCent][i][j],label,"");
                        leg0->AddEntry(recoJetPtOverGenJetPt[iCent][i][j],collHistLabel2,"");
                        if(nCentBin > 1){
                            leg0->AddEntry(recoJetPtOverGenJetPt[iCent][i][j],
                                Form("%d - %d%c",centBin[iCent],centBin[iCent+1],'%'),"");
                        }
                    }
                    if(i == 0){
                        leg0->AddEntry(recoJetPtOverGenJetPt[iCent][i][j],
                            Form("%.1f < |#eta| < %.1f",absEtaBin[j],absEtaBin[j+1]),"");
                    }
                    if(j == 0){
                        leg0->AddEntry(recoJetPtOverGenJetPt[iCent][i][j],
                            Form("%.1f < p_{t} < %.1f",ptBin[i],ptBin[i+1]),"");
                    }
                    
                    leg0->Draw();
                }
                
                // fit
                TF1 *fit = recoJetPtOverGenJetPt[iCent][i][j]->GetFunction("gaus");
                widthHist[iCent][j]->SetBinContent(i+1,fit->GetParameter(2));
                widthHist[iCent][j]->SetBinError(i+1,fit->GetParError(2));
            }
        }
    
        // get y range
        maxY = -1;
        for(Int_t i = 0; i < nAbsEtaBin; ++i){
            maxY = max(maxY,widthHist[iCent][i]->GetBinContent(widthHist[iCent][i]->GetMaximumBin()));
        }
        
        minY = maxY;
        for(Int_t i = 0; i < nAbsEtaBin; ++i){
            minY = min(minY,widthHist[iCent][i]->GetBinContent(widthHist[iCent][i]->GetMinimumBin()));
        }
        
        // save canvas if autosave is on
        if(autosave){
            cjetPtComp[iCent]->SaveAs(Form("%s%sjetPtCompCentBin%d.png",
                coll.Data(),jetAnaLabel.Data(),iCent));
        }
    }
    
    // plot gaussian width and fit to custom function
    TCanvas *cwidth = new TCanvas(Form("%s%swidth",coll.Data(),jetAnaLabel.Data()),
                    Form("%s%swidth",coll.Data(),jetAnaLabel.Data()),
                    360*nCentBin+100*(nCentBin==1),250*nAbsEtaBin);
    makeMultiPanelCanvas(cwidth,nCentBin,nAbsEtaBin);
    TF1 *widthFit = new TF1("widthFit",fitStr.Data(),ptBin[0],ptBin[nPtBin]);
    Double_t FitParam[nFitParam][nCentBin][nAbsEtaBin];
    Double_t FitParamErr[nFitParam][nCentBin][nAbsEtaBin];
    for(Int_t i = 0; i < nCentBin; ++i){
        for(Int_t j = 0; j < nAbsEtaBin; ++j){
            cwidth->cd(i + 1 + j*nCentBin);
            handsomeTH1(widthHist[i][j],1);
            widthHist[i][j]->SetStats(0);
            widthHist[i][j]->GetXaxis()->SetTitleSize(0.08);
            widthHist[i][j]->GetYaxis()->SetTitleSize(0.08);
            widthHist[i][j]->GetXaxis()->SetLabelSize(0.08);
            widthHist[i][j]->GetYaxis()->SetLabelSize(0.08);
            widthHist[i][j]->SetAxisRange(0.9*minY,1.1*maxY,"Y");
            widthHist[i][j]->Draw("ep");
            widthHist[i][j]->Fit(widthFit);

            // draw labels
            if(i == 0 || j == 0){
                Float_t xoffset = 0.1*(i==0 && nCentBin>1);
                TLegend *leg0 = new TLegend(0.36+xoffset,0.58,0.76+xoffset,0.95);
                leg0->SetFillStyle(0);
                leg0->SetBorderSize(0);
                leg0->SetTextSize(0.08);
                if(i == 0 && j == 0){
                    TString label = coll + " " + jetAnaLabel;
                    leg0->AddEntry(widthHist[i][j],label,"");
                    leg0->AddEntry(widthHist[i][j],collHistLabel1,"");
                    leg0->AddEntry(widthHist[i][j],collHistLabel2,"");
                }
                if(j == 0 && nCentBin > 1){
                    leg0->AddEntry(widthHist[i][j],
                        Form("%d- %d%c",centBin[i],centBin[i+1],'%'),"");
                }
                if(i == 0){
                    leg0->AddEntry(widthHist[i][j],
                        Form("%.1f < |#eta| < %.1f",absEtaBin[j],absEtaBin[j+1]),"");
                }
                
                leg0->Draw();
            }
            
            TF1 *fit = widthHist[i][j]->GetFunction("widthFit");
            for(Int_t k = 0; k < nFitParam; ++k){
                FitParam[k][i][j] = fit->GetParameter(k);
                FitParamErr[k][i][j] = fit->GetParError(k);
            }
        }
    }
    // save canvas if autosave is on
    if(autosave){
        cwidth->SaveAs(Form("%s%swidth.png",coll.Data(),jetAnaLabel.Data()));
    }
    
    /*
    // print results to file
    TString result_file_name = coll + "resCoeff.h";
    std::ofstream outf(result_file_name.Data());
    outf << "// binning used\nconst Int_t nCentBin = " << nCentBin << ";\n"
        << "Int_t centBin[nCentBin + 1] = {" << centBin[0];
    for(Int_t i = 1; i <= nCentBin; ++i){
        outf << ", " << centBin[i];
    }
    outf << "};\n";
    outf << "// coefficients in fit function y = " << fitStr;
    if(nCentBin == 1){
        outf << "Double_t";
        for(Int_t i = 0; i < nFitParam - 1; ++i){
            outf << " " << coll << "C" << i << " = " << FitParam[i][0] << ",";
        }
        outf << " " << coll << "C" << (nFitParam-1) << " = " << FitParam[nFitParam-1][0] 
            << ";\n\n// errors\nDouble_t";
        for(Int_t i = 0; i < nFitParam - 1; ++i){
            outf << " " << coll << "C" << i << "Err = " << FitParamErr[i][0] << ",";
        }
        outf << " " << coll << "C" << (nFitParam-1) << "Err = " << FitParamErr[nFitParam-1][0] << ";";
    }else{
        for(Int_t i = 0; i < nFitParam; ++i){
            outf << "Double_t " << coll << "C" << i << "[" << nCentBin << "] = {";
            for(Int_t j = 0; j < nCentBin - 1; ++j){
                outf << "\n    " << FitParam[i][j] << ",";
            }
            outf << "\n    " << FitParam[i][nCentBin-1] << "\n};\n\n";
        }
        
        outf << "// errors\n";
        for(Int_t i = 0; i < nFitParam; ++i){
            outf << "Double_t " << coll << "C" << i << "Err[" << nCentBin << "] = {";
            for(Int_t j = 0; j < nCentBin - 1; ++j){
                outf << "\n    " << FitParamErr[i][j] << ",";
            }
            outf << "\n    " << FitParamErr[i][nCentBin-1] << "\n};\n\n";
        }
    }*/
    
    out_hist_file->Write();
}




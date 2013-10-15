{
//=========Macro generated from canvas: c1/
//=========  (Tue Oct 15 23:51:14 2013) by ROOT version5.32/01
   TCanvas *c1 = new TCanvas("c1", "",0,22,1100,330);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(0);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.15);
   c1->SetRightMargin(0.08);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.15);
   c1->SetFrameLineColor(0);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p_0_0
   TPad *p_0_0 = new TPad("p_0_0", "p_0_0",0,0,0.3034431,0.9829488);
   p_0_0->Draw();
   p_0_0->cd();
   p_0_0->Range(-0.6299473,-0.5975904,1.999,2.053012);
   p_0_0->SetFillColor(0);
   p_0_0->SetBorderMode(0);
   p_0_0->SetBorderSize(0);
   p_0_0->SetTickx(1);
   p_0_0->SetTicky(1);
   p_0_0->SetLeftMargin(0.24);
   p_0_0->SetRightMargin(0);
   p_0_0->SetTopMargin(0.02);
   p_0_0->SetBottomMargin(0.15);
   p_0_0->SetFrameLineColor(0);
   p_0_0->SetFrameBorderMode(0);
   p_0_0->SetFrameLineColor(0);
   p_0_0->SetFrameBorderMode(0);
   Double_t xAxis1[11] = {0.001, 0.2008, 0.4006, 0.6003999, 0.8001999, 0.9999999, 1.1998, 1.3996, 1.5994, 1.7992, 1.999}; 
   
   TH1D *htemp41_3__1 = new TH1D("htemp41_3__1","",10, xAxis1);
   htemp41_3__1->SetMinimum(-0.2);
   htemp41_3__1->SetMaximum(2);
   htemp41_3__1->SetEntries(3071.983);
   htemp41_3__1->SetDirectory(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#6699cc");
   htemp41_3__1->SetFillColor(ci);
   htemp41_3__1->SetFillStyle(3005);

   ci = TColor::GetColor("#0000ff");
   htemp41_3__1->SetLineColor(ci);
   htemp41_3__1->SetLineStyle(0);
   htemp41_3__1->SetMarkerStyle(20);
   htemp41_3__1->GetXaxis()->SetTitle("x_{J#gamma} = p^{Jet}_{T}/p^{#gamma}_{T}");
   htemp41_3__1->GetXaxis()->CenterTitle(true);
   htemp41_3__1->GetXaxis()->SetNdivisions(505);
   htemp41_3__1->GetXaxis()->SetLabelFont(43);
   htemp41_3__1->GetXaxis()->SetLabelOffset(0.01);
   htemp41_3__1->GetXaxis()->SetLabelSize(18);
   htemp41_3__1->GetXaxis()->SetTitleSize(20);
   htemp41_3__1->GetXaxis()->SetTitleFont(43);
   htemp41_3__1->GetYaxis()->SetTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dx_{J#gamma}}");
   htemp41_3__1->GetYaxis()->CenterTitle(true);
   htemp41_3__1->GetYaxis()->SetLabelFont(43);
   htemp41_3__1->GetYaxis()->SetLabelOffset(0.01);
   htemp41_3__1->GetYaxis()->SetLabelSize(18);
   htemp41_3__1->GetYaxis()->SetTitleSize(20);
   htemp41_3__1->GetYaxis()->SetTitleOffset(1.5);
   htemp41_3__1->GetYaxis()->SetTitleFont(43);
   htemp41_3__1->GetZaxis()->SetLabelFont(42);
   htemp41_3__1->GetZaxis()->SetLabelSize(0.045);
   htemp41_3__1->GetZaxis()->SetTitleSize(0.035);
   htemp41_3__1->GetZaxis()->SetTitleFont(42);
   htemp41_3__1->Draw("hist");
   TBox *box = new TBox(0,0,0.2,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.2,0.1676601,0.4,0.1930733);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.4,1.151595,0.6,1.296448);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.6,0.827655,0.8,0.9702916);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.8,0.3356406,1,0.4199955);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.3498298,1.2,0.4781365);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.2,0.2035208,1.4,0.3090675);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.4,0.03283636,1.6,0.05635633);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.6,0.006894562,1.8,0.01364293);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.8,0,2,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,0,0.2,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.2,0.1422469,0.4,0.1676601);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.4,1.006741,0.6,1.151595);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.6,0.9702916,0.8,1.112928);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.8,0.4199955,1,0.5043504);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.4781365,1.2,0.6064431);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.2,0.3090675,1.4,0.4146141);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.4,0.05635633,1.6,0.07987629);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.6,0.01364293,1.8,0.02039129);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.8,0,2,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0,0.25,0.03798449);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0,0.375,0.2089147);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.308163,0.5,0.4215641);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.5216562,0.625,0.6949097);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7687801,0.75,0.9333563);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.9796426,0.875,1.235284);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.9196683,1,1.045617);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.4887609,1.125,0.7738113);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.2215541,1.25,0.3940136);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.0591431,1.375,0.1700321);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,0.06124709,1.5,0.08119473);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.011469,1.625,0.03601161);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.01573986,1.75,0.04123686);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0,1.875,0.02848836);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0,2,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2,0.003719088,2.125,0.005777033);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.625,0,2.75,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   
   TH1D *xjg_icent15099_final = new TH1D("xjg_icent15099_final","",40,0,5);
   xjg_icent15099_final->SetBinContent(2,0.01899224);
   xjg_icent15099_final->SetBinContent(3,0.1044573);
   xjg_icent15099_final->SetBinContent(4,0.3648635);
   xjg_icent15099_final->SetBinContent(5,0.608283);
   xjg_icent15099_final->SetBinContent(6,0.8510682);
   xjg_icent15099_final->SetBinContent(7,1.107463);
   xjg_icent15099_final->SetBinContent(8,0.9826426);
   xjg_icent15099_final->SetBinContent(9,0.6312861);
   xjg_icent15099_final->SetBinContent(10,0.3077838);
   xjg_icent15099_final->SetBinContent(11,0.1145876);
   xjg_icent15099_final->SetBinContent(12,0.07122091);
   xjg_icent15099_final->SetBinContent(13,0.0237403);
   xjg_icent15099_final->SetBinContent(14,0.02848836);
   xjg_icent15099_final->SetBinContent(15,0.01424418);
   xjg_icent15099_final->SetBinContent(16,0.004748061);
   xjg_icent15099_final->SetBinContent(17,0.004748061);
   xjg_icent15099_final->SetBinContent(22,0.004748061);
   xjg_icent15099_final->SetBinError(2,0.009496121);
   xjg_icent15099_final->SetBinError(3,0.02227038);
   xjg_icent15099_final->SetBinError(4,0.04470348);
   xjg_icent15099_final->SetBinError(5,0.05960856);
   xjg_icent15099_final->SetBinError(6,0.07003888);
   xjg_icent15099_final->SetBinError(7,0.07824848);
   xjg_icent15099_final->SetBinError(8,0.07481089);
   xjg_icent15099_final->SetBinError(9,0.06267701);
   xjg_icent15099_final->SetBinError(10,0.04682835);
   xjg_icent15099_final->SetBinError(11,0.02726855);
   xjg_icent15099_final->SetBinError(12,0.01838916);
   xjg_icent15099_final->SetBinError(13,0.01061699);
   xjg_icent15099_final->SetBinError(14,0.01163033);
   xjg_icent15099_final->SetBinError(15,0.008223882);
   xjg_icent15099_final->SetBinError(16,0.004748061);
   xjg_icent15099_final->SetBinError(17,0.004748061);
   xjg_icent15099_final->SetBinError(22,0.004748061);
   xjg_icent15099_final->SetEntries(905.8923);
   xjg_icent15099_final->SetLineStyle(0);
   xjg_icent15099_final->SetMarkerStyle(21);
   xjg_icent15099_final->GetXaxis()->SetTitle("p_{T}^{Jet}/p_{T}^{#gamma}  ");
   xjg_icent15099_final->GetXaxis()->CenterTitle(true);
   xjg_icent15099_final->GetXaxis()->SetLabelFont(42);
   xjg_icent15099_final->GetXaxis()->SetLabelOffset(0.01);
   xjg_icent15099_final->GetXaxis()->SetLabelSize(0.045);
   xjg_icent15099_final->GetXaxis()->SetTitleSize(0.055);
   xjg_icent15099_final->GetXaxis()->SetTitleFont(42);
   xjg_icent15099_final->GetYaxis()->SetTitle(" ");
   xjg_icent15099_final->GetYaxis()->CenterTitle(true);
   xjg_icent15099_final->GetYaxis()->SetLabelFont(42);
   xjg_icent15099_final->GetYaxis()->SetLabelOffset(0.01);
   xjg_icent15099_final->GetYaxis()->SetLabelSize(0.045);
   xjg_icent15099_final->GetYaxis()->SetTitleSize(0.055);
   xjg_icent15099_final->GetYaxis()->SetTitleOffset(1.25);
   xjg_icent15099_final->GetYaxis()->SetTitleFont(42);
   xjg_icent15099_final->GetZaxis()->SetLabelFont(42);
   xjg_icent15099_final->GetZaxis()->SetLabelSize(0.045);
   xjg_icent15099_final->GetZaxis()->SetTitleSize(0.035);
   xjg_icent15099_final->GetZaxis()->SetTitleFont(42);
   xjg_icent15099_final->Draw("same ");
   Double_t xAxis2[11] = {0.001, 0.2008, 0.4006, 0.6003999, 0.8001999, 0.9999999, 1.1998, 1.3996, 1.5994, 1.7992, 1.999}; 
   
   TH1D *dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm = new TH1D("dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm","",10, xAxis2);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(2,0.1676601);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(3,1.151595);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(4,0.9702916);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(5,0.4199955);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(6,0.4781365);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(7,0.3090675);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(8,0.05635633);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinContent(9,0.01364293);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(2,0.09762219);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(3,0.2711561);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(4,0.242889);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(5,0.2214927);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(6,0.1881734);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(7,0.1608761);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(8,0.05635633);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetBinError(9,0.070714);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetEntries(48.82122);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetLineColor(2);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetLineStyle(0);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetMarkerColor(2);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->SetMarkerStyle(20);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetXaxis()->CenterTitle(true);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->CenterTitle(true);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleOffset(1.25);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleSize(0.035);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm->Draw("same");
   TLine *line = new TLine(0,0,2,0);
   line->Draw();
   
   TLegend *leg = new TLegend(0.2916647,0.7545885,0.9862476,0.9769226,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(43);
   leg->SetTextSize(17);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("xjg_icent15099_final","pp Data (Smeared), 5.3 pb^{-1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("dataSrc1_reco1_cent3SubtractedExtrapExtrapNorm","PbPb Data, 150#mub^{-1}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("dataSrc0_reco1_cent3SubtractedExtrapExtrapNorm","","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   TLatex *   tex = new TLatex(0.65,0.74,"#sqrt{s_{NN}}=2.76 TeV ");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(15);
   tex->Draw();
      tex = new TLatex(0.72,0.6,"50% - 100%");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(16);
   tex->Draw();
      tex = new TLatex(0.275,0.9,"(a)");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis3[11] = {0.001, 0.2008, 0.4006, 0.6003999, 0.8001999, 0.9999999, 1.1998, 1.3996, 1.5994, 1.7992, 1.999}; 
   
   TH1D *htemp41_3__2 = new TH1D("htemp41_3__2","",10, xAxis3);
   htemp41_3__2->SetMinimum(-0.2);
   htemp41_3__2->SetMaximum(2);
   htemp41_3__2->SetEntries(3071.983);
   htemp41_3__2->SetDirectory(0);

   ci = TColor::GetColor("#6699cc");
   htemp41_3__2->SetFillColor(ci);
   htemp41_3__2->SetFillStyle(3005);

   ci = TColor::GetColor("#0000ff");
   htemp41_3__2->SetLineColor(ci);
   htemp41_3__2->SetLineStyle(0);
   htemp41_3__2->SetMarkerStyle(20);
   htemp41_3__2->GetXaxis()->SetTitle("x_{J#gamma} = p^{Jet}_{T}/p^{#gamma}_{T}");
   htemp41_3__2->GetXaxis()->CenterTitle(true);
   htemp41_3__2->GetXaxis()->SetNdivisions(505);
   htemp41_3__2->GetXaxis()->SetLabelFont(43);
   htemp41_3__2->GetXaxis()->SetLabelOffset(0.01);
   htemp41_3__2->GetXaxis()->SetLabelSize(18);
   htemp41_3__2->GetXaxis()->SetTitleSize(20);
   htemp41_3__2->GetXaxis()->SetTitleFont(43);
   htemp41_3__2->GetYaxis()->SetTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dx_{J#gamma}}");
   htemp41_3__2->GetYaxis()->CenterTitle(true);
   htemp41_3__2->GetYaxis()->SetLabelFont(43);
   htemp41_3__2->GetYaxis()->SetLabelOffset(0.01);
   htemp41_3__2->GetYaxis()->SetLabelSize(18);
   htemp41_3__2->GetYaxis()->SetTitleSize(20);
   htemp41_3__2->GetYaxis()->SetTitleOffset(1.5);
   htemp41_3__2->GetYaxis()->SetTitleFont(43);
   htemp41_3__2->GetZaxis()->SetLabelFont(42);
   htemp41_3__2->GetZaxis()->SetLabelSize(0.045);
   htemp41_3__2->GetZaxis()->SetTitleSize(0.035);
   htemp41_3__2->GetZaxis()->SetTitleFont(42);
   htemp41_3__2->Draw("sameaxis");
   p_0_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_1_0
   p_1_0 = new TPad("p_1_0", "p_1_0",0.3034431,0,0.5340599,0.9829488);
   p_1_0->Draw();
   p_1_0->cd();
   p_1_0->Range(0.001,-0.5975904,1.999,2.053012);
   p_1_0->SetFillColor(0);
   p_1_0->SetBorderMode(0);
   p_1_0->SetBorderSize(0);
   p_1_0->SetTickx(1);
   p_1_0->SetTicky(1);
   p_1_0->SetLeftMargin(0);
   p_1_0->SetRightMargin(0);
   p_1_0->SetTopMargin(0.02);
   p_1_0->SetBottomMargin(0.15);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   Double_t xAxis4[17] = {0.001, 0.125875, 0.25075, 0.375625, 0.5005, 0.625375, 0.7502499, 0.8751249, 0.9999999, 1.124875, 1.24975, 1.374625, 1.4995, 1.624375, 1.74925, 1.874125, 1.999}; 
   
   TH1D *htemp41_2__3 = new TH1D("htemp41_2__3","",16, xAxis4);
   htemp41_2__3->SetMinimum(-0.2);
   htemp41_2__3->SetMaximum(2);
   htemp41_2__3->SetEntries(3404.768);
   htemp41_2__3->SetDirectory(0);

   ci = TColor::GetColor("#6699cc");
   htemp41_2__3->SetFillColor(ci);
   htemp41_2__3->SetFillStyle(3005);

   ci = TColor::GetColor("#0000ff");
   htemp41_2__3->SetLineColor(ci);
   htemp41_2__3->SetLineStyle(0);
   htemp41_2__3->SetMarkerStyle(20);
   htemp41_2__3->GetXaxis()->SetTitle("x_{J#gamma} = p^{Jet}_{T}/p^{#gamma}_{T}");
   htemp41_2__3->GetXaxis()->CenterTitle(true);
   htemp41_2__3->GetXaxis()->SetNdivisions(505);
   htemp41_2__3->GetXaxis()->SetLabelFont(43);
   htemp41_2__3->GetXaxis()->SetLabelOffset(0.01);
   htemp41_2__3->GetXaxis()->SetLabelSize(18);
   htemp41_2__3->GetXaxis()->SetTitleSize(20);
   htemp41_2__3->GetXaxis()->SetTitleFont(43);
   htemp41_2__3->GetYaxis()->SetTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dx_{J#gamma}}");
   htemp41_2__3->GetYaxis()->CenterTitle(true);
   htemp41_2__3->GetYaxis()->SetLabelFont(43);
   htemp41_2__3->GetYaxis()->SetLabelOffset(0.01);
   htemp41_2__3->GetYaxis()->SetLabelSize(18);
   htemp41_2__3->GetYaxis()->SetTitleSize(20);
   htemp41_2__3->GetYaxis()->SetTitleOffset(1.5);
   htemp41_2__3->GetYaxis()->SetTitleFont(43);
   htemp41_2__3->GetZaxis()->SetLabelFont(42);
   htemp41_2__3->GetZaxis()->SetLabelSize(0.045);
   htemp41_2__3->GetZaxis()->SetTitleSize(0.035);
   htemp41_2__3->GetZaxis()->SetTitleFont(42);
   htemp41_2__3->Draw("hist");
   box = new TBox(0,0,0.125,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0.03210556,0.25,0.04277297);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0.03169846,0.375,0.04000549);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.4164541,0.5,0.4986426);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.6906304,0.625,0.7912097);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.6277765,0.75,0.7169184);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.599439,0.875,0.7030026);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.5799721,1,0.7248151);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.5349627,1.125,0.727711);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.04952937,1.25,0.07450416);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.120581,1.375,0.203729);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,-0.02100988,1.5,-0.01087355);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.01583883,1.625,0.03580412);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0,1.75,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0.00932909,1.875,0.03210556);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,-0.028407,2,-0.006085591);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,0,0.125,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0.02143815,0.25,0.03210556);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0.02339144,0.375,0.03169846);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.3342655,0.5,0.4164541);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.5900511,0.625,0.6906304);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7169184,0.75,0.8060604);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.7030026,0.875,0.8065662);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.7248151,1,0.8696581);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.727711,1.125,0.9204594);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.07450416,1.25,0.09947896);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.203729,1.375,0.2868771);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,-0.03114621,1.5,-0.02100988);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.03580412,1.625,0.05576941);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0,1.75,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0.03210556,1.875,0.05488203);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,-0.05072841,2,-0.028407);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0,0.25,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0,0.375,0.1871798);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.305311,0.5,0.4176626);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.5705188,0.625,0.7600006);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7375185,0.75,0.8954025);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.9826296,0.875,1.239051);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.8613058,1,0.9792615);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.5055887,1.125,0.8004532);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.220567,1.25,0.3922581);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.07068861,1.375,0.2032246);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,0.05308081,1.5,0.07036877);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.0183504,1.625,0.05761857);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.007869932,1.75,0.02061843);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0,1.875,0.03798449);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0,2,0.02848836);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.625,0,2.75,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   
   TH1D *xjg_icent13050_final = new TH1D("xjg_icent13050_final","",40,0,5);
   xjg_icent13050_final->SetBinContent(2,0.004748061);
   xjg_icent13050_final->SetBinContent(3,0.09358991);
   xjg_icent13050_final->SetBinContent(4,0.3614868);
   xjg_icent13050_final->SetBinContent(5,0.6652597);
   xjg_icent13050_final->SetBinContent(6,0.8164605);
   xjg_icent13050_final->SetBinContent(7,1.11084);
   xjg_icent13050_final->SetBinContent(8,0.9202837);
   xjg_icent13050_final->SetBinContent(9,0.653021);
   xjg_icent13050_final->SetBinContent(10,0.3064125);
   xjg_icent13050_final->SetBinContent(11,0.1369566);
   xjg_icent13050_final->SetBinContent(12,0.06172479);
   xjg_icent13050_final->SetBinContent(13,0.03798449);
   xjg_icent13050_final->SetBinContent(14,0.01424418);
   xjg_icent13050_final->SetBinContent(15,0.01899224);
   xjg_icent13050_final->SetBinContent(16,0.01424418);
   xjg_icent13050_final->SetBinContent(22,0.004748061);
   xjg_icent13050_final->SetBinError(2,0.004748061);
   xjg_icent13050_final->SetBinError(3,0.02260248);
   xjg_icent13050_final->SetBinError(4,0.04377061);
   xjg_icent13050_final->SetBinError(5,0.06183615);
   xjg_icent13050_final->SetBinError(6,0.06933705);
   xjg_icent13050_final->SetBinError(7,0.07877411);
   xjg_icent13050_final->SetBinError(8,0.07142185);
   xjg_icent13050_final->SetBinError(9,0.06243879);
   xjg_icent13050_final->SetBinError(10,0.04746457);
   xjg_icent13050_final->SetBinError(11,0.0302702);
   xjg_icent13050_final->SetBinError(12,0.01711938);
   xjg_icent13050_final->SetBinError(13,0.01342954);
   xjg_icent13050_final->SetBinError(14,0.008223882);
   xjg_icent13050_final->SetBinError(15,0.009496121);
   xjg_icent13050_final->SetBinError(16,0.008223882);
   xjg_icent13050_final->SetBinError(22,0.004748061);
   xjg_icent13050_final->SetEntries(903.3201);
   xjg_icent13050_final->SetLineStyle(0);
   xjg_icent13050_final->SetMarkerStyle(21);
   xjg_icent13050_final->GetXaxis()->SetTitle("p_{T}^{Jet}/p_{T}^{#gamma}  ");
   xjg_icent13050_final->GetXaxis()->CenterTitle(true);
   xjg_icent13050_final->GetXaxis()->SetLabelFont(42);
   xjg_icent13050_final->GetXaxis()->SetLabelOffset(0.01);
   xjg_icent13050_final->GetXaxis()->SetLabelSize(0.045);
   xjg_icent13050_final->GetXaxis()->SetTitleSize(0.055);
   xjg_icent13050_final->GetXaxis()->SetTitleFont(42);
   xjg_icent13050_final->GetYaxis()->SetTitle(" ");
   xjg_icent13050_final->GetYaxis()->CenterTitle(true);
   xjg_icent13050_final->GetYaxis()->SetLabelFont(42);
   xjg_icent13050_final->GetYaxis()->SetLabelOffset(0.01);
   xjg_icent13050_final->GetYaxis()->SetLabelSize(0.045);
   xjg_icent13050_final->GetYaxis()->SetTitleSize(0.055);
   xjg_icent13050_final->GetYaxis()->SetTitleOffset(1.25);
   xjg_icent13050_final->GetYaxis()->SetTitleFont(42);
   xjg_icent13050_final->GetZaxis()->SetLabelFont(42);
   xjg_icent13050_final->GetZaxis()->SetLabelSize(0.045);
   xjg_icent13050_final->GetZaxis()->SetTitleSize(0.035);
   xjg_icent13050_final->GetZaxis()->SetTitleFont(42);
   xjg_icent13050_final->Draw("same ");
   Double_t xAxis5[17] = {0.001, 0.125875, 0.25075, 0.375625, 0.5005, 0.625375, 0.7502499, 0.8751249, 0.9999999, 1.124875, 1.24975, 1.374625, 1.4995, 1.624375, 1.74925, 1.874125, 1.999}; 
   
   TH1D *dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm = new TH1D("dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm","",16, xAxis5);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(2,0.03210556);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(3,0.03169846);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(4,0.4164541);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(5,0.6906304);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(6,0.7169184);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(7,0.7030026);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(8,0.7248151);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(9,0.727711);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(10,0.07450416);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(11,0.203729);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(12,-0.02100988);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(13,0.03580412);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(15,0.03210556);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(16,-0.028407);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinContent(17,0.00369856);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(2,0.03210556);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(3,0.05359908);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(4,0.144114);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(5,0.1858099);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(6,0.1733012);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(7,0.190653);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(8,0.1785091);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(9,0.1835861);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(10,0.0870365);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(11,0.1081563);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(12,0.06695078);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(13,0.0535583);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(15,0.03210556);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(16,0.028407);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetBinError(17,0.04286869);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetEntries(89.72144);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetLineColor(2);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetLineStyle(0);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetMarkerColor(2);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->SetMarkerStyle(20);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetXaxis()->CenterTitle(true);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->CenterTitle(true);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleOffset(1.25);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleSize(0.035);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent2SubtractedExtrapExtrapNorm->Draw("same");
   line = new TLine(0,0,2,0);
   line->Draw();
   
   leg = new TLegend(0.2796373,0.7545885,0.9742202,0.9937661,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(43);
   leg->SetTextSize(17);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("dataSrc2_reco1_cent0SubtractedExtrapExtrapNorm","","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
      tex = new TLatex(0.2,0.9,"p^{#gamma}_{T} > 60 GeV/c     |#eta^{#gamma}| < 1.44");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(15);
   tex->Draw();
      tex = new TLatex(0.2,0.8,"p^{Jet}_{T} > 30 GeV/c    |#eta^{Jet}| < 1.6");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(15);
   tex->Draw();
      tex = new TLatex(0.6,0.7,"#Delta#phi_{J#gamma} > #frac{7}{8}#pi");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(15);
   tex->Draw();
      tex = new TLatex(0.67,0.6,"30% - 50%");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(16);
   tex->Draw();
      tex = new TLatex(0.05,0.9,"(b)");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(18);
   tex->Draw();
   p_1_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_2_0
   p_2_0 = new TPad("p_2_0", "p_2_0",0.5340599,0,0.7646767,0.9829488);
   p_2_0->Draw();
   p_2_0->cd();
   p_2_0->Range(0.001,-0.5975904,1.999,2.053012);
   p_2_0->SetFillColor(0);
   p_2_0->SetBorderMode(0);
   p_2_0->SetBorderSize(0);
   p_2_0->SetTickx(1);
   p_2_0->SetTicky(1);
   p_2_0->SetLeftMargin(0);
   p_2_0->SetRightMargin(0);
   p_2_0->SetTopMargin(0.02);
   p_2_0->SetBottomMargin(0.15);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   Double_t xAxis6[17] = {0.001, 0.125875, 0.25075, 0.375625, 0.5005, 0.625375, 0.7502499, 0.8751249, 0.9999999, 1.124875, 1.24975, 1.374625, 1.4995, 1.624375, 1.74925, 1.874125, 1.999}; 
   
   TH1D *htemp41_1__4 = new TH1D("htemp41_1__4","",16, xAxis6);
   htemp41_1__4->SetMinimum(-0.2);
   htemp41_1__4->SetMaximum(2);
   htemp41_1__4->SetEntries(4465.953);
   htemp41_1__4->SetDirectory(0);

   ci = TColor::GetColor("#6699cc");
   htemp41_1__4->SetFillColor(ci);
   htemp41_1__4->SetFillStyle(3005);

   ci = TColor::GetColor("#0000ff");
   htemp41_1__4->SetLineColor(ci);
   htemp41_1__4->SetLineStyle(0);
   htemp41_1__4->SetMarkerStyle(20);
   htemp41_1__4->GetXaxis()->SetTitle("x_{J#gamma} = p^{Jet}_{T}/p^{#gamma}_{T}");
   htemp41_1__4->GetXaxis()->CenterTitle(true);
   htemp41_1__4->GetXaxis()->SetNdivisions(505);
   htemp41_1__4->GetXaxis()->SetLabelFont(43);
   htemp41_1__4->GetXaxis()->SetLabelOffset(0.01);
   htemp41_1__4->GetXaxis()->SetLabelSize(18);
   htemp41_1__4->GetXaxis()->SetTitleSize(20);
   htemp41_1__4->GetXaxis()->SetTitleFont(43);
   htemp41_1__4->GetYaxis()->SetTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dx_{J#gamma}}");
   htemp41_1__4->GetYaxis()->CenterTitle(true);
   htemp41_1__4->GetYaxis()->SetLabelFont(43);
   htemp41_1__4->GetYaxis()->SetLabelOffset(0.01);
   htemp41_1__4->GetYaxis()->SetLabelSize(18);
   htemp41_1__4->GetYaxis()->SetTitleSize(20);
   htemp41_1__4->GetYaxis()->SetTitleOffset(1.5);
   htemp41_1__4->GetYaxis()->SetTitleFont(43);
   htemp41_1__4->GetZaxis()->SetLabelFont(42);
   htemp41_1__4->GetZaxis()->SetLabelSize(0.045);
   htemp41_1__4->GetZaxis()->SetTitleSize(0.035);
   htemp41_1__4->GetZaxis()->SetTitleFont(42);
   htemp41_1__4->Draw("hist");
   box = new TBox(0,0,0.125,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0.02012973,0.25,0.02882911);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0.2218086,0.375,0.3015373);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.7038208,0.5,0.9075729);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.7630395,0.625,0.9346454);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7676714,0.75,0.8995657);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.7495849,0.875,0.8572411);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.4256139,1,0.5034503);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.2281416,1.125,0.2845938);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.02768955,1.25,0.03735593);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.01951687,1.375,0.02898729);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,0.03095537,1.5,0.05145125);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.01118713,1.625,0.02118856);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.001337368,1.75,0.002951521);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0,1.875,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0,2,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,0,0.125,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0.01143036,0.25,0.02012973);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0.1420799,0.375,0.2218086);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.5000686,0.5,0.7038208);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.5914337,0.625,0.7630395);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.635777,0.75,0.7676714);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.6419288,0.875,0.7495849);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.5034503,1,0.5812867);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.2845938,1.125,0.3410461);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.03735593,1.25,0.04702232);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.02898729,1.375,0.03845771);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,0.05145125,1.5,0.07194713);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.02118856,1.625,0.03118999);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.002951521,1.75,0.004565673);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0,1.875,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0,2,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0,0.25,0.03798449);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0,0.375,0.1899224);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.3213518,0.5,0.4396063);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.630421,0.625,0.8397976);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7994688,0.75,0.9706147);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.8097755,0.875,1.02109);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,1.00479,1,1.142396);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.4987275,1.125,0.7895905);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.2255026,1.25,0.4010355);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.06333663,1.375,0.1820882);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,0.07522112,1.5,0.09971999);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.011469,1.625,0.03601161);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.01049324,1.75,0.02749124);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0,1.875,0.04748061);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0,2,0.01899224);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.75,0,2.875,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   
   TH1D *xjg_icent11030_final = new TH1D("xjg_icent11030_final","",40,0,5);
   xjg_icent11030_final->SetBinContent(2,0.01899224);
   xjg_icent11030_final->SetBinContent(3,0.09496121);
   xjg_icent11030_final->SetBinContent(4,0.380479);
   xjg_icent11030_final->SetBinContent(5,0.7351093);
   xjg_icent11030_final->SetBinContent(6,0.8850418);
   xjg_icent11030_final->SetBinContent(7,0.9154326);
   xjg_icent11030_final->SetBinContent(8,1.073593);
   xjg_icent11030_final->SetBinContent(9,0.644159);
   xjg_icent11030_final->SetBinContent(10,0.313269);
   xjg_icent11030_final->SetBinContent(11,0.1227124);
   xjg_icent11030_final->SetBinContent(12,0.08747055);
   xjg_icent11030_final->SetBinContent(13,0.0237403);
   xjg_icent11030_final->SetBinContent(14,0.01899224);
   xjg_icent11030_final->SetBinContent(15,0.0237403);
   xjg_icent11030_final->SetBinContent(16,0.009496121);
   xjg_icent11030_final->SetBinContent(23,0.004748061);
   xjg_icent11030_final->SetBinError(2,0.009496121);
   xjg_icent11030_final->SetBinError(3,0.02123397);
   xjg_icent11030_final->SetBinError(4,0.04478886);
   xjg_icent11030_final->SetBinError(5,0.06497586);
   xjg_icent11030_final->SetBinError(6,0.06928742);
   xjg_icent11030_final->SetBinError(7,0.07445508);
   xjg_icent11030_final->SetBinError(8,0.07591114);
   xjg_icent11030_final->SetBinError(9,0.06368698);
   xjg_icent11030_final->SetBinError(10,0.04419199);
   xjg_icent11030_final->SetBinError(11,0.02913164);
   xjg_icent11030_final->SetBinError(12,0.02341621);
   xjg_icent11030_final->SetBinError(13,0.01061699);
   xjg_icent11030_final->SetBinError(14,0.009496121);
   xjg_icent11030_final->SetBinError(15,0.01061699);
   xjg_icent11030_final->SetBinError(16,0.006714772);
   xjg_icent11030_final->SetBinError(23,0.004748061);
   xjg_icent11030_final->SetEntries(934.0706);
   xjg_icent11030_final->SetLineStyle(0);
   xjg_icent11030_final->SetMarkerStyle(21);
   xjg_icent11030_final->GetXaxis()->SetTitle("p_{T}^{Jet}/p_{T}^{#gamma}  ");
   xjg_icent11030_final->GetXaxis()->CenterTitle(true);
   xjg_icent11030_final->GetXaxis()->SetLabelFont(42);
   xjg_icent11030_final->GetXaxis()->SetLabelOffset(0.01);
   xjg_icent11030_final->GetXaxis()->SetLabelSize(0.045);
   xjg_icent11030_final->GetXaxis()->SetTitleSize(0.055);
   xjg_icent11030_final->GetXaxis()->SetTitleFont(42);
   xjg_icent11030_final->GetYaxis()->SetTitle(" ");
   xjg_icent11030_final->GetYaxis()->CenterTitle(true);
   xjg_icent11030_final->GetYaxis()->SetLabelFont(42);
   xjg_icent11030_final->GetYaxis()->SetLabelOffset(0.01);
   xjg_icent11030_final->GetYaxis()->SetLabelSize(0.045);
   xjg_icent11030_final->GetYaxis()->SetTitleSize(0.055);
   xjg_icent11030_final->GetYaxis()->SetTitleOffset(1.25);
   xjg_icent11030_final->GetYaxis()->SetTitleFont(42);
   xjg_icent11030_final->GetZaxis()->SetLabelFont(42);
   xjg_icent11030_final->GetZaxis()->SetLabelSize(0.045);
   xjg_icent11030_final->GetZaxis()->SetTitleSize(0.035);
   xjg_icent11030_final->GetZaxis()->SetTitleFont(42);
   xjg_icent11030_final->Draw("same ");
   Double_t xAxis7[17] = {0.001, 0.125875, 0.25075, 0.375625, 0.5005, 0.625375, 0.7502499, 0.8751249, 0.9999999, 1.124875, 1.24975, 1.374625, 1.4995, 1.624375, 1.74925, 1.874125, 1.999}; 
   
   TH1D *dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm = new TH1D("dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm","",16, xAxis7);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(2,0.02012973);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(3,0.2218086);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(4,0.7038208);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(5,0.7630395);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(6,0.7676714);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(7,0.7495849);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(8,0.5034503);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(9,0.2845938);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(10,0.03735593);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(11,0.02898729);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(12,0.05145125);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(13,0.02118856);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(14,0.002951521);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinContent(17,0.03352256);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(2,0.0174939);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(3,0.06146448);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(4,0.113001);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(5,0.1253968);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(6,0.1167505);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(7,0.1118689);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(8,0.09855131);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(9,0.07851754);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(10,0.04810435);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(11,0.05665766);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(12,0.04070958);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(13,0.02953985);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(14,0.01549704);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetBinError(17,0.03201141);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetEntries(208.369);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetLineColor(2);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetLineStyle(0);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetMarkerColor(2);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->SetMarkerStyle(20);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetXaxis()->CenterTitle(true);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->CenterTitle(true);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleOffset(1.25);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleSize(0.035);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent1SubtractedExtrapExtrapNorm->Draw("same");
   line = new TLine(0,0,2,0);
   line->Draw();
      tex = new TLatex(0.67,0.6,"10% - 30%");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(16);
   tex->Draw();
      tex = new TLatex(0.05,0.9,"(c)");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(18);
   tex->Draw();
   p_2_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_3_0
   p_3_0 = new TPad("p_3_0", "p_3_0",0.7646767,0,1,0.9829488);
   p_3_0->Draw();
   p_3_0->cd();
   p_3_0->Range(0.001,-0.5975904,2.039775,2.053012);
   p_3_0->SetFillColor(0);
   p_3_0->SetBorderMode(0);
   p_3_0->SetBorderSize(0);
   p_3_0->SetTickx(1);
   p_3_0->SetTicky(1);
   p_3_0->SetLeftMargin(0);
   p_3_0->SetRightMargin(0.02);
   p_3_0->SetTopMargin(0.02);
   p_3_0->SetBottomMargin(0.15);
   p_3_0->SetFrameLineColor(0);
   p_3_0->SetFrameBorderMode(0);
   p_3_0->SetFrameLineColor(0);
   p_3_0->SetFrameBorderMode(0);
   Double_t xAxis8[17] = {0.001, 0.125875, 0.25075, 0.375625, 0.5005, 0.625375, 0.7502499, 0.8751249, 0.9999999, 1.124875, 1.24975, 1.374625, 1.4995, 1.624375, 1.74925, 1.874125, 1.999}; 
   
   TH1D *htemp41_0__5 = new TH1D("htemp41_0__5","",16, xAxis8);
   htemp41_0__5->SetMinimum(-0.2);
   htemp41_0__5->SetMaximum(2);
   htemp41_0__5->SetEntries(5259.211);
   htemp41_0__5->SetDirectory(0);

   ci = TColor::GetColor("#6699cc");
   htemp41_0__5->SetFillColor(ci);
   htemp41_0__5->SetFillStyle(3005);

   ci = TColor::GetColor("#0000ff");
   htemp41_0__5->SetLineColor(ci);
   htemp41_0__5->SetLineStyle(0);
   htemp41_0__5->SetMarkerStyle(20);
   htemp41_0__5->GetXaxis()->SetTitle("x_{J#gamma} = p^{Jet}_{T}/p^{#gamma}_{T}");
   htemp41_0__5->GetXaxis()->CenterTitle(true);
   htemp41_0__5->GetXaxis()->SetNdivisions(505);
   htemp41_0__5->GetXaxis()->SetLabelFont(43);
   htemp41_0__5->GetXaxis()->SetLabelOffset(0.01);
   htemp41_0__5->GetXaxis()->SetLabelSize(18);
   htemp41_0__5->GetXaxis()->SetTitleSize(20);
   htemp41_0__5->GetXaxis()->SetTitleFont(43);
   htemp41_0__5->GetYaxis()->SetTitle("#frac{1}{N_{#gamma}} #frac{dN_{J#gamma}}{dx_{J#gamma}}");
   htemp41_0__5->GetYaxis()->CenterTitle(true);
   htemp41_0__5->GetYaxis()->SetLabelFont(43);
   htemp41_0__5->GetYaxis()->SetLabelOffset(0.01);
   htemp41_0__5->GetYaxis()->SetLabelSize(18);
   htemp41_0__5->GetYaxis()->SetTitleSize(20);
   htemp41_0__5->GetYaxis()->SetTitleOffset(1.5);
   htemp41_0__5->GetYaxis()->SetTitleFont(43);
   htemp41_0__5->GetZaxis()->SetLabelFont(42);
   htemp41_0__5->GetZaxis()->SetLabelSize(0.045);
   htemp41_0__5->GetZaxis()->SetTitleSize(0.035);
   htemp41_0__5->GetZaxis()->SetTitleFont(42);
   htemp41_0__5->Draw("hist");
   box = new TBox(0,0,0.125,0);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0.03621098,0.25,0.05282981);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0.01214314,0.375,0.01678064);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.7226824,0.5,0.9448623);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.8404209,0.625,1.040423);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7432882,0.75,0.8766624);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.40608,0.875,0.4652201);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.568121,1,0.6714192);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.1612023,1.125,0.2012368);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.1298613,1.25,0.1760957);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.07749417,1.375,0.1164052);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,-0.00738839,1.5,-0.004360142);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,-0.007598273,1.625,-0.003893852);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.007408054,1.75,0.017086);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,-0.0234689,1.875,-0.008305847);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0.007751213,2,0.02831771);
   box->SetFillColor(19);
   box->SetFillStyle(0);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,0,0.125,0);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0.01959215,0.25,0.03621098);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0.007505634,0.375,0.01214314);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.5005025,0.5,0.7226824);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.6404184,0.625,0.8404209);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.6099141,0.75,0.7432882);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,0.3469399,0.875,0.40608);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.6714192,1,0.7747175);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.2012368,1.125,0.2412713);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.1760957,1.25,0.2223301);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.1164052,1.375,0.1553163);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,-0.01041664,1.5,-0.00738839);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,-0.01130269,1.625,-0.007598273);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.017086,1.75,0.02676395);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,-0.03863196,1.875,-0.0234689);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0.02831771,2,0.0488842);

   ci = TColor::GetColor("#ff0000");
   box->SetFillColor(ci);
   box->SetFillStyle(3004);

   ci = TColor::GetColor("#ff0000");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.125,0,0.25,0.04748061);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.25,0,0.375,0.2563953);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.375,0.3156478,0.5,0.4318032);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.5,0.5727825,0.625,0.7630161);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.625,0.7253174,0.75,0.8805894);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.75,1.043856,0.875,1.316255);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.875,0.790109,1,0.8983144);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1,0.4809178,1.125,0.7613939);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.125,0.2542888,1.25,0.4522292);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.25,0.06262885,1.375,0.1800534);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.375,0.06006782,1.5,0.0796314);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.5,0.011469,1.625,0.03601161);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.625,0.02098649,1.75,0.05498249);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.75,0,1.875,0.04748061);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(1.875,0,2,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.125,0,2.25,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(2.625,0,2.75,0.009496121);

   ci = TColor::GetColor("#00ff00");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   box->SetLineColor(ci);
   box->Draw();
   
   TH1D *xjg_icent10010_final = new TH1D("xjg_icent10010_final","",40,0,5);
   xjg_icent10010_final->SetBinContent(2,0.0237403);
   xjg_icent10010_final->SetBinContent(3,0.1281976);
   xjg_icent10010_final->SetBinContent(4,0.3737255);
   xjg_icent10010_final->SetBinContent(5,0.6678993);
   xjg_icent10010_final->SetBinContent(6,0.8029534);
   xjg_icent10010_final->SetBinContent(7,1.180056);
   xjg_icent10010_final->SetBinContent(8,0.8442117);
   xjg_icent10010_final->SetBinContent(9,0.6211558);
   xjg_icent10010_final->SetBinContent(10,0.353259);
   xjg_icent10010_final->SetBinContent(11,0.1213411);
   xjg_icent10010_final->SetBinContent(12,0.06984961);
   xjg_icent10010_final->SetBinContent(13,0.0237403);
   xjg_icent10010_final->SetBinContent(14,0.03798449);
   xjg_icent10010_final->SetBinContent(15,0.0237403);
   xjg_icent10010_final->SetBinContent(16,0.004748061);
   xjg_icent10010_final->SetBinContent(18,0.004748061);
   xjg_icent10010_final->SetBinContent(22,0.004748061);
   xjg_icent10010_final->SetBinError(2,0.01061699);
   xjg_icent10010_final->SetBinError(3,0.02467165);
   xjg_icent10010_final->SetBinError(4,0.04290656);
   xjg_icent10010_final->SetBinError(5,0.06456587);
   xjg_icent10010_final->SetBinError(6,0.06691404);
   xjg_icent10010_final->SetBinError(7,0.08000622);
   xjg_icent10010_final->SetBinError(8,0.07214845);
   xjg_icent10010_final->SetBinError(9,0.06066963);
   xjg_icent10010_final->SetBinError(10,0.04770545);
   xjg_icent10010_final->SetBinError(11,0.03014371);
   xjg_icent10010_final->SetBinError(12,0.01995374);
   xjg_icent10010_final->SetBinError(13,0.01061699);
   xjg_icent10010_final->SetBinError(14,0.01342954);
   xjg_icent10010_final->SetBinError(15,0.01061699);
   xjg_icent10010_final->SetBinError(16,0.004748061);
   xjg_icent10010_final->SetBinError(18,0.004748061);
   xjg_icent10010_final->SetBinError(22,0.004748061);
   xjg_icent10010_final->SetEntries(914.6037);
   xjg_icent10010_final->SetLineStyle(0);
   xjg_icent10010_final->SetMarkerStyle(21);
   xjg_icent10010_final->GetXaxis()->SetTitle("p_{T}^{Jet}/p_{T}^{#gamma}  ");
   xjg_icent10010_final->GetXaxis()->CenterTitle(true);
   xjg_icent10010_final->GetXaxis()->SetLabelFont(42);
   xjg_icent10010_final->GetXaxis()->SetLabelOffset(0.01);
   xjg_icent10010_final->GetXaxis()->SetLabelSize(0.045);
   xjg_icent10010_final->GetXaxis()->SetTitleSize(0.055);
   xjg_icent10010_final->GetXaxis()->SetTitleFont(42);
   xjg_icent10010_final->GetYaxis()->SetTitle(" ");
   xjg_icent10010_final->GetYaxis()->CenterTitle(true);
   xjg_icent10010_final->GetYaxis()->SetLabelFont(42);
   xjg_icent10010_final->GetYaxis()->SetLabelOffset(0.01);
   xjg_icent10010_final->GetYaxis()->SetLabelSize(0.045);
   xjg_icent10010_final->GetYaxis()->SetTitleSize(0.055);
   xjg_icent10010_final->GetYaxis()->SetTitleOffset(1.25);
   xjg_icent10010_final->GetYaxis()->SetTitleFont(42);
   xjg_icent10010_final->GetZaxis()->SetLabelFont(42);
   xjg_icent10010_final->GetZaxis()->SetLabelSize(0.045);
   xjg_icent10010_final->GetZaxis()->SetTitleSize(0.035);
   xjg_icent10010_final->GetZaxis()->SetTitleFont(42);
   xjg_icent10010_final->Draw("same ");
   Double_t xAxis9[17] = {0.001, 0.125875, 0.25075, 0.375625, 0.5005, 0.625375, 0.7502499, 0.8751249, 0.9999999, 1.124875, 1.24975, 1.374625, 1.4995, 1.624375, 1.74925, 1.874125, 1.999}; 
   
   TH1D *dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm = new TH1D("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm","",16, xAxis9);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(2,0.03621098);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(3,0.01214314);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(4,0.7226824);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(5,0.8404209);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(6,0.7432882);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(7,0.40608);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(8,0.6714192);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(9,0.2012368);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(10,0.1760957);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(11,0.1164052);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(12,-0.00738839);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(13,-0.007598273);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(14,0.017086);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(15,-0.0234689);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(16,0.02831771);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinContent(17,0.02831771);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(2,0.02694525);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(3,0.05763359);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(4,0.1404906);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(5,0.1451564);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(6,0.1284104);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(7,0.1063397);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(8,0.1194711);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(9,0.08575785);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(10,0.07056235);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(11,0.05482455);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(12,0.03278457);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(13,0.02758503);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(14,0.02840412);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(15,0.01636146);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(16,0.02594444);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetBinError(17,0.02594444);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetEntries(151.9036);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetLineColor(2);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetLineStyle(0);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetMarkerColor(2);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->SetMarkerStyle(20);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetXaxis()->CenterTitle(true);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetXaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetXaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->CenterTitle(true);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelOffset(0.01);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleSize(0.055);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleOffset(1.25);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetYaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelFont(42);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetZaxis()->SetLabelSize(0.045);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleSize(0.035);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->GetZaxis()->SetTitleFont(42);
   dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm->Draw("same");
   line = new TLine(0,0,2,0);
   line->Draw();
      tex = new TLatex(0.67,0.6,"0% - 10%");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(16);
   tex->Draw();
      tex = new TLatex(0.05,0.9,"(d)");
tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(18);
   tex->Draw();
   p_3_0->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}

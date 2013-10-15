#ifndef drawPlotsGammaJetPapers_h
#define drawPlotsGammaJetPapers_h

void drawXSys(int cBin, TH1D * h)
{
   if (cBin==0) {
      TH1D *cent0_systematic_l = new TH1D("cent0_systematic_l","",16,0,2);
      TH1D *cent0_systematic_r = new TH1D("cent0_systematic_r","",16,0,2);
      for (Int_t i = 1; i <= 16; i++) {
         cent0_systematic_l->SetBinContent(i, h->GetBinContent(i));
         cent0_systematic_r->SetBinContent(i, h->GetBinContent(i));
      }
      for (Int_t i = 1; i <= 16; i++) {
         if (cent0_systematic_l->GetBinContent(i) != 0) {
            Float_t x = cent0_systematic_l->GetXaxis()->GetBinCenter(i);
            Float_t y = (sqrt(4.0 * 4.0 + 2.0 * 2.0 + 1.0 * 1.0 + 2.0 * 2.0) / 5.0) * (fabs(1.559 - 0.656 * x - 1));
            Float_t e = cent0_systematic_l->GetBinContent(i) * TMath::Sqrt(TMath::Power(y, 2.0) + TMath::Power(10e-2, 2.0) + TMath::Power(1.8e-2, 2.0) + TMath::Power(0.8e-2, 2.0) + TMath::Power(1.6e-2, 2.0) + TMath::Power(0.7e-2, 2.0) + TMath::Power(7.9e-2, 2.0) + TMath::Power(6.0e-2, 2.0));
//            fprintf(stderr, "%d %.2f %.2f %.3f %.3f\n", 0, x - 0.5 * cent0_systematic_l->GetXaxis()->GetBinWidth(i), x + 0.5 * cent0_systematic_l->GetXaxis()->GetBinWidth(i), TMath::Sqrt(TMath::Power(y, 2.0)), fabs(e / cent0_systematic_l->GetBinContent(i)));
            Float_t sign = x < 0.8521341463 ? -1 : 1;
            cent0_systematic_l->SetBinContent(i, cent0_systematic_l->GetBinContent(i) - sign * 0.5 * e);
            cent0_systematic_l->SetBinError(i, 0.5 * e);
            cent0_systematic_r->SetBinContent(i, cent0_systematic_r->GetBinContent(i) + sign * 0.5 * e);
            cent0_systematic_r->SetBinError(i, 0.5 * e);
         }
      }

      for (Int_t i = 1; i < cent0_systematic_l->GetNbinsX() + 1; i++) {
        TBox *box = new TBox(cent0_systematic_l->GetXaxis()->GetBinLowEdge(i), cent0_systematic_l->GetBinContent(i) - cent0_systematic_l->GetBinError(i), cent0_systematic_l->GetXaxis()->GetBinLowEdge(i + 1), cent0_systematic_l->GetBinContent(i) + cent0_systematic_l->GetBinError(i));
        box->SetLineColor(kRed);
        box->SetFillStyle(0);
        box->Draw("l");
      }
      for (Int_t i = 1; i < cent0_systematic_r->GetNbinsX() + 1; i++) {
        TBox *box = new TBox(cent0_systematic_r->GetXaxis()->GetBinLowEdge(i), cent0_systematic_r->GetBinContent(i) - cent0_systematic_r->GetBinError(i), cent0_systematic_r->GetXaxis()->GetBinLowEdge(i + 1), cent0_systematic_r->GetBinContent(i) + cent0_systematic_r->GetBinError(i));
        box->SetLineColor(kRed);
        box->SetFillColor(kRed);
        box->SetFillStyle(3004);
        box->Draw("lf");
      }

      /*
      cent0_systematic_l->SetFillStyle(3006);
      cent0_systematic_r->SetFillStyle(3007);
            
      cent0_systematic_l->SetLineColor(kRed - 3);
      cent0_systematic_l->SetFillColor(kRed - 3);
      cent0_systematic_l->SetLineWidth(1);
      cent0_systematic_l->SetMarkerStyle(0);
      cent0_systematic_l->Draw("e3same");
      cent0_systematic_r->SetLineColor(kBlue - 3);
      cent0_systematic_r->SetFillColor(kBlue - 3);
      cent0_systematic_r->SetLineWidth(1);
      cent0_systematic_r->SetMarkerStyle(0);
      cent0_systematic_r->Draw("e3same");
      */
   }
   if (cBin==1) {
      TH1D *cent1_systematic_l = new TH1D("cent1_systematic_l","",16,0,2);
      TH1D *cent1_systematic_r = new TH1D("cent1_systematic_r","",16,0,2);
      for (Int_t i = 1; i <= 16; i++) {
         cent1_systematic_l->SetBinContent(i, h->GetBinContent(i));
         cent1_systematic_r->SetBinContent(i, h->GetBinContent(i));
      }
      for (Int_t i = 1; i <= 16; i++) {
         if (cent1_systematic_l->GetBinContent(i) != 0) {
            Float_t x = cent1_systematic_l->GetXaxis()->GetBinCenter(i);
            Float_t y = (sqrt(4.0 * 4.0 + 2.0 * 2.0 + 1.0 * 1.0 + 2.0 * 2.0) / 5.0) * (fabs(1.525 - 0.624 * x - 1));
            Float_t e = cent1_systematic_l->GetBinContent(i) * TMath::Sqrt(TMath::Power(y, 2.0) + TMath::Power(10e-2, 2.0) + TMath::Power(1.7e-2, 2.0) + TMath::Power(0.5e-2, 2.0) + TMath::Power(1.6e-2, 2.0) + TMath::Power(0.7e-2, 2.0) + TMath::Power(7.8e-2, 2.0) + TMath::Power(6.0e-2, 2.0));
//            fprintf(stderr, "%d %.2f %.2f %.3f %.3f\n", 1, x - 0.5 * cent1_systematic_l->GetXaxis()->GetBinWidth(i), x + 0.5 * cent1_systematic_l->GetXaxis()->GetBinWidth(i), TMath::Sqrt(TMath::Power(y, 2.0)), fabs(e / cent1_systematic_l->GetBinContent(i)));
            Float_t sign = x < 0.8413461538 ? -1 : 1;
            cent1_systematic_l->SetBinContent(i, cent1_systematic_l->GetBinContent(i) - sign * 0.5 * e);
            cent1_systematic_l->SetBinError(i, 0.5 * e);
            cent1_systematic_r->SetBinContent(i, cent1_systematic_r->GetBinContent(i) + sign * 0.5 * e);
            cent1_systematic_r->SetBinError(i, 0.5 * e);
         }
      }

      for (Int_t i = 1; i < cent1_systematic_l->GetNbinsX() + 1; i++) {
        TBox *box = new TBox(cent1_systematic_l->GetXaxis()->GetBinLowEdge(i), cent1_systematic_l->GetBinContent(i) - cent1_systematic_l->GetBinError(i), cent1_systematic_l->GetXaxis()->GetBinLowEdge(i + 1), cent1_systematic_l->GetBinContent(i) + cent1_systematic_l->GetBinError(i));
        box->SetLineColor(kRed);
        box->SetFillStyle(0);
        box->Draw("l");
      }
      for (Int_t i = 1; i < cent1_systematic_r->GetNbinsX() + 1; i++) {
        TBox *box = new TBox(cent1_systematic_r->GetXaxis()->GetBinLowEdge(i), cent1_systematic_r->GetBinContent(i) - cent1_systematic_r->GetBinError(i), cent1_systematic_r->GetXaxis()->GetBinLowEdge(i + 1), cent1_systematic_r->GetBinContent(i) + cent1_systematic_r->GetBinError(i));
        box->SetLineColor(kRed);
        box->SetFillColor(kRed);
        box->SetFillStyle(3004);
        box->Draw("lf");
      }
      /*
      cent1_systematic_l->SetLineColor(kRed - 10);
      cent1_systematic_l->SetFillColor(kRed - 10);
      cent1_systematic_l->SetLineWidth(10);
      cent1_systematic_l->SetMarkerStyle(0);
      cent1_systematic_l->Draw("e1same");
      cent1_systematic_r->SetLineColor(kBlue - 10);
      cent1_systematic_r->SetFillColor(kBlue - 10);
      cent1_systematic_r->SetLineWidth(10);
      cent1_systematic_r->SetMarkerStyle(0);
      cent1_systematic_r->Draw("e1same");
      */
   }
   if (cBin==2) {
      TH1D *cent2_systematic_l = new TH1D("cent2_systematic_l","",16,0,2);
      TH1D *cent2_systematic_r = new TH1D("cent2_systematic_r","",16,0,2);
      for (Int_t i = 1; i <= 16; i++) {
         cent2_systematic_l->SetBinContent(i, h->GetBinContent(i));
         cent2_systematic_r->SetBinContent(i, h->GetBinContent(i));
      }
      for (Int_t i = 1; i <= 16; i++) {
         if (cent2_systematic_l->GetBinContent(i) != 0) {
            Float_t x = cent2_systematic_l->GetXaxis()->GetBinCenter(i);
            Float_t y = (sqrt(3.0 * 3.0 + 2.0 * 2.0 + 1.0 * 1.0 + 2.0 * 2.0) / 5.0) * (fabs(1.500 - 0.730 * x - 1));
            Float_t e = cent2_systematic_l->GetBinContent(i) * TMath::Sqrt(TMath::Power(y, 2.0) + TMath::Power(10e-2, 2.0) + TMath::Power(1.6e-2, 2.0) + TMath::Power(0.1e-2, 2.0) + TMath::Power(1.6e-2, 2.0) + TMath::Power(0.7e-2, 2.0) + TMath::Power(3.6e-2, 2.0) + TMath::Power(6.0e-2, 2.0));
//            fprintf(stderr, "%d %.2f %.2f %.3f %.3f\n", 2, x - 0.5 * cent2_systematic_l->GetXaxis()->GetBinWidth(i), x + 0.5 * cent2_systematic_l->GetXaxis()->GetBinWidth(i), TMath::Sqrt(TMath::Power(y, 2.0)), fabs(e / cent2_systematic_l->GetBinContent(i)));
            Float_t sign = x < 0.6849315068 ? -1 : 1;
            cent2_systematic_l->SetBinContent(i, cent2_systematic_l->GetBinContent(i) - sign * 0.5 * e);
            cent2_systematic_l->SetBinError(i, 0.5 * e);
            cent2_systematic_r->SetBinContent(i, cent2_systematic_r->GetBinContent(i) + sign * 0.5 * e);
            cent2_systematic_r->SetBinError(i, 0.5 * e);
         }
      }
      
      for (Int_t i = 1; i < cent2_systematic_l->GetNbinsX() + 1; i++) {
        TBox *box = new TBox(cent2_systematic_l->GetXaxis()->GetBinLowEdge(i), cent2_systematic_l->GetBinContent(i) - cent2_systematic_l->GetBinError(i), cent2_systematic_l->GetXaxis()->GetBinLowEdge(i + 1), cent2_systematic_l->GetBinContent(i) + cent2_systematic_l->GetBinError(i));
        box->SetLineColor(kRed);
        box->SetFillStyle(0);
        box->Draw("l");
      }
      for (Int_t i = 1; i < cent2_systematic_r->GetNbinsX() + 1; i++) {
        TBox *box = new TBox(cent2_systematic_r->GetXaxis()->GetBinLowEdge(i), cent2_systematic_r->GetBinContent(i) - cent2_systematic_r->GetBinError(i), cent2_systematic_r->GetXaxis()->GetBinLowEdge(i + 1), cent2_systematic_r->GetBinContent(i) + cent2_systematic_r->GetBinError(i));
        box->SetLineColor(kRed);
        box->SetFillColor(kRed);
        box->SetFillStyle(3004);
        box->Draw("lf");
      }

      /*
      cent2_systematic_l->SetLineColor(kRed - 10);
      cent2_systematic_l->SetFillColor(kRed - 10);
      cent2_systematic_l->SetLineWidth(10);
      cent2_systematic_l->SetMarkerStyle(0);
      cent2_systematic_l->Draw("e1same");
      cent2_systematic_r->SetLineColor(kBlue - 10);
      cent2_systematic_r->SetFillColor(kBlue - 10);
      cent2_systematic_r->SetLineWidth(10);
      cent2_systematic_r->SetMarkerStyle(0);
      cent2_systematic_r->Draw("e1same");
      */
   }
   
   if (cBin==3) {
      TH1D *cent3_systematic_l = new TH1D("cent3_systematic_l","",10,0,2);
      TH1D *cent3_systematic_r = new TH1D("cent3_systematic_r","",10,0,2);
      for (Int_t i = 1; i <= 10; i++) {
         cent3_systematic_l->SetBinContent(i, h->GetBinContent(i));
         cent3_systematic_r->SetBinContent(i, h->GetBinContent(i));
      }
      for (Int_t i = 1; i <= 10; i++) {
         if (cent3_systematic_l->GetBinContent(i) != 0) {
            Float_t x = cent3_systematic_l->GetXaxis()->GetBinCenter(i);
            Float_t y = (sqrt(3.0 * 3.0 + 2.0 * 2.0 + 1.0 * 1.0 + 2.0 * 2.0) / 5.0) * (fabs(1.242 - 0.474 * x - 1));
            Float_t e = cent3_systematic_l->GetBinContent(i) * TMath::Sqrt(TMath::Power(y, 2.0) + TMath::Power(10e-2, 2.0) + TMath::Power(1.6e-2, 2.0) + TMath::Power(0.1e-2, 2.0) + TMath::Power(3.7e-2, 2.0) + TMath::Power(0.7e-2, 2.0) + TMath::Power(2.3e-2, 2.0) + TMath::Power(6.0e-2, 2.0));
//            fprintf(stderr, "%d %.2f %.2f %.3f %.3f\n", 3, x - 0.5 * cent3_systematic_l->GetXaxis()->GetBinWidth(i), x + 0.5 * cent3_systematic_l->GetXaxis()->GetBinWidth(i), TMath::Sqrt(TMath::Power(y, 2.0)), fabs(e / cent3_systematic_l->GetBinContent(i)));
            Float_t sign = x < 0.5105485232 ? -1 : 1;
            cent3_systematic_l->SetBinContent(i, cent3_systematic_l->GetBinContent(i) - sign * 0.5 * e);
            cent3_systematic_l->SetBinError(i, 0.5 * e);
            cent3_systematic_r->SetBinContent(i, cent3_systematic_r->GetBinContent(i) + sign * 0.5 * e);
            cent3_systematic_r->SetBinError(i, 0.5 * e);
         }
      }

      
      for (Int_t i = 1; i < cent3_systematic_l->GetNbinsX() + 1; i++) {
	TBox *box = new TBox(cent3_systematic_l->GetXaxis()->GetBinLowEdge(i), cent3_systematic_l->GetBinContent(i) - cent3_systematic_l->GetBinError(i), cent3_systematic_l->GetXaxis()->GetBinLowEdge(i + 1), cent3_systematic_l->GetBinContent(i) + cent3_systematic_l->GetBinError(i));
	box->SetLineColor(kRed);
	box->SetFillStyle(0);
	box->Draw("l");
      }
      for (Int_t i = 1; i < cent3_systematic_r->GetNbinsX() + 1; i++) {
	TBox *box = new TBox(cent3_systematic_r->GetXaxis()->GetBinLowEdge(i), cent3_systematic_r->GetBinContent(i) - cent3_systematic_r->GetBinError(i), cent3_systematic_r->GetXaxis()->GetBinLowEdge(i + 1), cent3_systematic_r->GetBinContent(i) + cent3_systematic_r->GetBinError(i));
	box->SetLineColor(kRed);
	box->SetFillColor(kRed);
	box->SetFillStyle(3004);
	box->Draw("lf");
      }
      /*
	cent3_systematic_l->SetLineColor(kRed - 10);
	cent3_systematic_l->SetFillColor(kRed - 10);
	cent3_systematic_l->SetLineWidth(10);
      cent3_systematic_l->SetMarkerStyle(0);
      cent3_systematic_l->Draw("e1same");
      cent3_systematic_r->SetLineColor(kBlue - 10);
      cent3_systematic_r->SetFillColor(kBlue - 10);
      cent3_systematic_r->SetLineWidth(10);
      cent3_systematic_r->SetMarkerStyle(0);
      cent3_systematic_r->Draw("e1same");
*/
   }
}

#endif

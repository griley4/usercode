{
//=========Macro generated from canvas: disp/disp
//=========  (Mon Apr 10 11:09:54 2017) by ROOT version5.26/00
   TCanvas *disp = new TCanvas("disp", "disp",5,47,900,867);
   gStyle->SetOptStat(0);
   disp->Range(0,0,1,1);
   disp->SetFillColor(0);
   disp->SetBorderMode(0);
   disp->SetBorderSize(2);
   disp->SetFrameFillStyle(0);
   disp->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: disp_1
   TPad *disp_1 = new TPad("disp_1", "disp_1",0.01,0.51,0.49,0.99);
   disp_1->Draw();
   disp_1->cd();
   disp_1->Range(-12,-4.105592,68,-0.6464537);
   disp_1->SetFillColor(0);
   disp_1->SetBorderMode(0);
   disp_1->SetBorderSize(2);
   disp_1->SetLogy();
   disp_1->SetLeftMargin(0.15);
   disp_1->SetFrameFillStyle(0);
   disp_1->SetFrameBorderMode(0);
   disp_1->SetFrameFillStyle(0);
   disp_1->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {0, 6.2, 7, 9, 11, 14, 18, 25, 30, 60}; 
   
   TH1F *xsec_mass = new TH1F("xsec_mass","xsec_mass",9, xAxis1);
   xsec_mass->SetBinContent(2,0.04743199);
   xsec_mass->SetBinContent(3,0.02288957);
   xsec_mass->SetBinContent(4,0.01052911);
   xsec_mass->SetBinContent(5,0.00729788);
   xsec_mass->SetBinContent(6,0.004679995);
   xsec_mass->SetBinContent(7,0.002752399);
   xsec_mass->SetBinContent(8,0.002321633);
   xsec_mass->SetBinContent(9,0.0004013286);
   xsec_mass->SetBinError(2,0.006281533);
   xsec_mass->SetBinError(3,0.002358319);
   xsec_mass->SetBinError(4,0.001509835);
   xsec_mass->SetBinError(5,0.001177612);
   xsec_mass->SetBinError(6,0.0007126356);
   xsec_mass->SetBinError(7,0.0003761611);
   xsec_mass->SetBinError(8,0.0003408355);
   xsec_mass->SetBinError(9,5.351047e-05);
   xsec_mass->SetEntries(8);
   xsec_mass->SetStats(0);
   xsec_mass->GetXaxis()->SetTitle("M_{J/#psi J/#psi} (GeV/c^{2})");
   xsec_mass->GetYaxis()->SetTitle("d#sigma/dM_{J/#psi J/#psi} (nb/(GeV/c^{2}))");
   xsec_mass->GetYaxis()->SetTitleOffset(1.6);
   xsec_mass->Draw("e1");
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.2764658,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("xsec_mass");
   pt->Draw();
   disp_1->Modified();
   disp->cd();
  
// ------------>Primitives in pad: disp_2
   disp_2 = new TPad("disp_2", "disp_2",0.51,0.51,0.99,0.99);
   disp_2->Draw();
   disp_2->cd();
   disp_2->Range(-16,-0.001505524,90.66667,0.01354972);
   disp_2->SetFillColor(0);
   disp_2->SetBorderMode(0);
   disp_2->SetBorderSize(2);
   disp_2->SetLeftMargin(0.15);
   disp_2->SetFrameFillStyle(0);
   disp_2->SetFrameBorderMode(0);
   disp_2->SetFrameFillStyle(0);
   disp_2->SetFrameBorderMode(0);
   Double_t xAxis2[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1F *xsec_pt = new TH1F("xsec_pt","xsec_pt",6, xAxis2);
   xsec_pt->SetBinContent(1,0.005511632);
   xsec_pt->SetBinContent(2,0.005816723);
   xsec_pt->SetBinContent(3,0.009881093);
   xsec_pt->SetBinContent(4,0.009516934);
   xsec_pt->SetBinContent(5,0.0057525);
   xsec_pt->SetBinContent(6,0.0003398774);
   xsec_pt->SetBinError(1,0.0006928908);
   xsec_pt->SetBinError(2,0.0009048236);
   xsec_pt->SetBinError(3,0.001589567);
   xsec_pt->SetBinError(4,0.001189617);
   xsec_pt->SetBinError(5,0.000607507);
   xsec_pt->SetBinError(6,2.986066e-05);
   xsec_pt->SetMinimum(0);
   xsec_pt->SetEntries(6);
   xsec_pt->SetStats(0);
   xsec_pt->GetXaxis()->SetTitle("p_{T}^{J/#psi J/#psi} (GeV/c)");
   xsec_pt->GetYaxis()->SetTitle("d#sigma/dp_{T}^{J/#psi J/#psi} (nb/(GeV/c))");
   xsec_pt->GetYaxis()->SetTitleOffset(1.7);
   xsec_pt->Draw("e1");
   
   pt = new TPaveText(0.01,0.9405275,0.2043862,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("xsec_pt");
   pt->Draw();
   disp_2->Modified();
   disp->cd();
  
// ------------>Primitives in pad: disp_3
   disp_3 = new TPad("disp_3", "disp_3",0.01,0.01,0.49,0.49);
   disp_3->Draw();
   disp_3->cd();
   disp_3->Range(-0.9,-0.05017638,5.1,0.4515874);
   disp_3->SetFillColor(0);
   disp_3->SetBorderMode(0);
   disp_3->SetBorderSize(2);
   disp_3->SetLeftMargin(0.15);
   disp_3->SetFrameFillStyle(0);
   disp_3->SetFrameBorderMode(0);
   disp_3->SetFrameFillStyle(0);
   disp_3->SetFrameBorderMode(0);
   Double_t xAxis3[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1F *xsec_dy = new TH1F("xsec_dy","xsec_dy",8, xAxis3);
   xsec_dy->SetBinContent(1,0.3536836);
   xsec_dy->SetBinContent(2,0.2089763);
   xsec_dy->SetBinContent(3,0.100067);
   xsec_dy->SetBinContent(4,0.05972152);
   xsec_dy->SetBinContent(5,0.03928412);
   xsec_dy->SetBinContent(6,0.02376292);
   xsec_dy->SetBinContent(7,0.02276975);
   xsec_dy->SetBinContent(8,0.01052381);
   xsec_dy->SetBinError(1,0.02861261);
   xsec_dy->SetBinError(2,0.02171715);
   xsec_dy->SetBinError(3,0.01411659);
   xsec_dy->SetBinError(4,0.01030196);
   xsec_dy->SetBinError(5,0.00684666);
   xsec_dy->SetBinError(6,0.005372485);
   xsec_dy->SetBinError(7,0.00464503);
   xsec_dy->SetBinError(8,0.002287784);
   xsec_dy->SetMinimum(0);
   xsec_dy->SetEntries(8);
   xsec_dy->SetStats(0);
   xsec_dy->GetXaxis()->SetTitle("|#Delta y| between J/#psi");
   xsec_dy->GetYaxis()->SetTitle("d#sigma/d|#Delta y| (nb)");
   xsec_dy->GetYaxis()->SetTitleOffset(1.6);
   xsec_dy->Draw("e1");
   
   pt = new TPaveText(0.01,0.9376606,0.2136868,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("xsec_dy");
   pt->Draw();
   disp_3->Modified();
   disp->cd();
  
// ------------>Primitives in pad: disp_4
   disp_4 = new TPad("disp_4", "disp_4",0.51,0.01,0.99,0.49);
   disp_4->Draw();
   disp_4->cd();
   disp_4->Range(-0.36,-0.02512627,2.04,0.2261364);
   disp_4->SetFillColor(0);
   disp_4->SetBorderMode(0);
   disp_4->SetBorderSize(2);
   disp_4->SetLeftMargin(0.15);
   disp_4->SetFrameFillStyle(0);
   disp_4->SetFrameBorderMode(0);
   disp_4->SetFrameFillStyle(0);
   disp_4->SetFrameBorderMode(0);
   Double_t xAxis4[10] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8}; 
   
   TH1F *xsec_y = new TH1F("xsec_y","xsec_y",9, xAxis4);
   xsec_y->SetBinContent(1,0.09687107);
   xsec_y->SetBinContent(2,0.1105371);
   xsec_y->SetBinContent(3,0.08927423);
   xsec_y->SetBinContent(4,0.1018527);
   xsec_y->SetBinContent(5,0.07761347);
   xsec_y->SetBinContent(6,0.0957653);
   xsec_y->SetBinContent(7,0.1376607);
   xsec_y->SetBinContent(8,0.1684277);
   xsec_y->SetBinContent(9,0.1205354);
   xsec_y->SetBinError(1,0.01497098);
   xsec_y->SetBinError(2,0.01567618);
   xsec_y->SetBinError(3,0.0123992);
   xsec_y->SetBinError(4,0.0136379);
   xsec_y->SetBinError(5,0.01098304);
   xsec_y->SetBinError(6,0.01426708);
   xsec_y->SetBinError(7,0.01744995);
   xsec_y->SetBinError(8,0.02301054);
   xsec_y->SetBinError(9,0.0227678);
   xsec_y->SetMinimum(0);
   xsec_y->SetEntries(9);
   xsec_y->SetStats(0);
   xsec_y->GetXaxis()->SetTitle("|Rapidity|_{J/#psi J/#psi}");
   xsec_y->GetYaxis()->SetTitle("d#sigma/d|y| (nb)");
   xsec_y->GetYaxis()->SetTitleOffset(1.6);
   xsec_y->Draw("e1");
   
   pt = new TPaveText(0.01,0.945,0.185785,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("xsec_y");
   pt->Draw();
   disp_4->Modified();
   disp->cd();
   disp->Modified();
   disp->cd();
   disp->SetSelected(disp);
}

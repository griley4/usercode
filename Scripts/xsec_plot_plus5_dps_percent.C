{
//=========Macro generated from canvas: disp/disp
//=========  (Mon Apr 10 08:39:23 2017) by ROOT version5.26/00
   TCanvas *disp = new TCanvas("disp", "disp",105,47,900,867);
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
   disp_1->Range(-12,-0.009030503,68,0.05681312);
   disp_1->SetFillColor(0);
   disp_1->SetBorderMode(0);
   disp_1->SetBorderSize(2);
   disp_1->SetLeftMargin(0.15);
   disp_1->SetFrameFillStyle(0);
   disp_1->SetFrameBorderMode(0);
   disp_1->SetFrameFillStyle(0);
   disp_1->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {0, 6.2, 7, 9, 11, 14, 18, 25, 30, 60}; 
   
   TH1F *xsec_mass = new TH1F("xsec_mass","xsec_mass",9, xAxis1);
   xsec_mass->SetBinContent(2,0.04772042);
   xsec_mass->SetBinContent(3,0.02303926);
   xsec_mass->SetBinContent(4,0.01063514);
   xsec_mass->SetBinContent(5,0.007453869);
   xsec_mass->SetBinContent(6,0.004836356);
   xsec_mass->SetBinContent(7,0.002857256);
   xsec_mass->SetBinContent(8,0.002504349);
   xsec_mass->SetBinContent(9,0.0003378739);
   xsec_mass->SetBinError(3,0.00491665);
   xsec_mass->SetBinError(4,0.003303743);
   xsec_mass->SetBinError(5,0.001716125);
   xsec_mass->SetBinError(6,0.001135021);
   xsec_mass->SetBinError(7,0.0006609687);
   xsec_mass->SetBinError(8,0.0004194695);
   xsec_mass->SetBinError(9,0.0003951307);
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
   disp_2->Range(-16,-0.001533419,90.66667,0.01380077);
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
   xsec_pt->SetBinContent(1,0.005706818);
   xsec_pt->SetBinContent(2,0.00608742);
   xsec_pt->SetBinContent(3,0.01006418);
   xsec_pt->SetBinContent(4,0.009523273);
   xsec_pt->SetBinContent(5,0.005761037);
   xsec_pt->SetBinContent(6,0.0003406502);
   xsec_pt->SetBinError(1,0.0007174285);
   xsec_pt->SetBinError(2,0.0009469319);
   xsec_pt->SetBinError(3,0.00161902);
   xsec_pt->SetBinError(4,0.001190409);
   xsec_pt->SetBinError(5,0.0006084086);
   xsec_pt->SetBinError(6,2.992855e-05);
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
   disp_3->Range(-0.9,-0.0507289,5.1,0.4565601);
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
   xsec_dy->SetBinContent(1,0.3575782);
   xsec_dy->SetBinContent(2,0.2118519);
   xsec_dy->SetBinContent(3,0.1014876);
   xsec_dy->SetBinContent(4,0.06084597);
   xsec_dy->SetBinContent(5,0.04031759);
   xsec_dy->SetBinContent(6,0.02449213);
   xsec_dy->SetBinContent(7,0.02255733);
   xsec_dy->SetBinContent(8,0.01138156);
   xsec_dy->SetBinError(1,0.02892768);
   xsec_dy->SetBinError(2,0.02201598);
   xsec_dy->SetBinError(3,0.014317);
   xsec_dy->SetBinError(4,0.01049593);
   xsec_dy->SetBinError(5,0.00702678);
   xsec_dy->SetBinError(6,0.005537352);
   xsec_dy->SetBinError(7,0.004601696);
   xsec_dy->SetBinError(8,0.002474252);
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
   disp_4->Range(-0.36,-0.02561198,2.04,0.2305078);
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
   xsec_y->SetBinContent(1,0.1041358);
   xsec_y->SetBinContent(2,0.116048);
   xsec_y->SetBinContent(3,0.09236936);
   xsec_y->SetBinContent(4,0.1046199);
   xsec_y->SetBinContent(5,0.07948587);
   xsec_y->SetBinContent(6,0.09706181);
   xsec_y->SetBinContent(7,0.1398772);
   xsec_y->SetBinContent(8,0.1716835);
   xsec_y->SetBinContent(9,0.1228601);
   xsec_y->SetBinError(1,0.01609371);
   xsec_y->SetBinError(2,0.01645771);
   xsec_y->SetBinError(3,0.01282908);
   xsec_y->SetBinError(4,0.01400843);
   xsec_y->SetBinError(5,0.011248);
   xsec_y->SetBinError(6,0.01446023);
   xsec_y->SetBinError(7,0.01773091);
   xsec_y->SetBinError(8,0.02345535);
   xsec_y->SetBinError(9,0.02320691);
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

{
//=========Macro generated from canvas: acc/acc
//=========  (Thu Jun  8 08:15:50 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",55,47,900,867);
   gStyle->SetOptStat(0);
   acc->Range(0,0,1,1);
   acc->SetFillColor(0);
   acc->SetBorderMode(0);
   acc->SetBorderSize(2);
   acc->SetFrameFillStyle(0);
   acc->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: acc_1
   TPad *acc_1 = new TPad("acc_1", "acc_1",0.01,0.76,0.49,0.99);
   acc_1->Draw();
   acc_1->cd();
   acc_1->Range(-0.39275,0.01061862,3.53475,0.05153931);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[6] = {0, 0.25, 1, 1.75, 2.5, 3.142}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",5, xAxis1);
   acc_eff_shape_dps->SetBinContent(1,  0.0219156);
   acc_eff_shape_dps->SetBinContent(2,  0.02411801);
   acc_eff_shape_dps->SetBinContent(3,  0.02384129);
   acc_eff_shape_dps->SetBinContent(4,  0.02880021);
   acc_eff_shape_dps->SetBinContent(5,  0.04108031);
   acc_eff_shape_dps->SetBinError(1,0.005720252);
   acc_eff_shape_dps->SetBinError(2,0.003451688);
   acc_eff_shape_dps->SetBinError(3,0.00344626);
   acc_eff_shape_dps->SetBinError(4,0.003771252);
   acc_eff_shape_dps->SetBinError(5,0.004808051);
   acc_eff_shape_dps->SetEntries(212.3242);
   acc_eff_shape_dps->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps->SetLineColor(ci);
   acc_eff_shape_dps->SetLineWidth(2);
   acc_eff_shape_dps->GetXaxis()->SetTitle("Four Mu #Delta#phi");
   acc_eff_shape_dps->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps->Draw("E1");
   
   TPaveText *pt = new TPaveText(0.01,0.9411508,0.2229874,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("");
   pt->Draw();
   acc_1->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_2
   acc_2 = new TPad("acc_2", "acc_2",0.51,0.76,0.99,0.99);
   acc_2->Draw();
   acc_2->cd();
   acc_2->Range(-0.39275,0.1569498,3.53475,0.3061645);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[6] = {0, 0.25, 1, 1.75, 2.5, 3.142}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",5, xAxis2);
   acc_shape->SetBinContent(1,0.1957793);
   acc_shape->SetBinContent(2,0.2387683);
   acc_shape->SetBinContent(3,0.2150582);
   acc_shape->SetBinContent(4,0.2529619);
   acc_shape->SetBinContent(5,0.2718868);
   acc_shape->SetBinError(1,0.01849439);
   acc_shape->SetBinError(2,0.01194453);
   acc_shape->SetBinError(3,0.0112757);
   acc_shape->SetBinError(4,0.01233442);
   acc_shape->SetBinError(5,0.01367188);
   acc_shape->SetEntries(1676.319);
   acc_shape->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape->SetLineColor(ci);
   acc_shape->SetLineWidth(2);
   acc_shape->GetXaxis()->SetTitle("Four Mu #Delta#phi");
   acc_shape->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1369568,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape");
   pt->Draw();
   acc_2->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_3
   acc_3 = new TPad("acc_3", "acc_3",0.01,0.51,0.49,0.74);
   acc_3->Draw();
   acc_3->cd();
   acc_3->Range(-7.500001,nan,67.5,nan);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[9] = {0, 5, 10, 12, 14, 17, 20, 25, 60}; 
   
   TH1D *acc_eff_shape_dps_pt1 = new TH1D("acc_eff_shape_dps_pt1","acc_eff_shape_dps_pt1",8, xAxis3);
   acc_eff_shape_dps_pt1->SetBinContent(2,0.007694378);
   acc_eff_shape_dps_pt1->SetBinContent(3,0.02667605);
   acc_eff_shape_dps_pt1->SetBinContent(4,0.04253364);
   acc_eff_shape_dps_pt1->SetBinContent(5,0.04979969);
   acc_eff_shape_dps_pt1->SetBinContent(6,0.0484733);
   acc_eff_shape_dps_pt1->SetBinContent(7,0.01238063);
   acc_eff_shape_dps_pt1->SetBinError(2,0.0008052746);
   acc_eff_shape_dps_pt1->SetBinError(3,0.003142117);
   acc_eff_shape_dps_pt1->SetBinError(4,0.006403224);
   acc_eff_shape_dps_pt1->SetBinError(5,0.009642748);
   acc_eff_shape_dps_pt1->SetBinError(6,0.01654474);
   acc_eff_shape_dps_pt1->SetBinError(7,0.01245703);
   acc_eff_shape_dps_pt1->SetEntries(62.43033);
   acc_eff_shape_dps_pt1->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt1->SetLineColor(ci);
   acc_eff_shape_dps_pt1->SetLineWidth(2);
   acc_eff_shape_dps_pt1->GetXaxis()->SetTitle("Dimuon_{1} pT(GeV)");
   acc_eff_shape_dps_pt1->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt1->Draw("E1");
   
   pt = new TPaveText(0.01,0.995,0.26484,nan,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_pt1");
   pt->Draw();
   acc_3->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_4
   acc_4 = new TPad("acc_4", "acc_4",0.51,0.51,0.99,0.74);
   acc_4->Draw();
   acc_4->cd();
   acc_4->Range(-7.500001,-9.249285e-07,67.5,0.3405607);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[9] = {0, 5, 10, 12, 14, 17, 20, 25, 60}; 
   
   TH1D *acc_shape_pt1 = new TH1D("acc_shape_pt1","acc_shape_pt1",8, xAxis4);
   acc_shape_pt1->SetBinContent(2,0.04847289);
   acc_shape_pt1->SetBinContent(3,0.09624066);
   acc_shape_pt1->SetBinContent(4,0.1222155);
   acc_shape_pt1->SetBinContent(5,0.1296685);
   acc_shape_pt1->SetBinContent(6,0.1440726);
   acc_shape_pt1->SetBinContent(7,0.233774);
   acc_shape_pt1->SetBinContent(8,0.1384661);
   acc_shape_pt1->SetBinError(2,0.002061678);
   acc_shape_pt1->SetBinError(3,0.006167045);
   acc_shape_pt1->SetBinError(4,0.0112613);
   acc_shape_pt1->SetBinError(5,0.01614087);
   acc_shape_pt1->SetBinError(6,0.02979528);
   acc_shape_pt1->SetBinError(7,0.05975678);
   acc_shape_pt1->SetBinError(8,0.06799967);
   acc_shape_pt1->SetEntries(167.0419);
   acc_shape_pt1->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt1->SetLineColor(ci);
   acc_shape_pt1->SetLineWidth(2);
   acc_shape_pt1->GetXaxis()->SetTitle("Dimuon_{1} pT (GeV)");
   acc_shape_pt1->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt1->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1788095,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_pt1");
   pt->Draw();
   acc_4->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_5
   acc_5 = new TPad("acc_5", "acc_5",0.01,0.26,0.49,0.49);
   acc_5->Draw();
   acc_5->cd();
   acc_5->Range(-5,nan,45,nan);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[8] = {0, 5, 8, 10, 12, 15, 20, 40}; 
   
   TH1D *acc_eff_shape_dps_pt2 = new TH1D("acc_eff_shape_dps_pt2","acc_eff_shape_dps_pt2",7, xAxis5);
   acc_eff_shape_dps_pt2->SetBinContent(2,0.009222299);
   acc_eff_shape_dps_pt2->SetBinContent(3,0.03151152);
   acc_eff_shape_dps_pt2->SetBinContent(4,0.08343379);
   acc_eff_shape_dps_pt2->SetBinContent(5,0.1224433);
   acc_eff_shape_dps_pt2->SetBinError(2,0.002184653);
   acc_eff_shape_dps_pt2->SetBinError(3,0.002510876);
   acc_eff_shape_dps_pt2->SetBinError(4,0.005769192);
   acc_eff_shape_dps_pt2->SetBinError(5,0.01645004);
   acc_eff_shape_dps_pt2->SetEntries(23.75696);
   acc_eff_shape_dps_pt2->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt2->SetLineColor(ci);
   acc_eff_shape_dps_pt2->SetLineWidth(2);
   acc_eff_shape_dps_pt2->GetXaxis()->SetTitle("Dimuon_{2} pT(GeV)");
   acc_eff_shape_dps_pt2->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt2->Draw("E1");
   
   pt = new TPaveText(0.01,0.995,0.2671652,nan,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_pt2");
   pt->Draw();
   acc_5->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_6
   acc_6 = new TPad("acc_6", "acc_6",0.51,0.26,0.99,0.49);
   acc_6->Draw();
   acc_6->cd();
   acc_6->Range(-5,nan,45,nan);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[8] = {0, 5, 8, 10, 12, 15, 20, 40}; 
   
   TH1D *acc_shape_pt2 = new TH1D("acc_shape_pt2","acc_shape_pt2",7, xAxis6);
   acc_shape_pt2->SetBinContent(2,0.05265816);
   acc_shape_pt2->SetBinContent(3,0.1057437);
   acc_shape_pt2->SetBinContent(4,0.2139455);
   acc_shape_pt2->SetBinContent(5,0.2844131);
   acc_shape_pt2->SetBinContent(6,0.3636484);
   acc_shape_pt2->SetBinError(2,0.002038654);
   acc_shape_pt2->SetBinError(3,0.006294303);
   acc_shape_pt2->SetBinError(4,0.02832959);
   acc_shape_pt2->SetBinError(5,0.07993658);
   acc_shape_pt2->SetBinError(6,0.2931753);
   acc_shape_pt2->SetEntries(21.30303);
   acc_shape_pt2->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt2->SetLineColor(ci);
   acc_shape_pt2->SetLineWidth(2);
   acc_shape_pt2->GetXaxis()->SetTitle("Dimuon_{2} pT (GeV)");
   acc_shape_pt2->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt2->Draw("E1");
   
   pt = new TPaveText(0.01,0.995,0.04860119,nan,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_pt2");
   pt->Draw();
   acc_6->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_7
   acc_7 = new TPad("acc_7", "acc_7",0.01,0.01,0.49,0.24);
   acc_7->Draw();
   acc_7->cd();
   acc_7->Range(-0.125,0.007205326,1.125,0.03269096);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[6] = {0, 0.05, 0.125, 0.2, 0.35, 1}; 
   
   TH1D *acc_eff_shape_dps_pta = new TH1D("acc_eff_shape_dps_pta","acc_eff_shape_dps_pta",5, xAxis7);
   acc_eff_shape_dps_pta->SetBinContent(1,0.01277959);
   acc_eff_shape_dps_pta->SetBinContent(2,0.01446442);
   acc_eff_shape_dps_pta->SetBinContent(3,0.0125155);
   acc_eff_shape_dps_pta->SetBinContent(4,0.01940185);
   acc_eff_shape_dps_pta->SetBinContent(5,0.02355463);
   acc_eff_shape_dps_pta->SetBinError(1,0.001783498);
   acc_eff_shape_dps_pta->SetBinError(2,0.001741287);
   acc_eff_shape_dps_pta->SetBinError(3,0.001836962);
   acc_eff_shape_dps_pta->SetBinError(4,0.002468002);
   acc_eff_shape_dps_pta->SetBinError(5,0.005616886);
   acc_eff_shape_dps_pta->SetEntries(146.2953);
   acc_eff_shape_dps_pta->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pta->SetLineColor(ci);
   acc_eff_shape_dps_pta->SetLineWidth(2);
   acc_eff_shape_dps_pta->GetXaxis()->SetTitle("Dimuon pT Assymetery");
   acc_eff_shape_dps_pta->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pta->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.2671652,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_pta");
   pt->Draw();
   acc_7->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_8
   acc_8 = new TPad("acc_8", "acc_8",0.51,0.01,0.99,0.24);
   acc_8->Draw();
   acc_8->cd();
   acc_8->Range(-0.125,0.04224347,1.125,0.1166407);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[6] = {0, 0.05, 0.125, 0.2, 0.35, 1}; 
   
   TH1D *acc_shape_pta = new TH1D("acc_shape_pta","acc_shape_pta",5, xAxis8);
   acc_shape_pta->SetBinContent(1,0.05620191);
   acc_shape_pta->SetBinContent(2,0.06427003);
   acc_shape_pta->SetBinContent(3,0.06354959);
   acc_shape_pta->SetBinContent(4,0.07737294);
   acc_shape_pta->SetBinContent(5,0.0947183);
   acc_shape_pta->SetBinError(1,0.003819494);
   acc_shape_pta->SetBinError(2,0.003759513);
   acc_shape_pta->SetBinError(3,0.004242388);
   acc_shape_pta->SetBinError(4,0.005066743);
   acc_shape_pta->SetBinError(5,0.0116485);
   acc_shape_pta->SetEntries(1161.971);
   acc_shape_pta->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pta->SetLineColor(ci);
   acc_shape_pta->SetLineWidth(2);
   acc_shape_pta->GetXaxis()->SetTitle("Dimuon pT Assymetery");
   acc_shape_pta->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pta->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1811347,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_pta");
   pt->Draw();
   acc_8->Modified();
   acc->cd();
   acc->Modified();
   acc->cd();
   acc->SetSelected(acc);
}

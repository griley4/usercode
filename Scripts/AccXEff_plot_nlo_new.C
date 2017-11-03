{
//=========Macro generated from canvas: acc/acc
//=========  (Thu Jun  8 08:08:12 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",105,47,900,867);
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
   acc_1->Range(-0.39275,-0.008294939,3.53475,0.1598064);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[6] = {0, 0.25, 1, 1.75, 2.5, 3.142}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",5, xAxis1);
   acc_eff_shape_dps->SetBinContent(1, 0.1291394);
   acc_eff_shape_dps->SetBinContent(2, 0.05207096);
   acc_eff_shape_dps->SetBinContent(3, 0.01889098);
   acc_eff_shape_dps->SetBinContent(4, 0.01585437);
   acc_eff_shape_dps->SetBinContent(5, 0.02483066);
   acc_eff_shape_dps->SetBinError(1,0.007453027);
   acc_eff_shape_dps->SetBinError(2,0.002300508);
   acc_eff_shape_dps->SetBinError(3,0.001394433);
   acc_eff_shape_dps->SetBinError(4,0.001240254);
   acc_eff_shape_dps->SetBinError(5,0.001828451);
   acc_eff_shape_dps->SetBinError(6,nan);
   acc_eff_shape_dps->SetEntries(867.0631);
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
   TText *text = pt->AddText("acc_eff_shape_dps");
   pt->Draw();
   acc_1->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_2
   acc_2 = new TPad("acc_2", "acc_2",0.51,0.76,0.99,0.99);
   acc_2->Draw();
   acc_2->cd();
   acc_2->Range(-0.39275,0.121038,3.53475,0.1468377);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[6] = {0, 0.25, 1, 1.75, 2.5, 3.142}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",5, xAxis2);
   acc_shape->SetBinContent(1,0.1356154);
   acc_shape->SetBinContent(2,0.1282936);
   acc_shape->SetBinContent(3,0.1341563);
   acc_shape->SetBinContent(4,0.1375319);
   acc_shape->SetBinContent(5,0.1370285);
   acc_shape->SetBinError(1,0.007659487);
   acc_shape->SetBinError(2,0.003739529);
   acc_shape->SetBinError(3,0.003920562);
   acc_shape->SetBinError(4,0.003865484);
   acc_shape->SetBinError(5,0.00452433);
   acc_shape->SetBinError(6,nan);
   acc_shape->SetEntries(3717.611);
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
   acc_3->Range(-7.500001,-0.01090407,67.5,0.1360594);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[9] = {0, 5, 10, 12, 14, 17, 20, 25, 60}; 
   
   TH1D *acc_eff_shape_dps_pt1 = new TH1D("acc_eff_shape_dps_pt1","acc_eff_shape_dps_pt1",8, xAxis3);
   acc_eff_shape_dps_pt1->SetBinContent(2,0.009837757);
   acc_eff_shape_dps_pt1->SetBinContent(3,0.02705243);
   acc_eff_shape_dps_pt1->SetBinContent(4,0.04625061);
   acc_eff_shape_dps_pt1->SetBinContent(5,0.06856784);
   acc_eff_shape_dps_pt1->SetBinContent(6,0.107855);
   acc_eff_shape_dps_pt1->SetBinContent(7,0.09681247);
   acc_eff_shape_dps_pt1->SetBinContent(8,0.08708955);
   acc_eff_shape_dps_pt1->SetBinError(1,nan);
   acc_eff_shape_dps_pt1->SetBinError(2,0.0007134627);
   acc_eff_shape_dps_pt1->SetBinError(3,0.001674693);
   acc_eff_shape_dps_pt1->SetBinError(4,0.002847612);
   acc_eff_shape_dps_pt1->SetBinError(5,0.004058556);
   acc_eff_shape_dps_pt1->SetBinError(6,0.007909483);
   acc_eff_shape_dps_pt1->SetBinError(7,0.009413876);
   acc_eff_shape_dps_pt1->SetBinError(8,0.01202711);
   acc_eff_shape_dps_pt1->SetBinError(9,nan);
   acc_eff_shape_dps_pt1->SetEntries(610.5979);
   acc_eff_shape_dps_pt1->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt1->SetLineColor(ci);
   acc_eff_shape_dps_pt1->SetLineWidth(2);
   acc_eff_shape_dps_pt1->GetXaxis()->SetTitle("Dimuon_{1} pT(GeV)");
   acc_eff_shape_dps_pt1->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt1->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.26484,0.995,"blNDC");
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
   acc_4->Range(-7.500001,0.005719079,67.5,0.4067544);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[9] = {0, 5, 10, 12, 14, 17, 20, 25, 60}; 
   
   TH1D *acc_shape_pt1 = new TH1D("acc_shape_pt1","acc_shape_pt1",8, xAxis4);
   acc_shape_pt1->SetBinContent(2,0.06221276);
   acc_shape_pt1->SetBinContent(3,0.1174435);
   acc_shape_pt1->SetBinContent(4,0.1520098);
   acc_shape_pt1->SetBinContent(5,0.1927425);
   acc_shape_pt1->SetBinContent(6,0.2394352);
   acc_shape_pt1->SetBinContent(7,0.2852731);
   acc_shape_pt1->SetBinContent(8,0.325689);
   acc_shape_pt1->SetBinContent(9,0.4000093);
   acc_shape_pt1->SetBinError(1,nan);
   acc_shape_pt1->SetBinError(2,0.001840106);
   acc_shape_pt1->SetBinError(3,0.003639678);
   acc_shape_pt1->SetBinError(4,0.005417116);
   acc_shape_pt1->SetBinError(5,0.007189064);
   acc_shape_pt1->SetBinError(6,0.01246501);
   acc_shape_pt1->SetBinError(7,0.01749302);
   acc_shape_pt1->SetBinError(8,0.02568432);
   acc_shape_pt1->SetBinError(9,0.1993962);
   acc_shape_pt1->SetEntries(1651.553);
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
   acc_5->Range(-5,-inf,45,inf);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[8] = {0, 5, 8, 10, 12, 15, 20, 40}; 
   
   TH1D *acc_eff_shape_dps_pt2 = new TH1D("acc_eff_shape_dps_pt2","acc_eff_shape_dps_pt2",7, xAxis5);
   acc_eff_shape_dps_pt2->SetBinContent(2,0.01306789);
   acc_eff_shape_dps_pt2->SetBinContent(3,0.02974824);
   acc_eff_shape_dps_pt2->SetBinContent(4,0.07445535);
   acc_eff_shape_dps_pt2->SetBinContent(5,0.1288635);
   acc_eff_shape_dps_pt2->SetBinContent(6,0.2113137);
   acc_eff_shape_dps_pt2->SetBinContent(7,0.103392);
   acc_eff_shape_dps_pt2->SetBinError(1,inf);
   acc_eff_shape_dps_pt2->SetBinError(2,0.003177828);
   acc_eff_shape_dps_pt2->SetBinError(3,0.0008786512);
   acc_eff_shape_dps_pt2->SetBinError(4,0.0009046616);
   acc_eff_shape_dps_pt2->SetBinError(5,0.001735813);
   acc_eff_shape_dps_pt2->SetBinError(8,nan);
   acc_eff_shape_dps_pt2->SetEntries(174.3851);
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
   acc_6->Range(-5,-0.0427095,45,0.7708694);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[8] = {0, 5, 8, 10, 12, 15, 20, 40}; 
   
   TH1D *acc_shape_pt2 = new TH1D("acc_shape_pt2","acc_shape_pt2",7, xAxis6);
   acc_shape_pt2->SetBinContent(2,0.07006388);
   acc_shape_pt2->SetBinContent(3,0.1212469);
   acc_shape_pt2->SetBinContent(4,0.2101744);
   acc_shape_pt2->SetBinContent(5,0.3127364);
   acc_shape_pt2->SetBinContent(6,0.4479475);
   acc_shape_pt2->SetBinContent(7,0.5631198);
   acc_shape_pt2->SetBinContent(8,1.000023);
   acc_shape_pt2->SetBinError(1,nan);
   acc_shape_pt2->SetBinError(2,0.001897887);
   acc_shape_pt2->SetBinError(3,0.00291483);
   acc_shape_pt2->SetBinError(4,0.007575387);
   acc_shape_pt2->SetBinError(5,0.01513342);
   acc_shape_pt2->SetBinError(6,0.03683775);
   acc_shape_pt2->SetBinError(7,0.09539815);
   acc_shape_pt2->SetBinError(8,1.459434);
   acc_shape_pt2->SetEntries(294.6979);
   acc_shape_pt2->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt2->SetLineColor(ci);
   acc_shape_pt2->SetLineWidth(2);
   acc_shape_pt2->GetXaxis()->SetTitle("Dimuon_{2} pT (GeV)");
   acc_shape_pt2->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt2->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1811347,0.995,"blNDC");
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
   acc_7->Range(-0.125,0.02080342,1.125,0.05420946);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[6] = {0, 0.05, 0.125, 0.2, 0.35, 1}; 
   
   TH1D *acc_eff_shape_dps_pta = new TH1D("acc_eff_shape_dps_pta","acc_eff_shape_dps_pta",5, xAxis7);
   acc_eff_shape_dps_pta->SetBinContent(1,0.02700643);
   acc_eff_shape_dps_pta->SetBinContent(2,0.03098703);
   acc_eff_shape_dps_pta->SetBinContent(3,0.03480909);
   acc_eff_shape_dps_pta->SetBinContent(4,0.03450216);
   acc_eff_shape_dps_pta->SetBinContent(5,0.04555698);
   acc_eff_shape_dps_pta->SetBinError(1,0.001650393);
   acc_eff_shape_dps_pta->SetBinError(2,0.001605613);
   acc_eff_shape_dps_pta->SetBinError(3,0.001995113);
   acc_eff_shape_dps_pta->SetBinError(4,0.001983535);
   acc_eff_shape_dps_pta->SetBinError(5,0.00403927);
   acc_eff_shape_dps_pta->SetBinError(6,nan);
   acc_eff_shape_dps_pta->SetEntries(1014.166);
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
   acc_8->Range(-0.125,0.08765287,1.125,0.1791428);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[6] = {0, 0.05, 0.125, 0.2, 0.35, 1}; 
   
   TH1D *acc_shape_pta = new TH1D("acc_shape_pta","acc_shape_pta",5, xAxis8);
   acc_shape_pta->SetBinContent(1,0.1034698);
   acc_shape_pta->SetBinContent(2,0.1107853);
   acc_shape_pta->SetBinContent(3,0.1209948);
   acc_shape_pta->SetBinContent(4,0.1295962);
   acc_shape_pta->SetBinContent(5,0.1585756);
   acc_shape_pta->SetBinError(1,0.00334853);
   acc_shape_pta->SetBinError(2,0.003151233);
   acc_shape_pta->SetBinError(3,0.003871473);
   acc_shape_pta->SetBinError(4,0.004017064);
   acc_shape_pta->SetBinError(5,0.007932899);
   acc_shape_pta->SetBinError(6,nan);
   acc_shape_pta->SetEntries(3592.779);
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

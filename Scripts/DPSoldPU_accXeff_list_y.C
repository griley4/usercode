{
//=========Macro generated from canvas: acc/acc
//=========  (Wed Jan 25 09:02:54 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",55,47,900,868);
   gStyle->SetOptStat(0);
   acc->Range(0,0,1,1);
   acc->SetFillColor(0);
   acc->SetBorderMode(0);
   acc->SetBorderSize(2);
   acc->SetFrameFillStyle(0);
   acc->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: acc_1
   TPad *acc_1 = new TPad("acc_1", "acc_1",0.01,0.6766667,0.49,0.99);
   acc_1->Draw();
   acc_1->cd();
   acc_1->Range(-3.025001,-inf,89.225,inf);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[11] = {6.2, 6.5, 7, 8.5, 11, 14, 18, 24, 30, 45, 80}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",10, xAxis1);
   acc_eff_shape_dps->SetBinContent(1,0.003625895);
   acc_eff_shape_dps->SetBinContent(2,0.00504015);
   acc_eff_shape_dps->SetBinContent(3,0.004900946);
   acc_eff_shape_dps->SetBinContent(4,0.004601238);
   acc_eff_shape_dps->SetBinContent(5,0.006519035);
   acc_eff_shape_dps->SetBinContent(6,0.01182224);
   acc_eff_shape_dps->SetBinContent(7,0.01537113);
   acc_eff_shape_dps->SetBinContent(8,0.01157894);
   acc_eff_shape_dps->SetBinContent(9,0.006657566);
   acc_eff_shape_dps->SetBinContent(10,0.01604464);
   acc_eff_shape_dps->SetBinError(1,0.0004115971);
   acc_eff_shape_dps->SetBinError(2,0.0004112891);
   acc_eff_shape_dps->SetBinError(3,0.0003493752);
   acc_eff_shape_dps->SetBinError(4,0.0003718767);
   acc_eff_shape_dps->SetBinError(5,0.0006182649);
   acc_eff_shape_dps->SetBinError(6,0.001462086);
   acc_eff_shape_dps->SetBinError(7,0.003812545);
   acc_eff_shape_dps->SetBinError(8,0.006780496);
   acc_eff_shape_dps->SetBinError(9,inf);
   acc_eff_shape_dps->SetBinError(10,inf);
   acc_eff_shape_dps->SetBinError(11,nan);
   acc_eff_shape_dps->SetEntries(551.9639);
   acc_eff_shape_dps->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps->SetLineColor(ci);
   acc_eff_shape_dps->SetLineWidth(2);
   acc_eff_shape_dps->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
   acc_eff_shape_dps->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps->Draw("E1");
   
   TPaveText *pt = new TPaveText(0.01,0.995,0.5438579,nan,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("acc_eff_shape_dps");
   pt->Draw();
   acc_1->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_2
   acc_2 = new TPad("acc_2", "acc_2",0.51,0.6766667,0.99,0.99);
   acc_2->Draw();
   acc_2->cd();
   acc_2->Range(-3.025001,0.01133893,89.225,0.1022666);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[11] = {6.2, 6.5, 7, 8.5, 11, 14, 18, 24, 30, 45, 80}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",10, xAxis2);
   acc_shape->SetBinContent(1,0.02789316);
   acc_shape->SetBinContent(2,0.03682146);
   acc_shape->SetBinContent(3,0.03964923);
   acc_shape->SetBinContent(4,0.03669231);
   acc_shape->SetBinContent(5,0.04820759);
   acc_shape->SetBinContent(6,0.07173398);
   acc_shape->SetBinContent(7,0.07569129);
   acc_shape->SetBinContent(8,0.04896541);
   acc_shape->SetBinContent(9,0.04478003);
   acc_shape->SetBinContent(10,0.08624225);
   acc_shape->SetBinError(1,0.004162506);
   acc_shape->SetBinError(2,0.003707321);
   acc_shape->SetBinError(3,0.002474251);
   acc_shape->SetBinError(4,0.001800333);
   acc_shape->SetBinError(5,0.00201665);
   acc_shape->SetBinError(6,0.003093101);
   acc_shape->SetBinError(7,0.003485788);
   acc_shape->SetBinError(8,0.002726557);
   acc_shape->SetBinError(9,0.00127038);
   acc_shape->SetBinError(10,0.003467635);
   acc_shape->SetBinError(11,nan);
   acc_shape->SetEntries(5830.655);
   acc_shape->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape->SetLineColor(ci);
   acc_shape->SetLineWidth(2);
   acc_shape->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
   acc_shape->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.185785,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape");
   pt->Draw();
   acc_2->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_3
   acc_3 = new TPad("acc_3", "acc_3",0.01,0.3433333,0.49,0.6566667);
   acc_3->Draw();
   acc_3->cd();
   acc_3->Range(-10,-0.007493989,90,0.06744589);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[10] = {0, 4, 8, 12, 15, 18, 22, 26, 30, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",9, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.00509843);
   acc_eff_shape_dps_pt->SetBinContent(2,0.0055055);
   acc_eff_shape_dps_pt->SetBinContent(3,0.006211806);
   acc_eff_shape_dps_pt->SetBinContent(4,0.01246575);
   acc_eff_shape_dps_pt->SetBinContent(5,0.02538593);
   acc_eff_shape_dps_pt->SetBinContent(6,0.0400525);
   acc_eff_shape_dps_pt->SetBinContent(7,0.0458451);
   acc_eff_shape_dps_pt->SetBinContent(8,0.02874296);
   acc_eff_shape_dps_pt->SetBinError(1,0.0005780548);
   acc_eff_shape_dps_pt->SetBinError(2,0.0004486776);
   acc_eff_shape_dps_pt->SetBinError(3,0.0004421724);
   acc_eff_shape_dps_pt->SetBinError(4,0.001004541);
   acc_eff_shape_dps_pt->SetBinError(5,0.002393386);
   acc_eff_shape_dps_pt->SetBinError(6,0.00490783);
   acc_eff_shape_dps_pt->SetBinError(7,0.01125196);
   acc_eff_shape_dps_pt->SetBinError(8,0.01671938);
   acc_eff_shape_dps_pt->SetEntries(65.49061);
   acc_eff_shape_dps_pt->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt->SetLineColor(ci);
   acc_eff_shape_dps_pt->SetLineWidth(2);
   acc_eff_shape_dps_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_eff_shape_dps_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.3555208,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_pt");
   pt->Draw();
   acc_3->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_4
   acc_4 = new TPad("acc_4", "acc_4",0.51,0.3433333,0.99,0.6566667);
   acc_4->Draw();
   acc_4->cd();
   acc_4->Range(-10,0.003968627,90,0.2687605);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[10] = {0, 4, 8, 12, 15, 18, 22, 26, 30, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",9, xAxis4);
   acc_shape_pt->SetBinContent(1,0.04237515);
   acc_shape_pt->SetBinContent(2,0.04130709);
   acc_shape_pt->SetBinContent(3,0.04456074);
   acc_shape_pt->SetBinContent(4,0.06989728);
   acc_shape_pt->SetBinContent(5,0.09787757);
   acc_shape_pt->SetBinContent(6,0.1380954);
   acc_shape_pt->SetBinContent(7,0.1711513);
   acc_shape_pt->SetBinContent(8,0.1658346);
   acc_shape_pt->SetBinContent(9,0.1760058);
   acc_shape_pt->SetBinError(1,0.001699177);
   acc_shape_pt->SetBinError(2,0.001252309);
   acc_shape_pt->SetBinError(3,0.001208424);
   acc_shape_pt->SetBinError(4,0.002452418);
   acc_shape_pt->SetBinError(5,0.004891732);
   acc_shape_pt->SetBinError(6,0.009621422);
   acc_shape_pt->SetBinError(7,0.02324977);
   acc_shape_pt->SetBinError(8,0.04303891);
   acc_shape_pt->SetBinError(9,0.05618818);
   acc_shape_pt->SetBinError(10,nan);
   acc_shape_pt->SetEntries(301.1745);
   acc_shape_pt->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt->SetLineColor(ci);
   acc_shape_pt->SetLineWidth(2);
   acc_shape_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_shape_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.2299628,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_pt");
   pt->Draw();
   acc_4->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_5
   acc_5 = new TPad("acc_5", "acc_5",0.01,0.01,0.49,0.3233333);
   acc_5->Draw();
   acc_5->cd();
   acc_5->Range(-0.275,0.002394734,2.475,0.02063522);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",10, xAxis5);
   acc_eff_shape_dps_y->SetBinContent(1,0.006797462);
   acc_eff_shape_dps_y->SetBinContent(2,0.008447607);
   acc_eff_shape_dps_y->SetBinContent(3,0.01434022);
   acc_eff_shape_dps_y->SetBinContent(4,0.01521911);
   acc_eff_shape_dps_y->SetBinContent(5,0.01412309);
   acc_eff_shape_dps_y->SetBinContent(6,0.01530765);
   acc_eff_shape_dps_y->SetBinContent(7,0.01599881);
   acc_eff_shape_dps_y->SetBinContent(8,0.008404481);
   acc_eff_shape_dps_y->SetBinContent(9,0.005915134);
   acc_eff_shape_dps_y->SetBinContent(10,0.005450354);
   acc_eff_shape_dps_y->SetBinError(1,0.000494813);
   acc_eff_shape_dps_y->SetBinError(2,0.0008358758);
   acc_eff_shape_dps_y->SetBinError(3,0.001751432);
   acc_eff_shape_dps_y->SetBinError(4,0.002086759);
   acc_eff_shape_dps_y->SetBinError(5,0.002096988);
   acc_eff_shape_dps_y->SetBinError(6,0.002249875);
   acc_eff_shape_dps_y->SetBinError(7,0.002117485);
   acc_eff_shape_dps_y->SetBinError(8,0.001127806);
   acc_eff_shape_dps_y->SetBinError(9,0.0007090816);
   acc_eff_shape_dps_y->SetBinError(10,0.0005697851);
   acc_eff_shape_dps_y->SetBinError(11,nan);
   acc_eff_shape_dps_y->SetEntries(499.0757);
   acc_eff_shape_dps_y->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_y->SetLineColor(ci);
   acc_eff_shape_dps_y->SetLineWidth(2);
   acc_eff_shape_dps_y->GetXaxis()->SetTitle("Four Mu Y");
   acc_eff_shape_dps_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_y->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.3438951,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_y");
   pt->Draw();
   acc_5->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_6
   acc_6 = new TPad("acc_6", "acc_6",0.51,0.01,0.99,0.3233333);
   acc_6->Draw();
   acc_6->cd();
   acc_6->Range(-0.275,0.03375756,2.475,0.08317406);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",10, xAxis6);
   acc_shape_y->SetBinContent(1,0.04533578);
   acc_shape_y->SetBinContent(2,0.05467553);
   acc_shape_y->SetBinContent(3,0.07045914);
   acc_shape_y->SetBinContent(4,0.06932971);
   acc_shape_y->SetBinContent(5,0.07149995);
   acc_shape_y->SetBinContent(6,0.06542751);
   acc_shape_y->SetBinContent(7,0.06843398);
   acc_shape_y->SetBinContent(8,0.05714925);
   acc_shape_y->SetBinContent(9,0.04644926);
   acc_shape_y->SetBinContent(10,0.04210437);
   acc_shape_y->SetBinError(1,0.001302102);
   acc_shape_y->SetBinError(2,0.002174724);
   acc_shape_y->SetBinError(3,0.003988202);
   acc_shape_y->SetBinError(4,0.004571022);
   acc_shape_y->SetBinError(5,0.004849923);
   acc_shape_y->SetBinError(6,0.004764831);
   acc_shape_y->SetBinError(7,0.004490964);
   acc_shape_y->SetBinError(8,0.003011167);
   acc_shape_y->SetBinError(9,0.002026664);
   acc_shape_y->SetBinError(10,0.001612269);
   acc_shape_y->SetBinError(11,nan);
   acc_shape_y->SetEntries(5308.266);
   acc_shape_y->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_y->SetLineColor(ci);
   acc_shape_y->SetLineWidth(2);
   acc_shape_y->GetXaxis()->SetTitle("Four Mu Y ");
   acc_shape_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_y->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.2183371,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_y");
   pt->Draw();
   acc_6->Modified();
   acc->cd();
   acc->Modified();
   acc->cd();
   acc->SetSelected(acc);
}

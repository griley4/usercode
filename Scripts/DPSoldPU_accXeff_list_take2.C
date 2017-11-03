{
//=========Macro generated from canvas: acc/acc
//=========  (Mon Jan 23 17:32:17 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",105,47,900,868);
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
   acc_1->Range(-3.025001,0.0003670558,89.225,0.02011329);
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
   acc_eff_shape_dps->SetBinError(1,0.0005677987);
   acc_eff_shape_dps->SetBinError(2,0.0007537295);
   acc_eff_shape_dps->SetBinError(3,0.0007414943);
   acc_eff_shape_dps->SetBinError(4,0.000646526);
   acc_eff_shape_dps->SetBinError(5,0.0009655007);
   acc_eff_shape_dps->SetBinError(6,0.001547135);
   acc_eff_shape_dps->SetBinError(7,0.002015306);
   acc_eff_shape_dps->SetBinError(8,0.00142477);
   acc_eff_shape_dps->SetBinError(9,0.0007363966);
   acc_eff_shape_dps->SetBinError(10,0.0009471474);
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
   
   TPaveText *pt = new TPaveText(0.01,0.9379046,0.3090179,0.995,"blNDC");
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
   acc_5->Range(-0.5625,0.002191209,5.0625,0.01958621);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[11] = {0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",10, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.005407532);
   acc_eff_shape_dps_dy->SetBinContent(2,0.006367652);
   acc_eff_shape_dps_dy->SetBinContent(3,0.007183075);
   acc_eff_shape_dps_dy->SetBinContent(4,0.006914909);
   acc_eff_shape_dps_dy->SetBinContent(5,0.009011957);
   acc_eff_shape_dps_dy->SetBinContent(6,0.01043607);
   acc_eff_shape_dps_dy->SetBinContent(7,0.01419795);
   acc_eff_shape_dps_dy->SetBinContent(8,0.0144408);
   acc_eff_shape_dps_dy->SetBinContent(9,0.01547821);
   acc_eff_shape_dps_dy->SetBinContent(10,0.007100947);
   acc_eff_shape_dps_dy->SetBinError(1,0.0008457114);
   acc_eff_shape_dps_dy->SetBinError(2,0.0009508174);
   acc_eff_shape_dps_dy->SetBinError(3,0.001084927);
   acc_eff_shape_dps_dy->SetBinError(4,0.0009700352);
   acc_eff_shape_dps_dy->SetBinError(5,0.001331877);
   acc_eff_shape_dps_dy->SetBinError(6,0.001362374);
   acc_eff_shape_dps_dy->SetBinError(7,0.001855286);
   acc_eff_shape_dps_dy->SetBinError(8,0.001770893);
   acc_eff_shape_dps_dy->SetBinError(9,0.001705836);
   acc_eff_shape_dps_dy->SetBinError(10,0.0004184799);
   acc_eff_shape_dps_dy->SetEntries(547.244);
   acc_eff_shape_dps_dy->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_dy->SetLineColor(ci);
   acc_eff_shape_dps_dy->SetLineWidth(2);
   acc_eff_shape_dps_dy->GetXaxis()->SetTitle("Four Mu #DeltaY");
   acc_eff_shape_dps_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.3624963,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_dy");
   pt->Draw();
   acc_5->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_6
   acc_6 = new TPad("acc_6", "acc_6",0.51,0.01,0.99,0.3233333);
   acc_6->Draw();
   acc_6->cd();
   acc_6->Range(-0.5625,0.03638277,5.0625,0.07961534);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[11] = {0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",10, xAxis6);
   acc_shape_dy->SetBinContent(1,0.04475798);
   acc_shape_dy->SetBinContent(2,0.05121143);
   acc_shape_dy->SetBinContent(3,0.04649524);
   acc_shape_dy->SetBinContent(4,0.04693655);
   acc_shape_dy->SetBinContent(5,0.05045379);
   acc_shape_dy->SetBinContent(6,0.06021166);
   acc_shape_dy->SetBinContent(7,0.06740094);
   acc_shape_dy->SetBinContent(8,0.0696383);
   acc_shape_dy->SetBinContent(9,0.06162176);
   acc_shape_dy->SetBinContent(10,0.04848286);
   acc_shape_dy->SetBinError(1,0.002483423);
   acc_shape_dy->SetBinError(2,0.002760018);
   acc_shape_dy->SetBinError(3,0.002818394);
   acc_shape_dy->SetBinError(4,0.002581213);
   acc_shape_dy->SetBinError(5,0.0032223);
   acc_shape_dy->SetBinError(6,0.003360308);
   acc_shape_dy->SetBinError(7,0.004160865);
   acc_shape_dy->SetBinError(8,0.004006829);
   acc_shape_dy->SetBinError(9,0.003492796);
   acc_shape_dy->SetBinError(10,0.001117594);
   acc_shape_dy->SetBinError(11,nan);
   acc_shape_dy->SetEntries(5892.711);
   acc_shape_dy->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_dy->SetLineColor(ci);
   acc_shape_dy->SetLineWidth(2);
   acc_shape_dy->GetXaxis()->SetTitle("Four Mu #DeltaY ");
   acc_shape_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.9379046,0.2369382,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_dy");
   pt->Draw();
   acc_6->Modified();
   acc->cd();
   acc->Modified();
   acc->cd();
   acc->SetSelected(acc);
}

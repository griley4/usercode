{
//=========Macro generated from canvas: acc/acc
//=========  (Sun Jan 22 13:43:41 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",10,69,900,900);
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
   acc_1->Range(-3.025001,0.0003691806,89.225,0.02010515);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[11] = {6.2, 6.5, 7, 8.5, 11, 14, 18, 24, 30, 45, 80}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",10, xAxis1);
   acc_eff_shape_dps->SetBinContent(1,0.003625894);
   acc_eff_shape_dps->SetBinContent(2,0.005040147);
   acc_eff_shape_dps->SetBinContent(3,0.004900944);
   acc_eff_shape_dps->SetBinContent(4,0.004601236);
   acc_eff_shape_dps->SetBinContent(5,0.006519032);
   acc_eff_shape_dps->SetBinContent(6,0.01182224);
   acc_eff_shape_dps->SetBinContent(7,0.01537112);
   acc_eff_shape_dps->SetBinContent(8,0.01157893);
   acc_eff_shape_dps->SetBinContent(9,0.006657563);
   acc_eff_shape_dps->SetBinContent(10,0.01604463);
   acc_eff_shape_dps->SetBinError(1,0.0005670719);
   acc_eff_shape_dps->SetBinError(2,0.0007525944);
   acc_eff_shape_dps->SetBinError(3,0.0007402356);
   acc_eff_shape_dps->SetBinError(4,0.0006454692);
   acc_eff_shape_dps->SetBinError(5,0.0009634478);
   acc_eff_shape_dps->SetBinError(6,0.001543331);
   acc_eff_shape_dps->SetBinError(7,0.002008586);
   acc_eff_shape_dps->SetBinError(8,0.001419939);
   acc_eff_shape_dps->SetBinError(9,0.0007337227);
   acc_eff_shape_dps->SetBinError(10,0.0009455578);
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
   
   TPaveText *pt = new TPaveText(0.01,0.9380352,0.3090179,0.995,"blNDC");
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
   acc_2->Range(-3.025001,0.01132477,89.225,0.1021658);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[11] = {6.2, 6.5, 7, 8.5, 11, 14, 18, 24, 30, 45, 80}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",10, xAxis2);
   acc_shape->SetBinContent(1,0.02786504);
   acc_shape->SetBinContent(2,0.03678434);
   acc_shape->SetBinContent(3,0.03960926);
   acc_shape->SetBinContent(4,0.03665532);
   acc_shape->SetBinContent(5,0.04815899);
   acc_shape->SetBinContent(6,0.07166167);
   acc_shape->SetBinContent(7,0.07561499);
   acc_shape->SetBinContent(8,0.04891605);
   acc_shape->SetBinContent(9,0.04473489);
   acc_shape->SetBinContent(10,0.08615531);
   acc_shape->SetBinError(1,0.004160349);
   acc_shape->SetBinError(2,0.003705385);
   acc_shape->SetBinError(3,0.002472956);
   acc_shape->SetBinError(4,0.001799393);
   acc_shape->SetBinError(5,0.002015586);
   acc_shape->SetBinError(6,0.003091437);
   acc_shape->SetBinError(7,0.003483907);
   acc_shape->SetBinError(8,0.002725118);
   acc_shape->SetBinError(9,0.001269712);
   acc_shape->SetBinError(10,0.003465747);
   acc_shape->SetBinError(11,nan);
   acc_shape->SetEntries(5830.655);
   acc_shape->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape->SetLineColor(ci);
   acc_shape->SetLineWidth(2);
   acc_shape->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
   acc_shape->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape->Draw("E1");
   
   pt = new TPaveText(0.01,0.9380352,0.185785,0.995,"blNDC");
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
   acc_3->Range(-10,-0.003930517,90,0.03537465);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[10] = {0, 4, 8, 12, 15, 18, 22, 26, 30, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",9, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.002674072);
   acc_eff_shape_dps_pt->SetBinContent(2,0.002887576);
   acc_eff_shape_dps_pt->SetBinContent(3,0.003258026);
   acc_eff_shape_dps_pt->SetBinContent(4,0.006538153);
   acc_eff_shape_dps_pt->SetBinContent(5,0.01331465);
   acc_eff_shape_dps_pt->SetBinContent(6,0.02100711);
   acc_eff_shape_dps_pt->SetBinContent(7,0.02404526);
   acc_eff_shape_dps_pt->SetBinContent(8,0.01507538);
   acc_eff_shape_dps_pt->SetBinError(1,0.0003031836);
   acc_eff_shape_dps_pt->SetBinError(2,0.0002353266);
   acc_eff_shape_dps_pt->SetBinError(3,0.0002319147);
   acc_eff_shape_dps_pt->SetBinError(4,0.0005268711);
   acc_eff_shape_dps_pt->SetBinError(5,0.001255305);
   acc_eff_shape_dps_pt->SetBinError(6,0.002574104);
   acc_eff_shape_dps_pt->SetBinError(7,0.00590153);
   acc_eff_shape_dps_pt->SetBinError(8,0.008769134);
   acc_eff_shape_dps_pt->SetEntries(65.49061);
   acc_eff_shape_dps_pt->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt->SetLineColor(ci);
   acc_eff_shape_dps_pt->SetLineWidth(2);
   acc_eff_shape_dps_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_eff_shape_dps_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.9380352,0.3555208,0.995,"blNDC");
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
   acc_4->Range(-10,0.002284332,90,0.1395645);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[10] = {0, 4, 8, 12, 15, 18, 22, 26, 30, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",9, xAxis4);
   acc_shape_pt->SetBinContent(1,0.02220292);
   acc_shape_pt->SetBinContent(2,0.02164329);
   acc_shape_pt->SetBinContent(3,0.02334808);
   acc_shape_pt->SetBinContent(4,0.03662343);
   acc_shape_pt->SetBinContent(5,0.05128401);
   acc_shape_pt->SetBinContent(6,0.07235657);
   acc_shape_pt->SetBinContent(7,0.08967659);
   acc_shape_pt->SetBinContent(8,0.08689084);
   acc_shape_pt->SetBinContent(9,0.09222015);
   acc_shape_pt->SetBinError(1,0.0008820899);
   acc_shape_pt->SetBinError(2,0.0006502637);
   acc_shape_pt->SetBinError(3,0.0006270208);
   acc_shape_pt->SetBinError(4,0.00126547);
   acc_shape_pt->SetBinError(5,0.002509362);
   acc_shape_pt->SetBinError(6,0.004895953);
   acc_shape_pt->SetBinError(7,0.01175652);
   acc_shape_pt->SetBinError(8,0.02178479);
   acc_shape_pt->SetBinError(9,0.02838657);
   acc_shape_pt->SetBinError(10,nan);
   acc_shape_pt->SetEntries(301.1745);
   acc_shape_pt->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt->SetLineColor(ci);
   acc_shape_pt->SetLineWidth(2);
   acc_shape_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_shape_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.9380352,0.2299628,0.995,"blNDC");
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
   acc_5->Range(-0.5625,0.001149266,5.0625,0.01027276);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[11] = {0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",10, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.002836193);
   acc_eff_shape_dps_dy->SetBinContent(2,0.003339765);
   acc_eff_shape_dps_dy->SetBinContent(3,0.003767446);
   acc_eff_shape_dps_dy->SetBinContent(4,0.003626796);
   acc_eff_shape_dps_dy->SetBinContent(5,0.004726675);
   acc_eff_shape_dps_dy->SetBinContent(6,0.005473606);
   acc_eff_shape_dps_dy->SetBinContent(7,0.007446674);
   acc_eff_shape_dps_dy->SetBinContent(8,0.007574045);
   acc_eff_shape_dps_dy->SetBinContent(9,0.008118153);
   acc_eff_shape_dps_dy->SetBinContent(10,0.003724371);
   acc_eff_shape_dps_dy->SetBinError(1,0.0004435666);
   acc_eff_shape_dps_dy->SetBinError(2,0.0004986935);
   acc_eff_shape_dps_dy->SetBinError(3,0.0005690327);
   acc_eff_shape_dps_dy->SetBinError(4,0.0005087731);
   acc_eff_shape_dps_dy->SetBinError(5,0.0006985553);
   acc_eff_shape_dps_dy->SetBinError(6,0.0007145504);
   acc_eff_shape_dps_dy->SetBinError(7,0.0009730774);
   acc_eff_shape_dps_dy->SetBinError(8,0.0009288144);
   acc_eff_shape_dps_dy->SetBinError(9,0.0008946928);
   acc_eff_shape_dps_dy->SetBinError(10,0.0002194882);
   acc_eff_shape_dps_dy->SetEntries(547.244);
   acc_eff_shape_dps_dy->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_dy->SetLineColor(ci);
   acc_eff_shape_dps_dy->SetLineWidth(2);
   acc_eff_shape_dps_dy->GetXaxis()->SetTitle("Four Mu #DeltaY");
   acc_eff_shape_dps_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.9380352,0.3624963,0.995,"blNDC");
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
   acc_6->Range(-0.5625,0.01908418,5.0625,0.04167511);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[11] = {0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",10, xAxis6);
   acc_shape_dy->SetBinContent(1,0.02345143);
   acc_shape_dy->SetBinContent(2,0.02683278);
   acc_shape_dy->SetBinContent(3,0.02436168);
   acc_shape_dy->SetBinContent(4,0.02459291);
   acc_shape_dy->SetBinContent(5,0.0264358);
   acc_shape_dy->SetBinContent(6,0.03154855);
   acc_shape_dy->SetBinContent(7,0.03531545);
   acc_shape_dy->SetBinContent(8,0.03648774);
   acc_shape_dy->SetBinContent(9,0.03228738);
   acc_shape_dy->SetBinContent(10,0.02540312);
   acc_shape_dy->SetBinError(1,0.001288529);
   acc_shape_dy->SetBinError(2,0.001429995);
   acc_shape_dy->SetBinError(3,0.001461765);
   acc_shape_dy->SetBinError(4,0.001338619);
   acc_shape_dy->SetBinError(5,0.001669787);
   acc_shape_dy->SetBinError(6,0.001737582);
   acc_shape_dy->SetBinError(7,0.002148196);
   acc_shape_dy->SetBinError(8,0.002067674);
   acc_shape_dy->SetBinError(9,0.001805537);
   acc_shape_dy->SetBinError(10,0.0005793865);
   acc_shape_dy->SetBinError(11,nan);
   acc_shape_dy->SetEntries(5892.711);
   acc_shape_dy->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_dy->SetLineColor(ci);
   acc_shape_dy->SetLineWidth(2);
   acc_shape_dy->GetXaxis()->SetTitle("Four Mu #DeltaY ");
   acc_shape_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.9380352,0.2369382,0.995,"blNDC");
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

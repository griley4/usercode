{
//=========Macro generated from canvas: acc/acc
//=========  (Mon Jan 23 17:43:54 2017) by ROOT version5.26/00
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
   acc_1->Range(-3.025001,-0.00879853,89.225,0.1827605);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[11] = {6.2, 6.5, 7, 8.5, 11, 14, 18, 24, 30, 45, 80}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",10, xAxis1);
   acc_eff_shape_dps->SetBinContent(0,0.01846972);
   acc_eff_shape_dps->SetBinContent(1,0.01953422);
   acc_eff_shape_dps->SetBinContent(2,0.02265232);
   acc_eff_shape_dps->SetBinContent(3,0.02203276);
   acc_eff_shape_dps->SetBinContent(4,0.02269034);
   acc_eff_shape_dps->SetBinContent(5,0.01853098);
   acc_eff_shape_dps->SetBinContent(6,0.02843624);
   acc_eff_shape_dps->SetBinContent(7,0.0459101);
   acc_eff_shape_dps->SetBinContent(8,0.06545206);
   acc_eff_shape_dps->SetBinContent(9,0.1080789);
   acc_eff_shape_dps->SetBinContent(10,0.09860529);
   acc_eff_shape_dps->SetBinError(0,0.002909392);
   acc_eff_shape_dps->SetBinError(1,0.0009018762);
   acc_eff_shape_dps->SetBinError(2,0.001158591);
   acc_eff_shape_dps->SetBinError(3,0.001249045);
   acc_eff_shape_dps->SetBinError(4,0.001176248);
   acc_eff_shape_dps->SetBinError(5,0.001223613);
   acc_eff_shape_dps->SetBinError(6,0.001910665);
   acc_eff_shape_dps->SetBinError(7,0.004393404);
   acc_eff_shape_dps->SetBinError(8,0.01009379);
   acc_eff_shape_dps->SetBinError(9,0.04112638);
   acc_eff_shape_dps->SetBinError(10,0.05770182);
   acc_eff_shape_dps->SetBinError(11,nan);
   acc_eff_shape_dps->SetEntries(86.74448);
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
   acc_2->Range(-3.025001,0.002005641,89.225,0.6208361);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[11] = {6.2, 6.5, 7, 8.5, 11, 14, 18, 24, 30, 45, 80}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",10, xAxis2);
   acc_shape->SetBinContent(0,0.09941009);
   acc_shape->SetBinContent(1,0.09756324);
   acc_shape->SetBinContent(2,0.1034867);
   acc_shape->SetBinContent(3,0.1086211);
   acc_shape->SetBinContent(4,0.1047518);
   acc_shape->SetBinContent(5,0.08873602);
   acc_shape->SetBinContent(6,0.1264215);
   acc_shape->SetBinContent(7,0.1558118);
   acc_shape->SetBinContent(8,0.1783417);
   acc_shape->SetBinContent(9,0.2665826);
   acc_shape->SetBinContent(10,0.4259358);
   acc_shape->SetBinError(0,0.006799484);
   acc_shape->SetBinError(1,0.004794411);
   acc_shape->SetBinError(2,0.003983716);
   acc_shape->SetBinError(3,0.002729971);
   acc_shape->SetBinError(4,0.002543143);
   acc_shape->SetBinError(5,0.002395428);
   acc_shape->SetBinError(6,0.003557312);
   acc_shape->SetBinError(7,0.005156056);
   acc_shape->SetBinError(8,0.01061803);
   acc_shape->SetBinError(9,0.02205832);
   acc_shape->SetBinError(10,0.1094428);
   acc_shape->SetBinError(11,nan);
   acc_shape->SetEntries(230.4777);
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
   acc_3->Range(-10,-0.01006093,90,0.1510972);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[10] = {0, 4, 8, 12, 15, 18, 22, 26, 30, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",9, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.01628423);
   acc_eff_shape_dps_pt->SetBinContent(2,0.01729379);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01274548);
   acc_eff_shape_dps_pt->SetBinContent(4,0.01708455);
   acc_eff_shape_dps_pt->SetBinContent(5,0.02224971);
   acc_eff_shape_dps_pt->SetBinContent(6,0.03640555);
   acc_eff_shape_dps_pt->SetBinContent(7,0.06137423);
   acc_eff_shape_dps_pt->SetBinContent(8,0.084504);
   acc_eff_shape_dps_pt->SetBinContent(9,0.1206896);
   acc_eff_shape_dps_pt->SetBinError(1,0.001461764);
   acc_eff_shape_dps_pt->SetBinError(2,0.001125337);
   acc_eff_shape_dps_pt->SetBinError(3,0.0008435943);
   acc_eff_shape_dps_pt->SetBinError(4,0.001084824);
   acc_eff_shape_dps_pt->SetBinError(5,0.001368147);
   acc_eff_shape_dps_pt->SetBinError(6,0.001937851);
   acc_eff_shape_dps_pt->SetBinError(7,0.003687394);
   acc_eff_shape_dps_pt->SetBinError(8,0.006525584);
   acc_eff_shape_dps_pt->SetBinError(9,0.008152426);
   acc_eff_shape_dps_pt->SetEntries(1130.826);
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
   acc_4->Range(-10,0.01520823,90,0.4105614);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[10] = {0, 4, 8, 12, 15, 18, 22, 26, 30, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",9, xAxis4);
   acc_shape_pt->SetBinContent(1,0.08155529);
   acc_shape_pt->SetBinContent(2,0.07476998);
   acc_shape_pt->SetBinContent(3,0.07113786);
   acc_shape_pt->SetBinContent(4,0.08874664);
   acc_shape_pt->SetBinContent(5,0.1207178);
   acc_shape_pt->SetBinContent(6,0.1583815);
   acc_shape_pt->SetBinContent(7,0.2067318);
   acc_shape_pt->SetBinContent(8,0.261295);
   acc_shape_pt->SetBinContent(9,0.3409275);
   acc_shape_pt->SetBinContent(10,0.5000116);
   acc_shape_pt->SetBinError(1,0.00337636);
   acc_shape_pt->SetBinError(2,0.002406362);
   acc_shape_pt->SetBinError(3,0.002050431);
   acc_shape_pt->SetBinError(4,0.002559416);
   acc_shape_pt->SetBinError(5,0.003338982);
   acc_shape_pt->SetBinError(6,0.00427775);
   acc_shape_pt->SetBinError(7,0.007228833);
   acc_shape_pt->SetBinError(8,0.01240433);
   acc_shape_pt->SetBinError(9,0.01503743);
   acc_shape_pt->SetBinError(10,0.2826177);
   acc_shape_pt->SetEntries(4288.797);
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
   acc_5->Range(-0.5625,0.001866802,5.0625,0.04990609);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[11] = {0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",10, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.02742132);
   acc_eff_shape_dps_dy->SetBinContent(2,0.02546546);
   acc_eff_shape_dps_dy->SetBinContent(3,0.02520141);
   acc_eff_shape_dps_dy->SetBinContent(4,0.02654698);
   acc_eff_shape_dps_dy->SetBinContent(5,0.02461253);
   acc_eff_shape_dps_dy->SetBinContent(6,0.02482702);
   acc_eff_shape_dps_dy->SetBinContent(7,0.02566114);
   acc_eff_shape_dps_dy->SetBinContent(8,0.02265824);
   acc_eff_shape_dps_dy->SetBinContent(9,0.01357843);
   acc_eff_shape_dps_dy->SetBinContent(10,0.02730608);
   acc_eff_shape_dps_dy->SetBinError(1,0.001264985);
   acc_eff_shape_dps_dy->SetBinError(2,0.001301488);
   acc_eff_shape_dps_dy->SetBinError(3,0.001427606);
   acc_eff_shape_dps_dy->SetBinError(4,0.001375087);
   acc_eff_shape_dps_dy->SetBinError(5,0.001623992);
   acc_eff_shape_dps_dy->SetBinError(6,0.001666925);
   acc_eff_shape_dps_dy->SetBinError(7,0.002453789);
   acc_eff_shape_dps_dy->SetBinError(8,0.003491914);
   acc_eff_shape_dps_dy->SetBinError(9,0.005164781);
   acc_eff_shape_dps_dy->SetBinError(10,0.01596601);
   acc_eff_shape_dps_dy->SetEntries(189.4255);
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
   acc_6->Range(-0.5625,0.01778958,5.0625,0.1390052);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[11] = {0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",10, xAxis6);
   acc_shape_dy->SetBinContent(1,0.119507);
   acc_shape_dy->SetBinContent(2,0.1182849);
   acc_shape_dy->SetBinContent(3,0.1149878);
   acc_shape_dy->SetBinContent(4,0.1114617);
   acc_shape_dy->SetBinContent(5,0.1129058);
   acc_shape_dy->SetBinContent(6,0.09890339);
   acc_shape_dy->SetBinContent(7,0.0922999);
   acc_shape_dy->SetBinContent(8,0.0865928);
   acc_shape_dy->SetBinContent(9,0.04371686);
   acc_shape_dy->SetBinContent(10,0.06837765);
   acc_shape_dy->SetBinError(1,0.002758867);
   acc_shape_dy->SetBinError(2,0.002931391);
   acc_shape_dy->SetBinError(3,0.003182571);
   acc_shape_dy->SetBinError(4,0.002934175);
   acc_shape_dy->SetBinError(5,0.003627702);
   acc_shape_dy->SetBinError(6,0.003447742);
   acc_shape_dy->SetBinError(7,0.004806185);
   acc_shape_dy->SetBinError(8,0.007041305);
   acc_shape_dy->SetBinError(9,0.009407877);
   acc_shape_dy->SetBinError(10,0.02578627);
   acc_shape_dy->SetBinError(11,nan);
   acc_shape_dy->SetEntries(1123.866);
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

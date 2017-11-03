{
//=========Macro generated from canvas: acc/acc
//=========  (Mon Feb 20 10:15:39 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",897,47,900,867);
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
   acc_1->Range(-3.025001,-0.01899178,89.225,0.170926);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 80}; 
   
   TH1D *fourmu_mass_alt = new TH1D("fourmu_mass_alt","fourmu_mass_alt",9, xAxis1);
   fourmu_mass_alt->SetBinContent(0,0.01846972);
   fourmu_mass_alt->SetBinContent(1,0.02142697);
   fourmu_mass_alt->SetBinContent(2,0.02221486);
   fourmu_mass_alt->SetBinContent(3,0.02262098);
   fourmu_mass_alt->SetBinContent(4,0.01853098);
   fourmu_mass_alt->SetBinContent(5,0.02843624);
   fourmu_mass_alt->SetBinContent(6,0.04699465);
   fourmu_mass_alt->SetBinContent(7,0.06688011);
   fourmu_mass_alt->SetBinContent(8,0.1080789);
   fourmu_mass_alt->SetBinContent(9,0.09860529);
   fourmu_mass_alt->SetBinError(0,0.002909392);
   fourmu_mass_alt->SetBinError(1,0.001357906);
   fourmu_mass_alt->SetBinError(2,0.001055741);
   fourmu_mass_alt->SetBinError(3,0.001298359);
   fourmu_mass_alt->SetBinError(4,0.001058198);
   fourmu_mass_alt->SetBinError(5,0.001610718);
   fourmu_mass_alt->SetBinError(6,0.002596644);
   fourmu_mass_alt->SetBinError(7,0.007227739);
   fourmu_mass_alt->SetBinError(8,0.01309785);
   fourmu_mass_alt->SetBinError(9,0.046094);
   fourmu_mass_alt->SetMinimum(0);
   fourmu_mass_alt->SetEntries(79.61445);
   fourmu_mass_alt->SetStats(0);
   fourmu_mass_alt->SetLineWidth(2);
   fourmu_mass_alt->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
   fourmu_mass_alt->GetYaxis()->SetTitle("Events");
   fourmu_mass_alt->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9390328,0.2043862,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("fourmu_mass_alt");
   pt->Draw();
   acc_1->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_2
   acc_2 = new TPad("acc_2", "acc_2",0.51,0.76,0.99,0.99);
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
   Double_t xAxis2[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 80}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",9, xAxis2);
   acc_shape->SetBinContent(0,0.09941009);
   acc_shape->SetBinContent(1,0.1011589);
   acc_shape->SetBinContent(2,0.1082266);
   acc_shape->SetBinContent(3,0.1041548);
   acc_shape->SetBinContent(4,0.08873602);
   acc_shape->SetBinContent(5,0.1264215);
   acc_shape->SetBinContent(6,0.1553584);
   acc_shape->SetBinContent(7,0.1891003);
   acc_shape->SetBinContent(8,0.2665826);
   acc_shape->SetBinContent(9,0.4259358);
   acc_shape->SetBinError(0,0.006799484);
   acc_shape->SetBinError(1,0.003065423);
   acc_shape->SetBinError(2,0.002427917);
   acc_shape->SetBinError(3,0.002896873);
   acc_shape->SetBinError(4,0.002395428);
   acc_shape->SetBinError(5,0.003557312);
   acc_shape->SetBinError(6,0.004966346);
   acc_shape->SetBinError(7,0.01285533);
   acc_shape->SetBinError(8,0.02205832);
   acc_shape->SetBinError(9,0.1094428);
   acc_shape->SetBinError(10,nan);
   acc_shape->SetEntries(205.6095);
   acc_shape->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   acc_shape->SetLineColor(ci);
   acc_shape->SetLineWidth(2);
   acc_shape->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
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
   acc_3->Range(-10,-0.003264493,90,0.116535);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",6, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.01642734);
   acc_eff_shape_dps_pt->SetBinContent(2,0.01386493);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01767661);
   acc_eff_shape_dps_pt->SetBinContent(4,0.02705417);
   acc_eff_shape_dps_pt->SetBinContent(5,0.05204162);
   acc_eff_shape_dps_pt->SetBinContent(6,0.09543021);
   acc_eff_shape_dps_pt->SetBinError(1,0.0009637853);
   acc_eff_shape_dps_pt->SetBinError(2,0.0008030143);
   acc_eff_shape_dps_pt->SetBinError(3,0.0009694275);
   acc_eff_shape_dps_pt->SetBinError(4,0.001426161);
   acc_eff_shape_dps_pt->SetBinError(5,0.002597588);
   acc_eff_shape_dps_pt->SetBinError(6,0.004561025);
   acc_eff_shape_dps_pt->SetEntries(1542.283);
   acc_eff_shape_dps_pt->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt->SetLineColor(ci);
   acc_eff_shape_dps_pt->SetLineWidth(2);
   acc_eff_shape_dps_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_eff_shape_dps_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.2555394,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_pt");
   pt->Draw();
   acc_3->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_4
   acc_4 = new TPad("acc_4", "acc_4",0.51,0.51,0.99,0.74);
   acc_4->Draw();
   acc_4->cd();
   acc_4->Range(-10,0.02730063,90,0.3402109);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",6, xAxis4);
   acc_shape_pt->SetBinContent(1,0.07760063);
   acc_shape_pt->SetBinContent(2,0.07182439);
   acc_shape_pt->SetBinContent(3,0.09438906);
   acc_shape_pt->SetBinContent(4,0.1344609);
   acc_shape_pt->SetBinContent(5,0.1875841);
   acc_shape_pt->SetBinContent(6,0.2883779);
   acc_shape_pt->SetBinContent(7,0.5000116);
   acc_shape_pt->SetBinError(1,0.002157914);
   acc_shape_pt->SetBinError(2,0.00187998);
   acc_shape_pt->SetBinError(3,0.002324277);
   acc_shape_pt->SetBinError(4,0.003344235);
   acc_shape_pt->SetBinError(5,0.005247647);
   acc_shape_pt->SetBinError(6,0.00862157);
   acc_shape_pt->SetBinError(7,0.2826177);
   acc_shape_pt->SetEntries(6135.923);
   acc_shape_pt->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt->SetLineColor(ci);
   acc_shape_pt->SetLineWidth(2);
   acc_shape_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_shape_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1695089,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_pt");
   pt->Draw();
   acc_4->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_5
   acc_5 = new TPad("acc_5", "acc_5",0.01,0.26,0.49,0.49);
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
   Double_t xAxis5[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",8, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.02650818);
   acc_eff_shape_dps_dy->SetBinContent(2,0.0255388);
   acc_eff_shape_dps_dy->SetBinContent(3,0.02563938);
   acc_eff_shape_dps_dy->SetBinContent(4,0.02482702);
   acc_eff_shape_dps_dy->SetBinContent(5,0.02566114);
   acc_eff_shape_dps_dy->SetBinContent(6,0.02265824);
   acc_eff_shape_dps_dy->SetBinContent(7,0.01357843);
   acc_eff_shape_dps_dy->SetBinContent(8,0.02730608);
   acc_eff_shape_dps_dy->SetBinError(1,0.0009077435);
   acc_eff_shape_dps_dy->SetBinError(2,0.001072157);
   acc_eff_shape_dps_dy->SetBinError(3,0.001377081);
   acc_eff_shape_dps_dy->SetBinError(4,0.001666925);
   acc_eff_shape_dps_dy->SetBinError(5,0.002453789);
   acc_eff_shape_dps_dy->SetBinError(6,0.003491914);
   acc_eff_shape_dps_dy->SetBinError(7,0.005164781);
   acc_eff_shape_dps_dy->SetBinError(8,0.01596601);
   acc_eff_shape_dps_dy->SetEntries(119.9391);
   acc_eff_shape_dps_dy->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_dy->SetLineColor(ci);
   acc_eff_shape_dps_dy->SetLineWidth(2);
   acc_eff_shape_dps_dy->GetXaxis()->SetTitle("Four Mu #DeltaY");
   acc_eff_shape_dps_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.2601897,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_dy");
   pt->Draw();
   acc_5->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_6
   acc_6 = new TPad("acc_6", "acc_6",0.51,0.26,0.99,0.49);
   acc_6->Draw();
   acc_6->cd();
   acc_6->Range(-0.5625,0.01803756,5.0625,0.1374335);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",8, xAxis6);
   acc_shape_dy->SetBinContent(1,0.1189365);
   acc_shape_dy->SetBinContent(2,0.1129757);
   acc_shape_dy->SetBinContent(3,0.1131935);
   acc_shape_dy->SetBinContent(4,0.09890339);
   acc_shape_dy->SetBinContent(5,0.0922999);
   acc_shape_dy->SetBinContent(6,0.0865928);
   acc_shape_dy->SetBinContent(7,0.04371686);
   acc_shape_dy->SetBinContent(8,0.06837765);
   acc_shape_dy->SetBinError(1,0.002009067);
   acc_shape_dy->SetBinError(2,0.002350973);
   acc_shape_dy->SetBinError(3,0.003016725);
   acc_shape_dy->SetBinError(4,0.003447742);
   acc_shape_dy->SetBinError(5,0.004806185);
   acc_shape_dy->SetBinError(6,0.007041305);
   acc_shape_dy->SetBinError(7,0.009407877);
   acc_shape_dy->SetBinError(8,0.02578627);
   acc_shape_dy->SetBinError(9,nan);
   acc_shape_dy->SetEntries(671.5389);
   acc_shape_dy->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_dy->SetLineColor(ci);
   acc_shape_dy->SetLineWidth(2);
   acc_shape_dy->GetXaxis()->SetTitle("Four Mu #DeltaY ");
   acc_shape_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1741592,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_dy");
   pt->Draw();
   acc_6->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_7
   acc_7 = new TPad("acc_7", "acc_7",0.01,0.01,0.49,0.24);
   acc_7->Draw();
   acc_7->cd();
   acc_7->Range(-0.275,0.00945233,2.475,0.05103306);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",10, xAxis7);
   acc_eff_shape_dps_y->SetBinContent(1,0.03577394);
   acc_eff_shape_dps_y->SetBinContent(2,0.03567842);
   acc_eff_shape_dps_y->SetBinContent(3,0.04134786);
   acc_eff_shape_dps_y->SetBinContent(4,0.03799442);
   acc_eff_shape_dps_y->SetBinContent(5,0.04216027);
   acc_eff_shape_dps_y->SetBinContent(6,0.03112481);
   acc_eff_shape_dps_y->SetBinContent(7,0.03069787);
   acc_eff_shape_dps_y->SetBinContent(8,0.02323072);
   acc_eff_shape_dps_y->SetBinContent(9,0.02243196);
   acc_eff_shape_dps_y->SetBinContent(10,0.01597226);
   acc_eff_shape_dps_y->SetBinError(1,0.003503381);
   acc_eff_shape_dps_y->SetBinError(2,0.003430908);
   acc_eff_shape_dps_y->SetBinError(3,0.003631484);
   acc_eff_shape_dps_y->SetBinError(4,0.003283295);
   acc_eff_shape_dps_y->SetBinError(5,0.003130688);
   acc_eff_shape_dps_y->SetBinError(6,0.002317426);
   acc_eff_shape_dps_y->SetBinError(7,0.00187935);
   acc_eff_shape_dps_y->SetBinError(8,0.001321922);
   acc_eff_shape_dps_y->SetBinError(9,0.001154492);
   acc_eff_shape_dps_y->SetBinError(10,0.0008532619);
   acc_eff_shape_dps_y->SetBinError(11,nan);
   acc_eff_shape_dps_y->SetEntries(1422.669);
   acc_eff_shape_dps_y->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_y->SetLineColor(ci);
   acc_eff_shape_dps_y->SetLineWidth(2);
   acc_eff_shape_dps_y->GetXaxis()->SetTitle("Four Mu Y");
   acc_eff_shape_dps_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_y->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.2462388,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_eff_shape_dps_y");
   pt->Draw();
   acc_7->Modified();
   acc->cd();
  
// ------------>Primitives in pad: acc_8
   acc_8 = new TPad("acc_8", "acc_8",0.51,0.01,0.99,0.24);
   acc_8->Draw();
   acc_8->cd();
   acc_8->Range(-0.275,0.08722972,2.475,0.1550003);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",10, xAxis8);
   acc_shape_y->SetBinContent(1,0.1384169);
   acc_shape_y->SetBinContent(2,0.1181601);
   acc_shape_y->SetBinContent(3,0.1348895);
   acc_shape_y->SetBinContent(4,0.1221794);
   acc_shape_y->SetBinContent(5,0.1254742);
   acc_shape_y->SetBinContent(6,0.1253957);
   acc_shape_y->SetBinContent(7,0.1189755);
   acc_shape_y->SetBinContent(8,0.1085901);
   acc_shape_y->SetBinContent(9,0.1063599);
   acc_shape_y->SetBinContent(10,0.09867097);
   acc_shape_y->SetBinError(1,0.007224648);
   acc_shape_y->SetBinError(2,0.006487557);
   acc_shape_y->SetBinError(3,0.006847398);
   acc_shape_y->SetBinError(4,0.00612185);
   acc_shape_y->SetBinError(5,0.005612622);
   acc_shape_y->SetBinError(6,0.004859493);
   acc_shape_y->SetBinError(7,0.003855022);
   acc_shape_y->SetBinError(8,0.002974873);
   acc_shape_y->SetBinError(9,0.002615033);
   acc_shape_y->SetBinError(10,0.002205397);
   acc_shape_y->SetBinError(11,nan);
   acc_shape_y->SetEntries(5669.523);
   acc_shape_y->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_y->SetLineColor(ci);
   acc_shape_y->SetLineWidth(2);
   acc_shape_y->GetXaxis()->SetTitle("Four Mu Y ");
   acc_shape_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_y->Draw("E1");
   
   pt = new TPaveText(0.01,0.9411508,0.1602083,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("acc_shape_y");
   pt->Draw();
   acc_8->Modified();
   acc->cd();
   acc->Modified();
   acc->cd();
   acc->SetSelected(acc);
}

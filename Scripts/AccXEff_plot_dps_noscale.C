{
//=========Macro generated from canvas: acc/acc
//=========  (Sun Mar 12 17:23:33 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",491,68,900,900);
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
   acc_1->Range(-0.5250007,-inf,66.725,inf);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 60}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",9, xAxis1);
   acc_eff_shape_dps->SetBinContent(1,0.00877193);
   acc_eff_shape_dps->SetBinContent(2,0.004137116);
   acc_eff_shape_dps->SetBinContent(3,0.004444444);
   acc_eff_shape_dps->SetBinContent(4,0.003940332);
   acc_eff_shape_dps->SetBinContent(5,0.007928229);
   acc_eff_shape_dps->SetBinContent(6,0.01156278);
   acc_eff_shape_dps->SetBinContent(7,0.01239816);
   acc_eff_shape_dps->SetBinContent(8,0.007899508);
   acc_eff_shape_dps->SetBinContent(9,0.009508716);
   acc_eff_shape_dps->SetBinError(1,0.001725587);
   acc_eff_shape_dps->SetBinError(2,0.0008147527);
   acc_eff_shape_dps->SetBinError(3,0.001236581);
   acc_eff_shape_dps->SetBinError(4,0.0007769935);
   acc_eff_shape_dps->SetBinError(5,0.001409792);
   acc_eff_shape_dps->SetBinError(6,0.001965697);
   acc_eff_shape_dps->SetBinError(7,0.001948222);
   acc_eff_shape_dps->SetBinError(8,0.001155207);
   acc_eff_shape_dps->SetBinError(9,inf);
   acc_eff_shape_dps->SetBinError(10,nan);
   acc_eff_shape_dps->SetEntries(146.5554);
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
   acc_2 = new TPad("acc_2", "acc_2",0.51,0.76,0.99,0.99);
   acc_2->Draw();
   acc_2->cd();
   acc_2->Range(-0.5250007,0.02697555,66.725,0.1036604);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 60}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",9, xAxis2);
   acc_shape->SetBinContent(1,0.04511278);
   acc_shape->SetBinContent(2,0.05496454);
   acc_shape->SetBinContent(3,0.05111111);
   acc_shape->SetBinContent(4,0.04981706);
   acc_shape->SetBinContent(5,0.06718131);
   acc_shape->SetBinContent(6,0.08888889);
   acc_shape->SetBinContent(7,0.07261778);
   acc_shape->SetBinContent(8,0.06462056);
   acc_shape->SetBinContent(9,0.07606973);
   acc_shape->SetBinError(1,0.007686523);
   acc_shape->SetBinError(2,0.005854099);
   acc_shape->SetBinError(3,0.005463183);
   acc_shape->SetBinError(4,0.003836615);
   acc_shape->SetBinError(5,0.003867583);
   acc_shape->SetBinError(6,0.004181737);
   acc_shape->SetBinError(7,0.005252772);
   acc_shape->SetBinError(8,0.002984818);
   acc_shape->SetBinError(9,0.008053719);
   acc_shape->SetBinError(10,nan);
   acc_shape->SetEntries(1197.294);
   acc_shape->SetStats(0);

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
   acc_3->Range(-10,0.0004021993,90,0.03505592);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",6, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.008507535);
   acc_eff_shape_dps_pt->SetBinContent(2,0.005943703);
   acc_eff_shape_dps_pt->SetBinContent(3,0.006827983);
   acc_eff_shape_dps_pt->SetBinContent(4,0.01192901);
   acc_eff_shape_dps_pt->SetBinContent(5,0.02479339);
   acc_eff_shape_dps_pt->SetBinContent(6,0.01970443);
   acc_eff_shape_dps_pt->SetBinError(1,0.001021161);
   acc_eff_shape_dps_pt->SetBinError(2,0.0008188531);
   acc_eff_shape_dps_pt->SetBinError(3,0.0009074707);
   acc_eff_shape_dps_pt->SetBinError(4,0.001874077);
   acc_eff_shape_dps_pt->SetBinError(5,0.005477021);
   acc_eff_shape_dps_pt->SetBinError(6,0.009948809);
   acc_eff_shape_dps_pt->SetEntries(44.71918);
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
   acc_4->Range(-10,0.02369302,90,0.2391663);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",6, xAxis4);
   acc_shape_pt->SetBinContent(1,0.06332037);
   acc_shape_pt->SetBinContent(2,0.05562409);
   acc_shape_pt->SetBinContent(3,0.06109248);
   acc_shape_pt->SetBinContent(4,0.0922316);
   acc_shape_pt->SetBinContent(5,0.1558442);
   acc_shape_pt->SetBinContent(6,0.1773399);
   acc_shape_pt->SetBinError(1,0.002860597);
   acc_shape_pt->SetBinError(2,0.002566119);
   acc_shape_pt->SetBinError(3,0.00278663);
   acc_shape_pt->SetBinError(4,0.005413866);
   acc_shape_pt->SetBinError(5,0.01458321);
   acc_shape_pt->SetBinError(6,0.03207053);
   acc_shape_pt->SetBinError(7,nan);
   acc_shape_pt->SetEntries(283.4986);
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
   acc_5->Range(-0.5625,0.002499556,5.0625,0.01622912);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",8, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.006136417);
   acc_eff_shape_dps_dy->SetBinContent(2,0.008392511);
   acc_eff_shape_dps_dy->SetBinContent(3,0.006360078);
   acc_eff_shape_dps_dy->SetBinContent(4,0.01097973);
   acc_eff_shape_dps_dy->SetBinContent(5,0.01182994);
   acc_eff_shape_dps_dy->SetBinContent(6,0.01152453);
   acc_eff_shape_dps_dy->SetBinContent(7,0.01238671);
   acc_eff_shape_dps_dy->SetBinContent(8,0.005119268);
   acc_eff_shape_dps_dy->SetBinError(1,0.001207137);
   acc_eff_shape_dps_dy->SetBinError(2,0.001652799);
   acc_eff_shape_dps_dy->SetBinError(3,0.001769569);
   acc_eff_shape_dps_dy->SetBinError(4,0.002165091);
   acc_eff_shape_dps_dy->SetBinError(5,0.002103592);
   acc_eff_shape_dps_dy->SetBinError(6,0.001959194);
   acc_eff_shape_dps_dy->SetBinError(7,0.001946423);
   acc_eff_shape_dps_dy->SetBinError(8,0.0007486309);
   acc_eff_shape_dps_dy->SetEntries(214.843);
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
   acc_6->Range(-0.5625,0.04542825,5.0625,0.1003718);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",8, xAxis6);
   acc_shape_dy->SetBinContent(1,0.05900401);
   acc_shape_dy->SetBinContent(2,0.06488057);
   acc_shape_dy->SetBinContent(3,0.0704501);
   acc_shape_dy->SetBinContent(4,0.07939189);
   acc_shape_dy->SetBinContent(5,0.08687616);
   acc_shape_dy->SetBinContent(6,0.08429371);
   acc_shape_dy->SetBinContent(7,0.06918429);
   acc_shape_dy->SetBinContent(8,0.05544058);
   acc_shape_dy->SetBinError(1,0.003840257);
   acc_shape_dy->SetBinError(2,0.004722447);
   acc_shape_dy->SetBinError(3,0.006074123);
   acc_shape_dy->SetBinError(4,0.006015709);
   acc_shape_dy->SetBinError(5,0.00590822);
   acc_shape_dy->SetBinError(6,0.00548591);
   acc_shape_dy->SetBinError(7,0.004727331);
   acc_shape_dy->SetBinError(8,0.002524561);
   acc_shape_dy->SetBinError(9,nan);
   acc_shape_dy->SetEntries(1591.095);
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
   acc_7->Range(-0.275,-0.001099687,2.475,0.01841885);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",10, xAxis7);
   acc_eff_shape_dps_y->SetBinContent(1,0.006454879);
   acc_eff_shape_dps_y->SetBinContent(2,0.007149901);
   acc_eff_shape_dps_y->SetBinContent(3,0.00965466);
   acc_eff_shape_dps_y->SetBinContent(4,0.0120532);
   acc_eff_shape_dps_y->SetBinContent(5,0.01061865);
   acc_eff_shape_dps_y->SetBinContent(6,0.01313131);
   acc_eff_shape_dps_y->SetBinContent(7,0.01116071);
   acc_eff_shape_dps_y->SetBinContent(8,0.006507592);
   acc_eff_shape_dps_y->SetBinContent(9,0.004765146);
   acc_eff_shape_dps_y->SetBinContent(10,0.00536193);
   acc_eff_shape_dps_y->SetBinError(1,0.0009067763);
   acc_eff_shape_dps_y->SetBinError(2,0.001332441);
   acc_eff_shape_dps_y->SetBinError(3,0.001902553);
   acc_eff_shape_dps_y->SetBinError(4,0.002251672);
   acc_eff_shape_dps_y->SetBinError(5,0.002225867);
   acc_eff_shape_dps_y->SetBinError(6,0.002592116);
   acc_eff_shape_dps_y->SetBinError(7,0.002244564);
   acc_eff_shape_dps_y->SetBinError(8,0.001424686);
   acc_eff_shape_dps_y->SetBinError(9,0.00127657);
   acc_eff_shape_dps_y->SetBinError(10,0.003801608);
   acc_eff_shape_dps_y->SetBinError(11,nan);
   acc_eff_shape_dps_y->SetEntries(163.6134);
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
   acc_8->Range(-0.275,0.009647087,2.475,0.1056923);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",10, xAxis8);
   acc_shape_y->SetBinContent(1,0.06024554);
   acc_shape_y->SetBinContent(2,0.06558185);
   acc_shape_y->SetBinContent(3,0.08652061);
   acc_shape_y->SetBinContent(4,0.08229426);
   acc_shape_y->SetBinContent(5,0.08171745);
   acc_shape_y->SetBinContent(6,0.08030303);
   acc_shape_y->SetBinContent(7,0.07946429);
   acc_shape_y->SetBinContent(8,0.06476604);
   acc_shape_y->SetBinContent(9,0.03539823);
   acc_shape_y->SetBinContent(10,0.03217158);
   acc_shape_y->SetBinError(1,0.002843313);
   acc_shape_y->SetBinError(2,0.004150843);
   acc_shape_y->SetBinError(3,0.005908274);
   acc_shape_y->SetBinError(4,0.006084286);
   acc_shape_y->SetBinError(5,0.006388297);
   acc_shape_y->SetBinError(6,0.00661921);
   acc_shape_y->SetBinError(7,0.006188225);
   acc_shape_y->SetBinError(8,0.004622759);
   acc_shape_y->SetBinError(9,0.003531983);
   acc_shape_y->SetBinError(10,0.009435344);
   acc_shape_y->SetBinError(11,nan);
   acc_shape_y->SetEntries(1302.638);
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

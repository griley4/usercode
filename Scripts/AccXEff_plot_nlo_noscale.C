{
//=========Macro generated from canvas: acc/acc
//=========  (Mon Mar 13 13:09:27 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",22,69,900,900);
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
   acc_eff_shape_dps->SetBinContent(0,0.02840909);
   acc_eff_shape_dps->SetBinContent(1,0.02412582);
   acc_eff_shape_dps->SetBinContent(2,0.02699714);
   acc_eff_shape_dps->SetBinContent(3,0.03230404);
   acc_eff_shape_dps->SetBinContent(4,0.02632434);
   acc_eff_shape_dps->SetBinContent(5,0.03187052);
   acc_eff_shape_dps->SetBinContent(6,0.04090498);
   acc_eff_shape_dps->SetBinContent(7,0.06147186);
   acc_eff_shape_dps->SetBinContent(8,0.107563);
   acc_eff_shape_dps->SetBinContent(9,0.125);
   acc_eff_shape_dps->SetBinError(0,0.004869746);
   acc_eff_shape_dps->SetBinError(1,0.001031759);
   acc_eff_shape_dps->SetBinError(2,0.001443153);
   acc_eff_shape_dps->SetBinError(3,0.002140521);
   acc_eff_shape_dps->SetBinError(4,0.002315854);
   acc_eff_shape_dps->SetBinError(5,0.003709793);
   acc_eff_shape_dps->SetBinError(6,0.00744782);
   acc_eff_shape_dps->SetBinError(7,0.02772703);
   acc_eff_shape_dps->SetBinError(8,0.06380327);
   acc_eff_shape_dps->SetBinError(9,inf);
   acc_eff_shape_dps->SetBinError(10,nan);
   acc_eff_shape_dps->SetEntries(59.74195);
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
   acc_2->Range(-0.5250007,0.01782492,66.725,0.5985117);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 60}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",9, xAxis2);
   acc_shape->SetBinContent(0,0.1095779);
   acc_shape->SetBinContent(1,0.1010841);
   acc_shape->SetBinContent(2,0.1126877);
   acc_shape->SetBinContent(3,0.1225653);
   acc_shape->SetBinContent(4,0.1147221);
   acc_shape->SetBinContent(5,0.125146);
   acc_shape->SetBinContent(6,0.1366516);
   acc_shape->SetBinContent(7,0.1688312);
   acc_shape->SetBinContent(8,0.2756303);
   acc_shape->SetBinContent(9,0.4);
   acc_shape->SetBinError(0,0.00993425);
   acc_shape->SetBinError(1,0.004122534);
   acc_shape->SetBinError(2,0.003398991);
   acc_shape->SetBinError(3,0.0046677);
   acc_shape->SetBinError(4,0.004558565);
   acc_shape->SetBinError(5,0.004847198);
   acc_shape->SetBinError(6,0.005302185);
   acc_shape->SetBinError(7,0.01307107);
   acc_shape->SetBinError(8,0.02430902);
   acc_shape->SetBinError(9,0.1183216);
   acc_shape->SetBinError(10,nan);
   acc_shape->SetEntries(162.9372);
   acc_shape->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape->SetLineColor(ci);
   acc_shape->SetLineWidth(2);
   acc_shape->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
   acc_shape->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.1369568,0.995,"blNDC");
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
   acc_3->Range(-10,-0.001694987,90,0.1129517);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",6, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.02512);
   acc_eff_shape_dps_pt->SetBinContent(2,0.02169781);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01518239);
   acc_eff_shape_dps_pt->SetBinContent(4,0.02253574);
   acc_eff_shape_dps_pt->SetBinContent(5,0.04468146);
   acc_eff_shape_dps_pt->SetBinContent(6,0.09239611);
   acc_eff_shape_dps_pt->SetBinError(1,0.002029818);
   acc_eff_shape_dps_pt->SetBinError(2,0.001873773);
   acc_eff_shape_dps_pt->SetBinError(3,0.001253196);
   acc_eff_shape_dps_pt->SetBinError(4,0.001477143);
   acc_eff_shape_dps_pt->SetBinError(5,0.002593812);
   acc_eff_shape_dps_pt->SetBinError(6,0.00472341);
   acc_eff_shape_dps_pt->SetEntries(1214.993);
   acc_eff_shape_dps_pt->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt->SetLineColor(ci);
   acc_eff_shape_dps_pt->SetLineWidth(2);
   acc_eff_shape_dps_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_eff_shape_dps_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.2555394,0.995,"blNDC");
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
   acc_4->Range(-10,0.03867008,90,0.3112867);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",6, xAxis4);
   acc_shape_pt->SetBinContent(1,0.09968);
   acc_shape_pt->SetBinContent(2,0.08679126);
   acc_shape_pt->SetBinContent(3,0.07876503);
   acc_shape_pt->SetBinContent(4,0.1066187);
   acc_shape_pt->SetBinContent(5,0.1594119);
   acc_shape_pt->SetBinContent(6,0.2650309);
   acc_shape_pt->SetBinContent(7,0.5);
   acc_shape_pt->SetBinError(1,0.004187908);
   acc_shape_pt->SetBinError(2,0.003865083);
   acc_shape_pt->SetBinError(3,0.002942437);
   acc_shape_pt->SetBinError(4,0.003342436);
   acc_shape_pt->SetBinError(5,0.005161336);
   acc_shape_pt->SetBinError(6,0.0086087);
   acc_shape_pt->SetBinError(7,0.2738613);
   acc_shape_pt->SetEntries(4142.855);
   acc_shape_pt->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt->SetLineColor(ci);
   acc_shape_pt->SetLineWidth(2);
   acc_shape_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_shape_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.1695089,0.995,"blNDC");
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
   acc_5->Range(-0.5625,-0.005381005,5.0625,0.1035527);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",8, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.03150486);
   acc_eff_shape_dps_dy->SetBinContent(2,0.03156422);
   acc_eff_shape_dps_dy->SetBinContent(3,0.03618522);
   acc_eff_shape_dps_dy->SetBinContent(4,0.02934039);
   acc_eff_shape_dps_dy->SetBinContent(5,0.02975724);
   acc_eff_shape_dps_dy->SetBinContent(6,0.02770331);
   acc_eff_shape_dps_dy->SetBinContent(7,0.01724138);
   acc_eff_shape_dps_dy->SetBinContent(8,0.05555556);
   acc_eff_shape_dps_dy->SetBinError(1,0.001347329);
   acc_eff_shape_dps_dy->SetBinError(2,0.00168729);
   acc_eff_shape_dps_dy->SetBinError(3,0.002397695);
   acc_eff_shape_dps_dy->SetBinError(4,0.002581188);
   acc_eff_shape_dps_dy->SetBinError(5,0.003463804);
   acc_eff_shape_dps_dy->SetBinError(6,0.005044111);
   acc_eff_shape_dps_dy->SetBinError(7,0.007776766);
   acc_eff_shape_dps_dy->SetBinError(8,0.03295395);
   acc_eff_shape_dps_dy->SetEntries(55.79263);
   acc_eff_shape_dps_dy->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_dy->SetLineColor(ci);
   acc_eff_shape_dps_dy->SetLineWidth(2);
   acc_eff_shape_dps_dy->GetXaxis()->SetTitle("Four Mu #DeltaY");
   acc_eff_shape_dps_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.2601897,0.995,"blNDC");
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
   acc_6->Range(-0.5625,0.01601735,5.0625,0.1557907);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",8, xAxis6);
   acc_shape_dy->SetBinContent(1,0.125014);
   acc_shape_dy->SetBinContent(2,0.1232841);
   acc_shape_dy->SetBinContent(3,0.1317081);
   acc_shape_dy->SetBinContent(4,0.1094198);
   acc_shape_dy->SetBinContent(5,0.0963195);
   acc_shape_dy->SetBinContent(6,0.1000894);
   acc_shape_dy->SetBinContent(7,0.04827586);
   acc_shape_dy->SetBinContent(8,0.09259259);
   acc_shape_dy->SetBinError(1,0.002802899);
   acc_shape_dy->SetBinError(2,0.003479703);
   acc_shape_dy->SetBinError(3,0.004780606);
   acc_shape_dy->SetBinError(4,0.005174913);
   acc_shape_dy->SetBinError(5,0.006430063);
   acc_shape_dy->SetBinError(6,0.009919571);
   acc_shape_dy->SetBinError(7,0.01321003);
   acc_shape_dy->SetBinError(8,0.0432833);
   acc_shape_dy->SetBinError(9,nan);
   acc_shape_dy->SetEntries(302.7692);
   acc_shape_dy->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_dy->SetLineColor(ci);
   acc_shape_dy->SetLineWidth(2);
   acc_shape_dy->GetXaxis()->SetTitle("Four Mu #DeltaY ");
   acc_shape_dy->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_dy->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.1741592,0.995,"blNDC");
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
   acc_7->Range(-0.275,-0.003995109,2.475,0.05739477);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",10, xAxis7);
   acc_eff_shape_dps_y->SetBinContent(1,0.03408015);
   acc_eff_shape_dps_y->SetBinContent(2,0.0341776);
   acc_eff_shape_dps_y->SetBinContent(3,0.04042232);
   acc_eff_shape_dps_y->SetBinContent(4,0.0388102);
   acc_eff_shape_dps_y->SetBinContent(5,0.04548826);
   acc_eff_shape_dps_y->SetBinContent(6,0.03347622);
   acc_eff_shape_dps_y->SetBinContent(7,0.03434877);
   acc_eff_shape_dps_y->SetBinContent(8,0.0270738);
   acc_eff_shape_dps_y->SetBinContent(9,0.01847124);
   acc_eff_shape_dps_y->SetBinContent(10,0.007042254);
   acc_eff_shape_dps_y->SetBinError(1,0.003334777);
   acc_eff_shape_dps_y->SetBinError(2,0.003284204);
   acc_eff_shape_dps_y->SetBinError(3,0.003561834);
   acc_eff_shape_dps_y->SetBinError(4,0.00337951);
   acc_eff_shape_dps_y->SetBinError(5,0.003428862);
   acc_eff_shape_dps_y->SetBinError(6,0.002657448);
   acc_eff_shape_dps_y->SetBinError(7,0.002349896);
   acc_eff_shape_dps_y->SetBinError(8,0.001854078);
   acc_eff_shape_dps_y->SetBinError(9,0.001680807);
   acc_eff_shape_dps_y->SetBinError(10,0.002671077);
   acc_eff_shape_dps_y->SetBinError(11,nan);
   acc_eff_shape_dps_y->SetEntries(1172.66);
   acc_eff_shape_dps_y->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_y->SetLineColor(ci);
   acc_eff_shape_dps_y->SetLineWidth(2);
   acc_eff_shape_dps_y->GetXaxis()->SetTitle("Four Mu Y");
   acc_eff_shape_dps_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_y->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.2462388,0.995,"blNDC");
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
   acc_8->Range(-0.275,0.02001456,2.475,0.1683177);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",10, xAxis8);
   acc_shape_y->SetBinContent(1,0.1394762);
   acc_shape_y->SetBinContent(2,0.1199268);
   acc_shape_y->SetBinContent(3,0.1408748);
   acc_shape_y->SetBinContent(4,0.1283286);
   acc_shape_y->SetBinContent(5,0.1364648);
   acc_shape_y->SetBinContent(6,0.1392121);
   acc_shape_y->SetBinContent(7,0.1321107);
   acc_shape_y->SetBinContent(8,0.1146001);
   acc_shape_y->SetBinContent(9,0.08514792);
   acc_shape_y->SetBinContent(10,0.0472837);
   acc_shape_y->SetBinError(1,0.007081765);
   acc_shape_y->SetBinError(2,0.006401985);
   acc_shape_y->SetBinError(3,0.00696296);
   acc_shape_y->SetBinError(4,0.006404603);
   acc_shape_y->SetBinError(5,0.006191972);
   acc_shape_y->SetBinError(6,0.005689669);
   acc_shape_y->SetBinError(7,0.004821396);
   acc_shape_y->SetBinError(8,0.003973787);
   acc_shape_y->SetBinError(9,0.003725006);
   acc_shape_y->SetBinError(10,0.007058212);
   acc_shape_y->SetBinError(11,nan);
   acc_shape_y->SetEntries(3955.284);
   acc_shape_y->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_y->SetLineColor(ci);
   acc_shape_y->SetLineWidth(2);
   acc_shape_y->GetXaxis()->SetTitle("Four Mu Y ");
   acc_shape_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_y->Draw("E1");
   
   pt = new TPaveText(0.01,0.941274,0.1602083,0.995,"blNDC");
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

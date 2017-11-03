{
//=========Macro generated from canvas: acc/acc
//=========  (Mon Jun 26 16:59:18 2017) by ROOT version5.26/00
   TCanvas *acc = new TCanvas("acc", "acc",992,47,900,867);
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
   acc_1->Range(-0.5250007,0.0005947131,66.725,0.02804051);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[9] = {6.2, 7, 9, 11, 14, 18, 25, 30, 60}; 
   
   TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",8, xAxis1);
   acc_eff_shape_dps->SetBinContent(1,0.0138663);
   acc_eff_shape_dps->SetBinContent(2,0.007297057);
   acc_eff_shape_dps->SetBinContent(3,0.006983944);
   acc_eff_shape_dps->SetBinContent(4,0.006515777);
   acc_eff_shape_dps->SetBinContent(5,0.01513188);
   acc_eff_shape_dps->SetBinContent(6,0.0212844);
   acc_eff_shape_dps->SetBinContent(7,0.02075543);
   acc_eff_shape_dps->SetBinContent(8,0.01572297);
   acc_eff_shape_dps->SetBinError(1,0.005700007);
   acc_eff_shape_dps->SetBinError(2,0.002768073);
   acc_eff_shape_dps->SetBinError(3,0.002648884);
   acc_eff_shape_dps->SetBinError(4,0.001813029);
   acc_eff_shape_dps->SetBinError(5,0.002381015);
   acc_eff_shape_dps->SetBinError(6,0.002688715);
   acc_eff_shape_dps->SetBinError(7,0.003494953);
   acc_eff_shape_dps->SetBinError(8,0.001817671);
   acc_eff_shape_dps->SetBinError(9,nan);
   acc_eff_shape_dps->SetEntries(147.6578);
   acc_eff_shape_dps->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps->SetLineColor(ci);
   acc_eff_shape_dps->SetLineWidth(2);
   acc_eff_shape_dps->GetXaxis()->SetTitle("Four Mu Mass (GeV)");
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
   acc_2->Range(-0.5250007,0.02095001,66.725,0.1043501);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[9] = {6.2, 7, 9, 11, 14, 18, 25, 30, 60}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",8, xAxis2);
   acc_shape->SetBinContent(1,0.04242565);
   acc_shape->SetBinContent(2,0.05467649);
   acc_shape->SetBinContent(3,0.05023714);
   acc_shape->SetBinContent(4,0.04889752);
   acc_shape->SetBinContent(5,0.06775292);
   acc_shape->SetBinContent(6,0.08721726);
   acc_shape->SetBinContent(7,0.06622535);
   acc_shape->SetBinContent(8,0.06673398);
   acc_shape->SetBinError(1,0.01010977);
   acc_shape->SetBinError(2,0.007753268);
   acc_shape->SetBinError(3,0.007255335);
   acc_shape->SetBinError(4,0.005070156);
   acc_shape->SetBinError(5,0.005167183);
   acc_shape->SetBinError(6,0.005615651);
   acc_shape->SetBinError(7,0.006380449);
   acc_shape->SetBinError(8,0.003837621);
   acc_shape->SetBinError(9,nan);
   acc_shape->SetEntries(1261.301);
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
   acc_3->Range(-10,-0.00740554,90,0.06664985);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[8] = {0, 7, 12, 16, 20, 25, 50, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",7, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.01602381);
   acc_eff_shape_dps_pt->SetBinContent(2,0.01095174);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01168921);
   acc_eff_shape_dps_pt->SetBinContent(4,0.02310725);
   acc_eff_shape_dps_pt->SetBinContent(5,0.04423705);
   acc_eff_shape_dps_pt->SetBinContent(6,0.03738464);
   acc_eff_shape_dps_pt->SetBinError(1,0.001877595);
   acc_eff_shape_dps_pt->SetBinError(2,0.001498482);
   acc_eff_shape_dps_pt->SetBinError(3,0.001585358);
   acc_eff_shape_dps_pt->SetBinError(4,0.003564303);
   acc_eff_shape_dps_pt->SetBinError(5,0.01010813);
   acc_eff_shape_dps_pt->SetBinError(6,0.01903852);
   acc_eff_shape_dps_pt->SetBinError(8,nan);
   acc_eff_shape_dps_pt->SetEntries(43.09103);
   acc_eff_shape_dps_pt->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt->SetLineColor(ci);
   acc_eff_shape_dps_pt->SetLineWidth(2);
   acc_eff_shape_dps_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_eff_shape_dps_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt->Draw("");
   
   pt = new TPaveText(0.01,0.9390328,0.2555394,0.995,"blNDC");
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
   acc_4->Range(-10,-0.02894417,90,0.2604975);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[8] = {0, 7, 12, 16, 20, 25, 50, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",7, xAxis4);
   acc_shape_pt->SetBinContent(1,0.06303445);
   acc_shape_pt->SetBinContent(2,0.05563422);
   acc_shape_pt->SetBinContent(3,0.05952711);
   acc_shape_pt->SetBinContent(4,0.09075836);
   acc_shape_pt->SetBinContent(5,0.1519772);
   acc_shape_pt->SetBinContent(6,0.1764764);
   acc_shape_pt->SetBinError(1,0.003809164);
   acc_shape_pt->SetBinError(2,0.003451218);
   acc_shape_pt->SetBinError(3,0.00366121);
   acc_shape_pt->SetBinError(4,0.007293693);
   acc_shape_pt->SetBinError(5,0.01967837);
   acc_shape_pt->SetBinError(6,0.04405057);
   acc_shape_pt->SetBinError(8,nan);
   acc_shape_pt->SetEntries(281.0925);
   acc_shape_pt->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   acc_shape_pt->SetLineColor(ci);
   acc_shape_pt->SetLineWidth(2);
   acc_shape_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_shape_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_shape_pt->Draw("");
   
   pt = new TPaveText(0.01,0.9390328,0.1695089,0.995,"blNDC");
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
   acc_5->Range(-0.5625,0.003863781,5.0625,0.03078765);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",8, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.01187512);
   acc_eff_shape_dps_dy->SetBinContent(2,0.01396993);
   acc_eff_shape_dps_dy->SetBinContent(3,0.01044501);
   acc_eff_shape_dps_dy->SetBinContent(4,0.02000486);
   acc_eff_shape_dps_dy->SetBinContent(5,0.02185234);
   acc_eff_shape_dps_dy->SetBinContent(6,0.0210377);
   acc_eff_shape_dps_dy->SetBinContent(7,0.02341459);
   acc_eff_shape_dps_dy->SetBinContent(8,0.009716729);
   acc_eff_shape_dps_dy->SetBinError(1,0.002298898);
   acc_eff_shape_dps_dy->SetBinError(2,0.002813435);
   acc_eff_shape_dps_dy->SetBinError(3,0.002912015);
   acc_eff_shape_dps_dy->SetBinError(4,0.003962323);
   acc_eff_shape_dps_dy->SetBinError(5,0.003904964);
   acc_eff_shape_dps_dy->SetBinError(6,0.003593231);
   acc_eff_shape_dps_dy->SetBinError(7,0.003655003);
   acc_eff_shape_dps_dy->SetBinError(8,0.001380813);
   acc_eff_shape_dps_dy->SetBinError(9,nan);
   acc_eff_shape_dps_dy->SetEntries(218.5694);
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
   acc_6->Range(-0.5625,0.04327623,5.0625,0.1020655);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",8, xAxis6);
   acc_shape_dy->SetBinContent(1,0.06044029);
   acc_shape_dy->SetBinContent(2,0.06330807);
   acc_shape_dy->SetBinContent(3,0.06574174);
   acc_shape_dy->SetBinContent(4,0.07667727);
   acc_shape_dy->SetBinContent(5,0.08596273);
   acc_shape_dy->SetBinContent(6,0.08354627);
   acc_shape_dy->SetBinContent(7,0.06900813);
   acc_shape_dy->SetBinContent(8,0.05463436);
   acc_shape_dy->SetBinError(1,0.005309377);
   acc_shape_dy->SetBinError(2,0.006133188);
   acc_shape_dy->SetBinError(3,0.007502905);
   acc_shape_dy->SetBinError(4,0.007969978);
   acc_shape_dy->SetBinError(5,0.007984294);
   acc_shape_dy->SetBinError(6,0.007376534);
   acc_shape_dy->SetBinError(7,0.006412971);
   acc_shape_dy->SetBinError(8,0.003346254);
   acc_shape_dy->SetBinError(9,nan);
   acc_shape_dy->SetEntries(1674.906);
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
   acc_7->Range(-0.225,0.003270527,2.025,0.03272641);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[10] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",9, xAxis7);
   acc_eff_shape_dps_y->SetBinContent(1,0.01210623);
   acc_eff_shape_dps_y->SetBinContent(2,0.01308504);
   acc_eff_shape_dps_y->SetBinContent(3,0.0175725);
   acc_eff_shape_dps_y->SetBinContent(4,0.02233113);
   acc_eff_shape_dps_y->SetBinContent(5,0.0201226);
   acc_eff_shape_dps_y->SetBinContent(6,0.02391319);
   acc_eff_shape_dps_y->SetBinContent(7,0.01843923);
   acc_eff_shape_dps_y->SetBinContent(8,0.01026719);
   acc_eff_shape_dps_y->SetBinContent(9,0.009959938);
   acc_eff_shape_dps_y->SetBinContent(10,0.01246155);
   acc_eff_shape_dps_y->SetBinError(1,0.001672954);
   acc_eff_shape_dps_y->SetBinError(2,0.002365468);
   acc_eff_shape_dps_y->SetBinError(3,0.003476399);
   acc_eff_shape_dps_y->SetBinError(4,0.004192833);
   acc_eff_shape_dps_y->SetBinError(5,0.00414863);
   acc_eff_shape_dps_y->SetBinError(6,0.004745504);
   acc_eff_shape_dps_y->SetBinError(7,0.003721692);
   acc_eff_shape_dps_y->SetBinError(8,0.002307569);
   acc_eff_shape_dps_y->SetBinError(9,0.002675129);
   acc_eff_shape_dps_y->SetBinError(10,0.008866378);
   acc_eff_shape_dps_y->SetEntries(211.6657);
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
   acc_8->Range(-0.225,0.02007656,2.025,0.1055221);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[10] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8}; 
   
   TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",9, xAxis8);
   acc_shape_y->SetBinContent(1,0.05942451);
   acc_shape_y->SetBinContent(2,0.06376124);
   acc_shape_y->SetBinContent(3,0.08578802);
   acc_shape_y->SetBinContent(4,0.08118201);
   acc_shape_y->SetBinContent(5,0.07871852);
   acc_shape_y->SetBinContent(6,0.08104465);
   acc_shape_y->SetBinContent(7,0.07234282);
   acc_shape_y->SetBinContent(8,0.06192989);
   acc_shape_y->SetBinContent(9,0.03694152);
   acc_shape_y->SetBinContent(10,0.0359489);
   acc_shape_y->SetBinError(1,0.003792139);
   acc_shape_y->SetBinError(2,0.005350657);
   acc_shape_y->SetBinError(3,0.007934435);
   acc_shape_y->SetBinError(4,0.008221209);
   acc_shape_y->SetBinError(5,0.008437795);
   acc_shape_y->SetBinError(6,0.008976686);
   acc_shape_y->SetBinError(7,0.007564251);
   acc_shape_y->SetBinError(8,0.005810437);
   acc_shape_y->SetBinError(9,0.00522034);
   acc_shape_y->SetBinError(10,0.01523291);
   acc_shape_y->SetEntries(1658.309);
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

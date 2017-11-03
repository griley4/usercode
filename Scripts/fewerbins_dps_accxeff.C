{
//=========Macro generated from canvas: acc/acc
//=========  (Mon Feb 20 10:18:27 2017) by ROOT version5.26/00
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
   acc_1->Range(-3.025001,-0.002295004,89.225,0.02065503);
   acc_1->SetFillColor(0);
   acc_1->SetBorderMode(0);
   acc_1->SetBorderSize(2);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   acc_1->SetFrameFillStyle(0);
   acc_1->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 80}; 
   
   TH1D *fourmu_mass_alt = new TH1D("fourmu_mass_alt","fourmu_mass_alt",9, xAxis1);
   fourmu_mass_alt->SetBinContent(1,0.004512168);
   fourmu_mass_alt->SetBinContent(2,0.005237332);
   fourmu_mass_alt->SetBinContent(3,0.004232796);
   fourmu_mass_alt->SetBinContent(4,0.006519035);
   fourmu_mass_alt->SetBinContent(5,0.01182224);
   fourmu_mass_alt->SetBinContent(6,0.01551388);
   fourmu_mass_alt->SetBinContent(7,0.01087612);
   fourmu_mass_alt->SetBinContent(8,0.006657566);
   fourmu_mass_alt->SetBinContent(9,0.01604464);
   fourmu_mass_alt->SetBinError(1,0.001010145);
   fourmu_mass_alt->SetBinError(2,0.0007732624);
   fourmu_mass_alt->SetBinError(3,0.0006617851);
   fourmu_mass_alt->SetBinError(4,0.0007255745);
   fourmu_mass_alt->SetBinError(5,0.001216691);
   fourmu_mass_alt->SetBinError(6,0.001440083);
   fourmu_mass_alt->SetBinError(7,0.001342571);
   fourmu_mass_alt->SetBinError(8,0.0004800581);
   fourmu_mass_alt->SetBinError(9,0.001441102);
   fourmu_mass_alt->SetMinimum(0);
   fourmu_mass_alt->SetEntries(646.8975);
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
   acc_2->Range(-3.025001,0.01961001,89.225,0.1009414);
   acc_2->SetFillColor(0);
   acc_2->SetBorderMode(0);
   acc_2->SetBorderSize(2);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   acc_2->SetFrameFillStyle(0);
   acc_2->SetFrameBorderMode(0);
   Double_t xAxis2[10] = {6.2, 7, 9, 11, 14, 18, 25, 30, 45, 80}; 
   
   TH1D *acc_shape = new TH1D("acc_shape","acc_shape",9, xAxis2);
   acc_shape->SetBinContent(1,0.03348827);
   acc_shape->SetBinContent(2,0.03935398);
   acc_shape->SetBinContent(3,0.03633432);
   acc_shape->SetBinContent(4,0.04820759);
   acc_shape->SetBinContent(5,0.07173398);
   acc_shape->SetBinContent(6,0.07441654);
   acc_shape->SetBinContent(7,0.04684684);
   acc_shape->SetBinContent(8,0.04478003);
   acc_shape->SetBinContent(9,0.08624225);
   acc_shape->SetBinError(1,0.002794324);
   acc_shape->SetBinError(2,0.002158004);
   acc_shape->SetBinError(3,0.001971652);
   acc_shape->SetBinError(4,0.00201665);
   acc_shape->SetBinError(5,0.003093101);
   acc_shape->SetBinError(6,0.00325603);
   acc_shape->SetBinError(7,0.002842803);
   acc_shape->SetBinError(8,0.00127038);
   acc_shape->SetBinError(9,0.003467635);
   acc_shape->SetBinError(10,nan);
   acc_shape->SetEntries(7091.24);
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
   acc_3->Range(-10,-0.003829682,90,0.06150733);
   acc_3->SetFillColor(0);
   acc_3->SetBorderMode(0);
   acc_3->SetBorderSize(2);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   acc_3->SetFrameFillStyle(0);
   acc_3->SetFrameBorderMode(0);
   Double_t xAxis3[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",6, xAxis3);
   acc_eff_shape_dps_pt->SetBinContent(1,0.00547208);
   acc_eff_shape_dps_pt->SetBinContent(2,0.005942975);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01422075);
   acc_eff_shape_dps_pt->SetBinContent(4,0.02905163);
   acc_eff_shape_dps_pt->SetBinContent(5,0.0450849);
   acc_eff_shape_dps_pt->SetBinContent(6,0.03631651);
   acc_eff_shape_dps_pt->SetBinError(1,0.0003975557);
   acc_eff_shape_dps_pt->SetBinError(2,0.0003866389);
   acc_eff_shape_dps_pt->SetBinError(3,0.0009944951);
   acc_eff_shape_dps_pt->SetBinError(4,0.002856667);
   acc_eff_shape_dps_pt->SetBinError(5,0.007399703);
   acc_eff_shape_dps_pt->SetBinError(6,0.01296153);
   acc_eff_shape_dps_pt->SetEntries(79.75476);
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
   acc_4->Range(-10,0.007800379,90,0.2509103);
   acc_4->SetFillColor(0);
   acc_4->SetBorderMode(0);
   acc_4->SetBorderSize(2);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   acc_4->SetFrameFillStyle(0);
   acc_4->SetFrameBorderMode(0);
   Double_t xAxis4[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",6, xAxis4);
   acc_shape_pt->SetBinContent(1,0.04205514);
   acc_shape_pt->SetBinContent(2,0.04366612);
   acc_shape_pt->SetBinContent(3,0.07317668);
   acc_shape_pt->SetBinContent(4,0.1105827);
   acc_shape_pt->SetBinContent(5,0.1599306);
   acc_shape_pt->SetBinContent(6,0.1857204);
   acc_shape_pt->SetBinError(1,0.001123451);
   acc_shape_pt->SetBinError(2,0.001069008);
   acc_shape_pt->SetBinError(3,0.002328358);
   acc_shape_pt->SetBinError(4,0.005829208);
   acc_shape_pt->SetBinError(5,0.01483562);
   acc_shape_pt->SetBinError(6,0.03161754);
   acc_shape_pt->SetBinError(7,nan);
   acc_shape_pt->SetEntries(571.8419);
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
   acc_5->Range(-0.5625,0.002992821,5.0625,0.01945777);
   acc_5->SetFillColor(0);
   acc_5->SetBorderMode(0);
   acc_5->SetBorderSize(2);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   acc_5->SetFrameFillStyle(0);
   acc_5->SetFrameBorderMode(0);
   Double_t xAxis5[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",8, xAxis5);
   acc_eff_shape_dps_dy->SetBinContent(1,0.005870714);
   acc_eff_shape_dps_dy->SetBinContent(2,0.007500112);
   acc_eff_shape_dps_dy->SetBinContent(3,0.007700724);
   acc_eff_shape_dps_dy->SetBinContent(4,0.01043607);
   acc_eff_shape_dps_dy->SetBinContent(5,0.01419795);
   acc_eff_shape_dps_dy->SetBinContent(6,0.0144408);
   acc_eff_shape_dps_dy->SetBinContent(7,0.01547821);
   acc_eff_shape_dps_dy->SetBinContent(8,0.007100947);
   acc_eff_shape_dps_dy->SetBinError(1,0.0006340292);
   acc_eff_shape_dps_dy->SetBinError(2,0.0008150998);
   acc_eff_shape_dps_dy->SetBinError(3,0.001031129);
   acc_eff_shape_dps_dy->SetBinError(4,0.001362374);
   acc_eff_shape_dps_dy->SetBinError(5,0.001855286);
   acc_eff_shape_dps_dy->SetBinError(6,0.001770893);
   acc_eff_shape_dps_dy->SetBinError(7,0.001705836);
   acc_eff_shape_dps_dy->SetBinError(8,0.0004184799);
   acc_eff_shape_dps_dy->SetEntries(501.3996);
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
   acc_6->Range(-0.5625,0.03884712,5.0625,0.0792205);
   acc_6->SetFillColor(0);
   acc_6->SetBorderMode(0);
   acc_6->SetBorderSize(2);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   acc_6->SetFrameFillStyle(0);
   acc_6->SetFrameBorderMode(0);
   Double_t xAxis6[9] = {0, 0.2, 0.4, 0.6, 0.9, 1.3, 1.8, 2.4, 4.5}; 
   
   TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",8, xAxis6);
   acc_shape_dy->SetBinContent(1,0.04787126);
   acc_shape_dy->SetBinContent(2,0.04641953);
   acc_shape_dy->SetBinContent(3,0.04983937);
   acc_shape_dy->SetBinContent(4,0.06021166);
   acc_shape_dy->SetBinContent(5,0.06740094);
   acc_shape_dy->SetBinContent(6,0.0696383);
   acc_shape_dy->SetBinContent(7,0.06162176);
   acc_shape_dy->SetBinContent(8,0.04848286);
   acc_shape_dy->SetBinError(1,0.001850494);
   acc_shape_dy->SetBinError(2,0.002070273);
   acc_shape_dy->SetBinError(3,0.002682375);
   acc_shape_dy->SetBinError(4,0.003360308);
   acc_shape_dy->SetBinError(5,0.004160865);
   acc_shape_dy->SetBinError(6,0.004006829);
   acc_shape_dy->SetBinError(7,0.003492796);
   acc_shape_dy->SetBinError(8,0.001117594);
   acc_shape_dy->SetBinError(9,nan);
   acc_shape_dy->SetEntries(5322.749);
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
   acc_7->Range(-0.275,0.002394734,2.475,0.02063522);
   acc_7->SetFillColor(0);
   acc_7->SetBorderMode(0);
   acc_7->SetBorderSize(2);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   acc_7->SetFrameFillStyle(0);
   acc_7->SetFrameBorderMode(0);
   Double_t xAxis7[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",10, xAxis7);
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
   acc_8->Range(-0.275,0.03375756,2.475,0.08317406);
   acc_8->SetFillColor(0);
   acc_8->SetBorderMode(0);
   acc_8->SetBorderSize(2);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   acc_8->SetFrameFillStyle(0);
   acc_8->SetFrameBorderMode(0);
   Double_t xAxis8[11] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2.2}; 
   
   TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",10, xAxis8);
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

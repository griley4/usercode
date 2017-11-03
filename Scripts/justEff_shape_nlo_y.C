{
//========= Macro generated from object: acc_eff_shape_dps_y/acc_eff_shape_dps_y
//========= by ROOT version5.26/00
   Double_t xAxis2[10] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",9, xAxis2);
   acc_eff_shape_dps_y->SetBinContent(1,0.260205);
   acc_eff_shape_dps_y->SetBinContent(2,0.303487);
   acc_eff_shape_dps_y->SetBinContent(3,0.305564);
   acc_eff_shape_dps_y->SetBinContent(4,0.32206);
   acc_eff_shape_dps_y->SetBinContent(5,0.354971);
   acc_eff_shape_dps_y->SetBinContent(6,0.256079);
   acc_eff_shape_dps_y->SetBinContent(7,0.276877);
   acc_eff_shape_dps_y->SetBinContent(8,0.251581);
   acc_eff_shape_dps_y->SetBinContent(9,0.231013);
   acc_eff_shape_dps_y->SetBinContent(10,0.158604);
   acc_eff_shape_dps_y->SetBinError(1,0.0289058);
   acc_eff_shape_dps_y->SetBinError(2,0.0336422);
   acc_eff_shape_dps_y->SetBinError(3,0.0311398);
   acc_eff_shape_dps_y->SetBinError(4,0.0326115);
   acc_eff_shape_dps_y->SetBinError(5,0.0315316);
   acc_eff_shape_dps_y->SetBinError(6,0.0230382);
   acc_eff_shape_dps_y->SetBinError(7,0.0216403);
   acc_eff_shape_dps_y->SetBinError(8,0.0194521);
   acc_eff_shape_dps_y->SetBinError(9,0.0234772);
   acc_eff_shape_dps_y->SetBinError(10,0.064942);
   acc_eff_shape_dps_y->SetEntries(947.945);
   acc_eff_shape_dps_y->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_y->SetLineColor(ci);
   acc_eff_shape_dps_y->SetLineWidth(2);
   acc_eff_shape_dps_y->GetXaxis()->SetTitle("Four Mu Y");
   acc_eff_shape_dps_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_y->Draw("");
}

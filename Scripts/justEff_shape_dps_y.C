{
//========= Macro generated from object: acc_eff_shape_dps_y/acc_eff_shape_dps_y
//========= by ROOT version5.26/00
   Double_t xAxis2[10] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8}; 
   
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",9, xAxis2);
   acc_eff_shape_dps_y->SetBinContent(1,0.204274);
   acc_eff_shape_dps_y->SetBinContent(2,0.207857);
   acc_eff_shape_dps_y->SetBinContent(3,0.212748);
   acc_eff_shape_dps_y->SetBinContent(4,0.279243);
   acc_eff_shape_dps_y->SetBinContent(5,0.247744);
   acc_eff_shape_dps_y->SetBinContent(6,0.311763);
   acc_eff_shape_dps_y->SetBinContent(7,0.267774);
   acc_eff_shape_dps_y->SetBinContent(8,0.191568);
   acc_eff_shape_dps_y->SetBinContent(9,0.256651);
   acc_eff_shape_dps_y->SetBinContent(10,0.317759);
   acc_eff_shape_dps_y->SetBinError(1,0.031709);
   acc_eff_shape_dps_y->SetBinError(2,0.0428964);
   acc_eff_shape_dps_y->SetBinError(3,0.0466401);
   acc_eff_shape_dps_y->SetBinError(4,0.0596931);
   acc_eff_shape_dps_y->SetBinError(5,0.0586324);
   acc_eff_shape_dps_y->SetBinError(6,0.0713512);
   acc_eff_shape_dps_y->SetBinError(7,0.0613041);
   acc_eff_shape_dps_y->SetBinError(8,0.0461049);
   acc_eff_shape_dps_y->SetBinError(9,0.077447);
   acc_eff_shape_dps_y->SetBinError(10,0.259923);
   acc_eff_shape_dps_y->SetEntries(163.849);
   acc_eff_shape_dps_y->SetStats(0);

   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_y->SetLineColor(ci);
   acc_eff_shape_dps_y->SetLineWidth(2);
   acc_eff_shape_dps_y->GetXaxis()->SetTitle("Four Mu Y");
   acc_eff_shape_dps_y->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_y->Draw("");
}

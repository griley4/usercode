{
//========= Macro generated from object: acc_eff_shape_dps_pt/acc_eff_shape_dps_pt
//========= by ROOT version5.26/00
   Double_t xAxis1[7] = {0, 7, 12, 16, 20, 25, 80}; 
   
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",6, xAxis1);
   acc_eff_shape_dps_pt->SetBinContent(1,0.256159);
   acc_eff_shape_dps_pt->SetBinContent(2,0.203724);
   acc_eff_shape_dps_pt->SetBinContent(3,0.213085);
   acc_eff_shape_dps_pt->SetBinContent(4,0.246589);
   acc_eff_shape_dps_pt->SetBinContent(5,0.303315);
   acc_eff_shape_dps_pt->SetBinContent(6,0.211839);
   acc_eff_shape_dps_pt->SetBinError(1,0.034651);
   acc_eff_shape_dps_pt->SetBinError(2,0.0309217);
   acc_eff_shape_dps_pt->SetBinError(3,0.031339);
   acc_eff_shape_dps_pt->SetBinError(4,0.0435914);
   acc_eff_shape_dps_pt->SetBinError(5,0.077624);
   acc_eff_shape_dps_pt->SetBinError(6,0.119324);
   acc_eff_shape_dps_pt->SetEntries(81.3506);
   acc_eff_shape_dps_pt->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#00ff00");
   acc_eff_shape_dps_pt->SetLineColor(ci);
   acc_eff_shape_dps_pt->SetLineWidth(2);
   acc_eff_shape_dps_pt->GetXaxis()->SetTitle("Four Mu pT (GeV)");
   acc_eff_shape_dps_pt->GetYaxis()->SetTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
   acc_eff_shape_dps_pt->Draw("");
}

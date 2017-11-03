{

  float dpbins[]={0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.,2.25,2.5,2.75,3.142};
  int ndpbins = 12;

  TH1D *delta_phi = new TH1D("delta_phi","delta_phi",ndpbins,dpbins);
  delta_phi->SetXTitle("Four Mu #Delta#phi");
  delta_phi->SetYTitle("Events");
  delta_phi->SetLineWidth(2);
  delta_phi->Sumw2();
  delta_phi->SetMinimum(0);
  delta_phi->Draw();
}

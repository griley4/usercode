
void readValues(){

  TFile *f = new TFile("L1L2Eff_final.root");
 // TDirectory *d = (TDirectory*)f->Get("tpTree/BMuQualSoft_pt_eta_Mu5_Track2/fit_eff_plots");
 // if(!d) std::cout << "directory not available" << std::endl;
  int N = 0;
  //string name;
  //name.Format("gEff_DATA_PT_AETA%i",N);
  TGraph *g = (TGraph*)f->Get("gEff_DATA_PT_AETA0");
  if(!g)std::cout << "TGraph is sunbathing." << std::endl;

  int n = g->GetN();
  std::cout << n << " points in graph" << std::endl;
  const char title = g->GetTitle();
  //const char savename = "Effplots/"+title+".C";  
  //std::cout<<savename<<std::endl;
  g->SaveAs("grph");

  // put loop over points here
 // for(int i = 0; i < n; i++){
    // check which bin the pt is in

 // } //iPT
  f->Close();
}

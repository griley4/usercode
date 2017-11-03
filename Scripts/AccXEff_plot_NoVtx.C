{
//float massbins[]={6.2,6.5,7,8.5,11,14,18,24,30,45,80};
//float ptbins[]={0,4,8,12,15,18,22,26,30,80};
//float dybins[]={0,0.1,0.2,0.3,0.45,0.6,0.9,1.3,1.8,2.4,4.5};
//float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
//int nmbins = 10; 
//int nptbins = 9;
//int ndybins = 10;
//int nybins = 10;
  float massbins[]={6.2,7,9,11,14,18,25,30,60};
  float massbins2[]={0,6.2,7,9,11,14,18,25,30,60};
  float ptbins[]={0,7,12,16,20,25,50,80};
  float dybins[]={0,0.2,0.4,0.6,0.9,1.3,1.8,2.4,4.5};
  //float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8};
  int nmbins = 8;
  int nmbins2 = 9;
  int nptbins = 7;
  int ndybins = 8;
  int nybins = 9;
int gendps_tot, gendps_acc, recodps_tot, genspslo_tot, recospslo_tot, genspsnlo_tot, recospsnlo_tot; 
Double_t err_frac_reco[80], err_frac_gen[80], acc_eff_frac[80];
//Double_t err_frac_reco[7], err_frac_gen[7], acc_eff_frac[7];
  TChain gendps("Events");
  TChain recodps("PATEventTree");
  TChain recospslo("PATEventTree");
  TChain recospsnlo("PATEventTree");
//SPSNLOgg
  //gendps.Add("genevents/GENEventTree_spsnlogg_xl1.root");
  //gendps.Add("genevents/GENEventTree_spsnlogg_xl2.root");
  //gendps.Add("genevents/GENEventTree_spsnlogg_xl3.root");
  //gendps.Add("genevents/GENEventTree_spsnlogg_xl4.root");
  //gendps.Add("genevents/GENEventTree_spsnlogg_xl5.root");
  //gendps.Add("genevents/GENEventTree_spsnlogg_xl6.root");
  //recodps.Add("Modified_Input_To_Fit_2012SPSNLOpy8_gg_TMTight_3MuL3Match.root");
  //float genscale = 118975./119415.;
  //float accscale = 19026./19098;
//real offset BS nlogg
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_1.root");
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_2.root");
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_3.root");
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_4.root");
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_5.root");
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_6_1.root");
  //gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_6_2.root");
  //recodps.Add("Modified_Input_To_Fit_2012SPSNLO_gg_TMTight_MuL3Match_PU_OffsetBS.root");
  //float genscale = 87654./93346.;
  //float accscale = 9767./10401.;
//DPS
  //gendps.Add("genevents/GENEventTree_dps_001.root");
  //gendps.Add("genevents/GENEventTree_dps_003.root");
  //gendps.Add("genevents/GENEventTree_dps_001Part2_small_2.root");
  //gendps.Add("genevents/GENEventTree_dps_001Part2_small_1.root");
  //recodps.Add("Modified_Input_To_Fit_2012DPS_GENTupleOnly_TMTight_MuL3Match.root");
  //float genscale = 60743./ ; //this scale is only for whole gentuple sample size
  //float accscale = 1. ; //this scale is only for whole gentuple sample size
//old DPS PU and FD
   gendps.Add("genevents/GENEventTree_dps_pu_old_1.root");
   gendps.Add("genevents/GENEventTree_dps_pu_old_2.root");
   gendps.Add("genevents/GENEventTree_dps_pu_old_3.root");
   recodps.Add("Modified_Input_To_Fit_2012DPS_PUold_TMTight_3MuL3MatchPv.root"); 
   float genscale = 93764./178772.;
   float accscale = 4837./9222.;
// -- acceptance x efficiency shape
  // -- 4-mu mass
  //TH1D *fourmu_mass = new TH1D("fourmu_mass","fourmu_mass",80,0,80);
  TH1D *fourmu_mass = new TH1D("fourmu_mass","fourmu_mass",nmbins,massbins);
  fourmu_mass->SetXTitle("Four Mu Mass (GeV)");
  fourmu_mass->SetYTitle("Events");
  fourmu_mass->SetLineWidth(2);
  fourmu_mass->Sumw2();
  fourmu_mass->SetMinimum(0);

  //TH1D *fourmu_mass_alt = new TH1D("fourmu_mass_alt","fourmu_mass_alt",80,0,80);
  TH1D *fourmu_mass_alt = new TH1D("fourmu_mass_alt","fourmu_mass_alt",nmbins,massbins);
  fourmu_mass_alt->SetXTitle("Four Mu Mass (GeV)");
  fourmu_mass_alt->SetYTitle("Events");
  fourmu_mass_alt->SetLineWidth(2);
  fourmu_mass_alt->Sumw2();
  fourmu_mass_alt->SetMinimum(0);

  //TH1D *fourmu_mass_alt2 = new TH1D("fourmu_mass_alt2","fourmu_mass_alt2",80,0,80);
  TH1D *fourmu_mass_alt2 = new TH1D("fourmu_mass_alt2","fourmu_mass_alt2",nmbins,massbins);
  fourmu_mass_alt2->SetXTitle("Four Mu Mass (GeV)");
  fourmu_mass_alt2->SetYTitle("Events");
  fourmu_mass_alt2->SetLineWidth(2);
  fourmu_mass_alt2->Sumw2();
  fourmu_mass_alt2->SetMinimum(0);

  //TH1D *acc_shape = new TH1D("acc_shape","acc_shape",80,0,80);
  TH1D *acc_shape = new TH1D("acc_shape","acc_shape",nmbins,massbins);
  acc_shape->SetXTitle("Four Mu Mass (GeV)");
  acc_shape->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape->SetMinimum(0);
  acc_shape->SetLineColor(kBlue);
  acc_shape->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",80,0,80);
  TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",nmbins,massbins);
  acc_eff_shape_dps->SetXTitle("Four Mu Mass (GeV)");
  acc_eff_shape_dps->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps->SetMinimum(0);
  acc_eff_shape_dps->SetLineColor(kGreen);
  acc_eff_shape_dps->SetLineWidth(2);
  
  TCanvas* disp = new TCanvas("c","c", 1800,1800);
  TCanvas* acc = new TCanvas("acc","acc", 900,900);
  acc.Divide(2,4);
  disp.Divide(3,4);


  disp->cd(1);
  gendps_tot = gendps.Draw("FourMu_Mass >> fourmu_mass","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  fourmu_mass.Scale(genscale);
  disp->cd(2);
  gendps_acc = gendps.Draw("FourMu_Mass >> fourmu_mass_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  fourmu_mass_alt2.Scale(accscale);
  disp->cd(3);
  recodps_tot = recodps.Draw("FourMu_Mass >> fourmu_mass_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps->Add(fourmu_mass_alt);
  acc_eff_shape_dps->Divide(fourmu_mass);
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_mass->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_mass_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<80; ibin++) acc_eff_shape_dps->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(1);
  acc_eff_shape_dps->Draw("E1");
  
  acc_shape->Add(fourmu_mass_alt2);
  acc_shape->Divide(fourmu_mass);
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_mass->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_mass_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) acc_eff_frac[ibin] = acc_shape->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<80; ibin++) acc_shape->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(2);
  acc_shape->Draw("E1");
  std::cout<<"M: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
//pT dists

  //TH1D *fourmu_pt = new TH1D("fourmu_pt","fourmu_pt",40,0,40);
  TH1D *fourmu_pt = new TH1D("fourmu_pt","fourmu_pt",nptbins,ptbins);
  fourmu_pt->SetXTitle("Four Mu pT (GeV)");
  fourmu_pt->SetYTitle("Events");
  fourmu_pt->SetLineWidth(2);
  fourmu_pt->Sumw2();
  fourmu_pt->SetMinimum(0);

  //TH1D *fourmu_pt_alt = new TH1D("fourmu_pt_alt","fourmu_pt_alt",40,0,40);
  TH1D *fourmu_pt_alt = new TH1D("fourmu_pt_alt","fourmu_pt_alt",nptbins,ptbins);
  fourmu_pt_alt->SetXTitle("Four Mu pT (GeV)");
  fourmu_pt_alt->SetYTitle("Events");
  fourmu_pt_alt->SetLineWidth(2);
  fourmu_pt_alt->Sumw2();
  fourmu_pt_alt->SetMinimum(0);

  //TH1D *fourmu_pt_alt2 = new TH1D("fourmu_pt_alt2","fourmu_pt_alt2",40,0,40);
  TH1D *fourmu_pt_alt2 = new TH1D("fourmu_pt_alt2","fourmu_pt_alt2",nptbins,ptbins);
  fourmu_pt_alt2->SetXTitle("Four Mu pT (GeV)");
  fourmu_pt_alt2->SetYTitle("Events");
  fourmu_pt_alt2->SetLineWidth(2);
  fourmu_pt_alt2->Sumw2();
  fourmu_pt_alt2->SetMinimum(0);

  //TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",40,0,40);
  TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",nptbins,ptbins);
  acc_shape_pt->SetXTitle("Four Mu pT (GeV)");
  acc_shape_pt->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape_pt->SetMinimum(0);
  acc_shape_pt->SetLineColor(kBlue);
  acc_shape_pt->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",40,0,40);
  TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",nptbins,ptbins);
  acc_eff_shape_dps_pt->SetXTitle("Four Mu pT (GeV)");
  acc_eff_shape_dps_pt->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps_pt->SetMinimum(0);
  acc_eff_shape_dps_pt->SetLineColor(kGreen);
  acc_eff_shape_dps_pt->SetLineWidth(2);
  
  disp->cd(4);

    gendps_tot = gendps.Draw("FourMu_pT >> fourmu_pt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  fourmu_pt.Scale(genscale);
  disp->cd(5);
    gendps_acc = gendps.Draw("FourMu_pT >> fourmu_pt_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  fourmu_pt_alt2.Scale(accscale);
  disp->cd(6);
    recodps_tot = recodps.Draw("FourMu_pT >> fourmu_pt_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps_pt->Add(fourmu_pt_alt);
  acc_eff_shape_dps_pt->Divide(fourmu_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_pt_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps_pt->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_shape_dps_pt->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(3);
  acc_eff_shape_dps_pt->Draw("E1");

  acc_shape_pt->Add(fourmu_pt_alt2);
  acc_shape_pt->Divide(fourmu_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_pt_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_shape_pt->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_shape_pt->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(4);
  acc_shape_pt->Draw("E1");
  std::cout<<"pT: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
  
  //dy dists

  //TH1D *fourmu_dy = new TH1D("fourmu_dy","fourmu_dy",45,0,4.5);
  TH1D *fourmu_dy = new TH1D("fourmu_dy","fourmu_dy",ndybins,dybins);
  fourmu_dy->SetXTitle("Four Mu #DeltaY");
  fourmu_dy->SetYTitle("Events");
  fourmu_dy->SetLineWidth(2);
  fourmu_dy->Sumw2();
  fourmu_dy->SetMinimum(0);

  //TH1D *fourmu_dy_alt = new TH1D("fourmu_dy_alt","fourmu_dy_alt",45,0,4.5);
  TH1D *fourmu_dy_alt = new TH1D("fourmu_dy_alt","fourmu_dy_alt",ndybins,dybins);
  fourmu_dy_alt->SetXTitle("Four Mu #DeltaY");
  fourmu_dy_alt->SetYTitle("Events");
  fourmu_dy_alt->SetLineWidth(2);
  fourmu_dy_alt->Sumw2();
  fourmu_dy_alt->SetMinimum(0);

  //TH1D *fourmu_dy_alt2 = new TH1D("fourmu_dy_alt2","fourmu_dy_alt2",45,0,4.5);
  TH1D *fourmu_dy_alt2 = new TH1D("fourmu_dy_alt2","fourmu_dy_alt2",ndybins,dybins);
  fourmu_dy_alt2->SetXTitle("Four Mu #DeltaY");
  fourmu_dy_alt2->SetYTitle("Events");
  fourmu_dy_alt2->SetLineWidth(2);
  fourmu_dy_alt2->Sumw2();
  fourmu_dy_alt2->SetMinimum(0);

  //TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",45,0,4.5);
  TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",ndybins,dybins);
  acc_shape_dy->SetXTitle("Four Mu #DeltaY ");
  acc_shape_dy->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape_dy->SetMinimum(0);
  acc_shape_dy->SetLineColor(kBlue);
  acc_shape_dy->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",45,0,4.5);
  TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",ndybins,dybins);
  acc_eff_shape_dps_dy->SetXTitle("Four Mu #DeltaY");
  acc_eff_shape_dps_dy->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps_dy->SetMinimum(0);
  acc_eff_shape_dps_dy->SetLineColor(kGreen);
  acc_eff_shape_dps_dy->SetLineWidth(2);
  
  disp->cd(7);

    gendps_tot = gendps.Draw("Psi1To2_dY >> fourmu_dy","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  fourmu_dy.Scale(genscale);
  disp->cd(8);
    gendps_acc = gendps.Draw("Psi1To2_dY >> fourmu_dy_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  fourmu_dy_alt2.Scale(accscale);
  disp->cd(9);
  recodps_tot = recodps.Draw("Psi1To2_dY >> fourmu_dy_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps_dy->Add(fourmu_dy_alt);
  acc_eff_shape_dps_dy->Divide(fourmu_dy);
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_dy->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_dy_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps_dy->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<42; ibin++) acc_eff_shape_dps_dy->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(5);
  acc_eff_shape_dps_dy->Draw("E1");

  acc_shape_dy->Add(fourmu_dy_alt2);
  acc_shape_dy->Divide(fourmu_dy);
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_dy->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_dy_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) acc_eff_frac[ibin] = acc_shape_dy->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<42; ibin++) acc_shape_dy->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(6);
  acc_shape_dy->Draw("E1");
  std::cout<<"dY: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
  //y dists

  //TH1D *fourmu_y = new TH1D("fourmu_dy","fourmu_dy",45,0,4.5);
  TH1D *fourmu_y = new TH1D("fourmu_y","fourmu_y",nybins,ybins);
  fourmu_y->SetXTitle("Four Mu Y");
  fourmu_y->SetYTitle("Events");
  fourmu_y->SetLineWidth(2);
  fourmu_y->Sumw2();
  fourmu_y->SetMinimum(0);

  //TH1D *fourmu_dy_alt = new TH1D("fourmu_dy_alt","fourmu_dy_alt",45,0,4.5);
  TH1D *fourmu_y_alt = new TH1D("fourmu_y_alt","fourmu_y_alt",nybins,ybins);
  fourmu_y_alt->SetXTitle("Four Mu Y");
  fourmu_y_alt->SetYTitle("Events");
  fourmu_y_alt->SetLineWidth(2);
  fourmu_y_alt->Sumw2();
  fourmu_y_alt->SetMinimum(0);

  //TH1D *fourmu_dy_alt2 = new TH1D("fourmu_dy_alt2","fourmu_dy_alt2",45,0,4.5);
  TH1D *fourmu_y_alt2 = new TH1D("fourmu_y_alt2","fourmu_y_alt2",nybins,ybins);
  fourmu_y_alt2->SetXTitle("Four Mu Y");
  fourmu_y_alt2->SetYTitle("Events");
  fourmu_y_alt2->SetLineWidth(2);
  fourmu_y_alt2->Sumw2();
  fourmu_y_alt2->SetMinimum(0);

  //TH1D *acc_shape_dy = new TH1D("acc_shape_dy","acc_shape_dy",45,0,4.5);
  TH1D *acc_shape_y = new TH1D("acc_shape_y","acc_shape_y",nybins,ybins);
  acc_shape_y->SetXTitle("Four Mu Y ");
  acc_shape_y->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape_y->SetMinimum(0);
  acc_shape_y->SetLineColor(kBlue);
  acc_shape_y->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",45,0,4.5);
  TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",nybins,ybins);
  acc_eff_shape_dps_y->SetXTitle("Four Mu Y");
  acc_eff_shape_dps_y->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps_y->SetMinimum(0);
  acc_eff_shape_dps_y->SetLineColor(kGreen);
  acc_eff_shape_dps_y->SetLineWidth(2);
  
  disp->cd(10);

    gendps_tot = gendps.Draw("abs(FourMu_Rapidity) >> fourmu_y","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  fourmu_y.Scale(genscale);
  disp->cd(11);
    gendps_acc = gendps.Draw("abs(FourMu_Rapidity) >> fourmu_y_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  fourmu_y_alt2.Scale(accscale);
  disp->cd(12);
   recodps_tot = recodps.Draw("abs(FourMu_Rapidity) >> fourmu_y_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps_y->Add(fourmu_y_alt);
  acc_eff_shape_dps_y->Divide(fourmu_y);
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_y->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_y_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps_y->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<42; ibin++) acc_eff_shape_dps_y->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(7);
  acc_eff_shape_dps_y->Draw("E1");

  acc_shape_y->Add(fourmu_y_alt2);
  acc_shape_y->Divide(fourmu_y);
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_gen[ibin] = 1.0/sqrt(fourmu_y->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) err_frac_reco[ibin] = 1.0/sqrt(fourmu_y_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<42; ibin++) acc_eff_frac[ibin] = acc_shape_y->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<42; ibin++) acc_shape_y->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(8);
  acc_shape_y->Draw("E1");
  disp.Draw();
  acc.Draw();
  std::cout<<"Y: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
  std::cout<<"Gen_tot : "<<gendps_tot<<" Gen_acc : "<<gendps_acc<<" Reco_tot : "<<recodps_tot<<std::endl;
}

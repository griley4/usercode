{
//float massbins[]={6.2,6.5,7,8.5,11,14,18,24,30,45,80};
//float ptbins[]={0,4,8,12,15,18,22,26,30,80};
//float dybins[]={0,0.1,0.2,0.3,0.45,0.6,0.9,1.3,1.8,2.4,4.5};
//float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
//int nmbins = 10; 
//int nptbins = 9;
//int ndybins = 10;
//int nybins = 10;
//float dpbins[]={0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.,2.25,2.5,2.75,3.142};
 float dpbins[]={0,0.25,1.0,1.75,2.5,3.142}; 
  float pt1bins[]={0,5,10,12,14,17,20,25,60};
  float pt2bins[]={0,5,8,10,12,15,20,40};
  float ptabins[]={0,0.05,0.125,0.2,0.35,1.};
  int ndpbins = 5;
  int npt1bins = 8;
  int npt2bins = 7;
  int nptabins = 5;
//int gendps_tot, gendps_acc, recodps_tot, genspslo_tot, recospslo_tot, genspsnlo_tot, recospsnlo_tot; 
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
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_1.root");
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_2.root");
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_3.root");
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_4.root");
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_5.root");
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_6_1.root");
  gendps.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_6_2.root");
  recodps.Add("Modified_Input_To_Fit_2012SPSNLO_gg_TMTight_MuL3Match_PU_OffsetBS.root");
  float genscale = 87654./93346.;
  float accscale = 9767./10401.;
//DPS
  //gendps.Add("genevents/GENEventTree_dps_001.root");
  //gendps.Add("genevents/GENEventTree_dps_003.root");
  //gendps.Add("genevents/GENEventTree_dps_001Part2_small_2.root");
  //gendps.Add("genevents/GENEventTree_dps_001Part2_small_1.root");
  //recodps.Add("Modified_Input_To_Fit_2012DPS_GENTupleOnly_TMTight_MuL3Match.root");
  //float genscale = 60743. ; //this scale is only for whole gentuple sample size
  //float accscale = 1. ; //this scale is only for whole gentuple sample size
//old DPS PU and FD
   //gendps.Add("genevents/GENEventTree_dps_pu_old_1.root");
   //gendps.Add("genevents/GENEventTree_dps_pu_old_2.root");
   //gendps.Add("genevents/GENEventTree_dps_pu_old_3.root");
   //recodps.Add("Modified_Input_To_Fit_2012DPS_PUold_TMTight_3MuL3MatchPv.root"); 
   //float genscale = 93764./178772.;
   //float accscale = 4837./9222.;
// -- acceptance x efficiency shape
  // -- 4-mu mass
  //TH1D *fourmu_mass = new TH1D("fourmu_mass","fourmu_mass",80,0,80);
  TH1D *delta_phi = new TH1D("delta_phi","delta_phi",ndpbins,dpbins);
  delta_phi->SetXTitle("Four Mu #Delta#phi");
  delta_phi->SetYTitle("Events");
  delta_phi->SetLineWidth(2);
  delta_phi->Sumw2();
  delta_phi->SetMinimum(0);

  //TH1D *fourmu_mass_alt = new TH1D("fourmu_mass_alt","fourmu_mass_alt",80,0,80);
  TH1D *delta_phi_alt = new TH1D("delta_phi_alt","delta_phi_alt",ndpbins,dpbins);
  delta_phi_alt->SetXTitle("Four Mu #Delta#phi");
  delta_phi_alt->SetYTitle("Events");
  delta_phi_alt->SetLineWidth(2);
  delta_phi_alt->Sumw2();
  delta_phi_alt->SetMinimum(0);

  //TH1D *fourmu_mass_alt2 = new TH1D("fourmu_mass_alt2","fourmu_mass_alt2",80,0,80);
  TH1D *delta_phi_alt2 = new TH1D("delta_phi_alt2","delta_phi_alt2",ndpbins,dpbins);
  delta_phi_alt2->SetXTitle("Four Mu #Delta #phi");
  delta_phi_alt2->SetYTitle("Events");
  delta_phi_alt2->SetLineWidth(2);
  delta_phi_alt2->Sumw2();
  delta_phi_alt2->SetMinimum(0);

  //TH1D *acc_shape = new TH1D("acc_shape","acc_shape",80,0,80);
  TH1D *acc_shape = new TH1D("acc_shape","acc_shape",ndpbins,dpbins);
  acc_shape->SetXTitle("Four Mu #Delta#phi");
  acc_shape->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape->SetMinimum(0);
  acc_shape->SetLineColor(kBlue);
  acc_shape->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",80,0,80);
  TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",ndpbins,dpbins);
  acc_eff_shape_dps->SetXTitle("Four Mu #Delta#phi");
  acc_eff_shape_dps->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps->SetMinimum(0);
  acc_eff_shape_dps->SetLineColor(kGreen);
  acc_eff_shape_dps->SetLineWidth(2);
  
  TCanvas* disp = new TCanvas("c","c", 1800,1800);
  TCanvas* acc = new TCanvas("acc","acc", 900,900);
  acc.Divide(2,4);
  disp.Divide(3,4);


  disp->cd(1);
  gendps_tot = gendps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>> delta_phi","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  delta_phi.Scale(genscale);
  disp->cd(2);
  gendps_acc = gendps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))) >> delta_phi_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  delta_phi.Scale(accscale);
  disp->cd(3);
  recodps_tot = recodps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))) >> delta_phi_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps->Add(delta_phi_alt);
  acc_eff_shape_dps->Divide(delta_phi);
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_gen[ibin] = 1.0/sqrt(delta_phi->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_reco[ibin] = 1.0/sqrt(delta_phi_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<80; ibin++) acc_eff_shape_dps->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(1);
  acc_eff_shape_dps->Draw("E1");
  
  acc_shape->Add(delta_phi_alt2);
  acc_shape->Divide(delta_phi);
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_gen[ibin] = 1.0/sqrt(delta_phi->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) err_frac_reco[ibin] = 1.0/sqrt(delta_phi_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<80; ibin++) acc_eff_frac[ibin] = acc_shape->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<80; ibin++) acc_shape->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(2);
  acc_shape->Draw("E1");
  std::cout<<"M: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
//pT1 dists

  //TH1D *psi1_pt = new TH1D("psi1_pt","psi1_pt",40,0,40);
  TH1D *psi1_pt = new TH1D("psi1_pt","psi1_pt",npt1bins,pt1bins);
  psi1_pt->SetXTitle("Dimuon_{1} pT (GeV)");
  psi1_pt->SetYTitle("Events");
  psi1_pt->SetLineWidth(2);
  psi1_pt->Sumw2();
  psi1_pt->SetMinimum(0);

  //TH1D *psi1_pt_alt = new TH1D("psi1_pt_alt","psi1_pt_alt",40,0,40);
  TH1D *psi1_pt_alt = new TH1D("psi1_pt_alt","psi1_pt_alt",npt1bins,pt1bins);
  psi1_pt_alt->SetXTitle("Dimuon_{1} pT (GeV)");
  psi1_pt_alt->SetYTitle("Events");
  psi1_pt_alt->SetLineWidth(2);
  psi1_pt_alt->Sumw2();
  psi1_pt_alt->SetMinimum(0);

  //TH1D *psi1_pt_alt2 = new TH1D("psi1_pt_alt2","psi1_pt_alt2",40,0,40);
  TH1D *psi1_pt_alt2 = new TH1D("psi1_pt_alt2","psi1_pt_alt2",npt1bins,pt1bins);
  psi1_pt_alt2->SetXTitle("Dimuon_{1} pT (GeV)");
  psi1_pt_alt2->SetYTitle("Events");
  psi1_pt_alt2->SetLineWidth(2);
  psi1_pt_alt2->Sumw2();
  psi1_pt_alt2->SetMinimum(0);

  //TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",40,0,40);
  TH1D *acc_shape_pt1 = new TH1D("acc_shape_pt1","acc_shape_pt1",npt1bins,pt1bins);
  acc_shape_pt1->SetXTitle("Dimuon_{1} pT (GeV)");
  acc_shape_pt1->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape_pt1->SetMinimum(0);
  acc_shape_pt1->SetLineColor(kBlue);
  acc_shape_pt1->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",40,0,40);
  TH1D *acc_eff_shape_dps_pt1 = new TH1D("acc_eff_shape_dps_pt1","acc_eff_shape_dps_pt1",npt1bins,pt1bins);
  acc_eff_shape_dps_pt1->SetXTitle("Dimuon_{1} pT(GeV)");
  acc_eff_shape_dps_pt1->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps_pt1->SetMinimum(0);
  acc_eff_shape_dps_pt1->SetLineColor(kGreen);
  acc_eff_shape_dps_pt1->SetLineWidth(2);
  
  disp->cd(4);

    gendps_tot = gendps.Draw("Psi_pT[0]>> psi1_pt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  psi1_pt.Scale(genscale);
  disp->cd(5);
    gendps_acc = gendps.Draw("Psi_pT[0]>> psi1_pt_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  psi1_pt_alt2.Scale(accscale);
  disp->cd(6);
    recodps_tot = recodps.Draw("Psi_pT[0]>> psi1_pt_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps_pt1->Add(psi1_pt_alt);
  acc_eff_shape_dps_pt1->Divide(psi1_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(psi1_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(psi1_pt_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps_pt1->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_shape_dps_pt1->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(3);
  acc_eff_shape_dps_pt1->Draw("E1");

  acc_shape_pt1->Add(psi1_pt_alt2);
  acc_shape_pt1->Divide(psi1_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(psi1_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(psi1_pt_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_shape_pt1->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_shape_pt1->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(4);
  acc_shape_pt1->Draw("E1");
  std::cout<<"pT: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
  
//pT2 dists

  //TH1D *psi2_pt = new TH1D("psi2_pt","psi2_pt",40,0,40);
  TH1D *psi2_pt = new TH1D("psi2_pt","psi2_pt",npt2bins,pt2bins);
  psi2_pt->SetXTitle("Dimuon_{2} pT (GeV)");
  psi2_pt->SetYTitle("Events");
  psi2_pt->SetLineWidth(2);
  psi2_pt->Sumw2();
  psi2_pt->SetMinimum(0);

  //TH1D *psi2_pt_alt = new TH1D("psi2_pt_alt","psi2_pt_alt",40,0,40);
  TH1D *psi2_pt_alt = new TH1D("psi2_pt_alt","psi2_pt_alt",npt2bins,pt2bins);
  psi2_pt_alt->SetXTitle("Dimuon_{2} pT (GeV)");
  psi2_pt_alt->SetYTitle("Events");
  psi2_pt_alt->SetLineWidth(2);
  psi2_pt_alt->Sumw2();
  psi2_pt_alt->SetMinimum(0);

  //TH1D *psi2_pt_alt2 = new TH1D("psi2_pt_alt2","psi2_pt_alt2",40,0,40);
  TH1D *psi2_pt_alt2 = new TH1D("psi2_pt_alt2","psi2_pt_alt2",npt2bins,pt2bins);
  psi2_pt_alt2->SetXTitle("Dimuon_{2} pT (GeV)");
  psi2_pt_alt2->SetYTitle("Events");
  psi2_pt_alt2->SetLineWidth(2);
  psi2_pt_alt2->Sumw2();
  psi2_pt_alt2->SetMinimum(0);

  //TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",40,0,40);
  TH1D *acc_shape_pt2 = new TH1D("acc_shape_pt2","acc_shape_pt2",npt2bins,pt2bins);
  acc_shape_pt2->SetXTitle("Dimuon_{2} pT (GeV)");
  acc_shape_pt2->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape_pt2->SetMinimum(0);
  acc_shape_pt2->SetLineColor(kBlue);
  acc_shape_pt2->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",40,0,40);
  TH1D *acc_eff_shape_dps_pt2 = new TH1D("acc_eff_shape_dps_pt2","acc_eff_shape_dps_pt2",npt2bins,pt2bins);
  acc_eff_shape_dps_pt2->SetXTitle("Dimuon_{2} pT(GeV)");
  acc_eff_shape_dps_pt2->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps_pt2->SetMinimum(0);
  acc_eff_shape_dps_pt2->SetLineColor(kGreen);
  acc_eff_shape_dps_pt2->SetLineWidth(2);
  
  disp->cd(7);

    gendps_tot = gendps.Draw("Psi_pT[1]>> psi2_pt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  psi2_pt.Scale(genscale);
  disp->cd(8);
    gendps_acc = gendps.Draw("Psi_pT[1]>> psi2_pt_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  psi2_pt_alt2.Scale(accscale);
  disp->cd(9);
    recodps_tot = recodps.Draw("Psi_pT[1]>> psi2_pt_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps_pt2->Add(psi2_pt_alt);
  acc_eff_shape_dps_pt2->Divide(psi2_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(psi2_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(psi2_pt_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_shape_dps_pt2->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(5);
  acc_eff_shape_dps_pt2->Draw("E1");

  acc_shape_pt2->Add(psi2_pt_alt2);
  acc_shape_pt2->Divide(psi2_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(psi2_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(psi2_pt_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_shape_pt2->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_shape_pt2->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(6);
  acc_shape_pt2->Draw("E1");
//pTa dists

  //TH1D *psia_pt = new TH1D("psia_pt","psia_pt",40,0,40);
  TH1D *psia_pt = new TH1D("psia_pt","psia_pt",nptabins,ptabins);
  psia_pt->SetXTitle("Dimuon pT Assymetery");
  psia_pt->SetYTitle("Events");
  psia_pt->SetLineWidth(2);
  psia_pt->Sumw2();
  psia_pt->SetMinimum(0);

  //TH1D *psia_pt_alt = new TH1D("psia_pt_alt","psia_pt_alt",40,0,40);
  TH1D *psia_pt_alt = new TH1D("psia_pt_alt","psia_pt_alt",nptabins,ptabins);
  psia_pt_alt->SetXTitle("Dimuon pT Assymetery");
  psia_pt_alt->SetYTitle("Events");
  psia_pt_alt->SetLineWidth(2);
  psia_pt_alt->Sumw2();
  psia_pt_alt->SetMinimum(0);

  //TH1D *psia_pt_alt2 = new TH1D("psia_pt_alt2","psia_pt_alt2",40,0,40);
  TH1D *psia_pt_alt2 = new TH1D("psia_pt_alt2","psia_pt_alt2",nptabins,ptabins);
  psia_pt_alt2->SetXTitle("Dimuon pT Assymetery");
  psia_pt_alt2->SetYTitle("Events");
  psia_pt_alt2->SetLineWidth(2);
  psia_pt_alt2->Sumw2();
  psia_pt_alt2->SetMinimum(0);

  //TH1D *acc_shape_pt = new TH1D("acc_shape_pt","acc_shape_pt",40,0,40);
  TH1D *acc_shape_pta = new TH1D("acc_shape_pta","acc_shape_pta",nptabins,ptabins);
  acc_shape_pta->SetXTitle("Dimuon pT Assymetery");
  acc_shape_pta->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_shape_pta->SetMinimum(0);
  acc_shape_pta->SetLineColor(kBlue);
  acc_shape_pta->SetLineWidth(2);

  //TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",40,0,40);
  TH1D *acc_eff_shape_dps_pta = new TH1D("acc_eff_shape_dps_pta","acc_eff_shape_dps_pta",nptabins,ptabins);
  acc_eff_shape_dps_pta->SetXTitle("Dimuon pT Assymetery");
  acc_eff_shape_dps_pta->SetYTitle("N_{Reco}/N_{Gen} (Arbitrary Units)");
  acc_eff_shape_dps_pta->SetMinimum(0);
  acc_eff_shape_dps_pta->SetLineColor(kGreen);
  acc_eff_shape_dps_pta->SetLineWidth(2);
  
  disp->cd(10);

    gendps_tot = gendps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> psia_pt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_tot = gendps_tot*genscale;
  psia_pt.Scale(genscale);
  disp->cd(11);
    gendps_acc = gendps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> psia_pt_alt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2)","");
  gendps_acc = gendps_acc*accscale;
  psia_pt_alt2.Scale(accscale);
  disp->cd(12);
    recodps_tot = recodps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> psia_pt_alt","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","");
  acc_eff_shape_dps_pta->Add(psia_pt_alt);
  acc_eff_shape_dps_pta->Divide(psia_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(psia_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(psia_pt_alt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_eff_shape_dps_pta->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_shape_dps_pta->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(7);
  acc_eff_shape_dps_pta->Draw("E1");

  acc_shape_pta->Add(psia_pt_alt2);
  acc_shape_pta->Divide(psia_pt);
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_gen[ibin] = 1.0/sqrt(psia_pt->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) err_frac_reco[ibin] = 1.0/sqrt(psia_pt_alt2->GetBinContent(ibin+1));
  for(Int_t ibin=0; ibin<40; ibin++) acc_eff_frac[ibin] = acc_shape_pta->GetBinContent(ibin+1);
  for(Int_t ibin=0; ibin<40; ibin++) acc_shape_pta->SetBinError(ibin+1, acc_eff_frac[ibin]*sqrt(err_frac_gen[ibin]*err_frac_gen[ibin]+err_frac_reco[ibin]*err_frac_reco[ibin]));
  acc->cd(8);
  acc_shape_pta->Draw("E1");
  std::cout<<"pT: Total AccXEff = "<<(float)recodps_tot/(float)gendps_tot<<" Total Eff only = "<<(float)recodps_tot/(float)gendps_acc<<" Total Acc only = "<<(float)gendps_acc/(float)gendps_tot<<std::endl;
}

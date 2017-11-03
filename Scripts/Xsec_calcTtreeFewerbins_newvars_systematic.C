#include <string>
#include <stdlib.h>
#include <cmath>
#include "Riostream.h"
#include <TROOT.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include <TRandom3.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1F.h>
#include <TH2F.h>
#include "TF1.h"
#include <TLorentzVector.h>
#include <TVector3.h>


int Xsec_calcTtreeFewerbins_newvars_systematic() {
  gROOT->Reset();

  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  //  float datapt[60],datady[20],datay[20];
  TChain data("ntuple");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");
//  float dpbins[]={0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.,2.25,2.5,2.75,3.142};
  float dpbins[]={0,0.25,1.0,1.75,2.5,3.142};
  float pt1bins[]={5,10,12,14,17,20,25,60};
  float pt2bins[]={5,8,10,12,15,20,40};
  float ptabins[]={0,0.05,0.125,0.2,0.35,1.};
  int ndpbins = 5;
  int npt1bins = 7;
  int npt2bins = 6;
  int nptabins = 5;
  //  float massbins[]={6.2,6.5,7,8.5,11,14,18,24,30,45,80};
  //  float massbins2[]={0,6.2,6.5,7,8.5,11,14,18,24,30,45,80};
  //  float ptbins[]={0,4,8,12,15,18,22,26,30,80};
  //  float dybins[]={0,0.1,0.2,0.3,0.45,0.6,0.9,1.3,1.8,2.4,4.5};
  ////  float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  //  float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  //  int nmbins = 10; 
  //  int nmbins2 = 10; 
  //  int nptbins = 9;
  //  int ndybins = 10;
  //  int nybins = 10;
  float fracDPS = 0.13;
  float fracNLO = 0.87;
  float corrPopdp = 0;
  float corrPoppt1 = 0;
  float corrPoppt2 = 0;
  float corrPoppta = 0;
  float xsec_sum_dp = 0;
  float xsec_sum_pt1= 0;
  float xsec_sum_pt2= 0;
  float xsec_sum_pta = 0;
  float xsecerr_sum_dp = 0;
  float xsecerr_sum_pt1 = 0;
  float xsecerr_sum_pt2 = 0;
  float xsecerr_sum_pta = 0;

  TH1F *dp_data = new TH1F("dp_data","dp_data",ndpbins,dpbins); 
  TH1F *pt1_data = new TH1F("pt1_data","pt1_data",npt1bins,pt1bins); 
  TH1F *pt2_data = new TH1F("pt2_data","pt2_data",npt2bins,pt2bins); 
  TH1F *pta_data = new TH1F("pta_data","pta_data",nptabins,ptabins); 
  TH1F *xsec_dp = new TH1F("xsec_dp","xsec_dp",ndpbins,dpbins); 
  TH1F *xsec_pt1 = new TH1F("xsec_pt1","xsec_pt1",npt1bins,pt1bins); 
  TH1F *xsec_pt2 = new TH1F("xsec_pt2","xsec_pt2",npt2bins,pt2bins); 
  TH1F *xsec_pta = new TH1F("xsec_pta","xsec_pta",nptabins,ptabins); 
  xsec_dp->SetMinimum(0);
  xsec_pt1->SetMinimum(0);
  xsec_pt2->SetMinimum(0);
  xsec_pta->SetMinimum(0);
  data.Add("TMTight_Selected_newAcc.root");
  //data.Draw("FourMu_Mass>>mass_data","","egoff"); 
  //data.Draw("FourMu_pT>>pt_data","","egoff"); 
  //data.Draw("Psi1To2_dY>>dy_data","","egoff"); 
  //data.Draw("abs(FourMu_Rapidity)>>y_data","","egoff"); 
  dp_data->SetBinContent(1,152.); 
  dp_data->SetBinContent(2,141.);   
  dp_data->SetBinContent(3,58.);
  dp_data->SetBinContent(4,39.);
  dp_data->SetBinContent(5,92);
  dp_data->SetBinError(1,13.); 
  dp_data->SetBinError(2,13.);   
  dp_data->SetBinError(3,8.);
  dp_data->SetBinError(4,7.);
  dp_data->SetBinError(5,10.);
  pt1_data->SetBinContent(1,73.4);
  pt1_data->SetBinContent(2,88.7);
  pt1_data->SetBinContent(3,96.);
  pt1_data->SetBinContent(4,88.5);
  pt1_data->SetBinContent(5,54.3);
  pt1_data->SetBinContent(6,46.);
  pt1_data->SetBinContent(7,31.6);
  pt1_data->SetBinError(1,9.1);
  pt1_data->SetBinError(2,9.8.);
  pt1_data->SetBinError(3,11.0);
  pt1_data->SetBinError(4,9.8);
  pt1_data->SetBinError(5,7.6);
  pt1_data->SetBinError(6,7.2);
  pt1_data->SetBinError(7,6.0);
  pt2_data->SetBinContent(1,108.);
  pt2_data->SetBinContent(2,126.);
  pt2_data->SetBinContent(3,123.);
  pt2_data->SetBinContent(4,76.1);
  pt2_data->SetBinContent(5,36.);
  pt2_data->SetBinContent(6,11.8);
  pt2_data->SetBinError(1,11.);
  pt2_data->SetBinError(2,12.);
  pt2_data->SetBinError(3,12.);
  pt2_data->SetBinError(4,9.2);
  pt2_data->SetBinError(5,6.);
  pt2_data->SetBinError(6,3.5);
  pta_data->SetBinContent(1,34.3);
  pta_data->SetBinContent(2,185.);
  pta_data->SetBinContent(3,100.);
  pta_data->SetBinContent(4,115.);
  pta_data->SetBinContent(5,43.6);
  pta_data->SetBinError(1,6.4);
  pta_data->SetBinError(2,14.);
  pta_data->SetBinError(3,11.);
  pta_data->SetBinError(4,11.0);
  pta_data->SetBinError(5,7.2);


  //corrections from DPS PU
  TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",ndpbins, dpbins);
  acc_eff_shape_dps->SetBinContent(1,0.0219156);
  acc_eff_shape_dps->SetBinContent(2,0.02411801);
  acc_eff_shape_dps->SetBinContent(3,0.02384129);
  acc_eff_shape_dps->SetBinContent(4,0.02880021);
  acc_eff_shape_dps->SetBinContent(5,0.04108031);

  TH1D *acc_eff_shape_dps_pt1 = new TH1D("acc_eff_shape_dps_pt1","acc_eff_shape_dps_pt1",npt1bins, pt1bins);
  acc_eff_shape_dps_pt1->SetBinContent(1,0.007694378);
  acc_eff_shape_dps_pt1->SetBinContent(2,0.02667605);
  acc_eff_shape_dps_pt1->SetBinContent(3,0.04253364);
  acc_eff_shape_dps_pt1->SetBinContent(4,0.04979969);
  acc_eff_shape_dps_pt1->SetBinContent(5,0.0484733);
  acc_eff_shape_dps_pt1->SetBinContent(6,0.01238063);

  TH1D *acc_eff_shape_dps_pt2 = new TH1D("acc_eff_shape_dps_pt2","acc_eff_shape_dps_pt2",npt2bins, pt2bins);
  acc_eff_shape_dps_pt2->SetBinContent(1,0.009222299);
  acc_eff_shape_dps_pt2->SetBinContent(2,0.03151152);
  acc_eff_shape_dps_pt2->SetBinContent(3,0.08343379);
  acc_eff_shape_dps_pt2->SetBinContent(4,0.1224433);

  TH1D *acc_eff_shape_dps_pta = new TH1D("acc_eff_shape_dps_pta","acc_eff_shape_dps_pta",nptabins, ptabins);
  acc_eff_shape_dps_pta->SetBinContent(1,0.01277959);
  acc_eff_shape_dps_pta->SetBinContent(2,0.01446442);
  acc_eff_shape_dps_pta->SetBinContent(3,0.0125155);
  acc_eff_shape_dps_pta->SetBinContent(4,0.01940185);
  acc_eff_shape_dps_pta->SetBinContent(5,0.02355463);

  TH1D *acc_eff_shape_nlo = new TH1D("acc_eff_shape_nlo","acc_eff_shape_nlo",ndpbins, dpbins);
  acc_eff_shape_nlo->SetBinContent(1,0.03755475);
  acc_eff_shape_nlo->SetBinContent(2,0.035136);
  acc_eff_shape_nlo->SetBinContent(3,0.02933197);
  acc_eff_shape_nlo->SetBinContent(4,0.03368309);
  acc_eff_shape_nlo->SetBinContent(5,0.03575284);

//  acc_eff_shape_nlo->SetBinContent(1,0.1291394);
//  acc_eff_shape_nlo->SetBinContent(2,0.05207096);
//  acc_eff_shape_nlo->SetBinContent(3,0.01889098);
//  acc_eff_shape_nlo->SetBinContent(4,0.01585437);
//  acc_eff_shape_nlo->SetBinContent(5,0.02483066);

  TH1D *acc_eff_shape_nlo_pt1 = new TH1D("acc_eff_shape_nlo_pt1","acc_eff_shape_nlo_pt1",npt1bins, pt1bins);
  acc_eff_shape_nlo_pt1->SetBinContent(1,0.009837757);
  acc_eff_shape_nlo_pt1->SetBinContent(2,0.02705243);
  acc_eff_shape_nlo_pt1->SetBinContent(3,0.04625061);
  acc_eff_shape_nlo_pt1->SetBinContent(4,0.06856784);
  acc_eff_shape_nlo_pt1->SetBinContent(5,0.107855);
  acc_eff_shape_nlo_pt1->SetBinContent(6,0.09681247);
  acc_eff_shape_nlo_pt1->SetBinContent(7,0.08708955);

  TH1D *acc_eff_shape_nlo_pt2 = new TH1D("acc_eff_shape_nlo_pt2","acc_eff_shape_nlo_pt2",npt2bins, pt2bins);
  acc_eff_shape_nlo_pt2->SetBinContent(1,0.01306789);
  acc_eff_shape_nlo_pt2->SetBinContent(2,0.02974824);
  acc_eff_shape_nlo_pt2->SetBinContent(3,0.07445535);
  acc_eff_shape_nlo_pt2->SetBinContent(4,0.1288635);
  acc_eff_shape_nlo_pt2->SetBinContent(5,0.2113137);
  acc_eff_shape_nlo_pt2->SetBinContent(6,0.103392);

  TH1D *acc_eff_shape_nlo_pta = new TH1D("acc_eff_shape_nlo_pta","acc_eff_shape_nlo_pta",nptabins, ptabins);
  acc_eff_shape_nlo_pta->SetBinContent(1,0.02700643);
  acc_eff_shape_nlo_pta->SetBinContent(2,0.03098703);
  acc_eff_shape_nlo_pta->SetBinContent(3,0.03480909);
  acc_eff_shape_nlo_pta->SetBinContent(4,0.03450216);
  acc_eff_shape_nlo_pta->SetBinContent(5,0.04555698);

   TH1D *dps_frac_dp= new TH1D("dps_frac_dp","dps_frac_dp",ndpbins, dpbins);
dps_frac_dp->SetBinContent(1,0.0522849);
dps_frac_dp->SetBinContent(2,0.103671);
dps_frac_dp->SetBinContent(3,0.246255);
dps_frac_dp->SetBinContent(4,0.310659);
dps_frac_dp->SetBinContent(5,0.333942);

   TH1D *dps_frac_pt1= new TH1D("dps_frac_pt1","dps_frac_pt1",npt1bins, pt1bins);
dps_frac_pt1->SetBinContent(2,0.132963);
dps_frac_pt1->SetBinContent(3,0.218501);
dps_frac_pt1->SetBinContent(4,0.237635);
dps_frac_pt1->SetBinContent(5,0.244286);
dps_frac_pt1->SetBinContent(6,0.219077);
dps_frac_pt1->SetBinContent(7,0.151189);
dps_frac_pt1->SetBinContent(8,0);

   TH1D *dps_frac_pt2= new TH1D("dps_frac_pt2","dps_frac_pt2",npt2bins, pt2bins);
dps_frac_pt2->SetBinContent(2,0.360542);
dps_frac_pt2->SetBinContent(3,0.195885);
dps_frac_pt2->SetBinContent(4,0.0925699);
dps_frac_pt2->SetBinContent(5,0.0364071);
dps_frac_pt2->SetBinContent(6,0);
dps_frac_pt2->SetBinContent(7,0);

   TH1D *dps_frac_pta = new TH1D("dps_frac_pta","dps_frac_pta",nptabins, ptabins);
dps_frac_pta->SetBinContent(1,0.190784);
dps_frac_pta->SetBinContent(2,0.185194);
dps_frac_pta->SetBinContent(3,0.156854);
dps_frac_pta->SetBinContent(4,0.200613);
dps_frac_pta->SetBinContent(5,0.14438);

  TH1D *tnp_diff_dp = new TH1D("tnp_diff_dp","tnp_diff_dp", ndpbins,dpbins);
  tnp_diff_dp->SetBinContent(1, 0.187299);
  tnp_diff_dp->SetBinContent(2,  0.211277);
  tnp_diff_dp->SetBinContent(3,  0.19255);
  tnp_diff_dp->SetBinContent(4, 0.213922);
  tnp_diff_dp->SetBinContent(5, 0.214664);
  TH1D *tnp_diff_pt1 = new TH1D("tnp_diff_pt1","tnp_diff_pt1", npt1bins, pt1bins);
  tnp_diff_pt1->SetBinContent(1,0.361584  );
  tnp_diff_pt1->SetBinContent(2,0.256302  );
  tnp_diff_pt1->SetBinContent(3, 0.21533  );
  tnp_diff_pt1->SetBinContent(4,0.184563  );
  tnp_diff_pt1->SetBinContent(5,0.146478  );
  tnp_diff_pt1->SetBinContent(6,0.118045  );
  tnp_diff_pt1->SetBinContent(7,0.0938983 );
  TH1D *tnp_diff_pt2 = new TH1D("tnp_diff_pt2","tnp_diff_pt2", npt2bins, pt2bins);
  tnp_diff_pt2->SetBinContent(1, 0.313698);
  tnp_diff_pt2->SetBinContent(2, 0.238785 );
  tnp_diff_pt2->SetBinContent(3, 0.190435 );
  tnp_diff_pt2->SetBinContent(4, 0.131826 );
  tnp_diff_pt2->SetBinContent(5, 0.0808294);
  tnp_diff_pt2->SetBinContent(6, 0.0811883);
  TH1D *tnp_diff_pta = new TH1D("tnp_diff_pta","tnp_diff_pta", nptabins, ptabins);
  tnp_diff_pta->SetBinContent(1,  0.207995);
  tnp_diff_pta->SetBinContent(2,  0.213028);
  tnp_diff_pta->SetBinContent(3,  0.215356 );
  tnp_diff_pta->SetBinContent(4,  0.195633);
  tnp_diff_pta->SetBinContent(5,  0.154274  );


  for(int dpbin=1; dpbin<=ndpbins; ++dpbin){
    corrPopdp = dp_data->GetBinContent(dpbin)/(0.0596*0.0596*20.2*(1+0.5*tnp_diff_dp->GetBinContent(dpbin))*((dps_frac_dp->GetBinContent(dpbin)*acc_eff_shape_dps->GetBinContent(dpbin))+((1-dps_frac_dp->GetBinContent(dpbin))*acc_eff_shape_nlo->GetBinContent(dpbin)))*(dpbins[dpbin]-dpbins[dpbin-1]));
    xsec_dp->SetBinContent(dpbin,corrPopdp*1e-3);
    xsec_sum_dp = xsec_sum_dp+(corrPopdp*1e-3*(dpbins[dpbin]-dpbins[dpbin-1]));
    xsec_dp->SetBinError(dpbin, xsec_dp->GetBinContent(dpbin)*(dp_data->GetBinError(dpbin)/dp_data->GetBinContent(dpbin)));
    xsecerr_sum_dp = 0;
  }
  for(int pt1bin=1; pt1bin<=npt1bins; ++pt1bin){
    corrPoppt1 = pt1_data->GetBinContent(pt1bin)/(pow(0.0596,2)*20.2*(1+0.5*tnp_diff_pt1->GetBinContent(pt1bin))*((dps_frac_pt1->GetBinContent(pt1bin)*acc_eff_shape_dps_pt1->GetBinContent(pt1bin))+((1.-dps_frac_pt1->GetBinContent(pt1bin))*acc_eff_shape_nlo_pt1->GetBinContent(pt1bin)))*(pt1bins[pt1bin]-pt1bins[pt1bin-1]));
    //            std::cout<<pt1_data->GetBinContent(pt1bin)<<" over "<<0.0593*0.0593*20.339<<" times "<<dps_frac_pt1->GetBinContent(pt1bin)<<" times "<<acc_eff_shape_dps_pt1->GetBinContent(pt1bin)<<" + "<<(1-(dps_frac_pt1->GetBinContent(pt1bin)))<<" times "<<acc_eff_shape_nlo_pt1->GetBinContent(pt1bin)<<" times "<<(pt1bins[pt1bin]-pt1bins[pt1bin-1])<<" equals??? "<<corrPoppt1<<std::endl;
//            std::cout<<pt1_data->GetBinContent(pt1bin)<<" over "<<0.0593*0.0593*20.339<<" times "<<fracDPS<<" times "<<acc_eff_shape_dps_pt1->GetBinContent(pt1bin)<<" + "<<fracNLO<<" times "<<acc_eff_shape_nlo_pt1->GetBinContent(pt1bin)<<" times "<<(pt1bins[pt1bin]-pt1bins[pt1bin-1])<<" equals??? "<<corrPoppt1<<std::endl;
    xsec_pt1->SetBinContent(pt1bin,corrPoppt1*1e-3);
    xsec_sum_pt1 = xsec_sum_pt1+(corrPoppt1*1e-3*(pt1bins[pt1bin]-pt1bins[pt1bin-1]));
    xsec_pt1->SetBinError(pt1bin, xsec_pt1->GetBinContent(pt1bin)*(pt1_data->GetBinError(pt1bin)/pt1_data->GetBinContent(pt1bin)));
  }
  for(int pt2bin=1; pt2bin<=npt2bins; ++pt2bin){
    corrPoppt2 = pt2_data->GetBinContent(pt2bin)/(pow(0.0596,2)*20.2*(1+0.5*tnp_diff_pt2->GetBinContent(pt2bin))*(dps_frac_pt2->GetBinContent(pt2bin)*acc_eff_shape_dps_pt2->GetBinContent(pt2bin)+(1-dps_frac_pt2->GetBinContent(pt2bin))*acc_eff_shape_nlo_pt2->GetBinContent(pt2bin))*(pt2bins[pt2bin]-pt2bins[pt2bin-1]));
    //          std::cout<<pt2_data->GetBinContent(pt2bin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_pt2->GetBinContent(pt2bin))+(fracNLO*acc_eff_shape_nlo_pt2->GetBinContent(pt2bin)))<<" times "<<(pt2bins[pt2bin]-pt2bins[pt2bin-1])<<" equals??? "<<corrPoppt2<<std::endl;
    xsec_pt2->SetBinContent(pt2bin,corrPoppt2*1e-3);
    xsec_sum_pt2 = xsec_sum_pt2+(corrPoppt2*1e-3*(pt2bins[pt2bin]-pt2bins[pt2bin-1]));
    xsec_pt2->SetBinError(pt2bin, xsec_pt2->GetBinContent(pt2bin)*(pt2_data->GetBinError(pt2bin)/pt2_data->GetBinContent(pt2bin)));
  }
  for(int ptabin=1; ptabin<=nptabins; ++ptabin){
    corrPoppta = pta_data->GetBinContent(ptabin)/(pow(0.0596,2)*20.2*(1+0.5*tnp_diff_pta->GetBinContent(ptabin))*(dps_frac_pta->GetBinContent(ptabin)*acc_eff_shape_dps_pta->GetBinContent(ptabin)+(1-dps_frac_pta->GetBinContent(ptabin))*acc_eff_shape_nlo_pta->GetBinContent(ptabin))*(ptabins[ptabin]-ptabins[ptabin-1]));
    //          std::cout<<dpta_data->GetBinContent(dptabin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_dpta->GetBinContent(dptabin))+(fracNLO*acc_eff_shape_nlo_dpta->GetBinContent(dptabin)))<<" times "<<(dptabins[dptabin]-dptabins[dptabin-1])<<" equals??? "<<corrPopdpta<<std::endl;
    xsec_pta->SetBinContent(ptabin,corrPoppta*1e-3);
    xsec_sum_pta = xsec_sum_pta+(corrPoppta*1e-3*(ptabins[ptabin]-ptabins[ptabin-1]));
    xsec_pta->SetBinError(ptabin, xsec_pta->GetBinContent(ptabin)*(pta_data->GetBinError(ptabin)/pta_data->GetBinContent(ptabin)));
  }
  std::cout<<"dPhi Integral: "<<xsec_sum_dp<<std::endl;
  std::cout<<"pT1 Integral: "<<xsec_sum_pt1<<std::endl;
  std::cout<<"pT2 Integral: "<<xsec_sum_pt2<<std::endl;
  std::cout<<"pTa Integral: "<<xsec_sum_pta<<std::endl;
  TCanvas* disp = new TCanvas("disp","disp",900,900);
  disp->Divide(2,2);
  disp->cd(1);
  disp_1->SetLeftMargin(0.15);
  xsec_dp->SetXTitle("#Delta#phi between J/#psi");
  xsec_dp->SetYTitle("d#sigma/d#Delta#phi (pb)");
  xsec_dp->SetTitleOffset(1.6,"Y");
  xsec_dp->Draw("e1");
  disp->cd(2);
  disp_2->SetLeftMargin(0.15);
  xsec_pt1->SetXTitle("p_{T}^{J/#psi 1} (GeV/c)");
  xsec_pt1->SetYTitle("d#sigma/dp_{T}^{J/#psi 1} (pb/(GeV/c))");
  xsec_pt1->SetTitleOffset(1.7,"Y");
  xsec_pt1->Draw("e1");
  disp->cd(3);
  disp_3->SetLeftMargin(0.15);
  xsec_pt2->SetXTitle("p_{T}^{J/#psi 2} (GeV/c)");
  xsec_pt2->SetYTitle("d#sigma/dp_{T}^{J/#psi 2} (pb/(GeV/c))");
  xsec_pt2->SetTitleOffset(1.7,"Y");
  xsec_pt2->Draw("e1");
  disp->cd(4);
  disp_4->SetLeftMargin(0.15);
  xsec_pta->SetXTitle("A_{p_{T}}^{J/#psi J/#psi}");
  xsec_pta->SetYTitle("d#sigma/dpt A (pb)");
  xsec_pta->SetTitleOffset(1.6,"Y");
  xsec_pta->Draw("e1");
  //  dy_data.Draw("e");    
}

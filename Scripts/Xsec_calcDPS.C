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


int Xsec_calcDPS() {
  gROOT->Reset();

  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  //  float datapt[60],datady[20],datay[20];
  TChain data("ntuple");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");

  float massbins[]={6.2,6.5,7,8.5,11,14,18,24,30,45,80};
  float massbins2[]={0,6.2,6.5,7,8.5,11,14,18,24,30,45,80};
  float ptbins[]={0,4,8,12,15,18,22,26,30,80};
  float dybins[]={0,0.1,0.2,0.3,0.45,0.6,0.9,1.3,1.8,2.4,4.5};
  float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  int nmbins = 10; 
  int nmbins2 = 11; 
  int nptbins = 9;
  int ndybins = 10;
  int nybins = 10;
  float corrPop = 0;
  float corrPoppt = 0;
  float corrPopdy = 0;
  float xsec_sum_mass = 0;
  float xsec_sum_dy= 0;
  float xsec_sum_pt = 0;

  TH1F *mass_data = new TH1F("mass_data","mass_data",nmbins,massbins); 
  TH1F *pt_data = new TH1F("pt_data","pt_data",nptbins,ptbins); 
  TH1F *dy_data = new TH1F("dy_data","dy_data",ndybins,dybins); 
  TH1F *y_data = new TH1F("y_data","y_data",nybins,ybins); 
  TH1F *xsec_mass = new TH1F("xsec_mass","xsec_mass",nmbins2,massbins2); 
  TH1F *xsec_pt = new TH1F("xsec_pt","xsec_pt",nptbins,ptbins); 
  TH1F *xsec_dy = new TH1F("xsec_dy","xsec_dy",ndybins,dybins); 
  mass_data->Sumw2();
  pt_data->Sumw2();
  dy_data->Sumw2();
  y_data->Sumw2();
  xsec_mass->Sumw2();
  xsec_pt->Sumw2();
  xsec_dy->Sumw2();
  xsec_pt->SetMinimum(0);
  xsec_dy->SetMinimum(0);
  mass_data->SetBinContent(1,6.); 
  mass_data->SetBinContent(2,14.);   
  mass_data->SetBinContent(3,33.);
  mass_data->SetBinContent(4,54.);
  mass_data->SetBinContent(5,81.);
  mass_data->SetBinContent(6,95.);
  mass_data->SetBinContent(7,103.);
  mass_data->SetBinContent(8,80.);
  mass_data->SetBinContent(9,193.);
  mass_data->SetBinContent(10,125.);
  mass_data->SetEntries(784.);
  pt_data->SetBinContent(1,78.);
  pt_data->SetBinContent(2,151.);
  pt_data->SetBinContent(3,198.);
  pt_data->SetBinContent(4,155.);
  pt_data->SetBinContent(5,114.);
  pt_data->SetBinContent(6,68.);
  pt_data->SetBinContent(7,17.);
  pt_data->SetBinContent(8,3.);
  pt_data->SetEntries(784.0);
  dy_data->SetBinContent(1,41.);
  dy_data->SetBinContent(2,45.);
  dy_data->SetBinContent(3,44.);
  dy_data->SetBinContent(4,51.);
  dy_data->SetBinContent(5,46.);
  dy_data->SetBinContent(6,59.);
  dy_data->SetBinContent(7,59.);
  dy_data->SetBinContent(8,67.);
  dy_data->SetBinContent(9,83.);
  dy_data->SetBinContent(10,289.);
  dy_data->SetEntries(784.);
  //corrections from DPS PU
  TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",nmbins, massbins);
  acc_eff_shape_dps->SetBinContent(1,0.003625894);
  acc_eff_shape_dps->SetBinContent(2,0.005040147);
  acc_eff_shape_dps->SetBinContent(3,0.004900944);
  acc_eff_shape_dps->SetBinContent(4,0.004601236);
  acc_eff_shape_dps->SetBinContent(5,0.006519032);
  acc_eff_shape_dps->SetBinContent(6,0.01182224);
  acc_eff_shape_dps->SetBinContent(7,0.01537112);
  acc_eff_shape_dps->SetBinContent(8,0.01157893);
  acc_eff_shape_dps->SetBinContent(9,0.006657563);
  acc_eff_shape_dps->SetBinContent(10,0.01604463);
  acc_eff_shape_dps->SetBinError(1,0.0005670719);
  acc_eff_shape_dps->SetBinError(2,0.0007525944);
  acc_eff_shape_dps->SetBinError(3,0.0007402356);
  acc_eff_shape_dps->SetBinError(4,0.0006454692);
  acc_eff_shape_dps->SetBinError(5,0.0009634478);
  acc_eff_shape_dps->SetBinError(6,0.001543331);
  acc_eff_shape_dps->SetBinError(7,0.002008586);
  acc_eff_shape_dps->SetBinError(8,0.001419939);
  acc_eff_shape_dps->SetBinError(9,0.0007337227);
  acc_eff_shape_dps->SetBinError(10,0.0009455578);
  TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",nptbins, ptbins);
  acc_eff_shape_dps_pt->SetBinContent(1,0.00509843);
  acc_eff_shape_dps_pt->SetBinContent(2,0.0055055);
  acc_eff_shape_dps_pt->SetBinContent(3,0.006211806);
  acc_eff_shape_dps_pt->SetBinContent(4,0.01246575);
  acc_eff_shape_dps_pt->SetBinContent(5,0.02538593);
  acc_eff_shape_dps_pt->SetBinContent(6,0.0400525);
  acc_eff_shape_dps_pt->SetBinContent(7,0.0458451);
  acc_eff_shape_dps_pt->SetBinContent(8,0.02874296);
  acc_eff_shape_dps_pt->SetBinError(1,0.0005780548);
  acc_eff_shape_dps_pt->SetBinError(2,0.0004486776);
  acc_eff_shape_dps_pt->SetBinError(3,0.0004421724);
  acc_eff_shape_dps_pt->SetBinError(4,0.001004541);
  acc_eff_shape_dps_pt->SetBinError(5,0.002393386);
  acc_eff_shape_dps_pt->SetBinError(6,0.00490783);
  acc_eff_shape_dps_pt->SetBinError(7,0.01125196);
  acc_eff_shape_dps_pt->SetBinError(8,0.01671938);

  TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",ndybins, dybins);
  acc_eff_shape_dps_dy->SetBinContent(1,0.005407532);
  acc_eff_shape_dps_dy->SetBinContent(2,0.006367652);
  acc_eff_shape_dps_dy->SetBinContent(3,0.007183075);
  acc_eff_shape_dps_dy->SetBinContent(4,0.006914909);
  acc_eff_shape_dps_dy->SetBinContent(5,0.009011957);
  acc_eff_shape_dps_dy->SetBinContent(6,0.01043607);
  acc_eff_shape_dps_dy->SetBinContent(7,0.01419795);
  acc_eff_shape_dps_dy->SetBinContent(8,0.0144408);
  acc_eff_shape_dps_dy->SetBinContent(9,0.01547821);
  acc_eff_shape_dps_dy->SetBinContent(10,0.007100947);
  acc_eff_shape_dps_dy->SetBinError(1,0.0008457114);
  acc_eff_shape_dps_dy->SetBinError(2,0.0009508174);
  acc_eff_shape_dps_dy->SetBinError(3,0.001084927);
  acc_eff_shape_dps_dy->SetBinError(4,0.0009700352);
  acc_eff_shape_dps_dy->SetBinError(5,0.001331877);
  acc_eff_shape_dps_dy->SetBinError(6,0.001362374);
  acc_eff_shape_dps_dy->SetBinError(7,0.001855286);
  acc_eff_shape_dps_dy->SetBinError(8,0.001770893);
  acc_eff_shape_dps_dy->SetBinError(9,0.001705836);
  acc_eff_shape_dps_dy->SetBinError(10,0.0004184799);
        for(int mbin=1; mbin<=nmbins; ++mbin){
          //corrPop = mass_data->GetBinContent(mbin)/((massbins[mbin]-massbins[mbin-1])*((acc_eff_shape_dps->GetBinContent(mbin))));
          corrPop = mass_data->GetBinContent(mbin)/((acc_eff_shape_dps->GetBinContent(mbin)));
          xsec_mass->SetBinContent(mbin+1,corrPop);
          xsec_sum_mass = xsec_sum_mass+(corrPop);
        }
        for(int ptbin=1; ptbin<=nptbins-1; ++ptbin){
          corrPoppt = pt_data->GetBinContent(ptbin)/((acc_eff_shape_dps_pt->GetBinContent(ptbin)));
//          std::cout<<pt_data->GetBinContent(ptbin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_pt->GetBinContent(ptbin))+(fracNLO*acc_eff_shape_nlo_pt->GetBinContent(ptbin)))<<" times "<<(ptbins[ptbin]-ptbins[ptbin-1])<<" equals??? "<<corrPoppt<<std::endl;
          xsec_pt->SetBinContent(ptbin,corrPoppt);
          xsec_sum_pt = xsec_sum_pt+(corrPoppt);
        }
        for(int dybin=1; dybin<=ndybins; ++dybin){
          corrPopdy = dy_data->GetBinContent(dybin)/((acc_eff_shape_dps_dy->GetBinContent(dybin)));
          std::cout<<dy_data->GetBinContent(dybin)<<" over "<<"10  times "<<acc_eff_shape_dps_dy->GetBinContent(dybin)<<" times "<<(dybins[dybin]-dybins[dybin-1])<<" equals??? "<<corrPopdy<<std::endl;
            xsec_dy->SetBinContent(dybin,corrPopdy);
          xsec_sum_dy = xsec_sum_dy+(corrPopdy);
        }
  std::cout<<"Mass Integral: "<<xsec_sum_mass<<std::endl;
  std::cout<<"pT Integral: "<<xsec_sum_pt<<std::endl;
  std::cout<<"dY Integral: "<<xsec_sum_dy<<std::endl;
      TCanvas* disp = new TCanvas("disp","disp",900,900);
          disp->Divide(2,2);
     disp->cd(1);
   xsec_mass->Draw("e");
     disp->cd(2);
   xsec_pt->Draw();
     disp->cd(3);
     xsec_dy->Draw("e");
//  dy_data.Draw("e");    
}

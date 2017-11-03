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
  //corrections from NLO PU
  TH1D *acc_eff_shape_nlo = new TH1D("acc_eff_shape_nlo","acc_eff_shape_nlo",nmbins, massbins);
   acc_eff_shape_nlo->SetBinContent(1,0.01953422);
   acc_eff_shape_nlo->SetBinContent(2,0.02265232);
   acc_eff_shape_nlo->SetBinContent(3,0.02203276);
   acc_eff_shape_nlo->SetBinContent(4,0.02269034);
   acc_eff_shape_nlo->SetBinContent(5,0.01853098);
   acc_eff_shape_nlo->SetBinContent(6,0.02843624);
   acc_eff_shape_nlo->SetBinContent(7,0.0459101);
   acc_eff_shape_nlo->SetBinContent(8,0.06545206);
   acc_eff_shape_nlo->SetBinContent(9,0.1080789);
   acc_eff_shape_nlo->SetBinContent(10,0.09860529);
   acc_eff_shape_nlo->SetBinError(1,0.0009018762);
   acc_eff_shape_nlo->SetBinError(2,0.001158591);
   acc_eff_shape_nlo->SetBinError(3,0.001249045);
   acc_eff_shape_nlo->SetBinError(4,0.001176248);
   acc_eff_shape_nlo->SetBinError(5,0.001223613);
   acc_eff_shape_nlo->SetBinError(6,0.001910665);
   acc_eff_shape_nlo->SetBinError(7,0.004393404);
   acc_eff_shape_nlo->SetBinError(8,0.01009379);
   acc_eff_shape_nlo->SetBinError(9,0.04112638);
   acc_eff_shape_nlo->SetBinError(10,0.05770182);
  TH1D *acc_eff_shape_nlo_pt = new TH1D("acc_eff_shape_nlo_pt","acc_eff_shape_nlo_pt",nptbins, ptbins);
   acc_eff_shape_nlo_pt->SetBinContent(1,0.01628423);
   acc_eff_shape_nlo_pt->SetBinContent(2,0.01729379);
   acc_eff_shape_nlo_pt->SetBinContent(3,0.01274548);
   acc_eff_shape_nlo_pt->SetBinContent(4,0.01708455);
   acc_eff_shape_nlo_pt->SetBinContent(5,0.02224971);
   acc_eff_shape_nlo_pt->SetBinContent(6,0.03640555);
   acc_eff_shape_nlo_pt->SetBinContent(7,0.06137423);
   acc_eff_shape_nlo_pt->SetBinContent(8,0.084504);
   acc_eff_shape_nlo_pt->SetBinContent(9,0.1206896);
   acc_eff_shape_nlo_pt->SetBinError(1,0.001461764);
   acc_eff_shape_nlo_pt->SetBinError(2,0.001125337);
   acc_eff_shape_nlo_pt->SetBinError(3,0.0008435943);
   acc_eff_shape_nlo_pt->SetBinError(4,0.001084824);
   acc_eff_shape_nlo_pt->SetBinError(5,0.001368147);
   acc_eff_shape_nlo_pt->SetBinError(6,0.001937851);
   acc_eff_shape_nlo_pt->SetBinError(7,0.003687394);
   acc_eff_shape_nlo_pt->SetBinError(8,0.006525584);
   acc_eff_shape_nlo_pt->SetBinError(9,0.008152426);
  TH1D *acc_eff_shape_nlo_dy = new TH1D("acc_eff_shape_nlo_dy","acc_eff_shape_nlo_dy",ndybins, dybins);
   acc_eff_shape_nlo_dy->SetBinContent(1,0.02742132);
   acc_eff_shape_nlo_dy->SetBinContent(2,0.02546546);
   acc_eff_shape_nlo_dy->SetBinContent(3,0.02520141);
   acc_eff_shape_nlo_dy->SetBinContent(4,0.02654698);
   acc_eff_shape_nlo_dy->SetBinContent(5,0.02461253);
   acc_eff_shape_nlo_dy->SetBinContent(6,0.02482702);
   acc_eff_shape_nlo_dy->SetBinContent(7,0.02566114);
   acc_eff_shape_nlo_dy->SetBinContent(8,0.02265824);
   acc_eff_shape_nlo_dy->SetBinContent(9,0.01357843);
   acc_eff_shape_nlo_dy->SetBinContent(10,0.02730608);
   acc_eff_shape_nlo_dy->SetBinError(1,0.001264985);
   acc_eff_shape_nlo_dy->SetBinError(2,0.001301488);
   acc_eff_shape_nlo_dy->SetBinError(3,0.001427606);
   acc_eff_shape_nlo_dy->SetBinError(4,0.001375087);
   acc_eff_shape_nlo_dy->SetBinError(5,0.001623992);
   acc_eff_shape_nlo_dy->SetBinError(6,0.001666925);
   acc_eff_shape_nlo_dy->SetBinError(7,0.002453789);
   acc_eff_shape_nlo_dy->SetBinError(8,0.003491914);
   acc_eff_shape_nlo_dy->SetBinError(9,0.005164781);
   acc_eff_shape_nlo_dy->SetBinError(10,0.01596601);
        for(int mbin=1; mbin<=nmbins; ++mbin){
          //corrPop = mass_data->GetBinContent(mbin)/((massbins[mbin]-massbins[mbin-1])*((acc_eff_shape_dps->GetBinContent(mbin))));
          corrPop = mass_data->GetBinContent(mbin)/((acc_eff_shape_nlo->GetBinContent(mbin)));
          xsec_mass->SetBinContent(mbin+1,corrPop);
          xsec_sum_mass = xsec_sum_mass+(corrPop);
        }
        for(int ptbin=1; ptbin<=nptbins-1; ++ptbin){
          corrPoppt = pt_data->GetBinContent(ptbin)/((acc_eff_shape_nlo_pt->GetBinContent(ptbin)));
//          std::cout<<pt_data->GetBinContent(ptbin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_pt->GetBinContent(ptbin))+(fracNLO*acc_eff_shape_nlo_pt->GetBinContent(ptbin)))<<" times "<<(ptbins[ptbin]-ptbins[ptbin-1])<<" equals??? "<<corrPoppt<<std::endl;
          xsec_pt->SetBinContent(ptbin,corrPoppt);
          xsec_sum_pt = xsec_sum_pt+(corrPoppt);
        }
        for(int dybin=1; dybin<=ndybins; ++dybin){
          corrPopdy = dy_data->GetBinContent(dybin)/((acc_eff_shape_nlo_dy->GetBinContent(dybin)));
          std::cout<<dy_data->GetBinContent(dybin)<<" over "<<"10  times "<<acc_eff_shape_nlo_dy->GetBinContent(dybin)<<" times "<<(dybins[dybin]-dybins[dybin-1])<<" equals??? "<<corrPopdy<<std::endl;
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

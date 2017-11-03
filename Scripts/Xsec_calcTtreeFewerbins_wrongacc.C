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


int Xsec_calcTtreeFewerbins_systematic() {
  gROOT->Reset();

  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  //  float datapt[60],datady[20],datay[20];
  TChain data("ntuple");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");
  float massbins[]={6.2,7,9,11,14,18,25,30,45,60};
  float massbins2[]={0,6.2,7,9,11,14,18,25,30,45,60};
  float ptbins[]={0,7,12,16,20,25,80};
  float dybins[]={0,0.2,0.4,0.6,0.9,1.3,1.8,2.4,4.5};
  //float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8};
  int nmbins = 9;
  int nmbins2 = 10;
  int nptbins = 6;
  int ndybins = 8;
  int nybins = 9;
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
  float fracDPS = 0.17;
  float fracNLO = 0.83;
  float corrPop = 0;
  float corrPoppt = 0;
  float corrPopdy = 0;
  float corrPopy = 0;
  float xsec_sum_mass = 0;
  float xsec_sum_dy= 0;
  float xsec_sum_y= 0;
  float xsec_sum_pt = 0;

  TH1F *mass_data = new TH1F("mass_data","mass_data",nmbins,massbins); 
  TH1F *pt_data = new TH1F("pt_data","pt_data",nptbins,ptbins); 
  TH1F *dy_data = new TH1F("dy_data","dy_data",ndybins,dybins); 
  TH1F *y_data = new TH1F("y_data","y_data",nybins,ybins); 
  TH1F *xsec_mass = new TH1F("xsec_mass","xsec_mass",nmbins2,massbins2); 
  TH1F *xsec_pt = new TH1F("xsec_pt","xsec_pt",nptbins,ptbins); 
  TH1F *xsec_dy = new TH1F("xsec_dy","xsec_dy",ndybins,dybins); 
  TH1F *xsec_y = new TH1F("xsec_y","xsec_y",nybins,ybins); 
  mass_data->Sumw2();
  pt_data->Sumw2();
  dy_data->Sumw2();
  y_data->Sumw2();
  xsec_mass->Sumw2();
  xsec_pt->Sumw2();
  xsec_dy->Sumw2();
  xsec_y->Sumw2();
  xsec_pt->SetMinimum(0);
  xsec_dy->SetMinimum(0);
  xsec_y->SetMinimum(0);
  data.Add("TMTight_Selected_newAcc.root");
  //data.Draw("FourMu_Mass>>mass_data","","egoff"); 
  //data.Draw("FourMu_pT>>pt_data","","egoff"); 
  //data.Draw("Psi1To2_dY>>dy_data","","egoff"); 
  //data.Draw("abs(FourMu_Rapidity)>>y_data","","egoff"); 
  mass_data->SetBinContent(1,76.); 
  mass_data->SetBinContent(2,98.);   
  mass_data->SetBinContent(3,52.);
  mass_data->SetBinContent(4,44.);
  mass_data->SetBinContent(5,43.);
  mass_data->SetBinContent(6,56.);
  mass_data->SetBinContent(7,42.);
  mass_data->SetBinContent(8,46.);
  mass_data->SetBinContent(9,18.);
  pt_data->SetBinContent(1,68.);
  pt_data->SetBinContent(2,44.);
  pt_data->SetBinContent(3,43.);
  pt_data->SetBinContent(4,69.);
  pt_data->SetBinContent(5,108.);
  pt_data->SetBinContent(6,141.);
  dy_data->SetBinContent(1,181.);
  dy_data->SetBinContent(2,102.);
  dy_data->SetBinContent(3,54.);
  dy_data->SetBinContent(4,38.);
  dy_data->SetBinContent(5,33.);
  dy_data->SetBinContent(6,23.);
  dy_data->SetBinContent(7,23.);
  dy_data->SetBinContent(8,23.);
  y_data->SetBinContent(1,43.);
  y_data->SetBinContent(2,55.);
  y_data->SetBinContent(3,53.);
  y_data->SetBinContent(4,59.);
  y_data->SetBinContent(5,53.);
  y_data->SetBinContent(6,46.);
  y_data->SetBinContent(7,65.);
  y_data->SetBinContent(8,68.);
  y_data->SetBinContent(9,28.);


  //corrections from DPS PU
  TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",nmbins, massbins);
   acc_eff_shape_dps->SetBinContent(1,1.5822e-02);
   acc_eff_shape_dps->SetBinContent(2,8.54437678586354547e-03);
   acc_eff_shape_dps->SetBinContent(3,7.99659469114371267e-03);
   acc_eff_shape_dps->SetBinContent(4,7.54980701508833982e-03);
   acc_eff_shape_dps->SetBinContent(5,1.56991186658943377e-02);
   acc_eff_shape_dps->SetBinContent(6,2.26809415435264700e-02);
   acc_eff_shape_dps->SetBinContent(7,2.36933355442586237e-02);
   acc_eff_shape_dps->SetBinContent(8,1.61915098926165013e-02);
   acc_eff_shape_dps->SetBinContent(9,1.86011380341726228e-02);
   acc_eff_shape_dps->SetBinError(1,3.12276556879868914e-03);
   acc_eff_shape_dps->SetBinError(2,1.75768005086097295e-03);
   acc_eff_shape_dps->SetBinError(3,2.23172284817075434e-03);
   acc_eff_shape_dps->SetBinError(4,1.52563594350197990e-03);
   acc_eff_shape_dps->SetBinError(5,2.80730488805274164e-03);
   acc_eff_shape_dps->SetBinError(6,3.87701467898636997e-03);
   acc_eff_shape_dps->SetBinError(7,3.74546751326509204e-03);
   acc_eff_shape_dps->SetBinError(8,2.39951381995248507e-03);
   acc_eff_shape_dps->SetBinError(9,1.86011380341726228e-02);
   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",nptbins, ptbins);
   acc_eff_shape_dps_pt->SetBinContent(1,0.01703218);
   acc_eff_shape_dps_pt->SetBinContent(2,0.01226194);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01311947);
   acc_eff_shape_dps_pt->SetBinContent(4,0.02308662);
   acc_eff_shape_dps_pt->SetBinContent(5,0.04539563);
   acc_eff_shape_dps_pt->SetBinContent(6,0.03832395);
   acc_eff_shape_dps_pt->SetBinError(1,0.002059571);
   acc_eff_shape_dps_pt->SetBinError(2,0.001689715);
   acc_eff_shape_dps_pt->SetBinError(3,0.001775105);
   acc_eff_shape_dps_pt->SetBinError(4,0.003627287);
   acc_eff_shape_dps_pt->SetBinError(5,0.0102709);
   acc_eff_shape_dps_pt->SetBinError(6,0.0193536);
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",ndybins, dybins);
   acc_eff_shape_dps_dy->SetBinContent(1,0.01274345);
   acc_eff_shape_dps_dy->SetBinContent(2,0.01561734);
   acc_eff_shape_dps_dy->SetBinContent(3,0.01254353);
   acc_eff_shape_dps_dy->SetBinContent(4,0.02086927);
   acc_eff_shape_dps_dy->SetBinContent(5,0.02324256);
   acc_eff_shape_dps_dy->SetBinContent(6,0.02268239);
   acc_eff_shape_dps_dy->SetBinContent(7,0.02457444);
   acc_eff_shape_dps_dy->SetBinContent(8,0.01025183);
   acc_eff_shape_dps_dy->SetBinError(1,0.002507535);
   acc_eff_shape_dps_dy->SetBinError(2,0.003200905);
   acc_eff_shape_dps_dy->SetBinError(3,0.003490375);
   acc_eff_shape_dps_dy->SetBinError(4,0.004196635);
   acc_eff_shape_dps_dy->SetBinError(5,0.004133712);
   acc_eff_shape_dps_dy->SetBinError(6,0.003856762);
   acc_eff_shape_dps_dy->SetBinError(7,0.003862536);
   acc_eff_shape_dps_dy->SetBinError(8,0.001515608);
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",nybins, ybins);
   acc_eff_shape_dps_y->SetBinContent(1,0.01291221);
   acc_eff_shape_dps_y->SetBinContent(2,0.01405488);
   acc_eff_shape_dps_y->SetBinContent(3,0.01898584);
   acc_eff_shape_dps_y->SetBinContent(4,0.02385327);
   acc_eff_shape_dps_y->SetBinContent(5,0.0207437);
   acc_eff_shape_dps_y->SetBinContent(6,0.02599477);
   acc_eff_shape_dps_y->SetBinContent(7,0.02117483);
   acc_eff_shape_dps_y->SetBinContent(8,0.01184234);
   acc_eff_shape_dps_y->SetBinContent(9,0.01030604);
   acc_eff_shape_dps_y->SetBinError(1,0.001837813);
   acc_eff_shape_dps_y->SetBinError(2,0.002628202);
   acc_eff_shape_dps_y->SetBinError(3,0.00375861);
   acc_eff_shape_dps_y->SetBinError(4,0.004481958);
   acc_eff_shape_dps_y->SetBinError(5,0.004369992);
   acc_eff_shape_dps_y->SetBinError(6,0.00516383);
   acc_eff_shape_dps_y->SetBinError(7,0.004367815);
   acc_eff_shape_dps_y->SetBinError(8,0.002732858);
   acc_eff_shape_dps_y->SetBinError(9,0.002768561);

   TH1D *acc_eff_shape_nlo = new TH1D("acc_eff_shape_nlo","acc_eff_shape_nlo",nmbins, massbins);
   acc_eff_shape_nlo->SetBinContent(0,0.05537891);
   acc_eff_shape_nlo->SetBinContent(1,0.04676272);
   acc_eff_shape_nlo->SetBinContent(2,0.05216534);
   acc_eff_shape_nlo->SetBinContent(3,0.06241625);
   acc_eff_shape_nlo->SetBinContent(4,0.05173734);
   acc_eff_shape_nlo->SetBinContent(5,0.06125286);
   acc_eff_shape_nlo->SetBinContent(6,0.0784159);
   acc_eff_shape_nlo->SetBinContent(7,0.1175085);
   acc_eff_shape_nlo->SetBinContent(8,0.2054267);
   acc_eff_shape_nlo->SetBinContent(9,0.2383271);
   acc_eff_shape_nlo->SetBinError(0,0.009495715);
   acc_eff_shape_nlo->SetBinError(1,0.002030104);
   acc_eff_shape_nlo->SetBinError(2,0.002828119);
   acc_eff_shape_nlo->SetBinError(3,0.004202965);
   acc_eff_shape_nlo->SetBinError(4,0.004644857);
   acc_eff_shape_nlo->SetBinError(5,0.007225524);
   acc_eff_shape_nlo->SetBinError(6,0.014457);
   acc_eff_shape_nlo->SetBinError(7,0.05343538);
   acc_eff_shape_nlo->SetBinError(8,0.1248392);
   acc_eff_shape_nlo->SetBinError(9,0.2383271);

   TH1D *acc_eff_shape_nlo_pt = new TH1D("acc_eff_shape_nlo_pt","acc_eff_shape_nlo_pt",nptbins, ptbins);
   acc_eff_shape_nlo_pt->SetBinContent(1,0.04872639);
   acc_eff_shape_nlo_pt->SetBinContent(2,0.04332501);
   acc_eff_shape_nlo_pt->SetBinContent(3,0.02950928);
   acc_eff_shape_nlo_pt->SetBinContent(4,0.04294508);
   acc_eff_shape_nlo_pt->SetBinContent(5,0.08541202);
   acc_eff_shape_nlo_pt->SetBinContent(6,0.1763979);
   acc_eff_shape_nlo_pt->SetBinError(1,0.003963494);
   acc_eff_shape_nlo_pt->SetBinError(2,0.003743325);
   acc_eff_shape_nlo_pt->SetBinError(3,0.002436131);
   acc_eff_shape_nlo_pt->SetBinError(4,0.002820824);
   acc_eff_shape_nlo_pt->SetBinError(5,0.004958545);
   acc_eff_shape_nlo_pt->SetBinError(6,0.009018198);

   TH1D *acc_eff_shape_nlo_dy = new TH1D("acc_eff_shape_nlo_dy","acc_eff_shape_nlo_dy",ndybins, dybins);
   acc_eff_shape_nlo_dy->SetBinContent(1,0.06107335);
   acc_eff_shape_nlo_dy->SetBinContent(2,0.06105638);
   acc_eff_shape_nlo_dy->SetBinContent(3,0.07010931);
   acc_eff_shape_nlo_dy->SetBinContent(4,0.05586374);
   acc_eff_shape_nlo_dy->SetBinContent(5,0.05754681);
   acc_eff_shape_nlo_dy->SetBinContent(6,0.05368312);
   acc_eff_shape_nlo_dy->SetBinContent(7,0.03392556);
   acc_eff_shape_nlo_dy->SetBinContent(8,0.1079217);
   acc_eff_shape_nlo_dy->SetBinError(1,0.002614834);
   acc_eff_shape_nlo_dy->SetBinError(2,0.003264542);
   acc_eff_shape_nlo_dy->SetBinError(3,0.004646877);
   acc_eff_shape_nlo_dy->SetBinError(4,0.004951825);
   acc_eff_shape_nlo_dy->SetBinError(5,0.00669995);
   acc_eff_shape_nlo_dy->SetBinError(6,0.009776569);
   acc_eff_shape_nlo_dy->SetBinError(7,0.01530636);
   acc_eff_shape_nlo_dy->SetBinError(8,0.0640478);

   TH1D *acc_eff_shape_nlo_y = new TH1D("acc_eff_shape_nlo_y","acc_eff_shape_nlo_y",nybins, ybins);
   acc_eff_shape_nlo_y->SetBinContent(1,0.06497778);
   acc_eff_shape_nlo_y->SetBinContent(2,0.06522329);
   acc_eff_shape_nlo_y->SetBinContent(3,0.07716298);
   acc_eff_shape_nlo_y->SetBinContent(4,0.07420639);
   acc_eff_shape_nlo_y->SetBinContent(5,0.08707309);
   acc_eff_shape_nlo_y->SetBinContent(6,0.06424597);
   acc_eff_shape_nlo_y->SetBinContent(7,0.06556989);
   acc_eff_shape_nlo_y->SetBinContent(8,0.05282088);
   acc_eff_shape_nlo_y->SetBinContent(9,0.03683992);
   acc_eff_shape_nlo_y->SetBinContent(10,0.01428942);
   acc_eff_shape_nlo_y->SetBinError(1,0.00645243);
   acc_eff_shape_nlo_y->SetBinError(2,0.006360834);
   acc_eff_shape_nlo_y->SetBinError(3,0.006918267);
   acc_eff_shape_nlo_y->SetBinError(4,0.0065709);
   acc_eff_shape_nlo_y->SetBinError(5,0.006692747);
   acc_eff_shape_nlo_y->SetBinError(6,0.005175412);
   acc_eff_shape_nlo_y->SetBinError(7,0.00457376);
   acc_eff_shape_nlo_y->SetBinError(8,0.003662358);
   acc_eff_shape_nlo_y->SetBinError(9,0.00339621);
   acc_eff_shape_nlo_y->SetBinError(10,0.005439343);

   TH1D *dps_frac_mass= new TH1D("dps_frac_mass","dps_frac_mass",nmbins, massbins);
dps_frac_mass->SetBinContent(1,0.0159351);
dps_frac_mass->SetBinContent(2,0.0100848);
dps_frac_mass->SetBinContent(3,0.014491);
dps_frac_mass->SetBinContent(4,0.0330867);
dps_frac_mass->SetBinContent(5,0.0789651);
dps_frac_mass->SetBinContent(6,0.107745);
dps_frac_mass->SetBinContent(7,0.169574);
dps_frac_mass->SetBinContent(8,0.28898);
dps_frac_mass->SetBinContent(9,0.505784);

   TH1D *dps_frac_pt= new TH1D("dps_frac_pt","dps_frac_pt",nptbins, ptbins);
dps_frac_pt->SetBinContent(1,0.159541);
dps_frac_pt->SetBinContent(2,0.141605);
dps_frac_pt->SetBinContent(3,0.135997);
dps_frac_pt->SetBinContent(4,0.0687008);
dps_frac_pt->SetBinContent(5,0.0267744);
dps_frac_pt->SetBinContent(6,0.00406399);

   TH1D *dps_frac_dy= new TH1D("dps_frac_dy","dps_frac_dy",ndybins, dybins);
dps_frac_dy->SetBinContent(1,0.0193123);
dps_frac_dy->SetBinContent(2,0.0275677);
dps_frac_dy->SetBinContent(3,0.0229501);
dps_frac_dy->SetBinContent(4,0.0752538);
dps_frac_dy->SetBinContent(5,0.152216);
dps_frac_dy->SetBinContent(6,0.324982);
dps_frac_dy->SetBinContent(7,0.777612);
dps_frac_dy->SetBinContent(8,0.867346);

   TH1D *dps_frac_y = new TH1D("dps_frac_y","dps_frac_y",nybins, ybins);
dps_frac_y->SetBinContent(1,0.164869);
dps_frac_y->SetBinContent(2,0.0994335);
dps_frac_y->SetBinContent(3,0.0764157);
dps_frac_y->SetBinContent(4,0.082791);
dps_frac_y->SetBinContent(5,0.0506051);
dps_frac_y->SetBinContent(6,0.0633223);
dps_frac_y->SetBinContent(7,0.0446446);
dps_frac_y->SetBinContent(8,0.0356755);
dps_frac_y->SetBinContent(9,0.0466506);

  for(int mbin=1; mbin<=nmbins; ++mbin){
    corrPop = mass_data->GetBinContent(mbin)/(0.0593*0.0593*20.339*((dps_frac_mass->GetBinContent(mbin)*acc_eff_shape_dps->GetBinContent(mbin))+((1-dps_frac_mass->GetBinContent(mbin))*acc_eff_shape_nlo->GetBinContent(mbin)))*(massbins[mbin]-massbins[mbin-1]));
    xsec_mass->SetBinContent(mbin+1,corrPop*1e-6);
    xsec_sum_mass = xsec_sum_mass+(corrPop*1e-6*(massbins[mbin]-massbins[mbin-1]));
    xsec_mass->SetBinError(mbin+1, xsec_mass->GetBinContent(mbin)/sqrt(mass_data->GetBinContent(mbin)));
  }
  for(int ptbin=1; ptbin<=nptbins; ++ptbin){
    corrPoppt = pt_data->GetBinContent(ptbin)/(pow(0.0593,2)*20.339*(dps_frac_pt->GetBinContent(ptbin)*acc_eff_shape_dps_pt->GetBinContent(ptbin)+(1-(dps_frac_pt->GetBinContent(ptbin)))*acc_eff_shape_nlo_pt->GetBinContent(ptbin))*(ptbins[ptbin]-ptbins[ptbin-1]));
//            std::cout<<pt_data->GetBinContent(ptbin)<<" over "<<0.0593*0.0593*20.339<<" times "<<dps_frac_pt->GetBinContent(ptbin)<<" times "<<acc_eff_shape_dps_pt->GetBinContent(ptbin)<<" + "<<(1-(dps_frac_pt->GetBinContent(ptbin)))<<" times "<<acc_eff_shape_nlo_pt->GetBinContent(ptbin)<<" times "<<(ptbins[ptbin]-ptbins[ptbin-1])<<" equals??? "<<corrPoppt<<std::endl;
//            std::cout<<pt_data->GetBinContent(ptbin)<<" over "<<0.0593*0.0593*20.339<<" times "<<fracDPS<<" times "<<acc_eff_shape_dps_pt->GetBinContent(ptbin)<<" + "<<fracNLO<<" times "<<acc_eff_shape_nlo_pt->GetBinContent(ptbin)<<" times "<<(ptbins[ptbin]-ptbins[ptbin-1])<<" equals??? "<<corrPoppt<<std::endl;
    xsec_pt->SetBinContent(ptbin,corrPoppt*1e-6);
    xsec_sum_pt = xsec_sum_pt+(corrPoppt*1e-6*(ptbins[ptbin]-ptbins[ptbin-1]));
    xsec_pt->SetBinError(ptbin, xsec_pt->GetBinContent(ptbin)/sqrt(pt_data->GetBinContent(ptbin)));
  }
  for(int dybin=1; dybin<=ndybins; ++dybin){
    corrPopdy = dy_data->GetBinContent(dybin)/(pow(0.0593,2)*20.339*(dps_frac_dy->GetBinContent(dybin)*acc_eff_shape_dps_dy->GetBinContent(dybin)+(1-dps_frac_dy->GetBinContent(dybin))*acc_eff_shape_nlo_dy->GetBinContent(dybin))*(dybins[dybin]-dybins[dybin-1]));
    //          std::cout<<dy_data->GetBinContent(dybin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_dy->GetBinContent(dybin))+(fracNLO*acc_eff_shape_nlo_dy->GetBinContent(dybin)))<<" times "<<(dybins[dybin]-dybins[dybin-1])<<" equals??? "<<corrPopdy<<std::endl;
    xsec_dy->SetBinContent(dybin,corrPopdy*1e-6);
    xsec_sum_dy = xsec_sum_dy+(corrPopdy*1e-6*(dybins[dybin]-dybins[dybin-1]));
    xsec_dy->SetBinError(dybin, xsec_dy->GetBinContent(dybin)/sqrt(dy_data->GetBinContent(dybin)));
  }
  for(int ybin=1; ybin<=nybins; ++ybin){
    corrPopy = y_data->GetBinContent(ybin)/(pow(0.0593,2)*20.339*(dps_frac_y->GetBinContent(ybin)*acc_eff_shape_dps_y->GetBinContent(ybin)+(1-dps_frac_y->GetBinContent(ybin))*acc_eff_shape_nlo_y->GetBinContent(ybin))*(ybins[ybin]-ybins[ybin-1]));
    //          std::cout<<dy_data->GetBinContent(dybin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_dy->GetBinContent(dybin))+(fracNLO*acc_eff_shape_nlo_dy->GetBinContent(dybin)))<<" times "<<(dybins[dybin]-dybins[dybin-1])<<" equals??? "<<corrPopdy<<std::endl;
    xsec_y->SetBinContent(ybin,corrPopy*1e-6);
    xsec_sum_y = xsec_sum_y+(corrPopy*1e-6*(ybins[ybin]-ybins[ybin-1]));
    xsec_y->SetBinError(ybin, xsec_y->GetBinContent(ybin)/sqrt(y_data->GetBinContent(ybin)));
  }
  std::cout<<"Mass Integral: "<<xsec_sum_mass<<std::endl;
  std::cout<<"pT Integral: "<<xsec_sum_pt<<std::endl;
  std::cout<<"dY Integral: "<<xsec_sum_dy<<std::endl;
  std::cout<<"Y Integral: "<<xsec_sum_y<<std::endl;
  TCanvas* disp = new TCanvas("disp","disp",900,900);
  disp->Divide(2,2);
  disp->cd(1);
  disp_1->SetLeftMargin(0.15);
  xsec_mass->SetXTitle("M_{J/#psi J/#psi} (GeV/c^{2})");
  xsec_mass->SetYTitle("d#sigma/dM_{J/#psi J/#psi} (nb/(GeV/c^{2}))");
  xsec_mass->SetTitleOffset(1.6,"Y");
  xsec_mass->Draw("e1");
  disp->cd(2);
  disp_2->SetLeftMargin(0.15);
  xsec_pt->SetXTitle("p_{T}^{J/#psi J/#psi} (GeV/c)");
  xsec_pt->SetYTitle("d#sigma/dp_{T}^{J/#psi J/#psi} (nb/(GeV/c))");
  xsec_pt->SetTitleOffset(1.7,"Y");
  xsec_pt->Draw("e1");
  disp->cd(3);
  disp_3->SetLeftMargin(0.15);
  xsec_dy->SetXTitle("|#Delta y| between J/#psi");
  xsec_dy->SetYTitle("d#sigma/d|#Delta y| (nb)");
  xsec_dy->SetTitleOffset(1.6,"Y");
  xsec_dy->Draw("e1");
  disp->cd(4);
  disp_4->SetLeftMargin(0.15);
  xsec_y->SetXTitle("|Rapidity|_{J/#psi J/#psi}");
  xsec_y->SetYTitle("d#sigma/d|y| (nb)");
  xsec_y->SetTitleOffset(1.6,"Y");
  xsec_y->Draw("e1");
  //  dy_data.Draw("e");    
}

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


int binfit_ttree_genlvl_3shapes_fast() {
  gROOT->Reset();
  gErrorIgnoreLevel=kError;
  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  float datamass[81]={0};
  int dpsmass[81]={0};
  int spsmass[81]={0};
  float nlomass[81]={0.0};
  int nloggmass[81]={0};
  int nlogumass[81]={0};
  int nlougmass[81]={0};
  //  float datapt[60],datady[20],datay[20];
  TChain dps("Events");
  TChain nlogg("Events");
  TChain sps("Events");

//  dps.Add("Modified_Input_To_Fit_2012DPS_TMTight_3MuL3Match.root");
  dps.Add("genevents/GENEventTree_dps_pu_old_1.root");
  dps.Add("genevents/GENEventTree_dps_pu_old_2.root");
  dps.Add("genevents/GENEventTree_dps_pu_old_3.root");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_1.root");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_2.root");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_3.root");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_4.root");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_5.root");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_6_1.root ");
  nlogg.Add("genevents/GENEventTree_pythia8_PU_OffsetBS_fixp3_6_2.root ");
  sps.Add("genevents/GENEventTree_SPSLO_xl21_1.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl21_2.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl22_1.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl22_2.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl23_1.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl23_2.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl26_1.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl26_2.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl27_1.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl27_2.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl28_1.root");
  sps.Add("genevents/GENEventTree_SPSLO_xl28_2.root");
  

  float massbins[]={6.2,7,9,11,14,18,25,30,60};
  float ptbins[]={0.,7,12,16,20,25,50,80};
  float dybins[]={0.,0.2,0.4,0.6,0.9,1.3,1.8,2.4,3.8};
  //float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  float ybins[]={0.,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8};
  int nmbins = 8; 
  int nptbins = 7;
  int ndybins = 8;
  int nybins = 9;
  //float massbins[]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60};
  //float ptbins[]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
  //float dybins[]={0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5};
  //float ybins[]={0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8};
  //  int nmbins = 30;
  //  int nptbins = 40;
  //  int ndybins = 45;
  //  int nybins = 18;
  //int nybins = 20;
    int mbinerr = -99;
    int ptbinerr = -99;
    int dybinerr = -99;
    int ybinerr = -99;
  TH1F *mass_data = new TH1F("mass_data","mass_data",nmbins,massbins); 
  TH1F *mass_dps = new TH1F("mass_dps","mass_dps",nmbins,massbins); 
  TH1F *mass_nlogg = new TH1F("mass_nlogg","mass_nlogg",nmbins,massbins); 
  TH1F *mass_nlo = new TH1F("mass_nlo","mass_nlo",nmbins,massbins); 
  TH1F *mass_sps = new TH1F("mass_sps","mass_sps",nmbins,massbins); 
  TH1F *mass_width = new TH1F("mass_width","mass_width",nmbins,massbins); 
  TH1F *pt_data = new TH1F("pt_data","pt_data",nptbins,ptbins); 
  TH1F *pt_dps = new TH1F("pt_dps","pt_dps",nptbins,ptbins); 
  TH1F *pt_nlogg = new TH1F("pt_nlogg","pt_nlogg",nptbins,ptbins); 
  TH1F *pt_nlo = new TH1F("pt_nlo","pt_nlo",nptbins,ptbins); 
  TH1F *pt_sps = new TH1F("pt_sps","pt_sps",nptbins,ptbins); 
  TH1F *pt_width = new TH1F("pt_width","pt_width",nptbins,ptbins); 
  TH1F *dy_data = new TH1F("dy_data","dy_data",ndybins,dybins); 
  TH1F *dy_dps = new TH1F("dy_dps","dy_dps",ndybins,dybins); 
  TH1F *dy_nlogg = new TH1F("dy_nlogg","dy_nlogg",ndybins,dybins); 
  TH1F *dy_nlo = new TH1F("dy_nlo","dy_nlo",ndybins,dybins); 
  TH1F *dy_sps = new TH1F("dy_sps","dy_sps",ndybins,dybins); 
  TH1F *dy_width = new TH1F("dy_width","dy_width",ndybins,dybins); 
  TH1F *y_data = new TH1F("y_data","y_data",nybins,ybins); 
  TH1F *y_dps = new TH1F("y_dps","y_dps",nybins,ybins); 
  TH1F *y_nlogg = new TH1F("y_nlogg","y_nlogg",nybins,ybins); 
  TH1F *y_nlo = new TH1F("y_nlo","y_nlo",nybins,ybins); 
  TH1F *y_sps = new TH1F("y_sps","y_sps",nybins,ybins); 
  TH1F *y_width = new TH1F("y_width","y_width",nybins,ybins); 

  mass_data->SetBinContent(1,47.43199);
  mass_data->SetBinContent(2,22.88957);
  mass_data->SetBinContent(3,10.52912);
  mass_data->SetBinContent(4,7.297879);
  mass_data->SetBinContent(5,4.679995);
  mass_data->SetBinContent(6,2.752399);
  mass_data->SetBinContent(7,2.321633);
  mass_data->SetBinContent(8,0.4013286);
  mass_data->SetBinError(1,6.281534);
  mass_data->SetBinError(2,2.358319);
  mass_data->SetBinError(3,1.509835);
  mass_data->SetBinError(4,1.177612);
  mass_data->SetBinError(5,0.7126356);
  mass_data->SetBinError(6,0.3761612);
  mass_data->SetBinError(7,0.3408355);
  mass_data->SetBinError(8,0.05351048);
  pt_data->SetBinContent(1,5.511632);
  pt_data->SetBinContent(2,5.816723);
  pt_data->SetBinContent(3,9.881093);
  pt_data->SetBinContent(4,9.516933);
  pt_data->SetBinContent(5,5.7525);
  pt_data->SetBinContent(6,0.676141);
  pt_data->SetBinContent(7,0.06380682);
  pt_data->SetBinError(1,0.6928909);
  pt_data->SetBinError(2,0.9048236);
  pt_data->SetBinError(3,1.589567);
  pt_data->SetBinError(4,1.189617);
  pt_data->SetBinError(5,0.607507);
  pt_data->SetBinError(6,0.06388734);
  pt_data->SetBinError(7,0.01890572);
  dy_data->SetBinContent(1,353.6836);
  dy_data->SetBinContent(2,208.9763);
  dy_data->SetBinContent(3,100.067);
  dy_data->SetBinContent(4,59.72152);
  dy_data->SetBinContent(5,39.28412);
  dy_data->SetBinContent(6,23.76292);
  dy_data->SetBinContent(7,22.76975);
  dy_data->SetBinContent(8,15.7347);
  //dy_data->SetBinContent(8,10.52381);
  dy_data->SetBinError(1,28.61261);
  dy_data->SetBinError(2,21.71715);
  dy_data->SetBinError(3,14.11659);
  dy_data->SetBinError(4,10.30196);
  dy_data->SetBinError(5,6.846661);
  dy_data->SetBinError(6,5.372485);
  dy_data->SetBinError(7,4.64503);
  dy_data->SetBinError(8,3.4205);
  //dy_data->SetBinError(8,2.287784);
  y_data->SetBinContent(1,96.87107);
  y_data->SetBinContent(2,110.5371);
  y_data->SetBinContent(3,89.27422);
  y_data->SetBinContent(4,101.8527);
  y_data->SetBinContent(5,77.61348);
  y_data->SetBinContent(6,95.7653);
  y_data->SetBinContent(7,137.6607);
  y_data->SetBinContent(8,168.4277);
  y_data->SetBinContent(9,120.5354);
  y_data->SetBinError(1,14.97098);
  y_data->SetBinError(2,15.67618);
  y_data->SetBinError(3,12.3992);
  y_data->SetBinError(4,13.63791);
  y_data->SetBinError(5,10.98304);
  y_data->SetBinError(6,14.26707);
  y_data->SetBinError(7,17.44995);
  y_data->SetBinError(8,23.01054);
  y_data->SetBinError(9,22.7678);

  mass_width->SetBinContent(1,0.8);
  mass_width->SetBinContent(2,2.);
  mass_width->SetBinContent(3,2.);
  mass_width->SetBinContent(4,3.);
  mass_width->SetBinContent(5,4.);
  mass_width->SetBinContent(6,5.);
  mass_width->SetBinContent(7,5.);
  mass_width->SetBinContent(8,30.);
  pt_width->SetBinContent(1,7.);
  pt_width->SetBinContent(2,5.);
  pt_width->SetBinContent(3,4.);
  pt_width->SetBinContent(4,4.);
  pt_width->SetBinContent(5,5.);
  pt_width->SetBinContent(6,25.);
  pt_width->SetBinContent(7,30.);
  dy_width->SetBinContent(1,0.2);
  dy_width->SetBinContent(2,0.2);
  dy_width->SetBinContent(3,0.2);
  dy_width->SetBinContent(4,0.3);
  dy_width->SetBinContent(5,0.4);
  dy_width->SetBinContent(6,0.5);
  dy_width->SetBinContent(7,0.6);
  dy_width->SetBinContent(8,1.4);
  //dy_width->SetBinContent(8,2.1);
  y_width->SetBinContent(1,0.2);
  y_width->SetBinContent(2,0.2);
  y_width->SetBinContent(3,0.2);
  y_width->SetBinContent(4,0.2);
  y_width->SetBinContent(5,0.2);
  y_width->SetBinContent(6,0.2);
  y_width->SetBinContent(7,0.2);
  y_width->SetBinContent(8,0.2);
  y_width->SetBinContent(9,0.2);

  dps.Draw("FourMu_Mass >> mass_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  nlogg.Draw("FourMu_Mass >> mass_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  sps.Draw("FourMu_Mass >> mass_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  mass_dps->Divide(mass_width);
  mass_nlogg->Divide(mass_width);
  mass_sps->Divide(mass_width);
  datamass[0]=mass_data->Integral("width");
  std::cout<<datamass[0]<<std::endl;
  dpsmass[0]=mass_dps->Integral("width");
  spsmass[0]=mass_sps->Integral("width");
  nloggmass[0]=mass_nlogg->Integral("width");
  nlomass[0]=nloggmass[0];

  scaledps = datamass[0]/ (float) dpsmass[0];
  scalesps= datamass[0]/ (float) spsmass[0];
  scalenlo= datamass[0]/ (float) nloggmass[0];
  float Chi2=0;
  float minchi2norm=99999999.9;
  float minchi2=9999999.9;
  float mina, minb, minc, minan, minbn, mincn;

  //   Chi2 = Chi2 + pow((datamass[1] - (0.00*scaledps*dpsmass[1] + 0.0*scalesps*spsmass[1] + 0.0*scalenlo*nlomass[1])),2)/sqrt(datamass[1]);
  //  std::cout<<"Scale: " <<datamass[0]<<" " << dpsmass[0]<<" "<<scaledps<<" "<<scalesps<<" "<<scalenlo<<" "<<std::endl;
        dps.Draw("FourMu_Mass >> mass_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("FourMu_Mass >> mass_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("FourMu_Mass >> mass_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        dps.Draw("FourMu_pT >> pt_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("FourMu_pT >> pt_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("FourMu_pT >> pt_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        dps.Draw("Psi1To2_dY >> dy_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("Psi1To2_dY >> dy_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("Psi1To2_dY >> dy_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        dps.Draw("abs(FourMu_Rapidity)>> y_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("abs(FourMu_Rapidity) >> y_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.0)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("abs(FourMu_Rapidity) >> y_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.0)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  mass_dps->Divide(mass_width);
  mass_nlogg->Divide(mass_width);
  mass_sps->Divide(mass_width);
  pt_dps->Divide(pt_width);
  pt_nlogg->Divide(pt_width);
  pt_sps->Divide(pt_width);
  dy_dps->Divide(dy_width);
  dy_nlogg->Divide(dy_width);
  dy_sps->Divide(dy_width);
  y_dps->Divide(y_width);
  y_nlogg->Divide(y_width);
  y_sps->Divide(y_width);
  for(float a=0.0; a<0.5; a=a+0.01){
    for(float b=0.0; b<0.5; b=b+0.01){
        for(int mbin=1; mbin<=nmbins; ++mbin){
        //  Chi2=Chi2 + pow((mass_data->GetBinContent(mbin) - (a*scaledps*mass_dps->GetBinContent(mbin) + b*scalesps*mass_sps->GetBinContent(mbin) + (1.-(a+b))*scalenlo*mass_nlogg->GetBinContent(mbin)))/sqrt(pow(mass_data->GetBinError(mbin),2)+pow((a*scaledps*mass_dps->GetBinContent(mbin) + b*scalesps*mass_sps->GetBinContent(mbin) + (1.-(a+b))*scalenlo*mass_nlogg->GetBinContent(mbin)*0.3),2)),2);
          }
        for(int ptbin=1; ptbin<=nptbins; ++ptbin){
          //Chi2=Chi2 + pow((pt_data->GetBinContent(ptbin) - (a*scaledps*pt_dps->GetBinContent(ptbin) + b*scalesps*pt_sps->GetBinContent(ptbin) + (1.-(a+b))*scalenlo*pt_nlogg->GetBinContent(ptbin)))/pt_data->GetBinError(ptbin),2);
          Chi2=Chi2 + pow((pt_data->GetBinContent(ptbin) - (a*scaledps*pt_dps->GetBinContent(ptbin) + b*scalesps*pt_sps->GetBinContent(ptbin) + (1.-(a+b))*scalenlo*pt_nlogg->GetBinContent(ptbin)))/sqrt(pow(pt_data->GetBinError(ptbin),2)+pow((a*scaledps*pt_dps->GetBinContent(ptbin) + b*scalesps*pt_sps->GetBinContent(ptbin) + (1.-(a+b))*scalenlo*pt_nlogg->GetBinContent(ptbin)*0.3),2)),2);
            //         std::cout<<pt_data->GetBinContent(ptbin)<<std::endl;
        }
        for(int dybin=1; dybin<=ndybins; ++dybin){
          //Chi2=Chi2 + pow((dy_data->GetBinContent(dybin) - (a*scaledps*dy_dps->GetBinContent(dybin) + b*scalesps*dy_sps->GetBinContent(dybin) + (1.-(a+b))*scalenlo*dy_nlogg->GetBinContent(dybin)))/sqrt(pow(dy_data->GetBinError(dybin),2)+pow((a*scaledps*dy_dps->GetBinContent(dybin) + b*scalesps*dy_sps->GetBinContent(dybin) + (1.-(a+b))*scalenlo*dy_nlogg->GetBinContent(dybin)*0.3),2)),2);
          //Chi2=Chi2 + pow((dy_data->GetBinContent(dybin) - (a*scaledps*dy_dps->GetBinContent(dybin) + b*scalesps*dy_sps->GetBinContent(dybin) + (1.-(a+b))*scalenlo*dy_nlogg->GetBinContent(dybin)))/dy_data->GetBinError(dybin),2);
          //           std::cout<<Chi2<<std::endl;
        }
        for(int ybin=1; ybin<=nybins; ++ybin){
          Chi2=Chi2 + pow((y_data->GetBinContent(ybin) - (a*scaledps*y_dps->GetBinContent(ybin) + b*scalesps*y_sps->GetBinContent(ybin) + (1.-(a+b))*scalenlo*y_nlogg->GetBinContent(ybin)))/sqrt(pow(y_data->GetBinError(ybin),2)+pow((a*scaledps*y_dps->GetBinContent(ybin) + b*scalesps*y_sps->GetBinContent(ybin) + (1.-(a+b))*scalenlo*y_nlogg->GetBinContent(ybin)*0.3),2)),2);
          //Chi2=Chi2 + pow((y_data->GetBinContent(ybin) - (a*scaledps*y_dps->GetBinContent(ybin) + b*scalesps*y_sps->GetBinContent(ybin) + (1.-(a+b))*scalenlo*y_nlogg->GetBinContent(ybin)))/y_data->GetBinError(ybin),2);
          //           std::cout<<Chi2<<std::endl;
        }
        //        std::cout<<"a, b, c: "<<a<<" "<<b<<" "<<c<<" Chi2: "<<Chi2<<std::endl;
        std::cout<<a<<" "<<b<<" "<<Chi2<<std::endl;
        if (Chi2<=minchi2){
          minchi2=Chi2; minan = a; minbn = b; mincn=(1.-(a+b)); 
        }
        //        std::cout<<a<<" "<<b<<" "<<c<<" "<<Chi2<<std::endl;
        Chi2=0;
    }
  }
    std::cout<<"Min Chi2: "<<minchi2<<" dps, sps, nlo: "<<minan<<" "<<minbn<<" "<<mincn<<std::endl;
    TCanvas* disp = new TCanvas("disp","disp",900,900);
    disp->Divide(2,2);
    TH1F *MassSum = new TH1F("MassSum","MassSum",nmbins,massbins);
    TH1F *MassBest = new TH1F("MassBest","MassBest",nmbins,massbins);
    TH1F *DpsBestM = new TH1F("DpsBestM","DpsBestM",nmbins,massbins);
    TH1F *SpsBestM = new TH1F("SpsBestM","SpsBestM",nmbins,massbins);
    TH1F *NloBestM = new TH1F("NloBestM","NloBestM",nmbins,massbins);
    TH1F *pTBest = new TH1F("pTBest","pTBest",nptbins,ptbins);
    TH1F *pTSum = new TH1F("pTSum","pTSum",nptbins,ptbins);
    TH1F *DpsBestpt = new TH1F("DpsBestpt","DpsBestpt",nptbins,ptbins);
    TH1F *NloBestpt = new TH1F("NloBestpt","NloBestpt",nptbins,ptbins);
    TH1F *SpsBestpt = new TH1F("SpsBestpt","SpsBestpt",nptbins,ptbins);
    TH1F *dyBest = new TH1F("dyBest","dyBest",ndybins,dybins);
    TH1F *dySum = new TH1F("dySum","dySum",ndybins,dybins);
    TH1F *DpsBestdy = new TH1F("DpsBestdy","DpsBestdy",ndybins,dybins);
    TH1F *NloBestdy = new TH1F("NloBestdy","NloBestdy",ndybins,dybins);
    TH1F *SpsBestdy = new TH1F("SpsBestdy","SpsBestdy",ndybins,dybins);
    TH1F *yBest = new TH1F("yBest","yBest",nybins,ybins);
    TH1F *ySum = new TH1F("ySum","ySum",nybins,ybins);
    TH1F *DpsBesty = new TH1F("DpsBesty","DpsBesty",nybins,ybins);
    TH1F *NloBesty = new TH1F("NloBesty","NloBesty",nybins,ybins);
    TH1F *SpsBesty = new TH1F("SpsBesty","SpsBesty",nybins,ybins);
    MassBest->SetMinimum(0);pTBest->SetMinimum(0);dyBest->SetMinimum(0);yBest->SetMinimum(0);
    mass_data->SetMinimum(0);pt_data->SetMinimum(0);dy_data->SetMinimum(0);y_data->SetMinimum(0);
    dps.Draw("FourMu_Mass>>DpsBestM","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("FourMu_Mass>>NloBestM","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("FourMu_Mass>>SpsBestM","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    dps.Draw("FourMu_pT>>DpsBestpt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("FourMu_pT>>NloBestpt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("FourMu_pT>>SpsBestpt","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    dps.Draw("Psi1To2_dY>>DpsBestdy","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("Psi1To2_dY>>NloBestdy","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("Psi1To2_dY>>SpsBestdy","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    dps.Draw("abs(FourMu_Rapidity)>>DpsBesty","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("abs(FourMu_Rapidity)>>NloBesty","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("abs(FourMu_Rapidity)>>SpsBesty","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  DpsBestM->Divide(mass_width);
  NloBestM->Divide(mass_width);
  SpsBestM->Divide(mass_width);
  DpsBestpt->Divide(pt_width);
  NloBestpt->Divide(pt_width);
  SpsBestpt->Divide(pt_width);
  DpsBestdy->Divide(dy_width);
  NloBestdy->Divide(dy_width);
  SpsBestdy->Divide(dy_width);
  DpsBesty->Divide(y_width);
  NloBesty->Divide(y_width);
  SpsBesty->Divide(y_width);
    //MassSum->Add(DpsBest,(float) mina);
    //MassSum->Add(SpsBest,minb);
    //MassSum->Add(NloBest,minc);
    mass_data->SetMinimum(0);
    mass_data->SetXTitle("Four Mu Mass (GeV)");
    pt_data->SetXTitle("Four Mu pT (GeV)");
    dy_data->SetXTitle("|#Delta Y| between J/#psi");
    y_data->SetXTitle("Four Mu Rapidity |Y|");
    mass_data->SetTitle("");
    pt_data->SetTitle("");
    dy_data->SetTitle("");
    y_data->SetTitle("");
    disp->cd(1);
    DpsBestM->SetLineColor(kRed);
    NloBestM->SetLineColor(kGreen);
    SpsBestM->SetLineColor(kBlue);
    DpsBestM->Scale(minan*scaledps);
    NloBestM->Scale(mincn*scalenlo);
    SpsBestM->Scale(minbn*scalesps);
    MassSum->Add(DpsBestM);
    MassSum->Add(NloBestM);
    MassSum->Add(SpsBestM);
    mass_data->Draw("E1");
    MassSum->Draw("same");
    DpsBestM->Draw("same");
    NloBestM->Draw("same");
    SpsBestM->Draw("same");
    TLegend *leg = new TLegend(0.6,0.7,0.90,0.9);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->AddEntry(DpsBestM,"DPS model","l");
    leg->AddEntry(NloBestM,"SPS NLO model","l");
    leg->AddEntry(MassSum,"MC model sum","l");
    leg->AddEntry(MassBest,"Data","lep");
    leg->Draw();
    disp->cd(2);
    DpsBestpt->SetLineColor(kRed);
    NloBestpt->SetLineColor(kGreen);
    SpsBestpt->SetLineColor(kBlue);
    DpsBestpt->Scale(minan*scaledps);
    NloBestpt->Scale(mincn*scalenlo);
    SpsBestpt->Scale(minbn*scalesps);
    pTSum->Add(DpsBestpt);
    pTSum->Add(NloBestpt);
    pTSum->Add(SpsBestpt);
    pt_data->Draw("e1");
    pTSum->Draw("same");
    DpsBestpt->Draw("same");
    NloBestpt->Draw("same");
    SpsBestpt->Draw("same");
    leg->Draw();
    disp->cd(3);
    DpsBestdy->SetLineColor(kRed);
    NloBestdy->SetLineColor(kGreen);
    SpsBestdy->SetLineColor(kBlue);
    DpsBestdy->Scale(minan*scaledps);
    NloBestdy->Scale(mincn*scalenlo);
    SpsBestdy->Scale(minbn*scalesps);
    dySum->Add(DpsBestdy);
    dySum->Add(NloBestdy);
    dySum->Add(SpsBestdy);
    dy_data->Draw("e1");
    dySum->Draw("same");
    DpsBestdy->Draw("same");
    NloBestdy->Draw("same");
    SpsBestdy->Draw("same");
    leg->Draw();
    disp->cd(4);
    DpsBesty->SetLineColor(kRed);
    NloBesty->SetLineColor(kGreen);
    SpsBesty->SetLineColor(kBlue);
    DpsBesty->Scale(minan*scaledps);
    NloBesty->Scale(mincn*scalenlo);
    SpsBesty->Scale(minbn*scalesps);
    ySum->Add(DpsBesty);
    ySum->Add(NloBesty);
    ySum->Add(SpsBesty);
    y_data->Draw("e1");
    ySum->Draw("same");
    DpsBesty->Draw("same");
    NloBesty->Draw("same");
    SpsBesty->Draw("same");
    leg->Draw();
  }

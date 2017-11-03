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


int binfit() {
  gROOT->Reset();

  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  float datamass[81]={0};
  int dpsmass[81]={0};
  int spsmass[81]={0};
  float nlomass[81]={0.0};
  int nloggmass[81]={0};
  int nlogumass[81]={0};
  int nlougmass[81]={0};
  //  float datapt[60],datady[20],datay[20];
  TChain data("ntuple");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");

//  data.Add("Data_AllCorrections.root");
//  dps.Add("Modified_Input_To_Fit_2012DPS_PUold_TMTight_3MuL3MatchPv.root");
  dps.Add("Modified_Input_To_Fit_2012DPS_GENTupleOnly_TMTight_MuL3Match.root");
  sps.Add("Modified_Input_To_Fit_2012SPSLOpy8_TMTight_3MuL3Match.root");
  nlogg.Add("Modified_Input_To_Fit_2012SPSNLOpy8_gg_TMTight_3MuL3Match.root");
//  nlogg.Add("Modified_Input_To_Fit_2012SPSNLO_gg_TMTight_MuL3Match_PU_OffsetBS.root");
  float massbins[]={6.2,6.5,7,8.5,11,14,18,24,30,45,80};
  float ptbins[]={0,4,8,12,15,18,22,26,30,80};
  float dybins[]={0,0.1,0.2,0.3,0.45,0.6,0.9,1.3,1.8,2.4,4.5};
  float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  int nmbins = 10; 
  int nptbins = 9;
  int ndybins = 10;
  int nybins = 20;

  TH1F *mass_data = new TH1F("mass_data","mass_data",nmbins,massbins); 
  TH1F *mass_dps = new TH1F("mass_dps","mass_dps",nmbins,massbins); 
  TH1F *mass_sps = new TH1F("mass_sps","mass_sps",nmbins,massbins); 
  TH1F *mass_nlogg = new TH1F("mass_nlogg","mass_nlogg",nmbins,massbins); 
  TH1F *mass_nlogu = new TH1F("mass_nlogu","mass_nlogu",nmbins,massbins); 
  TH1F *mass_nloug = new TH1F("mass_nloug","mass_nloug",nmbins,massbins); 
  TH1F *mass_nlo = new TH1F("mass_nlo","mass_nlo",nmbins,massbins); 
  TH1F *pt_data = new TH1F("pt_data","pt_data",nptbins,ptbins); 
  TH1F *pt_dps = new TH1F("pt_dps","pt_dps",nptbins,ptbins); 
  TH1F *pt_sps = new TH1F("pt_sps","pt_sps",nptbins,ptbins); 
  TH1F *pt_nlogg = new TH1F("pt_nlogg","pt_nlogg",nptbins,ptbins); 
  TH1F *pt_nlogu = new TH1F("pt_nlogu","pt_nlogu",nptbins,ptbins); 
  TH1F *pt_nloug = new TH1F("pt_nloug","pt_nloug",nptbins,ptbins); 
  TH1F *pt_nlo = new TH1F("pt_nlo","pt_nlo",nptbins,ptbins); 
  TH1F *dy_data = new TH1F("dy_data","dy_data",ndybins,dybins); 
  TH1F *dy_dps = new TH1F("dy_dps","dy_dps",ndybins,dybins); 
  TH1F *dy_sps = new TH1F("dy_sps","dy_sps",ndybins,dybins); 
  TH1F *dy_nlogg = new TH1F("dy_nlogg","dy_nlogg",ndybins,dybins); 
  TH1F *dy_nlogu = new TH1F("dy_nlogu","dy_nlogu",ndybins,dybins); 
  TH1F *dy_nloug = new TH1F("dy_nloug","dy_nloug",ndybins,dybins); 
  TH1F *dy_nlo = new TH1F("dy_nlo","dy_nlo",ndybins,dybins); 
  TH1F *y_data = new TH1F("y_data","y_data",nybins,ybins); 
  TH1F *y_dps = new TH1F("y_dps","y_dps",nybins,ybins); 
  TH1F *y_sps = new TH1F("y_sps","y_sps",nybins,ybins); 
  TH1F *y_nlogg = new TH1F("y_nlogg","y_nlogg",nybins,ybins); 
  TH1F *y_nlogu = new TH1F("y_nlogu","y_nlogu",nybins,ybins); 
  TH1F *y_nloug = new TH1F("y_nloug","y_nloug",nybins,ybins); 
  TH1F *y_nlo = new TH1F("y_nlo","y_nlo",nybins,ybins); 
  mass_data->SetBinContent(0,44.3);
  mass_data->SetBinContent(0,81.2);
  mass_data->SetBinContent(0,120.6);
  mass_data->SetBinContent(0,103.0);
  mass_data->SetBinContent(0,90.9);
  mass_data->SetBinContent(0,77.6);
  mass_data->SetBinContent(0,71.6);
  mass_data->SetBinContent(0,78.1);
  mass_data->SetBinContent(0,78.7);
  mass_data->SetBinContent(0,55.4);
  mass_data->SetEntries(801.9);
  dps.Draw("FourMu_Mass >> mass_dps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
  sps.Draw("FourMu_Mass >> mass_sps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
  nlogg.Draw("FourMu_Mass >> mass_nlogg","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
  nlogu.Draw("FourMu_Mass >> mass_nlogu","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
  nloug.Draw("FourMu_Mass >> mass_nloug","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");

  datamass[0]=801.9;
  std::cout<<datamass[0]<<std::endl;
  dpsmass[0]=mass_dps->Integral();
  spsmass[0]=mass_sps->Integral();
  nloggmass[0]=mass_nlogg->Integral();
  nlogumass[0]=mass_nlogu->Integral();
  nlougmass[0]=mass_nlogg->Integral();
  //siggg=2.01;siggu=0.45;sigug=0.13;
  siggg=1.0;siggu=0.0;sigug=0.0;
  nlomass[0]=siggg*nloggmass[0] + siggu*nlogumass[0] + sigug*nlougmass[0]; 

  scaledps = datamass[0]/ (float) dpsmass[0];
  scalesps= datamass[0]/ (float) spsmass[0];
  scalenlo= datamass[0]/ (float) nloggmass[0];
  float Chi2=0;
  float minchi2norm=99999999.9;
  float minchi2=9999999.9;
  float mina, minb, minc, minan, minbn, mincn;

  //   Chi2 = Chi2 + pow((datamass[1] - (0.00*scaledps*dpsmass[1] + 0.0*scalesps*spsmass[1] + 0.0*scalenlo*nlomass[1])),2)/sqrt(datamass[1]);
  //  std::cout<<"Scale: " <<datamass[0]<<" " << dpsmass[0]<<" "<<scaledps<<" "<<scalesps<<" "<<scalenlo<<" "<<std::endl;
  for(float a=0.0; a<1; a=a+0.1){
    for(float b=0.0; b<1; b=b+0.1){
      for(float c=0.0; c<1; c=c+0.1){
  mass_data->SetBinContent(1,44.3); 
  mass_data->SetBinContent(2,81.2);   
  mass_data->SetBinContent(3,120.6);
  mass_data->SetBinContent(4,103.0);
  mass_data->SetBinContent(5,90.9);
  mass_data->SetBinContent(6,77.6);
  mass_data->SetBinContent(7,71.6);
  mass_data->SetBinContent(8,78.1);
  mass_data->SetBinContent(9,78.7);
  mass_data->SetBinContent(10,55.4);
  mass_data->SetEntries(801.9);
  pt_data->SetBinContent(1,65.1);
  pt_data->SetBinContent(2,108.2);
  pt_data->SetBinContent(3,76.5);
  pt_data->SetBinContent(4,75.0);
  pt_data->SetBinContent(5,105.0);
  pt_data->SetBinContent(6,105.6);
  pt_data->SetBinContent(7,104.0);
  pt_data->SetBinContent(8,68.1);
  pt_data->SetBinContent(9,85.9);
  pt_data->SetEntries(793.4);
  dy_data->SetBinContent(1,129.8);
  dy_data->SetBinContent(2,139.6);
  dy_data->SetBinContent(3,93.1);
  dy_data->SetBinContent(4,82.5);
  dy_data->SetBinContent(5,63.0);
  dy_data->SetBinContent(6,66.2);
  dy_data->SetBinContent(7,58.1);
  dy_data->SetBinContent(8,46.4);
  dy_data->SetBinContent(9,48.5);
  dy_data->SetBinContent(10,74.3);
  dy_data->SetEntries(801.6);
        dps.Draw("FourMu_Mass >> mass_dps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        sps.Draw("FourMu_Mass >> mass_sps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("FourMu_Mass >> mass_nlogg","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        dps.Draw("FourMu_pT >> pt_dps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        sps.Draw("FourMu_pT >> pt_sps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("FourMu_pT >> pt_nlogg","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        dps.Draw("Psi1To2_dY >> dy_dps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        sps.Draw("Psi1To2_dY >> dy_sps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("Psi1To2_dY >> dy_nlogg","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
        //data.Draw("FourMu_Rapidity>> y_data","Weight","goff");
        //dps.Draw("FourMu_Rapidity>> y_dps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
        //sps.Draw("FourMu_Rapidity >> y_sps","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
        //nlogg.Draw("FourMu_Rapidity >> y_nlogg","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4","goff");
        for(int mbin=1; mbin<=nmbins; ++mbin){
        //Chi2=(mass_data->GetBinContent(mbin));
          Chi2=Chi2 + pow((mass_data->GetBinContent(mbin) - (a*scaledps*mass_dps->GetBinContent(mbin) + b*scalesps*mass_sps->GetBinContent(mbin) + c*scalenlo*mass_nlogg->GetBinContent(mbin))),2)/sqrt(abs(mass_data->GetBinContent(mbin)));
        //             std::cout<<Chi2<<std::endl;
        }
        for(int ptbin=1; ptbin<=nptbins; ++ptbin){
          Chi2=Chi2 + pow((pt_data->GetBinContent(ptbin) - (a*scaledps*pt_dps->GetBinContent(ptbin) + b*scalesps*pt_sps->GetBinContent(ptbin) + c*scalenlo*pt_nlogg->GetBinContent(ptbin))),2)/sqrt(abs(pt_data->GetBinContent(ptbin)));
            //         std::cout<<pt_data->GetBinContent(ptbin)<<std::endl;
        }
        for(int dybin=1; dybin<=ndybins; ++dybin){
          Chi2=Chi2 + pow((dy_data->GetBinContent(dybin) - (a*scaledps*dy_dps->GetBinContent(dybin) + b*scalesps*dy_sps->GetBinContent(dybin) + c*scalenlo*dy_nlogg->GetBinContent(dybin))),2)/sqrt(abs(dy_data->GetBinContent(dybin)));
          //           std::cout<<Chi2<<std::endl;
        }
        //for(int ybin=1; ybin<=nybins; ++ybin){
        //  Chi2=Chi2 + pow((y_data->GetBinContent(ybin) - (a*scaledps*y_dps->GetBinContent(ybin) + b*scalesps*y_sps->GetBinContent(ybin) + c*scalenlo*y_nlogg->GetBinContent(ybin))),2)/sqrt(abs(y_data->GetBinContent(ybin)));
        //  //           std::cout<<Chi2<<std::endl;
        //}
        //        std::cout<<"a, b, c: "<<a<<" "<<b<<" "<<c<<" Chi2: "<<Chi2<<std::endl;
        std::cout<<a<<" "<<b<<" "<<c<<" "<<Chi2<<std::endl;
          if ( fabs(1.-(a+b+c))<0.01){
           // std::cout<<"NORM: "<<a+b+c<<std::endl;
        if (Chi2<=minchi2norm){
            minchi2norm=Chi2; minan = a; minbn = b; mincn = c;
          }
        }
        if (Chi2<=minchi2){
          minchi2=Chi2; mina = a; minb = b; minc = c;
        }
          //      std::cout<<a<<" "<<b<<" "<<c<<" "<<Chi2<<std::endl;
        Chi2=0;
        }
      }
    }
    std::cout<<"Min Chi2: "<<minchi2<<" dps, sps, nlo: "<<mina<<" "<<minb<<" "<<minc<<std::endl;
    std::cout<<"Min normed Chi2: "<<minchi2norm<<" dps, sps, nlo: "<<minan<<" "<<minbn<<" "<<mincn<<std::endl;
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
    TH1F *SpsBestpt = new TH1F("SpsBestpt","SpsBestpt",nptbins,ptbins);
    TH1F *NloBestpt = new TH1F("NloBestpt","NloBestpt",nptbins,ptbins);
    TH1F *dyBest = new TH1F("dyBest","dyBest",ndybins,dybins);
    TH1F *dySum = new TH1F("dySum","dySum",ndybins,dybins);
    TH1F *DpsBestdy = new TH1F("DpsBestdy","DpsBestdy",ndybins,dybins);
    TH1F *SpsBestdy = new TH1F("SpsBestdy","SpsBestdy",ndybins,dybins);
    TH1F *NloBestdy = new TH1F("NloBestdy","NloBestdy",ndybins,dybins);
    //TH1F *yBest = new TH1F("yBest","yBest",nybins,ybins);
    //TH1F *ySum = new TH1F("ySum","ySum",nybins,ybins);
    //TH1F *DpsBesty = new TH1F("DpsBesty","DpsBesty",nybins,ybins);
    //TH1F *SpsBesty = new TH1F("SpsBesty","SpsBesty",nybins,ybins);
    //TH1F *NloBesty = new TH1F("NloBesty","NloBesty",nybins,ybins);
  MassBest->SetBinContent(1,44.3); 
  MassBest->SetBinContent(2,81.2);   
  MassBest->SetBinContent(3,120.6);
  MassBest->SetBinContent(4,103.0);
  MassBest->SetBinContent(5,90.9);
  MassBest->SetBinContent(6,77.6);
  MassBest->SetBinContent(7,71.6);
  MassBest->SetBinContent(8,78.1);
  MassBest->SetBinContent(9,78.7);
  MassBest->SetBinContent(10,55.4);
  MassBest->SetEntries(801.9);
  pTBest->SetBinContent(1,65.1);
  pTBest->SetBinContent(2,108.2);
  pTBest->SetBinContent(3,76.5);
  pTBest->SetBinContent(4,75.0);
  pTBest->SetBinContent(5,105.0);
  pTBest->SetBinContent(6,105.6);
  pTBest->SetBinContent(7,104.0);
  pTBest->SetBinContent(8,68.1);
  pTBest->SetBinContent(9,85.9);
  pTBest->SetEntries(793.4);
  dyBest->SetBinContent(1,129.8);
  dyBest->SetBinContent(2,139.6);
  dyBest->SetBinContent(3,93.1);
  dyBest->SetBinContent(4,82.5);
  dyBest->SetBinContent(5,63.0);
  dyBest->SetBinContent(6,66.2);
  dyBest->SetBinContent(7,58.1);
  dyBest->SetBinContent(8,46.4);
  dyBest->SetBinContent(9,48.5);
  dyBest->SetBinContent(10,74.3);
  dyBest->SetEntries(801.6);
    MassBest->SetMinimum(0);pTBest->SetMinimum(0);dyBest->SetMinimum(0);//yBest->SetMinimum(0);
    dps.Draw("FourMu_Mass>>DpsBestM","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    sps.Draw("FourMu_Mass>>SpsBestM","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    nlogg.Draw("FourMu_Mass>>NloBestM","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    dps.Draw("FourMu_pT>>DpsBestpt","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    sps.Draw("FourMu_pT>>SpsBestpt","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    nlogg.Draw("FourMu_pT>>NloBestpt","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    dps.Draw("Psi1To2_dY>>DpsBestdy","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    sps.Draw("Psi1To2_dY>>SpsBestdy","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
    nlogg.Draw("Psi1To2_dY>>NloBestdy","FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4","goff");
//    dps.Draw("FourMu_Rapidity>>DpsBesty","(FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4)","goff");
//    sps.Draw("FourMu_Rapidity>>SpsBesty","(FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4)","goff");
//    nlogg.Draw("FourMu_Rapidity>>NloBesty","(FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=1.2&&Psi_pT>6.5||abs(Psi_y)>1.2&&abs(Psi_y)<1.43&&(Psi_pT>-8.696*abs(Psi_y)+16.9)||abs(Psi_y)>=1.43&&abs(Psi_y)<=2.2&&Psi_pT>4.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)>=3&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-6.0*abs(Mu_Eta)+10)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>1.1)==4)","goff");
    //MassSum->Add(DpsBest,(float) mina);
    //MassSum->Add(SpsBest,minb);
    //MassSum->Add(NloBest,minc);
    //MassBest->SetMinimum(0);
    disp->cd(1);
    MassBest->Draw("e");
    DpsBestM->SetLineColor(kRed);
    SpsBestM->SetLineColor(kBlue);
    NloBestM->SetLineColor(kGreen);
    DpsBestM->Scale(minan*scaledps);
    SpsBestM->Scale(minbn*scalesps);
    NloBestM->Scale(mincn*scalenlo);
    MassSum->Add(DpsBestM);
    MassSum->Add(SpsBestM);
    MassSum->Add(NloBestM);
    DpsBestM->Draw("same");
    SpsBestM->Draw("same");
    NloBestM->Draw("same");
    MassSum->Draw("same");
    disp->cd(2);
    pTBest->Draw("e");
    DpsBestpt->SetLineColor(kRed);
    SpsBestpt->SetLineColor(kBlue);
    NloBestpt->SetLineColor(kGreen);
    DpsBestpt->Scale(minan*scaledps);
    SpsBestpt->Scale(minbn*scalesps);
    NloBestpt->Scale(mincn*scalenlo);
    pTSum->Add(DpsBestpt);
    pTSum->Add(SpsBestpt);
    pTSum->Add(NloBestpt);
    DpsBestpt->Draw("same");
    SpsBestpt->Draw("same");
    NloBestpt->Draw("same");
    pTSum->Draw("same");
    disp->cd(3);
    dyBest->Draw("e");
    DpsBestdy->SetLineColor(kRed);
    SpsBestdy->SetLineColor(kBlue);
    NloBestdy->SetLineColor(kGreen);
    DpsBestdy->Scale(minan*scaledps);
    SpsBestdy->Scale(minbn*scalesps);
    NloBestdy->Scale(mincn*scalenlo);
    dySum->Add(DpsBestdy);
    dySum->Add(SpsBestdy);
    dySum->Add(NloBestdy);
    DpsBestdy->Draw("same");
    SpsBestdy->Draw("same");
    NloBestdy->Draw("same");
    dySum->Draw("same");
    disp->cd(4);
//    data.Draw("FourMu_Rapidity>> yBest","Weight","e");
//    DpsBesty->SetLineColor(kRed);
//    SpsBesty->SetLineColor(kBlue);
//    NloBesty->SetLineColor(kGreen);
//    DpsBesty->Scale(minan*scaledps);
//    SpsBesty->Scale(minbn*scalesps);
//    NloBesty->Scale(mincn*scalenlo);
//    ySum->Add(DpsBesty);
//    ySum->Add(SpsBesty);
//    ySum->Add(NloBesty);
//    DpsBesty->Draw("same");
//    SpsBesty->Draw("same");
//    NloBesty->Draw("same");
//    ySum->Draw("same");
  }

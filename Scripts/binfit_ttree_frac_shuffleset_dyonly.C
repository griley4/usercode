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


int binfit_ttree_frac_shuffleset_dyonly() {
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
  TChain data("PATEventTree");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");

  data.Add("Selected_events_newAcc.root");
//  dps.Add("Modified_Input_To_Fit_2012DPS_TMTight_3MuL3Match.root");
  dps.Add("Shuffled_JPsi_sample.root");
  //dps.Add("Modified_Input_To_Fit_2012DPS_GENTupleOnly_TMTight_MuL3Match.root");
  sps.Add("Modified_Input_To_Fit_2012SPSLOpy8_TMTight_3MuL3Match.root");
  //nlogg.Add("Modified_Input_To_Fit_2012SPSNLOpy8_gg_TMTight_3MuL3Match.root");
  nlogg.Add("Modified_Input_To_Fit_2012SPSNLO_gg_TMTight_MuL3Match_PU_OffsetBS.root");
  //float massbins[]={6.2,7,8,10,13,17,23,30,42,80};
  //float ptbins[]={0,7,12,16,20,25,80};
  //float dybins[]={0,0.2,0.4,0.6,0.9,1.3,1.8,2.4,4.5};
  ////float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  //float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  //int nmbins = 9; 
  //int nptbins = 6;
  //int ndybins = 8;
  //int nybins = 10;
  float massbins[]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60};
  float ptbins[]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80};
  float dybins[]={0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5};
  float ybins[]={0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8};
    int nmbins = 30;
    int nptbins = 40;
    int ndybins = 45;
    int nybins = 18;
  //int nybins = 20;
    int mbinerr = -99;
    int ptbinerr = -99;
    int dybinerr = -99;
    int ybinerr = -99;
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
  data.Draw("FourMu_Mass >> mass_data","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
  dps.Draw("FourMu_Mass >> mass_dps","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
  sps.Draw("FourMu_Mass >> mass_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  nlogg.Draw("FourMu_Mass >> mass_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  nlogu.Draw("FourMu_Mass >> mass_nlogu","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  nloug.Draw("FourMu_Mass >> mass_nloug","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");

  datamass[0]=mass_data->Integral();
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
  for(float a=0.0; a<1.0; a=a+0.01){
        data.Draw("FourMu_Mass >> mass_data","","goff");
        dps.Draw("FourMu_Mass >> mass_dps","","goff");
        sps.Draw("FourMu_Mass >> mass_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("FourMu_Mass >> mass_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        data.Draw("FourMu_pT >> pt_data","","goff");
        dps.Draw("FourMu_pT >> pt_dps","","goff");
        sps.Draw("FourMu_pT >> pt_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("FourMu_pT >> pt_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        data.Draw("Psi1To2_dY >> dy_data","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
        dps.Draw("Psi1To2_dY >> dy_dps","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
        sps.Draw("Psi1To2_dY >> dy_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("Psi1To2_dY >> dy_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        data.Draw("abs(FourMu_Rapidity)>> y_data","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
        dps.Draw("abs(FourMu_Rapidity)>> y_dps","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
        sps.Draw("abs(FourMu_Rapidity) >> y_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("abs(FourMu_Rapidity) >> y_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        for(int mbin=1; mbin<=nmbins; ++mbin){
          if (mass_data->GetBinContent(mbin) == 0){
            //mbinerr = 1.;
            continue;
          }
          //else{mbinerr = sqrt(abs(mass_data->GetBinContent(mbin)));}
          //Chi2=Chi2 + pow((mass_data->GetBinContent(mbin) - (a*scaledps*mass_dps->GetBinContent(mbin) + b*scalesps*mass_sps->GetBinContent(mbin) + c*scalenlo*mass_nlogg->GetBinContent(mbin))),2)/mbinerr;
//          Chi2=Chi2 + pow((mass_data->GetBinContent(mbin) - (a*scaledps*mass_dps->GetBinContent(mbin) + b*scalesps*mass_sps->GetBinContent(mbin) + c*scalenlo*mass_nlogg->GetBinContent(mbin)))/sqrt(abs(mass_data->GetBinContent(mbin))),2);
          //           std::cout<<Chi2<<std::endl;
        }
        for(int ptbin=1; ptbin<=nptbins; ++ptbin){
          if (pt_data->GetBinContent(ptbin) == 0){
            ptbinerr = 1.;
          }
          else{ptbinerr = sqrt(abs(pt_data->GetBinContent(ptbin)));}
//          Chi2=Chi2 + pow((pt_data->GetBinContent(ptbin) - (a*scaledps*pt_dps->GetBinContent(ptbin) + (1-a)*scalenlo*pt_nlogg->GetBinContent(ptbin)))/ptbinerr,2);
            //         std::cout<<pt_data->GetBinContent(ptbin)<<std::endl;
        }
        for(int dybin=1; dybin<=ndybins; ++dybin){
          if (dy_data->GetBinContent(dybin) == 0){
            dybinerr = 1.;
          }
          else{dybinerr = sqrt(abs(dy_data->GetBinContent(dybin)));}
          Chi2=Chi2 + pow((dy_data->GetBinContent(dybin) - (a*scaledps*dy_dps->GetBinContent(dybin) + (1-a)*scalenlo*dy_nlogg->GetBinContent(dybin)))/dybinerr,2);
          //           std::cout<<Chi2<<std::endl;
        }
        for(int ybin=1; ybin<=nybins; ++ybin){
          if (y_data->GetBinContent(ybin) == 0){
            ybinerr = 1.;
          }
          else{ybinerr = sqrt(abs(y_data->GetBinContent(ybin)));}
//          Chi2=Chi2 + pow((y_data->GetBinContent(ybin) - (a*scaledps*y_dps->GetBinContent(ybin) + (1-a)*scalenlo*y_nlogg->GetBinContent(ybin)))/ybinerr,2);
          //           std::cout<<Chi2<<std::endl;
        }
        //        std::cout<<"a, b, c: "<<a<<" "<<b<<" "<<c<<" Chi2: "<<Chi2<<std::endl;
        std::cout<<a<<" "<<Chi2<<std::endl;
        if (Chi2<=minchi2){
          minchi2=Chi2; minan = a; minbn = 0.; mincn=(1-a); 
        }
        //        std::cout<<a<<" "<<b<<" "<<c<<" "<<Chi2<<std::endl;
        Chi2=0;
    }
    std::cout<<"Min Chi2: "<<minchi2<<" dps, sps, nlo: "<<minan<<" "<<minbn<<" "<<mincn<<std::endl;
    TCanvas* disp = new TCanvas("disp","disp",900,900);
//    disp->Divide(2,2);
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
    TH1F *yBest = new TH1F("yBest","yBest",nybins,ybins);
    TH1F *ySum = new TH1F("ySum","ySum",nybins,ybins);
    TH1F *DpsBesty = new TH1F("DpsBesty","DpsBesty",nybins,ybins);
    TH1F *SpsBesty = new TH1F("SpsBesty","SpsBesty",nybins,ybins);
    TH1F *NloBesty = new TH1F("NloBesty","NloBesty",nybins,ybins);
    MassBest->SetMinimum(0);pTBest->SetMinimum(0);dyBest->SetMinimum(0);yBest->SetMinimum(0);
//    dps.Draw("FourMu_Mass>>DpsBestM","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("FourMu_Mass>>SpsBestM","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("FourMu_Mass>>NloBestM","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
  //  dps.Draw("FourMu_pT>>DpsBestpt","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("FourMu_pT>>SpsBestpt","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("FourMu_pT>>NloBestpt","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    dps.Draw("Psi1To2_dY>>DpsBestdy","Psi_pT[0]>8.0&&Psi_pT[1]>8.0","goff");
    sps.Draw("Psi1To2_dY>>SpsBestdy","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("Psi1To2_dY>>NloBestdy","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    //dps.Draw("abs(FourMu_Rapidity)>>DpsBesty","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("abs(FourMu_Rapidity)>>SpsBesty","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("abs(FourMu_Rapidity)>>NloBesty","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    //MassSum->Add(DpsBest,(float) mina);
    //MassSum->Add(SpsBest,minb);
    //MassSum->Add(NloBest,minc);
    MassBest->SetMinimum(0);
    MassBest->SetXTitle("Four Mu Mass (GeV)");
    pTBest->SetXTitle("Four Mu pT (GeV)");
    dyBest->SetXTitle("|#Delta Y| between J/#psi");
    yBest->SetXTitle("Four Mu Rapidity |Y|");
    MassBest->SetYTitle("Events / 2. GeV");
    pTBest->SetYTitle("Events / 2. GeV");
    dyBest->SetYTitle("Events / 0.1");
    yBest->SetYTitle("Events / 0.1");
    MassBest->SetTitle("");
    pTBest->SetTitle("");
    dyBest->SetTitle("");
    yBest->SetTitle("");
//    disp->cd(1);
//    DpsBestM->SetLineColor(kRed);
//    SpsBestM->SetLineColor(kBlue);
//    NloBestM->SetLineColor(kGreen);
//    DpsBestM->Scale(minan*scaledps);
//    SpsBestM->Scale(minbn*scalesps);
//    NloBestM->Scale(mincn*scalenlo);
//    MassSum->Add(DpsBestM);
//    MassSum->Add(SpsBestM);
//    MassSum->Add(NloBestM);
//    data.Draw("FourMu_Mass >> MassBest","","e");
//    MassSum->Draw("same");
//    DpsBestM->Draw("same");
//    SpsBestM->Draw("same");
//    NloBestM->Draw("same");
//    TLegend *leg = new TLegend(0.6,0.7,0.90,0.9);
//    leg->SetFillStyle(0);
//    leg->SetBorderSize(0);
//    leg->SetShadowColor(0);
//    leg->AddEntry(DpsBestM,"DPS model","l");
//    leg->AddEntry(SpsBestM,"SPS LO model","l");
//    leg->AddEntry(NloBestM,"SPS NLO model","l");
//    leg->AddEntry(MassSum,"MC model sum","l");
//    leg->AddEntry(MassBest,"Data","lep");
//    leg->Draw();
//    disp->cd(2);
//    DpsBestpt->SetLineColor(kRed);
//    SpsBestpt->SetLineColor(kBlue);
//    NloBestpt->SetLineColor(kGreen);
//    DpsBestpt->Scale(minan*scaledps);
//    SpsBestpt->Scale(minbn*scalesps);
//    NloBestpt->Scale(mincn*scalenlo);
//    pTSum->Add(DpsBestpt);
//    pTSum->Add(SpsBestpt);
//    pTSum->Add(NloBestpt);
//    data.Draw("FourMu_pT >> pTBest","","e");
//    pTSum->Draw("same");
//    DpsBestpt->Draw("same");
//    SpsBestpt->Draw("same");
//    NloBestpt->Draw("same");
//    leg->Draw();
//    disp->cd(3);
    DpsBestdy->SetLineColor(kRed);
    SpsBestdy->SetLineColor(kBlue);
    NloBestdy->SetLineColor(kGreen);
    DpsBestdy->Scale(minan*scaledps);
    SpsBestdy->Scale(minbn*scalesps);
    NloBestdy->Scale(mincn*scalenlo);
    dySum->Add(DpsBestdy);
    dySum->Add(SpsBestdy);
    dySum->Add(NloBestdy);
    data.Draw("Psi1To2_dY >> dyBest","","e");
    dySum->Draw("same");
    DpsBestdy->Draw("same");
    SpsBestdy->Draw("same");
    NloBestdy->Draw("same");
    leg->Draw();
//    disp->cd(4);
//    DpsBesty->SetLineColor(kRed);
//    SpsBesty->SetLineColor(kBlue);
//    NloBesty->SetLineColor(kGreen);
//    DpsBesty->Scale(minan*scaledps);
//    SpsBesty->Scale(minbn*scalesps);
//    NloBesty->Scale(mincn*scalenlo);
//    ySum->Add(DpsBesty);
//    ySum->Add(SpsBesty);
//    ySum->Add(NloBesty);
//    data.Draw("abs(FourMu_Rapidity)>> yBest","","e");
//    ySum->Draw("same");
//    DpsBesty->Draw("same");
//    SpsBesty->Draw("same");
//    NloBesty->Draw("same");
//    leg->Draw();
  }

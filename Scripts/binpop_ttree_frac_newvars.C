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


int binpop_ttree_frac_newvars() {
  gROOT->Reset();

  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  float datapt1[81]={0};
  int dpspt1[81]={0};
  int spspt1[81]={0};
  float nlopt1[81]={0.0};
  int nloggpt1[81]={0};
  int nlogupt1[81]={0};
  int nlougpt1[81]={0};
  //  float datapt[60],datady[20],datay[20];
  TChain data("PATEventTree");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");

  data.Add("Selected_events_newAcc.root");
//  dps.Add("Modified_Input_To_Fit_2012DPS_TMTight_3MuL3Match.root");
  dps.Add("Modified_Input_To_Fit_2012DPS_PUold_TMTight_3MuL3MatchPv.root");
  //dps.Add("Modified_Input_To_Fit_2012DPS_GENTupleOnly_TMTight_MuL3Match.root");
  sps.Add("Modified_Input_To_Fit_2012SPSLOpy8_TMTight_3MuL3Match.root");
  //nlogg.Add("Modified_Input_To_Fit_2012SPSNLOpy8_gg_TMTight_3MuL3Match.root");
  nlogg.Add("Modified_Input_To_Fit_2012SPSNLO_gg_TMTight_MuL3Match_PU_OffsetBS.root");
  float dpbins[]={0,0.25,1.0,1.75,2.5,3.142};
  float pt1bins[]={0,5,10,12,14,17,20,25,60};
  float pt2bins[]={0,5,8,10,12,15,20,40};
  float ptabins[]={0,0.05,0.125,0.2,0.35,1.};
  int ndpbins = 5;
  int npt1bins = 8;
  int npt2bins = 7;
  int nptabins = 5;
  TH1F *dp_data = new TH1F("dp_data","dp_data",ndpbins,dpbins); 
  TH1F *dp_dps = new TH1F("dp_dps","dp_dps",ndpbins,dpbins); 
  TH1F *dp_sps = new TH1F("dp_sps","dp_sps",ndpbins,dpbins); 
  TH1F *dp_nlogg = new TH1F("dp_nlogg","dp_nlogg",ndpbins,dpbins); 
  TH1F *dp_nlogu = new TH1F("dp_nlogu","dp_nlogu",ndpbins,dpbins); 
  TH1F *dp_nloug = new TH1F("dp_nloug","dp_nloug",ndpbins,dpbins); 
  TH1F *dp_nlo = new TH1F("dp_nlo","dp_nlo",ndpbins,dpbins); 
  TH1F *pt1_data = new TH1F("pt1_data","pt1_data",npt1bins,pt1bins); 
  TH1F *pt1_dps = new TH1F("pt1_dps","pt1_dps",npt1bins,pt1bins); 
  TH1F *pt1_sps = new TH1F("pt1_sps","pt1_sps",npt1bins,pt1bins); 
  TH1F *pt1_nlogg = new TH1F("pt1_nlogg","pt1_nlogg",npt1bins,pt1bins); 
  TH1F *pt1_nlogu = new TH1F("pt1_nlogu","pt1_nlogu",npt1bins,pt1bins); 
  TH1F *pt1_nloug = new TH1F("pt1_nloug","pt1_nloug",npt1bins,pt1bins); 
  TH1F *pt1_nlo = new TH1F("pt1_nlo","pt1_nlo",npt1bins,pt1bins); 
  TH1F *pt2_data = new TH1F("pt2_data","pt2_data",npt2bins,pt2bins); 
  TH1F *pt2_dps = new TH1F("pt2_dps","pt2_dps",npt2bins,pt2bins); 
  TH1F *pt2_sps = new TH1F("pt2_sps","pt2_sps",npt2bins,pt2bins); 
  TH1F *pt2_nlogg = new TH1F("pt2_nlogg","pt2_nlogg",npt2bins,pt2bins); 
  TH1F *pt2_nlogu = new TH1F("pt2_nlogu","pt2_nlogu",npt2bins,pt2bins); 
  TH1F *pt2_nloug = new TH1F("pt2_nloug","pt2_nloug",npt2bins,pt2bins); 
  TH1F *pt2_nlo = new TH1F("pt2_nlo","pt2_nlo",npt2bins,pt2bins); 
  TH1F *pta_data = new TH1F("pta_data","pta_data",nptabins,ptabins); 
  TH1F *pta_dps = new TH1F("pta_dps","pta_dps",nptabins,ptabins); 
  TH1F *pta_sps = new TH1F("pta_sps","pta_sps",nptabins,ptabins); 
  TH1F *pta_nlogg = new TH1F("pta_nlogg","pta_nlogg",nptabins,ptabins); 
  TH1F *pta_nlogu = new TH1F("pta_nlogu","pta_nlogu",nptabins,ptabins); 
  TH1F *pta_nloug = new TH1F("pta_nloug","pta_nloug",nptabins,ptabins); 
  TH1F *pta_nlo = new TH1F("pta_nlo","pta_nlo",nptabins,ptabins); 
  data.Draw("Psi_pT[0] >> pt1_data","","goff");
  dps.Draw("Psi_pT[0] >> pt1_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  sps.Draw("Psi_pT[0] >> pt1_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  nlogg.Draw("Psi_pT[0] >> pt1_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  nlogu.Draw("Psi_pT[0] >> pt1_nlogu","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
  nloug.Draw("Psi_pT[0] >> pt1_nloug","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");

  datapt1[0]=pt1_data->Integral();
  std::cout<<datapt1[0]<<std::endl;
  dpspt1[0]=pt1_dps->Integral();
  spspt1[0]=pt1_sps->Integral();
  nloggpt1[0]=pt1_nlogg->Integral();
  nlogupt1[0]=pt1_nlogu->Integral();
  nlougpt1[0]=pt1_nlogg->Integral();
  //siggg=2.01;siggu=0.45;sigug=0.13;
  siggg=1.0;siggu=0.0;sigug=0.0;
  nlopt1[0]=siggg*nloggpt1[0] + siggu*nlogupt1[0] + sigug*nlougpt1[0]; 

  scaledps = datapt1[0]/ (float) dpspt1[0];
  scalesps= datapt1[0]/ (float) spspt1[0];
  scalenlo= datapt1[0]/ (float) nloggpt1[0];
  float Chi2=0;
  float dpsN = 0;
  float totN = 0;
  float minchi2norm=99999999.9;
  float minchi2=9999999.9;
  float a = 0.18; 
  float minan = 0.18;
  float minbn = 0.;
  float mincn = 0.82;
        data.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))) >> dp_data","","goff");
        dps.Draw(" TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px))))>> dp_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        sps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))) >> dp_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw(" TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px))))>> dp_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        data.Draw("Psi_pT[0]>> pt1_data","","goff");
        dps.Draw("Psi_pT[0] >> pt1_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        sps.Draw("Psi_pT[0] >> pt1_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("Psi_pT[1] >> pt1_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        data.Draw("Psi_pT[1]>> pt2_data","","goff");
        dps.Draw("Psi_pT[1]>> pt2_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        sps.Draw("Psi_pT[1] >> pt2_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("Psi_pT[1] >> pt2_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        data.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> pta_data","","goff");
        dps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> pta_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        sps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1]) >> pta_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        nlogg.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> pta_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4","goff");
        std::cout<<"dPt Bins "<<std::endl;
        totN=dpsN=0;
        for(int dpbin=1; dpbin<=ndpbins; ++dpbin){
         totN =  a*scaledps*dp_dps->GetBinContent(dpbin) + (1-a)*scalenlo*dp_nlogg->GetBinContent(dpbin);
         dpsN = a*scaledps*dp_dps->GetBinContent(dpbin);
         std::cout<<"dps_frac_dp->SetBinContent("<<dpbin<<","<<dpsN/totN<<");"<<std::endl;
        }
        totN=dpsN=0;
        std::cout<<" pT1 Bins "<<std::endl;
        for(int pt1bin=2; pt1bin<=npt1bins; ++pt1bin){
         totN =  a*scaledps*pt1_dps->GetBinContent(pt1bin) + (1-a)*scalenlo*pt1_nlogg->GetBinContent(pt1bin);
         dpsN = a*scaledps*pt1_dps->GetBinContent(pt1bin);
         //std::cout<<"Bin "<<pt1bin<<" DPS fraction: "<<dpsN/totN<<std::endl;
         std::cout<<"dps_frac_pt1->SetBinContent("<<pt1bin<<","<<dpsN/totN<<");"<<std::endl;
        }
        totN=dpsN=0;
        std::cout<<" pT2 Bins "<<std::endl;
        for(int pt2bin=2; pt2bin<=npt2bins; ++pt2bin){
         totN =  a*scaledps*pt2_dps->GetBinContent(pt2bin) + (1-a)*scalenlo*pt2_nlogg->GetBinContent(pt2bin);
         dpsN = a*scaledps*pt2_dps->GetBinContent(pt2bin);
         //std::cout<<"Bin "<<pt2bin<<" DPS fraction: "<<dpsN/totN<<std::endl;
         std::cout<<"dps_frac_pt2->SetBinContent("<<pt2bin<<","<<dpsN/totN<<");"<<std::endl;
        }
        totN=dpsN=0;
        std::cout<<" pTa Bins "<<std::endl;
        for(int ptabin=1; ptabin<=nptabins; ++ptabin){
         totN =  a*scaledps*pta_dps->GetBinContent(ptabin) + (1-a)*scalenlo*pta_nlogg->GetBinContent(ptabin);
         dpsN = a*scaledps*pta_dps->GetBinContent(ptabin);
         //std::cout<<"Bin "<<ptabin<<" DPS fraction: "<<dpsN/totN<<std::endl;
         std::cout<<"dps_frac_pta->SetBinContent("<<ptabin<<","<<dpsN/totN<<");"<<std::endl;
        }
        //        std::cout<<"a, b, c: "<<a<<" "<<b<<" "<<c<<" Chi2: "<<Chi2<<std::endl;
        //        std::cout<<a<<" "<<b<<" "<<c<<" "<<Chi2<<std::endl;
        Chi2=0;
    TCanvas* disp = new TCanvas("disp","disp",900,900);
    disp->Divide(2,2);
    TH1F *dPSum = new TH1F("dPSum","dPSum",ndpbins,dpbins);
    TH1F *dPBest = new TH1F("dPBest","dPBest",ndpbins,dpbins);
    TH1F *DpsBestdP = new TH1F("DpsBestdP","DpsBestdP",ndpbins,dpbins);
    TH1F *SpsBestdP = new TH1F("SpsBestdP","SpsBestdP",ndpbins,dpbins);
    TH1F *NloBestdP = new TH1F("NloBestdP","NloBestdP",ndpbins,dpbins);
    TH1F *pT1Best = new TH1F("pT1Best","pT1Best",npt1bins,pt1bins);
    TH1F *pT1Sum = new TH1F("pT1Sum","pT1Sum",npt1bins,pt1bins);
    TH1F *DpsBestpt1 = new TH1F("DpsBestpt1","DpsBestpt1",npt1bins,pt1bins);
    TH1F *SpsBestpt1 = new TH1F("SpsBestpt1","SpsBestpt1",npt1bins,pt1bins);
    TH1F *NloBestpt1 = new TH1F("NloBestpt1","NloBestpt1",npt1bins,pt1bins);
    TH1F *pT2Best = new TH1F("pT2Best","pT2Best",npt2bins,pt2bins);
    TH1F *pT2Sum = new TH1F("pT2Sum","pT2Sum",npt2bins,pt2bins);
    TH1F *DpsBestpt2 = new TH1F("DpsBestpt2","DpsBestpt2",npt2bins,pt2bins);
    TH1F *SpsBestpt2 = new TH1F("SpsBestpt2","SpsBestpt2",npt2bins,pt2bins);
    TH1F *NloBestpt2 = new TH1F("NloBestpt2","NloBestpt2",npt2bins,pt2bins);
    TH1F *pTaBest = new TH1F("pTaBest","pTaBest",nptabins,ptabins);
    TH1F *pTaSum = new TH1F("pTaSum","pTaSum",nptabins,ptabins);
    TH1F *DpsBestpta = new TH1F("DpsBestpta","DpsBestpta",nptabins,ptabins);
    TH1F *SpsBestpta = new TH1F("SpsBestpta","SpsBestpta",nptabins,ptabins);
    TH1F *NloBestpta = new TH1F("NloBestpta","NloBestpta",nptabins,ptabins);
    dPBest->SetMinimum(0);pT1Best->SetMinimum(0);pT2Best->SetMinimum(0);pTaBest->SetMinimum(0);
    dps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px))))>>DpsBestdP","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px))))>>SpsBestdP","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px))))>>NloBestdP","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    dps.Draw("Psi_pT[0]>>DpsBestpt1","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("Psi_pT[0]>>SpsBestpt1","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("Psi_pT[0]>>NloBestpt1","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    dps.Draw("Psi_pT[1]>>DpsBestpt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("Psi_pT[1]>>SpsBestpt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("Psi_pT[1]>>NloBestpt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    dps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>>DpsBestpta","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    sps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>>SpsBestpta","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    nlogg.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>>NloBestpta","(FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4)","goff");
    //MassSum->Add(DpsBest,(float) mina);
    //MassSum->Add(SpsBest,minb);
    //MassSum->Add(NloBest,minc);
    dPBest->SetMinimum(0);
    pT2Best->SetMaximum(200);
    pTaBest->SetMaximum(160);
    dPBest->SetXTitle("#Delta #phi between J/#psi");
    pT1Best->SetXTitle("Leading J/#psi pT (GeV)");
    pT2Best->SetXTitle("Subleading J/#psi pT (GeV)");
    pTaBest->SetXTitle("pT Assymetery between J/#psi");
    disp->cd(1);
    DpsBestdP->SetLineColor(kRed);
    SpsBestdP->SetLineColor(kBlue);
    NloBestdP->SetLineColor(kGreen);
    DpsBestdP->Scale(minan*scaledps);
    SpsBestdP->Scale(minbn*scalesps);
    NloBestdP->Scale(mincn*scalenlo);
    dPSum->Add(DpsBestdP);
    dPSum->Add(SpsBestdP);
    dPSum->Add(NloBestdP);
    data.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))),abs((TMath::ATan2(Psi1_py,Psi1_px))-(TMath::ATan2(Psi2_py,Psi2_px)))) >> dPBest","","e");
    dPSum->Draw("same");
    DpsBestdP->Draw("same");
    SpsBestdP->Draw("same");
    NloBestdP->Draw("same");
    TLegend *leg = new TLegend(0.6,0.7,0.90,0.9);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->AddEntry(DpsBestdP,"DPS model","l");
    leg->AddEntry(SpsBestdP,"SPS LO model","l");
    leg->AddEntry(NloBestdP,"SPS NLO model","l");
    leg->AddEntry(dPSum,"MC model sum","l");
    leg->AddEntry(dPBest,"Data","lep");
    leg->Draw();
    disp->cd(2);
    DpsBestpt1->SetLineColor(kRed);
    SpsBestpt1->SetLineColor(kBlue);
    NloBestpt1->SetLineColor(kGreen);
    DpsBestpt1->Scale(minan*scaledps);
    SpsBestpt1->Scale(minbn*scalesps);
    NloBestpt1->Scale(mincn*scalenlo);
    pT1Sum->Add(DpsBestpt1);
    pT1Sum->Add(SpsBestpt1);
    pT1Sum->Add(NloBestpt1);
    data.Draw("Psi_pT[0]>> pT1Best","","e");
    pT1Sum->Draw("same");
    DpsBestpt1->Draw("same");
    SpsBestpt1->Draw("same");
    NloBestpt1->Draw("same");
    leg->Draw();
    disp->cd(3);
    DpsBestpt2->SetLineColor(kRed);
    SpsBestpt2->SetLineColor(kBlue);
    NloBestpt2->SetLineColor(kGreen);
    DpsBestpt2->Scale(minan*scaledps);
    SpsBestpt2->Scale(minbn*scalesps);
    NloBestpt2->Scale(mincn*scalenlo);
    pT2Sum->Add(DpsBestpt2);
    pT2Sum->Add(SpsBestpt2);
    pT2Sum->Add(NloBestpt2);
    data.Draw("Psi_pT[1]>> pT2Best","","e");
    pT2Sum->Draw("same");
    DpsBestpt2->Draw("same");
    SpsBestpt2->Draw("same");
    NloBestpt2->Draw("same");
    leg->Draw();
    disp->cd(4);
    DpsBestpta->SetLineColor(kRed);
    SpsBestpta->SetLineColor(kBlue);
    NloBestpta->SetLineColor(kGreen);
    DpsBestpta->Scale(minan*scaledps);
    SpsBestpta->Scale(minbn*scalesps);
    NloBestpta->Scale(mincn*scalenlo);
    pTaSum->Add(DpsBestpta);
    pTaSum->Add(SpsBestpta);
    pTaSum->Add(NloBestpta);
    data.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> pTaBest","","e");
    pTaSum->Draw("same");
    DpsBestpta->Draw("same");
    SpsBestpta->Draw("same");
    NloBestpta->Draw("same");
    leg->Draw();
  }

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


int binfit_ttree_genlvl_3shapes_fast_toterr_newvars() {
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

  float dpbins[]={0,0.25,1.0,1.75,2.5,3.142};
  float pt1bins[]={5,10,12,14,17,20,25,60};
  float pt2bins[]={5,8,10,12,15,20,40};
  float ptabins[]={0,0.05,0.125,0.2,0.35,1.};
  int ndpbins = 5;
  int npt1bins = 7;
  int npt2bins = 6;
  int nptabins = 5;

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
  TH1F *dp_data = new TH1F("dp_data","dp_data",ndpbins,dpbins); 
  TH1F *dp_dps = new TH1F("dp_dps","dp_dps",ndpbins,dpbins); 
  TH1F *dp_nlogg = new TH1F("dp_nlogg","dp_nlogg",ndpbins,dpbins); 
  TH1F *dp_nlo = new TH1F("dp_nlo","dp_nlo",ndpbins,dpbins); 
  TH1F *dp_sps = new TH1F("dp_sps","dp_sps",ndpbins,dpbins); 
  TH1F *dp_width = new TH1F("dp_width","dp_width",ndpbins,dpbins); 
  TH1F *pt1_data = new TH1F("pt1_data","pt1_data",npt1bins,pt1bins); 
  TH1F *pt1_dps = new TH1F("pt1_dps","pt1_dps",npt1bins,pt1bins); 
  TH1F *pt1_nlogg = new TH1F("pt1_nlogg","pt1_nlogg",npt1bins,pt1bins); 
  TH1F *pt1_nlo = new TH1F("pt1_nlo","pt1_nlo",npt1bins,pt1bins); 
  TH1F *pt1_sps = new TH1F("pt1_sps","pt1_sps",npt1bins,pt1bins); 
  TH1F *pt1_width = new TH1F("pt1_width","pt1_width",npt1bins,pt1bins); 
  TH1F *pt2_data = new TH1F("pt2_data","pt2_data",npt2bins,pt2bins); 
  TH1F *pt2_dps = new TH1F("pt2_dps","pt2_dps",npt2bins,pt2bins); 
  TH1F *pt2_nlogg = new TH1F("pt2_nlogg","pt2_nlogg",npt2bins,pt2bins); 
  TH1F *pt2_nlo = new TH1F("pt2_nlo","pt2_nlo",npt2bins,pt2bins); 
  TH1F *pt2_sps = new TH1F("pt2_sps","pt2_sps",npt2bins,pt2bins); 
  TH1F *pt2_width = new TH1F("pt2_width","pt2_width",npt2bins,pt2bins); 
  TH1F *pta_data = new TH1F("pta_data","pta_data",nptabins,ptabins); 
  TH1F *pta_dps = new TH1F("pta_dps","pta_dps",nptabins,ptabins); 
  TH1F *pta_nlogg = new TH1F("pta_nlogg","pta_nlogg",nptabins,ptabins); 
  TH1F *pta_nlo = new TH1F("pta_nlo","pta_nlo",nptabins,ptabins); 
  TH1F *pta_sps = new TH1F("pta_sps","pta_sps",nptabins,ptabins); 
  TH1F *pta_width = new TH1F("pta_width","pta_width",nptabins,ptabins); 

  dp_data->SetBinContent(1,209.4656);
  dp_data->SetBinContent(2,69.02457);
  dp_data->SetBinContent(3,34.69847);
  dp_data->SetBinContent(4,20.12112);
  dp_data->SetBinContent(5,48.60252);
  dp_data->SetBinError(1,17.91482);
  dp_data->SetBinError(2,6.363967);
  dp_data->SetBinError(3,4.785995);
  dp_data->SetBinError(4,3.611484);
  dp_data->SetBinError(5,5.282882);

//  dp_data->SetBinContent(1,61.85498);
//  dp_data->SetBinContent(2,47.36565);
//  dp_data->SetBinContent(3,49.67321);
//  dp_data->SetBinContent(4,34.65094);
//  dp_data->SetBinContent(5,62.26616);
//  dp_data->SetBinError(1,5.290229);
//  dp_data->SetBinError(2,4.367046);
//  dp_data->SetBinError(3,6.851477);
//  dp_data->SetBinError(4,6.2194);
//  dp_data->SetBinError(5,6.76806);
  pt1_data->SetBinContent(1,17.98249);
  pt1_data->SetBinContent(2,20.29754);
  pt1_data->SetBinContent(3,13.24415);
  pt1_data->SetBinContent(4,5.774441);
  pt1_data->SetBinContent(5,2.390215);
  pt1_data->SetBinContent(6,1.380788);
  pt1_data->SetBinContent(7,0.1380014);
  pt1_data->SetBinError(1,2.229437);
  pt1_data->SetBinError(2,2.242569);
  pt1_data->SetBinError(3,1.517559);
  pt1_data->SetBinError(4,0.6394296);
  pt1_data->SetBinError(5,0.3345421);
  pt1_data->SetBinError(6,0.2161233);
  pt1_data->SetBinError(7,0.0262028);
  pt2_data->SetBinContent(1,36.13713);
  pt2_data->SetBinContent(2,26.1461);
  pt2_data->SetBinContent(3,10.42912);
  pt2_data->SetBinContent(4,2.576978);
  pt2_data->SetBinContent(5,0.4564093);
  pt2_data->SetBinContent(6,0.07642577);
  pt2_data->SetBinError(1,3.680634);
  pt2_data->SetBinError(2,2.490104);
  pt2_data->SetBinError(3,1.017475);
  pt2_data->SetBinError(4,0.31154);
  pt2_data->SetBinError(5,0.07606822);
  pt2_data->SetBinError(6,0.02266866);
  pta_data->SetBinContent(1,345.8567);
  pta_data->SetBinContent(2,1079.745);
  pta_data->SetBinContent(3,519.3201);
  pta_data->SetBinContent(4,301.3317);
  pta_data->SetBinContent(5,20.04797);
  pta_data->SetBinError(1,64.53302);
  pta_data->SetBinError(2,81.71044);
  pta_data->SetBinError(3,57.12521);
  pta_data->SetBinError(4,28.82303);
  pta_data->SetBinError(5,3.310673);

////stat error only. commment out for full error
//  mass_data->SetBinError(1,6.281534);
//  mass_data->SetBinError(2,2.358319);
//  mass_data->SetBinError(3,1.509835);
//  mass_data->SetBinError(4,1.177612);
//  mass_data->SetBinError(5,0.7126356);
//  mass_data->SetBinError(6,0.3761612);
//  mass_data->SetBinError(7,0.3408355);
//  mass_data->SetBinError(8,0.05351048);
//  pt_data->SetBinError(1,0.6928909);
//  pt_data->SetBinError(2,0.9048236);
//  pt_data->SetBinError(3,1.589567);
//  pt_data->SetBinError(4,1.189617);
//  pt_data->SetBinError(5,0.607507);
//  pt_data->SetBinError(6,0.06388734);
//  pt_data->SetBinError(7,0.01890572);
//  dy_data->SetBinError(1,28.61261);
//  dy_data->SetBinError(2,21.71715);
//  dy_data->SetBinError(3,14.11659);
//  dy_data->SetBinError(4,10.30196);
//  dy_data->SetBinError(5,6.846661);
//  dy_data->SetBinError(6,5.372485);
//  dy_data->SetBinError(7,4.64503);
//  dy_data->SetBinError(8,2.287784);
//  y_data->SetBinError(1,14.97098);
//  y_data->SetBinError(2,15.67618);
//  y_data->SetBinError(3,12.3992);
//  y_data->SetBinError(4,13.63791);
//  y_data->SetBinError(5,10.98304);
//  y_data->SetBinError(6,14.26707);
//  y_data->SetBinError(7,17.44995);
//  y_data->SetBinError(8,23.01054);
//  y_data->SetBinError(9,22.7678);


  dp_width->SetBinContent(1,0.25);
  dp_width->SetBinContent(2,0.75);
  dp_width->SetBinContent(3,0.75);
  dp_width->SetBinContent(4,0.75);
  dp_width->SetBinContent(5,0.642);
  pt1_width->SetBinContent(1,5.);
  pt1_width->SetBinContent(2,2.);
  pt1_width->SetBinContent(3,2.);
  pt1_width->SetBinContent(4,3.);
  pt1_width->SetBinContent(5,3.);
  pt1_width->SetBinContent(6,5.);
  pt1_width->SetBinContent(7,35);
  pt2_width->SetBinContent(1,3.);
  pt2_width->SetBinContent(2,2.);
  pt2_width->SetBinContent(3,2.);
  pt2_width->SetBinContent(4,3.);
  pt2_width->SetBinContent(5,5.);
  pt2_width->SetBinContent(6,20.);
  pta_width->SetBinContent(1,0.05);
  pta_width->SetBinContent(2,0.12);
  pta_width->SetBinContent(3,0.075);
  pta_width->SetBinContent(4,0.15);
  pta_width->SetBinContent(5,0.65);

  dps.Draw("Psi_pT[0]>> pt1_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  nlogg.Draw("Psi_pT[0] >> pt1_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  sps.Draw("Psi_pT[0] >> pt1_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  pt1_dps->Divide(pt1_width);
  pt1_nlogg->Divide(pt1_width);
  pt1_sps->Divide(pt1_width);
  datamass[0]=pt1_data->Integral("width");
  std::cout<<datamass[0]<<std::endl;
  dpsmass[0]=pt1_dps->Integral("width");
  spsmass[0]=pt1_sps->Integral("width");
  nloggmass[0]=pt1_nlogg->Integral("width");
  nlomass[0]=nloggmass[0];

  scaledps = datamass[0]/ (float) dpsmass[0];
  scalesps= datamass[0]/ (float) spsmass[0];
  scalenlo= datamass[0]/ (float) nloggmass[0];
  float Chi2dp=0;float Chi2pt1=0;float Chi2pt2=0;float Chi2pta=0;
  float minchi2norm=99999999.9;
  float minchi2=9999999.9;
  float minchi2dp=9999999.9;
  float minchi2pt1=9999999.9;
  float minchi2pt2=9999999.9;
  float minchi2pta=9999999.9;
  float mina, minb, minc, minan, minbn, mincn;

  //   Chi2 = Chi2 + pow((datamass[1] - (0.00*scaledps*dpsmass[1] + 0.0*scalesps*spsmass[1] + 0.0*scalenlo*nlomass[1])),2)/sqrt(datamass[1]);
  //  std::cout<<"Scale: " <<datamass[0]<<" " << dpsmass[0]<<" "<<scaledps<<" "<<scalesps<<" "<<scalenlo<<" "<<std::endl;
        dps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>> dp_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>> dp_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>> dp_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        dps.Draw("Psi_pT[0]>> pt1_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("Psi_pT[0]>> pt1_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("Psi_pT[0]>> pt1_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        dps.Draw("Psi_pT[1]>> pt2_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("Psi_pT[1]>> pt2_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("Psi_pT[1]>> pt2_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        dps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>> pta_dps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        nlogg.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1]) >> pta_nlogg","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.0)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
        sps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1]) >>pta_sps","FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.0)==2&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  dp_dps->Divide(dp_width);
  dp_nlogg->Divide(dp_width);
  dp_sps->Divide(dp_width);
  pt1_dps->Divide(pt1_width);
  pt1_nlogg->Divide(pt1_width);
  pt1_sps->Divide(pt1_width);
  pt2_dps->Divide(pt2_width);
  pt2_nlogg->Divide(pt2_width);
  pt2_sps->Divide(pt2_width);
  pta_dps->Divide(pta_width);
  pta_nlogg->Divide(pta_width);
  pta_sps->Divide(pta_width);
  for(float a=0.2; a<0.21; a=a+0.01){
    for(float b=0.0; b<0.001; b=b+0.01){
        for(int dpbin=1; dpbin<=ndpbins; ++dpbin){
          Chi2dp=Chi2dp + pow((dp_data->GetBinContent(dpbin) - (a*scaledps*dp_dps->GetBinContent(dpbin) + b*scalesps*dp_sps->GetBinContent(dpbin) + (1.-(a+b))*scalenlo*dp_nlogg->GetBinContent(dpbin)))/sqrt(pow(dp_data->GetBinError(dpbin),2)+pow((a*scaledps*dp_dps->GetBinContent(dpbin) + b*scalesps*dp_sps->GetBinContent(dpbin) + (1.-(a+b))*scalenlo*dp_nlogg->GetBinContent(dpbin))*0.3,2)),2);
          //Chi2m=Chi2m + pow((mass_data->GetBinContent(mbin) - (a*scaledps*mass_dps->GetBinContent(mbin) + b*scalesps*mass_sps->GetBinContent(mbin) + (1.-(a+b))*scalenlo*mass_nlogg->GetBinContent(mbin)))/mass_data->GetBinError(mbin),2);
          }
        for(int pt1bin=1; pt1bin<=npt1bins; ++pt1bin){
          //Chi2pt1=Chi2pt1 + pow((pt1_data->GetBinContent(pt1bin) - (a*scaledps*pt1_dps->GetBinContent(pt1bin) + b*scalesps*pt1_sps->GetBinContent(pt1bin) + (1.-(a+b))*scalenlo*pt1_nlogg->GetBinContent(pt1bin)))/pt1_data->GetBinError(pt1bin),2);
          Chi2pt1=Chi2pt1 + pow((pt1_data->GetBinContent(pt1bin) - (a*scaledps*pt1_dps->GetBinContent(pt1bin) + b*scalesps*pt1_sps->GetBinContent(pt1bin) + (1.-(a+b))*scalenlo*pt1_nlogg->GetBinContent(pt1bin)))/sqrt(pow(pt1_data->GetBinError(pt1bin),2)+pow((a*scaledps*pt1_dps->GetBinContent(pt1bin) + b*scalesps*pt1_sps->GetBinContent(pt1bin) + (1.-(a+b))*scalenlo*pt1_nlogg->GetBinContent(pt1bin))*0.3,2)),2);
            //         std::cout<<pt_data->GetBinContent(ptbin)<<std::endl;
        }
        for(int pt2bin=1; pt2bin<=npt2bins; ++pt2bin){
          Chi2pt2=Chi2pt2 + pow((pt2_data->GetBinContent(pt2bin) - (a*scaledps*pt2_dps->GetBinContent(pt2bin) + b*scalesps*pt2_sps->GetBinContent(pt2bin) + (1.-(a+b))*scalenlo*pt2_nlogg->GetBinContent(pt2bin)))/sqrt(pow(pt2_data->GetBinError(pt2bin),2)+pow((a*scaledps*pt2_dps->GetBinContent(pt2bin) + b*scalesps*pt2_sps->GetBinContent(pt2bin) + (1.-(a+b))*scalenlo*pt2_nlogg->GetBinContent(pt2bin))*0.3,2)),2);
          //Chi2dy=Chi2dy + pow((dy_data->GetBinContent(dybin) - (a*scaledps*dy_dps->GetBinContent(dybin) + b*scalesps*dy_sps->GetBinContent(dybin) + (1.-(a+b))*scalenlo*dy_nlogg->GetBinContent(dybin)))/dy_data->GetBinError(dybin),2);
          //           std::cout<<Chi2<<std::endl;
        }
        for(int ptabin=1; ptabin<=nptabins; ++ptabin){
          Chi2pta=Chi2pta + pow((pta_data->GetBinContent(ptabin) - (a*scaledps*pta_dps->GetBinContent(ptabin) + b*scalesps*pta_sps->GetBinContent(ptabin) + (1.-(a+b))*scalenlo*pta_nlogg->GetBinContent(ptabin)))/sqrt(pow(pta_data->GetBinError(ptabin),2)+pow((a*scaledps*pta_dps->GetBinContent(ptabin) + b*scalesps*pta_sps->GetBinContent(ptabin) + (1.-(a+b))*scalenlo*pta_nlogg->GetBinContent(ptabin))*0.3,2)),2);
          //Chi2y=Chi2y + pow((y_data->GetBinContent(ybin) - (a*scaledps*y_dps->GetBinContent(ybin) + b*scalesps*y_sps->GetBinContent(ybin) + (1.-(a+b))*scalenlo*y_nlogg->GetBinContent(ybin)))/y_data->GetBinError(ybin),2);
          //           std::cout<<Chi2<<std::endl;
        }
        //        std::cout<<"a, b, c: "<<a<<" "<<b<<" "<<c<<" Chi2: "<<Chi2<<std::endl;
        std::cout<<a<<" "<<b<<" "<<(1-(a+b))<<" "<<Chi2pt1+Chi2pt2+Chi2pta+Chi2dp<<std::endl;
        if (Chi2dp+Chi2pt1+Chi2pt2+Chi2pta<=minchi2){
          minchi2=Chi2dp+Chi2pt1+Chi2pt2+Chi2pta; minan = a; minbn = b; mincn=(1.-(a+b)); 
          minchi2dp=Chi2dp;minchi2pt1=Chi2pt1;minchi2pt2=Chi2pt2;minchi2pta=Chi2pta;
        
        }
        
        //        std::cout<<a<<" "<<b<<" "<<c<<" "<<Chi2<<std::endl;
        Chi2dp=0;Chi2pt1=0;Chi2pt2=0;Chi2pta=0;
    }
  }
    std::cout<<"Min Chi2: "<<minchi2dp<<" "<<minchi2pt1<<" "<<minchi2pt2<<" "<<minchi2pta<<" dps, sps, nlo: "<<minan<<" "<<minbn<<" "<<mincn<<std::endl;
    TCanvas* disp = new TCanvas("disp","disp",900,900);
    disp->Divide(2,2);
    TH1F *dpSum = new TH1F("dpSum","dpSum",ndpbins,dpbins);
    TH1F *dpBest = new TH1F("dpBest","dpBest",ndpbins,dpbins);
    TH1F *DpsBestdp = new TH1F("DpsBestdp","DpsBestdp",ndpbins,dpbins);
    TH1F *SpsBestdp = new TH1F("SpsBestdp","SpsBestdp",ndpbins,dpbins);
    TH1F *NloBestdp = new TH1F("NloBestdp","NloBestdp",ndpbins,dpbins);
    TH1F *pT1Best = new TH1F("pT1Best","pT1Best",npt1bins,pt1bins);
    TH1F *pT1Sum = new TH1F("pT1Sum","pT1Sum",npt1bins,pt1bins);
    TH1F *DpsBestpt1 = new TH1F("DpsBestpt1","DpsBestpt1",npt1bins,pt1bins);
    TH1F *NloBestpt1 = new TH1F("NloBestpt1","NloBestpt1",npt1bins,pt1bins);
    TH1F *SpsBestpt1 = new TH1F("SpsBestpt1","SpsBestpt1",npt1bins,pt1bins);
    TH1F *pT2Best = new TH1F("pT2Best","pT2Best",npt2bins,pt2bins);
    TH1F *pT2Sum = new TH1F("pT2Sum","pT2Sum",npt2bins,pt2bins);
    TH1F *DpsBestpt2 = new TH1F("DpsBestpt2","DpsBestpt2",npt2bins,pt2bins);
    TH1F *NloBestpt2 = new TH1F("NloBestpt2","NloBestpt2",npt2bins,pt2bins);
    TH1F *SpsBestpt2 = new TH1F("SpsBestpt2","SpsBestpt2",npt2bins,pt2bins);
    TH1F *pTaBest = new TH1F("pTaBest","pTaBest",nptabins,ptabins);
    TH1F *pTaSum = new TH1F("pTaSum","pTaSum",nptabins,ptabins);
    TH1F *DpsBestpta = new TH1F("DpsBestpta","DpsBestpta",nptabins,ptabins);
    TH1F *NloBestpta = new TH1F("NloBestpta","NloBestpta",nptabins,ptabins);
    TH1F *SpsBestpta = new TH1F("SpsBestpta","SpsBestpta",nptabins,ptabins);
    dpBest->SetMinimum(0);pT1Best->SetMinimum(0);pT2Best->SetMinimum(0);pTaBest->SetMinimum(0);
    dp_data->SetMinimum(0);pt1_data->SetMinimum(0);pt2_data->SetMinimum(0);pta_data->SetMinimum(0);
    dps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>>DpsBestdp","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>>NloBestdp","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("TMath::Min((2*TMath::Pi()-abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1])))),abs((TMath::ATan2(Psi_py[0],Psi_px[0]))-(TMath::ATan2(Psi_py[1],Psi_px[1]))))>>SpsBestdp","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    dps.Draw("Psi_pT[0]>>DpsBestpt1","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("Psi_pT[0]>>NloBestpt1","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("Psi_pT[0]>>SpsBestpt1","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    dps.Draw("Psi_pT[1]>>DpsBestpt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("Psi_pT[1]>>NloBestpt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("Psi_pT[1]>>SpsBestpt2","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    dps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>>DpsBestpta","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    nlogg.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>>NloBestpta","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
    sps.Draw("(Psi_pT[0]-Psi_pT[1])/(Psi_pT[0]+Psi_pT[1])>>SpsBestpta","(FourMu_Mass>=0&&FourMu_Mass<=60&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2)&&Sum$(Psi_Mass[]<3.35&&Psi_Mass>2.85)==2","goff");
  DpsBestdp->Divide(dp_width);
  NloBestdp->Divide(dp_width);
  SpsBestdp->Divide(dp_width);
  DpsBestpt1->Divide(pt1_width);
  NloBestpt1->Divide(pt1_width);
  SpsBestpt1->Divide(pt1_width);
  DpsBestpt2->Divide(pt2_width);
  NloBestpt2->Divide(pt2_width);
  SpsBestpt2->Divide(pt2_width);
  DpsBestpta->Divide(pta_width);
  NloBestpta->Divide(pta_width);
  SpsBestpta->Divide(pta_width);
    //dpSum->Add(DpsBest,(float) mina);
    //dpSum->Add(SpsBest,minb);
    //dpSum->Add(NloBest,minc);
    dp_data->SetMinimum(0);
    dp_data->SetXTitle("|#Delta #phi| between J/#psi");
    pt1_data->SetXTitle("Leading J/#psi pT (GeV)");
    pt2_data->SetXTitle("Sub-leading J/#psi pT (GeV)");
    pta_data->SetXTitle("J/#psi pT Asymmetery");
    dp_data->SetTitle("");
    pt1_data->SetTitle("");
    pt2_data->SetTitle("");
    pta_data->SetTitle("");
    disp->cd(1);
    DpsBestdp->SetLineColor(kRed);
    NloBestdp->SetLineColor(kGreen);
    SpsBestdp->SetLineColor(kBlue);
    DpsBestdp->Scale(minan*scaledps);
    NloBestdp->Scale(mincn*scalenlo);
    SpsBestdp->Scale(minbn*scalesps);
    dpSum->Add(DpsBestdp);
    dpSum->Add(NloBestdp);
    dpSum->Add(SpsBestdp);
    dp_data->Draw("E1");
    dpSum->Draw("same");
    DpsBestdp->Draw("same");
    NloBestdp->Draw("same");
    SpsBestdp->Draw("same");
    TLegend *leg = new TLegend(0.6,0.7,0.90,0.9);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->AddEntry(DpsBestdp,"DPS model","l");
    leg->AddEntry(NloBestdp,"SPS NLO model","l");
    leg->AddEntry(dpSum,"MC model sum","l");
    leg->AddEntry(dpBest,"Data","lep");
    leg->Draw();
    disp->cd(2);
    DpsBestpt1->SetLineColor(kRed);
    NloBestpt1->SetLineColor(kGreen);
    SpsBestpt1->SetLineColor(kBlue);
    DpsBestpt1->Scale(minan*scaledps);
    NloBestpt1->Scale(mincn*scalenlo);
    SpsBestpt1->Scale(minbn*scalesps);
    pT1Sum->Add(DpsBestpt1);
    pT1Sum->Add(NloBestpt1);
    pT1Sum->Add(SpsBestpt1);
    pt1_data->Draw("e1");
    pT1Sum->Draw("same");
    DpsBestpt1->Draw("same");
    NloBestpt1->Draw("same");
    SpsBestpt1->Draw("same");
    leg->Draw();
    disp->cd(3);
    DpsBestpt2->SetLineColor(kRed);
    NloBestpt2->SetLineColor(kGreen);
    SpsBestpt2->SetLineColor(kBlue);
    DpsBestpt2->Scale(minan*scaledps);
    NloBestpt2->Scale(mincn*scalenlo);
    SpsBestpt2->Scale(minbn*scalesps);
    pT2Sum->Add(DpsBestpt2);
    pT2Sum->Add(NloBestpt2);
    pT2Sum->Add(SpsBestpt2);
    pt2_data->Draw("e1");
    pT2Sum->Draw("same");
    DpsBestpt2->Draw("same");
    NloBestpt2->Draw("same");
    SpsBestpt2->Draw("same");
    leg->Draw();
    disp->cd(4);
    DpsBestpta->SetLineColor(kRed);
    NloBestpta->SetLineColor(kGreen);
    SpsBestpta->SetLineColor(kBlue);
    DpsBestpta->Scale(minan*scaledps);
    NloBestpta->Scale(mincn*scalenlo);
    SpsBestpta->Scale(minbn*scalesps);
    pTaSum->Add(DpsBestpta);
    pTaSum->Add(NloBestpta);
    pTaSum->Add(SpsBestpta);
    pta_data->Draw("e1");
    pTaSum->Draw("same");
    DpsBestpta->Draw("same");
    NloBestpta->Draw("same");
    SpsBestpta->Draw("same");
    leg->Draw();
  }

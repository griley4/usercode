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


int Xsec_calcTtreeFewerbins() {
  gROOT->Reset();

  float scaledps,scalesps,scalenlo,siggg,siggu,sigug;
  //  float datapt[60],datady[20],datay[20];
  TChain data("ntuple");
  TChain dps("PATEventTree");
  TChain sps("PATEventTree");
  TChain nlogg("PATEventTree");
  TChain nlogu("PATEventTree");
  TChain nloug("PATEventTree");
  float massbins[]={6.2,7,9,11,14,18,25,30,60};
  float massbins2[]={0,6.2,7,9,11,14,18,25,30,60};
  float ptbins[]={0,7,12,16,20,25,50,80};
  float dybins[]={0,0.2,0.4,0.6,0.9,1.3,1.8,2.4,4.5};
  //float ybins[]={-2.2,-1.8,-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.2};
  float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8};
  int nmbins = 8;
  int nmbins2 = 9;
  int nptbins = 7;
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
  float fracDPS = 0.13;
  float fracNLO = 0.87;
  float corrPop = 0;
  float corrPoppt = 0;
  float corrPopdy = 0;
  float corrPopy = 0;
  float xsec_sum_mass = 0;
  float xsec_sum_dy= 0;
  float xsec_sum_y= 0;
  float xsec_sum_pt = 0;
  float xsecerr_sum_mass = 0;
  float xsecerr_sum_dy= 0;
  float xsecerr_sum_y= 0;
  float xsecerr_sum_pt = 0;

  TH1F *mass_data = new TH1F("mass_data","mass_data",nmbins,massbins); 
  TH1F *pt_data = new TH1F("pt_data","pt_data",nptbins,ptbins); 
  TH1F *dy_data = new TH1F("dy_data","dy_data",ndybins,dybins); 
  TH1F *y_data = new TH1F("y_data","y_data",nybins,ybins); 
  TH1F *xsec_mass = new TH1F("xsec_mass","xsec_mass",nmbins2,massbins2); 
  TH1F *xsec_pt = new TH1F("xsec_pt","xsec_pt",nptbins,ptbins); 
  TH1F *xsec_dy = new TH1F("xsec_dy","xsec_dy",ndybins,dybins); 
  TH1F *xsec_y = new TH1F("xsec_y","xsec_y",nybins,ybins); 
  xsec_pt->SetMinimum(0);
  xsec_dy->SetMinimum(0);
  xsec_y->SetMinimum(0);
  data.Add("TMTight_Selected_newAcc.root");
  //data.Draw("FourMu_Mass>>mass_data","","egoff"); 
  //data.Draw("FourMu_pT>>pt_data","","egoff"); 
  //data.Draw("Psi1To2_dY>>dy_data","","egoff"); 
  //data.Draw("abs(FourMu_Rapidity)>>y_data","","egoff"); 
  mass_data->SetBinContent(1,74.); 
  mass_data->SetBinContent(2,99.);   
  mass_data->SetBinContent(3,53.);
  mass_data->SetBinContent(4,44.);
  mass_data->SetBinContent(5,44.);
  mass_data->SetBinContent(6,60.);
  mass_data->SetBinContent(7,47.);
  mass_data->SetBinContent(8,63.);
  mass_data->SetBinError(1,9.8); 
  mass_data->SetBinError(2,10.2);   
  mass_data->SetBinError(3,7.6);
  mass_data->SetBinError(4,7.1);
  mass_data->SetBinError(5,6.7);
  mass_data->SetBinError(6,8.2);
  mass_data->SetBinError(7,6.9);
  mass_data->SetBinError(8,8.4);
  pt_data->SetBinContent(1,70.);
  pt_data->SetBinContent(2,45.);
  pt_data->SetBinContent(3,46.);
  pt_data->SetBinContent(4,72.);
  pt_data->SetBinContent(5,107.);
  pt_data->SetBinContent(6,127.);
  pt_data->SetBinContent(7,13.5.);
  pt_data->SetBinError(1,8.8);
  pt_data->SetBinError(2,7.0);
  pt_data->SetBinError(3,7.4);
  pt_data->SetBinError(4,9.0);
  pt_data->SetBinError(5,11.3);
  pt_data->SetBinError(6,12.);
  pt_data->SetBinError(7,4.);
  dy_data->SetBinContent(1,178.);
  dy_data->SetBinContent(2,102.);
  dy_data->SetBinContent(3,56.);
  dy_data->SetBinContent(4,40.);
  dy_data->SetBinContent(5,35.);
  dy_data->SetBinContent(6,23.);
  dy_data->SetBinContent(7,25.);
  dy_data->SetBinContent(8,23.);
  dy_data->SetBinError(1,14.4);
  dy_data->SetBinError(2,10.6);
  dy_data->SetBinError(3,7.9);
  dy_data->SetBinError(4,6.9);
  dy_data->SetBinError(5,6.1);
  dy_data->SetBinError(6,5.2);
  dy_data->SetBinError(7,5.1);
  dy_data->SetBinError(8,5.0);
  y_data->SetBinContent(1,44.);
  y_data->SetBinContent(2,55.);
  y_data->SetBinContent(3,54.);
  y_data->SetBinContent(4,59.);
  y_data->SetBinContent(5,53.);
  y_data->SetBinContent(6,49.);
  y_data->SetBinContent(7,71.);
  y_data->SetBinContent(8,71.);
  y_data->SetBinContent(9,36.);    
  y_data->SetBinError(1,6.8);
  y_data->SetBinError(2,7.8);
  y_data->SetBinError(3,7.5);
  y_data->SetBinError(4,7.9);
  y_data->SetBinError(5,7.5);
  y_data->SetBinError(6,7.3);
  y_data->SetBinError(7,9.0);
  y_data->SetBinError(8,9.7);
  y_data->SetBinError(9,6.8);    


  //corrections from DPS PU
  TH1D *acc_eff_shape_dps = new TH1D("acc_eff_shape_dps","acc_eff_shape_dps",nmbins, massbins);
  acc_eff_shape_dps->SetBinContent(1,0.0138663);
  acc_eff_shape_dps->SetBinContent(2,0.007297057);
  acc_eff_shape_dps->SetBinContent(3,0.006983944);
  acc_eff_shape_dps->SetBinContent(4,0.006515777);
  acc_eff_shape_dps->SetBinContent(5,0.01513188);
  acc_eff_shape_dps->SetBinContent(6,0.0212844);
  acc_eff_shape_dps->SetBinContent(7,0.02075543);
  acc_eff_shape_dps->SetBinContent(8,0.01572297);
  acc_eff_shape_dps->SetBinError(1,0.005700007);
  acc_eff_shape_dps->SetBinError(2,0.002768073);
  acc_eff_shape_dps->SetBinError(3,0.002648884);
  acc_eff_shape_dps->SetBinError(4,0.001813029);
  acc_eff_shape_dps->SetBinError(5,0.002381015);
  acc_eff_shape_dps->SetBinError(6,0.002688715);
  acc_eff_shape_dps->SetBinError(7,0.003494953);
  acc_eff_shape_dps->SetBinError(8,0.001817671);

   TH1D *acc_eff_shape_dps_pt = new TH1D("acc_eff_shape_dps_pt","acc_eff_shape_dps_pt",nptbins, ptbins);
   acc_eff_shape_dps_pt->SetBinContent(1,0.01602381);
   acc_eff_shape_dps_pt->SetBinContent(2,0.01095174);
   acc_eff_shape_dps_pt->SetBinContent(3,0.01168921);
   acc_eff_shape_dps_pt->SetBinContent(4,0.02310725);
   acc_eff_shape_dps_pt->SetBinContent(5,0.04423705);
   acc_eff_shape_dps_pt->SetBinContent(6,0.03702168);
   acc_eff_shape_dps_pt->SetBinContent(7,0.0);
   acc_eff_shape_dps_pt->SetBinError(1,0.001870541);
   acc_eff_shape_dps_pt->SetBinError(2,0.001494617);
   acc_eff_shape_dps_pt->SetBinError(3,0.001580997);
   acc_eff_shape_dps_pt->SetBinError(4,0.003545111);
   acc_eff_shape_dps_pt->SetBinError(5,0.0100058);
   acc_eff_shape_dps_pt->SetBinError(6,0.01868969);
   acc_eff_shape_dps_pt->SetBinError(7,0.0);
   TH1D *acc_eff_shape_dps_dy = new TH1D("acc_eff_shape_dps_dy","acc_eff_shape_dps_dy",ndybins, dybins);
   acc_eff_shape_dps_dy->SetBinContent(1,0.01187512);
   acc_eff_shape_dps_dy->SetBinContent(2,0.01396993);
   acc_eff_shape_dps_dy->SetBinContent(3,0.01044501);
   acc_eff_shape_dps_dy->SetBinContent(4,0.02000486);
   acc_eff_shape_dps_dy->SetBinContent(5,0.02185234);
   acc_eff_shape_dps_dy->SetBinContent(6,0.0210377);
   acc_eff_shape_dps_dy->SetBinContent(7,0.02341459);
   acc_eff_shape_dps_dy->SetBinContent(8,0.009716729);
   acc_eff_shape_dps_dy->SetBinError(1,0.002292474);
   acc_eff_shape_dps_dy->SetBinError(2,0.002804204);
   acc_eff_shape_dps_dy->SetBinError(3,0.00290485);
   acc_eff_shape_dps_dy->SetBinError(4,0.003943803);
   acc_eff_shape_dps_dy->SetBinError(5,0.003885059);
   acc_eff_shape_dps_dy->SetBinError(6,0.003575585);
   acc_eff_shape_dps_dy->SetBinError(7,0.003635067);
   acc_eff_shape_dps_dy->SetBinError(8,0.00137765);
   TH1D *acc_eff_shape_dps_y = new TH1D("acc_eff_shape_dps_y","acc_eff_shape_dps_y",nybins, ybins);
   acc_eff_shape_dps_y->SetBinContent(1,0.01210623);
   acc_eff_shape_dps_y->SetBinContent(2,0.01308504);
   acc_eff_shape_dps_y->SetBinContent(3,0.0175725);
   acc_eff_shape_dps_y->SetBinContent(4,0.02233113);
   acc_eff_shape_dps_y->SetBinContent(5,0.0201226);
   acc_eff_shape_dps_y->SetBinContent(6,0.02391319);
   acc_eff_shape_dps_y->SetBinContent(7,0.01843923);
   acc_eff_shape_dps_y->SetBinContent(8,0.01026719);
   acc_eff_shape_dps_y->SetBinContent(9,0.009959938);
   acc_eff_shape_dps_y->SetBinContent(10,0.01246155);
   acc_eff_shape_dps_y->SetBinError(1,0.001672954);
   acc_eff_shape_dps_y->SetBinError(2,0.002365468);
   acc_eff_shape_dps_y->SetBinError(3,0.003476399);
   acc_eff_shape_dps_y->SetBinError(4,0.004192833);
   acc_eff_shape_dps_y->SetBinError(5,0.00414863);
   acc_eff_shape_dps_y->SetBinError(6,0.004745504);
   acc_eff_shape_dps_y->SetBinError(7,0.003721692);
   acc_eff_shape_dps_y->SetBinError(8,0.002307569);
   acc_eff_shape_dps_y->SetBinError(9,0.002675129);
   acc_eff_shape_dps_y->SetBinError(10,0.008866378);

   TH1D *acc_eff_shape_nlo = new TH1D("acc_eff_shape_nlo","acc_eff_shape_nlo",nmbins, massbins);
   acc_eff_shape_nlo->SetBinContent(1,0.02483095);
   acc_eff_shape_nlo->SetBinContent(2,0.0279386);
   acc_eff_shape_nlo->SetBinContent(3,0.03291799);
   acc_eff_shape_nlo->SetBinContent(4,0.02685266);
   acc_eff_shape_nlo->SetBinContent(5,0.03207134);
   acc_eff_shape_nlo->SetBinContent(6,0.0427784);
   acc_eff_shape_nlo->SetBinContent(7,0.06479052);
   acc_eff_shape_nlo->SetBinContent(8,0.1151735);
   acc_eff_shape_nlo->SetBinError(1,0.001987281);
   acc_eff_shape_nlo->SetBinError(2,0.001638146);
   acc_eff_shape_nlo->SetBinError(3,0.002336627);
   acc_eff_shape_nlo->SetBinError(4,0.002124807);
   acc_eff_shape_nlo->SetBinError(5,0.002363715);
   acc_eff_shape_nlo->SetBinError(6,0.002899397);
   acc_eff_shape_nlo->SetBinError(7,0.007934405);
   acc_eff_shape_nlo->SetBinError(8,0.01464195);

   TH1D *acc_eff_shape_nlo_pt = new TH1D("acc_eff_shape_nlo_pt","acc_eff_shape_nlo_pt",nptbins, ptbins);
   acc_eff_shape_nlo_pt->SetBinContent(1,0.02522776);
   acc_eff_shape_nlo_pt->SetBinContent(2,0.02213021);
   acc_eff_shape_nlo_pt->SetBinContent(3,0.01518503);
   acc_eff_shape_nlo_pt->SetBinContent(4,0.02341921);
   acc_eff_shape_nlo_pt->SetBinContent(5,0.04743189);
   acc_eff_shape_nlo_pt->SetBinContent(6,0.09842778);
   acc_eff_shape_nlo_pt->SetBinContent(7,0.09508368);
   acc_eff_shape_nlo_pt->SetBinError(1,0.002050204);
   acc_eff_shape_nlo_pt->SetBinError(2,0.001889677);
   acc_eff_shape_nlo_pt->SetBinError(3,0.001236359);
   acc_eff_shape_nlo_pt->SetBinError(4,0.001531429);
   acc_eff_shape_nlo_pt->SetBinError(5,0.002744452);
   acc_eff_shape_nlo_pt->SetBinError(6,0.005013865);
   acc_eff_shape_nlo_pt->SetBinError(7,0.03146514);

   TH1D *acc_eff_shape_nlo_dy = new TH1D("acc_eff_shape_nlo_dy","acc_eff_shape_nlo_dy",ndybins, dybins);
   acc_eff_shape_nlo_dy->SetBinContent(1,0.03273912);
   acc_eff_shape_nlo_dy->SetBinContent(2,0.03202487);
   acc_eff_shape_nlo_dy->SetBinContent(3,0.03638981);
   acc_eff_shape_nlo_dy->SetBinContent(4,0.02995349);
   acc_eff_shape_nlo_dy->SetBinContent(5,0.03100966);
   acc_eff_shape_nlo_dy->SetBinContent(6,0.02885756);
   acc_eff_shape_nlo_dy->SetBinContent(7,0.01757322);
   acc_eff_shape_nlo_dy->SetBinContent(8,0.05705021);
   acc_eff_shape_nlo_dy->SetBinError(1,0.001389774);
   acc_eff_shape_nlo_dy->SetBinError(2,0.001705956);
   acc_eff_shape_nlo_dy->SetBinError(3,0.002398764);
   acc_eff_shape_nlo_dy->SetBinError(4,0.002643527);
   acc_eff_shape_nlo_dy->SetBinError(5,0.003608469);
   acc_eff_shape_nlo_dy->SetBinError(6,0.005252726);
   acc_eff_shape_nlo_dy->SetBinError(7,0.007923561);
   acc_eff_shape_nlo_dy->SetBinError(8,0.03380871);

   TH1D *acc_eff_shape_nlo_y = new TH1D("acc_eff_shape_nlo_y","acc_eff_shape_nlo_y",nybins, ybins);
   acc_eff_shape_nlo_y->SetBinContent(1,0.0360656);
   acc_eff_shape_nlo_y->SetBinContent(2,0.03628627);
   acc_eff_shape_nlo_y->SetBinContent(3,0.04247071);
   acc_eff_shape_nlo_y->SetBinContent(4,0.04016971);
   acc_eff_shape_nlo_y->SetBinContent(5,0.04643257);
   acc_eff_shape_nlo_y->SetBinContent(6,0.03353658);
   acc_eff_shape_nlo_y->SetBinContent(7,0.0328369);
   acc_eff_shape_nlo_y->SetBinContent(8,0.02708806);
   acc_eff_shape_nlo_y->SetBinContent(9,0.02018681);
   acc_eff_shape_nlo_y->SetBinContent(10,0.007981328);
   acc_eff_shape_nlo_y->SetBinError(1,0.003532441);
   acc_eff_shape_nlo_y->SetBinError(2,0.003490384);
   acc_eff_shape_nlo_y->SetBinError(3,0.003746011);
   acc_eff_shape_nlo_y->SetBinError(4,0.003500181);
   acc_eff_shape_nlo_y->SetBinError(5,0.003492146);
   acc_eff_shape_nlo_y->SetBinError(6,0.002638296);
   acc_eff_shape_nlo_y->SetBinError(7,0.002224778);
   acc_eff_shape_nlo_y->SetBinError(8,0.001838354);
   acc_eff_shape_nlo_y->SetBinError(9,0.001845983);
   acc_eff_shape_nlo_y->SetBinError(10,0.003028673);

   TH1D *dps_frac_mass= new TH1D("dps_frac_mass","dps_frac_mass",nmbins, massbins);
dps_frac_mass->SetBinContent(1,0.0301084);
dps_frac_mass->SetBinContent(2,0.0190119);
dps_frac_mass->SetBinContent(3,0.0274898);
dps_frac_mass->SetBinContent(4,0.0615788);
dps_frac_mass->SetBinContent(5,0.15156);
dps_frac_mass->SetBinContent(6,0.189228);
dps_frac_mass->SetBinContent(7,0.295645);
dps_frac_mass->SetBinContent(8,0.476932);

   TH1D *dps_frac_pt= new TH1D("dps_frac_pt","dps_frac_pt",nptbins, ptbins);
dps_frac_pt->SetBinContent(1,0.283265);
dps_frac_pt->SetBinContent(2,0.242023);
dps_frac_pt->SetBinContent(3,0.229335);
dps_frac_pt->SetBinContent(4,0.129631);
dps_frac_pt->SetBinContent(5,0.0503911);
dps_frac_pt->SetBinContent(6,0.00799221);
dps_frac_pt->SetBinContent(7,0.000);

   TH1D *dps_frac_dy= new TH1D("dps_frac_dy","dps_frac_dy",ndybins, dybins);
dps_frac_dy->SetBinContent(1,0.0376058);
dps_frac_dy->SetBinContent(2,0.0539371);
dps_frac_dy->SetBinContent(3,0.0432607);
dps_frac_dy->SetBinContent(4,0.140195);
dps_frac_dy->SetBinContent(5,0.258465);
dps_frac_dy->SetBinContent(6,0.483106);
dps_frac_dy->SetBinContent(7,0.874272);
dps_frac_dy->SetBinContent(8,0.932418);

   TH1D *dps_frac_y = new TH1D("dps_frac_y","dps_frac_y",nybins, ybins);
dps_frac_y->SetBinContent(1,0.288885);
dps_frac_y->SetBinContent(2,0.186415);
dps_frac_y->SetBinContent(3,0.138392);
dps_frac_y->SetBinContent(4,0.149104);
dps_frac_y->SetBinContent(5,0.0969777);
dps_frac_y->SetBinContent(6,0.114167);
dps_frac_y->SetBinContent(7,0.0842319);
dps_frac_y->SetBinContent(8,0.0691124);
dps_frac_y->SetBinContent(9,0.0867541);

  TH1D *tnp_diff_m = new TH1D("tnp_diff_m","tnp_diff_m", nmbins,massbins);
//tnp_diff_m->SetBinContent(1,sqrt(pow(0.0545147,2)+pow(0.17606 ,2)) );
tnp_diff_m->SetBinContent(1,  0.225772 );
tnp_diff_m->SetBinContent(2,  0.195318);
tnp_diff_m->SetBinContent(3,  0.185349 );
tnp_diff_m->SetBinContent(4,  0.19523  );
tnp_diff_m->SetBinContent(5, 0.227704  );
tnp_diff_m->SetBinContent(6, 0.249557  );
tnp_diff_m->SetBinContent(7,  0.186917 );
tnp_diff_m->SetBinContent(8,  0.159981 );

  TH1D *tnp_diff_pt = new TH1D("tnp_diff_pt","tnp_diff_pt", nmbins,massbins);
tnp_diff_pt->SetBinContent(1, 0.242883  );
tnp_diff_pt->SetBinContent(2, 0.227406  );
tnp_diff_pt->SetBinContent(3, 0.262689  );
tnp_diff_pt->SetBinContent(4, 0.262272  );
tnp_diff_pt->SetBinContent(5,  0.200667 );
tnp_diff_pt->SetBinContent(6,  0.145214);
tnp_diff_pt->SetBinContent(7,  0.0741036);

  TH1D *tnp_diff_dy = new TH1D("tnp_diff_dy","tnp_diff_dy", nmbins,massbins);
tnp_diff_dy->SetBinContent(1,  0.202084);
tnp_diff_dy->SetBinContent(2,  0.197799);
tnp_diff_dy->SetBinContent(3, 0.218628 );
tnp_diff_dy->SetBinContent(4, 0.186049 );
tnp_diff_dy->SetBinContent(5, 0.174535 );
tnp_diff_dy->SetBinContent(6, 0.158371 );
tnp_diff_dy->SetBinContent(7, 0.256187 );
tnp_diff_dy->SetBinContent(8, 0.253261 );

  TH1D *tnp_diff_y = new TH1D("tnp_diff_y","tnp_diff_y", nmbins,massbins);
tnp_diff_y->SetBinContent(1,  0.179059);
tnp_diff_y->SetBinContent(2,  0.176668);
tnp_diff_y->SetBinContent(3, 0.167134 );
tnp_diff_y->SetBinContent(4,  0.159208);
tnp_diff_y->SetBinContent(5,  0.175817);
tnp_diff_y->SetBinContent(6,  0.205444);
tnp_diff_y->SetBinContent(7,  0.280293);
tnp_diff_y->SetBinContent(8,  0.273412);
tnp_diff_y->SetBinContent(9,  0.16372 );


  for(int mbin=1; mbin<=nmbins; ++mbin){
    corrPop = mass_data->GetBinContent(mbin)/(0.0593*0.0593*20.339*(1+0.5*tnp_diff_m->GetBinContent(mbin))*((dps_frac_mass->GetBinContent(mbin)*acc_eff_shape_dps->GetBinContent(mbin))+((1-dps_frac_mass->GetBinContent(mbin))*acc_eff_shape_nlo->GetBinContent(mbin)))*(massbins[mbin]-massbins[mbin-1]));
    xsec_mass->SetBinContent(mbin+1,corrPop*1e-3);
    xsec_sum_mass = xsec_sum_mass+(corrPop*1e-3*(massbins[mbin]-massbins[mbin-1]));
    xsec_mass->SetBinError(mbin+1, xsec_mass->GetBinContent(mbin+1)*(mass_data->GetBinError(mbin)/mass_data->GetBinContent(mbin)));
    xsecerr_sum_mass = 0;
  }
  for(int ptbin=1; ptbin<=nptbins; ++ptbin){
    corrPoppt = pt_data->GetBinContent(ptbin)/(pow(0.0593,2)*20.339*(1+0.5*tnp_diff_pt->GetBinContent(ptbin))*((dps_frac_pt->GetBinContent(ptbin)*acc_eff_shape_dps_pt->GetBinContent(ptbin))+((1.-dps_frac_pt->GetBinContent(ptbin))*acc_eff_shape_nlo_pt->GetBinContent(ptbin)))*(ptbins[ptbin]-ptbins[ptbin-1]));
    //            std::cout<<pt_data->GetBinContent(ptbin)<<" over "<<0.0593*0.0593*20.339<<" times "<<dps_frac_pt->GetBinContent(ptbin)<<" times "<<acc_eff_shape_dps_pt->GetBinContent(ptbin)<<" + "<<(1-(dps_frac_pt->GetBinContent(ptbin)))<<" times "<<acc_eff_shape_nlo_pt->GetBinContent(ptbin)<<" times "<<(ptbins[ptbin]-ptbins[ptbin-1])<<" equals??? "<<corrPoppt<<std::endl;
//            std::cout<<pt_data->GetBinContent(ptbin)<<" over "<<0.0593*0.0593*20.339<<" times "<<fracDPS<<" times "<<acc_eff_shape_dps_pt->GetBinContent(ptbin)<<" + "<<fracNLO<<" times "<<acc_eff_shape_nlo_pt->GetBinContent(ptbin)<<" times "<<(ptbins[ptbin]-ptbins[ptbin-1])<<" equals??? "<<corrPoppt<<std::endl;
    xsec_pt->SetBinContent(ptbin,corrPoppt*1e-3);
    xsec_sum_pt = xsec_sum_pt+(corrPoppt*1e-3*(ptbins[ptbin]-ptbins[ptbin-1]));
    xsec_pt->SetBinError(ptbin, xsec_pt->GetBinContent(ptbin)*(pt_data->GetBinError(ptbin)/pt_data->GetBinContent(ptbin)));
  }
  for(int dybin=1; dybin<=ndybins; ++dybin){
    corrPopdy = dy_data->GetBinContent(dybin)/(pow(0.0593,2)*20.339*(1+0.5*tnp_diff_dy->GetBinContent(dybin))*(dps_frac_dy->GetBinContent(dybin)*acc_eff_shape_dps_dy->GetBinContent(dybin)+(1-dps_frac_dy->GetBinContent(dybin))*acc_eff_shape_nlo_dy->GetBinContent(dybin))*(dybins[dybin]-dybins[dybin-1]));
    //          std::cout<<dy_data->GetBinContent(dybin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_dy->GetBinContent(dybin))+(fracNLO*acc_eff_shape_nlo_dy->GetBinContent(dybin)))<<" times "<<(dybins[dybin]-dybins[dybin-1])<<" equals??? "<<corrPopdy<<std::endl;
    xsec_dy->SetBinContent(dybin,corrPopdy*1e-3);
    xsec_sum_dy = xsec_sum_dy+(corrPopdy*1e-3*(dybins[dybin]-dybins[dybin-1]));
    xsec_dy->SetBinError(dybin, xsec_dy->GetBinContent(dybin)*(dy_data->GetBinError(dybin)/dy_data->GetBinContent(dybin)));
  }
  for(int ybin=1; ybin<=nybins; ++ybin){
    corrPopy = y_data->GetBinContent(ybin)/(pow(0.0593,2)*20.339*(1+0.5*tnp_diff_y->GetBinContent(ybin))*(dps_frac_y->GetBinContent(ybin)*acc_eff_shape_dps_y->GetBinContent(ybin)+(1-dps_frac_y->GetBinContent(ybin))*acc_eff_shape_nlo_y->GetBinContent(ybin))*(ybins[ybin]-ybins[ybin-1]));
    //          std::cout<<dy_data->GetBinContent(dybin)<<" over "<<0.0593*0.0593*20.339<<" times "<<((fracDPS*acc_eff_shape_dps_dy->GetBinContent(dybin))+(fracNLO*acc_eff_shape_nlo_dy->GetBinContent(dybin)))<<" times "<<(dybins[dybin]-dybins[dybin-1])<<" equals??? "<<corrPopdy<<std::endl;
    xsec_y->SetBinContent(ybin,corrPopy*1e-3);
    xsec_sum_y = xsec_sum_y+(corrPopy*1e-3*(ybins[ybin]-ybins[ybin-1]));
    xsec_y->SetBinError(ybin, xsec_y->GetBinContent(ybin)*(y_data->GetBinError(ybin)/y_data->GetBinContent(ybin)));
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
  xsec_mass->SetYTitle("d#sigma/dM_{J/#psi J/#psi} (pb/(GeV/c^{2}))");
  xsec_mass->SetTitleOffset(1.6,"Y");
  xsec_mass->Draw("e1");
  disp->cd(2);
  disp_2->SetLeftMargin(0.15);
  xsec_pt->SetXTitle("p_{T}^{J/#psi J/#psi} (GeV/c)");
  xsec_pt->SetYTitle("d#sigma/dp_{T}^{J/#psi J/#psi} (pb/(GeV/c))");
  xsec_pt->SetTitleOffset(1.7,"Y");
  xsec_pt->Draw("e1");
  disp->cd(3);
  disp_3->SetLeftMargin(0.15);
  xsec_dy->SetXTitle("|#Delta y| between J/#psi");
  xsec_dy->SetYTitle("d#sigma/d|#Delta y| (pb)");
  xsec_dy->SetTitleOffset(1.6,"Y");
  xsec_dy->Draw("e1");
  disp->cd(4);
  disp_4->SetLeftMargin(0.15);
  xsec_y->SetXTitle("|Rapidity|_{J/#psi J/#psi}");
  xsec_y->SetYTitle("d#sigma/d|y| (pb)");
  xsec_y->SetTitleOffset(1.6,"Y");
  xsec_y->Draw("e1");
  //  dy_data.Draw("e");    
}

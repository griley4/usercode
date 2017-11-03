#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooBifurGauss.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooChi2Var.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"

void fitSingleXsecRatio(){
  using namespace RooFit;
  RooRealVar ptmin("ptmin","ptmin",20.,95.);
  RooRealVar ptmax("ptmax","ptmax",20.,95.);
  RooRealVar ratio("ratio","ratio",0.,5.);
  RooRealVar error("error","error",0.,1.);

 bkg_p1mass2 = new RooRealVar("bkg_p1mass2","",0.5,-1,1);
 bkg_p2mass2 = new RooRealVar("bkg_p2mass2","",0.2,-1,1);
 bkg_p3mass2 = new RooRealVar("bkg_p3mass2","",0.2,-1,1);
 bkg_p4mass2 = new RooRealVar("bkg_p4mass2","",0.5,-1,1);
 bkg_p5mass2 = new RooRealVar("bkg_p5mass2","",-0.2,-1,1);

  RooChebychev poly("poly","",ptmin,RooArgList(*bkg_p1mass2,*bkg_p2mass2));
  //RooChebychev poly("poly","",ptmin,RooArgList(*bkg_p1mass2,*bkg_p2mass2,*bkg_p3mass2,*bkg_p4mass2,*bkg_p5mass2));

 float xsec_bins[]={20,21,22,23,24,25,26,27,28,29,30,32,34,36,38,42,46,50,60,75,95};
 int nxbins = 20;
 //TH1F* xsec = new TH1F("xsec","xsec",nxbins,xsec_bins);
 TH1F* xsec = new TH1F("xsec","xsec",20,0,95);
 xsec->SetBinContent(1 ,1.991);
 xsec->SetBinContent(2 ,2.005);
 xsec->SetBinContent(3 ,2.033);
 xsec->SetBinContent(4 ,2.073);
 xsec->SetBinContent(5 ,2.113);
 xsec->SetBinContent(6 ,2.124);
 xsec->SetBinContent(7 ,2.179);
 xsec->SetBinContent(8 ,2.262);
 xsec->SetBinContent(9 ,2.239);
 xsec->SetBinContent(10,2.343);
 xsec->SetBinContent(11,2.353);
 xsec->SetBinContent(12,2.397);
 xsec->SetBinContent(13,2.475);
 xsec->SetBinContent(14,2.428);
 xsec->SetBinContent(15,2.614);
 xsec->SetBinContent(16,2.636);
 xsec->SetBinContent(17,2.731);
 xsec->SetBinContent(18,2.904);
 xsec->SetBinContent(19,2.979);
 xsec->SetBinContent(20,3.004);
 xsec->SetBinError(1 ,6.7e-02);
 xsec->SetBinError(2 ,6.9e-02);
 xsec->SetBinError(3 ,6.7e-02);
 xsec->SetBinError(4 ,6.7e-02);
 xsec->SetBinError(5 ,6.8e-02);
 xsec->SetBinError(6 ,6.8e-02);
 xsec->SetBinError(7 ,6.8e-02);
 xsec->SetBinError(8 ,6.8e-02);
 xsec->SetBinError(9 ,6.9e-02);
 xsec->SetBinError(10,6.9e-02);
 xsec->SetBinError(11,6.9e-02);
 xsec->SetBinError(12,7.1e-02);
 xsec->SetBinError(13,7.4e-02);
 xsec->SetBinError(14,9.1e-02);
 xsec->SetBinError(15,9.2e-02);
 xsec->SetBinError(16,9.6e-02);
 xsec->SetBinError(17,9.8e-02);
 xsec->SetBinError(18,1.4e-01);
 xsec->SetBinError(19,1.4e-01);
 xsec->SetBinError(20,1.5e-01);

  
  hist_xsec= new RooDataHist("hist_xsec","hist_xsec",RooArgList(ptmin),xsec);
//  RooArgSet dataVars(ptmin,ptmax,ratio,error);
//  RooDataSet* readdata = RooDataSet::read("jpsi_7tev.txt",dataVars);
//  RooDataSet* data ;
//  data = new RooDataSet("data","data",readdata ,dataVars);
  number = new RooRealVar("number","number",1,1,400);
  RooPlot* frame2 = ptmin.frame(Title("pT"));
  frame2 = ptmin.frame(20);
  hist_xsec->plotOn(frame2);

 RooAddPdf model("model","model",RooArgList(poly),RooArgList(*number)); 
  model.fitTo(*hist_xsec,SumW2Error(kTRUE));
  //model.chi2FitTo(*hist_xsec);

  model.plotOn(frame2);
  frame2->Draw();
  //c2->SaveAs("pic/Psi2_mass.pdf");
  //c2->Close();
}

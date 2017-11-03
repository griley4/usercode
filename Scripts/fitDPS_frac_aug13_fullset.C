#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooBifurGauss.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"

void fitDPS_frac_aug13_fullset(){
  using namespace RooFit;
  

  RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.85,3.35);
  RooRealVar FourMu_Mass("FourMu_Mass","FourMu_Mass",0.,300.);
  RooRealVar FourMu_pT("FourMu_pT","FourMu_pT",0.,80.);
  RooRealVar FourMu_RapidityAbs("FourMu_RapidityAbs","FourMu_RapidityAbs",0.,1.8);
  RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",0.0,3.6);

  //reshuffle shape for delta y 2 paris per event
//  dps_dy_p0 = new RooRealVar("dps_dy_p0","",-9.26946e-01,-1,1);
//  dps_dy_p1 = new RooRealVar("dps_dy_p1","",5.59079e-02,-1,1);
//  dps_dy_p2 = new RooRealVar("dps_dy_p2","",-1.37646e-01,-1,1);
//  dps_dy_p3 = new RooRealVar("dps_dy_p3","",3.14491e-03,-1,1);
//  dps_dy_p4 = new RooRealVar("dps_dy_p4","",4.50327e-02,-1,1);
//  RooChebychev dps_dy("dps_dy","",Psi1To2_dY,RooArgList(*dps_dy_p0,*dps_dy_p1,*dps_dy_p2,*dps_dy_p3,*dps_dy_p4));
  //reshuffle shape for delta y
  dps_dy_p0 = new RooRealVar("dps_dy_p0","",-9.24843e-01);
  dps_dy_p1 = new RooRealVar("dps_dy_p1","",5.24759e-02);
  dps_dy_p2 = new RooRealVar("dps_dy_p2","",-1.34973e-01);
  dps_dy_p3 = new RooRealVar("dps_dy_p3","",9.32637e-04);
  dps_dy_p4 = new RooRealVar("dps_dy_p4","",4.63581e-02);
  //RooChebychev dps_dy("dps_dy","",Psi1To2_dY,RooArgList(*dps_dy_p0,*dps_dy_p1,*dps_dy_p2,*dps_dy_p3));
  RooChebychev dps_dy("dps_dy","",Psi1To2_dY,RooArgList(*dps_dy_p0,*dps_dy_p1,*dps_dy_p2,*dps_dy_p3,*dps_dy_p4));
  //NLO MC shape for delta y
  //nlo_dy_p0 = new RooRealVar("nlo_dy_p0","",-3.22512);
  nlo_dy_p0 = new RooRealVar("nlo_dy_p0","",-2.67283e+00);
  RooExponential nlo_dy("nlo_dy","",Psi1To2_dY,*nlo_dy_p0);

  //DeltaY combined shape
  frac_dy = new RooRealVar("frac_dy","",0.5,0,1);
  RooAddPdf both_dy("both_dy","both_dy",RooArgList(dps_dy,nlo_dy),RooArgList(*frac_dy));

  //DPS MC Y shape
  dps_y_p0 = new RooRealVar("dps_y_p0","",-1.24729e-01 );
  dps_y_p1 = new RooRealVar("dps_y_p1","",7.03629e-01);
  dps_y_p2 = new RooRealVar("dps_y_p2","",-5.78798e-01);
  dps_y_p3 = new RooRealVar("dps_y_p3","",-1.39076);
  dps_y_p4 = new RooRealVar("dps_y_p4","",4.10994e-01);
  RooChebychev dps_y_1("dps_y_1","",FourMu_RapidityAbs,RooArgList(*dps_y_p0,*dps_y_p1,*dps_y_p2));
  RooExponential dps_y_2("dps_y_2","",FourMu_RapidityAbs,*dps_y_p3);
  RooAddPdf dps_y("dps_y","dps_y",RooArgList(dps_y_1,dps_y_2),RooArgList(*dps_y_p4));

  //NLO MC Y shape
  nlo_y_p0 = new RooRealVar("nlo_y_p0","",1.48447);
  nlo_y_p1 = new RooRealVar("nlo_y_p1","",2.50631e-01);
  nlo_y_p2 = new RooRealVar("nlo_y_p2","",6.62438e-01);
  nlo_y_p3 = new RooRealVar("nlo_y_p3","",4.11870e-01);
  //RooChebychev nlo_y("nlo_y","",FourMu_RapidityAbs,RooArgList(*nlo_y_p0,*nlo_y_p1,*nlo_y_p2,*nlo_y_p3));
  RooCBShape  nlo_y("nlo_y","nlo_y",FourMu_RapidityAbs,*nlo_y_p0,*nlo_y_p1,*nlo_y_p2,*nlo_y_p3);
 
  //Y combined shape
  frac_y = new RooRealVar("frac_y","",0.5,0,1);
  RooAddPdf both_y("both_y","both_y",RooArgList(dps_y,nlo_y),RooArgList(*frac_y)); 

  //DPS MC pT shape GEN
  dps_pt_p0 = new RooRealVar("dps_pt_p0","",3.33387);
  dps_pt_p1 = new RooRealVar("dps_pt_p1","",1.64025);
  dps_pt_p2 = new RooRealVar("dps_pt_p2","",1.29822e-01);
  dps_pt_p3 = new RooRealVar("dps_pt_p3","",1.16266e+01);
  dps_pt_p4 = new RooRealVar("dps_pt_p4","",4.96686);
  RooGaussian dps_pt_1("dps_pt1","dps_pt1",FourMu_pT,*dps_pt_p0,*dps_pt_p1);
  RooGaussian dps_pt_2("dps_pt2","dps_pt2",FourMu_pT,*dps_pt_p3,*dps_pt_p4);
  RooAddPdf dps_pt("dps_pt","dps_pt",RooArgList(dps_pt_1,dps_pt_2),RooArgList(*dps_pt_p2));
  ////DPS MC pT shape RECO
  //dps_pt_p0 = new RooRealVar("dps_pt_p0","",4.47910);
  //dps_pt_p1 = new RooRealVar("dps_pt_p1","",2.45127);
  //dps_pt_p2 = new RooRealVar("dps_pt_p2","",3.15825e-01);
  //dps_pt_p3 = new RooRealVar("dps_pt_p3","",1.49660e+01);
  //dps_pt_p4 = new RooRealVar("dps_pt_p4","",4.75934);
  //RooGaussian dps_pt_1("dps_pt1","dps_pt1",FourMu_pT,*dps_pt_p0,*dps_pt_p1);
  //RooGaussian dps_pt_2("dps_pt2","dps_pt2",FourMu_pT,*dps_pt_p3,*dps_pt_p4);
  //RooAddPdf dps_pt("dps_pt","dps_pt",RooArgList(dps_pt_1,dps_pt_2),RooArgList(*dps_pt_p2));


  //NLO MC pT shape GEN
  nlo_pt_p0 = new RooRealVar("nlo_pt_p0","",3.78462);
  nlo_pt_p1 = new RooRealVar("nlo_pt_p1","",2.01436);
  nlo_pt_p2 = new RooRealVar("nlo_pt_p2","",1.00271e-01);
  nlo_pt_p3 = new RooRealVar("nlo_pt_p3","",1.62007e+01);
  nlo_pt_p4 = new RooRealVar("nlo_pt_p4","",5.81421);
  nlo_pt_p5 = new RooRealVar("nlo_pt_p5","",-1.19218);
  nlo_pt_p6 = new RooRealVar("nlo_pt_p6","",1.45409e+02);
  RooGaussian nlo_pt_1("nlo_pt1","nlo_pt1",FourMu_pT,*nlo_pt_p0,*nlo_pt_p1);
  RooCBShape  nlo_pt_2("nlo_pt2","nlo_pt2",FourMu_pT,*nlo_pt_p3,*nlo_pt_p4,*nlo_pt_p5,*nlo_pt_p6);
  RooAddPdf nlo_pt("nlo_pt","nlo_pt",RooArgList(nlo_pt_1,nlo_pt_2),RooArgList(*nlo_pt_p2));
//  //NLO MC pT shape RECO
//  nlo_pt_p0 = new RooRealVar("nlo_pt_p0","",5.56031);
//  nlo_pt_p1 = new RooRealVar("nlo_pt_p1","",3.39767);
//  nlo_pt_p2 = new RooRealVar("nlo_pt_p2","",1.52329e-01);
//  nlo_pt_p3 = new RooRealVar("nlo_pt_p3","",2.18093e+01);
//  nlo_pt_p4 = new RooRealVar("nlo_pt_p4","",7.14216);
//  nlo_pt_p5 = new RooRealVar("nlo_pt_p5","",-1.18356);
//  nlo_pt_p6 = new RooRealVar("nlo_pt_p6","",1.38303e+02);
//  RooGaussian nlo_pt_1("nlo_pt1","nlo_pt1",FourMu_pT,*nlo_pt_p0,*nlo_pt_p1);
//  RooCBShape  nlo_pt_2("nlo_pt2","nlo_pt2",FourMu_pT,*nlo_pt_p3,*nlo_pt_p4,*nlo_pt_p5,*nlo_pt_p6);
//  RooAddPdf nlo_pt("nlo_pt","nlo_pt",RooArgList(nlo_pt_1,nlo_pt_2),RooArgList(*nlo_pt_p2));

  //pT combined shape
  frac_pt = new RooRealVar("frac_pt","",0.5,0,1);
  RooAddPdf both_pt("both_pt","both_pt",RooArgList(dps_pt,nlo_pt),RooArgList(*frac_pt));

  RooArgSet dataVars(Psi1_Mass, Psi2_Mass,Psi1To2_dY, FourMu_Mass, FourMu_pT, FourMu_RapidityAbs);
  //RooDataSet* readdata = RooDataSet::read("nlofullset_fit_aug13.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("dpsfullset_fit_aug13.txt",dataVars);
  RooDataSet* readdata = RooDataSet::read("datafullset_fit_aug13.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("DPSMLF_shuffle_pt8.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("nlofullset_genfit_aug13.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("dpsfullset_genfit_aug13.txt",dataVars);
  RooDataSet* data ;
  data = new RooDataSet("data","data",readdata ,dataVars);
 float ptbins[]={0,7,12,16,20,25,50,80};
 int nptbins = 7;
 TH1F* pthist = new TH1F("pthist","pthist",nptbins,ptbins);
  pthist->SetBinContent(1,5.5);
  pthist->SetBinContent(2,5.8);
  pthist->SetBinContent(3,10.);
  pthist->SetBinContent(4,9.5);
  pthist->SetBinContent(5,5.8);
  pthist->SetBinContent(6,0.68);
  pthist->SetBinContent(7,0.064);
  pthist->SetBinError(1,0.7);
  pthist->SetBinError(2,0.9);
  pthist->SetBinError(3,1.6);
  pthist->SetBinError(4,1.2);
  pthist->SetBinError(5,0.6);
  pthist->SetBinError(6,0.06);
  pthist->SetBinError(7,0.02);
  float ybins[]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8};
  int nybins = 9;
 TH1F* yhist = new TH1F("yhist","yhist",nybins,ybins);
 yhist->SetBinContent(1,96.6);
 yhist->SetBinContent(2,110.3);
 yhist->SetBinContent(3,89.3);
 yhist->SetBinContent(4,101.9);
 yhist->SetBinContent(5,77.6);
 yhist->SetBinContent(6,95.8);
 yhist->SetBinContent(7,137.7);
 yhist->SetBinContent(8,168.4);
 yhist->SetBinContent(9,120.5);
 yhist->SetBinError(1,15.);
 yhist->SetBinError(1,15.7);
 yhist->SetBinError(1,12.4);
 yhist->SetBinError(1,13.6);
 yhist->SetBinError(1,11.0);
 yhist->SetBinError(1,14.3);
 yhist->SetBinError(1,17.4);
 yhist->SetBinError(1,23.0);
 yhist->SetBinError(1,22.8);
 
 float dybins[]={0,0.2,0.4,0.6,0.9,1.3,1.8,2.4,3.8};
 int ndybins = 8;
 TH1F* dyhist = new TH1F("dyhist","dyhist",ndybins,dybins);
 dyhist->SetBinContent(1,353.7);
 dyhist->SetBinContent(2,209.0);
 dyhist->SetBinContent(3,100.0);
 dyhist->SetBinContent(4,59.7);
 dyhist->SetBinContent(5,39.3);
 dyhist->SetBinContent(6,23.8);
 dyhist->SetBinContent(7,22.8);
 dyhist->SetBinContent(8,15.7);
 dyhist->SetBinError(1,28.6);
 dyhist->SetBinError(2,21.7);
 dyhist->SetBinError(3,14.1);
 dyhist->SetBinError(4,10.3);
 dyhist->SetBinError(5,6.8);
 dyhist->SetBinError(6,5.4);
 dyhist->SetBinError(7,4.6);
 dyhist->SetBinError(8,3.4);

//  hist_y = new RooDataHist("hist_y","hist_y",RooArgList(FourMu_RapidityAbs),yhist);
//  hist_dy = new RooDataHist("hist_dy","hist_dy",RooArgList(Psi1To2_dY),dyhist);
//  hist_pt = new RooDataHist("hist_pt","hist_pt",RooArgList(FourMu_pT),pthist);
//  pdf_y = new RooHistPdf("pdf_y","pdf_y",RooArgList(FourMu_RapidityAbs),*hist_y);
//  pdf_dy = new RooHistPdf("pdf_dy","pdf_dy",RooArgList(Psi1To2_dY),*hist_dy);
//  pdf_pt = new RooHistPdf("pdf_pt","pdf_pt",RooArgList(FourMu_pT),*hist_pt);
//  data_model = new RooProdPdf("data_model","data_model",RooArgList(*pdf_pt,*pdf_y));

  RooProdPdf dps_model("dps_model","dps_model",RooArgList(dps_dy));
  RooProdPdf nlo_model("nlo_model","nlo_model",RooArgList(nlo_dy));
  ndps = new RooRealVar("ndps","",80,0,200); 
  //ndps = new RooRealVar("ndps","",1,0,2000); 
  nnlo = new RooRealVar("nnlo","",5,0,2000); 
  fdps = new RooRealVar("fdps","",0.5,0,1); 
  //RooAddPdf model("model","model",RooArgList(dps_model,nlo_model),RooArgList(*ndps,*nnlo));
  RooAddPdf model("model","model",RooArgList(dps_model,nlo_model),RooArgList(*ndps,*nnlo));
//  dps_dy.fitTo(*data,Hesse(kTRUE),Minos(kFALSE));
  model.fitTo(*data,Extended(kTRUE),Hesse(kTRUE),Minos(kFALSE));
//  nlo_dy.fitTo(*data,Hesse(kTRUE),Minos(kFALSE));
  TCanvas* c1 = new TCanvas("c1","c1",800,800);
//    c1->Divide(2,1);
//    c1->cd(1);
//    RooPlot* frame1 = FourMu_pT.frame(Title("pT (GeV)"));
//    frame1 = FourMu_pT.frame(7);
//    hist_pt->plotOn(frame1);
//    model.plotOn(frame1,LineColor(kBlack));
//    model.plotOn(frame1,Components("DPS,dps_pt"),LineColor(kRed),LineStyle(kDashed));
//    model.plotOn(frame1,Components("NLO,nlo_pt"),LineColor(kBlue),LineStyle(kDotted));
//    frame1->Draw();
//    c1->cd(2);
//    c1->Divide(1,2);
    RooPlot* frame2 = Psi1To2_dY.frame(Title("#Delta y"));
    frame2 = Psi1To2_dY.frame(25);
//    hist_dy->plotOn(frame2);
    data->plotOn(frame2,LineColor(kBlack));
//    float chi = frame2->chiSquare();
//    RooHist* pull_dy= frame2->pullHist();
    model.plotOn(frame2,LineColor(kBlack));
    model.plotOn(frame2,Components("DPS,dps_dy"),LineColor(kRed),LineStyle(kDashed));
    model.plotOn(frame2,Components("NLO,nlo_dy"),LineColor(kBlue),LineStyle(kDotted));
//    pull_dy->SetMarkerSize(.7);
//    RooPlot* frame_dy= Psi1To2_dY.frame(Bins(20));
//    frame_dy->addPlotable(pull_dy,"P");
    frame2->SetXTitle("|#Delta Y| Between J/#psi");
//    frame_dy->SetXTitle("|#Delta Y| Between J/#psi");
//    c1->cd(1);
    frame2->Draw();
////    c1->cd(2);
////    frame_dy->Draw();
//    std::cout<<"Chi2 = "<<chi<<std::endl;
//    c1->cd(2);
//    RooPlot* frame3 = FourMu_RapidityAbs.frame(Title("Rapidity"));
//    frame3 = FourMu_RapidityAbs.frame(9);
//    hist_y->plotOn(frame3);
//    model.plotOn(frame3,LineColor(kBlack));
//    model.plotOn(frame3,Components("DPS,dps_y"),LineColor(kRed),LineStyle(kDashed));
//    model.plotOn(frame3,Components("NLO,nlo_y"),LineColor(kBlue),LineStyle(kDotted));
//    frame3->SetMinimum(0);
//    frame3->Draw();
//
//  
    //RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot");
//    RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot",*data, &model, RooArgList(*ndps,*nnlo));
//
//  // Check that our weights have the desired properties
//
//  std::cout << "Check SWeights:" << std::endl;
//
//  std::cout << std::endl <<  "Yield of dps is " 
//	    << ndps->getVal() << ".  From sWeights it is "
//	    << sData->GetYieldFromSWeight("ndps") << std::endl;
//
//  std::cout << std::endl <<  "Yield of nlo is " 
//	    << nnlo->getVal() << ".  From sWeights it is "
//	    << sData->GetYieldFromSWeight("nnlo") << std::endl;
//
//  cout << endl;   cout << endl;   cout << endl;
//  float sum20=0;
//  float sum50=0;
//  float sum100=0;
//  float sum200=0;
//  float sum300=0;
//  float sum400=0;
//  float total=0;
//
//  // saving weights into a file
//  ofstream myfile;
//  myfile.open ("DPSweights_syst_fixnlo_floatdps.txt");
//  // plot the weight event by event with the Sum of events values as cross-check
//  for(Int_t i=0; i < data->numEntries(); i++) {
//      //myfile << sData->GetSWeight(i,"nsig") << " " << sData->GetSWeight(i,"nBbkg") << " " << sData->GetSWeight(i,"nbkg") << " " << sData->GetSWeight(i,"nbkg2") << endl;  
//      //myfile << sData->GetSWeight(i,"nsig") <<endl;
//    myfile 
//	   << " " << (float) data->get(i)->getRealValue("FourMu_Mass")
//	   << " " << (float) data->get(i)->getRealValue("FourMu_pT")
//	   << " " << (float) data->get(i)->getRealValue("Psi1To2_dY")
//	   << " " << (float) data->get(i)->getRealValue("Psi1_Mass")
//	   << " " << (float) data->get(i)->getRealValue("Psi2_Mass")
//	   << " " << (float) data->get(i)->getRealValue("FourMu_RapidityAbs")
//             << " " << sData->GetSWeight(i,"ndps")
//             << " " << sData->GetSWeight(i,"nnlo")
//             << endl;
//      total+=sData->GetSWeight(i,"ndps");         
//      if(i<20) sum20+=sData->GetSWeight(i,"ndps");
//      if(i<50) sum50+=sData->GetSWeight(i,"ndps");
//      if(i<100) sum100+=sData->GetSWeight(i,"ndps");
//      if(i<200) sum200+=sData->GetSWeight(i,"ndps");
//      if(i<300) sum300+=sData->GetSWeight(i,"ndps");
//      if(i<400) sum400+=sData->GetSWeight(i,"ndps");
//
//    }
//  myfile.close();
//
//  std::cout << std::endl;
//
//  std::cout<<"Sum of the sWeights is: "<<total<<std::endl;
//  std::cout<<"Sum of the first 20 sWeights is: "<<sum20<<std::endl;
//  std::cout<<"Sum of the first 50 sWeights is: "<<sum50<<std::endl;
//  std::cout<<"Sum of the first 100 sWeights is: "<<sum100<<std::endl;
//  std::cout<<"Sum of the first 200 sWeights is: "<<sum200<<std::endl;
//  std::cout<<"Sum of the first 300 sWeights is: "<<sum300<<std::endl;
//  std::cout<<"Sum of the first 400 sWeights is: "<<sum400<<std::endl;
//  std::cout<<"Total # of events: "<<data->numEntries()<<std::endl;

//NLL stuff and chi2

//  RooMCStudy *mgr = new RooMCStudy(model,RooArgSet(Psi1To2_dY, FourMu_pT, FourMu_RapidityAbs),Silence(),Extended(),FitOptions(Save(kTRUE),PrintEvalErrors(0)));
//
//  mgr->generateAndFit(10000);
//  RooPlot* frame0 = mgr->plotNLL(-6800.0,-4800.0,80);
//  RooPlot* frame1a = mgr->plotParam(ndps,Bins(40));                                                                                   
//  RooPlot* frame1b = mgr->plotError(ndps,FrameRange(60,100),FrameBins(40));                                                                                       
//  RooPlot* frame1c = mgr->plotPull(ndps,FrameRange(-5,5),FrameBins(20),FitGauss(kTRUE));
//
//
//  RooPlot* frame3a = mgr->plotParam(nnlo,Bins(40));                              
//  RooPlot* frame3b = mgr->plotError(nnlo,Bins(40));
//  RooPlot* frame3c = mgr->plotPull(nnlo,FrameRange(-3,3),FrameBins(20),FitGauss(kTRUE));

}

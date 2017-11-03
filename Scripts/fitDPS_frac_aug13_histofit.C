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

void fitDPS_frac_aug13_histofit(){
  using namespace RooFit;
  

  RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.85,3.35);
  RooRealVar FourMu_Mass("FourMu_Mass","FourMu_Mass",0.,300.);
  RooRealVar FourMu_pT("FourMu_pT","FourMu_pT",0.,80.);
  RooRealVar FourMu_RapidityAbs("FourMu_RapidityAbs","FourMu_RapidityAbs",0.,1.8);
  RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",0.0,3.6);

  RooArgSet dataVars(Psi1_Mass, Psi2_Mass,Psi1To2_dY, FourMu_Mass, FourMu_pT, FourMu_RapidityAbs);
  //RooDataSet* readdata = RooDataSet::read("nlofullset_fit_aug13.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("dpsfullset_fit_aug13.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("nlofullset_genfit_aug13.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("dpsfullset_genfit_aug13.txt",dataVars);
  //RooDataSet* data ;
  //data = new RooDataSet("data","data",readdata ,dataVars);
 float ptbins[]={0,7,12,16,20,25,50,80};
 int nptbins = 7;

 TH1F* pthist_dps = new TH1F("pthist_dps","pthist_dps",nptbins,ptbins);
  pthist_dps->SetBinContent(1,1.95068664169787742e-01);
  pthist_dps->SetBinContent(2,2.91822721598002488e-01);
  pthist_dps->SetBinContent(3,3.48002496878901335e-01);
  pthist_dps->SetBinContent(4,1.37328339575530589e-01);
  pthist_dps->SetBinContent(5,2.65293383270911350e-02);
  pthist_dps->SetBinContent(6,1.24843945068664171e-03);
  pthist_dps->SetBinContent(7,0.0);

 TH1F* pthist_nlo = new TH1F("pthist_nlo","pthist_nlo",nptbins,ptbins);
  pthist_nlo->SetBinContent(1,1.01210557650327437e-01);
  pthist_nlo->SetBinContent(2,1.44870013891645166e-01);
  pthist_nlo->SetBinContent(3,2.89740027783290333e-01);
  pthist_nlo->SetBinContent(4,2.93709069259773803e-01);
  pthist_nlo->SetBinContent(5,1.50823576106370316e-01);
  pthist_nlo->SetBinContent(6,1.92498511609446310e-02);
  pthist_nlo->SetBinContent(7,3.96904147648342940e-04);

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

  hist_y = new RooDataHist("hist","hist",RooArgList(FourMu_RapidityAbs),yhist);
  hist_pt = new RooDataHist("hist_pt","hist_pt",RooArgList(FourMu_pT),pthist);
  hist_pt_nlo = new RooDataHist("hist_pt_nlo","hist_pt_nlo",RooArgList(FourMu_pT),pthist_nlo);
  hist_pt_dps = new RooDataHist("hist_pt_dps","hist_pt_dps",RooArgList(FourMu_pT),pthist_dps);
  pdf_y = new RooHistPdf("pdf_y","pdf_y",RooArgList(FourMu_RapidityAbs),*hist_y);
  pdf_pt_nlo = new RooHistPdf("pdf_pt_nlo","pdf_pt_nlo",RooArgList(FourMu_pT),*hist_pt_nlo);
  pdf_pt_dps = new RooHistPdf("pdf_pt_dps","pdf_pt_dps",RooArgList(FourMu_pT),*hist_pt_dps);
//  data_model = new RooProdPdf("data_model","data_model",RooArgList(*pdf_pt,*pdf_y));

  RooProdPdf dps_model("dps_model","dps_model",RooArgList(*pdf_pt_dps));
  RooProdPdf nlo_model("nlo_model","nlo_model",RooArgList(*pdf_pt_nlo));
  ndps = new RooRealVar("ndps","",1,0,2000); 
  nnlo = new RooRealVar("nnlo","",5,0,2000); 
  fdps = new RooRealVar("fdps","",0.5,0,2); 
  fnlo = new RooRealVar("fnlo","",0.5,0,2); 
  RooAddPdf model("model","model",RooArgList(dps_model,nlo_model),RooArgList(*ndps,*nnlo));
//  RooChi2Var chi2("chi2","chi2",model,*hist_pt,DataError(RooAbsData::SumW2)) ;
//  RooMinuit m(chi2) ;
//  m.migrad() ;
//  m.hesse() ;
//    RooFitResult* r_chi2_wgt = m.save() ;


  model.fitTo(*hist_pt,Extended(kTRUE),Hesse(kTRUE),Minos(kFALSE));
//  dps_y.fitTo(*data,Hesse(kTRUE),Minos(kFALSE));
  TCanvas* c1 = new TCanvas("c1","c1",800,800);
//    c1->Divide(2,1);
//    c1->cd(1);
    RooPlot* frame1 = FourMu_pT.frame(Title("pT (GeV)"));
    frame1 = FourMu_pT.frame(40);
    hist_pt->plotOn(frame1);
    model.plotOn(frame1,LineColor(kBlack));
    model.plotOn(frame1,Components("DPS,*dps*"),LineColor(kRed),LineStyle(kDashed));
    model.plotOn(frame1,Components("NLO,*nlo*"),LineColor(kBlue),LineStyle(kDotted));
    frame1->Draw();
//    c1->cd(2);
//    c1->Divide(1,2);
//    RooPlot* frame2 = Psi1To2_dY.frame(Title("#Delta y"));
//    frame2 = Psi1To2_dY.frame(25);
//    data->plotOn(frame2);
//    model.plotOn(frame2,LineColor(kBlack));
//    float chi = frame2->chiSquare();
////    RooHist* pull_dy= frame2->pullHist();
//    model.plotOn(frame2,Components("DPS,dps_dy"),LineColor(kRed),LineStyle(kDashed));
//    model.plotOn(frame2,Components("NLO,nlo_dy"),LineColor(kBlue),LineStyle(kDotted));
////    pull_dy->SetMarkerSize(.7);
////    RooPlot* frame_dy= Psi1To2_dY.frame(Bins(20));
////    frame_dy->addPlotable(pull_dy,"P");
//    frame2->SetXTitle("|#Delta Y| Between J/#psi");
////    frame_dy->SetXTitle("|#Delta Y| Between J/#psi");
////    c1->cd(1);
//    frame2->Draw();
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

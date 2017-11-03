#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooBifurGauss.h"
#include "RooChebychev.h"
#include "RooVoigtian.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "Riostream.h"
void fitValidation_2var() {
using namespace RooFit ;

  //RooRealVar Psi1_CTxy("Psi1_CTxy","Psi1_CTxy",-0.02,0.05);
  //RooRealVar Psi2_CTxy("Psi2_CTxy","Psi2_CTxy",-0.03,0.5);
  //RooRealVar Psi1To2Significance("Psi1To2Significance","Psi1To2Significance",0.,8.);
  //RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.9892,3.2028);
  //RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.9892,3.2028);
  RooRealVar Psi1_CTxy("Psi1_CTxy","Psi1_CTxy",-0.02,0.025);
  RooRealVar Psi2_CTxy("Psi2_CTxy","Psi2_CTxy",-0.02,0.025);
  RooRealVar Psi1To2Significance("Psi1To2Significance","Psi1To2Significance",0.,5.);
  RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.85,3.35);
  RooRealVar FourMu_Rapidity("FourMu_Rapidity","FourMu_Rapidity",-6,6.);
  RooRealVar FourMu_RapidityAbs("FourMu_RapidityAbs","FourMu_RapidityAbs",0,1.8);
  RooRealVar FourMu_Mass("FourMu_Mass","FourMu_Mass",0.,60.);
  RooRealVar FourMu_pT("FourMu_pT","FourMu_pT",0.,80.);
  RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",0.,4.5);

//--yo, these are SigMC Fit parameters in ctxy
  RooRealVar sigmcR_mean_coreCT1("sigmcR_mean_coreCT1","",0);
  RooRealVar sigmcR_mean_tailCT1("sigmcR_mean_tailCT1","",0);
  RooRealVar sigmcR_sigma_coreCT1("sigmcR_sigma_coreCT1","",-3.61754e-03);
  RooRealVar sigmcR_sigma_tailCT1("sigmcR_sigma_tailCT1","",1.87819e-03);
  RooFormulaVar R_sigma_totCT1("sigmcR_sigma_totCT1","","",RooArgList(sigmcR_sigma_coreCT1,sigmcR_sigma_tailCT1));
  RooRealVar sigmcR_fracCT1("sigmcR_fracCT1","",2.91514e-01);
  //RooRealVar sigmcR_fracCT1("sigmcR_fracCT1","",3.14045e-01,0.0,0.9);
  RooGaussian sigmcct_1a("sigmcct_1a","ct distributionsigmc",Psi1_CTxy,sigmcR_mean_coreCT1,sigmcR_sigma_coreCT1);
  RooGaussian sigmcct_1b("sigmcct_1b","ct distributionsigmc",Psi1_CTxy,sigmcR_mean_tailCT1,sigmcR_sigma_tailCT1);
 
  RooAddPdf sigmcct_1("sigmcct_1","ct distributionsigmc",RooArgList(sigmcct_1a,sigmcct_1b),RooArgList(sigmcR_fracCT1));

//-- ctxy bkg
  RooRealVar sigmcR_mean_coreCT2("sigmcR_mean_coreCT2","",0);
  RooRealVar sigmcR_mean_tailCT2("sigmcR_mean_tailCT2","",0);
  RooRealVar sigmcR_sigma_coreCT2("sigmcR_sigma_coreCT2","",4.50487e-03);
  RooRealVar sigmcR_sigma_tailCT2("sigmcR_sigma_tailCT2","",2.37444e-03);
  RooFormulaVar R_sigma_totCT2("sigmcR_sigma_totCT2","","",RooArgList(sigmcR_sigma_coreCT2,sigmcR_sigma_tailCT2));

  RooRealVar sigmcR_fracCT2("sigmcR_fracCT2","",2.91514e-01);
  //RooRealVar sigmcR_fracCT1("sigmcR_fracCT1","",3.14045e-01,0.0,0.9);
  RooGaussian sigmcct_2a("sigmcct_2a","ct distributionsigmc",Psi2_CTxy,sigmcR_mean_coreCT2,sigmcR_sigma_coreCT2);
  RooGaussian sigmcct_2b("sigmcct_2b","ct distributionsigmc",Psi2_CTxy,sigmcR_mean_tailCT2,sigmcR_sigma_tailCT2);
 
  RooAddPdf sigmcct_2("sigmcct_2","ct distributionsigmc",RooArgList(sigmcct_2a,sigmcct_2b),RooArgList(sigmcR_fracCT2));
    RooRealVar ct_mean_core2("ctmeancore2","",0,-1,1);
    RooRealVar ct_sigma_core2("ctsigmacore2","",0,0,1);
    RooRealVar ct_lambda2("ctlambda2","",4.50851e-03);
    RooGaussModel resolute_cour2("resolute_cour2","",Psi2_CTxy,sigmcR_mean_tailCT2,sigmcR_sigma_tailCT2);
    //RooGaussModel resolute_cour("resolute_cour","",Psi1_CTxy,ct_mean_core,ct_sigma_core);
    RooDecay bkg_CT2_SB1("ct2sb1","",Psi2_CTxy,ct_lambda2,resolute_cour2,RooDecay::SingleSided);
//  bkg1_R_mean_core = new RooRealVar("bkg1_R_mean_core","",3.81478e-03);
//  bkg1_R_mean_tail = new RooRealVar("bkg1_R_mean_tail","",1.64523e-03);
//  bkg1_R_sigma_core = new RooRealVar("bkg1_R_sigma_core","",9.65292e-03,0,1);
//  bkg1_R_sigma_tail = new RooRealVar("bkg1_R_sigma_tail","",3.74515e-01,0,1);
//  bkg_frac_1 = new RooRealVar("bkg_frac_1","",2.63568e-01,0,1);
//  bkg1_R_sigma_tot = new RooFormulaVar("bkg1_R_sigma_tot","","@0*@1",RooArgList(*bkg1_R_sigma_tail,*bkg1_R_sigma_core));
//
//  RooGaussian bkg_ctSB1_1a("bkg_ctSB1_1a","ct distribution",Psi1_CTxy,*bkg1_R_mean_core,*bkg1_R_sigma_core);
//  RooGaussian bkg_ctSB1_1b("bkg_ctSB1_1b","ct distribution",Psi1_CTxy,*bkg1_R_mean_tail,*bkg1_R_sigma_tot);
//  RooAddPdf bkg_CT1_SB1("bkg_CT1_SB1","ct distribution",RooArgList(bkg_ctSB1_1a,bkg_ctSB1_1b),RooArgList(*bkg_frac_1));
////////////////////////////////////////////////////////////////
//roodecay ctxy bkg paramaterization
    RooRealVar ct_mean_core("ctmeancore","",0,-1,1);
    RooRealVar ct_sigma_core("ctsigmacore","",0,0,1);
    RooRealVar ct_lambda("ctlambda","",4.50851e-03);
    RooGaussModel resolute_cour("resolute_cour","",Psi1_CTxy,sigmcR_mean_tailCT1,sigmcR_sigma_tailCT1);
    //RooGaussModel resolute_cour("resolute_cour","",Psi1_CTxy,ct_mean_core,ct_sigma_core);
    RooDecay bkg_CT1_SB1("ct1sb1","",Psi1_CTxy,ct_lambda,resolute_cour,RooDecay::SingleSided);
    

    //RooRealVar R_mean_core("R_mean_core","",5.20481e-01,0,2);
    //RooRealVar R_sigma_core("R_sigma_core","",3.45099e-01);
    //RooRealVar etab_lambda("etab_lambda","",4.77901e-01);
//-- These are signal mc fit parameters for dsig
    //RooRealVar R_mean_core("R_mean_core","",4.88713e-01);
    //RooRealVar R_sigma_core("R_sigma_core","",3.40958e-01);
    //RooRealVar etab_lambda("etab_lambda","",5.51736e-01);
    RooRealVar R_mean_core("R_mean_core","",4.38195e-01);
    RooRealVar R_sigma_core("R_sigma_core","",2.98492e-01);
    RooRealVar etab_lambda("etab_lambda","",6.33575e-01);
    RooGaussModel resolution_core("resolution_core","",Psi1To2Significance,R_mean_core,R_sigma_core);
    RooDecay sig_distT("sig_distT","",Psi1To2Significance,etab_lambda,resolution_core,RooDecay::SingleSided);
    
    //--These are bkg parameters for dsig
    RooRealVar bkg_co02("bkg_co02","",9.99454e-01,0,1);
    RooRealVar bkg_co12("bkg_co12","",8.23944e-01,0,1);
    RooRealVar bkg_flau2("bkg_flau2","",1,0,1);
    RooRealVar bkg_meanlandau2("bkg_meanlandau2","",1.99530);
    RooRealVar bkg_sigmalandau2("bkg_sigmalandau2","",5.85777e-01);
    //RooRealVar bkg_meanlandau2("bkg_meanlandau2","",6.21076e-01);
    //RooRealVar bkg_sigmalandau2("bkg_sigmalandau2","",2.40785e-01);
    RooChebychev bkg_polyshape2("bkg_polyshape2","",Psi1To2Significance,RooArgList(bkg_co02,bkg_co12));
    RooLandau bkg_landau2("bkg_landau2", "bkg_landau2", Psi1To2Significance, bkg_meanlandau2, bkg_sigmalandau2);
    RooAddPdf bkg_distT2("bkg_distT2","", RooArgList(bkg_landau2,bkg_polyshape2),RooArgList(bkg_flau2));


  //  RooDataSet* data = RooDataSet::read("TMTight_mlfReduced.txt",RooArgList(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy,Psi1To2Significance)); 
  RooArgSet dataVars(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy, Psi1To2Significance); 
  dataVars.add(RooArgSet(Psi1To2_dY, FourMu_Mass, FourMu_pT, FourMu_Rapidity, FourMu_RapidityAbs));
  RooDataSet* readdata = RooDataSet::read("Selected_noVtxCut.txt",dataVars);
  RooDataSet* data ;
  data = new RooDataSet("data","data",readdata ,dataVars);
    
    RooProdPdf sig_model("sig_model","sig_model",RooArgList(sigmcct_1,sig_distT));
    RooProdPdf bkg_model("bkg_model","bkg_model",RooArgList(bkg_CT1_SB1,bkg_landau2));

  RooRealVar nsig("nsig","number of Signal events",564,1,5000);
  RooRealVar nbkg("nbkg","number of background events",200,1,5000);

  RooAddPdf model("model","model",RooArgList(sig_model,bkg_model),RooArgList(nsig,nbkg));
  model.fitTo(*data,Extended(kTRUE),Hesse(kTRUE),Minos(kFALSE));

  RooMCStudy *mgr = new RooMCStudy(model,RooArgSet(Psi1_CTxy,Psi1To2Significance),Silence(),Extended(),FitOptions(Save(kTRUE),PrintEvalErrors(0)));

  mgr->generateAndFit(10000);
  RooPlot* frame0 = mgr->plotNLL(-6800.0,-4800.0,80);
  RooPlot* frame1a = mgr->plotParam(nsig,Bins(40));                                                                                   
  RooPlot* frame1b = mgr->plotError(nsig,FrameRange(20,30),FrameBins(40));                                                                                       
  RooPlot* frame1c = mgr->plotPull(nsig,FrameRange(-5,5),FrameBins(20),FitGauss(kTRUE));


  RooPlot* frame3a = mgr->plotParam(nbkg,Bins(40));                              
  RooPlot* frame3b = mgr->plotError(nbkg,Bins(40));
  RooPlot* frame3c = mgr->plotPull(nbkg,FrameRange(-3,3),FrameBins(20),FitGauss(kTRUE));


  TCanvas* c1 = new TCanvas("c1","",0,0,700,500);
  c1->cd(); c1->SetFillColor(kWhite);
  frame0->SetTitle("");
  frame0->SetStats(0);
  frame0->Draw();                                                                
  TCanvas* c1a = new TCanvas("c1a","",10,10,700,500);
  c1a->cd(); c1a->SetFillColor(kWhite);
  frame1a->SetTitle("");
  frame1a->SetStats(0);
  frame1a->Draw();                                                               

  TCanvas* c1b = new TCanvas("c1b","",20,20,700,500);
  c1b->cd(); c1b->SetFillColor(kWhite);
  frame1b->SetTitle("");
  frame1b->SetStats(0);
  frame1b->Draw();    


  TCanvas* c1c = new TCanvas("c1c","",30,30,700,500);
  c1c->cd(); c1c->SetFillColor(kWhite);
  frame1c->SetTitle("");
  frame1c->GetXaxis()->SetTitle("Signal Pull");
  frame1c->SetStats(0);
  frame1c->Draw();

  TFile *f = new TFile("FitResult4Par_mcstudy.root","RECREATE");
  TTree * tree = mgr->fitParDataSet().tree();  
  tree->SetBranchStatus("*",1);
  tree->Write();
  f->Write();


//  RooPlot* frame1 = Psi1_Mass.frame(Title("#mu^{+}#mu^{-}"));
//  frame1 = Psi1_Mass.frame(20);
//  data->plotOn(frame1);
//  model.plotOn(frame1);
//  model.plotOn(frame1,RooFit::Components("sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
//  model.plotOn(frame1,RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
//  TCanvas* c1 = new TCanvas("c1","",10,10,700,500);
//  c1->cd();
//  c1->SetFillColor(kWhite);
//  frame1->SetTitle("");
//  frame1->SetXTitle("#mu^{+}#mu^{-} 1 Invariant Mass [GeV/c^{2}]");
//  frame1->Draw();
//	frame1->SetStats(1);
//  //c1->SaveAs("pic/Psi1_mass.pdf");
//  //c1->Close();
//
//  RooPlot* frame2 = Psi2_Mass.frame(Title("#mu^{+}#mu^{-}"));
//  frame2 = Psi2_Mass.frame(20);
//  data->plotOn(frame2);
//  model.plotOn(frame2);
//  model.plotOn(frame2,RooFit::Components("Sig,sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
//    model.plotOn(frame2,RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
//    TCanvas* c2 = new TCanvas("c2","",10,10,700,500);
//    c2->cd();
//    c2->SetFillColor(kWhite);
//    frame2->SetTitle("");
//    frame2->SetXTitle("#mu^{+}#mu^{-} 2 Invariant Mass [GeV/c^{2}]");
//    frame2->Draw();
//    //c2->SaveAs("pic/Psi2_mass.pdf");
//    //c2->Close();
//
//    RooPlot* frame5 = Psi1_CTxy.frame(Title("#mu^{+}#mu^{-}#mu^{+}#mu^{-} ct"));
//    frame5 = Psi1_CTxy.frame(30);
//    data->plotOn(frame5,DrawOption("p"));
//  model.plotOn(frame5);
//  model.plotOn(frame5,RooFit::Components("sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
//  model.plotOn(frame5,RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
//  TCanvas* c5 = new TCanvas("c5","",10,10,700,500);
//  c5->cd();
//  c5->SetFillColor(kWhite);
//  frame5->SetTitle("");
//  frame5->SetMaximum(1000);
//  frame5->SetMinimum(1.5);
//  frame5->SetXTitle("J/#psi^{1} ct_{xy} [cm]");
//  frame5->Draw();
//  c5->SetLogy();
//  //c5->SaveAs("pic/Psi1_CTxy.pdf");
//  //c5->Close();
//
//  RooPlot* frame3 = Psi1To2Significance.frame(Title("#mu^{+}#mu^{-}#mu^{+}#mu^{-} ct"));
//  frame3 = Psi1To2Significance.frame(20);
//  data->plotOn(frame3);
//  model.plotOn(frame3);
//  model.plotOn(frame3,RooFit::Components("sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
//  model.plotOn(frame3,RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
//  TCanvas* c3 = new TCanvas("c3","",10,10,700,500);
//  c3->cd();
//  c3->SetFillColor(kWhite);
//  frame3->SetTitle("");
//  frame3->SetXTitle("J/#psi Distance Significance");
//  frame3->Draw();
//  //c3->SaveAs("pic/Psi1To2Significance.pdf");
//
//  RooAbsReal* nll = model.createNLL(*data);
//  before = nll->getVal();
//  nres = 1;
//  after = nll->getVal();
//  std::cout<<" " <<sqrt(2*fabs(before - after))<<std::endl;


}

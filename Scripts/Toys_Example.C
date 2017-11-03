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
void genMLFToysRedFeb9() {
using namespace RooFit ;

  //RooRealVar Psi1_CTxy("Psi1_CTxy","Psi1_CTxy",-0.02,0.05);
  //RooRealVar Psi2_CTxy("Psi2_CTxy","Psi2_CTxy",-0.03,0.5);
  //RooRealVar Psi1To2Significance("Psi1To2Significance","Psi1To2Significance",0.,8.);
  //RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.9892,3.2028);
  //RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.9892,3.2028);
  RooRealVar Psi1_CTxy("Psi1_CTxy","Psi1_CTxy",-0.02,0.025);
  RooRealVar Psi2_CTxy("Psi2_CTxy","Psi2_CTxy",-0.05,0.1);
  RooRealVar Psi1To2Significance("Psi1To2Significance","Psi1To2Significance",0.,5.);
  RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.85,3.35);
  RooRealVar run("run","run number",0.,1e10);
  RooRealVar event("event","event number",0.,1e10);
  RooRealVar FourMu_Mass("FourMu_Mass","FourMu_Mass",0.,60.);
  RooRealVar FourMu_pT("FourMu_pT","FourMu_pT",0.,999.);
  RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",-100.,100);

//--mass 1 signal fixed to resonance MC

  jpsi1_mass_1 = new RooRealVar("jpsi1_mass_1","",3.090);
  jpsi1_width_1 = new RooRealVar("jpsi1_width_1","",1.14270e-01);
  jpsi1_width_2 = new RooRealVar("jpsi1_width_2","",2.89063e-01);
  frac_1 = new RooRealVar("frac_1","",7.96073e-02);
  jpsi1_width_a = new RooFormulaVar("jpsi1_width_a","","@0*@1",RooArgList(*jpsi1_width_1,*jpsi1_width_2));

  RooGaussian jpsi1mass_1("jpsi1mass_1","jpsi mass distribution",Psi1_Mass,*jpsi1_mass_1,*jpsi1_width_1);
  RooGaussian jpsi1mass_2("jpsi1mass_2","jpsi mass distribution",Psi1_Mass,*jpsi1_mass_1,*jpsi1_width_a);
  RooAddPdf jpsi1mass("jpsi1mass","jpsi1 mass distribution",RooArgList(jpsi1mass_1,jpsi1mass_2),RooArgList(*frac_1));
//-- bkg params for mass 1

  bkg_jpsi1_mass_1 = new RooRealVar("bkg_jpsi1_mass_1","",3.09313e+00);
  bkg_jpsi1_width_1 = new RooRealVar("bkg_jpsi1_width_1","",5.53070e-02);
  bkg_jpsi1_width_2 = new RooRealVar("bkg_jpsi1_width_2","",3.12231e-01);
  bkg_jpsi1_width_a = new RooFormulaVar("bkg_jpsi1_width_a","","@0*@1",RooArgList(*bkg_jpsi1_width_1,*bkg_jpsi1_width_2));
  RooRealVar*    bkg_frac_6 = new RooRealVar("bkg_frac_6","",7.46426e-01);
  bkg_p3 = new RooRealVar("bkg_p3","",-3.27375e-01);
  bkg_p4 = new RooRealVar("bkg_p4","",3.25982e-01);
  bkg_p5 = new RooRealVar("bkg_p5","",7.81093e-02);

  //RooGaussian bkg_jpsi1mass_1("bkg_jpsi1mass_1","jpsi mass distribution",Psi1_Mass,*bkg_jpsi1_mass_1,*bkg_jpsi1_width_1);
  RooGaussian bkg_jpsi1mass_1("bkg_jpsi1mass_1","jpsi mass distribution",Psi1_Mass,*jpsi1_mass_1,*bkg_jpsi1_width_1);
  RooGaussian bkg_jpsi1mass_2("bkg_jpsi1mass_2","jpsi mass distribution",Psi1_Mass,*jpsi1_mass_1,*bkg_jpsi1_width_a);
  //RooGaussian bkg_jpsi1mass_2("bkg_jpsi1mass_2","jpsi mass distribution",Psi1_Mass,*bkg_jpsi1_mass_1,*bkg_jpsi1_width_a);
  RooAddPdf bkg_jpsi1mass("bkg_jpsi1mass","jpsi1 mass distribution",RooArgList(bkg_jpsi1mass_1,bkg_jpsi1mass_2),RooArgList(*bkg_frac_6));
  RooChebychev bkg_jpsi1mass_Pol("bkg_jpsi1mass_Pol","",Psi1_Mass,RooArgList(*bkg_p3,*bkg_p4,*bkg_p5));
  frac_bkg = new RooRealVar("frac_bkg","",8.56329e-01);
  RooAddPdf bkg_mass1model("bkg_mass1model","jpsi 1 bkg model",RooArgList(bkg_jpsi1mass,bkg_jpsi1mass_Pol),RooArgList(*frac_bkg));


//mass 2 signal fixed to resonaance mc

  jpsi2_mass_1 = new RooRealVar("jpsi2_mass_2","",3.09352e+00);
  jpsi2_width_1 = new RooRealVar("jpsi2_width_1","",1.20268e-01);
  jpsi2_width_2 = new RooRealVar("jpsi2_width_2","",2.83741e-01);
  frac_2 = new RooRealVar("frac_2","",8.99141e-02);
  jpsi2_width_a = new RooFormulaVar("jpsi2_width_a","","@0*@1",RooArgList(*jpsi2_width_1,*jpsi2_width_2));

  //RooGaussian jpsi2mass_1("jpsi2mass_1","jpsi mass distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_1);
  RooGaussian jpsi2mass_1("jpsi2mass_1","jpsi mass distribution",Psi2_Mass,*jpsi1_mass_1,*jpsi2_width_1);
  RooGaussian jpsi2mass_2("jpsi2mass_2","jpsi mass distribution",Psi2_Mass,*jpsi1_mass_1,*jpsi2_width_a);
  //RooGaussian jpsi2mass_2("jpsi2mass_2","jpsi mass distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_a);
  RooAddPdf jpsi2mass("jpsi2mass","jpsi2 mass distribution",RooArgList(jpsi2mass_1,jpsi2mass_2),RooArgList(*frac_2));


//mass 2 bkg shape
  bkg_jpsi2_mass_1 = new RooRealVar("bkg_jpsi2_mass_1","",3.08933e+00);
  bkg_jpsi2_width_1 = new RooRealVar("bkg_jpsi2_width_1","",4.60421e-02);
  bkg_jpsi2_width_2 = new RooRealVar("bkg_jpsi2_width_2","",8.67431e-01);
  bkg_jpsi2_width_a = new RooFormulaVar("bkg_jpsi2_width_a","","@0*@1",RooArgList(*bkg_jpsi2_width_1,*bkg_jpsi2_width_2));
  RooRealVar*    bkg_frac_7 = new RooRealVar("bkg_frac_7","",8.55387e-01);
  bkg_p3mass2 = new RooRealVar("bkg_p3mass2","",-2.40973e-01);
  bkg_p4mass2 = new RooRealVar("bkg_p4mass2","",-5.11436e-01);
  bkg_p5mass2 = new RooRealVar("bkg_p5mass2","",2.98477e-01);
  //RooGaussian bkg_jpsi2mass_1("bkg_jpsi2mass_1","jpsi mass distribution",Psi2_Mass,*bkg_jpsi2_mass_1,*bkg_jpsi2_width_1);
  RooGaussian bkg_jpsi2mass_1("bkg_jpsi2mass_1","jpsi mass distribution",Psi2_Mass,*jpsi1_mass_1,*bkg_jpsi2_width_1);
  //RooGaussian bkg_jpsi2mass_2("bkg_jpsi2mass_2","jpsi mass distribution",Psi2_Mass,*bkg_jpsi2_mass_1,*bkg_jpsi2_width_a);
  RooGaussian bkg_jpsi2mass_2("bkg_jpsi2mass_2","jpsi mass distribution",Psi2_Mass,*jpsi1_mass_1,*bkg_jpsi2_width_a);
  RooAddPdf bkg_jpsi2mass("bkg_jpsi2mass","jpsi1 mass distribution",RooArgList(bkg_jpsi2mass_1,bkg_jpsi2mass_2),RooArgList(*bkg_frac_7));
  RooChebychev bkg_jpsi2mass_Pol("bkg_jpsi2mass_Pol","",Psi2_Mass,RooArgList(*bkg_p3mass2,*bkg_p4mass2,*bkg_p5mass2));
  frac_bkg_mass2 = new RooRealVar("frac_bkg_mass2","",6.62096e-06);
  RooAddPdf bkg_mass2model("bkg_mass2model","jpsi 2 bkg model",RooArgList(bkg_jpsi2mass,bkg_jpsi2mass_Pol),RooArgList(*frac_bkg_mass2));

//--yo, these are SigMC Fit parameters in ctxy
  RooRealVar sigmcR_mean_coreCT1("sigmcR_mean_coreCT1","",5.38046e-04,-1,1);
  RooRealVar sigmcR_mean_tailCT1("sigmcR_mean_tailCT1","",-1.83163e-04,-1,1);
  RooRealVar sigmcR_sigma_coreCT1("sigmcR_sigma_coreCT1","",4.58764e-03,0,1);
  RooRealVar sigmcR_sigma_tailCT1("sigmcR_sigma_tailCT1","",2.55377e-03,0,1);
  RooFormulaVar R_sigma_totCT1("sigmcR_sigma_totCT1","","",RooArgList(sigmcR_sigma_coreCT1,sigmcR_sigma_tailCT1));
  RooRealVar sigmcR_fracCT1("sigmcR_fracCT1","",0.5,0,1);
  //RooRealVar sigmcR_fracCT1("sigmcR_fracCT1","",3.14045e-01,0.0,0.9);
  RooGaussian sigmcct_1a("sigmcct_1a","ct distributionsigmc",Psi1_CTxy,sigmcR_mean_coreCT1,sigmcR_sigma_coreCT1);
  RooGaussian sigmcct_1b("sigmcct_1b","ct distributionsigmc",Psi1_CTxy,sigmcR_mean_tailCT1,sigmcR_sigma_tailCT1);
 
  RooAddPdf sigmcct_1("sigmcct_1","ct distributionsigmc",RooArgList(sigmcct_1a,sigmcct_1b),RooArgList(sigmcR_fracCT1));

//-- ctxy bkg
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
    RooRealVar ct_lambda("ctlambda","",0.5,1e-4,1);
    RooGaussModel resolute_cour("resolute_cour","",Psi1_CTxy,sigmcR_mean_tailCT1,sigmcR_sigma_tailCT1);
    //RooGaussModel resolute_cour("resolute_cour","",Psi1_CTxy,ct_mean_core,ct_sigma_core);
    RooDecay bkg_CT1_SB1("ct1sb1","",Psi1_CTxy,ct_lambda,resolute_cour,RooDecay::SingleSided);
    

    //RooRealVar R_mean_core("R_mean_core","",5.20481e-01,0,2);
    //RooRealVar R_sigma_core("R_sigma_core","",3.45099e-01);
    //RooRealVar etab_lambda("etab_lambda","",4.77901e-01);
//-- These are signal mc fit parameters for dsig
    RooRealVar R_mean_core("R_mean_core","",4.88713e-01);
    RooRealVar R_sigma_core("R_sigma_core","",3.40958e-01);
    RooRealVar etab_lambda("etab_lambda","",5.51736e-01);
    RooGaussModel resolution_core("resolution_core","",Psi1To2Significance,R_mean_core,R_sigma_core);
    RooDecay sig_distT("sig_distT","",Psi1To2Significance,etab_lambda,resolution_core,RooDecay::SingleSided);
//--These are bkg parameters for dsig
    RooRealVar bkg_co02("bkg_co02","",9.99454e-01,-2,2);
    RooRealVar bkg_co12("bkg_co12","",0);
    RooRealVar bkg_flau2("bkg_flau2","",1);
    RooRealVar bkg_meanlandau2("bkg_meanlandau2","",9.76918e-01,0,3);
    RooRealVar bkg_sigmalandau2("bkg_sigmalandau2","",4.58691e-01,0,1);
    RooChebychev bkg_polyshape2("bkg_polyshape2","",Psi1To2Significance,RooArgList(bkg_co02,bkg_co12));
    RooLandau bkg_landau2("bkg_landau2", "bkg_landau2", Psi1To2Significance, bkg_meanlandau2, bkg_sigmalandau2);
    RooAddPdf bkg_distT2("bkg_distT2","", RooArgList(bkg_landau2,bkg_polyshape2),RooArgList(bkg_flau2));


  //  RooDataSet* data = RooDataSet::read("TMTight_mlfReduced.txt",RooArgList(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy,Psi1To2Significance)); 
  RooArgSet dataVars(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy, Psi1To2Significance); 
  dataVars.add(RooArgSet(Psi1To2_dY, FourMu_Mass, FourMu_pT, run, event));
  RooDataSet* readdata = RooDataSet::read("TMTight_5varMLFreduced.txt",dataVars);
  RooDataSet* data ;
  data = new RooDataSet("data","data",readdata ,dataVars);
    

    RooProdPdf sig_model("sig_model","sig_model",RooArgList(jpsi1mass,jpsi2mass,sigmcct_1,sig_distT));
    RooProdPdf bkg_model("bkg_model","bkg_model",RooArgList(bkg_mass1model,bkg_mass2model,bkg_CT1_SB1,bkg_landau2));
    //RooProdPdf bkg_model("bkg_model","bkg_model",RooArgList(bkg_mass1model,bkg_mass2model,bkg_CT1_SB1,bkg_landau2,nlh));

  RooRealVar nsig("nsig","number of Signal events",200,1,5000);
  RooRealVar nbkg("nbkg","number of background events",200,1,5000);

  RooAddPdf model("model","model",RooArgList(sig_model,bkg_model),RooArgList(nsig,nbkg));
  model.fitTo(*data,Extended(kTRUE),Hesse(kTRUE),Minos(kFALSE));

  RooMCStudy *mgr = new RooMCStudy(model,RooArgSet(Psi1_Mass,Psi2_Mass,Psi1_CTxy,Psi1To2Significance,FourMu_Mass),Silence(),Extended(),FitOptions(Save(kTRUE),PrintEvalErrors(0)));

  mgr->generateAndFit(10000);
  RooPlot* frame0 = mgr->plotNLL(-20500,-15500,80);
  RooPlot* frame1a = mgr->plotParam(nsig,Bins(40));                                                                                   
  RooPlot* frame1b = mgr->plotError(nsig,FrameRange(30,50),FrameBins(40));                                                                                       
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

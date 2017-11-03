#include "RooRealVar.h"
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

void fitJ2_Only_newvars(){
  using namespace RooFit;


  RooRealVar Psi1_CTxy("Psi1_CTxy","Psi1_CTxy",-0.02,0.025);
  RooRealVar Psi2_CTxy("Psi2_CTxy","Psi2_CTxy",-0.05,0.1);
  RooRealVar Psi1To2Significance("Psi1To2Significance","Psi1To2Significance",0.,5.);
  RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.85,3.35);
  //RooRealVar run("run","run number",0.,1e13);
  //RooRealVar event("event","event number",0.,1e13);
  RooRealVar FourMu_Mass("FourMu_Mass","FourMu_Mass",6.,100.);
  //RooRealVar FourMu_Mass("FourMu_Mass","FourMu_Mass",0.,80.);
  RooRealVar FourMu_pT("FourMu_pT","FourMu_pT",0.,80.);
  RooRealVar FourMu_Rapidity("FourMu_Rapidity","FourMu_Rapidity",-6,6.);
  RooRealVar FourMu_RapidityAbs("FourMu_RapidityAbs","FourMu_RapidityAbs",0.,1.8);
  RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",0,4.5);
  RooRealVar Delta_Phi("Delta_Phi","Delta_Phi",2.5,3.142);
  RooRealVar pT_Asymmetery("pT_Asymmetery","pT_Asymmetery",0.,1.);
  RooRealVar Psi1_pT("Psi1_pT","Psi1_pT",0,60);
  RooRealVar Psi2_pT("Psi2_pT","Psi2_pT",0,40);
  //RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",-100.,100);

  jpsi2_mass_1 = new RooRealVar("jpsi2_mass_2","",3.09616e+00,2.9,4);
  jpsi2_width_1 = new RooRealVar("jpsi2_width_1","",2.76248e-02,9e-3,1);
  jpsi2_width_2 = new RooRealVar("jpsi2_width_2","",8.40910e-02);
  frac_2 = new RooRealVar("frac_2","",9.54822e-01);
  jpsi2_width_a = new RooFormulaVar("jpsi2_width_a","","@0*@1",RooArgList(*jpsi2_width_1,*jpsi2_width_2));

 //RooGaussian jpsi2mass("jpsi2mass_1","jpsi mass distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_1);
 RooGaussian jpsi2mass_1("jpsi2mass_1","jpsi mass distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_1);
 RooGaussian jpsi2mass_2("jpsi2mass_2","jpsi mass distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_2);
 //RooGaussian jpsi2mass_2("jpsi2mass_2","jpsi mass distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_a);
 RooAddPdf jpsi2mass("jpsi2mass","jpsi2 mass distribution",RooArgList(jpsi2mass_1,jpsi2mass_2),RooArgList(*frac_2));
  
  //cb shape trials
  //jpsi2_width_1 = new RooRealVar("jpsi2_width_1","",2.86972e-02,0,1);
  //jpsi1_alpha= new RooRealVar("jpsi1_alpha","",3.96952e+00,0,5);
  //jpsi1_n = new RooRealVar("jpsi1_n","",2.53643e+00,0,5);
  //RooCBShape jpsi2mass("jpsi2mass","jpsi2 mass cb distribution",Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_1,*jpsi1_alpha, *jpsi1_n);

//mass 2 bkg shape
 // bkg_p3mass2 = new RooRealVar("bkg_p3mass2","",0,-1,1);
  bkg_p3mass2 = new RooRealVar("bkg_p3mass2","",-3.07917e-01,-1,1);
  //bkg_p3mass2 = new RooRealVar("bkg_p3mass2","",1.23930e-02);
  bkg_p4mass2 = new RooRealVar("bkg_p4mass2","",0);
  //bkg_p4mass2 = new RooRealVar("bkg_p4mass2","",-5.16296e-01,-1,1);
  //bkg_p4mass2 = new RooRealVar("bkg_p4mass2","",-5.87706e-01);
  //bkg_p5mass2 = new RooRealVar("bkg_p5mass2","",0,-1,1);
  bkg_p5mass2 = new RooRealVar("bkg_p5mass2","",0);

  RooChebychev bkg_jpsi2mass_Pol("bkg_jpsi2mass_Pol","",Psi2_Mass,RooArgList(*bkg_p3mass2,*bkg_p4mass2,*bkg_p5mass2));
  //RooChebychev bkg_jpsi2mass_Pol("bkg_jpsi2mass_Pol","",Psi2_Mass,RooArgList(*bkg_p3mass2,*bkg_p4mass2,*bkg_p5mass2));
  
  RooArgSet dataVars(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy, Psi1To2Significance); 
  dataVars.add(RooArgSet(Psi1To2_dY, FourMu_Mass, FourMu_pT, FourMu_Rapidity,FourMu_RapidityAbs, Psi1_pT, Psi2_pT, pT_Asymmetery, Delta_Phi));
  //RooDataSet* readdata = RooDataSet::read("nlopuInputToFit.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("dpsInputToFit.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("Selected_newAcc.txt",dataVars);
  RooDataSet* readdata = RooDataSet::read("Selected_newAcc_newVars.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("Selected_pt10_y1p9.txt",dataVars);
 // RooDataSet* readdata = RooDataSet::read("Selected_pt10_y1p2.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("Selected_noVtxCut.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("Selected_pt8_y0p95.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("Selected_ptLE8_yGE0p95.txt",dataVars);
  RooDataSet* data ;
  data = new RooDataSet("data","data",readdata ,dataVars);
    RooProdPdf sig_model("sig_model","sig_model",RooArgList(jpsi2mass));
    RooProdPdf bkg_model("bkg_model","bkg_model",RooArgList(bkg_jpsi2mass_Pol));

  //RooRealVar nsig("nsig","number of Signal events",564);
  RooRealVar nsig("nsig","number of Signal events",200,1,5000);
  RooRealVar nbkg("nbkg","number of background events",1,0,100);
  //RooRealVar nbkg("nbkg","number of background events",1.);

  RooAddPdf model("model","model",RooArgList(sig_model,bkg_model),RooArgList(nsig,nbkg));
  model.fitTo(*data,Extended(kTRUE),Hesse(kTRUE),Minos(kFALSE));

  RooPlot* frame2 = Psi2_Mass->frame(Title("#mu^{+}#mu^{-}"));
  frame2 = Psi2_Mass->frame(10);
  data->plotOn(frame2);
  model.plotOn(frame2);
  model.plotOn(frame2,RooFit::Components("Sig,sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(kDashed));
    model.plotOn(frame2,RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(kDashed));
  model.paramOn(frame2,Layout(0.65));
  frame2->getAttText()->SetTextSize(0.02);
  TCanvas* c2 = new TCanvas("c2","c2",10,10,500,500);
    c2->cd();
    c2->SetLeftMargin(0.11);
    c2->SetFillColor(kWhite);
    frame2->SetTitleOffset(1.3,"Y");
    frame2->SetTitle("");
    frame2->SetXTitle("#mu^{+}#mu^{-} 2 Invariant Mass [GeV/c^{2}]");
    frame2->Draw();
    //c2->SaveAs("pic/Psi2_mass.pdf");
    //c2->Close();
}

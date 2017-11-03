#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include <TPaveText.h>

using namespace RooFit ;
using namespace RooStats ;

void AddModel(RooWorkspace*);
void DoSPlot(RooWorkspace*);
void MakePlots(RooWorkspace*);

void splotMLFdatafit_withNLO()
{

  gROOT->SetStyle("Plain");

  RooWorkspace* wspace = new RooWorkspace("myWS");

  AddModel(wspace);
  DoSPlot(wspace);
  MakePlots(wspace);

  delete wspace;
  
}

 
//____________________________________
void AddModel(RooWorkspace* ws){
  std::cout<<"Add Model"<<std::endl;
  RooRealVar* run = new RooRealVar("run","run number",0.,1e10);
  RooRealVar* event = new RooRealVar("event","event number",0.,1e10);
  RooRealVar* FourMu_Mass = new RooRealVar("FourMu_Mass","FourMu_Mass",0.,999.);
  RooRealVar* FourMu_pT= new RooRealVar("FourMu_pT","FourMu_pT",0.,999.);
  RooRealVar* Psi1_CTxy = new RooRealVar("Psi1_CTxy","Psi1_CTxy",-0.05,0.1);
  RooRealVar* Psi2_CTxy = new RooRealVar("Psi2_CTxy","Psi2_CTxy",-100,100.);
  RooRealVar* Psi1_Mass = new RooRealVar("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar* Psi2_Mass = new RooRealVar("Psi2_Mass","Psi2_Mass",2.85,3.35);
  RooRealVar* Psi1To2_dY = new RooRealVar("Psi1To2_dY","Psi1To2_dY",-100.,100);
  RooRealVar* Psi1To2Significance = new RooRealVar("Psi1To2Significance","Psi1To2Significance",0.,8.);
  std::cout<<"begin read data"<<std::endl;
  // Variables
  RooArgSet dataVars(*Psi1_Mass, *Psi2_Mass, *Psi1_CTxy, *Psi2_CTxy, *Psi1To2Significance); 
  dataVars.add(RooArgSet(*Psi1To2_dY, *FourMu_Mass, *FourMu_pT, *run, *event));
  RooDataSet* readdata = RooDataSet::read("dataInputToFit.txt",dataVars);
  //RooDataSet* readdata = RooDataSet::read("TMTight_5varMLFreduced.txt",dataVars);
  RooDataSet* data ;
  data = new RooDataSet("data","data",readdata ,dataVars);
//BEGIN PDF SHAPES
  std::cout<<"begin pdf shapes"<<std::endl;
  jpsi1_mass_1 = new RooRealVar("jpsi1_mass_1","",3.09136);
  jpsi1_width_1 = new RooRealVar("jpsi1_width_1","",7.74729e-02);
  jpsi1_width_2 = new RooRealVar("jpsi1_width_2","",3.64832e-01);
  frac_1 = new RooRealVar("frac_1","",7.42738e-02);
  jpsi1_width_a = new RooFormulaVar("jpsi1_width_a","","@0*@1",RooArgList(*jpsi1_width_1,*jpsi1_width_2));

  RooGaussian jpsi1mass_1("jpsi1mass_1","jpsi mass distribution",*Psi1_Mass,*jpsi1_mass_1,*jpsi1_width_1);
  RooGaussian jpsi1mass_2("jpsi1mass_2","jpsi mass distribution",*Psi1_Mass,*jpsi1_mass_1,*jpsi1_width_a);
  RooAddPdf jpsi1mass("jpsi1mass","jpsi1 mass distribution",RooArgList(jpsi1mass_1,jpsi1mass_2),RooArgList(*frac_1));
//-- bkg params for mass 1

  bkg_jpsi1_mass_1 = new RooRealVar("bkg_jpsi1_mass_1","",3.09136);
  bkg_jpsi1_width_1 = new RooRealVar("bkg_jpsi1_width_1","",5.20963e-02);
  bkg_jpsi1_width_2 = new RooRealVar("bkg_jpsi1_width_2","",9.98745e-01);
  RooRealVar*    bkg_frac_6 = new RooRealVar("bkg_frac_6","",9.26091e-01);
  bkg_jpsi1_width_a = new RooFormulaVar("bkg_jpsi1_width_a","","@0*@1",RooArgList(*bkg_jpsi1_width_1,*bkg_jpsi1_width_2));
  bkg_p3 = new RooRealVar("bkg_p3","",-1.81248e-01);
  bkg_p4 = new RooRealVar("bkg_p4","",-4.66191e-01);
  bkg_p5 = new RooRealVar("bkg_p5","",4.49594e-01);

  RooGaussian bkg_jpsi1mass_1("bkg_jpsi1mass_1","jpsi mass distribution",*Psi1_Mass,*bkg_jpsi1_mass_1,*bkg_jpsi1_width_1);
  RooGaussian bkg_jpsi1mass_2("bkg_jpsi1mass_2","jpsi mass distribution",*Psi1_Mass,*bkg_jpsi1_mass_1,*bkg_jpsi1_width_a);
  RooAddPdf bkg_jpsi1mass("bkg_jpsi1mass","jpsi1 mass distribution",RooArgList(bkg_jpsi1mass_1,bkg_jpsi1mass_2),RooArgList(*bkg_frac_6));
  RooChebychev bkg_jpsi1mass_Pol("bkg_jpsi1mass_Pol","",*Psi1_Mass,RooArgList(*bkg_p3,*bkg_p4,*bkg_p5));
  frac_bkg = new RooRealVar("frac_bkg","",7.75667e-01);
  RooAddPdf bkg_mass1model("bkg_mass1model","jpsi 1 bkg model",RooArgList(bkg_jpsi1mass,bkg_jpsi1mass_Pol),RooArgList(*frac_bkg));


//mass 2 signal fixed to resonaance mc

  jpsi2_mass_1 = new RooRealVar("jpsi2_mass_2","",3.09136);
  jpsi2_width_1 = new RooRealVar("jpsi2_width_1","",8.49500e-02);
  jpsi2_width_2 = new RooRealVar("jpsi2_width_2","",3.71140e-01);
  frac_2 = new RooRealVar("frac_2","",6.00536e-02);
  jpsi2_width_a = new RooFormulaVar("jpsi2_width_a","","@0*@1",RooArgList(*jpsi2_width_1,*jpsi2_width_2));

  RooGaussian jpsi2mass_1("jpsi2mass_1","jpsi mass distribution",*Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_1);
  RooGaussian jpsi2mass_2("jpsi2mass_2","jpsi mass distribution",*Psi2_Mass,*jpsi2_mass_1,*jpsi2_width_a);
  RooAddPdf jpsi2mass("jpsi2mass","jpsi2 mass distribution",RooArgList(jpsi2mass_1,jpsi2mass_2),RooArgList(*frac_2));


//mass 2 bkg shape
  bkg_jpsi2_mass_1 = new RooRealVar("bkg_jpsi2_mass_1","",3.09136);
  bkg_jpsi2_width_1 = new RooRealVar("bkg_jpsi2_width_1","",7.36673e-02);
  bkg_jpsi2_width_2 = new RooRealVar("bkg_jpsi2_width_2","",9.94934e-01);
  RooRealVar*    bkg_frac_7 = new RooRealVar("bkg_frac_7","",7.00674e-06);
  bkg_jpsi2_width_a = new RooFormulaVar("bkg_jpsi2_width_a","","@0*@1",RooArgList(*bkg_jpsi2_width_1,*bkg_jpsi2_width_2));
  bkg_p3mass2 = new RooRealVar("bkg_p3mass2","",-5.26058e-01);
  bkg_p4mass2 = new RooRealVar("bkg_p4mass2","",6.33263e-01);
  bkg_p5mass2 = new RooRealVar("bkg_p5mass2","",8.80738e-02);

  RooGaussian bkg_jpsi2mass_1("bkg_jpsi2mass_1","jpsi mass distribution",*Psi2_Mass,*bkg_jpsi1_mass_1,*bkg_jpsi2_width_1);
  RooGaussian bkg_jpsi2mass_2("bkg_jpsi2mass_2","jpsi mass distribution",*Psi2_Mass,*bkg_jpsi1_mass_1,*bkg_jpsi2_width_a);
  RooAddPdf bkg_jpsi2mass("bkg_jpsi2mass","jpsi1 mass distribution",RooArgList(bkg_jpsi2mass_1,bkg_jpsi2mass_2),RooArgList(*bkg_frac_7));
  RooChebychev bkg_jpsi2mass_Pol("bkg_jpsi2mass_Pol","",*Psi2_Mass,RooArgList(*bkg_p3mass2,*bkg_p4mass2,*bkg_p5mass2));
  frac_bkg_mass2 = new RooRealVar("frac_bkg_mass2","",7.60762e-01);
  RooAddPdf bkg_mass2model("bkg_mass2model","jpsi 2 bkg model",RooArgList(bkg_jpsi2mass,bkg_jpsi2mass_Pol),RooArgList(*frac_bkg_mass2));

//--yo, these are SigMC Fit parameters in ctxy for bkg
  RooRealVar sigmcR_mean_coreCT1("sigmcR_mean_coreCT1","",1.93295e-04);
  RooRealVar sigmcR_mean_tailCT1("sigmcR_mean_tailCT1","",4.07126e-05);
  RooRealVar sigmcR_sigma_coreCT1("sigmcR_sigma_coreCT1","",5.09628e-03);
  RooRealVar sigmcR_sigma_tailCT1("sigmcR_sigma_tailCT1","",2.18344e-03);
  RooFormulaVar R_sigma_totCT1("sigmcR_sigma_totCT1","","",RooArgList(sigmcR_sigma_coreCT1,sigmcR_sigma_tailCT1));
  RooRealVar sigmcR_fracCT1("sigmcR_fracCT1","",1.90423e-01);
  RooGaussian sigmcct_1a("sigmcct_1a","ct distributionsigmc",*Psi1_CTxy,sigmcR_mean_coreCT1,sigmcR_sigma_coreCT1);
  RooGaussian sigmcct_1b("sigmcct_1b","ct distributionsigmc",*Psi1_CTxy,sigmcR_mean_tailCT1,sigmcR_sigma_tailCT1);
 
  RooAddPdf sigmcct_1("sigmcct_1","ct distributionsigmc",RooArgList(sigmcct_1a,sigmcct_1b),RooArgList(sigmcR_fracCT1));

//-- ctxy bkg
//  bkg1_R_mean_core = new RooRealVar("bkg1_R_mean_core","",3.81478e-03);
//  bkg1_R_mean_tail = new RooRealVar("bkg1_R_mean_tail","",1.64523e-03);
//  bkg1_R_sigma_core = new RooRealVar("bkg1_R_sigma_core","",9.65292e-03);
//  bkg1_R_sigma_tail = new RooRealVar("bkg1_R_sigma_tail","",3.74515e-01);
//  bkg_frac_1 = new RooRealVar("bkg_frac_1","",2.63568e-01);
//  bkg1_R_sigma_tot = new RooFormulaVar("bkg1_R_sigma_tot","","@0*@1",RooArgList(*bkg1_R_sigma_tail,*bkg1_R_sigma_core));
//
//  RooGaussian bkg_ctSB1_1a("bkg_ctSB1_1a","ct distribution",*Psi1_CTxy,*bkg1_R_mean_core,*bkg1_R_sigma_core);
//  RooGaussian bkg_ctSB1_1b("bkg_ctSB1_1b","ct distribution",*Psi1_CTxy,*bkg1_R_mean_tail,*bkg1_R_sigma_tot);
//  RooAddPdf bkg_CT1_SB1("bkg_CT1_SB1","ct distribution",RooArgList(bkg_ctSB1_1a,bkg_ctSB1_1b),RooArgList(*bkg_frac_1));
////////////////////////////////////////////////////////////////////////

//roodecay ctxy bkg paramaterization
    RooRealVar ct_mean_core("ctmeancore","",0,-1,1);
    RooRealVar ct_sigma_core("ctsigmacore","",0,0,1);
    RooRealVar ct_lambda("ctlambda","",2.42748e-03);
    RooGaussModel resolute_cour("resolute_cour","",*Psi1_CTxy,sigmcR_mean_tailCT1,sigmcR_sigma_tailCT1);
    //RooGaussModel resolute_cour("resolute_cour","",Psi1_CTxy,ct_mean_core,ct_sigma_core);
    RooDecay bkg_CT1_SB1("ct1sb1","",*Psi1_CTxy,ct_lambda,resolute_cour,RooDecay::SingleSided);
//-- These are signal mc fit parameters for dsig

    RooRealVar R_mean_core("R_mean_core","",3.89325e-01);
    RooRealVar R_sigma_core("R_sigma_core","",2.61409e-01);
    RooRealVar etab_lambda("etab_lambda","",6.11751e-01);
    RooGaussModel resolution_core("resolution_core","",*Psi1To2Significance,R_mean_core,R_sigma_core);
    RooDecay sig_distT("sig_distT","",*Psi1To2Significance,etab_lambda,resolution_core,RooDecay::SingleSided);
//--These are bkg parameters for dsig
    RooRealVar bkg_co02("bkg_co02","",-6.99005e-01);
    RooRealVar bkg_co12("bkg_co12","",-5.11977e-01);
    RooRealVar bkg_flau2("bkg_flau2","",9.99972e-01);
    RooRealVar bkg_meanlandau2("bkg_meanlandau2","",6.34623e-01);
    RooRealVar bkg_sigmalandau2("bkg_sigmalandau2","",2.37338e-01);
    RooChebychev bkg_polyshape2("bkg_polyshape2","",*Psi1To2Significance,RooArgList(bkg_co02,bkg_co12));
    RooLandau bkg_landau2("bkg_landau2", "bkg_landau2", *Psi1To2Significance, bkg_meanlandau2, bkg_sigmalandau2);
    RooAddPdf bkg_distT2("bkg_distT2","", RooArgList(bkg_landau2,bkg_polyshape2),RooArgList(bkg_flau2));

    RooProdPdf sig_model("sig_model","sig_model",RooArgList(jpsi1mass,jpsi2mass,sigmcct_1,sig_distT));
    RooProdPdf bkg_model("bkg_model","bkg_model",RooArgList(bkg_mass1model,bkg_mass2model,bkg_CT1_SB1,bkg_distT2));

  RooRealVar nsig("nsig","number of Signal events",745,1,2000);
  RooRealVar nbkg("nbkg","number of background events",257,0,2000);

  RooAddPdf model("model","model",RooArgList(sig_model,bkg_model),RooArgList(nsig,nbkg));


  std::cout << "import model" << std::endl;
  ws->import(model);
  std::cout << "import data" << std::endl;
  ws->import(*data);

  cout << "data entries: " << data->numEntries() << endl;

}

//____________________________________
void DoSPlot(RooWorkspace* ws){
  std::cout << "Calculate sWeights" << std::endl;

  RooAbsPdf* model = ws->pdf("model");
  RooRealVar* nsig = ws->var("nsig");
  RooRealVar* nbkg = ws->var("nbkg");
  RooDataSet* data = (RooDataSet*) ws->data("data");
  std::cout<<"Fit Model to data"<<std::endl;
  // fit the model to the data.
  model->fitTo(*data,Extended(kTRUE),Hesse(kTRUE),Minos(kFALSE));

  RooMsgService::instance().setSilentMode(true);
  std::cout<<" Add SWeights to dataset" <<std::endl;
  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot",
					       *data, model, RooArgList(*nsig,*nbkg) );


  // Check that our weights have the desired properties

  std::cout << "Check SWeights:" << std::endl;

  std::cout << std::endl <<  "Yield of sig is " 
	    << nsig->getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("nsig") << std::endl;

  std::cout << std::endl <<  "Yield of bkg is " 
	    << nbkg->getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("nbkg") << std::endl;

  cout << endl;   cout << endl;   cout << endl;
  float sum20=0;
  float sum50=0;
  float sum100=0;
  float sum200=0;
  float sum300=0;
  float sum600=0;
  float sum900=0;
  float sum1200=0;
  float total=0;

  // saving weights into a file
  ofstream myfile;
  myfile.open ("weightsreducedFeb9.txt");
  // plot the weight event by event with the Sum of events values as cross-check
  for(Int_t i=0; i < data->numEntries(); i++) {
      //myfile << sData->GetSWeight(i,"nsig") << " " << sData->GetSWeight(i,"nBbkg") << " " << sData->GetSWeight(i,"nbkg") << " " << sData->GetSWeight(i,"nbkg2") << endl;  
      //myfile << sData->GetSWeight(i,"nsig") <<endl;
    myfile << (unsigned int) data->get(i)->getRealValue("run")
//             << " " << (unsigned int) data->get(i)->getRealValue("event")
//	   << " " << (float) data->get(i)->getRealValue("FourMu_Mass")
//	   << " " << (float) data->get(i)->getRealValue("FourMu_pT")
//	   << " " << (float) data->get(i)->getRealValue("Psi1To2_dY")
//	   << " " << (float) data->get(i)->getRealValue("Psi1_Mass")
//	   << " " << (float) data->get(i)->getRealValue("Psi2_Mass")
//	   << " " << (float) data->get(i)->getRealValue("Psi1_CTxy")
//	   << " " << (float) data->get(i)->getRealValue("Psi1To2Significance")
             << " " << sData->GetSWeight(i,"nsig")
             << endl;
     // std::cout << "nsig Weight   " << sData->GetSWeight(i,"nsig") 
     //		<< "   nBbkg Weight   " << sData->GetSWeight(i,"nBbkg")
     //		<< "   nbkg Weight   " << sData->GetSWeight(i,"nbkg")
     //		<< "   nbkg2 Weight  " << sData->GetSWeight(i,"nbkg2")
//		<< "   Total Weight   " << sData->GetSumOfEventSWeight(i) 
//		<< std::endl;
      total+=sData->GetSWeight(i,"nsig");         
      if(i<20) sum20+=sData->GetSWeight(i,"nsig");
      if(i<50) sum50+=sData->GetSWeight(i,"nsig");
      if(i<100) sum100+=sData->GetSWeight(i,"nsig");
      if(i<200) sum200+=sData->GetSWeight(i,"nsig");
      if(i<300) sum300+=sData->GetSWeight(i,"nsig");
      if(i<600) sum600+=sData->GetSWeight(i,"nsig");
      if(i<900) sum900+=sData->GetSWeight(i,"nsig");
      if(i<1200) sum1200+=sData->GetSWeight(i,"nsig");

    }
  myfile.close();

  std::cout << std::endl;

  std::cout<<"Sum of the sWeights is: "<<total<<std::endl;
  std::cout<<"Sum of the first 20 sWeights is: "<<sum20<<std::endl;
  std::cout<<"Sum of the first 50 sWeights is: "<<sum50<<std::endl;
  std::cout<<"Sum of the first 100 sWeights is: "<<sum100<<std::endl;
  std::cout<<"Sum of the first 200 sWeights is: "<<sum200<<std::endl;
  std::cout<<"Sum of the first 300 sWeights is: "<<sum300<<std::endl;
  std::cout<<"Sum of the first 600 sWeights is: "<<sum600<<std::endl;
  std::cout<<"Sum of the first 900 sWeights is: "<<sum900<<std::endl;
  std::cout<<"Sum of the first 1200 sWeights is: "<<sum1200<<std::endl;
  std::cout<<"Total # of events: "<<data->numEntries()<<std::endl;

  // import this new dataset with sWeights
  std::cout << "import new dataset with sWeights" << std::endl;
  ws->import(*data, Rename("dataWithSWeights"));

}

void MakePlots(RooWorkspace* ws){

  std::cout << "make plots" << std::endl;

  RooAbsPdf* model = ws->pdf("model");
  RooAbsPdf* model_dY = ws->pdf("model_dY");
  RooRealVar* nsig = ws->var("nsig");
  RooRealVar* nsigDPS = ws->var("nsigDPS");
  RooRealVar* nsigSPS = ws->var("nsigSPS");
  RooRealVar* nbkg = ws->var("nbkg");
  RooRealVar* FourMu_Mass = ws->var("FourMu_Mass");
  RooRealVar* Psi1_Mass = ws->var("Psi1_Mass");
  RooRealVar* Psi2_Mass = ws->var("Psi2_Mass");
  RooRealVar* Psi1_CTxy = ws->var("Psi1_CTxy");
  RooRealVar* Psi2_CTxy = ws->var("Psi2_CTxy");
  RooRealVar* Psi1To2_dY = ws->var("Psi1To2_dY");
  RooRealVar* Psi1To2Significance = ws->var("Psi1To2Significance");

  // note, we get the dataset with sWeights
  RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");
  model->fitTo(*data, Extended() );

  // make TTree with efficiency variation info
  //TFile *fFile = new TFile("Fit_Results_Eff_Cut.root","recreate");
  setTDRStyle();
  // make our canvas
  TCanvas* cmass1 = new TCanvas("sPlotMass1","sPlotMass1", 600, 600);
  cmass1->cd();
  cmass1->SetFillColor(kWhite);

  RooPlot* Mass1Plot = Psi1_Mass->frame(20);
  data->plotOn(Mass1Plot,Name("data"), DataError(RooAbsData::SumW2));
  model->plotOn(Mass1Plot,Name("all"));
  model->plotOn(Mass1Plot,Name("sig"),RooFit::Components("Sig,sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(2));
  model->plotOn(Mass1Plot,Name("bkg"),RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(3));
  Mass1Plot->SetTitle("");
  Mass1Plot->SetXTitle("#mu^{+}#mu^{-} 1 Invariant Mass (GeV/c^{2})");
  Mass1Plot->SetYTitle("Events / 0.025 GeV/c^{2}");
  Mass1Plot->SetLabelOffset(0.012);
  //Mass1Plot->SetTitleOffset(0.95);
  Mass1Plot->Draw();
  //cmass1->SaveAs("pic/Psi1_mass.pdf");
  //cmass1->Close();

  TCanvas* cmass2 = new TCanvas("sPlotMass2","sPlotMass2", 600, 600);
  cmass2->cd();
  cmass2->SetFillColor(kWhite);
  RooPlot* Mass2Plot = Psi2_Mass->frame(20); 
  data->plotOn(Mass2Plot,Name("data"), DataError(RooAbsData::SumW2)); 
  model->plotOn(Mass2Plot,Name("all"));   
  model->plotOn(Mass2Plot,Name("sig"),RooFit::Components("Sig,sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(2));
  model->plotOn(Mass2Plot,Name("bkg"),RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(3));
  Mass2Plot->SetTitle("");
  Mass2Plot->SetXTitle("#mu^{+}#mu^{-} 2 Invariant Mass (GeV/c^{2})");
  Mass2Plot->SetYTitle("Events / 0.025 GeV/c^{2}");
  Mass2Plot->SetLabelOffset(0.012);
  //Mass2Plot->SetTitleOffset(0.95);
  Mass2Plot->Draw();
  //cmass2->SaveAs("pic/Psi2_mass.pdf");
  //cmass2->Close();

  TCanvas* cctxy1 = new TCanvas("sPlotCTxy1","sPlotCTxy1", 600, 600);
  cctxy1->cd();
  cctxy1->SetFillColor(kWhite);
  RooPlot* CTxy1Plot = Psi1_CTxy->frame(30); 
  data->plotOn(CTxy1Plot,Name("data"), DataError(RooAbsData::SumW2)); 
  model->plotOn(CTxy1Plot,Name("all"));   
  model->plotOn(CTxy1Plot,Name("sig"),RooFit::Components("Sig,sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(2));
  model->plotOn(CTxy1Plot,Name("bkg"),RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(3));
  CTxy1Plot->SetTitle("");
  CTxy1Plot->SetXTitle("J/#psi^{1} ct_{xy} (cm)");
  CTxy1Plot->SetYTitle("Events / 0.005 cm");
  CTxy1Plot->SetMaximum(2000);
  CTxy1Plot->SetMinimum(0.1);
  CTxy1Plot->Draw();
  cctxy1->SetLogy();
  //cctxy1->SaveAs("pic/Psi1_CTxy.pdf");
  //cctxy1->Close();

  TCanvas* csig = new TCanvas("sPlotSig","sPlotSig", 600, 600);
  csig->cd();
  RooPlot* SigPlot = Psi1To2Significance->frame(20); 
  data->plotOn(SigPlot,Name("data"), DataError(RooAbsData::SumW2)); 
  model->plotOn(SigPlot,Name("all"));   
  model->plotOn(SigPlot,Name("sig"),RooFit::Components("Sig,sig_*"),RooFit::LineColor(kRed), RooFit::LineStyle(2));
  model->plotOn(SigPlot,Name("bkg"),RooFit::Components("bkg_model"),RooFit::LineColor(kGreen), RooFit::LineStyle(3));
  SigPlot->SetTitle("");
  SigPlot->SetYTitle("Events / 0.4");
  SigPlot->SetXTitle("J/#psi Distance Significance");
  SigPlot->Draw();

//  TCanvas* csig = new TCanvas("sPlotSig","sPlotSig", 600, 600);
//  csig->cd();
//  RooPlot* SigPlot = FourMu_Mass->frame(10,21,20); 
//  data->plotOn(SigPlot,Name("data"), DataError(RooAbsData::SumW2)); 
//  SigPlot->SetTitle("");
//  SigPlot->SetYTitle("Events / 0.55 GeV");
//  SigPlot->SetXTitle("Mass_{4#mu} GeV");
//  SigPlot->Draw();
}

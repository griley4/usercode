{
//  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);


  using namespace RooFit;
  RooRealVar mass("mass","Four Muon Mass (GeV)",6,60);
  RooRealVar FourMu_pT("pt","pt",0,100);
  //RooRealVar run("run","run",0,9000000000);
  //RooRealVar event("event","event",0,9000000000);
  RooRealVar VtxProb("VtxProb","VtxProb",0.1,1.);
  RooRealVar Psi1To2Significance("Psi1To2Significance","Psi1To2Significance",0.,5.);
  RooRealVar Psi1_Mass("Psi1_Mass","Psi1_Mass",2.85,3.35);
  RooRealVar Psi2_Mass("Psi2_Mass","Psi2_Mass",2.85,3.35);
  RooRealVar Psi1_pT("Psi1_pT","Psi1_pT",0,100);
  RooRealVar Psi2_pT("Psi2_pT","Psi2_pT",0,100);
  RooRealVar Psi1_eta("Psi1_eta","Psi1_eta",-2.4,2.4);
  RooRealVar Psi2_eta("Psi2_eta","Psi2_eta",-2.4,2.4);
  RooRealVar Psi1_CTxy("Psi1_CTxy","Psi1_CTxy",-1.,1.);
  RooRealVar Psi2_CTxy("Psi2_CTxy","Psi2_CTxy",-1.,1.);
  RooRealVar Psi1To2_dY("Psi1To2_dY","Psi1To2_dY",0.,5.);
  RooRealVar FourMu_Rapidity("FourMu_Rapidity","FourMu_Rapidity",-5,5);
  RooRealVar FourMu_RapidityAbs("FourMu_RapidityAbs","FourMu_RapidityAbs",-5,5);
  RooArgSet args(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy, Psi1To2Significance); 
  args.add(RooArgSet(Psi1To2_dY, mass, FourMu_pT, FourMu_Rapidity,FourMu_RapidityAbs));
  //RooDataSet* data = RooDataSet::read("massfit_TMTightReduced.txt",args);
  RooDataSet *data =  new RooDataSet("data","data",args,0);
  data = RooDataSet::read("Selected_newAcc.txt",args);
  //// Best 8TEV fit param values (2.89 sigma)
  //RooRealVar a0("a0","a0",-0.556454);
  //RooRealVar a1("a1","a1",0.19792);
  //RooRealVar a2("a2","a2",0.0);
  //RooRealVar a3("a3","a3",0.0);
  //RooRealVar a4("a4","a4",0.0404559);
 //fit to full range for toy gen
  RooRealVar a0("a0","a0",-1.08522e+00);
  RooRealVar a1("a1","a1",0);
  RooRealVar a2("a2","a2",1.65577e-01);
  RooRealVar a3("a3","a3",0.0);
  RooRealVar a4("a4","a4",0.0);
  RooChebychev bkg("bkg","Background",mass,RooArgSet(a0,a1,a2,a3,a4));
  RooRealVar tau("tau","lifetime",-4.52851e-01);
  RooExponential exp("exp","Exp", mass, tau);
  RooRealVar frac("frac","frac",4.25470e-01);
  RooAddPdf bkgsum("bkgsum","exp+bkg",RooArgList(exp,bkg),RooArgList(frac));
  //RooRealVar nbkg("nbkg","nbackground",2.42167e+03 );
  RooRealVar nbkg("nbkg","nbackground",2500,0,4000);
  Float_t before = 0;
  Float_t after = 0;
  Float_t resolution = 0.143;
//  for(Int_t i = 100; i<=600; ++i){ 
  Int_t i = 273;
  before = after = 0;
   //SCAN
  RooRealVar mean("mean","{4#mu}_{mass}",i/10.);
  //RooRealVar mean("mean","{4#mu}_Mass}",25.1);
  resolution = 80.31 + (2.01 * (i/10.)) + (0.1045*(i/10.)*(i/10.)); 
  RooRealVar sigma("sigma","sigma 4mu mass",resolution/1000.);
  //RooRealVar sigma("sigma","sigma 4mu mass",0.143);
  RooRealVar width("width","Width",0.12,0.01,3);
  //RooRealVar width("width","Width",0.12);
  RooVoigtian Voig("voig","voig PDF",mass,mean,sigma,width);

  RooRealVar nsig("nsig","nsignal",100,0,500);
  RooAddPdf sum("sum","g+p",RooArgList(Voig,bkgsum),RooArgList(nsig,nbkg));

  sum.fitTo(*data,Extended(kTRUE));
  RooPlot* Massframe = mass.frame(60);
  //RooPlot* Massframe = mass.frame(10,21,16);
  TCanvas c1("c1","c1",700,700);
  data->plotOn(Massframe);
  sum.plotOn(Massframe,Name("background"));
  sum.plotOn(Massframe,Components(bkgsum),LineStyle(kDashed));
  sum.plotOn(Massframe,Name("sig"),Components(Voig),LineColor(kRed));
  Massframe->Draw();
//RooAbsReal* nll = sum.createNLL(*data);
//before = nll->getVal();
//nsig = 0;
//after = nll->getVal();
//std::cout<<" "<<before<<" " <<sqrt(2*fabs(before - after))<< "    " << i/10. <<  " " << width <<" " <<resolution/1000.<<"  Result"<<std::endl;
// }

}

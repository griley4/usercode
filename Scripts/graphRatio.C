{

  int n = 20;
  float ratio[] = {1.991,2.005,2.033,2.073,2.113,2.124,2.179,2.262,2.239,2.343,2.353,2.397,2.475,2.428,2.614,2.636,2.731,2.904,2.979,3.004};
  float pct[] = {6.7e-02,6.9e-02,6.7e-02,6.7e-02,6.8e-02,6.8e-02,6.8e-02,6.8e-02,6.9e-02,6.9e-02,6.9e-02,7.1e-02,7.4e-02,9.1e-02,9.2e-02,9.6e-02,9.8e-02,1.4e-01,1.4e-01,1.5e-01};
  float pt[] = {20.5,21.5,22.5,23.5,24.5,25.5,26.5,27.5,28.5,29.5,31,33,35,37,40,44,48,55,67.5,85};
  float pte[] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,1,1,1,1,2,2,2,5,7.5,10};
  float xsec[] = {44.1,34,26.4,21,17,13.8,11.2,9.39,7.7,6.45,5.01,3.58,2.65,1.92,1.34,0.77,0.49,0.25,0.08,0.02};
  float xsecpct[] = {0.053,0.054,0.053,0.052,0.053,0.054,0.054,0.055,0.056,0.057,0.056,0.058,0.063,0.07,0.071,0.079,0.084,0.091,0.1,0.17,0.156};
  float error[20]=0;
  float xsece[20]=0;
  for(int i=0;i<n;++i){
   error[i] = pct[i]*ratio[i];
    xsece[i] = xsecpct[i]*xsec[i]; 
  }
  TCanvas* c1 = new TCanvas("c1","c1",600,800);
  TGraphErrors* g = new TGraphErrors(n,pt,ratio,pte,error);
  TGraphErrors* h = new TGraphErrors(n,pt,xsec,pte,xsece);
  h->Draw("AP");
  TF1 *f1 = new TF1("f1","pol2",0,100);
  TF1 *f2b = new TF1("f2b","gaus+gaus(3)",0,100);
  TF1 *f2 = new TF1("f2","[2]*(x*(1+(1/([0]-2))*((x**2)/[1]))**-[0])",0,100);
  f2->SetParameter(0,4);
  f2->SetParameter(1,12);
  f2->SetParLimits(0,0,10);
  f2->SetParLimits(1,0,1000);
  TF1 *f2a = new TF1("f2a","expo*f2",0,100);
  //g->Fit("f1","FR");
  h->Fit("f2","R");
  c1->SetLogy();
  TAxis a = g->GetXAxis();
  a.SetLimits(1,100);
  g->SetMinimum(0);
  g->Draw();

}

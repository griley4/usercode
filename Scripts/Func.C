//this was to full sample
//{
//  TF1 func("func","[6]*([0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x)",0.1,3.5);
//  func->FixParameter(1,-6.223e-3);
//  func->FixParameter(2,-5.732e-3);
//  func->FixParameter(3,6.985e-3);
//  func->FixParameter(4,-2.369e-3);
//  func->FixParameter(5,2.595e-4);
//  func->FixParameter(0,0.017);
//
//}
{
  TF1 func("func","[6]*([0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x)",0.1,3.5);
  func->FixParameter(0 , 5.96493e+00);
  func->FixParameter(1 ,-1.27799e+00);
  func->FixParameter(2 ,-3.55991e+00);
  func->FixParameter(3 , 3.52331e+00);
  func->FixParameter(4 ,-1.17150e+00);
  func->FixParameter(5 , 1.27785e-01);
  func->SetParameter(6 , 4.34693e+02);
}

//fit to pt>8 dps mc
Minimizer is Linear
Chi2                      =     1.66992
NDf                       =     7
p0                        =     12.1244         +/-     3.82022     
p1                        =     -13.2993        +/-     39.1897     
p2                        =     38.4441         +/-     77.1988     
p3                        =     -33.5514        +/-     58.8228     
p4                        =     11.5073         +/-     19.2886     
p5                        =     -1.40449        +/-     2.2828      

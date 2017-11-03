{
  std::cout<<"new Cuts with muons"<<std::endl;
  //std::cout<<"FourMu_Mass>=0&&FourMu_Mass<=80&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-5.35*abs(Psi_y)+13.0)||abs(Psi_y)>=1.8&&abs(Psi_y)<=2.2&&Psi_pT>3.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.4&&Mu_pT>2.0)==4"<<std::endl;
  std::cout<<"FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.4&&(Psi_pT>-5.55*abs(Psi_y)+13.3)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4"<<std::endl;

  std::cout<<"3 muon acceptance lines"<<std::endl;
  std::cout<<"TLine ta(0,3.5,1.2,3.5)"<<std::endl;
  std::cout<<"TLine tb(1.2,3.5,1.6,2.0)"<<std::endl;
  std::cout<<"TLine tc(1.6,2.0,2.0,2.0)"<<std::endl;
             
             
  std::cout<<"JPsi Acceptance lines"<<std::endl;
  std::cout<<"TLine Ja(0,8.0,0.95,8.0)"<<std::endl;
  std::cout<<"TLine Jb(0.95,8.0,1.4,5.5)"<<std::endl;
  //std::cout<<"TLine Jb(0.95,8.0,1.8,3.5)"<<std::endl;
  std::cout<<"TLine Jc(1.4,5.5,1.9,5.5)"<<std::endl;
  //std::cout<<"TLine Jc(1.8,3.5,2.2,3.5)"<<std::endl;

}



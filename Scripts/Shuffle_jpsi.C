#include <vector>
#include <TROOT.h>
#include <TFile.h>
#include "TF1.h"
#include "Riostream.h"
#include <TChain.h>
#include <TStyle.h>
#include <stdlib.h>
#include "TLorentzVector.h" 
#include "TMath.h" 

int main() {
  gROOT->Reset();

  TChain *chainDataraw = new TChain("PATEventTree");
  chainDataraw->Add("../January2017/Modified_Input_To_Fit_2012MuOnia_TMTight_3MuL3Match.root");
  TChain *chainData = (TChain*)chainDataraw->CopyTree("FourMu_Mass>=0&&FourMu_Mass<=60&&FourMu_VtxProb>=0.1&&Sum$(abs(Psi_y)<=0.95&&Psi_pT>8.0||abs(Psi_y)>0.95&&abs(Psi_y)<1.8&&(Psi_pT>-3.33*abs(Psi_y)+11.0)||abs(Psi_y)>=1.4&&abs(Psi_y)<=1.9&&Psi_pT>5.5)==2&&Sum$(abs(Mu_Eta)<=1.2&&Mu_pT>3.5||abs(Mu_Eta)>1.2&&abs(Mu_Eta)<1.6&&(Mu_pT>-3.75*abs(Mu_Eta)+8)||abs(Mu_Eta)>=1.6&&abs(Mu_Eta)<=2.0&&Mu_pT>2.0)==4");

  TFile *fFile = new TFile("Shuffled_JPsi_sample.root","recreate");
  TTree *fTree = new TTree("PATEventTree", "PATEventTree");
  float FourMu_Mass,FourMu_pT, FourMu_Rapidity,Psi1To2_dY,Psi1To2_dphi,Psi_pT_asym,Mu_pT[4],Mu_Eta[4], Psi_pT[2], Psi_y[2], Mu_L3Match[4];
  float cFourMu_Mass, cFourMu_pT, cFourMu_Rapidity, cPsi1To2_dY, cMu_pT[4], cMu_Eta[4], cMu_L3Match[4], cPsi_pT[2], cPsi_y[2], cPsi1_px, cPsi1_py, cPsi1_pz, cPsi1_p, cPsi_Mass[2],cPsi2_px, cPsi2_py, cPsi2_pz, cPsi2_p, cPsi1_phi, cPsi2_phi, cPsi1_eta, cPsi2_eta;
  fTree->Branch("FourMu_Mass",  &FourMu_Mass,   "FourMu_Mass/F");
  fTree->Branch("FourMu_pT",  &FourMu_pT,   "FourMu_pT/F");
  fTree->Branch("FourMu_Rapidity",  &FourMu_Rapidity,   "FourMu_Rapidity/F");
  fTree->Branch("Psi1To2_dY",  &Psi1To2_dY,   "Psi1To2_dY/F");
  fTree->Branch("Psi1To2_dphi",  &Psi1To2_dphi,   "Psi1To2_dphi/F");
  fTree->Branch("Psi_pT",   Psi_pT,   "Psi_pT[2]/F");
  fTree->Branch("Psi_pT_asym",   &Psi_pT_asym,   "Psi_pT_asym/F");
  fTree->Branch("Psi_y",   Psi_y,   "Psi_y[2]/F");
  //  fTree->Branch("Mu_pT",  Mu_pT,   "Mu_pT[4]/F");
  //  fTree->Branch("Mu_Eta",  Mu_Eta,   "Mu_Eta[4]/F");
  //  fTree->Branch("Mu_L3Match",  Mu_L3Match,   "Mu_L3Match[4]/O");
  chainData->SetBranchAddress("FourMu_Mass",       &cFourMu_Mass);
  chainData->SetBranchAddress("FourMu_pT",       &cFourMu_pT);
  chainData->SetBranchAddress("FourMu_Rapidity",       &cFourMu_Rapidity);
  chainData->SetBranchAddress("Psi1To2_dY",       &cPsi1To2_dY);
  chainData->SetBranchAddress("Psi_pT",       cPsi_pT);
  chainData->SetBranchAddress("Psi_Mass",       cPsi_Mass);
  chainData->SetBranchAddress("Psi1_px",       &cPsi1_px);
  chainData->SetBranchAddress("Psi1_py",       &cPsi1_py);
  chainData->SetBranchAddress("Psi1_pz",       &cPsi1_pz);
  chainData->SetBranchAddress("Psi1_p",       &cPsi1_p);
  chainData->SetBranchAddress("Psi2_pz",       &cPsi2_px);
  chainData->SetBranchAddress("Psi2_py",       &cPsi2_py);
  chainData->SetBranchAddress("Psi2_pz",       &cPsi2_pz);
  chainData->SetBranchAddress("Psi2_p",       &cPsi2_p);
  chainData->SetBranchAddress("Psi_y",       cPsi_y);
  chainData->SetBranchAddress("Psi1_phi",       &cPsi1_phi);
  chainData->SetBranchAddress("Psi2_phi",       &cPsi2_phi);
  chainData->SetBranchAddress("Psi1_eta",       &cPsi1_eta);
  chainData->SetBranchAddress("Psi2_eta",       &cPsi2_eta);

  int cevent = chainData->GetEntries();
  TLorentzVector P1(0,0,0,0);
  TLorentzVector P2(0,0,0,0);
  std::cout<<"Events for weightsTree : FullTree "<<cevent<<" : " <<cevent<<std::endl;
  for (int i=0; i<cevent; ++i){
    chainData->GetEvent(i);
     P1.SetPtEtaPhiM(cPsi_pT[0],cPsi1_eta,cPsi1_phi,cPsi_Mass[0]); 
     P2.SetPtEtaPhiM(cPsi_pT[1],cPsi2_eta,cPsi2_phi,cPsi_Mass[1]); 
//    P1.SetPx(cPsi1_px);
//    P1.SetPy(cPsi1_py);
//    P1.SetPz(cPsi1_pz);
//    float e1 = sqrt(pow(cPsi1_p*2.99e8,2)+pow(cPsi_Mass[0]*pow(2.99e8,2),2));
//    P1.SetE(e1);
//    P2.SetPx(cPsi2_px);
//    P2.SetPy(cPsi2_py);
//    P2.SetPz(cPsi2_pz);
//    float e2 = sqrt(pow(cPsi2_p*2.99e8,2)+pow(cPsi_Mass[1]*pow(2.99e8,2),2));
//    P2.SetE(e2);

    TLorentzVector T1(0,0,0,0);
    TLorentzVector T2(0,0,0,0);

    for (int j=i; j<cevent; ++j){
      chainData->GetEvent(j);
     T1.SetPtEtaPhiM(cPsi_pT[0],cPsi1_eta,cPsi1_phi,cPsi_Mass[0]); 
     T2.SetPtEtaPhiM(cPsi_pT[1],cPsi2_eta,cPsi2_phi,cPsi_Mass[1]); 
//      T1.SetPx(cPsi1_px);
//      T1.SetPy(cPsi1_py);
//      T1.SetPz(cPsi1_pz);
//      T1.SetM(cPsi_Mass[0]);
//      T2.SetPx(cPsi2_px);
//      T2.SetPy(cPsi2_py);
//      T2.SetPz(cPsi2_pz);
//      T2.SetM(cPsi_Mass[1]);
      for(int q=0; q<2; ++q){
        if(q==0){
          TLorentzVector M0(0,0,0,0);
          M0 = P1 + T2;
          FourMu_Mass  = M0.M();
          FourMu_pT  = M0.Pt();
          FourMu_Rapidity  = M0.Rapidity();
          Psi_y[0] = P1.Rapidity();
          Psi_y[1] = T2.Rapidity();
          Psi_pT[0] = P1.Pt();
          Psi_pT[1] = T2.Pt();
          float diff0 = P1.Rapidity()-T2.Rapidity();
          Psi1To2_dY  = TMath::Abs(diff0);
          Psi1To2_dphi = TMath::Min((2*TMath::Pi()-TMath::Abs((TMath::ATan2(P1.Py(),P1.Px()))-(TMath::ATan2(T2.Py(),T2.Px())))),TMath::Abs((TMath::ATan2(P1.Py(),P1.Px()))-(TMath::ATan2(T2.Py(),T2.Px()))));
          Psi_pT_asym = (P1.Pt()-T2.Pt())/(P1.Pt()+T2.Pt());
          fTree->Fill();
        }
        if(q==1){
          TLorentzVector M1(0,0,0,0);
          M1 = T1 + P2;
          FourMu_Mass  = M1.M();
          FourMu_pT  = M1.Pt();
          FourMu_Rapidity  = M1.Rapidity();
          Psi_y[0] = T1.Rapidity();
          Psi_y[1] = P2.Rapidity();
          Psi_pT[0] = T1.Pt();
          Psi_pT[1] = P2.Pt();
          float diff1 = T1.Rapidity()-P2.Rapidity();
          Psi1To2_dY  = TMath::Abs(diff1);
          Psi1To2_dphi = TMath::Min((2*TMath::Pi()-TMath::Abs((TMath::ATan2(T1.Py(),T1.Px()))-(TMath::ATan2(P2.Py(),P2.Px())))),TMath::Abs((TMath::ATan2(T1.Py(),T1.Px()))-(TMath::ATan2(P2.Py(),P2.Px()))));
          Psi_pT_asym = (T1.Pt()-P2.Pt())/(T1.Pt()+P2.Pt());
          fTree->Fill();
        }
      }
      ++j;
    }
    ++i;
  }
  fFile->Write();
  fFile->Close();
  //std::cout<<dataeff[0][6]<<std::endl;
  //std::cout<<ptbins[0]<<" "<<ptbins[1]<<" "<<etabins[0]<<" "<<etabins[1]<<std::endl;
}

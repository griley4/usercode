#include <string>
#include <stdlib.h>
#include <cmath>
#include "Riostream.h"

#include <TROOT.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include <TRandom3.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1F.h>
#include <TH2F.h>
#include "TF1.h"
#include <TLorentzVector.h>
#include <TVector3.h>


int TriggerCheck() {
  gROOT->Reset();

  TChain data("PATEventTree");

  data.Add("Selected_events_newAcc.root");
  TH1F* flip_m = new TH1F("flip_m","flip_m",50,2.85,3.35);
  TH1F* flip_m4 = new TH1F("flip_m4","flip_m4",50,2.85,3.35);

  float mu_px0,mu_px1,mu_px2,mu_px3,mu_py0,mu_py1,mu_py2,mu_py3,mu_pz0,mu_pz1,mu_pz2,mu_pz3,mu0e,mu1e,mu2e,mu3e;
  float jpsi_mass0,jpsi_mass1,dimu_mass0,dimu_mass1;
  float mu_mass = 0.01057;
  float Mu_px[4],Mu_py[4],Mu_pz[4],Psi_Mass[2];
  int Mu_charge[4];
  bool Mu_L3Match[4];
  data.SetBranchAddress("Mu_px",       Mu_px);
  data.SetBranchAddress("Mu_py",       Mu_py);
  data.SetBranchAddress("Mu_pz",       Mu_pz);
  data.SetBranchAddress("Mu_charge",       Mu_charge);
  data.SetBranchAddress("Mu_L3Match",       Mu_L3Match);
  data.SetBranchAddress("Psi_Mass",       Psi_Mass);


  int ouch=0;
  int checked=0;
  int checked4=0;
  int onematch=0;
  int bothmatch=0;
  int chevent = data.GetEntries();
  for(int e=0;e<chevent;++e){
    data.GetEvent(e);
    int MatchN =0;

    mu_px0 = Mu_px[0];
    mu_py0 = Mu_py[0];
    mu_pz0 = Mu_pz[0];
    mu_px1 = Mu_px[1];
    mu_py1 = Mu_py[1];
    mu_pz1 = Mu_pz[1];
    mu_px2 = Mu_px[2];
    mu_py2 = Mu_py[2];
    mu_pz2 = Mu_pz[2];
    mu_px3 = Mu_px[3];
    mu_py3 = Mu_py[3];
    mu_pz3 = Mu_pz[3];
    TLorentzVector mu0,mu1,mu2,mu3;

    mu0.SetPx(mu_px0);mu0.SetPy(mu_py0);mu0.SetPz(mu_pz0);
    mu1.SetPx(mu_px1);mu1.SetPy(mu_py1);mu1.SetPz(mu_pz1);
    mu2.SetPx(mu_px2);mu2.SetPy(mu_py2);mu2.SetPz(mu_pz2);
    mu3.SetPx(mu_px3);mu3.SetPy(mu_py3);mu3.SetPz(mu_pz3);
    mu0e = sqrt(mu0.P()*mu0.P()+mu_mass*mu_mass);
    mu0.SetE(mu0e);
    mu1e = sqrt(mu1.P()*mu1.P()+mu_mass*mu_mass);
    mu1.SetE(mu1e);
    mu2e = sqrt(mu2.P()*mu2.P()+mu_mass*mu_mass);
    mu2.SetE(mu2e);
    mu3e = sqrt(mu3.P()*mu3.P()+mu_mass*mu_mass);
    mu3.SetE(mu3e);


    for(int i=0;i<4;++i){
      if(Mu_L3Match[i]){
        ++MatchN;
      }
    }

    if(MatchN==3){
      if(Mu_L3Match[0]&&Mu_L3Match[1]){
        std::cout<<(Mu_L3Match[2]&&Mu_L3Match[3])<<" ";
        TLorentzVector jpTrig = mu0+mu1;
        std::cout<<fabs(jpTrig.M()-Psi_Mass[0])/Psi_Mass[0]*100<<" ";
        std::cout<<fabs(jpTrig.M()-Psi_Mass[1])/Psi_Mass[1]*100<<" ";
        if(Mu_L3Match[2]){
          if(Mu_charge[2]*Mu_charge[0]==-1){
            TLorentzVector jpFlip = mu0+mu2;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass02 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else if(Mu_charge[2]*Mu_charge[1]==-1){
            TLorentzVector jpFlip = mu1+mu2;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass12 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else{ 
            std::cout<<"PROBLEM no pair neutral"<<std::endl;
            break;
          }
        }
        else if(Mu_L3Match[3]){
          if(Mu_charge[3]*Mu_charge[0]==-1){
            TLorentzVector jpFlip = mu0+mu3;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass03 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else if(Mu_charge[3]*Mu_charge[1]==-1){
            TLorentzVector jpFlip = mu1+mu3;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass13 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else{ 
            std::cout<<"PROBLEM no pair neutral"<<std::endl;
            break;
          }
        }
        else{std::cout<<"PROBLEM where's the 3rd triggerd muon"<<std::endl;break;}
        ++checked;
      }
      else if(Mu_L3Match[2]&&Mu_L3Match[3]){
        std::cout<<(Mu_L3Match[1]&&Mu_L3Match[0])<<" ";
        TLorentzVector jpTrig = mu2+mu3;
        std::cout<<fabs(jpTrig.M()-Psi_Mass[1])/Psi_Mass[1]*100<<" ";
        std::cout<<fabs(jpTrig.M()-Psi_Mass[0])/Psi_Mass[0]*100<<" ";
        if(Mu_L3Match[0]){
          if(Mu_charge[0]*Mu_charge[2]==-1){
            TLorentzVector jpFlip = mu0+mu2;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass02 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else if(Mu_charge[0]*Mu_charge[3]==-1){
            TLorentzVector jpFlip = mu0+mu3;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass03 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else{ 
            std::cout<<"PROBLEM no pair neutral"<<std::endl;
            break;
          }
        }
        else if(Mu_L3Match[1]){
          if(Mu_charge[1]*Mu_charge[2]==-1){
            TLorentzVector jpFlip = mu1+mu2;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass12 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else if(Mu_charge[1]*Mu_charge[3]==-1){
            TLorentzVector jpFlip = mu1+mu3;
            if(2.85<=jpFlip.M()&&jpFlip.M()<=3.35){++ouch;}
            std::cout<<"flip mass13 = "<<jpFlip.M()<<" ";
            flip_m->Fill(jpFlip.M());
          }
          else{ 
            std::cout<<"PROBLEM no pair neutral"<<std::endl;
            break;
          }
        }
        else{std::cout<<"PROBLEM where's the 3rd triggerd muon"<<std::endl;break;}
        ++checked;
      }
    }
    else if(MatchN==4){
      int ohtwo=0;int onethree=0;
      if(Mu_charge[0]*Mu_charge[2] ==-1){
        TLorentzVector jpFlip02 = mu0+mu2;
        TLorentzVector jpFlip13 = mu1+mu3;
        if(2.85<=jpFlip02.M()&&jpFlip02.M()<=3.35){ohtwo=1;}
            flip_m->Fill(jpFlip02.M());
        if(2.85<=jpFlip13.M()&&jpFlip13.M()<=3.35){onethree=1;}
            flip_m->Fill(jpFlip13.M());
        if(ohtwo+onethree==1){
          ++onematch;
        }
        else if(ohtwo+onethree==2){
          ++bothmatch;
        }
        ++checked4;
      }
      else if(Mu_charge[1]*Mu_charge[2] ==-1){
        TLorentzVector jpFlip12 = mu1+mu2;
        TLorentzVector jpFlip03 = mu0+mu3;
        if(2.85<=jpFlip12.M()&&jpFlip12.M()<=3.35){ohtwo=1;}
            flip_m->Fill(jpFlip12.M());
        if(2.85<=jpFlip03.M()&&jpFlip03.M()<=3.35){onethree=1;}
            flip_m->Fill(jpFlip03.M());
        if(ohtwo+onethree==1){
          ++onematch;
        }
        else if(ohtwo+onethree==2){
          ++bothmatch;
        }
        ++checked4;
      }
    }
    else{std::cout<<"PROBLEM, not 3 nor 4 matched"<<std::endl;break;}
    std::endl;
    std::cout<<MatchN<<std::endl;
  }
  flip_m->Draw();
  std::cout<<ouch<<" out of "<< checked <<"from a total of "<<chevent<<std::endl;
  std::cout<<onematch<<" single matches and "<< bothmatch<<" double. out of "<< checked4 <<" from a total of "<<chevent<<std::endl;
}

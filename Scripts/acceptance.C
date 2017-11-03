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
#include "Riostream.h"

int main() {
  gROOT->Reset();

  // info in new ttree
  Float_t mumass = 0.105658;

  Int_t nacce, iacc, nacc = 10000;
  //  Int_t nacce, iacc, nacc = 10000;

  // muon angular disribution (helicity angle)
  Double_t PI=3.14159265359;
  TRandom3 rndm(0); // initialize seed based on clock time

  //  TF1 *fCosTheta = new TF1("fCosTheta","1+[0]*x*x",-1,1); 
  //  fCosTheta->SetParameter(0, 0.0);
  TF1 *fCosTheta = new TF1("fCosTheta","1.48+[0]*x*x+[1]*x*x*x*x",-1,1); 
  fCosTheta->SetParameter(0, 0.0034);
  fCosTheta->SetParameter(1,-0.58);

  TF1 *fAngle = new TF1("fAngle","x",0,2.0*PI); 

  Double_t aaa;
  Double_t c1,c2;
  Double_t new_phi, new_theta;
  Double_t new_E, new_mom;
  TVector3 new_dir;

  Double_t eta[4], pt[4];

  // Read the data file
  // Format:
  // #evt Sweight px py pz m px py pz m

  ifstream infile;
  // data  infile.open("SelectedWeightInfo.txt");
  // DPS
  //  infile.open("dps/SelectedPsiGenInfoDPS.txt");
  infile.open("dps/dps-input.txt");

  // SPS
  //  infile.open("sps/SelectedPsiGenInfoSPS.txt");
  // SPS NLO
  //  infile.open("nlo/SelectedPsiGenInfoNLOCombined.txt");

  ofstream outfile;
  outfile.open("muons.txt");

  Int_t nevt;
  Double_t sweight,deltay;
  Double_t px1,py1,pz1,m1,e1,y1,pt1;
  Double_t px2,py2,pz2,m2,e2,y2,pt2;
  TLorentzVector j1data,j2data,system;
  TLorentzVector j1mu,j2mu;

  TLorentzVector System, JPsi1_lab, JPsi2_lab, JPsi1_syst, JPsi2_syst;
  TLorentzVector Mu1p_jpsi, Mu1m_jpsi, Mu2p_jpsi, Mu2m_jpsi; 
  TLorentzVector Mu1p_syst, Mu1m_syst, Mu2p_syst, Mu2m_syst;
  TLorentzVector Mu1p_lab, Mu1m_lab, Mu2p_lab, Mu2m_lab;
  TLorentzVector beam1_syst, beam2_syst, beam1_jpsi1, beam2_jpsi1, 
    beam1_jpsi2, beam2_jpsi2;


  // loop over data
  while(!infile.eof()){
    infile >> nevt >> sweight >> px1 >> py1 >> pz1 >> m1 
	   >> px2 >> py2 >> pz2 >> m2;
    
    // cout << "Loaded event " << endl;
    // cout << "nevt, sweight : " << nevt << "," << sweight << endl;
    // cout << "px,py,pz 1    : " << px1 << "," << py1 << "," << pz1 << endl;
    // cout << "px,py,pz 2    : " << px2 << "," << py2 << "," << pz2 << endl;
    // cout << "m1, m2        : " << m1 << "," << m2 << endl;
    
    // set the jpsi momenta in lab
    
    j1data.SetXYZM(px1,py1,pz1,m1);
    j2data.SetXYZM(px2,py2,pz2,m2);
    
    e1 = j1data.E();
    e2 = j2data.E();

    y1 = j1data.Rapidity();
    y2 = j2data.Rapidity();
    deltay=abs(y2-y1);

    pt1 = j1data.Pt();
    pt2 = j2data.Pt();
    
    // boostvectors for muons
    TVector3 BoostToLabFromPsi1 = (j1data.BoostVector());
    TVector3 BoostToLabFromPsi2 = (j2data.BoostVector());
    
    // calculate the combined system
    // add 4 momenta
    system = j1data + j2data;
    //  cout << m1 << " , " << m2 << " , " << sweight << " , " 
    //      << system.M() << " , " << system.Rapidity() << endl; 
    
    //loop
    iacc = 0;
    nacce = 0;
    while(++iacc < nacc){
      
      //---------------------------------------------  
      // decay the J/psi into muons in J/psi cm frame
      
      // determine muon relative momentum in psi frame based on psi mass
      new_E = 0.5*m1;
      new_phi = fAngle->GetRandom();
      //     new_theta = fAngle->GetRandom();
      c1 = fCosTheta->GetRandom();
      new_theta = acos(c1);
      
      new_mom = sqrt( pow(new_E, 2) - pow(mumass, 2) );
      new_dir.SetMagThetaPhi( new_mom, new_theta, new_phi );
      Mu1p_jpsi.SetPxPyPzE( new_dir.Px(), new_dir.Py(), new_dir.Pz(), new_E );
      Mu1m_jpsi.SetPxPyPzE( -1.0*new_dir.Px(), -1.0*new_dir.Py(), -1.0*new_dir.Pz(), new_E );
      
      new_E = 0.5*m2;
      new_phi = fAngle->GetRandom();
      //    new_theta = fAngle->GetRandom();
      
      c2 = fCosTheta->GetRandom();
      new_theta = acos(c2);
      
      new_mom = sqrt( pow(new_E, 2) - pow(mumass, 2) );
      new_dir.SetMagThetaPhi( new_mom, new_theta, new_phi );
      Mu2p_jpsi.SetPxPyPzE( new_dir.Px(), new_dir.Py(), new_dir.Pz(), new_E );
      Mu2m_jpsi.SetPxPyPzE( -1.0*new_dir.Px(), -1.0*new_dir.Py(), -1.0*new_dir.Pz(), new_E );
      
      // decay angle is measured with respect to J/psi flight in the 
      // double J/psi system
      // - find J/psi direction by boosting them into JJ frame 
      // - decay J into back to back muons with direction via cos-theta
      // - boost muons along J/psi in JJ frame
      
      Mu1p_lab=Mu1p_jpsi; Mu1m_lab=Mu1m_jpsi;
      Mu1p_lab.Boost(BoostToLabFromPsi1);
      Mu1m_lab.Boost(BoostToLabFromPsi1);
      
      // boost muons to lab frame from Psi2
      Mu2p_lab=Mu2p_jpsi; Mu2m_lab=Mu2m_jpsi;
      Mu2p_lab.Boost(BoostToLabFromPsi2);
      Mu2m_lab.Boost(BoostToLabFromPsi2);
      
      
      //------------------------------------------------------------
      // implement the muon acceptance cuts
      
      // step through muons
      pt[0] = Mu1p_lab.Pt();
      eta[0] = abs(Mu1p_lab.PseudoRapidity());
      
      pt[1] = Mu1m_lab.Pt();
      eta[1] = abs(Mu1m_lab.PseudoRapidity());
      
      pt[2] = Mu2p_lab.Pt();
      eta[2] = abs(Mu2p_lab.PseudoRapidity());
      
      pt[3] = Mu2m_lab.Pt();
      eta[3] = abs(Mu2m_lab.PseudoRapidity());


      // revisit the muon selection criteria !!!
      // make distributions in data and from simulation
      // check the cutoffs produce the same subsample
      // apply the cutoffs to the original sample -> feed in here!
      
      int nmu3=0;
      int nmu4=0;
      // loop over muons
      for(int im=0; im < 4; im++){
	
	if(eta[im] <= 1.2){
	  if( pt[im] > 3.5 ) nmu3++;
	}
	
	if( 1.2 < eta[im] && eta[im] < 1.6 ){
	  if( pt[im] > -3.75*eta[im]+8. ) nmu3++;
	  else if( pt[im] > -6.*eta[im]+10. ) nmu4++;
	}
	
	if( 1.6 <= eta[im] && eta[im] <= 2.4 ){
	  if(pt[im] > 2.) nmu3++;
	  else if(pt[im] > 1.1) nmu4++; 
	} 


	// revisit the cutoff !

	//	cout << im << " : " << eta[im] << " , " << pt[im] <<  " : " << nmu3 << "," << nmu4 << endl;
	
	
      } // endfor
      
      
      //     cout << nmu3 << " , " << nmu4 << endl;

      if(nmu3 == 4 || (nmu3 == 3 && nmu4 == 1)) nacce++;
      
      
      //------------------------------------------------------------
      // write muon momenta to file

      /*      
      outfile << Mu1p_lab.Px() << "    " <<  Mu1p_lab.Py() << "    " <<  Mu1p_lab.Pz() << "    "
	      << Mu1m_lab.Px() << "    " <<  Mu1m_lab.Py() << "    " <<  Mu1m_lab.Pz() << "    "
	      << Mu2p_lab.Px() << "    " <<  Mu2p_lab.Py() << "    " <<  Mu2p_lab.Pz() << "    "
	      << Mu2m_lab.Px() << "    " <<  Mu2m_lab.Py() << "    " <<  Mu2m_lab.Pz() 
	      << endl;
      */
      

    } // endloop per event
    
    // calculate acceptance for this event
    
    aaa = double(nacce)/double(nacc);

    cout << nevt << " , " << sweight << " , " << aaa << " , "
	 << m1 << " , " << m2 << " , " 
	 << system.Pt() << " , " << system.M() << " , " 
	 << system.Rapidity() << " , " 
	 << y1 << " , " << y2 << " , " 
	 << pt1 << " , " << pt2 << endl;
      

    //    if(nevt == 300) break;
    //    if(nevt == 1416) break;
    //    if(nevt == 4726) break;
  }
  outfile.close();
  
  infile.close();
  
  //  cout << "Done ! " << endl;
} // end macro

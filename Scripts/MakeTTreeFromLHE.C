#include "Riostream.h"
#include "TLorentzVector.h"
void MakeTTreeFromLHE() {
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("MakeTTreeFromLHE.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%slhedata_helac.txt",dir.Data()));

   Float_t iid1,ipx1, ipy1, ipz1,ie1,im1,iid2, ipx2,ipy2,ipz2,ie2,im2;
   Int_t nfd;
   Float_t FourMu_Mass,FourMu_pT,Psi1To2_dY,FourMu_Rapidity, FourMu_RapidityAbs;
   float Psi_Mass[2], Psi_pT[2], Psi_y[2];
   Int_t nlines = 0, Feeddown;
   TFile *f = new TFile("LHE_Ttree_helac.root","RECREATE");
   TTree *t = new TTree("Events","Events");

   t->Branch("FourMu_Mass", &FourMu_Mass, "FourMu_Mass/F");
   t->Branch("FourMu_pT", &FourMu_pT, "FourMu_pT/F");
   t->Branch("FourMu_Rapidity", &FourMu_Rapidity, "FourMu_Rapidity/F");
   t->Branch("Psi1To2_dY", &Psi1To2_dY, "Psi1To2_dY/F");
   t->Branch("Psi_Mass", Psi_Mass, "Psi_Mass[2]/F");
   t->Branch("Psi_pT", Psi_pT, "Psi_pT[2]/F");
   t->Branch("Psi_y", Psi_y, "Psi_y[2]/F");
   t->Branch("FourMu_RapidityAbs", &FourMu_RapidityAbs, "FourMu_RapidityAbs/F");
   t->Branch("Feeddown", &Feeddown, "Feeddown/I");
   while (1) {
    in>>iid1>>ipx1>>ipy1>>ipz1>>ie1>>im1>>iid2>>ipx2>>ipy2>>ipz2>>ie2>>im2>>nfd;
      if (!in.good()) break;
      if (nfd > 5) {std::cout<<nlines<<std::endl;break;}
      if (nlines <5) printf("px=%8f, FeedDown=%1i\n",ipx1,nfd);
      nlines++;
      TLorentzVector p1;
      TLorentzVector p2;
      p1.SetPx(ipx1);
      p1.SetPy(ipy1);
      p1.SetPz(ipz1);
      p1.SetE(ie1);
      p2.SetPx(ipx2);
      p2.SetPy(ipy2);
      p2.SetPz(ipz2);
      p2.SetE(ie2);
      TLorentzVector m4 = p1+p2;
      FourMu_Mass = m4.M();
      FourMu_pT = m4.Pt();
      FourMu_Rapidity = m4.Rapidity();
      FourMu_RapidityAbs = abs(m4.Rapidity());
      Psi1To2_dY = abs(p1.Rapidity()-p2.Rapidity());
      Feeddown = nfd;
      if (p1.Pt() >= p2.Pt()){
        Psi_Mass[0] = p1.M();
        Psi_Mass[1] = p2.M();
        Psi_pT[0] = p1.Pt();
        Psi_pT[1] = p2.Pt();
        Psi_y[0] = p1.Rapidity();
        Psi_y[1] = p2.Rapidity();
      }
      else{
        Psi_Mass[0] = p2.M();
        Psi_Mass[1] = p1.M();
        Psi_pT[0] = p2.Pt();
        Psi_pT[1] = p1.Pt();
        Psi_y[0] = p2.Rapidity();
        Psi_y[1] = p1.Rapidity();
      }

      //if(Feeddown > 4){std::cout<<"blergh"<<std::endl;}
    t->Fill();
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

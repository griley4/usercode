#include "Riostream.h"
void MakeTTreeFromWeights() {
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("MakeTTreeFromWeights.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%sSelected_newAcc.txt",dir.Data()));

   Float_t run,event,FourMu_Mass,FourMu_pT,Psi1To2_dY,FourMu_Rapidity,Weight,Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy, Psi1To2Significance,FourMu_RapidityAbs;
   Int_t nlines = 0;
   TFile *f = new TFile("TMTight_Selected_newAcc.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","Psi1_Mass:Psi2_Mass:Psi1_CTxy:Psi2_CTxy:Psi1To2Significance:Psi1To2_dY:FourMu_Mass:FourMu_pT:FourMu_Rapidity:FourMu_RapidityAbs");

   while (1) {
    in>>Psi1_Mass>>Psi2_Mass>>Psi1_CTxy>>Psi2_CTxy>>Psi1To2Significance>>Psi1To2_dY>>FourMu_Mass>>FourMu_pT>>FourMu_Rapidity>>FourMu_RapidityAbs;
      if (!in.good()) break;
      if (nlines < 5) printf("Mass=%8f, weight=%8f\n",FourMu_Mass,Weight);
      ntuple->Fill(Psi1_Mass, Psi2_Mass, Psi1_CTxy, Psi2_CTxy, Psi1To2Significance,Psi1To2_dY, FourMu_Mass, FourMu_pT, FourMu_Rapidity,FourMu_RapidityAbs);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

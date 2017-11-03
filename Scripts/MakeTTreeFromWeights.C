#include "Riostream.h"
void MakeTTreeFromWeights() {
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("MakeTTreeFromWeights.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%sDPSweights_syst_fixnlo_floatdps.txt",dir.Data()));

   Float_t FourMu_Mass,FourMu_pT,Psi1To2_dY,Psi1_Mass,Psi2_Mass,FourMu_RapidityAbs,Weight;
   Int_t nlines = 0;
   TFile *f = new TFile("DPS_Weights_ptGT8_data_fixNLOfloatDPS.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","Psi1_Mass:Psi2_Mass:Psi1To2_dY:FourMu_Mass:FourMu_pT:FourMu_RapidityAbs:Weight");

   while (1) {
    in>>FourMu_Mass>>FourMu_pT>>Psi1To2_dY>>Psi1_Mass>>Psi2_Mass>>FourMu_RapidityAbs>>Weight;
      if (!in.good()) break;
      if (nlines < 5) printf("Mass=%8f, weight=%8f\n",FourMu_Mass,Weight);
      ntuple->Fill(Psi1_Mass, Psi2_Mass,Psi1To2_dY, FourMu_Mass, FourMu_pT, FourMu_RapidityAbs, Weight);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

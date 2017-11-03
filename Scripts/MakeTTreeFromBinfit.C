#include "Riostream.h"
void MakeTTreeFromBinfit() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("MakeTTreeFromBinfit.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%sBinfit_results_reco_ptGT8.txt",dir.Data()));

   Float_t fracd,fracs, fracn, chi;
   Int_t nlines;
   string result;
   TFile *f = new TFile("Binfit_results_spsdpsnlo_ptYdy_reco8gev.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","fracd:fracs:fracn:chi");

   while (1) {
      in >> fracd >> fracs >> fracn >> chi;
      if (!in.good()) break;
      if (nlines < 5) printf("fracd=%8f, chi=%8f \n",fracd,chi);
      ntuple->Fill(fracd,fracs,fracn,chi);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

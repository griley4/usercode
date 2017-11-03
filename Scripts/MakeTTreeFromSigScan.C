#include "Riostream.h"
void MakeTTreeFromSigScan() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("MakeTTreeFromSigScan.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%sSigScan_grep.txt",dir.Data()));

   Float_t nll, sig, mean, width, widtherr, res;
   Int_t nlines;
   string result;
   TFile *f = new TFile("FullRangeMassVoigfit_resolutionFunc_newAcc.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","nll:sig:mean:width:widtherr:res");

   while (1) {
      in >> nll>>sig>>mean>>width>>widtherr>>res>>result;
      if (!in.good()) break;
      if (nlines < 5) printf("sig=%8f, mean=%8f \n",sig,mean);
      ntuple->Fill(nll,sig, mean, width, widtherr, res);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

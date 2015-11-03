// ----------------------------------------------------------------------
// // FourMuonAnalysis
// // ---------
// // Summary: This version looks for 3 muons via HLT paths Dimuon0_Jpsi_Muon || Dimuon0_Upsilon_Muon and adds some extra muon quality information over the last version
// //
// // ----------------------------------------------------------------------
// // Send all questions, wishes and complaints to the 
// //
// // Author:  Grant Riley: University of Tennessee
// // ----------------------------------------------------------------------
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>
#include "TLorentzVector.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h"

edmEventTree::edmEventTree(edm::ParameterSet const& iConfig):
  fRootFileName(iConfig.getUntrackedParameter<string>("rootFileName", string("PATEventTree.root"))),
  fMuonCollectionLabel(iConfig.getUntrackedParameter<InputTag>("MuonCollectionLabel", edm::InputTag("patMuonsWithTrigger"))),
  fgoodMuonInputLabel(iConfig.getUntrackedParameter<InputTag>("goodMuonInputLabel", edm::InputTag("goodMuons"))),
  fJPsiCandLabel(iConfig.getUntrackedParameter<InputTag>("DiMuCandLabel", edm::InputTag("DiMuCand"))),
  fUpsilonCandLabel(iConfig.getUntrackedParameter<InputTag>("UpsCandLabel", edm::InputTag("UpsCand"))),
  fFourMuonCandLabel(iConfig.getUntrackedParameter<InputTag>("FourMuCandLabel", edm::InputTag("FourMuCand")))
{
  cout << "----------------------------------------------------------------------" << endl;
}
//-----------------------------------------
edmEventTree::~edmEventTree() {}
//----------------------------------------
void edmEventTree::endJob() {

  fFile->cd();
  fFile->Write();
  fFile->Close();
  delete fFile;

  cout << "==>edmEventTree> Succesfully ended job" << endl;

}
//------------------------------------------
void PATEventTree::beginJob() {

  fFile = TFile::Open(fRootFileName.c_str(), "RECREATE");
  fFile->cd();

  nevt = 0;

  fTree = new TTree("edmEventTree", "edmEventTree");

  fTree->Branch("run",          &fRun,          "run/i");
  fTree->Branch("lumiblock",    &fLumiBlock,    "lumiblock/i");
  fTree->Branch("event",        &fEvent,        "event/i");
  fTree->Branch("bx",           &fBX,           "bx/I");
  fTree->Branch("orbit",        &fOrbit,        "orbit/I");
  fTree->Branch("HLTP_Dimuon0_Jpsi_Muon", fHLTP_Dimuon0_Jpsi_Muon, "HLTP_Dimuon0_Jpsi_Muon[3]/O");
  fTree->Branch("HLTP_Dimuon0_Upsilon_Muon", fHLTP_Dimuon0_Upsilon_Muon, "HLTP_Dimuon0_Upsilon_Muon[3]/O");
  fTree->Branch("HLTP_TripleMu5",         fHLTP_TripleMu5,       "HLTP_TripleMu5[3]/O");
  fTree->Branch("MuN",          &fMuN,          "MuN/I");
  fTree->Branch("MuIndex",      fMuIndex,       "MuIndex[MuN]/I");
  fTree->Branch("MiscTkIndex",  fMiscTkIndex,   "MiscTkIndex[MiscTkN]/I");
  fTree->Branch("PcToTk",       fPcToTk,        "PcToTk[PcN]/I");
  fTree->Branch("TkToPc",       fTkToPc,        "TkToPc[TkN]/I");
  fTree->Branch("PcToPv",       fPcToPv,        "PcToPv[PcN]/I");
  fTree->Branch("PcToSsv",      fPcToSsv,       "PcToSsv[PcN]/I");
  fTree->Branch("PcToGtv",      fPcToGtv,       "PcToGtv[PcN]/I");
  fTree->Branch("PcTkQuality",  fPcTkQuality,   "PcTkQuality[PcN]/I");
  fTree->Branch("PcJtN",        fPcJtN,         "PcJtN[PcN]/I");
  fTree->Branch("PcPdgId",      fPcPdgId,       "PcPdgId[PcN]/I");
  fTree->Branch("PcPixHitN",    fPcPixHitN,     "PcPixHitN[PcN]/I");
  fTree->Branch("PcPixLayN",    fPcPixLayN,     "PcPixLayN[PcN]/I");
  fTree->Branch("PcStripHitN",  fPcStripHitN,   "PcStripHitN[PcN]/I");
  fTree->Branch("PcStripLayN",  fPcStripLayN,   "PcStripLayN[PcN]/I");
  fTree->Branch("PcCharge",     fPcCharge,      "PcCharge[PcN]/F");
  fTree->Branch("PcChi2",       fPcChi2,        "PcChi2[PcN]/F");
  fTree->Branch("PcNdof",       fPcNdof,        "PcNdof[PcN]/F");
  fTree->Branch("PcEnergy",     fPcEnergy,      "PcEnergy[PcN]/F");
  fTree->Branch("PcEt",         fPcEt,          "PcEt[PcN]/F");
  fTree->Branch("PcP",          fPcP,           "PcP[PcN]/F");
  fTree->Branch("PcPt",         fPcPt,          "PcPt[PcN]/F");
  fTree->Branch("PcPx",         fPcPx,          "PcPx[PcN]/F");
  fTree->Branch("PcPy",         fPcPy,          "PcPy[PcN]/F");
  fTree->Branch("PcPz",         fPcPz,          "PcPz[PcN]/F");
  fTree->Branch("PcTheta",      fPcTheta,       "PcTheta[PcN]/F");
  fTree->Branch("PcEta",        fPcEta,         "PcEta[PcN]/F");
  fTree->Branch("PcPhi",        fPcPhi,         "PcPhi[PcN]/F");
  fTree->Branch("PcD0",         fPcD0,          "PcD0[PcN]/F");
  fTree->Branch("PcDz",         fPcDz,          "PcDz[PcN]/F");
  fTree->Branch("PcEtaErr",     fPcEtaErr,      "PcEtaErr[PcN]/F");
  fTree->Branch("PcPhiErr",     fPcPhiErr,      "PcPhiErr[PcN]/F");
  fTree->Branch("PcD0Err",      fPcD0Err,       "PcD0Err[PcN]/F");
  fTree->Branch("PcDzErr",      fPcDzErr,       "PcDzErr[PcN]/F");
  fTree->Branch("PcVx",         fPcVx,          "PcVx[PcN]/F");
  fTree->Branch("PcVy",         fPcVy,          "PcVy[PcN]/F");
  fTree->Branch("PcVz",         fPcVz,          "PcVz[PcN]/F");
  fTree->Branch("PcEcalIso",    fPcEcalIso,     "PcEcalIso[PcN]/F");
  fTree->Branch("PcHcalIso",    fPcHcalIso,     "PcHcalIso[PcN]/F");
  fTree->Branch("PcTrackIso",   fPcTrackIso,    "PcTrackIso[PcN]/F");
  fTree->Branch("PcIP",         fPcIP,          "PcIP[PcN]/F");
  fTree->Branch("PcIPxy",       fPcIPxy,        "PcIPxy[PcN]/F");
  fTree->Branch("MuHitN",       fMuHitN,        "MuHitN[MuN]/I");
//  fTree->Branch("MuChambers",	&fMuChambers,	"MuChambers[MuN]/I");
  fTree->Branch("MuMatchedN",   fMuMatchedN,    "MuMatchedN[MuN]/I");
  fTree->Branch("MuMatchedNSegArb",   fMuMatchedNSegArb,    "MuMatchedNSegArb[MuN]/I");
  fTree->Branch("MuMatchedNSegTrkArb",   fMuMatchedNSegTrkArb,    "MuMatchedNSegTrkArb[MuN]/I");
  fTree->Branch("MuMatchedNSegTrkArbClean",   fMuMatchedNSegTrkArbClean,    "MuMatchedNSegTrkArbClean[MuN]/I");
  fTree->Branch("MuHLTN",       fMuHLTN,        "MuHLTN[MuN]/I");
  fTree->Branch("MuToHLT",      fMuToHLT,       "MuToHLT[MuN]/I");
  fTree->Branch("MuChi2",       fMuChi2,        "MuChi2[MuN]/F");
  fTree->Branch("MuNdof",       fMuNdof,        "MuNdof[MuN]/F");
  fTree->Branch("MuTkKink",     fMuTkKink,      "MuTkKink[MuN]/F");
  fTree->Branch("MuGlbKink",    fMuGlbKink,     "MuGlbKink[MuN]/F");
  fTree->Branch("MuGlbProb",    fMuGlbProb,     "MuGlbProb[MuN]/F");
  fTree->Branch("MuTkSADist",   fMuTkSADist,    "MuTkSADist[MuN]/F");
  fTree->Branch("MuTkSAdR",     fMuTkSAdR,      "MuTkSAdR[MuN]/F");
  fTree->Branch("MuECALEnergy", fMuECALEnergy,  "MuECALEnergy[MuN]/F");
  fTree->Branch("MuHCALEnergy", fMuHCALEnergy,  "MuHCALEnergy[MuN]/F");
  fTree->Branch("MuCalCompat",  fMuCalCompat,   "MuCalCompat[MuN]/F");
  fTree->Branch("MuIsGlobal",   fMuIsGlobal,    "MuIsGlobal[MuN]/O");
  fTree->Branch("MuIsTracker",  fMuIsTracker,   "MuIsTracker[MuN]/O");
  fTree->Branch("MuIsStandalone", fMuIsStandalone, "MuIsStandalone[MuN]/O");
  fTree->Branch("MuIsCalo",     fMuIsCalo,      "MuIsCalo[MuN]/O");
  fTree->Branch("MuArbitrated", fMuArbitrated,  "MuArbitrated[MuN]/O");
  fTree->Branch("MuLastStationLoose", fMuLastStationLoose, "MuLastStationLoose[MuN]/O");
  fTree->Branch("MuLastStationTight", fMuLastStationTight, "MuLastStationTight[MuN]/O");
  fTree->Branch("Mu2DCompatibilityLoose", fMu2DCompatibilityLoose, "Mu2DCompatibilityLoose[MuN]/O");
  fTree->Branch("Mu2DCompatibilityTight", fMu2DCompatibilityTight, "Mu2DCompatibilityTight[MuN]/O");
  fTree->Branch("MuOneStationLoose", fMuOneStationLoose, "MuOneStationLoose[MuN]/O");
  fTree->Branch("MuOneStationTight", fMuOneStationTight, "MuOneStationTight[MuN]/O");
  fTree->Branch("MuHLTMatch",   fMuHLTMatch,    "MuHLTMatch[MuN][2]/O");
  fTree->Branch("MuL3Match",    fMuL3Match,     "MuL3Match[MuN]/O");
  fTree->Branch("MuTightMatch", fMuTightMatch,  "MuTightMatch[MuN]/O");

  fTree->Branch("PcToJt",       fPcToJt,        "PcToJt[PcN][5]/I");

  fTree->Branch("PvN",          &fPvN,          "PvN/I");
  fTree->Branch("RePvN",        &fRePvN,        "RePvN/I");
  fTree->Branch("AllPvN",       &fAllPvN,       "AllPvN/I");
  fTree->Branch("PvIndex",      fPvIndex,       "PvIndex[AllPvN]/I");
  fTree->Branch("PvTkN",        fPvTkN,         "PvTkN[AllPvN]/I");
  fTree->Branch("PvClosestI",   fPvClosestI,    "PvClosestI[AllPvN]/I");
  fTree->Branch("PvX",          fPvX,           "PvX[AllPvN]/F");
  fTree->Branch("PvY",          fPvY,           "PvY[AllPvN]/F");
  fTree->Branch("PvZ",          fPvZ,           "PvZ[AllPvN]/F");
  fTree->Branch("PvXe",         fPvXe,          "PvXe[AllPvN]/F");
  fTree->Branch("PvYe",         fPvYe,          "PvYe[AllPvN]/F");
  fTree->Branch("PvZe",         fPvZe,          "PvZe[AllPvN]/F");
  fTree->Branch("PvPx",         fPvPx,          "PvPx[AllPvN]/F");
  fTree->Branch("PvPy",         fPvPy,          "PvPy[AllPvN]/F");
  fTree->Branch("PvPz",         fPvPz,          "PvPz[AllPvN]/F");
  fTree->Branch("PvPt",         fPvPt,          "PvPt[AllPvN]/F");
  fTree->Branch("PvP",          fPvP,           "PvP[AllPvN]/F");
  fTree->Branch("PvEnergy",     fPvEnergy,      "PvEnergy[AllPvN]/F");
  fTree->Branch("PvEta",        fPvEta,         "PvEta[AllPvN]/F");
  fTree->Branch("PvChi2",       fPvChi2,        "PvChi2[AllPvN]/F");
  fTree->Branch("PvNdof",       fPvNdof,        "PvNdof[AllPvN]/F");
  fTree->Branch("PvMass",       fPvMass,        "PvMass[AllPvN]/F");
  fTree->Branch("PvIsFake",     fPvIsFake,      "PvIsFake[AllPvN]/O");
  fTree->Branch("PvIsRefit",    fPvIsRefit,     "PvIsRefit[AllPvN]/O");

  fTree->Branch("JtN",          &fJtN,          "JtN/I");
  fTree->Branch("JtStandN",     &fJtStandN,     "JtStandN/I");
  fTree->Branch("JtTkN",        fJtTkN,         "JtTkN[JtN]/I");
  fTree->Branch("JtSsvN",       fJtSsvN,        "JtSsvN[JtN]/I");
  fTree->Branch("JtGtvN",       fJtGtvN,        "JtGtvN[JtN]/I");
  fTree->Branch("JtIndex",      fJtIndex,       "JtIndex[JtN]/I");
  fTree->Branch("JtStandIndex", fJtStandIndex,  "JtStandIndex[JtStandN]/I");
  fTree->Branch("JtToPv",       fJtToPv,        "JtToPv[JtN]/I");
  fTree->Branch("JtnConstituents", fJtnConstituents, "JtnConstituents[JtN]/I");
  fTree->Branch("Jtn60",        fJtn60,         "Jtn60[JtN]/I");
  fTree->Branch("Jtn90",        fJtn90,         "Jtn90[JtN]/I");
  fTree->Branch("JtnChargedParticles", fJtnChargedParticles, "JtnChargedParticles[JtN]/I");
  fTree->Branch("JtnNeutralParticles", fJtnNeutralParticles, "JtnNeutralParticles[JtN]/I");
  fTree->Branch("JtnChargedHadrons", fJtnChargedHadrons, "JtnChargedHadrons[JtN]/I");
  fTree->Branch("JtnNeutralHadrons", fJtnNeutralHadrons, "JtnNeutralHadrons[JtN]/I");
  fTree->Branch("JtnPhotons",   fJtnPhotons,    "JtnPhotons[JtN]/I");
  fTree->Branch("JtnElectrons", fJtnElectrons,  "JtnElectrons[JtN]/I");
  fTree->Branch("JtnMuons",     fJtnMuons,      "JtnMuons[JtN]/I");
  fTree->Branch("JtnHFHadrons", fJtnHFHadrons,  "JtnHFHadrons[JtN]/I");
  fTree->Branch("JtnHFEMParticles", fJtnHFEMParticles, "JtnHFEMParticles[JtN]/I");
  fTree->Branch("JtRankTCHE",   fJtRankTCHE,    "JtRankTCHE[JtN]/I");
  fTree->Branch("JtRankTCHP",   fJtRankTCHP,    "JtRankTCHP[JtN]/I");
  fTree->Branch("JtRankP",      fJtRankP,       "JtRankP[JtN]/I");
  fTree->Branch("JtRankBP",     fJtRankBP,      "JtRankBP[JtN]/I");
  fTree->Branch("JtRankSSVHE",  fJtRankSSVHE,   "JtRankSSVHE[JtN]/I");
  fTree->Branch("JtRankSSVHP",  fJtRankSSVHP,   "JtRankSSVHP[JtN]/I");
  fTree->Branch("JtRankCSV",    fJtRankCSV,     "JtRankCSV[JtN]/I");
  fTree->Branch("JtRankCSVMVA", fJtRankCSVMVA,  "JtRankCSVMVA[JtN]/I");
  fTree->Branch("JtRankGT",     fJtRankGT,      "JtRankGT[JtN]/I");
  fTree->Branch("JtRankSE",     fJtRankSE,      "JtRankSE[JtN]/I");
  fTree->Branch("JtRankSM",     fJtRankSM,      "JtRankSM[JtN]/I");
  fTree->Branch("JtCharge",     fJtCharge,      "JtCharge[JtN]/F");
  fTree->Branch("JtDiscTCHE",   fJtDiscTCHE,    "JtDiscTCHE[JtN]/F");
  fTree->Branch("JtDiscTCHP",   fJtDiscTCHP,    "JtDiscTCHP[JtN]/F");
  fTree->Branch("JtDiscP",      fJtDiscP,       "JtDiscP[JtN]/F");
  fTree->Branch("JtDiscBP",     fJtDiscBP,      "JtDiscBP[JtN]/F");
  fTree->Branch("JtDiscSSVHE",  fJtDiscSSVHE,   "JtDiscSSVHE[JtN]/F");
  fTree->Branch("JtDiscSSVHP",  fJtDiscSSVHP,   "JtDiscSSVHP[JtN]/F");
  fTree->Branch("JtDiscCSV",    fJtDiscCSV,     "JtDiscCSV[JtN]/F");
  fTree->Branch("JtDiscCSVMVA", fJtDiscCSVMVA,  "JtDiscCSVMVA[JtN]/F");
  fTree->Branch("JtDiscGT",     fJtDiscGT,      "JtDiscGT[JtN]/F");
  fTree->Branch("JtDiscSE",     fJtDiscSE,      "JtDiscSE[JtN]/F");
  fTree->Branch("JtDiscSM",     fJtDiscSM,      "JtDiscSM[JtN]/F");
  fTree->Branch("JtMaxDist",    fJtMaxDist,     "JtMaxDist[JtN]/F");
  fTree->Branch("JtPhi",        fJtPhi,         "JtPhi[JtN]/F");
  fTree->Branch("JtTheta",      fJtTheta,       "JtTheta[JtN]/F");
  fTree->Branch("JtEta",        fJtEta,         "JtEta[JtN]/F");
  fTree->Branch("JtRapidity",   fJtRapidity,    "JtRapidity[JtN]/F");
  fTree->Branch("JtP",          fJtP,           "JtP[JtN]/F");
  fTree->Branch("JtPt",         fJtPt,          "JtPt[JtN]/F");
  fTree->Branch("JtPx",         fJtPx,          "JtPx[JtN]/F");
  fTree->Branch("JtPy",         fJtPy,          "JtPy[JtN]/F");
  fTree->Branch("JtPz",         fJtPz,          "JtPz[JtN]/F");
  fTree->Branch("JtEnergy",     fJtEnergy,      "JtEnergy[JtN]/F");
  fTree->Branch("JtEt",         fJtEt,          "JtEt[JtN]/F");
  fTree->Branch("JtMass",       fJtMass,        "JtMass[JtN]/F");
  fTree->Branch("JtMt",         fJtMt,          "JtMt[JtN]/F");
  fTree->Branch("JtVx",         fJtVx,          "JtVx[JtN]/F");
  fTree->Branch("JtVy",         fJtVy,          "JtVy[JtN]/F");
  fTree->Branch("JtVz",         fJtVz,          "JtVz[JtN]/F");
  fTree->Branch("JtChargedEmEnergy", fJtChargedEmEnergy, "JtChargedEmEnergy[JtN]/F");
  fTree->Branch("JtNeutralEmEnergy", fJtNeutralEmEnergy, "JtNeutralEmEnergy[JtN]/F");
  fTree->Branch("JtChargedHadronEnergy", fJtChargedHadronEnergy, "JtChargedHadronEnergy[JtN]/F");
  fTree->Branch("JtNeutralHadronEnergy", fJtNeutralHadronEnergy, "JtNeutralHadronEnergy[JtN]/F");
  fTree->Branch("JtPhotonEnergy", fJtPhotonEnergy, "JtPhotonEnergy[JtN]/F");
  fTree->Branch("JtElectronEnergy", fJtElectronEnergy, "JtElectronEnergy[JtN]/F");
  fTree->Branch("JtMuonEnergy", fJtMuonEnergy,  "JtMuonEnergy[JtN]/F");
  fTree->Branch("JtHFHadronEnergy", fJtHFHadronEnergy, "JtHFHadronEnergy[JtN]/F");
  fTree->Branch("JtHFEMEnergy", fJtHFEMEnergy,  "JtHFEMEnergy[JtN]/F");
  fTree->Branch("JtdRMean",     fJtdRMean,      "JtdRMean[JtN]/F");
  fTree->Branch("JtdRMax",      fJtdRMax,       "JtdRMax[JtN]/F");
  fTree->Branch("JtPtRelMean",  fJtPtRelMean,   "JtPtRelMean[JtN]/F");
  fTree->Branch("JtPtRelMax",   fJtPtRelMax,    "JtPtRelMax[JtN]/F");
  fTree->Branch("JtPtRelSum",   fJtPtRelSum,    "JtPtRelSum[JtN]/F");
  fTree->Branch("JtPullPx",     fJtPullPx,      "JtPullPx[JtN]/F");
  fTree->Branch("JtPullPy",     fJtPullPy,      "JtPullPy[JtN]/F");
  fTree->Branch("JtPullPz",     fJtPullPz,      "JtPullPz[JtN]/F");
  fTree->Branch("JtIsStandard", fJtIsStandard,  "JtIsStandard[JtN]/O");
  fTree->Branch("JtIsFat",      fJtIsFat,       "JtIsFat[JtN]/O");
  fTree->Branch("JtIsSub",      fJtIsSub,       "JtIsSub[JtN]/O");
  fTree->Branch("JtIsFilt",     fJtIsFilt,      "JtIsFilt[JtN]/O");
  fTree->Branch("JtHLTMatch",   fJtHLTMatch,    "JtHLTMatch[JtN][2]/O");
  fTree->Branch("JtVeto",       fJtVeto,        "JtVeto[JtN]/O");

  fTree->Branch("JtHLTN",       fJtHLTN,        "JtHLTN[JtN]/I");
  fTree->Branch("JtToHLT",      fJtToHLT,       "JtToHLT[JtN]/I");
  fTree->Branch("JtToPc",       fJtToPc,        "JtToPc[JtN][20]/I");
  fTree->Branch("JtToSsv",      fJtToSsv,       "JtToSsv[JtN][2]/I");
  fTree->Branch("JtToGtv",      fJtToGtv,       "JtToGtv[JtN][4]/I");

  if (fUseFatJets) {
    fTree->Branch("JtFatN",       &fJtFatN,       "JtFatN/I");
    fTree->Branch("JtFatIndex",   fJtFatIndex,    "JtFatIndex[JtFatN]/I");
    fTree->Branch("JtSubN",       &fJtSubN,       "JtSubN/I");
    fTree->Branch("JtSubIndex",   fJtSubIndex,    "JtSubIndex[JtSubN]/I");
    fTree->Branch("JtFiltN",      &fJtFiltN,      "JtFiltN/I");
    fTree->Branch("JtFiltIndex",  fJtFiltIndex,   "JtFiltIndex[JtFiltN]/I");
    fTree->Branch("FatSubN",      fFatSubN,       "FatSubN[JtFatN]/I");
    fTree->Branch("FatFiltN",     fFatFiltN,      "FatFiltN[JtFatN]/I");
    fTree->Branch("SubToFat",     fSubToFat,      "SubToFat[JtSubN]/I");
    fTree->Branch("FiltToFat",    fFiltToFat,     "FiltToFat[JtFiltN]/I");
  }

  fTree->Branch("SvN",          &fSvN,          "SvN/I");
  fTree->Branch("SsvN",         &fSsvN,         "SsvN/I");
  fTree->Branch("GtvN",         &fGtvN,         "GtvN/I");
  fTree->Branch("SvIndex",      fSvIndex,       "SvIndex[SvN]/I");
  fTree->Branch("SvTkN",        fSvTkN,         "SvTkN[SvN]/I");
  fTree->Branch("SvToJt",       fSvToJt,        "SvToJt[SvN]/I");
  fTree->Branch("SvSeqInJt",    fSvSeqInJt,     "SvSeqInJt[SvN]/I");
  fTree->Branch("SvX",          fSvX,           "SvX[SvN]/F");
  fTree->Branch("SvY",          fSvY,           "SvY[SvN]/F");
  fTree->Branch("SvZ",          fSvZ,           "SvZ[SvN]/F");
  fTree->Branch("SvXe",         fSvXe,          "SvXe[SvN]/F");
  fTree->Branch("SvYe",         fSvYe,          "SvYe[SvN]/F");
  fTree->Branch("SvZe",         fSvZe,          "SvZe[SvN]/F");
  fTree->Branch("SvPx",         fSvPx,          "SvPx[SvN]/F");
  fTree->Branch("SvPy",         fSvPy,          "SvPy[SvN]/F");
  fTree->Branch("SvPz",         fSvPz,          "SvPz[SvN]/F");
  fTree->Branch("SvPt",         fSvPt,          "SvPt[SvN]/F");
  fTree->Branch("SvEta",        fSvEta,         "SvEta[SvN]/F");
  fTree->Branch("SvChi2",       fSvChi2,        "SvChi2[SvN]/F");
  fTree->Branch("SvNdof",       fSvNdof,        "SvNdof[SvN]/F");
  fTree->Branch("SvDist",       fSvDist,        "SvDist[SvN]/F");
  fTree->Branch("SvDistCM",     fSvDistCM,      "SvDistCM[SvN]/F");
  fTree->Branch("SvMass",       fSvMass,        "SvMass[SvN]/F");
  fTree->Branch("SvTau",        fSvTau,         "SvTau[SvN]/F");
  fTree->Branch("SvTauCM",      fSvTauCM,       "SvTauCM[SvN]/F");
  fTree->Branch("SvIsGTV",      fSvIsGTV,       "SvIsGTV[SvN]/O");

  fTree->Branch("SvToPc",       fSvToPc,        "SvToPc[SvN][20]/I");

  fTree->Branch("METN",         &fMETN,         "METN/I");
  fTree->Branch("METIndex",     fMETIndex,      "METIndex[METN]/I");
  fTree->Branch("METCharge",    fMETCharge,     "METCharge[METN]/F");
  fTree->Branch("METPhi",       fMETPhi,        "METPhi[METN]/F");
  fTree->Branch("METTheta",     fMETTheta,      "METTheta[METN]/F");
  fTree->Branch("METEta",       fMETEta,        "METEta[METN]/F");
  fTree->Branch("METRapidity",  fMETRapidity,   "METRapidity[METN]/F");
  fTree->Branch("METP",         fMETP,          "METP[METN]/F");
  fTree->Branch("METPt",        fMETPt,         "METPt[METN]/F");
  fTree->Branch("METPx",        fMETPx,         "METPx[METN]/F");
  fTree->Branch("METPy",        fMETPy,         "METPy[METN]/F");
  fTree->Branch("METPz",        fMETPz,         "METPz[METN]/F");
  fTree->Branch("METEnergy",    fMETEnergy,     "METEnergy[METN]/F");
  fTree->Branch("METEt",        fMETEt,         "METEt[METN]/F");
  fTree->Branch("METMass",      fMETMass,       "METMass[METN]/F");
  fTree->Branch("METMt",        fMETMt,         "METMt[METN]/F");
  fTree->Branch("METVx",        fMETVx,         "METVx[METN]/F");
  fTree->Branch("METVy",        fMETVy,         "METVy[METN]/F");
  fTree->Branch("METVz",        fMETVz,         "METVz[METN]/F");

  fTree->Branch("JPsiN",           &fJPsiN,           "JPsiN/I");
  fTree->Branch("JPsiMuMuN",       &fJPsiMuMuN,       "JPsiMuMuN/I");
  fTree->Branch("JPsiMuTkN",       &fJPsiMuTkN,       "JPsiMuTkN/I");
  fTree->Branch("BaseJPsiI",       fBaseJPsiI,        "BaseJPsiI[2]/I");
  fTree->Branch("JPsiIndex",       fJPsiIndex,        "JPsiIndex[JPsiN]/I");
  fTree->Branch("JPsiClosestPVinZ", fJPsiClosestPVinZ, "JPsiClosestPVinZ[JPsiN]/I");
  fTree->Branch("JPsiCharge",      fJPsiCharge,       "JPsiCharge[JPsiN]/F");
  fTree->Branch("JPsiPhi",         fJPsiPhi,          "JPsiPhi[JPsiN]/F");
  fTree->Branch("JPsiTheta",       fJPsiTheta,        "JPsiTheta[JPsiN]/F");
  fTree->Branch("JPsiEta",         fJPsiEta,          "JPsiEta[JPsiN]/F");
  fTree->Branch("JPsiRapidity",    fJPsiRapidity,     "JPsiRapidity[JPsiN]/F");
  fTree->Branch("JPsiP",           fJPsiP,            "JPsiP[JPsiN]/F");
  fTree->Branch("JPsiPt",          fJPsiPt,           "JPsiPt[JPsiN]/F");
  fTree->Branch("JPsiPx",          fJPsiPx,           "JPsiPx[JPsiN]/F");
  fTree->Branch("JPsiPy",          fJPsiPy,           "JPsiPy[JPsiN]/F");
  fTree->Branch("JPsiPz",          fJPsiPz,           "JPsiPz[JPsiN]/F");
  fTree->Branch("JPsiEnergy",      fJPsiEnergy,       "JPsiEnergy[JPsiN]/F");
  fTree->Branch("JPsiEt",          fJPsiEt,           "JPsiEt[JPsiN]/F");
  fTree->Branch("JPsiMass",        fJPsiMass,         "JPsiMass[JPsiN]/F");
  fTree->Branch("JPsiMt",          fJPsiMt,           "JPsiMt[JPsiN]/F");
  fTree->Branch("JPsiChi2",        fJPsiChi2,         "JPsiChi2[JPsiN]/F");
  fTree->Branch("JPsiNdof",        fJPsiNdof,         "JPsiNdof[JPsiN]/F");
  fTree->Branch("JPsiVx",          fJPsiVx,           "JPsiVx[JPsiN]/F");
  fTree->Branch("JPsiVy",          fJPsiVy,           "JPsiVy[JPsiN]/F");
  fTree->Branch("JPsiVz",          fJPsiVz,           "JPsiVz[JPsiN]/F");
  fTree->Branch("JPsiVxE",         fJPsiVxE,          "JPsiVxE[JPsiN]/F");
  fTree->Branch("JPsiVyE",         fJPsiVyE,          "JPsiVyE[JPsiN]/F");
  fTree->Branch("JPsiVzE",         fJPsiVzE,          "JPsiVzE[JPsiN]/F");
  fTree->Branch("JPsiVtxPhi",      fJPsiVtxPhi,       "JPsiVtxPhi[JPsiN]/F");
  fTree->Branch("JPsiVtxTheta",    fJPsiVtxTheta,     "JPsiVtxTheta[JPsiN]/F");
  fTree->Branch("JPsiVtxEta",      fJPsiVtxEta,       "JPsiVtxEta[JPsiN]/F");
  fTree->Branch("JPsiVtxRapidity", fJPsiVtxRapidity,  "JPsiVtxRapidity[JPsiN]/F");
  fTree->Branch("JPsiVtxP",        fJPsiVtxP,         "JPsiVtxP[JPsiN]/F");
  fTree->Branch("JPsiVtxPt",       fJPsiVtxPt,        "JPsiVtxPt[JPsiN]/F");
  fTree->Branch("JPsiVtxPx",       fJPsiVtxPx,        "JPsiVtxPx[JPsiN]/F");
  fTree->Branch("JPsiVtxPy",       fJPsiVtxPy,        "JPsiVtxPy[JPsiN]/F");
  fTree->Branch("JPsiVtxPz",       fJPsiVtxPz,        "JPsiVtxPz[JPsiN]/F");
  fTree->Branch("JPsiVtxEnergy",   fJPsiVtxEnergy,    "JPsiVtxEnergy[JPsiN]/F");
  fTree->Branch("JPsiVtxEt",       fJPsiVtxEt,        "JPsiVtxEt[JPsiN]/F");
  fTree->Branch("JPsiVtxMass",     fJPsiVtxMass,      "JPsiVtxMass[JPsiN]/F");
  fTree->Branch("JPsiVtxMt",       fJPsiVtxMt,        "JPsiVtxMt[JPsiN]/F");

  fTree->Branch("JPsiMuI",         fJPsiMuI,          "JPsiMuI[JPsiN][2]/I");
  fTree->Branch("JPsiMuCategory",  fJPsiMuCategory,   "JPsiMuCategory[JPsiN][2]/I");
  fTree->Branch("JPsiMuCutKin",    fJPsiMuCutKin,     "JPsiMuCutKin[JPsiN][2]/O");
  fTree->Branch("JPsiMuCutHLT",    fJPsiMuCutHLT,     "JPsiMuCutHLT[JPsiN][2]/O");
  fTree->Branch("JPsiMuCutIso",    fJPsiMuCutIso,     "JPsiMuCutIso[JPsiN][2]/O");
  fTree->Branch("JPsiMuCutSA",     fJPsiMuCutSA,      "JPsiMuCutSA[JPsiN][2]/O");
  fTree->Branch("JPsiMuCutTrk",    fJPsiMuCutTrk,     "JPsiMuCutTrk[JPsiN][2]/O");
  fTree->Branch("JPsiMuType",      fJPsiMuType,       "JPsiMuType[JPsiN][2][5]/O");

  fTree->Branch("EtabN",        &fEtabN,        "EtabN/I");
  fTree->Branch("EtabIndex",    fEtabIndex,     "EtabIndex[EtabN]/I");
  fTree->Branch("EtabDuplicatesI", fEtabDuplicatesI, "EtabDuplicatesI[EtabN]/I");
  fTree->Branch("EtabCharge",   fEtabCharge,    "EtabCharge[EtabN]/F");
  fTree->Branch("EtabPhi",      fEtabPhi,       "EtabPhi[EtabN]/F");
  fTree->Branch("EtabTheta",    fEtabTheta,     "EtabTheta[EtabN]/F");
  fTree->Branch("EtabEta",      fEtabEta,       "EtabEta[EtabN]/F");
  fTree->Branch("EtabRapidity", fEtabRapidity,  "EtabRapidity[EtabN]/F");
  fTree->Branch("EtabP",        fEtabP,         "EtabP[EtabN]/F");
  fTree->Branch("EtabPt",       fEtabPt,        "EtabPt[EtabN]/F");
  fTree->Branch("EtabPx",       fEtabPx,        "EtabPx[EtabN]/F");
  fTree->Branch("EtabPy",       fEtabPy,        "EtabPy[EtabN]/F");
  fTree->Branch("EtabPz",       fEtabPz,        "EtabPz[EtabN]/F");
  fTree->Branch("EtabEnergy",   fEtabEnergy,    "EtabEnergy[EtabN]/F");
  fTree->Branch("EtabEt",       fEtabEt,        "EtabEt[EtabN]/F");
  fTree->Branch("EtabMass",     fEtabMass,      "EtabMass[EtabN]/F");
  fTree->Branch("EtabMt",       fEtabMt,        "EtabMt[EtabN]/F");
  fTree->Branch("EtabChi2",     fEtabChi2,      "EtabChi2[EtabN]/F");
  fTree->Branch("EtabNdof",     fEtabNdof,      "EtabNdof[EtabN]/F");
  fTree->Branch("EtabVx",       fEtabVx,        "EtabVx[EtabN]/F");
  fTree->Branch("EtabVy",       fEtabVy,        "EtabVy[EtabN]/F");
  fTree->Branch("EtabVz",       fEtabVz,        "EtabVz[EtabN]/F");
  fTree->Branch("EtabVxE",      fEtabVxE,       "EtabVxE[EtabN]/F");
  fTree->Branch("EtabVyE",      fEtabVyE,       "EtabVyE[EtabN]/F");
  fTree->Branch("EtabVzE",      fEtabVzE,       "EtabVzE[EtabN]/F");
  fTree->Branch("EtabVtxPhi",   fEtabVtxPhi,    "EtabVtxPhi[EtabN]/F");
  fTree->Branch("EtabVtxTheta", fEtabVtxTheta,  "EtabVtxTheta[EtabN]/F");
  fTree->Branch("EtabVtxEta",   fEtabVtxEta,    "EtabVtxEta[EtabN]/F");
  fTree->Branch("EtabVtxRapidity",fEtabVtxRapidity,"EtabVtxRapidity[EtabN]/F");
  fTree->Branch("EtabVtxP",     fEtabVtxP,      "EtabVtxP[EtabN]/F");
  fTree->Branch("EtabVtxPt",    fEtabVtxPt,     "EtabVtxPt[EtabN]/F");
  fTree->Branch("EtabVtxPx",    fEtabVtxPx,     "EtabVtxPx[EtabN]/F");
  fTree->Branch("EtabVtxPy",    fEtabVtxPy,     "EtabVtxPy[EtabN]/F");
  fTree->Branch("EtabVtxPz",    fEtabVtxPz,     "EtabVtxPz[EtabN]/F");
  fTree->Branch("EtabVtxEnergy",fEtabVtxEnergy, "EtabVtxEnergy[EtabN]/F");
  fTree->Branch("EtabVtxEt",    fEtabVtxEt,     "EtabVtxEt[EtabN]/F");
  fTree->Branch("EtabVtxMass",  fEtabVtxMass,   "EtabVtxMass[EtabN]/F");
  fTree->Branch("EtabVtxMt",    fEtabVtxMt,     "EtabVtxMt[EtabN]/F");

  fTree->Branch("BaseEtabI",    &fBaseEtabI,    "BaseEtabI/I");
  fTree->Branch("EtabJPsiI",    fEtabJPsiI,     "EtabJPsiI[EtabN][2]/I");
  fTree->Branch("EtabMuI",      fEtabMuI,       "EtabMuI[EtabN][4]/I");
  fTree->Branch("EtabMuN",      fEtabMuN,       "EtabMuN[EtabN]/I");
  fTree->Branch("EtabToRePvI",  fEtabToRePvI,   "EtabToRePvI[EtabN]/I");
  fTree->Branch("EtabCT",       fEtabCT,        "EtabCT[EtabN]/F");
  fTree->Branch("EtabCTxy",     fEtabCTxy,      "EtabCTxy[EtabN]/F");
  fTree->Branch("EtabVtxCT",    fEtabVtxCT,     "EtabVtxCT[EtabN]/F");
  fTree->Branch("EtabVtxCTxy",  fEtabVtxCTxy,   "EtabVtxCTxy[EtabN]/F");
  fTree->Branch("EtabJPsiDeltaL",fEtabJPsiDeltaL,"EtabJPsiDeltaL[EtabN]/F");
  fTree->Branch("EtabJPsiDeltaT",fEtabJPsiDeltaT,"EtabJPsiDeltaT[EtabN]/F");
  fTree->Branch("EtabJPsiVtxErr",fEtabJPsiVtxErr,"EtabJPsiVtxErr[EtabN]/F");
  fTree->Branch("EtabJPsiVtxErrxy",fEtabJPsiVtxErrxy,"EtabJPsiVtxErrxy[EtabN]/F");
  fTree->Branch("EtabJPsiProjX",fEtabJPsiProjX, "EtabJPsiProjX[EtabN][2]/F");
  fTree->Branch("EtabJPsiProjY",fEtabJPsiProjY, "EtabJPsiProjY[EtabN][2]/F");
  fTree->Branch("EtabJPsiProjZ",fEtabJPsiProjZ, "EtabJPsiProjZ[EtabN][2]/F");
  fTree->Branch("EtabJPsiCT",   fEtabJPsiCT,    "EtabJPsiCT[EtabN][2]/F");
  fTree->Branch("EtabJPsiCTxy", fEtabJPsiCTxy,  "EtabJPsiCTxy[EtabN][2]/F");
  fTree->Branch("EtabJPsiVtxCT",fEtabJPsiVtxCT, "EtabJPsiVtxCT[EtabN][2]/F");
  fTree->Branch("EtabJPsiVtxCTxy",fEtabJPsiVtxCTxy,"EtabJPsiVtxCTxy[EtabN][2]/F");
  fTree->Branch("EtabJPsiToPVVtxErr",fEtabJPsiToPVVtxErr,"EtabJPsiToPVVtxErr[EtabN][2]/F");
  fTree->Branch("EtabJPsiToPVVtxErrxy",fEtabJPsiToPVVtxErrxy,"EtabJPsiToPVVtxErrxy[EtabN][2]/F");
  // isolation information
  fTree->Branch("EtabJPsiIsoTkN", fEtabJPsiIsoTkN, "EtabJPsiIsoTkN[EtabN][2]/I");
  fTree->Branch("EtabJPsiIso7PV", fEtabJPsiIso7PV, "EtabJPsiIso7PV[EtabN][2]/F");
  fTree->Branch("EtabJPsiIsoTkCA",fEtabJPsiIsoTkCA,"EtabJPsiIsoTkCA[EtabN][2]/F");

  fTree->Branch("HN",           &fHN,           "HN/I");
  fTree->Branch("HIndex",       fHIndex,        "HIndex[HN]/I");
  fTree->Branch("HCharge",      fHCharge,       "HCharge[HN]/F");
  fTree->Branch("HPhi",         fHPhi,          "HPhi[HN]/F");
  fTree->Branch("HTheta",       fHTheta,        "HTheta[HN]/F");
  fTree->Branch("HEta",         fHEta,          "HEta[HN]/F");
  fTree->Branch("HRapidity",    fHRapidity,     "HRapidity[HN]/F");
  fTree->Branch("HP",           fHP,            "HP[HN]/F");
  fTree->Branch("HPt",          fHPt,           "HPt[HN]/F");
  fTree->Branch("HPx",          fHPx,           "HPx[HN]/F");
  fTree->Branch("HPy",          fHPy,           "HPy[HN]/F");
  fTree->Branch("HPz",          fHPz,           "HPz[HN]/F");
  fTree->Branch("HEnergy",      fHEnergy,       "HEnergy[HN]/F");
  fTree->Branch("HEt",          fHEt,           "HEt[HN]/F");
  fTree->Branch("HMass",        fHMass,         "HMass[HN]/F");
  fTree->Branch("HMt",          fHMt,           "HMt[HN]/F");
  fTree->Branch("HVx",          fHVx,           "HVx[HN]/F");
  fTree->Branch("HVy",          fHVy,           "HVy[HN]/F");
  fTree->Branch("HVz",          fHVz,           "HVz[HN]/F");

  fTree->Branch("HJtI",         fHJtI,          "HJtI[HN][2]/I");

  // Only for MC
  if (fIsMC) {
    fTree->Branch("PcToGn",       fPcToGn,        "PcToGn[PcN]/I");
    fTree->Branch("JtBdRN",       &fJtBdRN,       "JtBdRN/I");
    fTree->Branch("JtBFlavN",     &fJtBFlavN,     "JtBFlavN/I");
    fTree->Branch("JtBdRIndex",   fJtBdRIndex,    "JtBdRIndex[JtBdRN]/I");
    fTree->Branch("JtToBdRIndex", fJtToBdRIndex,  "JtToBdRIndex[JtBdRN]/I");
    fTree->Branch("JtBdR",        fJtBdR,         "JtBdR[JtBdRN]/F");
    fTree->Branch("JtBFlavIndex", fJtBFlavIndex,  "JtBFlavIndex[JtBFlavN]/I");
    fTree->Branch("JtFlavour",    fJtFlavour,     "JtFlavour[JtN]/I");
    fTree->Branch("JtBdRMatch",   fJtBdRMatch,    "JtBdRMatch[JtN]/O");
    fTree->Branch("GnN",          &fGnN,          "GnN/I");
    fTree->Branch("GnBN",         &fGnBN,         "GnBN/I");
    fTree->Branch("GnIndex",      fGnIndex,       "GnIndex[GnN]/I");
    fTree->Branch("GnBIndex",     fGnBIndex,      "GnBIndex[GnBN]/I");
    fTree->Branch("GnIsJet",      fGnIsJet,       "GnIsJet[GnN]/I");
    fTree->Branch("GnLongLived",  fGnLongLived,   "GnLongLived[GnN]/I");
    fTree->Branch("GnPdgId",      fGnPdgId,       "GnPdgId[GnN]/I");
    fTree->Branch("GnNMothers",   fGnNMothers,    "GnNMothers[GnN]/I");
    fTree->Branch("GnNDaughters", fGnNDaughters,  "GnNDaughters[GnN]/I");
    fTree->Branch("GnCharge",     fGnCharge,      "GnCharge[GnN]/F");
    fTree->Branch("GnPhi",        fGnPhi,         "GnPhi[GnN]/F");
    fTree->Branch("GnTheta",      fGnTheta,       "GnTheta[GnN]/F");
    fTree->Branch("GnEta",        fGnEta,         "GnEta[GnN]/F");
    fTree->Branch("GnRapidity",   fGnRapidity,    "GnRapidity[GnN]/F");
    fTree->Branch("GnP",          fGnP,           "GnP[GnN]/F");
    fTree->Branch("GnPt",         fGnPt,          "GnPt[GnN]/F");
    fTree->Branch("GnPx",         fGnPx,          "GnPx[GnN]/F");
    fTree->Branch("GnPy",         fGnPy,          "GnPy[GnN]/F");
    fTree->Branch("GnPz",         fGnPz,          "GnPz[GnN]/F");
    fTree->Branch("GnEnergy",     fGnEnergy,      "GnEnergy[GnN]/F");
    fTree->Branch("GnEt",         fGnEt,          "GnEt[GnN]/F");
    fTree->Branch("GnMass",       fGnMass,        "GnMass[GnN]/F");
    fTree->Branch("GnMt",         fGnMt,          "GnMt[GnN]/F");
    fTree->Branch("GnVx",         fGnVx,          "GnVx[GnN]/F");
    fTree->Branch("GnVy",         fGnVy,          "GnVy[GnN]/F");
    fTree->Branch("GnVz",         fGnVz,          "GnVz[GnN]/F");
    fTree->Branch("GnDist",       fGnDist,        "GnDist[GnN]/F");
    fTree->Branch("GnDistCM",     fGnDistCM,      "GnDistCM[GnN]/F");
    fTree->Branch("GnTau",        fGnTau,         "GnTau[GnN]/F");
    fTree->Branch("GnTauCM",      fGnTauCM,       "GnTauCM[GnN]/F");

    fTree->Branch("GnMotherIndex", fGnMotherIndex, "GnMotherIndex[GnN][5]/I");
    fTree->Branch("GnDaughterIndex", fGnDaughterIndex, "GnDaughterIndex[GnN][20]/I");
  }

  // Only for 2 JPsi events
  if (fIsJPsiMuMu) {
    fTree->Branch("JPsiI",        fJPsiI,         "JPsiI[2]/I");
    fTree->Branch("JPsidRMatchI", fJPsidRMatchI,  "JPsidRMatchI[2]/I");
    fTree->Branch("MuI",          fMuI,           "MuI[2][2]/I");
    fTree->Branch("MudRMatchI",   fMudRMatchI,    "MudRMatchI[2][2]/I");
    fTree->Branch("MuByPtI",      fMuByPtI,       "MuByPtI[4]/I");
    fTree->Branch("MuByPtMatchI", fMuByPtMatchI,  "MuByPtMatchI[4]/I");
  }

  // Only for Etab->2JPsi events
  if (fIsEtabJPsi&&fIsJPsiMuMu) {
    fTree->Branch("EtabI",            &fEtabI,           "EtabI/I");
    fTree->Branch("EtabdRMatchI",     &fEtabdRMatchI,    "EtabdRMatchI/I");
    fTree->Branch("Mu11_4MomJPsi1CM", fMu11_4MomJPsi1CM, "Mu11_4MomJPsi1CM[4]/F");
    fTree->Branch("Mu12_4MomJPsi1CM", fMu12_4MomJPsi1CM, "Mu12_4MomJPsi1CM[4]/F");
    fTree->Branch("Mu21_4MomJPsi2CM", fMu21_4MomJPsi2CM, "Mu21_4MomJPsi2CM[4]/F");
    fTree->Branch("Mu22_4MomJPsi2CM", fMu22_4MomJPsi2CM, "Mu22_4MomJPsi2CM[4]/F");
    fTree->Branch("JPsi1_4MomEtabCM", fJPsi1_4MomEtabCM, "JPsi1_4MomEtabCM[4]/F");
    fTree->Branch("JPsi2_4MomEtabCM", fJPsi2_4MomEtabCM, "JPsi2_4MomEtabCM[4]/F");
    fTree->Branch("Etab_4MomJPsi1CM", fEtab_4MomJPsi1CM, "Etab_4MomJPsi1CM[4]/F");
    fTree->Branch("Etab_4MomJPsi2CM", fEtab_4MomJPsi2CM, "Etab_4MomJPsi2CM[4]/F");
  }

}


//------------------------------------------
void edmEventTree::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup){
    edm::Handle< std::vector<pat::Muon> > muonHandle;
    try{
      iEvent.getByLabel(fMuonCollectionLabel, muonHandle);
    } catch (cms::Exception &ex) {
      cout << "No muon collection with label " << fMuonCollectionLabel << endl;
    }
    

























//**%%%??int main(int argc, char* argv[]) 
//**%%%??{
//**%%%??  // ----------------------------------------------------------------------
//**%%%??  // First Part: 
//**%%%??  //
//**%%%??  //  * enable the AutoLibraryLoader 
//**%%%??  //  * book the histograms of interest 
//**%%%??  //  * open the input file
//**%%%??  // ----------------------------------------------------------------------
//**%%%??
//**%%%??  // load framework libraries
//**%%%??  gSystem->Load( "libFWCoreFWLite" );
//**%%%??  AutoLibraryLoader::enable();
//**%%%??
//**%%%??  // initialize command line parser
//**%%%??  optutl::CommandLineParser parser ("Analyze FWLite Histograms");
//**%%%??
//**%%%??  // set defaults
//**%%%??  parser.integerValue ("maxEvents"  ) = 1000;
//**%%%??  parser.integerValue ("outputEvery") =   10;
//**%%%??  parser.stringValue  ("outputFile" ) = "analyzeEdmTuple.root";
//**%%%??
//**%%%??  // parse arguments
//**%%%??  parser.parseArguments (argc, argv);
//**%%%??  int maxEvents_ = parser.integerValue("maxEvents");
//**%%%??  unsigned int outputEvery_ = parser.integerValue("outputEvery");
//**%%%??  std::string outputFile_ = parser.stringValue("outputFile");
//**%%%??  std::vector<std::string> inputFiles_ = parser.stringVector("inputFiles");
//**%%%??
//**%%%??  // book a set of histograms
//**%%%??  fwlite::TFileService fs = fwlite::TFileService(outputFile_.c_str());
//**%%%??  TFileDirectory dir = fs.mkdir("analyzePatMuon");
//**%%%??  TH1F* muonPt_  = dir.make<TH1F>("muonPt"  , "pt"  ,   100,   0., 300.);
//**%%%??  TH1F* muonEta_ = dir.make<TH1F>("muonEta" , "eta" ,   100,  -3.,   3.);
//**%%%??  TH1F* muonEnergy_ = dir.make<TH1F>("muonEnergy" , "E" ,   100,  -0.,   50.);  
//**%%%??  TH1F* dimuMass_ = dir.make<TH1F>("dimuMass" , "mass" ,   100,  0.,   6.);  
//**%%%??
//**%%%??  // loop the events
//**%%%??  int ievt=0;  
//**%%%??  for(unsigned int iFile=0; iFile<inputFiles_.size(); ++iFile){
//**%%%??    // open input file (can be located on castor)
//**%%%??    TFile* inFile = TFile::Open(inputFiles_[iFile].c_str());
//**%%%??    if( inFile ){
//**%%%??      // ----------------------------------------------------------------------
//**%%%??      // Second Part: 
//**%%%??      //
//**%%%??      //  * loop the events in the input file 
//**%%%??      //  * receive the collections of interest via fwlite::Handle
//**%%%??      //  * fill the histograms
//**%%%??      //  * after the loop close the input file
//**%%%??      // ----------------------------------------------------------------------      
//**%%%??      fwlite::Event ev(inFile);
//**%%%??      for(ev.toBegin(); !ev.atEnd(); ++ev, ++ievt){
//**%%%??        edm::EventBase const & event = ev;
//**%%%??        // break loop if maximal number of events is reached 
//**%%%??        if(maxEvents_>0 ? ievt+1>maxEvents_ : false) break;
//**%%%??        // simple event counter
//**%%%??        if(outputEvery_!=0 ? (ievt>0 && ievt%outputEvery_==0) : false) 
//**%%%??                std::cout << "  processing event: " << ievt << std::endl;
//**%%%??
//**%%%??        // Handle to the muon pt
//**%%%??        edm::Handle<std::vector<float> > muonPt;
//**%%%??        event.getByLabel(std::string("patMuonAnalyzer:pt"), muonPt);
//**%%%??        // loop muon collection and fill histograms
//**%%%??        for(std::vector<float>::const_iterator mu1=muonPt->begin(); mu1!=muonPt->end(); ++mu1){
//**%%%??                muonPt_ ->Fill( *mu1 );
//**%%%??        }
//**%%%??        // Handle to the muon eta
//**%%%??        edm::Handle<std::vector<float> > muonEta;
//**%%%??        event.getByLabel(std::string("patMuonAnalyzer:eta"), muonEta);
//**%%%??        for(std::vector<float>::const_iterator mu1=muonEta->begin(); mu1!=muonEta->end(); ++mu1){
//**%%%??                muonEta_ ->Fill( *mu1 );
//**%%%??        }
//**%%%??        // Handle to the muon energy
//**%%%??        edm::Handle<std::vector<float> > muonEnergy;
//**%%%??        event.getByLabel(std::string("patMuonAnalyzer:energy"), muonEnergy);
//**%%%??        for(std::vector<float>::const_iterator mu1=muonEnergy->begin(); mu1!=muonEnergy->end(); ++mu1){
//**%%%??                muonEnergy_ ->Fill( *mu1 );
//**%%%??        }
//**%%%??        // Handle to the jpsi mass
//**%%%??        edm::Handle<std::vector<float> > DiMuMass;
//**%%%??        event.getByLabel(std::string("patMuonAnalyzer:mass"), DiMuMass);
//**%%%??        for(std::vector<float>::const_iterator jp1=DiMuMass->begin(); jp1!=DiMuMass->end(); ++jp1){
//**%%%??                dimuMass_ ->Fill( *jp1 );
//**%%%??        }
//**%%%??
//**%%%??      }  
//**%%%??      // close input file
//**%%%??      inFile->Close();
//**%%%??    }
//**%%%??    // break loop if maximal number of events is reached:
//**%%%??    // this has to be done twice to stop the file loop as well
//**%%%??    if(maxEvents_>0 ? ievt+1>maxEvents_ : false) break;
//**%%%??  }
//**%%%??  return 0;
//**%%%??}


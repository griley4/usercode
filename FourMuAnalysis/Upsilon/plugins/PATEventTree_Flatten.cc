// ----------------------------------------------------------------------
// FourMuonAnalysis
// ---------
// Summary: This version looks for 3 muons via HLT paths Dimuon0_Jpsi_Muon || Dimuon0_Upsilon_Muon and adds some extra muon quality information over the last version
//
// ----------------------------------------------------------------------
// Send all questions, wishes and complaints to the 
//
// Author:  Grant Riley: University of Tennessee
// ----------------------------------------------------------------------

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

#include "PATEventTree_Flatten.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMatrix.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"

#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>

using namespace std;
using namespace edm;
using namespace reco;
using namespace pat;

// ----------------------------------------------------------------------
PATEventTree::PATEventTree(edm::ParameterSet const& iConfig): 
  fRootFileName(iConfig.getUntrackedParameter<string>("rootFileName", string("PATEventTree.root"))),
  fIsMC(iConfig.getUntrackedParameter<bool>("isMC", false)),
  fHLTPathLabel(iConfig.getUntrackedParameter<InputTag>("HLTPathLabel", edm::InputTag("TriggerResults::HLT"))),
  fHLTFilterLabel(iConfig.getUntrackedParameter<InputTag>("HLTFilterLabel", edm::InputTag("hltTriggerSummaryAOD"))),
  fHLTCollectionLabel(iConfig.getUntrackedParameter<InputTag>("HLTCollectionLabel", edm::InputTag("patTrigger"))),
  fMuonCollectionLabel(iConfig.getUntrackedParameter<InputTag>("MuonCollectionLabel", edm::InputTag("patMuons"))),
  fTrackCollectionLabel(iConfig.getUntrackedParameter<InputTag>("TrackCollectionLabel", edm::InputTag("generalTracks"))),
  fGenCollectionLabel(iConfig.getUntrackedParameter<InputTag>("GenCollectionLabel", edm::InputTag("genParticles"))),
  fDimuonCandLabel(iConfig.getUntrackedParameter<InputTag>("DimuonCandLabel", edm::InputTag("Dimuon"))),
  fFourmuonCandLabel(iConfig.getUntrackedParameter<InputTag>("FourmuonCandLabel", edm::InputTag("Fourmuon"))),
  fDimuonInputLabel(iConfig.getUntrackedParameter<InputTag>("DimuonInputLabel", edm::InputTag("goodMuons"))),
  fInit(0)
{
  string rcsid = string("$Id: PATEventTree.cc,v 2.00 2015/11/03 11:25:00 Exp $");
  cout << "----------------------------------------------------------------------" << endl;
  cout << "---  PATEventTree flattener" << endl;
  cout << "---  version:                         " << rcsid << endl;
  cout << "---  rootFileName:                    " << fRootFileName << endl;
  cout << "---  MuonCollectionLabel:             " << fMuonCollectionLabel << endl;
  cout << "---  GenCollectionLabel:              " << fGenCollectionLabel << endl;
  cout << "----------------------------------------------------------------------" << endl;
}

// ----------------------------------------------------------------------
PATEventTree::~PATEventTree() { }  

// ----------------------------------------------------------------------
void PATEventTree::endJob() {

  fFile->cd();
  fFile->Write();
  fFile->Close();
  delete fFile;

  cout << "==>PATEventTree> Succesfully ended job" << endl;

}

// ----------------------------------------------------------------------
void PATEventTree::beginJob() {

  fFile = TFile::Open(fRootFileName.c_str(), "RECREATE");
  fFile->cd();

  nevt = 0;

  fTree = new TTree("PATEventTree", "PATEventTree");

  fTree->Branch("run",          &fRun,          "run/i");
  fTree->Branch("lumiblock",    &fLumiBlock,    "lumiblock/i");
  fTree->Branch("event",        &fEvent,        "event/i");
  fTree->Branch("bx",           &fBX,           "bx/I");
  fTree->Branch("orbit",        &fOrbit,        "orbit/I");
  fTree->Branch("bz",           &fBz,           "bz/F");
  fTree->Branch("HLTP_Dimuon0_Jpsi_Muon", fHLTP_Dimuon0_Jpsi_Muon, "HLTP_Dimuon0_Jpsi_Muon[3]/O");
  fTree->Branch("HLTP_Dimuon0_Upsilon_Muon", fHLTP_Dimuon0_Upsilon_Muon, "HLTP_Dimuon0_Upsilon_Muon[3]/O");
  fTree->Branch("HLTP_TripleMu5",         fHLTP_TripleMu5,       "HLTP_TripleMu5[3]/O");
  fTree->Branch("PcN",          &fPcN,          "PcN/I");
  fTree->Branch("MuN",          &fMuN,          "MuN/I");
  fTree->Branch("TkN",          &fTkN,          "TkN/I");
  fTree->Branch("PcIndex",      fPcIndex,       "PcIndex[PcN]/I");
  fTree->Branch("MuIndex",      fMuIndex,       "MuIndex[MuN]/I");
  fTree->Branch("TkToPc",       fTkToPc,        "TkToPc[TkN]/I");
  fTree->Branch("PcToTk",       fPcToTk,        "PcToTk[PcN]/I");
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
  fTree->Branch("MuIsHighPurity",fMuIsHighPurity,"MuIsHighPurity[MuN]/O");
  fTree->Branch("goodSoftMuon",fgoodSoftMuon,"goodSoftMuon[MuN]/O");
  fTree->Branch("goodSoftMuonMod",fgoodSoftMuonMod,"goodSoftMuonMod[MuN]/O");
  fTree->Branch("goodTightMuon",fgoodTightMuon,"goodTightMuon[MuN]/O");

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

  // Only for MC
  if (fIsMC) {
    fTree->Branch("PcToGn",       fPcToGn,        "PcToGn[PcN]/I");
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

}


// ----------------------------------------------------------------------
void  PATEventTree::beginRun(const Run &run, const EventSetup &iSetup) {
  bool hasChanged;
  fValidHLTConfig = fHltConfig.init(run,iSetup,"HLT",hasChanged);
}


// ----------------------------------------------------------------------
void PATEventTree::endRun(Run const &run, EventSetup const&iSetup) {
  fValidHLTConfig = false;
} 


// ----------------------------------------------------------------------
void PATEventTree::analyze(const edm::Event& iEvent,
			const edm::EventSetup& iSetup) {

  // ----------------------------------------------------------------------
  // -- Get collections of event information
  // ----------------------------------------------------------------------
  edm::Handle<reco::GenParticleCollection> genHandle;
  if (fIsMC) {
    try{
      iEvent.getByLabel(fGenCollectionLabel, genHandle);
    } catch (cms::Exception &ex) {
      cout << "No gen particle collection with label " << fGenCollectionLabel << endl;
    }
  }
  edm::Handle< std::vector<reco::Track> > ctfTrackHandle;
  try{ 
    iEvent.getByLabel(fTrackCollectionLabel, ctfTrackHandle);
  } catch (cms::Exception &ex) {
    cout << "No ctf track collection with label " << fTrackCollectionLabel << endl;
  }
  edm::Handle< std::vector<pat::Muon> > muonHandle;
  try{ 
    iEvent.getByLabel(fMuonCollectionLabel, muonHandle);
  } catch (cms::Exception &ex) {
    cout << "No muon collection with label " << fMuonCollectionLabel << endl;
  }
  edm::Handle< reco::CompositeCandidateCollection > DimuonCandHandle;
  try{ 
    iEvent.getByLabel(fDimuonCandLabel, DimuonCandHandle);
  } catch (cms::Exception &ex) {
    cout << "No composite candidate collection with label " << fDimuonCandLabel << endl;
  }
  edm::Handle< pat::TriggerObjectStandAloneCollection > HLTHandle;
  try{ 
    iEvent.getByLabel(fHLTCollectionLabel, HLTHandle);
  } catch (cms::Exception &ex) {
    cout << "No HLT collection with label " << fHLTCollectionLabel << endl;
  }
  edm::Handle< reco::CompositeCandidateCollection > FourmuonCandHandle;
  try{ 
    iEvent.getByLabel(fFourmuonCandLabel, FourmuonCandHandle);
  } catch (cms::Exception &ex) {
    cout << "No composite candidate collection with label " << fFourmuonCandLabel << endl;
  }
  edm::Handle< reco::MuonRefVector > DimuonInputHandle;
  try{ 
    iEvent.getByLabel(fDimuonInputLabel, DimuonInputHandle);
  } catch (cms::Exception &ex) {
    cout << "No muon ref collection with label " << fDimuonInputLabel << endl;
  }

  fPcN = PARTMAX;
  ++nevt; 
  init();

  // ----------------------------------------------------------------------
  // -- Event information
  // ----------------------------------------------------------------------
  fRun       = iEvent.id().run();
  fLumiBlock = iEvent.luminosityBlock();
  fEvent     = iEvent.id().event();

  const edm::Timestamp timeStamp = iEvent.time();
  unsigned int high = timeStamp.value() >> 32;       // seconds
  unsigned int low = 0xffffffff & timeStamp.value(); // microseconds  

  fTimeLo    = low;
  fTimeHi    = high;

  fBX        = iEvent.bunchCrossing();
  fOrbit     = iEvent.orbitNumber();

  // -- Magnetic field
  ESHandle<MagneticField> MF;
  iSetup.get<IdealMagneticFieldRecord>().get(MF);
  const MagneticField* theMagneticField = MF.product();
  fBz    = fabs(theMagneticField->inTesla(GlobalPoint(0,0,0)).z());

  // access HLT information from event
  unsigned int psSet = fHltConfig.prescaleSet(iEvent, iSetup);
  Handle<TriggerResults> hHLTresults;
  bool hltF = true;
  try {
    iEvent.getByLabel(fHLTPathLabel, hHLTresults);
  } catch (cms::Exception &ex) {
    hltF = false;
  }

  //to cout all trigger paths in event
  //const TriggerNames &trigName = iEvent.triggerNames(*hHLTresults);
  /*cout<<"trigger paths in event"<<endl;
  for (unsigned int itrig = 0; itrig < trigName.size(); itrig++) {
    cout<<trigName.triggerName(itrig)<<endl;
  }*/

  // look at the filters that were passed
  edm::Handle<trigger::TriggerEvent> triggerEventHandle;
  trigger::TriggerEvent triggerEvent;
  hltF = true;
  try {
    iEvent.getByLabel(fHLTFilterLabel,triggerEventHandle);
  } catch (cms::Exception &ex) {
    hltF = false;
  }
  if(hltF) triggerEvent = *(triggerEventHandle.product());

  // ----------------------------------------------------------------------
  // -- HLT path information
  // ----------------------------------------------------------------------
  if ( hltF ) fillHLTPath( psSet, hHLTresults, triggerEvent );
  //if ( fHLT_Skim && !(fHLTP_Dimuon0_Upsilon_Muon[1] || fHLTP_Dimuon0_Jpsi_Muon[1]) ) return; // only ntuplize events passing trigger if skimming enabled

  // ----------------------------------------------------------------------
  // -- HLT objects
  // ----------------------------------------------------------------------
  if ( HLTHandle.isValid() ) fillHLT( *(HLTHandle.product()) );
  else { cout << "--> No valid HLT collection" << endl; }

  // ----------------------------------------------------------------------
  // -- Gen particles
  // ----------------------------------------------------------------------
  if (fIsMC) {
    if ( genHandle.isValid() ) fillGen( *(genHandle.product()) );
    else { cout << "--> No valid gen collection" << endl; }
  }

  // ----------------------------------------------------------------------
  // -- Fill particles
  // ----------------------------------------------------------------------
  if ( muonHandle.isValid() && ctfTrackHandle.isValid() ) fillParticles( *(muonHandle.product()), *(ctfTrackHandle.product()) );
  else { cout << "--> Missing valid particle collection" << endl; }
	
  // determine track IP
  for (Int_t itk=0; itk<fTkN; itk++) {
    float x1, y1, z1;
    x1 = y1 = z1 = -9999.0;
    float px1, py1, pz1, px2, py2, pz2, px3, py3, pz3;
    px1 = fPcVx[itk]-fPcPx[itk];
    py1 = fPcVy[itk]-fPcPy[itk];
    pz1 = fPcVz[itk]-fPcPz[itk];
    px2 = fPcVx[itk]+fPcPx[itk];
    py2 = fPcVy[itk]+fPcPy[itk];
    pz2 = fPcVz[itk]+fPcPz[itk];
    px3 = fPvX[0];
    py3 = fPvY[0];
    pz3 = fPvZ[0];

    float u = ( (px3-px1)*(px2-px1)+(py3-py1)*(py2-py1)+(pz3-pz1)*(pz2-pz1) )/( (px2-px1)*(px2-px1)+(py2-py1)*(py2-py1)+(pz2-pz1)*(pz2-pz1) );
    x1 = px1 + u*(px2 - px1);
    y1 = py1 + u*(py2 - py1);
    z1 = pz1 + u*(pz2 - pz1);
    fPcIP[itk] = sqrt( (x1-px3)*(x1-px3)+(y1-py3)*(y1-py3)+(z1-pz3)*(z1-pz3) );
    fPcIPxy[itk] = sqrt( (x1-px3)*(x1-px3)+(y1-py3)*(y1-py3) );
  } // end loop over tracks

  // ----------------------------------------------------------------------
  // -- JPsi Candidates
  // ----------------------------------------------------------------------
  // Make transient tracks for vertex-building
  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
  // do the conversion:
  vector<TransientTrack> t_tks = (*theB).build(ctfTrackHandle);
  // Use dimuon collection and transient tracks to make J/Psi candidates
  if ( DimuonCandHandle.isValid() && DimuonInputHandle.isValid() ) fillDimuonCand( *(DimuonCandHandle.product()), *(DimuonInputHandle.product()), t_tks );
  else { cout << "--> No valid Dimuon cand. collection" << endl; }
  fJPsiMuMuN = fJPsiN;
  // ----------------------------------------------------------------------
  // -- Etab Candidates
  // ----------------------------------------------------------------------
  if ( fJPsiN>1 ) makeEtabCand( t_tks );

	if (fgsmmN>=4){
    fTree->Fill();
  }
}


// ------------------------------------------------------------------------
void PATEventTree::init() {

  fEvSphericity = fEvAplanarity = fEvLambda[0] = fEvLambda[1] = fEvLambda[2] = fEvThrust = fEvThrust_Major = fEvThrust_Minor = -9999.;
  for (int i = 0; i < 7; i++) fEvFW[i] = -9999.;

  // Only for MC
  if (fIsMC) {
    for (int i = 0; i < fGnN; i++) {
      fGnIndex[i] = fGnBIndex[i] = fGnIsJet[i] = fGnLongLived[i] = fGnPdgId[i] = fGnNMothers[i] = fGnNDaughters[i] = -9999;
      fGnCharge[i] = fGnPhi[i] = fGnTheta[i] = fGnEta[i] = fGnRapidity[i] = fGnP[i] = fGnPt[i] = fGnPx[i] = fGnPy[i] = fGnPz[i] = fGnEnergy[i] = fGnEt[i] = fGnMass[i] = fGnMt[i] = fGnVx[i] = fGnVy[i] = fGnVz[i] = fGnDist[i] = fGnDistCM[i] = fGnTau[i] = fGnTauCM[i] = -9999.;
      for (int j = 0; j < MOTHERMAX; j++) fGnMotherIndex[i][j]  = -9999;
      for (int k = 0; k < DAUGHTERMAX; k++) fGnDaughterIndex[i][k]  = -9999;
    }
    for (int i = 0; i < fJtN; i++) {
      fJtBdRIndex[i] = fJtBFlavIndex[i] = fJtToBdRIndex[i] = -9999;
      fJtBdR[i] = -9999.;
      fJtBdRMatch[i] = false;
    }
  }
	
  fHLTP_DoubleMu3_PS = fHLTP_DoubleMu6_PS = fHLTP_DoubleMu7_PS = fHLTP_Dimuon0_Upsilon_Muon_PS = fHLTP_Dimuon0_Jpsi_Muon_PS = fHLTP_Dimuon0_Jpsi_PS = fHLTP_Dimuon10_Jpsi_Barrel_PS = fHLTP_TripleMu5_PS = 0;

  for (int i = 0; i < 3; i++) {
    fHLTP_DoubleMu3[i] = fHLTP_DoubleMu6[i] = fHLTP_DoubleMu7[i] = fHLTP_Dimuon0_Upsilon_Muon[i] = fHLTP_Dimuon0_Jpsi_Muon[i] = fHLTP_Dimuon0_Jpsi[i] = fHLTP_Dimuon10_Jpsi_Barrel[i] = fHLTP_TripleMu5[i] = false;
  }

  for (int i = 0; i < 5; i++) {
    fHLTP_DoubleMu3_Filters[i] = fHLTP_DoubleMu6_Filters[i] = fHLTP_DoubleMu7_Filters[i] = fHLTP_TripleMu5_Filters[i] = fHLTP_Dimuon0_Jpsi_Filters[i] = fHLTP_Dimuon0_Jpsi_Muon_Filters[i] = fHLTP_Dimuon10_Jpsi_Barrel_Filters[i] = false;
  }
  fHLTP_Dimuon0_Jpsi_Filters[5] = fHLTP_Dimuon0_Jpsi_Filters[6] = fHLTP_Dimuon0_Jpsi_Muon_Filters[5] = fHLTP_Dimuon0_Jpsi_Muon_Filters[6] = fHLTP_Dimuon0_Jpsi_Muon_Filters[7] = fHLTP_Dimuon10_Jpsi_Barrel_Filters[5] = fHLTP_Dimuon10_Jpsi_Barrel_Filters[6] = false;

  for (int i = 0; i < fHLTN; i++) {
    fHLT_Index[i] = fHLT_ToPc[i] = fHLT_ToJt[i] = fHLT_PdgId[i] = -9999;
    fHLT_Mass[i] = fHLT_Energy[i] = fHLT_Et[i] = fHLT_P[i] = fHLT_Pt[i] = fHLT_Px[i] = fHLT_Py[i] = fHLT_Pz[i] = fHLT_Theta[i] = fHLT_Eta[i] = fHLT_Phi[i] = -9999.;
    for (int j = 0; j < 2; j++) { 
      fHLT_Mu[i][j] = fHLT_Mu12[i][j] = fHLT_Mu15[i][j] = fHLT_Mu20[i][j] = fHLT_Mu24[i][j] = fHLT_Mu30[i][j] = fHLT_IsoMu12[i][j] = fHLT_IsoMu15[i][j] = fHLT_IsoMu17[i][j] = fHLT_IsoMu24[i][j] = fHLT_IsoMu30[i][j] = fHLT_DoubleMu3[i][j] = fHLT_DoubleMu6[i][j] = fHLT_DoubleMu7[i][j] = fHLT_Dimuon0_Jpsi_Muon[i][j] = fHLT_Dimuon0_Jpsi[i][j] = fHLT_Dimuon7_Jpsi_Displaced[i][j] = fHLT_Dimuon7_Jpsi_X_Barrel[i][j] = fHLT_Dimuon10_Jpsi_Barrel[i][j] = fHLT_TripleMu5[i][j] = fHLT_Jet[i][j] = false;
    }
  }

  for (int i = 0; i < fPcN; i++) {
//    fMuChambers[i] = const std::vector <-999,-999>;
    fPcIndex[i] = fMuIndex[i] = fElecIndex[i] = fMiscTkIndex[i] = fPhotIndex[i] = fPcToGn[i] = fPcToTk[i] = fTkToPc[i] = fPcToPv[i] = fMuToHLT[i] = fPcToSsv[i] = fPcToGtv[i] = fPcTkQuality[i] = fPcPdgId[i] = -9999;
    fPcCharge[i] = fPcChi2[i] = fPcNdof[i] = fPcEnergy[i] = fPcEt[i] = fPcP[i] = fPcPt[i] = fPcPx[i] = fPcPy[i] = fPcPz[i] = fPcTheta[i] = fPcEta[i] = fPcPhi[i] = fPcD0[i] = fPcDz[i] = fPcEtaErr[i] = fPcPhiErr[i] = fPcD0Err[i] = fPcDzErr[i] = fPcVx[i] = fPcVy[i] = fPcVz[i] = fPcEcalIso[i] = fPcHcalIso[i] = fPcTrackIso[i] = fPcIP[i] = fPcIPxy[i] = -9999.;
    fPcJtN[i] = fPcPixHitN[i] = fPcPixLayN[i] = fPcStripHitN[i] = fPcStripLayN[i] = fMuHLTN[i] = fMuHitN[i] = fMuMatchedN[i] = fMuMatchedNSegArb[i]  = fMuMatchedNSegTrkArb[i] = fMuMatchedNSegTrkArbClean[i] = 0;
    fMuChi2[i] = fMuNdof[i] = fMuTkKink[i] = fMuGlbKink[i] = fMuGlbProb[i] = fMuTkSADist[i] = fMuTkSAdR[i] = fMuECALEnergy[i] = fMuHCALEnergy[i] = fMuCalCompat[i] = -9999.;
    fMuIsGlobal[i] = fMuIsTracker[i] = fMuIsStandalone[i] = fMuIsCalo[i] = fMuArbitrated[i] = fMuLastStationLoose[i] = fMuLastStationTight[i] = fMu2DCompatibilityLoose[i] = fMu2DCompatibilityTight[i] = fMuOneStationLoose[i] = fMuOneStationTight[i] = fMuHLTMatch[i][0] = fMuHLTMatch[i][1] = fMuL3Match[i] = fMuTightMatch[i] = false;
    for (int j = 0; j < PARTTOJETMAX; j++) fPcToJt[i][j] = -9999;
  }

  for (int i = 0; i < fAllPvN; i++) {
    fPvIndex[i] = fPvTkN[i] = fPvClosestI[i] = -9999;
    fPvX[i] = fPvY[i] = fPvZ[i] = fPvXe[i] = fPvYe[i] = fPvZe[i] = fPvPx[i] = fPvPy[i] = fPvPz[i] = fPvPt[i] = fPvP[i] = fPvEnergy[i] = fPvEta[i] = fPvChi2[i] = fPvNdof[i] = fPvMass[i] = -9999.;
    fPvIsFake[i] = true;
    fPvIsRefit[i] = false;
  }

  for (int i = 0; i < fJtN; i++) {
    fJtIndex[i] = fJtStandIndex[i] = fJtFatIndex[i] = fJtSubIndex[i] = fJtFiltIndex[i] = fJtToPv[i] = fJtToHLT[i] = fJtnConstituents[i] = fJtFlavour[i] = fJtn60[i] = fJtn90[i] = fJtnChargedParticles[i] = fJtnNeutralParticles[i] = fJtnChargedHadrons[i] = fJtnNeutralHadrons[i] = fJtnPhotons[i] = fJtnElectrons[i] = fJtnMuons[i] = fJtnHFHadrons[i] = fJtnHFEMParticles[i] = fSubToFat[i] = fFiltToFat[i] = -9999;
    fJtRankTCHE[i] = fJtRankTCHP[i] = fJtRankP[i] = fJtRankBP[i] = fJtRankSSVHE[i] = fJtRankSSVHP[i] = fJtRankCSV[i] = fJtRankCSVMVA[i] = fJtRankGT[i] = fJtRankSE[i] = fJtRankSM[i] = 9999;
    fJtCharge[i] = fJtDiscTCHE[i] = fJtDiscTCHP[i] = fJtDiscP[i] = fJtDiscBP[i] = fJtDiscSSVHE[i] = fJtDiscSSVHP[i] = fJtDiscCSV[i] = fJtDiscCSVMVA[i] = fJtDiscGT[i] = fJtDiscSE[i] = fJtDiscSM[i] = fJtMaxDist[i] = fJtPhi[i] = fJtTheta[i] = fJtEta[i] = fJtRapidity[i] = fJtP[i] = fJtPt[i] = fJtPx[i] = fJtPy[i] = fJtPz[i] = fJtEnergy[i] = fJtEt[i] = fJtMass[i] = fJtMt[i] = fJtVx[i] = fJtVy[i] = fJtVz[i] = fJtChargedEmEnergy[i] = fJtNeutralEmEnergy[i] = fJtChargedHadronEnergy[i] = fJtNeutralHadronEnergy[i] = fJtPhotonEnergy[i] = fJtElectronEnergy[i] = fJtMuonEnergy[i] = fJtHFHadronEnergy[i] = fJtHFEMEnergy[i] = fJtdRMean[i] = fJtdRMax[i] = fJtPtRelMean[i] = fJtPtRelMax[i] = fJtPtRelSum[i] = fJtPullPx[i] = fJtPullPy[i] = fJtPullPz[i] = -9999.;
    fJtIsStandard[i] = fJtIsFat[i] = fJtIsSub[i] = fJtIsFilt[i] = fJtBFromH[i] = fJtHLTMatch[i][0] = fJtHLTMatch[i][1] = fJtVeto[i] = false;
    for (int j = 0; j < PARTINJETMAX; j++) fJtToPc[i][j] = -9999;
    for (int j = 0; j < SVINJETMAX; j++) fJtToSsv[i][j] = fJtToGtv[i][j] = -9999;

    fFatSubN[i] = fFatFiltN[i] = fJtHLTN[i] = fJtTkN[i] = fJtSsvN[i] = fJtGtvN[i] = 0;
  }

  for (int i = 0; i < fSvN; i++) {
    fSvIndex[i] = fSvTkN[i] = fSvToJt[i] = fSvSeqInJt[i] = -9999;
    fSvX[i] = fSvY[i] = fSvZ[i] =  fSvXe[i] = fSvYe[i] = fSvZe[i] = fSvPx[i] = fSvPy[i] = fSvPz[i] = fSvPt[i] = fSvEta[i] = fSvChi2[i] = fSvNdof[i] = fSvDist[i] = fSvDistCM[i] = fSvMass[i] = fSvTau[i] = fSvTauCM[i] = -9999.;
    fSvIsGTV[i] = false;
    for (int j = 0; j < TKINSVMAX; j++) fSvToPc[i][j] = -9999;
  }

  for (int i = 0; i < METMAX; i++) {
    fMETIndex[i] = -9999;
    fMETCharge[i] = fMETPhi[i] = fMETTheta[i] = fMETEta[i] = fMETRapidity[i] = fMETP[i] = fMETPt[i] = fMETPx[i] = fMETPy[i] = fMETPz[i] = fMETEnergy[i] = fMETEt[i] = fMETMass[i] = fMETMt[i] = fMETVx[i] = fMETVy[i] = fMETVz[i] = -9999.;
  }

  fBaseJPsiI[0] = fBaseJPsiI[1] = -9999;
  for (int i = 0; i < JPsiMAX; i++) {
    fJPsiIndex[i] = fJPsiClosestPVinZ[i] = fJPsiMuI[i][0] = fJPsiMuI[i][1] = fJPsiMuCategory[i][0] = fJPsiMuCategory[i][1] = -9999;
    fJPsiCharge[i] = fJPsiPhi[i] = fJPsiTheta[i] = fJPsiEta[i] = fJPsiRapidity[i] = fJPsiP[i] = fJPsiPt[i] = fJPsiPx[i] = fJPsiPy[i] = fJPsiPz[i] = fJPsiEnergy[i] = fJPsiEt[i] = fJPsiMass[i] = fJPsiMt[i] = fJPsiChi2[i] = fJPsiNdof[i] = fJPsiVx[i] = fJPsiVy[i] = fJPsiVz[i] = fJPsiVtxPhi[i] = fJPsiVtxTheta[i] = fJPsiVtxEta[i] = fJPsiVtxRapidity[i] = fJPsiVtxP[i] = fJPsiVtxPt[i] = fJPsiVtxPx[i] = fJPsiVtxPy[i] = fJPsiVtxPz[i] = fJPsiVtxEnergy[i] = fJPsiVtxEt[i] = fJPsiVtxMass[i] = fJPsiVtxMt[i] = -9999.;
    for (int j = 0; j < 2; j++) {
      fJPsiMuCutKin[i][j] = fJPsiMuCutHLT[i][j] = fJPsiMuCutIso[i][j] = fJPsiMuCutSA[i][j] = fJPsiMuCutTrk[i][j] = false;
      for (int k = 0; k < 5; k++) fJPsiMuType[i][j][k] = false;
    }
  }
  if ( fIsJPsiMuMu ) {
    for (int i = 0; i < 2; i++) {
      fJPsiI[i] = fJPsidRMatchI[i] = -9999;
      for (int j = 0; j < 2; j++) fMuI[i][j] = fMudRMatchI[i][j] = -9999;
    }
    for (int i = 0; i < 4; i++) fMuByPtI[i] = fMuByPtMatchI[i] = -9999;
  }

  fBaseEtabI = -9999;
  for (int i = 0; i < ETABMAX; i++) {
    fEtabIndex[i] = fEtabDuplicatesI[i] = fEtabJPsiI[i][0] = fEtabJPsiI[i][1] = fEtabMuI[i][0] = fEtabMuI[i][1] = fEtabMuI[i][2] = fEtabMuI[i][3] = fEtabJPsiIsoTkN[i][0] = fEtabJPsiIsoTkN[i][1] = fEtabToRePvI[i] = -9999;
    fEtabMuN[i] = 0;
    fEtabCharge[i] = fEtabPhi[i] = fEtabTheta[i] = fEtabEta[i] = fEtabRapidity[i] = fEtabP[i] = fEtabPt[i] = fEtabPx[i] = fEtabPy[i] = fEtabPz[i] = fEtabEnergy[i] = fEtabEt[i] = fEtabMass[i] = fEtabMt[i] = fEtabVx[i] = fEtabVy[i] = fEtabVz[i] = fEtabVxE[i] = fEtabVyE[i] = fEtabVzE[i] = fEtabVtxPhi[i] = fEtabVtxTheta[i] = fEtabVtxEta[i] = fEtabVtxRapidity[i] = fEtabVtxP[i] = fEtabVtxPt[i] = fEtabVtxPx[i] = fEtabVtxPy[i] = fEtabVtxPz[i] = fEtabVtxEnergy[i] = fEtabVtxEt[i] = fEtabVtxMass[i] = fEtabVtxMt[i] = fEtabCT[i] = fEtabCTxy[i] = fEtabJPsiDeltaL[i] = fEtabJPsiDeltaT[i] = fEtabJPsiVtxErr[i] = fEtabJPsiVtxErrxy[i] = fEtabJPsiProjX[i][0] = fEtabJPsiProjX[i][1] = fEtabJPsiProjY[i][0] = fEtabJPsiProjY[i][1] = fEtabJPsiProjZ[i][0] = fEtabJPsiProjZ[i][1] = fEtabJPsiIso7PV[i][0] = fEtabJPsiIso7PV[i][1] = fEtabJPsiIsoTkCA[i][0] = fEtabJPsiIsoTkCA[i][1] = fEtabJPsiCT[i][0] = fEtabJPsiCT[i][1] = fEtabJPsiCTxy[i][0] = fEtabJPsiCTxy[i][1] = fEtabJPsiVtxCT[i][0] = fEtabJPsiVtxCT[i][1] = fEtabJPsiVtxCTxy[i][0] = fEtabJPsiVtxCTxy[i][1] = fEtabJPsiToPVVtxErr[i][0] = fEtabJPsiToPVVtxErr[i][1] = fEtabJPsiToPVVtxErrxy[i][0] = fEtabJPsiToPVVtxErrxy[i][1] = -9999.;
  }
  if ( fIsEtabJPsi&&fIsJPsiMuMu ) { fEtabI = fEtabdRMatchI = -9999; }

  for (int i = 0; i < HMAX; i++) {
    fHIndex[i] = fHJtI[i][0] = fHJtI[i][1] = -9999;
    fHCharge[i] = fHPhi[i] = fHTheta[i] = fHEta[i] = fHRapidity[i] = fHP[i] = fHPt[i] = fHPx[i] = fHPy[i] = fHPz[i] = fHEnergy[i] = fHEt[i] = fHMass[i] = fHMt[i] = fHVx[i] = fHVy[i] = fHVz[i] = -9999.;
  }

  // Only for JPsi->MuMu events
  if (fIsEtabJPsi&&fIsJPsiMuMu) {
    for (int i = 0; i < 4; i++) {
      fMu11_4MomJPsi1CM[i] = fMu12_4MomJPsi1CM[i] = fMu21_4MomJPsi2CM[i] = fMu22_4MomJPsi2CM[i] = fJPsi1_4MomEtabCM[i] = fJPsi2_4MomEtabCM[i] = fEtab_4MomJPsi1CM[i] = fEtab_4MomJPsi2CM[i] = -9999.0;
    }
  }

  fPvN = fRePvN = fAllPvN = fHLTN = fPcN = fTkN = fMuN = fElecN = fMiscTkN = fPhotN = JtShift = fJtN = fJtStandN = fJtFatN = fJtSubN = fJtFiltN = fMETN = fSvN = fSsvN = fGtvN = fJPsiN = fEtabN = fHN = fGnN = fGnBN = fJtBdRN = fJtBFlavN = fgsmN = fgsmmN = fgtmN = 0;

}


void PATEventTree::fillHLTPath(const unsigned int psSet, const edm::Handle<edm::TriggerResults>& hHLTresults, const trigger::TriggerEvent& triggerEvent) {

  // -- Read HLT configuration and names
  vector<string> validTriggerNames;
  if (fValidHLTConfig) validTriggerNames = fHltConfig.triggerNames();
  else cout << "==> PATEventTree: No valid Trigger configuration!!!" << endl;

  if (validTriggerNames.size() < 1) {
    cout << "==> PATEventTree: NO valid trigger names returned by HLT config provided!!??" << endl;
  }

  // to cout all trigger paths in configuration
  /*cout<<"trigger paths in configuration"<<endl;
  for (unsigned int it = 0; it < validTriggerNames.size(); it++) {
    cout<<validTriggerNames[it]<<endl;
  }*/

  bool accept, wasrun, error;
  unsigned int prescale;

  for (unsigned int itrig = 0; itrig < validTriggerNames.size(); itrig++) {

    wasrun   = hHLTresults->wasrun(itrig);
    accept   = hHLTresults->accept(itrig);
    error    = hHLTresults->error(itrig); 
    prescale = fHltConfig.prescaleValue(psSet, validTriggerNames[itrig]);

    if (validTriggerNames[itrig].find("HLT_DoubleMu3_v")!=string::npos)  {
      fHLTP_DoubleMu3[0] = wasrun;
      fHLTP_DoubleMu3[1] = accept;
      fHLTP_DoubleMu3[2] = error;
      fHLTP_DoubleMu3_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_DoubleMu6_v")!=string::npos) {
      fHLTP_DoubleMu6[0] = wasrun;
      fHLTP_DoubleMu6[1] = accept;
      fHLTP_DoubleMu6[2] = error;
      fHLTP_DoubleMu6_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_DoubleMu7_v")!=string::npos) {
      fHLTP_DoubleMu7[0] = wasrun;
      fHLTP_DoubleMu7[1] = accept;
      fHLTP_DoubleMu7[2] = error;
      fHLTP_DoubleMu7_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_TripleMu5_v")!=string::npos) {
      fHLTP_TripleMu5[0] = wasrun;
      fHLTP_TripleMu5[1] = accept;
      fHLTP_TripleMu5[2] = error;
      fHLTP_TripleMu5_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_Dimuon0_Jpsi_v")!=string::npos) {
      fHLTP_Dimuon0_Jpsi[0] = wasrun;
      fHLTP_Dimuon0_Jpsi[1] = accept;
      fHLTP_Dimuon0_Jpsi[2] = error;
      fHLTP_Dimuon0_Jpsi_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_Dimuon0_Jpsi_Muon_v")!=string::npos) {
      fHLTP_Dimuon0_Jpsi_Muon[0] = wasrun;
      fHLTP_Dimuon0_Jpsi_Muon[1] = accept;
      fHLTP_Dimuon0_Jpsi_Muon[2] = error;
      fHLTP_Dimuon0_Jpsi_Muon_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_Dimuon0_Upsilon_Muon_v")!=string::npos) {
      fHLTP_Dimuon0_Upsilon_Muon[0] = wasrun;
      fHLTP_Dimuon0_Upsilon_Muon[1] = accept;
      fHLTP_Dimuon0_Upsilon_Muon[2] = error;
      fHLTP_Dimuon0_Upsilon_Muon_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_Dimuon10_Jpsi_Barrel_v")!=string::npos) {
      fHLTP_Dimuon10_Jpsi_Barrel[0] = wasrun;
      fHLTP_Dimuon10_Jpsi_Barrel[1] = accept;
      fHLTP_Dimuon10_Jpsi_Barrel[2] = error;
      fHLTP_Dimuon10_Jpsi_Barrel_PS = prescale;
    }
  }

  for(uint filterIndex=0;filterIndex<triggerEvent.sizeFilters();++filterIndex){  //loop over all trigger filters in event (i.e. filters passed)
    string label = triggerEvent.filterTag(filterIndex).label();
    if(label.find( "hltL1sL1DoubleMu0" ) != string::npos ) {
      fHLTP_DoubleMu3_Filters[0] = true;
      fHLTP_Dimuon0_Jpsi_Filters[0] = true;
      fHLTP_Dimuon0_Jpsi_Muon_Filters[0] = true;
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[0] = true;
    } else if(label.find( "hltPreDimuon0JpsiMuon" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[1] = true;
    } else if(label.find( "hltTripleMuonL1Filtered0" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[2] = true;
    } else if(label.find( "hltTripleMuonL2PreFiltered0" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[3] = true;
    } else if(label.find( "hltTripleMuL3PreFiltered0" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[4] = true;
    } else if(label.find( "hltJpsiMuonL3Filtered" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[5] = true;
    } else if(label.find( "hltDisplacedmumuVtxProducerJpsiMuon" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[6] = true;
    } else if(label.find( "hltVertexmumuFilterJpsiMuon" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Muon_Filters[7] = true;
    } else if(label.find( "hltPreDimuon0Jpsi" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Filters[1] = true;
    } else if(label.find( "hltDimuonL1Filtered0" ) != string::npos ) {
      fHLTP_DoubleMu3_Filters[2] = true;
      fHLTP_Dimuon0_Jpsi_Filters[2] = true;
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[2] = true;
    } else if(label.find( "hltDimuonL2PreFiltered0" ) != string::npos ) {
      fHLTP_DoubleMu3_Filters[3] = true;
      fHLTP_Dimuon0_Jpsi_Filters[3] = true;
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[3] = true;
    } else if(label.find( "hltJpsiL3Filtered" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Filters[4] = true;
    } else if(label.find( "hltDisplacedmumuVtxProducerJpsi0" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Filters[5] = true;
    } else if(label.find( "hltVertexmumuFilterJpsi" ) != string::npos ) {
      fHLTP_Dimuon0_Jpsi_Filters[6] = true;
    } else if(label.find( "hltPreDimuon10JpsiBarrel" ) != string::npos ) {
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[1] = true;
    } else if(label.find( "hltBarrelJpsiL3Filtered" ) != string::npos ) {
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[4] = true;
    } else if(label.find( "hltDisplacedmumuVtxProducerJpsiBarrel" ) != string::npos ) {
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[5] = true;
    } else if(label.find( "hltVertexmumuFilterJpsiBarrel" ) != string::npos ) {
      fHLTP_Dimuon10_Jpsi_Barrel_Filters[6] = true;
    } else if(label.find( "hltPreDoubleMu3" ) != string::npos ) {
      fHLTP_DoubleMu3_Filters[1] = true;
    } else if(label.find( "hltDiMuonL3PreFiltered3" ) != string::npos ) {
      fHLTP_DoubleMu3_Filters[4] = true;
    } else if(label.find( "hltL1sL1DoubleMu3" ) != string::npos ) {
      fHLTP_DoubleMu6_Filters[0] = true;
      fHLTP_DoubleMu7_Filters[0] = true;
      fHLTP_TripleMu5_Filters[0] = true;
    } else if(label.find( "hltPreDoubleMu6" ) != string::npos ) {
      fHLTP_DoubleMu6_Filters[1] = true;
    } else if(label.find( "hltPreDoubleMu7" ) != string::npos ) {
      fHLTP_DoubleMu7_Filters[1] = true;
    } else if(label.find( "hltPreTripleMu5" ) != string::npos ) {
      fHLTP_TripleMu5_Filters[1] = true;
    } else if(label.find( "hltL1DoubleMuon3L1Filtered0" ) != string::npos ) {
      fHLTP_DoubleMu6_Filters[2] = true;
      fHLTP_DoubleMu7_Filters[2] = true;
    } else if(label.find( "hltDiMuon3L2PreFiltered0" ) != string::npos ) {
      fHLTP_DoubleMu6_Filters[3] = true;
      fHLTP_DoubleMu7_Filters[3] = true;
    } else if(label.find( "hltDiMuonL3PreFiltered6" ) != string::npos ) {
      fHLTP_DoubleMu6_Filters[4] = true;
    } else if(label.find( "hltDiMuonL3PreFiltered7" ) != string::npos ) {
      fHLTP_DoubleMu7_Filters[4] = true;
    } else if(label.find( "hltL1DoubleMu3L1TriMuFiltered3" ) != string::npos ) {
      fHLTP_TripleMu5_Filters[2] = true;
    } else if(label.find( "hltL1DoubleMu3L2TriMuFiltered3" ) != string::npos ) {
      fHLTP_TripleMu5_Filters[3] = true;
    } else if(label.find( "hltL1DoubleMu3L3TriMuFiltered5" ) != string::npos ) {
      fHLTP_TripleMu5_Filters[4] = true;
    }
  }
}


void PATEventTree::fillHLT(const pat::TriggerObjectStandAloneCollection& HLTObjects) {

  for ( int ih = 0; ih < (int) HLTObjects.size(); ih++) {
    if ( fHLTN > HLTMAX-1 ) break;

    fHLT_Index[fHLTN] = fHLTN;
    fHLT_PdgId[fHLTN] = HLTObjects[fHLTN].pdgId();
    fHLT_Mass[fHLTN] = HLTObjects[fHLTN].mass();
    fHLT_Energy[fHLTN] = HLTObjects[fHLTN].energy();
    fHLT_Et[fHLTN] = HLTObjects[fHLTN].et();
    fHLT_P[fHLTN] = HLTObjects[fHLTN].p();
    fHLT_Pt[fHLTN] = HLTObjects[fHLTN].pt();
    fHLT_Px[fHLTN] = HLTObjects[fHLTN].px();
    fHLT_Py[fHLTN] = HLTObjects[fHLTN].py();
    fHLT_Pz[fHLTN] = HLTObjects[fHLTN].pz();
    fHLT_Theta[fHLTN] = HLTObjects[fHLTN].theta();
    fHLT_Eta[fHLTN] = HLTObjects[fHLTN].eta();
    fHLT_Phi[fHLTN] = HLTObjects[fHLTN].phi();

    // See if Mu trigger was detected
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu12_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu12_v3", false, false) ) fHLT_Mu12[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu15_v2", false, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu15_v4", false, false) ) fHLT_Mu15[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu20_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu20_v3", false, false) ) fHLT_Mu20[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu24_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu24_v3", false, false) ) fHLT_Mu24[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu30_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu30_v3", false, false) ) fHLT_Mu30[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu12_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu12_v5", false, false) ) fHLT_IsoMu12[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu15_v5", false, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu15_v9", false, false) ) fHLT_IsoMu15[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu17_v5", false, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu17_v9", false, false) ) fHLT_IsoMu17[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu24_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu24_v5", false, false) ) fHLT_IsoMu24[fHLTN][0] = fHLT_Mu[fHLTN][0] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu30_v1", false, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu30_v5", false, false) ) fHLT_IsoMu30[fHLTN][0] = fHLT_Mu[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_DoubleMu3_v7", false, false) ) fHLT_DoubleMu3[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_DoubleMu6_v5", false, false) ) fHLT_DoubleMu6[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_DoubleMu7_v5", false, false) ) fHLT_DoubleMu7[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Jpsi_Muon_v4", false, false) ) fHLT_Dimuon0_Jpsi_Muon[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Jpsi_v3", false, false) ) fHLT_Dimuon0_Jpsi[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon7_Jpsi_Displaced_v3", false, false) ) fHLT_Dimuon7_Jpsi_Displaced[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon10_Jpsi_Barrel_v3", false, false) ) fHLT_Dimuon10_Jpsi_Barrel[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_TripleMu5_v6", false, false) ) fHLT_TripleMu5[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon7_Jpsi_X_Barrel_v3", false, false) ) fHLT_Dimuon7_Jpsi_X_Barrel[fHLTN][0] = true;

    if( HLTObjects[fHLTN].hasPathName("HLT_Mu12_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu12_v3", true, false) ) fHLT_Mu12[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu15_v2", true, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu15_v4", true, false) ) fHLT_Mu15[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu20_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu20_v3", true, false) ) fHLT_Mu20[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu24_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu24_v3", true, false) ) fHLT_Mu24[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_Mu30_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_Mu30_v3", true, false) ) fHLT_Mu30[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu12_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu12_v5", true, false) ) fHLT_IsoMu12[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu15_v5", true, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu15_v9", true, false) ) fHLT_IsoMu15[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu17_v5", true, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu17_v9", true, false) ) fHLT_IsoMu17[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu24_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu24_v5", true, false) ) fHLT_IsoMu24[fHLTN][1] = fHLT_Mu[fHLTN][1] = true; 
    if( HLTObjects[fHLTN].hasPathName("HLT_IsoMu30_v1", true, false) || HLTObjects[fHLTN].hasPathName("HLT_IsoMu30_v5", true, false) ) fHLT_IsoMu30[fHLTN][1] = fHLT_Mu[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_DoubleMu3_v7", true, false) ) fHLT_DoubleMu3[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_DoubleMu6_v5", true, false) ) fHLT_DoubleMu6[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_DoubleMu7_v5", true, false) ) fHLT_DoubleMu7[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Jpsi_Muon_v4", true, false) ) fHLT_Dimuon0_Jpsi_Muon[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Upsilon_Muon", true, false) ) fHLT_Dimuon0_Upsilon_Muon[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Jpsi_v3", true, false) ) fHLT_Dimuon0_Jpsi[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon7_Jpsi_Displaced_v3", true, false) ) fHLT_Dimuon7_Jpsi_Displaced[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon10_Jpsi_Barrel_v3", true, false) ) fHLT_Dimuon10_Jpsi_Barrel[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_TripleMu5_v6", true, false) ) fHLT_TripleMu5[fHLTN][1] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon7_Jpsi_X_Barrel_v3", true, false) ) fHLT_Dimuon7_Jpsi_X_Barrel[fHLTN][1] = true;

    // See if Jet trigger was detected
    if(
      HLTObjects[fHLTN].hasPathName("HLT_Jet30_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet30_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet60_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet60_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet80_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet80_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet110_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet110_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet150_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet150_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet190_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet190_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet240_v1", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet240_v4", false, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet370_v1", false, false) ) {
      fHLT_Jet[fHLTN][0] = true; 
    } if(
      HLTObjects[fHLTN].hasPathName("HLT_Jet30_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet30_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet60_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet60_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet80_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet80_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet110_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet110_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet150_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet150_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet190_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet190_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet240_v1", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet240_v4", true, false) ||
      HLTObjects[fHLTN].hasPathName("HLT_Jet370_v1", true, false) ) {
      fHLT_Jet[fHLTN][1] = true; 
    }
    fHLTN++;
  }
}


void PATEventTree::fillGen(const std::vector<GenParticle>& genColl) {

  for ( unsigned int ig = 0; ig < genColl.size(); ig++) {
    if ( fGnN > GENMAX-1 ) break;

    fGnIndex[fGnN] = fGnN;
    if( genColl[fGnN].isJet() ) fGnIsJet[fGnN]=1;
    else fGnIsJet[fGnN]=0;
    if( genColl[fGnN].longLived() ) fGnLongLived[fGnN]=1;
    else fGnLongLived[fGnN]=0;
    fGnPdgId[fGnN] = (int) genColl[fGnN].pdgId();
    fGnNMothers[fGnN] = (int) genColl[fGnN].numberOfMothers();
    fGnNDaughters[fGnN] = (int) genColl[fGnN].numberOfDaughters();
    fGnCharge[fGnN] = (float) genColl[fGnN].charge();
    fGnPhi[fGnN] = (float) genColl[fGnN].phi();
    fGnTheta[fGnN] = (float) genColl[fGnN].theta();
    fGnEta[fGnN] = (float) genColl[fGnN].eta();
    fGnRapidity[fGnN] = (float) genColl[fGnN].rapidity();
    fGnP[fGnN] = (float) genColl[fGnN].p();
    fGnPt[fGnN] = (float) genColl[fGnN].pt();
    fGnPx[fGnN] = (float) genColl[fGnN].px();
    fGnPy[fGnN] = (float) genColl[fGnN].py();
    fGnPz[fGnN] = (float) genColl[fGnN].pz();
    fGnEnergy[fGnN] = (float) genColl[fGnN].energy();
    fGnEt[fGnN] = (float) genColl[fGnN].et();
    fGnMass[fGnN] = (float) genColl[fGnN].mass();
    fGnMt[fGnN] = (float) genColl[fGnN].mt();
    fGnVx[fGnN] = (float) genColl[fGnN].vx();
    fGnVy[fGnN] = (float) genColl[fGnN].vy();
    fGnVz[fGnN] = (float) genColl[fGnN].vz();

    fGnN++;
  }

  // loop over candidates again to find daughters and mothers
  for ( int ig = 0; ig < fGnN; ig++) {

    for( int im = 0; im < fGnNMothers[ig]; im++) {
      if( im == MOTHERMAX ) break;

      // set cand equal to imth mother of ith particle
      const Candidate* mother = genColl[ig].mother( (unsigned int) im );
      for ( int ig2 = (fGnN-1); ig2 >= 0; ig2-- ) {
        if( ((int)mother->pdgId()==fGnPdgId[ig2]) && ((int)mother->numberOfDaughters()==fGnNDaughters[ig2])
          && ((float)mother->px()==fGnPx[ig2]) && ((float)mother->py()==fGnPy[ig2])
          && ((float)mother->pz()==fGnPz[ig2]) && ((float)mother->vx()==fGnVx[ig2])
          && ((float)mother->vy()==fGnVy[ig2]) && ((float)mother->vz()==fGnVz[ig2]) ) fGnMotherIndex[ig][im]=fGnIndex[ig2];
      }
    }

    // identify end state B-hadrons
    bool EndStateB = false;
    int PdgId = abs(fGnPdgId[ig]);
    if (PdgId==511||PdgId==521||PdgId==10511||PdgId==10521||PdgId==513||PdgId==523||PdgId==10513||PdgId==10523||PdgId==20513||PdgId==20523||PdgId==515||PdgId==525||PdgId==531||PdgId==10531||PdgId==551||PdgId==10551||PdgId==100551||PdgId==110551||PdgId==200551||PdgId==210551||PdgId==553||PdgId==10553||PdgId==20553||PdgId==30553||PdgId==100553||PdgId==110553||PdgId==120553||PdgId==130553||PdgId==200553||PdgId==210553||PdgId==220553||PdgId==300553||PdgId==9000553||PdgId==9010553||PdgId==555||PdgId==10555||PdgId==20555||PdgId==100555||PdgId==110555||PdgId==120555||PdgId==200555||PdgId==5122||PdgId==5112||PdgId==5212||PdgId==5222||PdgId==5114||PdgId==5214||PdgId==5224||PdgId==5132||PdgId==5232||PdgId==5312||PdgId==5322||PdgId==5314||PdgId==5324||PdgId==5332||PdgId==5334||PdgId==5142||PdgId==5242||PdgId==5412||PdgId==5422||PdgId==5414||PdgId==5424||PdgId==5342||PdgId==5432||PdgId==5434||PdgId==5442||PdgId==5444||PdgId==5512||PdgId==5522||PdgId==5514||PdgId==5524||PdgId==5542||PdgId==5544||PdgId==554||PdgId==557||PdgId==100557||PdgId==533||PdgId==10533||PdgId==20533||PdgId==535||PdgId==541||PdgId==10541||PdgId==543||PdgId==10543||PdgId==20543||PdgId==545) EndStateB = true;

    for( int id = 0; id < fGnNDaughters[ig]; id++ ) {
      if( id == DAUGHTERMAX ) break;

      // set cand equal to idth daughter of ith particle
      const Candidate* daughter = genColl[ig].daughter( (unsigned int) id );
      for ( int ig2 = 0; ig2 < fGnN; ig2++ ) {
        if( ((int)daughter->pdgId()==fGnPdgId[ig2]) && ((int)daughter->numberOfDaughters()==fGnNDaughters[ig2])
          && ((float)daughter->px()==fGnPx[ig2]) && ((float)daughter->py()==fGnPy[ig2]) 
          && ((float)daughter->pz()==fGnPz[ig2]) && ((float)daughter->vx()==fGnVx[ig2]) 
          && ((float)daughter->vy()==fGnVy[ig2]) && ((float)daughter->vz()==fGnVz[ig2]) ) {
          fGnDaughterIndex[ig][id]=fGnIndex[ig2];

          // only consider end state B-hadrons, so veto if daughter is B-hadron
          PdgId = abs(fGnPdgId[ig2]);
          if (PdgId==511||PdgId==521||PdgId==10511||PdgId==10521||PdgId==513||PdgId==523||PdgId==10513||PdgId==10523||PdgId==20513||PdgId==20523||PdgId==515||PdgId==525||PdgId==531||PdgId==10531||PdgId==551||PdgId==10551||PdgId==100551||PdgId==110551||PdgId==200551||PdgId==210551||PdgId==553||PdgId==10553||PdgId==20553||PdgId==30553||PdgId==100553||PdgId==110553||PdgId==120553||PdgId==130553||PdgId==200553||PdgId==210553||PdgId==220553||PdgId==300553||PdgId==9000553||PdgId==9010553||PdgId==555||PdgId==10555||PdgId==20555||PdgId==100555||PdgId==110555||PdgId==120555||PdgId==200555||PdgId==5122||PdgId==5112||PdgId==5212||PdgId==5222||PdgId==5114||PdgId==5214||PdgId==5224||PdgId==5132||PdgId==5232||PdgId==5312||PdgId==5322||PdgId==5314||PdgId==5324||PdgId==5332||PdgId==5334||PdgId==5142||PdgId==5242||PdgId==5412||PdgId==5422||PdgId==5414||PdgId==5424||PdgId==5342||PdgId==5432||PdgId==5434||PdgId==5442||PdgId==5444||PdgId==5512||PdgId==5522||PdgId==5514||PdgId==5524||PdgId==5542||PdgId==5544||PdgId==554||PdgId==557||PdgId==100557||PdgId==533||PdgId==10533||PdgId==20533||PdgId==535||PdgId==541||PdgId==10541||PdgId==543||PdgId==10543||PdgId==20543||PdgId==545) EndStateB = false;
        } // end if (cuts to make sure particles are the same)
      } // end loop over Gen particles
    } // end loop over daughters

    if (EndStateB) { fGnBIndex[fGnBN]=ig; fGnBN++; }

    // find flight distance and lifetime info for particles
    if (fGnNDaughters[ig]>0) {
      float dx, dy, dz, beta, gamma;
      dx = fGnVx[ig]-fGnVx[fGnDaughterIndex[ig][0]]; dy = fGnVy[ig]-fGnVy[fGnDaughterIndex[ig][0]]; dz = fGnVz[ig]-fGnVz[fGnDaughterIndex[ig][0]];
      beta = fGnP[ig]/fGnEnergy[ig];
      if (beta<1.0) gamma = 1.0/sqrt(1.0-beta*beta); // avoid NAN DistCM values
      else gamma = 99999;
      fGnDist[ig] = sqrt(dx*dx+dy*dy+dz*dz);
      fGnTau[ig] = fGnDist[ig]/(beta*29979245800.0);
      fGnDistCM[ig] = gamma*fGnDist[ig];
      fGnTauCM[ig] = fGnTau[ig]/gamma;
    }
  }
}


void PATEventTree::fillParticles(const std::vector<pat::Muon>& muons, const std::vector<reco::Track>& ctftracks ){

  int TkI;  // the index of the underlying ctf track
	fgsmN = fgsmmN = fgtmN = 0;
  for (int i = 0; i != (int) muons.size(); i++) {
    if (fPcN > PARTMAX - 1) break;

    if (muons[fMuN].track().isNonnull()) TkI = (int) muons[fMuN].track().index();
    else if (muons[fMuN].innerTrack().isNonnull()) TkI = (int) muons[fMuN].innerTrack().index();
    else continue;  // skip if I can't associate to ctftrack

    // associate to gen particles (iterating from the back for speed and to ensure a final state particle)
    if (fIsMC&&muons[fMuN].genParticleRef().isNonnull()) {
      for (int ig = fGnN-1; ig >= 0; ig--) {
        if (fGnPdgId[ig]==(int) muons[fMuN].genParticleRef()->pdgId() && fGnPt[ig]==(float) muons[fMuN].genParticleRef()->pt() && fGnEta[ig]==(float) muons[fMuN].genParticleRef()->eta()) { fPcToGn[fPcN] = ig; break; }
      }
    }
    fPcToTk[fPcN] = TkI;
    fTkToPc[TkI] = fPcN;
    fPcIndex[fPcN] = fPcN;
    fMuIndex[fMuN] = fPcN;
    fPcPdgId[fPcN] = (int) muons[fMuN].pdgId();
    fPcCharge[fPcN] = (float) muons[fMuN].charge();
    fPcEnergy[fPcN] = (float) muons[fMuN].energy();
    fPcEt[fPcN] = (float) muons[fMuN].et();
    fPcP[fPcN] = (float) muons[fMuN].p();
    fPcPt[fPcN] = (float) muons[fMuN].pt();
    fPcPx[fPcN] = (float) muons[fMuN].px();
    fPcPy[fPcN] = (float) muons[fMuN].py();
    fPcPz[fPcN] = (float) muons[fMuN].pz();
    fPcTheta[fPcN] = (float) muons[fMuN].theta();
    fPcEta[fPcN] = (float) muons[fMuN].eta();
    fPcPhi[fPcN] = (float) muons[fMuN].phi();
    fPcVx[fPcN] = (float) muons[fMuN].vx();
    fPcVy[fPcN] = (float) muons[fMuN].vy();
    fPcVz[fPcN] = (float) muons[fMuN].vz();
    fPcEcalIso[fPcN] = (float) muons[fMuN].ecalIso();
    fPcHcalIso[fPcN] = (float) muons[fMuN].hcalIso();
    fPcTrackIso[fPcN] = (float) muons[fMuN].trackIso();

    fPcTkQuality[fPcN] = (int) ctftracks[TkI].qualityMask();
    fPcChi2[fPcN] = (float) ctftracks[TkI].chi2();
    fPcNdof[fPcN] = (float) ctftracks[TkI].ndof();
    fPcD0[fPcN] = (float) ctftracks[TkI].d0();
    fPcDz[fPcN] = (float) ctftracks[TkI].dz();
    fPcEtaErr[fPcN] = (float) ctftracks[TkI].etaError();
    fPcPhiErr[fPcN] = (float) ctftracks[TkI].phiError();
    fPcD0Err[fPcN] = (float) ctftracks[TkI].d0Error();
    fPcDzErr[fPcN] = (float) ctftracks[TkI].dzError();
    // hit pattern of the innerTrack
    const reco::HitPattern& hits = ctftracks[TkI].hitPattern();
    fPcPixHitN[fPcN] = (int) hits.numberOfValidPixelHits();
    fPcPixLayN[fPcN] = (int) hits.pixelLayersWithMeasurement();
    fPcStripHitN[fPcN] = (int) hits.numberOfValidStripHits();
    fPcStripLayN[fPcN] = (int) hits.stripLayersWithMeasurement();

    //-- HLT info
    // L3 muon object match to muons
    TriggerObjectStandAloneCollection L3mu_match = muons[fMuN].triggerObjectMatchesByFilter("hltTripleMuL3PreFiltered0");
    if( L3mu_match.size() != 0 ) fMuL3Match[fMuN] = true;

    // Muon match to objects at the last stage of HLT filter
    TriggerObjectStandAloneCollection MuHLTmatches = muons[fMuN].triggerObjectMatches();
    if(MuHLTmatches.size()>0) {
      fMuHLTN[fMuN] = (int) MuHLTmatches.size();
      for (int imh = 0; imh < (int) MuHLTmatches.size(); imh++) {
        for (int ih = 0; ih < (int) fHLTN; ih++) {
          if(fabs(MuHLTmatches[imh].pt()-fHLT_Pt[ih])<0.001 && fabs(MuHLTmatches[imh].eta()-fHLT_Eta[ih])<0.001 && fabs(MuHLTmatches[imh].phi()-fHLT_Phi[ih])<0.001) { fMuToHLT[fMuN] = ih; fHLT_ToPc[ih] = fPcN; break; }
        }
      }
      if(fMuToHLT[fMuN]>=0) {
        if( fHLT_Mu[fMuToHLT[fMuN]][0] ) fMuHLTMatch[fMuN][0] = true;
        if( fHLT_Mu[fMuToHLT[fMuN]][1] ) fMuHLTMatch[fMuN][1] = true;
      }
    }
    // muon specific
    fMuHitN[fMuN] = muons[fMuN].numberOfChambers();
//    fMuChambers[fMuN]  = muons[fMuN].Chambers();
    fMuMatchedN[fMuN] = muons[fMuN].numberOfMatches();
    fMuMatchedNSegArb[fMuN] = muons[fMuN].numberOfMatches(reco::Muon::SegmentArbitration);
    fMuMatchedNSegTrkArb[fMuN] = muons[fMuN].numberOfMatches(reco::Muon::SegmentAndTrackArbitration);
    fMuMatchedNSegTrkArbClean[fMuN] = muons[fMuN].numberOfMatches(reco::Muon::SegmentAndTrackArbitrationCleaned);
    fMuIsGlobal[fMuN] = muons[fMuN].isGlobalMuon();
    fMuIsTracker[fMuN] = muons[fMuN].isTrackerMuon();
    fMuIsStandalone[fMuN] = muons[fMuN].isStandAloneMuon();
    fMuIsCalo[fMuN] = muons[fMuN].isCaloMuon();
    fMuArbitrated[fMuN] = muons[fMuN].muonID("TrackerMuonArbitrated");
    fMuLastStationLoose[fMuN] = muons[fMuN].muonID("TMLastStationLoose");
    fMuLastStationTight[fMuN] = muons[fMuN].muonID("TMLastStationTight");
    fMu2DCompatibilityLoose[fMuN] = muons[fMuN].muonID("TM2DCompatibilityLoose");
    fMu2DCompatibilityTight[fMuN] = muons[fMuN].muonID("TM2DCompatibilityTight");
    fMuOneStationLoose[fMuN] = muons[fMuN].muonID("TMOneStationLoose");
    fMuOneStationTight[fMuN] = muons[fMuN].muonID("TMOneStationTight");
		fMuIsHighPurity[fMuN] = ctftracks[TkI].quality(reco::TrackBase::highPurity);
		
    // global fit info
    if( muons[fMuN].globalTrack().isNonnull() ) {
      fMuChi2[fMuN] = muons[fMuN].globalTrack()->chi2();
      fMuNdof[fMuN] = muons[fMuN].globalTrack()->ndof();
    }
    // muon quality info
    if( muons[fMuN].isQualityValid() ) {
      fMuTkKink[fMuN] = muons[fMuN].combinedQuality().trkKink;
      fMuGlbKink[fMuN] = muons[fMuN].combinedQuality().glbKink;
      fMuGlbProb[fMuN] = muons[fMuN].combinedQuality().glbTrackProbability;
      fMuTkSADist[fMuN] = muons[fMuN].combinedQuality().localDistance;
      fMuTkSAdR[fMuN] = muons[fMuN].combinedQuality().globalDeltaEtaPhi;
      fMuTightMatch[fMuN] = muons[fMuN].combinedQuality().tightMatch;
    }
    // muon energy info
    if( muons[fMuN].isEnergyValid() ) {
      fMuECALEnergy[fMuN] = muons[fMuN].calEnergy().em;
      fMuHCALEnergy[fMuN] = muons[fMuN].calEnergy().had;
    }
    fMuCalCompat[fMuN] = muons[fMuN].caloCompatibility();

		if (muon::isGoodMuon(muons[fMuN],muon::SelectionType(12))
				&& fPcPixLayN[fPcN] > 0 
				&& fPcStripLayN[fPcN]>5 
				&& fMuIsHighPurity[fMuN]
				&& fPcD0[fPcN] < 0.3
				&& fPcDz[fPcN] < 20.0)
				{fgoodSoftMuon[fMuN] = 1; fgsmN++;}
		if (muon::isGoodMuon(muons[fMuN],muon::SelectionType(11))
				&& fPcPixLayN[fPcN] > 0 
				&& fPcStripLayN[fPcN]>5 
				&& fMuIsHighPurity[fMuN]
				&& fPcD0[fPcN] < 0.3
				&& fPcDz[fPcN] < 20.0)
				{fgoodSoftMuonMod[fMuN] = 1; fgsmmN++;}
		if (fMuIsGlobal[fMuN]
				&& muons[fMuN].isPFMuon()
				&& fMuChi2[fMuN] < 2
				&& muons[fMuN].globalTrack()->hitPattern().numberOfValidMuonHits()>0
				&& muons[fMuN].numberOfMatchedStations()>1
				&& fabs(muons[fMuN].muonBestTrack()->d0()) < 0.2
				&& fabs(muons[fMuN].muonBestTrack()->dz()) < 0.5
				&& fPcPixHitN[fPcN] > 0 
				&& fPcStripLayN[fPcN] > 5 )
				{fgoodTightMuon[fMuN] = 1; fgtmN++;}



    fMuN++;
    fPcN++;
  }
}
void PATEventTree::fillPrimaryVertices(const std::vector<Vertex>& vertices) {

  for (unsigned int i = 0; i != vertices.size(); i++) {
    if (fAllPvN > PVMAX - 1) break;

    fPvIndex[fAllPvN] = fAllPvN;
    fPvTkN[fAllPvN] = (int) vertices[fAllPvN].tracksSize();
    fPvX[fAllPvN] = (float) vertices[fAllPvN].x();
    fPvY[fAllPvN] = (float) vertices[fAllPvN].y();
    fPvZ[fAllPvN] = (float) vertices[fAllPvN].z();
    fPvXe[fAllPvN] = (float) vertices[fAllPvN].xError();
    fPvYe[fAllPvN] = (float) vertices[fAllPvN].yError();
    fPvZe[fAllPvN] = (float) vertices[fAllPvN].zError();
    fPvChi2[fAllPvN] = (float) vertices[fAllPvN].chi2();
    fPvNdof[fAllPvN] = (float) vertices[fAllPvN].ndof();
    fPvIsFake[fAllPvN] = vertices[fAllPvN].isFake();

    math::XYZTLorentzVectorD pvP4 = vertices[fAllPvN].p4(0.13957018,0);
    fPvPx[fAllPvN] = (float) pvP4.px();
    fPvPy[fAllPvN] = (float) pvP4.py();
    fPvPz[fAllPvN] = (float) pvP4.pz();
    fPvPt[fAllPvN] = (float) pvP4.pt();
    fPvP[fAllPvN] = (float) sqrt( pvP4.pt()*pvP4.pt() + pvP4.pz()*pvP4.pz() );
    fPvEnergy[fAllPvN] = (float) pvP4.energy();
    fPvEta[fAllPvN] = (float) -log(tan(0.5*acos(pvP4.pz()/sqrt(pvP4.px()*pvP4.px()+pvP4.py()*pvP4.py()+pvP4.pz()*pvP4.pz()))));
    fPvMass[fAllPvN] = (float) pvP4.M();

    // loop over all tracks in the vertex
    for(reco::Vertex::trackRef_iterator track = vertices[fAllPvN].tracks_begin(); track != vertices[fAllPvN].tracks_end(); ++track) {
      fPcToPv[fTkToPc[track->key()]] = fPvN;
    }

    fPvN++; fAllPvN++;
  }

  // find closest PV to a given PV
  for (Int_t ip1=0; ip1<fPvN; ip1++) {
    fPvClosestI[ip1] = -9999;
    float DistToClosest = 9999;
    for (Int_t ip2=0; ip2<fPvN; ip2++) {
      if( ip2==ip1 ) continue;
      float DistToPV = sqrt( pow(fPvX[ip1]-fPvX[ip2],2)+pow(fPvY[ip1]-fPvY[ip2],2)+pow(fPvZ[ip1]-fPvZ[ip2],2) );
      if( DistToPV<DistToClosest ) { fPvClosestI[ip1]=ip2; DistToClosest=DistToPV; }
    }
  }
}

void PATEventTree::fillDimuonCand(const reco::CompositeCandidateCollection& JPsiCands, const reco::MuonRefVector& goodMuons, std::vector<TransientTrack>& t_tks) {

  for(unsigned int ijp = 0; ijp < JPsiCands.size(); ijp++) {
    if( fJPsiN == JPsiMAX ) break;
    //if( JPsiCands[fJPsiN].mass()<2.0 || JPsiCands[fJPsiN].mass()>4.0 ) continue; // only consider candidates within a loose J/Psi mass window

    fJPsiIndex[fJPsiN] = fJPsiN;
    fJPsiCharge[fJPsiN] = (float) JPsiCands[fJPsiN].charge();
    fJPsiPhi[fJPsiN] = (float) JPsiCands[fJPsiN].phi();
    fJPsiTheta[fJPsiN] = (float) JPsiCands[fJPsiN].theta();
    fJPsiEta[fJPsiN] = (float) JPsiCands[fJPsiN].eta();
    fJPsiRapidity[fJPsiN] = (float) JPsiCands[fJPsiN].rapidity();
    fJPsiP[fJPsiN] = (float) JPsiCands[fJPsiN].p();
    fJPsiPt[fJPsiN] = (float) JPsiCands[fJPsiN].pt();
    fJPsiPx[fJPsiN] = (float) JPsiCands[fJPsiN].px();
    fJPsiPy[fJPsiN] = (float) JPsiCands[fJPsiN].py();
    fJPsiPz[fJPsiN] = (float) JPsiCands[fJPsiN].pz();
    fJPsiEnergy[fJPsiN] = (float) JPsiCands[fJPsiN].energy();
    fJPsiEt[fJPsiN] = (float) JPsiCands[fJPsiN].et();
    fJPsiMass[fJPsiN] = (float) JPsiCands[fJPsiN].mass();
    fJPsiMt[fJPsiN] = (float) JPsiCands[fJPsiN].mt();

    for(unsigned int ijpd = 0; ijpd < JPsiCands[fJPsiN].numberOfDaughters(); ijpd++) {
      if( ijpd==2 ) { cout<<"more than 2 JPsi daughters!"<<endl; break; }
      
      const Candidate* daughter = JPsiCands[fJPsiN].daughter( ijpd );
      int MuI = -9999, TkI = -9999;
      for (int igm = 0; igm < (int) goodMuons.size(); igm++) {
        if( (fabs((float)daughter->px()-goodMuons[igm]->px())<0.001) && (fabs((float)daughter->py()-goodMuons[igm]->py())<0.001) && (fabs((float)daughter->pz()-goodMuons[igm]->pz())<0.001) ) { MuI = igm; break; }
      }
      if( MuI < 0 ) continue;
      if(goodMuons[MuI]->track().isNonnull()) TkI = (int) goodMuons[MuI]->track().index();
      else TkI=-9999;
      if( TkI>=0 ) fJPsiMuI[fJPsiN][ijpd]=fTkToPc[TkI];
      // Quality cut variables
      bool KinGood = false, HLTGood = false, IsoGood = false, SAGood = false, TrkGood = false;
      if( goodMuons[MuI]->pt()>20. && fabs(goodMuons[MuI]->eta())<2.1 ) KinGood = fJPsiMuCutKin[fJPsiN][ijpd] = true;
      if( TkI>=0 && fTkToPc[TkI]<fMuN && fMuHLTMatch[fTkToPc[TkI]][1] ) HLTGood = fJPsiMuCutHLT[fJPsiN][ijpd] = true;
      if( goodMuons[MuI]->isolationR03().sumPt/goodMuons[MuI]->pt()<0.15 ) IsoGood = fJPsiMuCutIso[fJPsiN][ijpd] = true;
      if( goodMuons[MuI]->numberOfChambers()>=1 && goodMuons[MuI]->numberOfMatches()>=2 ) SAGood = fJPsiMuCutSA[fJPsiN][ijpd] = true;
      if( TkI>=0 && fPcPixHitN[fTkToPc[TkI]]>=1 && (fPcPixHitN[fTkToPc[TkI]]+fPcStripHitN[fTkToPc[TkI]])>=11 ) TrkGood = fJPsiMuCutTrk[fJPsiN][ijpd] = true;
      // Determine quality of daughter
      if( KinGood && HLTGood && IsoGood && TrkGood && SAGood ) { fJPsiMuCategory[fJPsiN][ijpd] = 1; fJPsiMuType[fJPsiN][ijpd][0] = true; }
      else if( KinGood && IsoGood && TrkGood && SAGood ) { fJPsiMuCategory[fJPsiN][ijpd] = 2; fJPsiMuType[fJPsiN][ijpd][1] = true; }
      else if( KinGood && TrkGood && SAGood ) { fJPsiMuCategory[fJPsiN][ijpd] = 3; fJPsiMuType[fJPsiN][ijpd][2] = true; }
      else if( KinGood && IsoGood && SAGood ) { fJPsiMuCategory[fJPsiN][ijpd] = 4; fJPsiMuType[fJPsiN][ijpd][3] = true; }
      else if( KinGood && IsoGood && TrkGood ) { fJPsiMuCategory[fJPsiN][ijpd] = 5; fJPsiMuType[fJPsiN][ijpd][4] = true; }
    } // end loop over daughters
    // set BaseJPsiI = index of highest Pt JPsi whose muons pass basic cuts
    if ( fBaseJPsiI[0]==-9999&&fJPsiMuI[fJPsiN][0]!=-9999&&fJPsiMuI[fJPsiN][1]!=-9999&&fJPsiMuCutSA[fJPsiN][0]&&fJPsiMuCutSA[fJPsiN][1]&&fJPsiMuCutTrk[fJPsiN][0]&&fJPsiMuCutTrk[fJPsiN][1]&&(fJPsiMuCutHLT[fJPsiN][0]||fJPsiMuCutHLT[fJPsiN][1]) ) fBaseJPsiI[0] = fJPsiN;
    else if ( fBaseJPsiI[0]!=-9999&&fBaseJPsiI[1]==-9999&&fJPsiMuI[fJPsiN][0]!=-9999&&fJPsiMuI[fJPsiN][1]!=-9999&&(fJPsiMuI[fJPsiN][0]!=fJPsiMuI[fBaseJPsiI[0]][0]&&fJPsiMuI[fJPsiN][0]!=fJPsiMuI[fBaseJPsiI[0]][1])&&(fJPsiMuI[fJPsiN][1]!=fJPsiMuI[fBaseJPsiI[0]][0]&&fJPsiMuI[fJPsiN][1]!=fJPsiMuI[fBaseJPsiI[0]][1])&&fJPsiMuCutSA[fJPsiN][0]&&fJPsiMuCutSA[fJPsiN][1]&&fJPsiMuCutTrk[fJPsiN][0]&&fJPsiMuCutTrk[fJPsiN][1]&&(fJPsiMuCutHLT[fJPsiN][0]||fJPsiMuCutHLT[fJPsiN][1]) ) fBaseJPsiI[1] = fJPsiN;
    // veto jets if they have muon from JPsi
    if( fJPsiMuCategory[fJPsiN][0]>0 && fJPsiMuCategory[fJPsiN][1]>0 && fJPsiMass[0]>2.8 && fJPsiMass[0]<3.35 ) {
      for(int ij = 0; ij < fJtN; ij++) {
        for(int ijt = 0; ijt < fJtTkN[ij]; ijt++) {
          if( fJtToPc[ij][ijt]>=0 && (fJtToPc[ij][ijt]==fJPsiMuI[fJPsiN][0]||fJtToPc[ij][ijt]==fJPsiMuI[fJPsiN][1]) ) fJtVeto[ij]=true;
        } // end loop over jet tracks
      }  // end loop over jets
    }

    // make J/Psi vertex from muons and fill vertex information
    vector<TransientTrack> mu_tks;
    if( fJPsiMuI[fJPsiN][0]!=-9999 && fPcToTk[fJPsiMuI[fJPsiN][0]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[fJPsiN][0]]]);
    if( fJPsiMuI[fJPsiN][1]!=-9999 && fPcToTk[fJPsiMuI[fJPsiN][1]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[fJPsiN][1]]]);
    if( mu_tks.size() == 2 ) {
      KalmanVertexFitter kvf(true);
      TransientVertex jpsi_cand = kvf.vertex(mu_tks);
      if( jpsi_cand.isValid() ) {
        reco::Vertex jpsi_vtx = jpsi_cand;
        const math::XYZTLorentzVectorD jpsi_mom = jpsi_vtx.p4(0.1056583,0.0);
        fJPsiChi2[fJPsiN]     = (float) jpsi_vtx.chi2();
        fJPsiNdof[fJPsiN]     = (float) jpsi_vtx.ndof();
        fJPsiVx[fJPsiN]       = (float) jpsi_vtx.x();
        fJPsiVy[fJPsiN]       = (float) jpsi_vtx.y();
        fJPsiVz[fJPsiN]       = (float) jpsi_vtx.z();
        fJPsiVxE[fJPsiN]      = (float) jpsi_vtx.xError();
        fJPsiVyE[fJPsiN]      = (float) jpsi_vtx.yError();
        fJPsiVzE[fJPsiN]      = (float) jpsi_vtx.zError();
        fJPsiVtxPx[fJPsiN]    = (float) jpsi_mom.x();
        fJPsiVtxPy[fJPsiN]    = (float) jpsi_mom.y();
        fJPsiVtxPz[fJPsiN]    = (float) jpsi_mom.z();
        fJPsiVtxPt[fJPsiN]    = (float) jpsi_mom.pt();
        fJPsiVtxP[fJPsiN]     = (float) jpsi_mom.P();
        fJPsiVtxEnergy[fJPsiN]= (float) jpsi_mom.energy();
        fJPsiVtxEt[fJPsiN]    = (float) jpsi_mom.Et();
        fJPsiVtxMass[fJPsiN]  = (float) jpsi_mom.mass();
        fJPsiVtxMt[fJPsiN]    = (float) jpsi_mom.mt();
        fJPsiVtxPhi[fJPsiN]   = (float) jpsi_mom.phi();
        fJPsiVtxTheta[fJPsiN] = (float) jpsi_mom.theta();
        fJPsiVtxEta[fJPsiN]   = (float) jpsi_mom.eta();
        fJPsiVtxRapidity[fJPsiN]= (float) jpsi_mom.Rapidity();

        // find closest PV in Z
        float ClosestPVdist = 9999;
        fJPsiClosestPVinZ[fJPsiN] = 0;
        for( int ip = 0; ip < fPvN; ip++ ) {
          float distZ = fabs( fJPsiVz[fJPsiN]-fPvZ[ip] );
          if( ClosestPVdist > distZ ) { 
            fJPsiClosestPVinZ[fJPsiN] = ip;
            ClosestPVdist = fabs( fJPsiVz[fJPsiN]-fPvZ[ip] );
	  }
	}
      }
    }
    fJPsiN++;
  } // end loop over JPsi candidates
}

void PATEventTree::makeEtabCand(std::vector<TransientTrack>& t_tks) {

  for(int ijp1 = 0; ijp1 < fJPsiMuMuN-1; ijp1++) {
    if( fEtabN == ETABMAX ) break;

    for(int ijp2 = ijp1+1; ijp2 < fJPsiMuMuN; ijp2++) {
      if( fEtabN == ETABMAX ) break;
      if( fJPsiMuI[ijp1][0]==-9999 || fJPsiMuI[ijp1][1]==-9999 || fJPsiMuI[ijp2][0]==-9999 || fJPsiMuI[ijp2][1]==-9999 ) continue; // only consider muons we can find
      if( fJPsiMuI[ijp1][0]==fJPsiMuI[ijp2][0] || fJPsiMuI[ijp1][0]==fJPsiMuI[ijp2][1] || fJPsiMuI[ijp1][1]==fJPsiMuI[ijp2][0] || fJPsiMuI[ijp1][1]==fJPsiMuI[ijp2][1] ) continue; // no sharing muons b/t J/Psi cands

      float ze1 = fJPsiEnergy[ijp1], zpx1 = fJPsiPx[ijp1], zpy1 = fJPsiPy[ijp1], zpz1 = fJPsiPz[ijp1], ze2 = fJPsiEnergy[ijp2], zpx2 = fJPsiPx[ijp2], zpy2 = fJPsiPy[ijp2], zpz2 = fJPsiPz[ijp2];
      float etabe = ze1+ze2, etabpx = zpx1+zpx2, etabpy = zpy1+zpy2, etabpz = zpz1+zpz2;
      float etabmass = sqrt(etabe*etabe-etabpx*etabpx-etabpy*etabpy-etabpz*etabpz);

      fEtabIndex[fEtabN] = fEtabN;
      fEtabPx[fEtabN] = etabpx;
      fEtabPy[fEtabN] = etabpy;
      fEtabPz[fEtabN] = etabpz;
      fEtabPt[fEtabN] = sqrt(etabpx*etabpx+etabpy*etabpy);
      fEtabP[fEtabN] = sqrt(etabpx*etabpx+etabpy*etabpy+etabpz*etabpz);
      fEtabEt[fEtabN] = fJPsiEt[ijp1]+fJPsiEt[ijp2];
      fEtabEnergy[fEtabN] = etabe;
      fEtabMt[fEtabN] = fJPsiMt[ijp1]+fJPsiMt[ijp2];
      fEtabMass[fEtabN] = etabmass;
      if( etabpx>0 ) fEtabPhi[fEtabN] = atan(etabpy/etabpx);
      else fEtabPhi[fEtabN] = atan(etabpy/etabpx)+etabpy/fabs(etabpy)*3.14159265;
      if( etabpz>0 ) fEtabTheta[fEtabN] = atan(fEtabPt[fEtabN]/etabpz);
      else fEtabTheta[fEtabN] = atan(fEtabPt[fEtabN]/etabpz)+3.14159265;
      if( fEtabP[fEtabN]==fabs(etabpz) ) fEtabEta[fEtabN] = 9999.0*etabpz/fabs(etabpz);
      else fEtabEta[fEtabN] = 0.5*log((fEtabP[fEtabN]+etabpz)/(fEtabP[fEtabN]-etabpz));
      if( etabe==fabs(etabpz) ) fEtabRapidity[fEtabN] = 9999.0*etabpz/fabs(etabpz);
      else fEtabRapidity[fEtabN] = 0.5*log((etabe+etabpz)/(etabe-etabpz));
      fEtabJPsiI[fEtabN][0]=ijp1;
      fEtabJPsiI[fEtabN][1]=ijp2;
      fEtabMuI[fEtabN][0]=fJPsiMuI[ijp1][0];
      fEtabMuI[fEtabN][1]=fJPsiMuI[ijp1][1];
      fEtabMuI[fEtabN][2]=fJPsiMuI[ijp2][0];
      fEtabMuI[fEtabN][3]=fJPsiMuI[ijp2][1];
      if( ijp1<fJPsiMuMuN ) fEtabMuN[fEtabN] += 2;
      else fEtabMuN[fEtabN] += 1;
      if( ijp2<fJPsiMuMuN ) fEtabMuN[fEtabN] += 2;
      else fEtabMuN[fEtabN] += 1;

      // check if another Eta_b candidate shares the same muons
      bool sameMu[4];
      for(int ie = 0; ie < fEtabN; ie++) { // iterate over earlier eta_b
        for(int i = 0; i < 4; i++) sameMu[i]=false;
        for(int imu1 = 0; imu1 < 4; imu1++) { // muons in earlier eta_b
          for(int imu2 = 0; imu2 < 4; imu2++) { // muons in this eta_b
            if( fEtabMuI[ie][imu1]==fEtabMuI[fEtabN][imu2] ) sameMu[imu2]=true;
	  }
	}
        if( sameMu[0] && sameMu[1] && sameMu[2] && sameMu[3] ) {
          fEtabDuplicatesI[fEtabN] = ie;
          break;
	}
      }

      // make vertex from muons and fill vertex information
      vector<TransientTrack> mu_tks;
      if( fPcToTk[fJPsiMuI[ijp1][0]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp1][0]]]);
      if( fPcToTk[fJPsiMuI[ijp1][1]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp1][1]]]);
      if( fPcToTk[fJPsiMuI[ijp2][0]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp2][0]]]);
      if( fPcToTk[fJPsiMuI[ijp2][1]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp2][1]]]);

      if( mu_tks.size() == 4 ) {
        KalmanVertexFitter kvf(true);
        TransientVertex etab_cand = kvf.vertex(mu_tks);
        if( etab_cand.isValid() ) {
          reco::Vertex etab_vtx = etab_cand;
          const math::XYZTLorentzVectorD etab_mom = etab_vtx.p4(0.1056583,0.0);
          fEtabChi2[fEtabN]     = (float) etab_vtx.chi2();
          fEtabNdof[fEtabN]     = (float) etab_vtx.ndof();
          fEtabVx[fEtabN]       = (float) etab_vtx.x();
          fEtabVy[fEtabN]       = (float) etab_vtx.y();
          fEtabVz[fEtabN]       = (float) etab_vtx.z();
          fEtabVxE[fEtabN]      = (float) etab_vtx.xError();
          fEtabVyE[fEtabN]      = (float) etab_vtx.yError();
          fEtabVzE[fEtabN]      = (float) etab_vtx.zError();
          fEtabVtxPx[fEtabN]    = (float) etab_mom.x();
          fEtabVtxPy[fEtabN]    = (float) etab_mom.y();
          fEtabVtxPz[fEtabN]    = (float) etab_mom.z();
          fEtabVtxPt[fEtabN]    = (float) etab_mom.pt();
          fEtabVtxP[fEtabN]     = (float) etab_mom.P();
          fEtabVtxEnergy[fEtabN]= (float) etab_mom.energy();
          fEtabVtxEt[fEtabN]    = (float) etab_mom.Et();
          fEtabVtxMass[fEtabN]  = (float) etab_mom.mass();
          fEtabVtxMt[fEtabN]    = (float) etab_mom.mt();
          fEtabVtxPhi[fEtabN]   = (float) etab_mom.phi();
          fEtabVtxTheta[fEtabN] = (float) etab_mom.theta();
          fEtabVtxEta[fEtabN]   = (float) etab_mom.eta();
          fEtabVtxRapidity[fEtabN]=(float) etab_mom.Rapidity();
        }
      }

      // find Eta_b from best J/Psi candidates
      if ( (fBaseJPsiI[0]==ijp1&&fBaseJPsiI[1]==ijp2) || (fBaseJPsiI[1]==ijp1&&fBaseJPsiI[1]==ijp2) ) fBaseEtabI=fEtabN;

      // find perp. and long. distance b/t Eta_b vector and J/Psi
      // refer to http://paulbourke.net/geometry/pointline/
      if( fEtabVx[fEtabN]!=-9999.0 ) {

        // Points at which tangent line between J/Psi and Eta_b vector intersect
        float x1, x2, y1, y2, z1, z2, jpsi1T, jpsi1L, jpsi2T, jpsi2L;
        x1 = x2 = y1 = y2 = z1 = z2 = jpsi1T = jpsi1L = jpsi2T = jpsi2L = -9999.0;
        float px1, py1, pz1, px2, py2, pz2, px3, py3, pz3;
        px1 = fEtabVx[fEtabN]-fEtabPx[fEtabN];
        py1 = fEtabVy[fEtabN]-fEtabPy[fEtabN];
        pz1 = fEtabVz[fEtabN]-fEtabPz[fEtabN];
        px2 = fEtabVx[fEtabN]+fEtabPx[fEtabN];
        py2 = fEtabVy[fEtabN]+fEtabPy[fEtabN];
        pz2 = fEtabVz[fEtabN]+fEtabPz[fEtabN];

        // find 1st J/Psi distances to Eta_b vector
        if( fJPsiVx[ijp1]!=-9999.0 ) {
          px3 = fJPsiVx[fEtabJPsiI[fEtabN][0]];
          py3 = fJPsiVy[fEtabJPsiI[fEtabN][0]];
          pz3 = fJPsiVz[fEtabJPsiI[fEtabN][0]];

          float u = ( (px3-px1)*(px2-px1)+(py3-py1)*(py2-py1)+(pz3-pz1)*(pz2-pz1) )/( (px2-px1)*(px2-px1)+(py2-py1)*(py2-py1)+(pz2-pz1)*(pz2-pz1) );
          fEtabJPsiProjX[fEtabN][0] = x1 = px1 + u*(px2 - px1);
          fEtabJPsiProjY[fEtabN][0] = y1 = py1 + u*(py2 - py1);
          fEtabJPsiProjZ[fEtabN][0] = z1 = pz1 + u*(pz2 - pz1);

          jpsi1T = sqrt( (x1-px3)*(x1-px3)+(y1-py3)*(y1-py3)+(z1-pz3)*(z1-pz3) );
          jpsi1L = sqrt( (x1-fEtabVx[fEtabN])*(x1-fEtabVx[fEtabN])+(y1-fEtabVy[fEtabN])*(y1-fEtabVy[fEtabN])+(z1-fEtabVz[fEtabN])*(z1-fEtabVz[fEtabN]) );
	}

        // find 2nd J/Psi distances to Eta_b vector
        if( fJPsiVx[ijp2]!=-9999.0 ) {
          px3 = fJPsiVx[fEtabJPsiI[fEtabN][1]];
          py3 = fJPsiVy[fEtabJPsiI[fEtabN][1]];
          pz3 = fJPsiVz[fEtabJPsiI[fEtabN][1]];

          float u = ( (px3-px1)*(px2-px1)+(py3-py1)*(py2-py1)+(pz3-pz1)*(pz2-pz1) )/( (px2-px1)*(px2-px1)+(py2-py1)*(py2-py1)+(pz2-pz1)*(pz2-pz1) );
          fEtabJPsiProjX[fEtabN][1] = x2 = px1 + u*(px2 - px1);
          fEtabJPsiProjY[fEtabN][1] = y2 = py1 + u*(py2 - py1);
          fEtabJPsiProjZ[fEtabN][1] = z2 = pz1 + u*(pz2 - pz1);

          jpsi2T = sqrt( (x2-px3)*(x2-px3)+(y2-py3)*(y2-py3)+(z2-pz3)*(z2-pz3) );
          jpsi2L = sqrt( (x2-fEtabVx[fEtabN])*(x2-fEtabVx[fEtabN])+(y2-fEtabVy[fEtabN])*(y2-fEtabVy[fEtabN])+(z2-fEtabVz[fEtabN])*(z2-fEtabVz[fEtabN]) );
	}

        // find J/Psi distances to each other, and error
        if( fJPsiVx[ijp1]!=-9999.0 && fJPsiVx[ijp2]!=-9999.0 ) {
          if( jpsi2L>jpsi1L ) fEtabJPsiDeltaT[fEtabN] = jpsi2T-jpsi1T;
          else fEtabJPsiDeltaT[fEtabN] = jpsi1T-jpsi2T;
          if( jpsi2T>jpsi1T ) fEtabJPsiDeltaL[fEtabN] = jpsi2L-jpsi1L;
          else fEtabJPsiDeltaL[fEtabN] = jpsi1L-jpsi2L;

          // J/Psi vtx to vtx error
          float DeltaX, DeltaY, DeltaZ;
          DeltaX = fJPsiVx[fEtabJPsiI[fEtabN][0]]-fJPsiVx[fEtabJPsiI[fEtabN][1]];
          DeltaY = fJPsiVy[fEtabJPsiI[fEtabN][0]]-fJPsiVy[fEtabJPsiI[fEtabN][1]];
          DeltaZ = fJPsiVz[fEtabJPsiI[fEtabN][0]]-fJPsiVz[fEtabJPsiI[fEtabN][1]];
          fEtabJPsiVtxErr[fEtabN] = sqrt( pow(DeltaX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2) ) + pow(DeltaY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2) ) + pow(DeltaZ,2)*( pow(fJPsiVzE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVzE[fEtabJPsiI[fEtabN][1]],2) ) ) / sqrt( pow(DeltaX,2)+pow(DeltaY,2)+pow(DeltaZ,2) );
          fEtabJPsiVtxErrxy[fEtabN] = sqrt( pow(DeltaX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2) ) + pow(DeltaY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2) ) ) / sqrt( pow(DeltaX,2)+pow(DeltaY,2) );
	}

        // find CT and CTxy
        if( fPvX[0]!=-9999 ) {
          float xvecX, xvecY, xvecZ, pvecX, pvecY, pvecZ;
          xvecX = fEtabVx[fEtabN]-fPvX[0];
          xvecY = fEtabVy[fEtabN]-fPvY[0];
          xvecZ = fEtabVz[fEtabN]-fPvZ[0];
          pvecX = fEtabPx[fEtabN];
          pvecY = fEtabPy[fEtabN];
          pvecZ = fEtabPz[fEtabN];
          fEtabCTxy[fEtabN] = (xvecX*fEtabPx[fEtabN]+xvecY*fEtabPy[fEtabN])/fEtabPt[fEtabN];
          fEtabCT[fEtabN] = (xvecX*fEtabPx[fEtabN]+xvecY*fEtabPy[fEtabN]+xvecZ*fEtabPz[fEtabN])/fEtabP[fEtabN];
          // using vtx kinematics
          pvecX = fEtabVtxPx[fEtabN];
          pvecY = fEtabVtxPy[fEtabN];
          pvecZ = fEtabVtxPz[fEtabN];
          fEtabVtxCTxy[fEtabN] = (xvecX*fEtabVtxPx[fEtabN]+xvecY*fEtabVtxPy[fEtabN])/fEtabVtxPt[fEtabN];
          fEtabVtxCT[fEtabN] = (xvecX*fEtabVtxPx[fEtabN]+xvecY*fEtabVtxPy[fEtabN]+xvecZ*fEtabVtxPz[fEtabN])/fEtabVtxP[fEtabN];
	}
      }

      // Determine isolation information
      for (Int_t ijp=0; ijp<2; ijp++) {
        float SumPt = 0;
        fEtabJPsiIsoTkN[fEtabN][ijp] = 0;
        fEtabJPsiIsoTkCA[fEtabN][ijp] = 9999;
        fEtabJPsiIso7PV[fEtabN][ijp] = 1;
        for (Int_t ipc=0; ipc<fTkN; ipc++) {
          if( fPcVx[ipc]==-9999 || fJPsiVx[fEtabJPsiI[fEtabN][ijp]]==-9999 ) continue;
          if( fPcIndex[ipc]==fJPsiMuI[fEtabJPsiI[fEtabN][0]][0] || fPcIndex[ipc]==fJPsiMuI[fEtabJPsiI[fEtabN][0]][1] || fPcIndex[ipc]==fJPsiMuI[fEtabJPsiI[fEtabN][1]][0] || fPcIndex[ipc]==fJPsiMuI[fEtabJPsiI[fEtabN][1]][1] ) continue;

          float x1, y1, z1, dCA;
          x1 = y1 = z1 = dCA = -9999.0;
          float px1, py1, pz1, px2, py2, pz2, px3, py3, pz3;
          px1 = fPcVx[ipc]-fPcPx[ipc];
          py1 = fPcVy[ipc]-fPcPy[ipc];
          pz1 = fPcVz[ipc]-fPcPz[ipc];
          px2 = fPcVx[ipc]+fPcPx[ipc];
          py2 = fPcVy[ipc]+fPcPy[ipc];
          pz2 = fPcVz[ipc]+fPcPz[ipc];
          px3 = fJPsiVx[fEtabJPsiI[fEtabN][ijp]];
          py3 = fJPsiVy[fEtabJPsiI[fEtabN][ijp]];
          pz3 = fJPsiVz[fEtabJPsiI[fEtabN][ijp]];

          float u = ( (px3-px1)*(px2-px1)+(py3-py1)*(py2-py1)+(pz3-pz1)*(pz2-pz1) )/( (px2-px1)*(px2-px1)+(py2-py1)*(py2-py1)+(pz2-pz1)*(pz2-pz1) );
          x1 = px1 + u*(px2 - px1);
          y1 = py1 + u*(py2 - py1);
          z1 = pz1 + u*(pz2 - pz1);
          dCA = sqrt( (x1-px3)*(x1-px3)+(y1-py3)*(y1-py3)+(z1-pz3)*(z1-pz3) );

          // determine dR to J/Psi
          Float_t dPhiToJPsi;
          if( (fPcPx[ipc]*fJPsiPx[fEtabJPsiI[fEtabN][ijp]]+fPcPy[ipc]*fJPsiPy[fEtabJPsiI[fEtabN][ijp]])/(fPcPt[ipc]*fJPsiPt[fEtabJPsiI[fEtabN][ijp]])>0.9999 ) dPhiToJPsi = 0;
          else if( (fPcPx[ipc]*fJPsiPx[fEtabJPsiI[fEtabN][ijp]]+fPcPy[ipc]*fJPsiPy[fEtabJPsiI[fEtabN][ijp]])/(fPcPt[ipc]*fJPsiPt[fEtabJPsiI[fEtabN][ijp]])<-0.9999 ) dPhiToJPsi = 3.14159265;
          else dPhiToJPsi = acos( (fPcPx[ipc]*fJPsiPx[fEtabJPsiI[fEtabN][ijp]]+fPcPy[ipc]*fJPsiPy[fEtabJPsiI[fEtabN][ijp]])/(fPcPt[ipc]*fJPsiPt[fEtabJPsiI[fEtabN][ijp]]) );
          Float_t dEtaToJPsi = fPcEta[ipc]-fJPsiEta[fEtabJPsiI[fEtabN][ijp]];
          Float_t dRToJPsi = sqrt(dPhiToJPsi*dPhiToJPsi+dEtaToJPsi*dEtaToJPsi);

          // first isolation type
          if( fPcPt[ipc]>0.9 && (fJPsiClosestPVinZ[fEtabJPsiI[fEtabN][ijp]]==fPcToPv[ipc] || (dCA<0.5&&fPcToPv[ipc]==-9999)) && dRToJPsi<0.7 ) {
            SumPt = SumPt+fPcPt[ipc];
	  }
          // second isolation type
          if( fPcPt[ipc]>0.5 && (fJPsiClosestPVinZ[fEtabJPsiI[fEtabN][ijp]]==fPcToPv[ipc] || fPcToPv[ipc]==-9999) && dCA<0.3 ) {
            if( dCA<fEtabJPsiIsoTkCA[fEtabN][ijp] ) fEtabJPsiIsoTkCA[fEtabN][ijp] = dCA;
            fEtabJPsiIsoTkN[fEtabN][ijp] = fEtabJPsiIsoTkN[fEtabN][ijp]+1;
	  }


        } // end loop over particles
        if( SumPt>0 ) fEtabJPsiIso7PV[fEtabN][ijp] = fJPsiPt[fEtabJPsiI[fEtabN][ijp]]/(fJPsiPt[fEtabJPsiI[fEtabN][ijp]]+SumPt);

      } // end loop over J/Psi within Eta_b

      // refit PV without muons from 4-mu candidate
      if( fEtabDuplicatesI[fEtabN] != -9999 ) {
        fEtabToRePvI[fEtabN] = fEtabToRePvI[fEtabDuplicatesI[fEtabN]];
      }
      else if( fPcToPv[fEtabMuI[fEtabN][0]]!=0 && fPcToPv[fEtabMuI[fEtabN][1]]!=0 && fPcToPv[fEtabMuI[fEtabN][2]]!=0 && fPcToPv[fEtabMuI[fEtabN][3]]!=0 ) {
        fEtabToRePvI[fEtabN] = 0; // no need to refit in this case
      }
      else {
        vector<TransientTrack> refit_tks;
        for (Int_t ipc=0; ipc<fTkN; ipc++) {
          if( fEtabMuI[fEtabN][0]==ipc || fEtabMuI[fEtabN][1]==ipc || fEtabMuI[fEtabN][2]==ipc || fEtabMuI[fEtabN][3]==ipc ) continue;
          if( fPcToTk[ipc]!=-9999 && fPcToPv[ipc]==0 ) refit_tks.push_back(t_tks[fPcToTk[ipc]]);
	}
	if( refit_tks.size()>1 ) {
          KalmanVertexFitter kvf(true);
          TransientVertex refit_pv = kvf.vertex(refit_tks);
          if( refit_pv.isValid() ) {
            if (fAllPvN > PVMAX - 1) break;
            fPvIndex[fAllPvN] = fEtabToRePvI[fEtabN] = fAllPvN;
            Vertex new_pv = refit_pv;
            fPvTkN[fAllPvN] = (int) new_pv.tracksSize();
            fPvX[fAllPvN] = (float) new_pv.x();
            fPvY[fAllPvN] = (float) new_pv.y();
            fPvZ[fAllPvN] = (float) new_pv.z();
            fPvXe[fAllPvN] = (float) new_pv.xError();
            fPvYe[fAllPvN] = (float) new_pv.yError();
            fPvZe[fAllPvN] = (float) new_pv.zError();
            fPvChi2[fAllPvN] = (float) new_pv.chi2();
            fPvNdof[fAllPvN] = (float) new_pv.ndof();
            fPvIsRefit[fAllPvN] = true;

            math::XYZTLorentzVectorD pvP4 = new_pv.p4(0.13957018,0);
            fPvPx[fAllPvN] = (float) pvP4.px();
            fPvPy[fAllPvN] = (float) pvP4.py();
            fPvPz[fAllPvN] = (float) pvP4.pz();
            fPvPt[fAllPvN] = (float) pvP4.pt();
            fPvP[fAllPvN] = (float) sqrt( pvP4.pt()*pvP4.pt() + pvP4.pz()*pvP4.pz() );
            fPvEnergy[fAllPvN] = (float) pvP4.energy();
            fPvEta[fAllPvN] = (float) -log(tan(0.5*acos(pvP4.pz()/sqrt(pvP4.px()*pvP4.px()+pvP4.py()*pvP4.py()+pvP4.pz()*pvP4.pz()))));
            fPvMass[fAllPvN] = (float) pvP4.M();
            fRePvN++; fAllPvN++;
	  }
	}
      }
      // determine CT and error relative to J/Psi
      if( fEtabToRePvI[fEtabN]!=-9999 && fEtabJPsiI[fEtabN][0]!=-9999 && fEtabJPsiI[fEtabN][1]!=-9999 ) {
        float xvecX, xvecY, xvecZ;
        xvecX = fJPsiVx[fEtabJPsiI[fEtabN][0]]-fPvX[fEtabToRePvI[fEtabN]];
        xvecY = fJPsiVy[fEtabJPsiI[fEtabN][0]]-fPvY[fEtabToRePvI[fEtabN]];
        xvecZ = fJPsiVz[fEtabJPsiI[fEtabN][0]]-fPvZ[fEtabToRePvI[fEtabN]];
        // J/Psi 1
        // using muon kinematics
        fEtabJPsiCT[fEtabN][0] = (fJPsiMass[fEtabJPsiI[fEtabN][0]]/fJPsiP[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][0]]+xvecZ*fJPsiPz[fEtabJPsiI[fEtabN][0]])/fJPsiP[fEtabJPsiI[fEtabN][0]];
        fEtabJPsiCTxy[fEtabN][0] = (fJPsiMass[fEtabJPsiI[fEtabN][0]]/fJPsiPt[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][0]])/fJPsiPt[fEtabJPsiI[fEtabN][0]];
        fEtabJPsiToPVVtxErr[fEtabN][0] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecZ,2)*( pow(fJPsiVzE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvZe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2)+pow(xvecZ,2) );
        fEtabJPsiToPVVtxErrxy[fEtabN][0] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2) );
        // using vtx kinematics
        fEtabJPsiVtxCT[fEtabN][0] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][0]]/fJPsiVtxP[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][0]]+xvecZ*fJPsiVtxPz[fEtabJPsiI[fEtabN][0]])/fJPsiVtxP[fEtabJPsiI[fEtabN][0]];
        fEtabJPsiVtxCTxy[fEtabN][0] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][0]]/fJPsiVtxPt[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][0]])/fJPsiVtxPt[fEtabJPsiI[fEtabN][0]];

        // J/Psi 2
        // using muon kinematics
        xvecX = fJPsiVx[fEtabJPsiI[fEtabN][1]]-fPvX[fEtabToRePvI[fEtabN]];
        xvecY = fJPsiVy[fEtabJPsiI[fEtabN][1]]-fPvY[fEtabToRePvI[fEtabN]];
        xvecZ = fJPsiVz[fEtabJPsiI[fEtabN][1]]-fPvZ[fEtabToRePvI[fEtabN]];
        fEtabJPsiCT[fEtabN][1] = (fJPsiMass[fEtabJPsiI[fEtabN][1]]/fJPsiP[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][1]]+xvecZ*fJPsiPz[fEtabJPsiI[fEtabN][1]])/fJPsiP[fEtabJPsiI[fEtabN][1]];
        fEtabJPsiCTxy[fEtabN][1] = (fJPsiMass[fEtabJPsiI[fEtabN][1]]/fJPsiPt[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][1]])/fJPsiPt[fEtabJPsiI[fEtabN][1]];
        fEtabJPsiToPVVtxErr[fEtabN][1] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecZ,2)*( pow(fJPsiVzE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvZe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2)+pow(xvecZ,2) );
        fEtabJPsiToPVVtxErrxy[fEtabN][1] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2) );
        // using vtx kinematics
        fEtabJPsiVtxCT[fEtabN][1] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][1]]/fJPsiVtxP[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][1]]+xvecZ*fJPsiVtxPz[fEtabJPsiI[fEtabN][1]])/fJPsiVtxP[fEtabJPsiI[fEtabN][1]];
        fEtabJPsiVtxCTxy[fEtabN][1] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][1]]/fJPsiVtxPt[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][1]])/fJPsiVtxPt[fEtabJPsiI[fEtabN][1]];
      }

      fEtabN++;
    } // end loop over second dimu cand
  } // end loop over first dimu cand
}
// define this as a plug-in
DEFINE_FWK_MODULE(PATEventTree);

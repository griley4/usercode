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
  fHLT_Skim(iConfig.getUntrackedParameter<bool>("HLT_Skim", false)),
  fIsEtabJPsi(iConfig.getUntrackedParameter<bool>("isEtabJPsi", false)),
  fIsJPsiMuMu(iConfig.getUntrackedParameter<bool>("isJPsiMuMu", false)),
  fIsMC(iConfig.getUntrackedParameter<bool>("isMC", false)),
  fUseFatJets(iConfig.getUntrackedParameter<bool>("useFatJets", false)),
  fHLTCollectionToken(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getUntrackedParameter<InputTag>("HLTCollectionLabel", edm::InputTag("patTrigger")))),
  fPrimaryVertexCollectionToken(consumes<reco::VertexCollection>(iConfig.getUntrackedParameter<InputTag>("PrimaryVertexCollectionLabel", edm::InputTag("offlinePrimaryVertices")))),
  fMuonCollectionToken(consumes<std::vector<pat::Muon> >(iConfig.getUntrackedParameter<InputTag>("MuonCollectionLabel", edm::InputTag("patMuonsWithTrigger")))),
  fElectronCollectionToken(consumes<std::vector<pat::Electron> >(iConfig.getUntrackedParameter<InputTag>("ElectronCollectionLabel", edm::InputTag("cleanPatElectrons")))),
  fPhotonCollectionToken(consumes<std::vector<pat::Photon> >(iConfig.getUntrackedParameter<InputTag>("PhotonCollectionLabel", edm::InputTag("cleanPatPhtons")))),
  fTrackCollectionToken(consumes<std::vector<reco::Track> >(iConfig.getUntrackedParameter<InputTag>("TrackCollectionLabel", edm::InputTag("generalTracks")))),
  fJetCollectionToken(consumes<std::vector<pat::Jet> >(iConfig.getUntrackedParameter<InputTag>("JetCollectionLabel", edm::InputTag("cleanPatJets")))),
  fMETCollectionToken(consumes< pat::METCollection >(iConfig.getUntrackedParameter<InputTag>("METCollectionLabel", edm::InputTag("patMETsPF")))),
  fJPsiInputToken(consumes< reco::MuonRefVector > (iConfig.getUntrackedParameter<InputTag>("JPsiInputLabel", edm::InputTag("goodMuons")))),
  fJPsiCandToken(consumes< reco::CompositeCandidateCollection >(iConfig.getUntrackedParameter<InputTag>("JPsiCandLabel", edm::InputTag("JPsiToMuMu")))),
  fHLTPathLabel(iConfig.getUntrackedParameter<InputTag>("HLTPathLabel", edm::InputTag("TriggerResults::HLT"))),
  fHLTFilterLabel(iConfig.getUntrackedParameter<InputTag>("HLTFilterLabel", edm::InputTag("hltTriggerSummaryAOD"))),
  //fParticleCollectionLabel(iConfig.getUntrackedParameter<InputTag>("ParticleCollectionLabel", edm::InputTag("cleanPatTrackCands"))),
  fGenCollectionLabel(iConfig.getUntrackedParameter<InputTag>("GenCollectionLabel", edm::InputTag("genParticles"))),
  //fUpsilonCandLabel(iConfig.getUntrackedParameter<InputTag>("UpsilonCandLabel", edm::InputTag("UpsilonToMuMu"))),
  fFatJetCollectionLabel(iConfig.getUntrackedParameter<std::vector<edm::InputTag> >("FatJetCollectionLabel")),
  fInit(0),
  fHltPrescale(iConfig, consumesCollector(), *this)
{
  string rcsid = string("$Id: PATEventTree.cc,v 1.00 2010/06/17 11:25:00 Exp $");
  cout << "----------------------------------------------------------------------" << endl;
  cout << "---  PATEventTree constructor" << endl;
  cout << "---  version:                         " << rcsid << endl;
  cout << "---  rootFileName:                    " << fRootFileName << endl;
  cout << "---  isJPsiMuMu:                      " << fIsJPsiMuMu << endl;
  cout << "---  useFatJets:                      " << fUseFatJets << endl;
  //cout << "---  MuonCollectionLabel:             " << fMuonCollectionLabel << endl;
  //cout << "---  ElectronCollectionLabel:         " << fElectronCollectionToken << endl;
  //cout << "---  PhotonCollectionLabel:           " << fPhotonCollectionToken << endl;
  //cout << "---  ParticleCollectionLabel:         " << fParticleCollectionLabel << endl;
  //cout << "---  TrackCollectionLabel:            " << fTrackCollectionLabel << endl;
  //cout << "---  JetCollectionLabel:              " << fJetCollectionLabel << endl;
  //cout << "---  GenCollectionLabel:              " << fGenCollectionLabel << endl;
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
  fTree->Branch("tlo",          &fTimeLo,       "tlo/i");
  fTree->Branch("thi",          &fTimeHi,       "thi/i");

  fTree->Branch("EvSphericity",   &fEvSphericity,   "EvSphericity/F");
  fTree->Branch("EvAplanarity",   &fEvAplanarity,   "EvAplanarity/F");
  fTree->Branch("EvLambda",       fEvLambda,        "EvLambda[3]/F");
  fTree->Branch("EvThrust",       &fEvThrust,       "EvThrust/F");
  fTree->Branch("EvThrust_Major", &fEvThrust_Major, "EvThrust_Major/F");
  fTree->Branch("EvThrust_Minor", &fEvThrust_Minor, "EvThrust_Minor/F");
  fTree->Branch("EvFW",           fEvFW,            "EvFW[7]/F");

  fTree->Branch("HLTP_DoubleMu3",         fHLTP_DoubleMu3,       "HLTP_DoubleMu3[3]/O");
  fTree->Branch("HLTP_DoubleMu6",         fHLTP_DoubleMu6,       "HLTP_DoubleMu6[3]/O");
  fTree->Branch("HLTP_DoubleMu7",         fHLTP_DoubleMu7,       "HLTP_DoubleMu7[3]/O");
  fTree->Branch("HLTP_Dimuon0_Jpsi",      fHLTP_Dimuon0_Jpsi,    "HLTP_Dimuon0_Jpsi[3]/O");
  fTree->Branch("HLTP_Dimuon0_Jpsi_Muon", fHLTP_Dimuon0_Jpsi_Muon, "HLTP_Dimuon0_Jpsi_Muon[3]/O");
  fTree->Branch("HLTP_Dimuon0_Upsilon_Muon", fHLTP_Dimuon0_Upsilon_Muon, "HLTP_Dimuon0_Upsilon_Muon[3]/O");
  fTree->Branch("HLTP_Dimuon10_Jpsi_Barrel", fHLTP_Dimuon10_Jpsi_Barrel, "HLTP_Dimuon10_Jpsi_Barrel[3]/O");
  fTree->Branch("HLTP_TripleMu5",         fHLTP_TripleMu5,       "HLTP_TripleMu5[3]/O");
  fTree->Branch("HLTP_QuadMuon0_Dimuon0_Jpsi", fHLTP_QuadMuon0_Dimuon0_Jpsi, "HLTP_QuadMuon0_Dimuon0_Jpsi[3]/O");
  fTree->Branch("HLTP_QuadMuon0_Dimuon0_Upsilon", fHLTP_QuadMuon0_Dimuon0_Upsilon, "HLTP_QuadMuon0_Dimuon0_Upsilon[3]/O");
  fTree->Branch("HLTP_DoubleMu3_PS",         &fHLTP_DoubleMu3_PS,       "HLTP_DoubleMu3_PS/i");
  fTree->Branch("HLTP_DoubleMu6_PS",         &fHLTP_DoubleMu6_PS,       "HLTP_DoubleMu6_PS/i");
  fTree->Branch("HLTP_DoubleMu7_PS",         &fHLTP_DoubleMu7_PS,       "HLTP_DoubleMu7_PS/i");
  fTree->Branch("HLTP_Dimuon0_Jpsi_Muon_PS", &fHLTP_Dimuon0_Jpsi_Muon_PS, "HLTP_Dimuon0_Jpsi_Muon_PS/i");
  fTree->Branch("HLTP_Dimuon0_Upsilon_Muon_PS", &fHLTP_Dimuon0_Upsilon_Muon_PS, "HLTP_Dimuon0_Upsilon_Muon_PS/i");
  fTree->Branch("HLTP_Dimuon0_Jpsi_PS",      &fHLTP_Dimuon0_Jpsi_PS,    "HLTP_Dimuon0_Jpsi_PS/i");
  fTree->Branch("HLTP_Dimuon10_Jpsi_Barrel_PS", &fHLTP_Dimuon10_Jpsi_Barrel_PS, "HLTP_Dimuon10_Jpsi_Barrel_PS/i");
  fTree->Branch("HLTP_TripleMu5_PS",         &fHLTP_TripleMu5_PS,       "HLTP_TripleMu5_PS/i");
  fTree->Branch("HLTP_QuadMuon0_Dimuon0_Jpsi_PS", &fHLTP_QuadMuon0_Dimuon0_Jpsi_PS, "HLTP_QuadMuon0_Dimuon0_Jpsi_PS/i");
  fTree->Branch("HLTP_QuadMuon0_Dimuon0_Upsilon_PS", &fHLTP_QuadMuon0_Dimuon0_Upsilon_PS, "HLTP_QuadMuon0_Dimuon0_Upsilon_PS/i");
  fTree->Branch("HLTP_DoubleMu3_Filters",    fHLTP_DoubleMu3_Filters,  "HLTP_DoubleMu3_Filters[5]/O");
  fTree->Branch("HLTP_DoubleMu6_Filters",    fHLTP_DoubleMu6_Filters,  "HLTP_DoubleMu6_Filters[5]/O");
  fTree->Branch("HLTP_DoubleMu7_Filters",    fHLTP_DoubleMu7_Filters,  "HLTP_DoubleMu7_Filters[5]/O");
  fTree->Branch("HLTP_TripleMu5_Filters",    fHLTP_TripleMu5_Filters,  "HLTP_TripleMu5_Filters[5]/O");
  fTree->Branch("HLTP_QuadMuon0_Dimuon0_Jpsi_Filters", fHLTP_QuadMuon0_Dimuon0_Jpsi_Filters, "HLTP_QuadMuon0_Dimuon0_Jpsi_Filters[7]/O");
  fTree->Branch("HLTP_QuadMuon0_Dimuon0_Upsilon_Filters", fHLTP_QuadMuon0_Dimuon0_Upsilon_Filters, "HLTP_QuadMuon0_Dimuon0_Upsilon_Filters[7]/O");
  fTree->Branch("HLTP_Dimuon0_Jpsi_Filters", fHLTP_Dimuon0_Jpsi_Filters, "HLTP_Dimuon0_Jpsi_Filters[7]/O");
  fTree->Branch("HLTP_Dimuon0_Jpsi_Muon_Filters", fHLTP_Dimuon0_Jpsi_Muon_Filters, "HLTP_Dimuon0_Jpsi_Muon_Filters[8]/O");
  fTree->Branch("HLTP_Dimuon0_Upsilon_Muon_Filters", fHLTP_Dimuon0_Upsilon_Muon_Filters, "HLTP_Dimuon0_Upsilon_Muon_Filters[8]/O");
  fTree->Branch("HLTP_Dimuon10_Jpsi_Barrel_Filters", fHLTP_Dimuon10_Jpsi_Barrel_Filters, "HLTP_Dimuon10_Jpsi_Barrel_Filters[7]/O");

  fTree->Branch("HLTN",           &fHLTN,           "HLTN/I");
  fTree->Branch("HLT_Index",      fHLT_Index,       "HLT_Index[HLTN]/I");
  fTree->Branch("HLT_ToPc",       fHLT_ToPc,        "HLT_ToPc[HLTN]/I");
  fTree->Branch("HLT_ToJt",       fHLT_ToJt,        "HLT_ToJt[HLTN]/I");
  fTree->Branch("HLT_PdgId",      fHLT_PdgId,       "HLT_PdgId[HLTN]/I");
  fTree->Branch("HLT_Mass",       fHLT_Mass,        "HLT_Mass[HLTN]/F");
  fTree->Branch("HLT_Energy",     fHLT_Energy,      "HLT_Energy[HLTN]/F");
  fTree->Branch("HLT_Et",         fHLT_Et,          "HLT_Et[HLTN]/F");
  fTree->Branch("HLT_P",          fHLT_P,           "HLT_P[HLTN]/F");
  fTree->Branch("HLT_Pt",         fHLT_Pt,          "HLT_Pt[HLTN]/F");
  fTree->Branch("HLT_Px",         fHLT_Px,          "HLT_Px[HLTN]/F");
  fTree->Branch("HLT_Py",         fHLT_Py,          "HLT_Py[HLTN]/F");
  fTree->Branch("HLT_Pz",         fHLT_Pz,          "HLT_Pz[HLTN]/F");
  fTree->Branch("HLT_Theta",      fHLT_Theta,       "HLT_Theta[HLTN]/F");
  fTree->Branch("HLT_Eta",        fHLT_Eta,         "HLT_Eta[HLTN]/F");
  fTree->Branch("HLT_Phi",        fHLT_Phi,         "HLT_Phi[HLTN]/F");

  fTree->Branch("HLT_Mu",         fHLT_Mu,          "HLT_Mu[HLTN][2]/O");
  fTree->Branch("HLT_Mu12",       fHLT_Mu12,        "HLT_Mu12[HLTN][2]/O");
  fTree->Branch("HLT_Mu15",       fHLT_Mu15,        "HLT_Mu15[HLTN][2]/O");
  fTree->Branch("HLT_Mu20",       fHLT_Mu20,        "HLT_Mu20[HLTN][2]/O");
  fTree->Branch("HLT_Mu24",       fHLT_Mu24,        "HLT_Mu24[HLTN][2]/O");
  fTree->Branch("HLT_Mu30",       fHLT_Mu30,        "HLT_Mu30[HLTN][2]/O");
  fTree->Branch("HLT_IsoMu12",    fHLT_IsoMu12,     "HLT_IsoMu12[HLTN][2]/O");
  fTree->Branch("HLT_IsoMu15",    fHLT_IsoMu15,     "HLT_IsoMu15[HLTN][2]/O");
  fTree->Branch("HLT_IsoMu17",    fHLT_IsoMu17,     "HLT_IsoMu17[HLTN][2]/O");
  fTree->Branch("HLT_IsoMu24",    fHLT_IsoMu24,     "HLT_IsoMu24[HLTN][2]/O");
  fTree->Branch("HLT_IsoMu30",    fHLT_IsoMu30,     "HLT_IsoMu30[HLTN][2]/O");
  fTree->Branch("HLT_DoubleMu3",  fHLT_DoubleMu3,   "HLT_DoubleMu3[HLTN][2]/O");
  fTree->Branch("HLT_DoubleMu6",  fHLT_DoubleMu6,   "HLT_DoubleMu6[HLTN][2]/O");
  fTree->Branch("HLT_DoubleMu7",  fHLT_DoubleMu7,   "HLT_DoubleMu7[HLTN][2]/O");
  fTree->Branch("HLT_Dimuon0_Jpsi_Muon", fHLT_Dimuon0_Jpsi_Muon, "HLT_Dimuon0_Jpsi_Muon[HLTN][2]/O");
  fTree->Branch("HLT_Dimuon0_Upsilon_Muon", fHLT_Dimuon0_Upsilon_Muon, "HLT_Dimuon0_Upsilon_Muon[HLTN][2]/O");
  fTree->Branch("HLT_Dimuon0_Jpsi", fHLT_Dimuon0_Jpsi, "HLT_Dimuon0_Jpsi[HLTN][2]/O");
  fTree->Branch("HLT_Dimuon7_Jpsi_Displaced", fHLT_Dimuon7_Jpsi_Displaced, "HLT_Dimuon7_Jpsi_Displaced[HLTN][2]/O");
  fTree->Branch("HLT_Dimuon7_Jpsi_X_Barrel", fHLT_Dimuon7_Jpsi_X_Barrel, "HLT_Dimuon7_Jpsi_X_Barrel[HLTN][2]/O");
  fTree->Branch("HLT_Dimuon10_Jpsi_Barrel", fHLT_Dimuon10_Jpsi_Barrel, "HLT_Dimuon10_Jpsi_Barrel[HLTN][2]/O");
  fTree->Branch("HLT_TripleMu5", fHLT_TripleMu5, "HLT_TripleMu5[HLTN][2]/O");
  fTree->Branch("HLT_QuadMuon0_Dimuon0_Jpsi", fHLT_QuadMuon0_Dimuon0_Jpsi, "HLT_QuadMuon0_Dimuon0_Jpsi[2]/O");
  fTree->Branch("HLT_QuadMuon0_Dimuon0_Upsilon", fHLT_QuadMuon0_Dimuon0_Upsilon, "HLT_QuadMuon0_Dimuon0_Upsilon[2]/O");
  fTree->Branch("HLT_Jet",        fHLT_Jet,         "HLT_Jet[HLTN][2]/O");

  fTree->Branch("PcN",          &fPcN,          "PcN/I");
  fTree->Branch("TkN",          &fTkN,          "TkN/I");
  fTree->Branch("MuN",          &fMuN,          "MuN/I");
  fTree->Branch("ElecN",        &fElecN,        "ElecN/I");
  //fTree->Branch("HadrN",        &fHadrN,        "HadrN/I");
  fTree->Branch("MiscTkN",      &fMiscTkN,      "MiscTkN/I");
  fTree->Branch("PhotN",        &fPhotN,        "PhotN/I");
  fTree->Branch("PcIndex",      fPcIndex,       "PcIndex[PcN]/I");
  fTree->Branch("MuIndex",      fMuIndex,       "MuIndex[MuN]/I");
  fTree->Branch("ElecIndex",    fElecIndex,     "ElecIndex[ElecN]/I");
  //fTree->Branch("HadrIndex",    fHadrIndex,     "HadrIndex[HadrN]/I");
  fTree->Branch("MiscTkIndex",  fMiscTkIndex,   "MiscTkIndex[MiscTkN]/I");
  fTree->Branch("PhotIndex",    fPhotIndex,     "PhotIndex[PhotN]/I");
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
  fTree->Branch("MuIsGood",   fMuIsGood,    "MuIsGood[MuN]/O");
  fTree->Branch("MuIsSoft",  fMuIsSoft,   "MuIsSoft[MuN]/O");
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
  edm::Handle< pat::TriggerObjectStandAloneCollection > HLTHandle;
  try{ 
    iEvent.getByToken(fHLTCollectionToken, HLTHandle);
  } catch (cms::Exception &ex) {
    cout << "No HLT collection " << endl;
  }
  edm::Handle< std::vector<pat::Muon> > muonHandle;
  try{ 
    iEvent.getByToken(fMuonCollectionToken, muonHandle);
  } catch (cms::Exception &ex) {
    cout << "No muon collection " << endl;
  }
  edm::Handle< std::vector<pat::Electron> > electronHandle;
  try{
    iEvent.getByToken(fElectronCollectionToken, electronHandle);
  } catch (cms::Exception &ex) {
    cout << "No electron collection " << endl;
  }
  edm::Handle< std::vector<pat::Photon> > photonHandle;
  try{ 
    iEvent.getByToken(fPhotonCollectionToken, photonHandle);
  } catch (cms::Exception &ex) {
    cout << "No photon collection " <<  endl;
  }
  /*edm::Handle< std::vector<pat::GenericParticle> > particleHandle;
  try{ 
    iEvent.getByLabel(fParticleCollectionLabel, particleHandle);
  } catch (cms::Exception &ex) {
  cout << "No generic particle collection with label " << fParticleCollectionLabel << endl;
  }*/
  edm::Handle< std::vector<reco::Track> > ctfTrackHandle;
  try{ 
    iEvent.getByToken(fTrackCollectionToken, ctfTrackHandle);
  } catch (cms::Exception &ex) {
    cout << "No ctf track collection" << endl;
  }
  edm::Handle<reco::VertexCollection> pvHandle;
  try{ 
    iEvent.getByToken(fPrimaryVertexCollectionToken, pvHandle);
  } catch (cms::Exception &ex) {
    cout << "No primary vertex collection" << endl;
  }
  edm::Handle< std::vector<pat::Jet> > jetHandle;
  try{ 
    iEvent.getByToken(fJetCollectionToken, jetHandle);
  } catch (cms::Exception &ex) {
    cout << "No jet collection with label " << endl;
  }
  std::vector< edm::Handle< std::vector<pat::Jet> > > fatJetHandle;
  if (fUseFatJets) {
    for( std::vector<edm::InputTag>::const_iterator inputTag = fFatJetCollectionLabel.begin(); inputTag != fFatJetCollectionLabel.end(); ++inputTag ) {
      try{
        edm::Handle< std::vector<pat::Jet> > tempHandle;
        iEvent.getByLabel(*inputTag, tempHandle);
        fatJetHandle.push_back(tempHandle);
      } catch (cms::Exception &ex) {
        cout << "No fat jet collection " << *inputTag << endl;
      }
    }
  }
  edm::Handle< pat::METCollection > METHandle;
  try{ 
    iEvent.getByToken(fMETCollectionToken, METHandle);
  } catch (cms::Exception &ex) {
    cout << "No MET collection " << endl;
  }
  edm::Handle< reco::CompositeCandidateCollection > JPsiCandHandle;
  try{ 
    iEvent.getByToken(fJPsiCandToken, JPsiCandHandle);
  } catch (cms::Exception &ex) {
    cout << "No composite candidate collection with label "<< endl;
  }
  edm::Handle< reco::MuonRefVector > JPsiInputHandle;
  try{ 
    iEvent.getByToken(fJPsiInputToken, JPsiInputHandle);
  } catch (cms::Exception &ex) {
    cout << "No muon ref collection " << endl;
  }

  fAllPvN = PVMAX;
  fHLTN = HLTMAX;
  fPcN = PARTMAX;
  fJtN = JETMAX;
  fSvN = SVMAX;
  fGnN = GENMAX;
  ++nevt; 
  init();

  cout << "Event info" << endl;

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
  unsigned int psSet = fHltPrescale.prescaleSet(iEvent, iSetup);
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
  if ( fHLT_Skim && !(fHLTP_Dimuon0_Upsilon_Muon[1] || fHLTP_Dimuon0_Jpsi_Muon[1] || fHLTP_QuadMuon0_Dimuon0_Jpsi[1] || fHLTP_QuadMuon0_Dimuon0_Upsilon[1]) ) return; // only ntuplize events passing trigger if skimming enabled

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
  if ( muonHandle.isValid() && electronHandle.isValid() && photonHandle.isValid() && ctfTrackHandle.isValid() ) fillParticles( *(muonHandle.product()), *(electronHandle.product()), *(photonHandle.product()), *(ctfTrackHandle.product()), *(pvHandle.product()) );
  else { cout << "--> Missing valid particle collection" << endl; }
  //if ( fTkN<2 ) return; // only look at events with at least 2 tracks

  // ----------------------------------------------------------------------
  // -- Primary vertices
  // ----------------------------------------------------------------------
  if ( pvHandle.isValid() ) fillPrimaryVertices( *(pvHandle.product()) );
  else { cout << "--> No valid primary vertex collection" << endl; }

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
  // -- Jets
  // ----------------------------------------------------------------------
  if ( jetHandle.isValid() ) {
    JtShift = fJtN;
    fillJets( *(jetHandle.product()) );
    fJtStandN = fJtN;
    for ( int ij = 0; ij < fJtStandN; ij++) { fJtStandIndex[ij] = ij; fJtIsStandard[ fJtStandIndex[ij] ] = true; }
  }
  else { cout << "--> No valid jet collection" << endl; }

  // ----------------------------------------------------------------------
  // -- Fat Jets
  // ----------------------------------------------------------------------
  if (fUseFatJets) {
    for ( unsigned int ijc = 0; ijc < fatJetHandle.size(); ijc++) {
      if ( fatJetHandle[ijc].isValid() ) {
        JtShift = fJtN;
        fillJets( *(fatJetHandle[ijc].product()) );
        // fill info specific to Fat jets
        if (ijc == 0) { 
	  fJtFatN = fJtN - JtShift;
          for ( int ijf = 0; ijf < fJtFatN; ijf++ ) { fJtFatIndex[ijf] = ijf+JtShift; fJtIsFat[ fJtFatIndex[ijf] ] = true; }
        } else if (ijc == 1) { 
	  fJtSubN = fJtN - JtShift;
          for ( int ijs = 0; ijs < fJtSubN; ijs++ ) { fJtSubIndex[ijs] = ijs+JtShift; fJtIsSub[ fJtSubIndex[ijs] ] = true; }
        } else if (ijc == 2) {
	  fJtFiltN = fJtN - JtShift;
          for ( int ijf = 0; ijf < fJtFiltN; ijf++ ) { fJtFiltIndex[ijf] = ijf+JtShift; fJtIsFilt[ fJtFiltIndex[ijf] ] = true; }
        }
      } else { cout << "--> No valid fat jet collection" << endl; }
    }
    jetDisambiguation();
  }
  // ----------------------------------------------------------------------
  // -- MET
  // ----------------------------------------------------------------------
  if ( METHandle.isValid() ) fillMET( *(METHandle.product()) );
  else { cout << "--> No valid MET collection" << endl; }


  // ----------------------------------------------------------------------
  // -- JPsi Candidates
  // ----------------------------------------------------------------------
  // Make transient tracks for vertex-building
  edm::ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
  // do the conversion:
  vector<TransientTrack> t_tks = (*theB).build(ctfTrackHandle);

  // Use dimuon collection and transient tracks to make J/Psi candidates
  if ( JPsiCandHandle.isValid() && JPsiInputHandle.isValid() ) fillJPsiMuMuCand( *(JPsiCandHandle.product()), *(JPsiInputHandle.product()), t_tks );
  else { cout << "--> No valid JPsi cand. collection" << endl; }
  fJPsiMuMuN = fJPsiN;

  // Use 1 muon and 1 track to make J/Psi candidates
  //if ( JPsiInputHandle.isValid() && ctfTrackHandle.isValid() ) makeJPsiMuTkCand( *(JPsiInputHandle.product()), *(ctfTrackHandle.product()), t_tks );
  //else { cout << "--> No valid JPsi cand. collection" << endl; }
  fJPsiMuTkN = fJPsiN-fJPsiMuMuN;

  

  // ----------------------------------------------------------------------
  // -- Etab Candidates
  // ----------------------------------------------------------------------
  if ( fJPsiN>1 ) makeEtabCand( t_tks );

  // ----------------------------------------------------------------------
  // -- Higgs Candidates
  // ----------------------------------------------------------------------
  if ( fJtStandN>1 ) makeHiggsCand( fJtStandIndex[0], fJtStandIndex[fJtStandN-1] );
  if ( fJtSubN>1 ) makeHiggsCand( fJtSubIndex[0], fJtSubIndex[fJtSubN-1] );
  if ( fJtFiltN>1 ) makeHiggsCand( fJtFiltIndex[0], fJtFiltIndex[fJtFiltN-1] );

  // ----------------------------------------------------------------------
  // -- Event topology
  // ----------------------------------------------------------------------

  fillTopology();
  if ( fIsJPsiMuMu&&(fJPsiI[0]==-9999&&fJPsiI[1]==-9999) ) return; // return if no MC JPsi found for expected JPsi event

  fTree->Fill();
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

  fHLTP_DoubleMu3_PS = fHLTP_DoubleMu6_PS = fHLTP_DoubleMu7_PS = fHLTP_Dimuon0_Upsilon_Muon_PS = fHLTP_Dimuon0_Jpsi_Muon_PS = fHLTP_Dimuon0_Jpsi_PS = fHLTP_Dimuon10_Jpsi_Barrel_PS = fHLTP_TripleMu5_PS = fHLTP_QuadMuon0_Dimuon0_Jpsi_PS = fHLTP_QuadMuon0_Dimuon0_Upsilon_PS = 0;

  for (int i = 0; i < 3; i++) {
    fHLTP_DoubleMu3[i] = fHLTP_DoubleMu6[i] = fHLTP_DoubleMu7[i] = fHLTP_Dimuon0_Upsilon_Muon[i] = fHLTP_Dimuon0_Jpsi_Muon[i] = fHLTP_Dimuon0_Jpsi[i] = fHLTP_Dimuon10_Jpsi_Barrel[i] = fHLTP_TripleMu5[i] = fHLTP_QuadMuon0_Dimuon0_Jpsi[i] = fHLTP_QuadMuon0_Dimuon0_Upsilon[i] = false;
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
    fMuIsGood[i] = fMuIsSoft[i] = fMuIsGlobal[i] = fMuIsTracker[i] = fMuIsStandalone[i] = fMuIsCalo[i] = fMuArbitrated[i] = fMuLastStationLoose[i] = fMuLastStationTight[i] = fMu2DCompatibilityLoose[i] = fMu2DCompatibilityTight[i] = fMuOneStationLoose[i] = fMuOneStationTight[i] = fMuHLTMatch[i][0] = fMuHLTMatch[i][1] = fMuL3Match[i] = fMuTightMatch[i] = false;
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

  fPvN = fRePvN = fAllPvN = fHLTN = fPcN = fTkN = fMuN = fElecN = fMiscTkN = fPhotN = JtShift = fJtN = fJtStandN = fJtFatN = fJtSubN = fJtFiltN = fMETN = fSvN = fSsvN = fGtvN = fJPsiN = fEtabN = fHN = fGnN = fGnBN = fJtBdRN = fJtBFlavN = 0;

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
    } else if (validTriggerNames[itrig].find("HLT_QuadMuon0_Dimuon0_Jpsi_v")!=string::npos) {
      fHLTP_QuadMuon0_Dimuon0_Jpsi[0] = wasrun;
      fHLTP_QuadMuon0_Dimuon0_Jpsi[1] = accept;
      fHLTP_QuadMuon0_Dimuon0_Jpsi[2] = error;
      fHLTP_QuadMuon0_Dimuon0_Jpsi_PS = prescale;
    } else if (validTriggerNames[itrig].find("HLT_QuadMuon0_Dimuon0_Upsilon_v")!=string::npos) {
      fHLTP_QuadMuon0_Dimuon0_Upsilon[0] = wasrun;
      fHLTP_QuadMuon0_Dimuon0_Upsilon[1] = accept;
      fHLTP_QuadMuon0_Dimuon0_Upsilon[2] = error;
      fHLTP_QuadMuon0_Dimuon0_Upsilon_PS = prescale;
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
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Jpsi_Muon_v1", false, false) ) fHLT_Dimuon0_Jpsi_Muon[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon0_Jpsi_v3", false, false) ) fHLT_Dimuon0_Jpsi[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon7_Jpsi_Displaced_v3", false, false) ) fHLT_Dimuon7_Jpsi_Displaced[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon10_Jpsi_Barrel_v3", false, false) ) fHLT_Dimuon10_Jpsi_Barrel[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_TripleMu5_v6", false, false) ) fHLT_TripleMu5[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_Dimuon7_Jpsi_X_Barrel_v3", false, false) ) fHLT_Dimuon7_Jpsi_X_Barrel[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_QuadMuon0_Dimuon0_Jpsi_v1", false, false) ) fHLT_QuadMuon0_Dimuon0_Jpsi[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_QuadMuon0_Dimuon0_Upsilon_v1", false, false) ) fHLT_QuadMuon0_Dimuon0_Upsilon[fHLTN][0] = true;


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
    if( HLTObjects[fHLTN].hasPathName("HLT_QuadMuon0_Dimuon0_Jpsi_v1", true, false) ) fHLT_QuadMuon0_Dimuon0_Jpsi[fHLTN][0] = true;
    if( HLTObjects[fHLTN].hasPathName("HLT_QuadMuon0_Dimuon0_Upsilon_v1", true, false) ) fHLT_QuadMuon0_Dimuon0_Upsilon[fHLTN][0] = \
											    true;
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


void PATEventTree::fillParticles(const std::vector<pat::Muon>& muons, const std::vector<pat::Electron>& electrons, const std::vector<pat::Photon>& photons, const std::vector<reco::Track>& ctftracks, const std::vector<Vertex>& vertices) {

  int TkI;  // the index of the underlying ctf track
  fTkN = (int) ctftracks.size();

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
    // hit pattern of the track
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
//    fMuIsGood[fMuN] = muons[fMuN].isGoodMuon();
    for(int iv = 0; iv < (int) vertices.size(); iv++){
       if(muons[fMuN].isSoftMuon(vertices[iv])){
	       fMuIsSoft[fMuN] =true;}}
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

    fMuN++;
    fPcN++;
  }

  for (int i = 0; i != (int) electrons.size(); i++) {
    if (fPcN > PARTMAX - 1) break;

    if (electrons[fElecN].track().isNonnull()) TkI = (int) electrons[fElecN].track().index();
    else if (electrons[fElecN].closestCtfTrackRef().isNonnull()) TkI = (int) electrons[fElecN].closestCtfTrackRef().index();
    else continue;  // skip if I can't associate to ctftrack

    if (fTkToPc[TkI] != -9999) continue; // don't use tracks that already came from muons
    if (fIsMC&&electrons[fElecN].genParticleRef().isNonnull()) {
      for (int ig = fGnN-1; ig >= 0; ig--) {
        if (fGnPdgId[ig]==(int) electrons[fElecN].genParticleRef()->pdgId() && fGnPt[ig]==(float) electrons[fElecN].genParticleRef()->pt() && fGnEta[ig]==(float) electrons[fElecN].genParticleRef()->eta()) { fPcToGn[fPcN] = ig; break; }
      }
    }
    fPcToTk[fPcN] = TkI;
    fTkToPc[TkI] = fPcN;
    fPcIndex[fPcN] = fPcN;
    fElecIndex[fElecN] = fPcN;
    fPcPdgId[fPcN] = (int) electrons[fElecN].pdgId();
    fPcCharge[fPcN] = (float) electrons[fElecN].charge();
    fPcEnergy[fPcN] = (float) electrons[fElecN].energy();
    fPcEt[fPcN] = (float) electrons[fElecN].et();
    fPcP[fPcN] = (float) electrons[fElecN].p();
    fPcPt[fPcN] = (float) electrons[fElecN].pt();
    fPcPx[fPcN] = (float) electrons[fElecN].px();
    fPcPy[fPcN] = (float) electrons[fElecN].py();
    fPcPz[fPcN] = (float) electrons[fElecN].pz();
    fPcTheta[fPcN] = (float) electrons[fElecN].theta();
    fPcEta[fPcN] = (float) electrons[fElecN].eta();
    fPcPhi[fPcN] = (float) electrons[fElecN].phi();
    fPcVx[fPcN] = (float) electrons[fElecN].vx();
    fPcVy[fPcN] = (float) electrons[fElecN].vy();
    fPcVz[fPcN] = (float) electrons[fElecN].vz();
    fPcEcalIso[fPcN] = (float) electrons[fElecN].ecalIso();
    fPcHcalIso[fPcN] = (float) electrons[fElecN].hcalIso();
    fPcTrackIso[fPcN] = (float) electrons[fElecN].trackIso();

    fPcTkQuality[fPcN] = (int) ctftracks[TkI].qualityMask();
    fPcChi2[fPcN] = (float) ctftracks[TkI].chi2();
    fPcNdof[fPcN] = (float) ctftracks[TkI].ndof();
    fPcD0[fPcN] = (float) ctftracks[TkI].d0();
    fPcDz[fPcN] = (float) ctftracks[TkI].dz();
    fPcEtaErr[fPcN] = (float) ctftracks[TkI].etaError();
    fPcPhiErr[fPcN] = (float) ctftracks[TkI].phiError();
    fPcD0Err[fPcN] = (float) ctftracks[TkI].d0Error();
    fPcDzErr[fPcN] = (float) ctftracks[TkI].dzError();
    // hit pattern of the track
    const reco::HitPattern& hits = ctftracks[TkI].hitPattern();
    fPcPixHitN[fPcN] = (int) hits.numberOfValidPixelHits();
    fPcPixLayN[fPcN] = (int) hits.pixelLayersWithMeasurement();
    fPcStripHitN[fPcN] = (int) hits.numberOfValidStripHits();
    fPcStripLayN[fPcN] = (int) hits.stripLayersWithMeasurement();

    // electron specific
    //TriggerObjectStandAloneCollection ElecHLTmatches = electrons[fElecN].triggerObjectMatches();
    //if(ElecHLTmatches.size()!=0) fElecHLTMatch[fElecN]=true;

    // for electrons only, can use gsfTrack info for these since they are better model for electron path
    // reco::GsfTrackRef gsftrack = electrons[fElecN].gsfTrack();
    // if (gsftrack.isNonnull()) { }

    fElecN++;
    fPcN++;
  }

  /*for (int i = 0; i != (int) particles.size(); i++) {
    if (fPcN > PARTMAX - 1) break;

    if (particles[fHadrN].track().isNonnull()) TkI = (int) particles[fHadrN].track().index();
    else continue; // skip if I can't associate to ctftrack

    if (fTkToPc[TkI] != -9999) continue; // don't use particles that already came from muons or electrons
    if (fIsMC&&particles[fHadrN].genParticleRef().isNonnull()) {
      for (int ig = fGnN-1; ig >= 0; ig--) {
        if (fGnPdgId[ig]==(int) particles[fHadrN].genParticleRef()->pdgId() && fGnPt[ig]==(float) particles[fHadrN].genParticleRef()->pt() && fGnEta[ig]==(float) particles[fHadrN].genParticleRef()->eta()) { fPcToGn[fPcN] = ig; break; }
      }
    }
    fPcToTk[fPcN] = TkI;
    fTkToPc[TkI] = fPcN;
    fPcIndex[fPcN] = fPcN;
    fHadrIndex[fHadrN] = fPcN;
    fPcCharge[fPcN] = (float) particles[fHadrN].charge();
    fPcPdgId[fPcN] = (float) particles[fHadrN].pdgId();
    fPcEnergy[fPcN] = (float) particles[fHadrN].energy();
    fPcEt[fPcN] = (float) particles[fHadrN].et();
    fPcP[fPcN] = (float) particles[fHadrN].p();
    fPcPt[fPcN] = (float) particles[fHadrN].pt();
    fPcPx[fPcN] = (float) particles[fHadrN].px();
    fPcPy[fPcN] = (float) particles[fHadrN].py();
    fPcPz[fPcN] = (float) particles[fHadrN].pz();
    fPcTheta[fPcN] = (float) particles[fHadrN].theta();
    fPcEta[fPcN] = (float) particles[fHadrN].eta();
    fPcPhi[fPcN] = (float) particles[fHadrN].phi();
    fPcVx[fPcN] = (float) particles[fHadrN].vx();
    fPcVy[fPcN] = (float) particles[fHadrN].vy();
    fPcVz[fPcN] = (float) particles[fHadrN].vz();
    fPcEcalIso[fPcN] = (float) particles[fHadrN].ecalIso();
    fPcHcalIso[fPcN] = (float) particles[fHadrN].hcalIso();
    fPcTrackIso[fPcN] = (float) particles[fHadrN].trackIso();

    fPcTkQuality[fPcN] = (int) ctftracks[TkI].qualityMask();
    fPcChi2[fPcN] = (float) ctftracks[TkI].chi2();
    fPcNdof[fPcN] = (float) ctftracks[TkI].ndof();
    fPcD0[fPcN] = (float) ctftracks[TkI].d0();
    fPcDz[fPcN] = (float) ctftracks[TkI].dz();
    fPcEtaErr[fPcN] = (float) ctftracks[TkI].etaError();
    fPcPhiErr[fPcN] = (float) ctftracks[TkI].phiError();
    fPcD0Err[fPcN] = (float) ctftracks[TkI].d0Error();
    fPcDzErr[fPcN] = (float) ctftracks[TkI].dzError();
    // hit pattern of the track
    const reco::HitPattern& hits = ctftracks[TkI].hitPattern();
    fPcPixHitN[fPcN] = (int) hits.numberOfValidPixelHits();
    fPcPixLayN[fPcN] = (int) hits.pixelLayersWithMeasurement();
    fPcStripHitN[fPcN] = (int) hits.numberOfValidStripHits();
    fPcStripLayN[fPcN] = (int) hits.stripLayersWithMeasurement();
 
    fHadrN++;
    fPcN++;
  }*/

  for (int i = 0; i != (int) ctftracks.size(); i++) {
    if (fPcN > PARTMAX - 1) break;

    if (fTkToPc[i] != -9999) continue; // don't use tracks that already came from particles
    fPcToTk[fPcN] = i;
    fTkToPc[i] = fPcN;
    fPcIndex[fPcN] = fPcN;
    fMiscTkIndex[fMiscTkN] = fPcN;
    fPcCharge[fPcN] = (float) ctftracks[i].charge();
    fPcP[fPcN] = (float) ctftracks[i].p();
    fPcPt[fPcN] = (float) ctftracks[i].pt();
    fPcPx[fPcN] = (float) ctftracks[i].px();
    fPcPy[fPcN] = (float) ctftracks[i].py();
    fPcPz[fPcN] = (float) ctftracks[i].pz();
    fPcTheta[fPcN] = (float) ctftracks[i].theta();
    fPcEta[fPcN] = (float) ctftracks[i].eta();
    fPcPhi[fPcN] = (float) ctftracks[i].phi();
    fPcVx[fPcN] = (float) ctftracks[i].vx();
    fPcVy[fPcN] = (float) ctftracks[i].vy();
    fPcVz[fPcN] = (float) ctftracks[i].vz();

    fPcTkQuality[fPcN] = (int) ctftracks[i].qualityMask();
    fPcChi2[fPcN] = (float) ctftracks[i].chi2();
    fPcNdof[fPcN] = (float) ctftracks[i].ndof();
    fPcD0[fPcN] = (float) ctftracks[i].d0();
    fPcDz[fPcN] = (float) ctftracks[i].dz();
    fPcEtaErr[fPcN] = (float) ctftracks[i].etaError();
    fPcPhiErr[fPcN] = (float) ctftracks[i].phiError();
    fPcD0Err[fPcN] = (float) ctftracks[i].d0Error();
    fPcDzErr[fPcN] = (float) ctftracks[i].dzError();
    // hit pattern of the track
    const reco::HitPattern& hits = ctftracks[i].hitPattern();
    fPcPixHitN[fPcN] = (int) hits.numberOfValidPixelHits();
    fPcPixLayN[fPcN] = (int) hits.pixelLayersWithMeasurement();
    fPcStripHitN[fPcN] = (int) hits.numberOfValidStripHits();
    fPcStripLayN[fPcN] = (int) hits.stripLayersWithMeasurement();

    fMiscTkN++;
    fPcN++;
  }

  for (int i = 0; i != (int) photons.size(); i++) {
    if (fPcN > PARTMAX - 1) break;

    if (fIsMC&&photons[fPhotN].genParticleRef().isNonnull()) {
      for (int ig = fGnN-1; ig >= 0; ig--) {
        if (fGnPdgId[ig]==(int) photons[fPhotN].genParticleRef()->pdgId() && fGnPt[ig]==(float) photons[fPhotN].genParticleRef()->pt() && fGnEta[ig]==(float) photons[fPhotN].genParticleRef()->eta()) { fPcToGn[fPcN] = ig; break; }
      }
    }
    fPcIndex[fPcN] = fPcN;
    fPhotIndex[fPhotN] = fPcN;
    fPcPdgId[fPcN] = (int) photons[fPhotN].pdgId();
    fPcCharge[fPcN] = (float) photons[fPhotN].charge();
    fPcEnergy[fPcN] = (float) photons[fPhotN].energy();
    fPcEt[fPcN] = (float) photons[fPhotN].et();
    fPcP[fPcN] = (float) photons[fPhotN].p();
    fPcPt[fPcN] = (float) photons[fPhotN].pt();
    fPcPx[fPcN] = (float) photons[fPhotN].px();
    fPcPy[fPcN] = (float) photons[fPhotN].py();
    fPcPz[fPcN] = (float) photons[fPhotN].pz();
    fPcTheta[fPcN] = (float) photons[fPhotN].theta();
    fPcEta[fPcN] = (float) photons[fPhotN].eta();
    fPcPhi[fPcN] = (float) photons[fPhotN].phi();
    fPcVx[fPcN] = (float) photons[fPhotN].vx();
    fPcVy[fPcN] = (float) photons[fPhotN].vy();
    fPcVz[fPcN] = (float) photons[fPhotN].vz();
    fPcEcalIso[fPcN] = (float) photons[fPhotN].ecalIso();
    fPcHcalIso[fPcN] = (float) photons[fPhotN].hcalIso();
    fPcTrackIso[fPcN] = (float) photons[fPhotN].trackIso();
    // photon specific
    //TriggerObjectStandAloneCollection PhotHLTmatches = photons[fPhotN].triggerObjectMatches();
    //if(PhotHLTmatches.size()!=0) fPhotHLTMatch[fPhotN]=true;

    fPhotN++;
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


void PATEventTree::fillJets(const std::vector<pat::Jet>& jets) {
  // vectors of indices to be used for sorting jets by b-tag discriminator (highest to lowest)
  std::vector<int> rankTCHE, rankTCHP, rankP, rankBP, rankSSVHE, rankSSVHP, rankCSV, rankCSVMVA, rankGT, rankSE, rankSM;
  for (unsigned int i = 0; i < jets.size(); i++) {
    if (fJtN > JETMAX - 1) break;

    // underlying candidate information
    fJtIndex[fJtN] = fJtN;
    fJtnConstituents[fJtN] = (int) jets[i].numberOfDaughters();
    fJtn60[fJtN] = (int) jets[i].n60();
    fJtn90[fJtN] = (int) jets[i].n90();
    fJtCharge[fJtN] = (float) jets[i].jetCharge();
    fJtMaxDist[fJtN] = (float) jets[i].maxDistance();
    fJtPhi[fJtN] = (float) jets[i].phi();
    fJtTheta[fJtN] = (float) jets[i].theta();
    fJtEta[fJtN] = (float) jets[i].eta();
    fJtRapidity[fJtN] = (float) jets[i].rapidity();
    fJtP[fJtN] = (float) jets[i].p();
    fJtPt[fJtN] = (float) jets[i].pt();
    fJtPx[fJtN] = (float) jets[i].px();
    fJtPy[fJtN] = (float) jets[i].py();
    fJtPz[fJtN] = (float) jets[i].pz();
    fJtEnergy[fJtN] = (float) jets[i].energy();
    fJtEt[fJtN] = (float) jets[i].et();
    fJtMass[fJtN] = (float) jets[i].mass();
    fJtMt[fJtN] = (float) jets[i].mt();
    fJtVx[fJtN] = (float) jets[i].vx();
    fJtVy[fJtN] = (float) jets[i].vy();
    fJtVz[fJtN] = (float) jets[i].vz();

    // if MC is available
    if (fIsMC) {
      fJtFlavour[fJtN] = (int) jets[i].partonFlavour();
      // match using PAT flavour
      if (abs(fJtFlavour[fJtN])==5) { fJtBFlavIndex[fJtBFlavN]=fJtN; fJtBFlavN++; }
    }

    // PF Jet specific information
    if (jets[i].isPFJet()) {
      fJtnChargedParticles[fJtN] = (int) jets[i].chargedMultiplicity();
      fJtChargedEmEnergy[fJtN] = (float) jets[i].chargedEmEnergy();
      fJtnNeutralParticles[fJtN] = (int) jets[i].neutralMultiplicity();
      fJtNeutralEmEnergy[fJtN] = (float) jets[i].neutralEmEnergy();
      fJtnChargedHadrons[fJtN] = (int) jets[i].chargedHadronMultiplicity();
      fJtChargedHadronEnergy[fJtN] = (float) jets[i].chargedHadronEnergy();
      fJtnNeutralHadrons[fJtN] = (int) jets[i].neutralHadronMultiplicity();
      fJtNeutralHadronEnergy[fJtN] = (float) jets[i].neutralHadronEnergy();
      fJtnPhotons[fJtN] = (int) jets[i].photonMultiplicity();
      fJtPhotonEnergy[fJtN] = (float) jets[i].photonEnergy();
      fJtnElectrons[fJtN] = (int) jets[i].electronMultiplicity();
      fJtElectronEnergy[fJtN] = (float) jets[i].electronEnergy();
      fJtnMuons[fJtN] = (int) jets[i].muonMultiplicity();
      fJtMuonEnergy[fJtN] = (float) jets[i].muonEnergy();
      fJtnHFHadrons[fJtN] = (int) jets[i].HFHadronMultiplicity();
      fJtHFHadronEnergy[fJtN] = (float) jets[i].HFHadronEnergy();
      fJtnHFEMParticles[fJtN] = (int) jets[i].HFEMMultiplicity();
      fJtHFEMEnergy[fJtN] = (float) jets[i].HFEMEnergy();
    }

    // b-tag information
    fJtDiscTCHE[fJtN] = (float) jets[i].bDiscriminator("trackCountingHighEffBJetTags");
    fJtDiscTCHP[fJtN] = (float) jets[i].bDiscriminator("trackCountingHighPurBJetTags");
    fJtDiscP[fJtN] = (float) jets[i].bDiscriminator("jetProbabilityBJetTags");
    fJtDiscBP[fJtN] = (float) jets[i].bDiscriminator("jetBProbabilityBJetTags");
    fJtDiscSSVHE[fJtN] = (float) jets[i].bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    fJtDiscSSVHP[fJtN] = (float) jets[i].bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
    fJtDiscCSV[fJtN] = (float) jets[i].bDiscriminator("combinedSecondaryVertexBJetTags");
    fJtDiscCSVMVA[fJtN] = (float) jets[i].bDiscriminator("combinedSecondaryVertexMVABJetTags");
    fJtDiscGT[fJtN] = (float) jets[i].bDiscriminator("ghostTrackBJetTags");
    fJtDiscSE[fJtN] = (float) jets[i].bDiscriminator("softElectronBJetTags");
    fJtDiscSM[fJtN] = (float) jets[i].bDiscriminator("softMuonBJetTags");
    // determine rank based on discriminator (0=highest disc. value) within jet collection
    fJtRankTCHE[fJtN] = fJtRankTCHP[fJtN] = fJtRankP[fJtN] = fJtRankBP[fJtN] = fJtRankSSVHE[fJtN] = fJtRankSSVHP[fJtN] = fJtRankCSV[fJtN] = fJtRankCSVMVA[fJtN] = fJtRankGT[fJtN] = fJtRankSE[fJtN] = fJtRankSM[fJtN] = fJtN-JtShift;
    // 1st: determine jet i's rank (by disc. value) compared to jets iterated so far
    for (int rank = fJtN-JtShift-1; rank >= 0; rank--) {
      if( fJtDiscTCHE[fJtN]>fJtDiscTCHE[rankTCHE[rank]] ) fJtRankTCHE[fJtN] = rank;
      if( fJtDiscTCHP[fJtN]>fJtDiscTCHP[rankTCHP[rank]] ) fJtRankTCHP[fJtN] = rank;
      if( fJtDiscP[fJtN]>fJtDiscP[rankP[rank]] ) fJtRankP[fJtN] = rank;
      if( fJtDiscBP[fJtN]>fJtDiscBP[rankBP[rank]] ) fJtRankBP[fJtN] = rank;
      if( fJtDiscSSVHE[fJtN]>fJtDiscSSVHE[rankSSVHE[rank]] ) fJtRankSSVHE[fJtN] = rank;
      if( fJtDiscSSVHP[fJtN]>fJtDiscSSVHP[rankSSVHP[rank]] ) fJtRankSSVHP[fJtN] = rank;
      if( fJtDiscCSV[fJtN]>fJtDiscCSV[rankCSV[rank]] ) fJtRankCSV[fJtN] = rank;
      if( fJtDiscCSVMVA[fJtN]>fJtDiscCSVMVA[rankTCHE[rank]] ) fJtRankCSVMVA[fJtN] = rank;
      if( fJtDiscGT[fJtN]>fJtDiscGT[rankGT[rank]] ) fJtRankGT[fJtN] = rank;
      if( fJtDiscSE[fJtN]>fJtDiscSE[rankSE[rank]] ) fJtRankSE[fJtN] = rank;
      if( fJtDiscSM[fJtN]>fJtDiscSM[rankSM[rank]] ) fJtRankSM[fJtN] = rank;
    }
    // 2nd: insert index in rank vector according to rank order (0=first, etc.), creating a vector of jet indices ordered by btag rank
    rankTCHE.insert( rankTCHE.begin()+fJtRankTCHE[fJtN],1,fJtN );
    rankTCHP.insert( rankTCHP.begin()+fJtRankTCHP[fJtN],1,fJtN );
    rankP.insert( rankP.begin()+fJtRankP[fJtN],1,fJtN );
    rankBP.insert( rankBP.begin()+fJtRankBP[fJtN],1,fJtN );
    rankSSVHE.insert( rankSSVHE.begin()+fJtRankSSVHE[fJtN],1,fJtN );
    rankSSVHP.insert( rankSSVHP.begin()+fJtRankSSVHP[fJtN],1,fJtN );
    rankCSV.insert( rankCSV.begin()+fJtRankCSV[fJtN],1,fJtN );
    rankCSVMVA.insert( rankCSVMVA.begin()+fJtRankCSVMVA[fJtN],1,fJtN );
    rankGT.insert( rankGT.begin()+fJtRankGT[fJtN],1,fJtN );
    rankSE.insert( rankSE.begin()+fJtRankSE[fJtN],1,fJtN );
    rankSM.insert( rankSM.begin()+fJtRankSM[fJtN],1,fJtN );


    // HLT
    TriggerObjectStandAloneCollection JetHLTmatches = jets[i].triggerObjectMatches();
    if(JetHLTmatches.size() > 0) {
      fJtHLTN[fJtN] = (int) JetHLTmatches.size();
      for (int ijh = 0; ijh < (int) JetHLTmatches.size(); ijh++) {
        for (int ih = 0; ih < (int) fHLTN; ih++) {
          if(fabs(JetHLTmatches[ijh].pt()-fHLT_Pt[ih])<0.001 && fabs(JetHLTmatches[ijh].eta()-fHLT_Eta[ih])<0.001 && fabs(JetHLTmatches[ijh].phi()-fHLT_Phi[ih])<0.001) { fJtToHLT[fJtN] = ih; fHLT_ToJt[ih] = fJtN; break; }
        }
      }
      if(fJtToHLT[fJtN]>=0) {
        if( fHLT_Jet[fJtToHLT[fJtN]][0] ) fJtHLTMatch[fJtN][0] = true;
        if( fHLT_Jet[fJtToHLT[fJtN]][1] ) fJtHLTMatch[fJtN][1] = true;
      }
    }

    //--------------------------------------------
    //-- Fill information for tracks within jets
    //--------------------------------------------
    // Fill jet to track association variables and jet charge (since normal method doesn't appear to work)
    const reco::TrackRefVector trv = jets[i].associatedTracks();
    int PvTkAssoc[20];
    for(unsigned int j = 0; j < 20; j++) PvTkAssoc[j] = 0;
    for(unsigned int j = 0; j < trv.size(); j++) {
      if( fJtTkN[fJtN] == PARTMAX ) break;
      if (trv[j].isNull()) continue;

      int PcI = -9999;
      PcI = fTkToPc[trv[j].index()];
      fJtToPc[fJtN][fJtTkN[fJtN]] = PcI; //Record index of particle in jet
      fPcToJt[PcI][fPcJtN[PcI]] = fJtN;  //Record index of jet containing track
      if( PcI>=0 && fPcToPv[PcI]>=0 && fPcToPv[PcI]<20 ) PvTkAssoc[fPcToPv[PcI]]++;
      fJtTkN[fJtN]++; //Number of tracks in jet
      fPcJtN[PcI]++;  //Number of jets containing particle
    }

    // fill JtToPv association based on number of tracks in jet assoc. to PV
    for(unsigned int j = 0; j < 20; j++) { 
      if( fJtToPv[fJtN]>=0 && PvTkAssoc[j]>PvTkAssoc[fJtToPv[fJtN]] ) fJtToPv[fJtN] = j;
      else if( fJtToPv[fJtN]<0 && PvTkAssoc[j]>0 ) fJtToPv[fJtN] = j;
    }
    // Fill candidate (dR and PtRel) information
    float JtdRSum = 0.0, JtdPhi, JtdEta, JtdR;
    fJtdRMean[fJtN] = fJtdRMax[fJtN] = fJtPtRelMax[fJtN] = fJtPtRelSum[fJtN] = fJtPullPx[fJtN] = fJtPullPy[fJtN] = fJtPullPz[fJtN] = 0.0;
    for(unsigned int ijp = 0; ijp < jets[i].numberOfDaughters(); ijp++) {
      const reco::Candidate * particle = jets[i].daughter(ijp);
      float PfPx = (float)particle->px(), PfPy = (float)particle->py(), PfPz = (float)particle->pz(), PfPt = (float)particle->pt(), PfP = (float)particle->p(), PfEta = (float)particle->eta();
      float PfDotJt = PfPx*fJtPx[fJtN]+PfPy*fJtPy[fJtN]+PfPz*fJtPz[fJtN];
      float ProjPfOnJt = PfDotJt/fJtP[fJtN];
      float PfPtRel = sqrt(PfP*PfP-ProjPfOnJt*ProjPfOnJt);
      fJtPtRelSum[fJtN] += PfPtRel;
      if( PfPtRel>fJtPtRelMax[fJtN] ) fJtPtRelMax[fJtN] = PfPtRel;
      //fJtPullPx[fJtN] += PfPx - (ProjPfOnJt/fJtP[fJtN])*fJtPx[fJtN]; // Pull is sum of all PtRel vectors (old way)
      fJtPullPx[fJtN] += PfPx - fJtPx[fJtN];
      fJtPullPy[fJtN] += PfPy - fJtPy[fJtN];
      fJtPullPz[fJtN] += PfPz - fJtPz[fJtN];
      JtdPhi = acos( (PfPx*fJtPx[fJtN]+PfPy*fJtPy[fJtN])/(PfPt*fJtPt[fJtN]) );
      JtdEta = PfEta-fJtEta[fJtN];
      JtdR = sqrt( JtdPhi*JtdPhi+JtdEta*JtdEta );
      JtdRSum += JtdR;
      if( JtdR>fJtdRMax[fJtN] ) fJtdRMax[fJtN] = JtdR;
    } // end loop over jet particles
    if( fJtnConstituents[fJtN]>0 ) {
      fJtdRMean[fJtN] = JtdRSum/float(fJtnConstituents[fJtN]);
      fJtPtRelMean[fJtN] = fJtPtRelSum[fJtN]/float(fJtnConstituents[fJtN]);
    }
    //--------------------------------------------
    //-- Fill information for secondary vertices
    //--------------------------------------------
    // Simple secondary vertices
    //fillSecondaryVertices(*jets[i].tagInfoSecondaryVertex("secondaryVertex"), false);
    // Ghost track vertices
    //fillSecondaryVertices(*jets[i].tagInfoSecondaryVertex("ghostTrackVertex"), true);
    fJtN++;
  }
  cout << "before rankstuff" << endl;
  fJtRankTCHE[fJtN] = fJtRankTCHP[fJtN] = fJtRankP[fJtN] = fJtRankBP[fJtN] = fJtRankSSVHE[fJtN] = fJtRankSSVHP[fJtN] = fJtRankCSV[fJtN] = fJtRankCSVMVA[fJtN] = fJtRankGT[fJtN] = fJtRankSE[fJtN] = fJtRankSM[fJtN] = fJtN;
  // 3rd: fill in finalized btag rankings using rank-ordered vectors
  for (int rank = fJtN-JtShift-1; rank >= 0; rank--) {
    fJtRankTCHE[rankTCHE[rank]] = rank;
    fJtRankTCHP[rankTCHP[rank]] = rank;
    fJtRankP[rankP[rank]] = rank;
    fJtRankBP[rankBP[rank]] = rank;
    fJtRankSSVHE[rankSSVHE[rank]] = rank;
    fJtRankSSVHP[rankSSVHP[rank]] = rank;
    fJtRankCSV[rankCSV[rank]] = rank;
    fJtRankCSVMVA[rankCSVMVA[rank]] = rank;
    fJtRankGT[rankGT[rank]] = rank;
    fJtRankSE[rankSE[rank]] = rank;
    fJtRankSM[rankSM[rank]] = rank;
  }
}


void PATEventTree::fillSecondaryVertices(const reco::SecondaryVertexTagInfo& svTagInfo, const bool IsGTV) {
  // Sort Sv by distance
  std::map<float,int> globalIndex;
  std::vector<float> distSort;
  cout << "tag info" << endl;
	cout << svTagInfo.nVertices() << endl;
  
  for(unsigned int isv = 0; isv < svTagInfo.nVertices(); isv++) {
    if( fSvN == SVMAX ) break;
    cout << "here1b" << endl;
    const reco::Vertex &sv = svTagInfo.secondaryVertex(isv);
    cout << "here1a" << endl;
    fSvIndex[fSvN] = fSvN;
    fSvTkN[fSvN] = (int) sv.tracksSize();
    fSvToJt[fSvN] = fJtN;
    if (IsGTV) fJtToGtv[fJtN][fJtGtvN[fJtN]] = fSvN;
    else fJtToSsv[fJtN][fJtSsvN[fJtN]] = fSvN;
    cout << "here1b" <<endl;
    fSvX[fSvN] = (float) sv.x();
    fSvY[fSvN] = (float) sv.y();
    fSvZ[fSvN] = (float) sv.z();
    fSvXe[fSvN] = (float) sv.xError();
    fSvYe[fSvN] = (float) sv.yError();
    fSvZe[fSvN] = (float) sv.zError();
    fSvChi2[fSvN] = (float) sv.chi2();
    fSvNdof[fSvN] = (float) sv.ndof();
    fSvIsGTV[fSvN] = IsGTV;
    fSvDist[fSvN] = (float) svTagInfo.flightDistance(isv, true).value();
    distSort.push_back(fSvDist[fSvN]);
    globalIndex[fSvDist[fSvN]] = fSvN;
    cout << "here2" << endl;
    math::XYZTLorentzVectorD svP4 = sv.p4(0.13957018,0);
    fSvPx[fSvN] = (float) svP4.px();
    fSvPy[fSvN] = (float) svP4.py();
    fSvPz[fSvN] = (float) svP4.pz();
    fSvPt[fSvN] = (float) svP4.pt();
    fSvEta[fSvN] = (float) -log(tan(0.5*acos(svP4.pz()/sqrt(svP4.px()*svP4.px()+svP4.py()*svP4.py()+svP4.pz()*svP4.pz()))));
    fSvMass[fSvN] = (float) svP4.M();
    cout << "here3" << endl;
    int TkN = 0;
    // loop over all tracks in the vertex (assumes each track only links to one SV of each type)
    for(reco::Vertex::trackRef_iterator track = sv.tracks_begin(); track != sv.tracks_end(); ++track) {
      if (IsGTV) fPcToGtv[fTkToPc[track->key()]] = fSvN;
      else fPcToSsv[fTkToPc[track->key()]] = fSvN;
      fSvToPc[fSvN][TkN] = fTkToPc[track->key()];
      TkN++;
    }
    cout << "here4" << endl;
    if (IsGTV) { fJtGtvN[fJtN]++; fGtvN++; }
    else { fJtSsvN[fJtN]++; fSsvN++; }
    fSvN++;
  }
  cout << "here5" << endl;
  // Sort Sv by distance
  std::sort(distSort.begin(), distSort.end());
  // Set Sv Dist and Tau using distance from PV if closest SV, distance from next closest SV otherwise
  for(int isv = 0; isv < (int) distSort.size(); isv++) {
    int gi = globalIndex[distSort[isv]];
    fSvSeqInJt[gi] = isv;
    float dx, dy, dz, momentum, energy, beta, gamma;
    if (isv==0) { dx = fSvX[gi]-fJtVx[fJtN]; dy = fSvY[gi]-fJtVy[fJtN]; dz = fSvZ[gi]-fJtVz[fJtN]; }
    else { dx = fSvX[gi]-fSvX[gi-1]; dy = fSvY[gi]-fSvY[gi-1]; dz = fSvZ[gi]-fSvZ[gi-1]; }
    fSvDist[gi] = sqrt(dx*dx+dy*dy+dz*dz);
    momentum = sqrt(fSvPx[gi]*fSvPx[gi]+fSvPy[gi]*fSvPy[gi]+fSvPz[gi]*fSvPz[gi]);
    energy = sqrt(fSvMass[gi]*fSvMass[gi]+momentum*momentum);
    beta = momentum/energy;
    if (beta<1.0) gamma = 1.0/sqrt(1.0-beta*beta); // avoid NAN DistCM values
    else gamma = 99999;
    fSvTau[gi] = fSvDist[gi]/(beta*29979245800.0);
    fSvDistCM[gi] = gamma*fSvDist[gi];
    fSvTauCM[gi] = fSvTau[gi]/gamma;
  }
}


void PATEventTree::jetDisambiguation() {

  float JtdPhi, JtdEta, JtdR;
  // Associate subjets to fat jets
  for(int ijf = 0; ijf < fJtFatN; ijf++) {
    int fatI = fJtFatIndex[ijf];

    // unfiltered subjet association
    for(int ijs = 0; ijs < fJtSubN; ijs++) {
      int subI = fJtSubIndex[ijs];

      JtdPhi = acos( (fJtPx[fatI]*fJtPx[subI]+fJtPy[fatI]*fJtPy[subI])/(fJtPt[fatI]*fJtPt[subI]) );
      JtdEta = fJtEta[fatI]-fJtEta[subI];
      JtdR = sqrt( JtdPhi*JtdPhi+JtdEta*JtdEta );
      if( JtdR<fJtdRMax[fatI] ) { fSubToFat[ijs] = fatI; fFatSubN[ijf]++; }
    }

    // filtered subjet association
    for(int ijfs = 0; ijfs < fJtFiltN; ijfs++) {
      int filtI = fJtFiltIndex[ijfs];

      JtdPhi = acos( (fJtPx[fatI]*fJtPx[filtI]+fJtPy[fatI]*fJtPy[filtI])/(fJtPt[fatI]*fJtPt[filtI]) );
      JtdEta = fJtEta[fatI]-fJtEta[filtI];
      JtdR = sqrt( JtdPhi*JtdPhi+JtdEta*JtdEta );
      if( JtdR<fJtdRMax[fatI] ) { fFiltToFat[ijfs] = fatI; fFatFiltN[ijf]++; }
    }
  }
}


void PATEventTree::fillMET(const pat::METCollection& METColl) {

  for(unsigned int im = 0; im < METColl.size(); im++) {
    if( fMETN == METMAX ) break;

    fMETIndex[fMETN] = fMETN;
    fMETPhi[fMETN] = (float) METColl[fMETN].phi();
    fMETTheta[fMETN] = (float) METColl[fMETN].theta();
    fMETEta[fMETN] = (float) METColl[fMETN].eta();
    fMETRapidity[fMETN] = (float) METColl[fMETN].rapidity();
    fMETP[fMETN] = (float) METColl[fMETN].p();
    fMETPt[fMETN] = (float) METColl[fMETN].pt();
    fMETPx[fMETN] = (float) METColl[fMETN].px();
    fMETPy[fMETN] = (float) METColl[fMETN].py();
    fMETPz[fMETN] = (float) METColl[fMETN].pz();
    fMETEnergy[fMETN] = (float) METColl[fMETN].energy();
    fMETEt[fMETN] = (float) METColl[fMETN].et();
    fMETMass[fMETN] = (float) METColl[fMETN].mass();
    fMETMt[fMETN] = (float) METColl[fMETN].mt();
    fMETVx[fMETN] = (float) METColl[fMETN].vx();
    fMETVy[fMETN] = (float) METColl[fMETN].vy();
    fMETVz[fMETN] = (float) METColl[fMETN].vz();
    fMETN++;
  } // end loop over MET candidates
}


void PATEventTree::fillJPsiMuMuCand(const reco::CompositeCandidateCollection& JPsiCands, const reco::MuonRefVector& goodMuons, std::vector<TransientTrack>& t_tks) {

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


void PATEventTree::makeJPsiMuTkCand(const reco::MuonRefVector& goodMuons, const std::vector<reco::Track>& ctftracks, std::vector<TransientTrack>& t_tks) {

  for(unsigned int igm = 0; igm < goodMuons.size(); igm++) {
    if( fJPsiN == JPsiMAX ) break;

    for(unsigned int itk = 0; itk < ctftracks.size(); itk++) {
      if( fJPsiN == JPsiMAX ) break;
      if( ctftracks[itk].charge()==goodMuons[igm]->charge() ) continue; // ignore same sign mu/tk combinations
      if( fTkToPc[itk]!=-9999 && fTkToPc[itk]<fMuN ) continue; // ignore tracks that are already identified as muons (to avoid double counting)

      float mue = (float) goodMuons[igm]->energy(), mupx = (float) goodMuons[igm]->px(), mupy = (float) goodMuons[igm]->py(), mupz = (float) goodMuons[igm]->pz(), mumass = (float) goodMuons[igm]->mass(), tkpx = (float) ctftracks[itk].px(), tkpy = (float) ctftracks[itk].py(), tkpz = (float) ctftracks[itk].pz();
      float tke = sqrt(mumass*mumass+tkpx*tkpx+tkpy*tkpy+tkpz*tkpz);
      float jpe = mue+tke, jppx = mupx+tkpx, jppy = mupy+tkpy, jppz = mupz+tkpz;
      float jpmass = sqrt(jpe*jpe-jppx*jppx-jppy*jppy-jppz*jppz);

      //if( jpmass<2.0 || jpmass>4.0 ) continue; // only consider candidates within a loose J/Psi mass window
      fJPsiIndex[fJPsiN] = fJPsiN;
      fJPsiCharge[fJPsiN] = (float) (goodMuons[igm]->charge()+ctftracks[itk].charge());
      fJPsiMass[fJPsiN] = jpmass;
      fJPsiPx[fJPsiN] = jppx;
      fJPsiPy[fJPsiN] = jppy;
      fJPsiPz[fJPsiN] = jppz;
      fJPsiP[fJPsiN] = sqrt(jppx*jppx+jppy*jppy+jppz*jppz);
      fJPsiPt[fJPsiN] = sqrt(jppx*jppx+jppy*jppy);
      fJPsiEnergy[fJPsiN] = jpe;
      fJPsiEt[fJPsiN] = sqrt(jppx*jppx+jppy*jppy+jpmass*jpmass);
      fJPsiMt[fJPsiN] = jpmass*fJPsiPt[fJPsiN]/fJPsiP[fJPsiN];
      if( jppx>0 ) fJPsiPhi[fJPsiN] = atan(jppy/jppx);
      else fJPsiPhi[fJPsiN] = atan(jppy/jppx)+jppy/fabs(jppy)*3.14159265;
      if( jppz>0 ) fJPsiTheta[fJPsiN] = atan(fJPsiPt[fJPsiN]/jppz);
      else fJPsiTheta[fJPsiN] = atan(fJPsiPt[fJPsiN]/jppz)+3.14159265;
      if( fJPsiP[fJPsiN]==fabs(jppz) ) fJPsiEta[fJPsiN] = 9999.0*jppz/fabs(jppz);
      else fJPsiEta[fJPsiN] = 0.5*log((fJPsiP[fJPsiN]+jppz)/(fJPsiP[fJPsiN]-jppz));
      if( jpe==fabs(jppz) ) fJPsiRapidity[fJPsiN] = 9999.0*jppz/fabs(jppz);
      else fJPsiRapidity[fJPsiN] = 0.5*log((jpe+jppz)/(jpe-jppz));

      // now get track information
      int TkI = -9999;
      if(goodMuons[igm]->track().isNonnull()) TkI = (int) goodMuons[igm]->track().index();
      if( TkI>=0 ) fJPsiMuI[fJPsiN][0]=fTkToPc[TkI];
      fJPsiMuI[fJPsiN][1]=fTkToPc[itk];
      // Quality cut variables (only applied to muon)
      bool KinGood = false, HLTGood = false, IsoGood = false, SAGood = false, TrkGood = false;
      if( goodMuons[igm]->pt()>2.0 && fabs(goodMuons[igm]->eta())<2.5 ) KinGood = fJPsiMuCutKin[fJPsiN][0] = true;
      if( TkI>=0 && fTkToPc[TkI]<fMuN && fMuHLTMatch[fTkToPc[TkI]][1] ) HLTGood = fJPsiMuCutHLT[fJPsiN][0] = true;
      if( goodMuons[igm]->isolationR03().sumPt/goodMuons[igm]->pt()<0.15 ) IsoGood = fJPsiMuCutIso[fJPsiN][0] = true;
      if( goodMuons[igm]->numberOfChambers()>=1 && goodMuons[igm]->numberOfMatches()>=2 ) SAGood = fJPsiMuCutSA[fJPsiN][0] = true;
      if( TkI>=0 && fPcPixHitN[fTkToPc[TkI]]>=1 && (fPcPixHitN[fTkToPc[TkI]]+fPcStripHitN[fTkToPc[TkI]])>=11 ) TrkGood = fJPsiMuCutTrk[fJPsiN][0] = true;
      // Determine quality of daughter
      if( KinGood && HLTGood && IsoGood && TrkGood && SAGood ) { fJPsiMuCategory[fJPsiN][0] = 1; fJPsiMuType[fJPsiN][0][0] = true; }
      else if( KinGood && IsoGood && TrkGood && SAGood ) { fJPsiMuCategory[fJPsiN][0] = 2; fJPsiMuType[fJPsiN][0][1] = true; }
      else if( KinGood && TrkGood && SAGood ) { fJPsiMuCategory[fJPsiN][0] = 3; fJPsiMuType[fJPsiN][0][2] = true; }
      else if( KinGood && IsoGood && SAGood ) { fJPsiMuCategory[fJPsiN][0] = 4; fJPsiMuType[fJPsiN][0][3] = true; }
      else if( KinGood && IsoGood && TrkGood ) { fJPsiMuCategory[fJPsiN][0] = 5; fJPsiMuType[fJPsiN][0][4] = true; }

      // set BaseJPsiI = index of highest Pt JPsi whose muons pass basic cuts
      if ( fBaseJPsiI[0]==-9999&&fJPsiMuI[fJPsiN][0]!=-9999&&fJPsiMuI[fJPsiN][1]!=-9999&&fJPsiMuCutSA[fJPsiN][0]&&fJPsiMuCutSA[fJPsiN][1]&&fJPsiMuCutTrk[fJPsiN][0]&&fJPsiMuCutTrk[fJPsiN][1]&&(fJPsiMuCutHLT[fJPsiN][0]||fJPsiMuCutHLT[fJPsiN][1]) ) fBaseJPsiI[0] = fJPsiN;
      else if ( fBaseJPsiI[0]!=-9999&&fBaseJPsiI[1]==-9999&&fJPsiMuI[fJPsiN][0]!=-9999&&fJPsiMuI[fJPsiN][1]!=-9999&&(fJPsiMuI[fJPsiN][0]!=fJPsiMuI[fBaseJPsiI[0]][0]&&fJPsiMuI[fJPsiN][0]!=fJPsiMuI[fBaseJPsiI[0]][1])&&(fJPsiMuI[fJPsiN][1]!=fJPsiMuI[fBaseJPsiI[0]][0]&&fJPsiMuI[fJPsiN][1]!=fJPsiMuI[fBaseJPsiI[0]][1])&&fJPsiMuCutSA[fJPsiN][0]&&fJPsiMuCutSA[fJPsiN][1]&&fJPsiMuCutTrk[fJPsiN][0]&&fJPsiMuCutTrk[fJPsiN][1]&&(fJPsiMuCutHLT[fJPsiN][0]||fJPsiMuCutHLT[fJPsiN][1]) ) fBaseJPsiI[1] = fJPsiN;
      // veto jets if they have muon from JPsi
      /*if( fJPsiMuCategory[fJPsiN][0]>0 && fJPsiMuCategory[fJPsiN][1]>0 && fJPsiMass[0]>2.0 && fJPsiMass[0]<4.0 ) {
        for(int ij = 0; ij < fJtN; ij++) {
          for(int ijt = 0; ijt < fJtTkN[ij]; ijt++) {
            if( fJtToPc[ij][ijt]>=0 && (fJtToPc[ij][ijt]==fJPsiMuI[fJPsiN][0]||fJtToPc[ij][ijt]==fJPsiMuI[fJPsiN][1]) ) fJtVeto[ij]=true;
          } // end loop over jet tracks
        }  // end loop over jets
      }*/

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
    } // end loop over tracks
  } // end loop over muons
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
          float xvecX, xvecY, xvecZ;
          xvecX = fEtabVx[fEtabN]-fPvX[0];
          xvecY = fEtabVy[fEtabN]-fPvY[0];
          xvecZ = fEtabVz[fEtabN]-fPvZ[0];
          fEtabCTxy[fEtabN] = (xvecX*fEtabPx[fEtabN]+xvecY*fEtabPy[fEtabN])/fEtabPt[fEtabN];
          fEtabCT[fEtabN] = (xvecX*fEtabPx[fEtabN]+xvecY*fEtabPy[fEtabN]+xvecZ*fEtabPz[fEtabN])/fEtabP[fEtabN];
          // using vtx kinematics
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
////Building Etab's out of Muon+Transient
//  for(int ijp1 = 0; ijp1 < fJPsiMuMuN; ijp1++) {
//    if( fEtabN == ETABMAX ) break;
//    int ijp2start = fJPsiMuMuN;
//    if( ijp2start <= ijp1 ) ijp2start = ijp1+1;
//
//    for(int ijp2 = ijp2start; ijp2 < fJPsiN; ijp2++) {
//      if( fEtabN == ETABMAX ) break;
//      if( fJPsiMuI[ijp1][0]==-9999 || fJPsiMuI[ijp1][1]==-9999 || fJPsiMuI[ijp2][0]==-9999 || fJPsiMuI[ijp2][1]==-9999 ) continue; // only consider muons we can find
//      if( fJPsiMuI[ijp1][0]==fJPsiMuI[ijp2][0] || fJPsiMuI[ijp1][0]==fJPsiMuI[ijp2][1] || fJPsiMuI[ijp1][1]==fJPsiMuI[ijp2][0] || fJPsiMuI[ijp1][1]==fJPsiMuI[ijp2][1] ) continue; // no sharing muons b/t J/Psi cands
//
//      float ze1 = fJPsiEnergy[ijp1], zpx1 = fJPsiPx[ijp1], zpy1 = fJPsiPy[ijp1], zpz1 = fJPsiPz[ijp1], ze2 = fJPsiEnergy[ijp2], zpx2 = fJPsiPx[ijp2], zpy2 = fJPsiPy[ijp2], zpz2 = fJPsiPz[ijp2];
//      float etabe = ze1+ze2, etabpx = zpx1+zpx2, etabpy = zpy1+zpy2, etabpz = zpz1+zpz2;
//      float etabmass = sqrt(etabe*etabe-etabpx*etabpx-etabpy*etabpy-etabpz*etabpz);
//
//      fEtabIndex[fEtabN] = fEtabN;
//      fEtabPx[fEtabN] = etabpx;
//      fEtabPy[fEtabN] = etabpy;
//      fEtabPz[fEtabN] = etabpz;
//      fEtabPt[fEtabN] = sqrt(etabpx*etabpx+etabpy*etabpy);
//      fEtabP[fEtabN] = sqrt(etabpx*etabpx+etabpy*etabpy+etabpz*etabpz);
//      fEtabEt[fEtabN] = fJPsiEt[ijp1]+fJPsiEt[ijp2];
//      fEtabEnergy[fEtabN] = etabe;
//      fEtabMt[fEtabN] = fJPsiMt[ijp1]+fJPsiMt[ijp2];
//      fEtabMass[fEtabN] = etabmass;
//      if( etabpx>0 ) fEtabPhi[fEtabN] = atan(etabpy/etabpx);
//      else fEtabPhi[fEtabN] = atan(etabpy/etabpx)+etabpy/fabs(etabpy)*3.14159265;
//      if( etabpz>0 ) fEtabTheta[fEtabN] = atan(fEtabPt[fEtabN]/etabpz);
//      else fEtabTheta[fEtabN] = atan(fEtabPt[fEtabN]/etabpz)+3.14159265;
//      if( fEtabP[fEtabN]==fabs(etabpz) ) fEtabEta[fEtabN] = 9999.0*etabpz/fabs(etabpz);
//      else fEtabEta[fEtabN] = 0.5*log((fEtabP[fEtabN]+etabpz)/(fEtabP[fEtabN]-etabpz));
//      if( etabe==fabs(etabpz) ) fEtabRapidity[fEtabN] = 9999.0*etabpz/fabs(etabpz);
//      else fEtabRapidity[fEtabN] = 0.5*log((etabe+etabpz)/(etabe-etabpz));
//      fEtabJPsiI[fEtabN][0]=ijp1;
//      fEtabJPsiI[fEtabN][1]=ijp2;
//      fEtabMuI[fEtabN][0]=fJPsiMuI[ijp1][0];
//      fEtabMuI[fEtabN][1]=fJPsiMuI[ijp1][1];
//      fEtabMuI[fEtabN][2]=fJPsiMuI[ijp2][0];
//      fEtabMuI[fEtabN][3]=fJPsiMuI[ijp2][1];
//      if( ijp1<fJPsiMuMuN ) fEtabMuN[fEtabN] += 2;
//      else fEtabMuN[fEtabN] += 1;
//      if( ijp2<fJPsiMuMuN ) fEtabMuN[fEtabN] += 2;
//      else fEtabMuN[fEtabN] += 1;
//
//      // check if another Eta_b candidate shares the same muons
//      bool sameMu[4];
//      for(int ie = 0; ie < fEtabN; ie++) { // iterate over earlier eta_b
//        for(int i = 0; i < 4; i++) sameMu[i]=false;
//        for(int imu1 = 0; imu1 < 4; imu1++) { // muons in earlier eta_b
//          for(int imu2 = 0; imu2 < 4; imu2++) { // muons in this eta_b
//            if( fEtabMuI[ie][imu1]==fEtabMuI[fEtabN][imu2] ) sameMu[imu2]=true;
//	  }
//	}
//        if( sameMu[0] && sameMu[1] && sameMu[2] && sameMu[3] ) {
//          fEtabDuplicatesI[fEtabN] = ie;
//          break;
//	}
//      }
//
//      // make J/Psi vertex from muons and fill vertex information
//      vector<TransientTrack> mu_tks;
//      if( fPcToTk[fJPsiMuI[ijp1][0]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp1][0]]]);
//      if( fPcToTk[fJPsiMuI[ijp1][1]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp1][1]]]);
//      if( fPcToTk[fJPsiMuI[ijp2][0]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp2][0]]]);
//      if( fPcToTk[fJPsiMuI[ijp2][1]]!=-9999 ) mu_tks.push_back(t_tks[fPcToTk[fJPsiMuI[ijp2][1]]]);
//
//      if( mu_tks.size() == 4 ) {
//        KalmanVertexFitter kvf(true);
//        TransientVertex etab_cand = kvf.vertex(mu_tks);
//        if( etab_cand.isValid() ) {
//          reco::Vertex etab_vtx = etab_cand;
//          const math::XYZTLorentzVectorD etab_mom = etab_vtx.p4(0.1056583,0.0);
//          fEtabChi2[fEtabN]     = (float) etab_vtx.chi2();
//          fEtabNdof[fEtabN]     = (float) etab_vtx.ndof();
//          fEtabVx[fEtabN]       = (float) etab_vtx.x();
//          fEtabVy[fEtabN]       = (float) etab_vtx.y();
//          fEtabVz[fEtabN]       = (float) etab_vtx.z();
//          fEtabVxE[fEtabN]      = (float) etab_vtx.xError();
//          fEtabVyE[fEtabN]      = (float) etab_vtx.yError();
//          fEtabVzE[fEtabN]      = (float) etab_vtx.zError();
//          fEtabVtxPx[fEtabN]    = (float) etab_mom.x();
//          fEtabVtxPy[fEtabN]    = (float) etab_mom.y();
//          fEtabVtxPz[fEtabN]    = (float) etab_mom.z();
//          fEtabVtxPt[fEtabN]    = (float) etab_mom.pt();
//          fEtabVtxP[fEtabN]     = (float) etab_mom.P();
//          fEtabVtxEnergy[fEtabN]= (float) etab_mom.energy();
//          fEtabVtxEt[fEtabN]    = (float) etab_mom.Et();
//          fEtabVtxMass[fEtabN]  = (float) etab_mom.mass();
//          fEtabVtxMt[fEtabN]    = (float) etab_mom.mt();
//          fEtabVtxPhi[fEtabN]   = (float) etab_mom.phi();
//          fEtabVtxTheta[fEtabN] = (float) etab_mom.theta();
//          fEtabVtxEta[fEtabN]   = (float) etab_mom.eta();
//          fEtabVtxRapidity[fEtabN]=(float) etab_mom.Rapidity();
//        }
//      }
//
//      // find Eta_b from best J/Psi candidates
//      if ( (fBaseJPsiI[0]==ijp1&&fBaseJPsiI[1]==ijp2) || (fBaseJPsiI[1]==ijp1&&fBaseJPsiI[1]==ijp2) ) fBaseEtabI=fEtabN;
//
//      // find perp. and long. distance b/t Eta_b vector and J/Psi
//      // refer to http://paulbourke.net/geometry/pointline/
//      if( fEtabVx[fEtabN]!=-9999.0 ) {
//
//        // Points at which tangent line between J/Psi and Eta_b vector intersect
//        float x1, x2, y1, y2, z1, z2, jpsi1T, jpsi1L, jpsi2T, jpsi2L;
//        x1 = x2 = y1 = y2 = z1 = z2 = jpsi1T = jpsi1L = jpsi2T = jpsi2L = -9999.0;
//        float px1, py1, pz1, px2, py2, pz2, px3, py3, pz3;
//        px1 = fEtabVx[fEtabN]-fEtabPx[fEtabN];
//        py1 = fEtabVy[fEtabN]-fEtabPy[fEtabN];
//        pz1 = fEtabVz[fEtabN]-fEtabPz[fEtabN];
//        px2 = fEtabVx[fEtabN]+fEtabPx[fEtabN];
//        py2 = fEtabVy[fEtabN]+fEtabPy[fEtabN];
//        pz2 = fEtabVz[fEtabN]+fEtabPz[fEtabN];
//
//        // find 1st J/Psi distances to Eta_b vector
//        if( fJPsiVx[ijp1]!=-9999.0 ) {
//          px3 = fJPsiVx[fEtabJPsiI[fEtabN][0]];
//          py3 = fJPsiVy[fEtabJPsiI[fEtabN][0]];
//          pz3 = fJPsiVz[fEtabJPsiI[fEtabN][0]];
//
//          float u = ( (px3-px1)*(px2-px1)+(py3-py1)*(py2-py1)+(pz3-pz1)*(pz2-pz1) )/( (px2-px1)*(px2-px1)+(py2-py1)*(py2-py1)+(pz2-pz1)*(pz2-pz1) );
//          fEtabJPsiProjX[fEtabN][0] = x1 = px1 + u*(px2 - px1);
//          fEtabJPsiProjY[fEtabN][0] = y1 = py1 + u*(py2 - py1);
//          fEtabJPsiProjZ[fEtabN][0] = z1 = pz1 + u*(pz2 - pz1);
//
//          jpsi1T = sqrt( (x1-px3)*(x1-px3)+(y1-py3)*(y1-py3)+(z1-pz3)*(z1-pz3) );
//          jpsi1L = sqrt( (x1-fEtabVx[fEtabN])*(x1-fEtabVx[fEtabN])+(y1-fEtabVy[fEtabN])*(y1-fEtabVy[fEtabN])+(z1-fEtabVz[fEtabN])*(z1-fEtabVz[fEtabN]) );
//	}
//
//        // find 2nd J/Psi distances to Eta_b vector
//        if( fJPsiVx[ijp2]!=-9999.0 ) {
//          px3 = fJPsiVx[fEtabJPsiI[fEtabN][1]];
//          py3 = fJPsiVy[fEtabJPsiI[fEtabN][1]];
//          pz3 = fJPsiVz[fEtabJPsiI[fEtabN][1]];
//
//          float u = ( (px3-px1)*(px2-px1)+(py3-py1)*(py2-py1)+(pz3-pz1)*(pz2-pz1) )/( (px2-px1)*(px2-px1)+(py2-py1)*(py2-py1)+(pz2-pz1)*(pz2-pz1) );
//          fEtabJPsiProjX[fEtabN][1] = x2 = px1 + u*(px2 - px1);
//          fEtabJPsiProjY[fEtabN][1] = y2 = py1 + u*(py2 - py1);
//          fEtabJPsiProjZ[fEtabN][1] = z2 = pz1 + u*(pz2 - pz1);
//
//          jpsi2T = sqrt( (x2-px3)*(x2-px3)+(y2-py3)*(y2-py3)+(z2-pz3)*(z2-pz3) );
//          jpsi2L = sqrt( (x2-fEtabVx[fEtabN])*(x2-fEtabVx[fEtabN])+(y2-fEtabVy[fEtabN])*(y2-fEtabVy[fEtabN])+(z2-fEtabVz[fEtabN])*(z2-fEtabVz[fEtabN]) );
//	}
//
//        // find J/Psi distances to each other, and error
//        if( fJPsiVx[ijp1]!=-9999.0 && fJPsiVx[ijp2]!=-9999.0 ) {
//          if( jpsi2L>jpsi1L ) fEtabJPsiDeltaT[fEtabN] = jpsi2T-jpsi1T;
//          else fEtabJPsiDeltaT[fEtabN] = jpsi1T-jpsi2T;
//          if( jpsi2T>jpsi1T ) fEtabJPsiDeltaL[fEtabN] = jpsi2L-jpsi1L;
//          else fEtabJPsiDeltaL[fEtabN] = jpsi1L-jpsi2L;
//
//          // J/Psi to J/Psi error
//          float DeltaX, DeltaY, DeltaZ;
//          DeltaX = fJPsiVx[fEtabJPsiI[fEtabN][0]]-fJPsiVx[fEtabJPsiI[fEtabN][1]];
//          DeltaY = fJPsiVy[fEtabJPsiI[fEtabN][0]]-fJPsiVy[fEtabJPsiI[fEtabN][1]];
//          DeltaZ = fJPsiVz[fEtabJPsiI[fEtabN][0]]-fJPsiVz[fEtabJPsiI[fEtabN][1]];
//          fEtabJPsiVtxErr[fEtabN] = sqrt( pow(DeltaX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2) ) + pow(DeltaY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2) ) + pow(DeltaZ,2)*( pow(fJPsiVzE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVzE[fEtabJPsiI[fEtabN][1]],2) ) ) / sqrt( pow(DeltaX,2)+pow(DeltaY,2)+pow(DeltaZ,2) );
//          fEtabJPsiVtxErrxy[fEtabN] = sqrt( pow(DeltaX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2) ) + pow(DeltaY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2) ) ) / sqrt( pow(DeltaX,2)+pow(DeltaY,2) );
//	}
//
//        // find CT and CTxy
//        if( fPvX[0]!=-9999 && fEtabPt[fEtabN]>0.0 && fEtabP[fEtabN]>0.0 ) {
//          float xvecX, xvecY, xvecZ, pvecX, pvecY, pvecZ;
//          xvecX = fEtabVx[fEtabN]-fPvX[0];
//          xvecY = fEtabVy[fEtabN]-fPvY[0];
//          xvecZ = fEtabVz[fEtabN]-fPvZ[0];
//          pvecX = fEtabPx[fEtabN];
//          pvecY = fEtabPy[fEtabN];
//          pvecZ = fEtabPz[fEtabN];
//          fEtabCTxy[fEtabN] = (xvecX*fEtabPx[fEtabN]+xvecY*fEtabPy[fEtabN])/fEtabPt[fEtabN];
//          fEtabCT[fEtabN] = (xvecX*fEtabPx[fEtabN]+xvecY*fEtabPy[fEtabN]+xvecZ*fEtabPz[fEtabN])/fEtabP[fEtabN];
//          // using vtx kinematics
//          pvecX = fEtabVtxPx[fEtabN];
//          pvecY = fEtabVtxPy[fEtabN];
//          pvecZ = fEtabVtxPz[fEtabN];
//          fEtabVtxCTxy[fEtabN] = (xvecX*fEtabVtxPx[fEtabN]+xvecY*fEtabVtxPy[fEtabN])/fEtabVtxPt[fEtabN];
//          fEtabVtxCT[fEtabN] = (xvecX*fEtabVtxPx[fEtabN]+xvecY*fEtabVtxPy[fEtabN]+xvecZ*fEtabVtxPz[fEtabN])/fEtabVtxP[fEtabN];
//	}
//      }
//
//      // refit PV without muons from 4-mu candidate
//      if( fEtabDuplicatesI[fEtabN] != -9999 ) {
//        fEtabToRePvI[fEtabN] = fEtabToRePvI[fEtabDuplicatesI[fEtabN]];
//      }
//      else if( fPcToPv[fEtabMuI[fEtabN][0]]!=0 && fPcToPv[fEtabMuI[fEtabN][1]]!=0 && fPcToPv[fEtabMuI[fEtabN][2]]!=0 && fPcToPv[fEtabMuI[fEtabN][3]]!=0 ) {
//        fEtabToRePvI[fEtabN] = 0; // no need to refit in this case
//      }
//      else {
//        vector<TransientTrack> refit_tks;
//        for (Int_t ipc=0; ipc<fTkN; ipc++) {
//          if( fEtabMuI[fEtabN][0]==ipc || fEtabMuI[fEtabN][1]==ipc || fEtabMuI[fEtabN][2]==ipc || fEtabMuI[fEtabN][3]==ipc ) continue;
//          if( fPcToTk[ipc]!=-9999 && fPcToPv[ipc]==0 ) refit_tks.push_back(t_tks[fPcToTk[ipc]]);
//	}
//	if( refit_tks.size()>1 ) {
//          KalmanVertexFitter kvf(true);
//          TransientVertex refit_pv = kvf.vertex(refit_tks);
//          if( refit_pv.isValid() ) {
//            if (fAllPvN > PVMAX - 1) break;
//            fPvIndex[fAllPvN] = fEtabToRePvI[fEtabN] = fAllPvN;
//            Vertex new_pv = refit_pv;
//            fPvTkN[fAllPvN] = (int) new_pv.tracksSize();
//            fPvX[fAllPvN] = (float) new_pv.x();
//            fPvY[fAllPvN] = (float) new_pv.y();
//            fPvZ[fAllPvN] = (float) new_pv.z();
//            fPvXe[fAllPvN] = (float) new_pv.xError();
//            fPvYe[fAllPvN] = (float) new_pv.yError();
//            fPvZe[fAllPvN] = (float) new_pv.zError();
//            fPvChi2[fAllPvN] = (float) new_pv.chi2();
//            fPvNdof[fAllPvN] = (float) new_pv.ndof();
//            fPvIsRefit[fAllPvN] = true;
//
//            math::XYZTLorentzVectorD pvP4 = new_pv.p4(0.13957018,0);
//            fPvPx[fAllPvN] = (float) pvP4.px();
//            fPvPy[fAllPvN] = (float) pvP4.py();
//            fPvPz[fAllPvN] = (float) pvP4.pz();
//            fPvPt[fAllPvN] = (float) pvP4.pt();
//            fPvP[fAllPvN] = (float) sqrt( pvP4.pt()*pvP4.pt() + pvP4.pz()*pvP4.pz() );
//            fPvEnergy[fAllPvN] = (float) pvP4.energy();
//            fPvEta[fAllPvN] = (float) -log(tan(0.5*acos(pvP4.pz()/sqrt(pvP4.px()*pvP4.px()+pvP4.py()*pvP4.py()+pvP4.pz()*pvP4.pz()))));
//            fPvMass[fAllPvN] = (float) pvP4.M();
//            fRePvN++; fAllPvN++;
//	  }
//	}
//      }
//      // determine error relative to J/Psi
//      if( fEtabToRePvI[fEtabN]!=-9999 && fEtabJPsiI[fEtabN][0]!=-9999 && fEtabJPsiI[fEtabN][1]!=-9999 ) {
//        float xvecX, xvecY, xvecZ;
//        xvecX = fJPsiVx[fEtabJPsiI[fEtabN][0]]-fPvX[fEtabToRePvI[fEtabN]];
//        xvecY = fJPsiVy[fEtabJPsiI[fEtabN][0]]-fPvY[fEtabToRePvI[fEtabN]];
//        xvecZ = fJPsiVz[fEtabJPsiI[fEtabN][0]]-fPvZ[fEtabToRePvI[fEtabN]];
//        // J/Psi 1
//        // using muon kinematics
//        fEtabJPsiCT[fEtabN][0] = (fJPsiMass[fEtabJPsiI[fEtabN][0]]/fJPsiP[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][0]]+xvecZ*fJPsiPz[fEtabJPsiI[fEtabN][0]])/fJPsiP[fEtabJPsiI[fEtabN][0]];
//        fEtabJPsiCTxy[fEtabN][0] = (fJPsiMass[fEtabJPsiI[fEtabN][0]]/fJPsiPt[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][0]])/fJPsiPt[fEtabJPsiI[fEtabN][0]];
//        fEtabJPsiToPVVtxErr[fEtabN][0] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecZ,2)*( pow(fJPsiVzE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvZe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2)+pow(xvecZ,2) );
//        fEtabJPsiToPVVtxErrxy[fEtabN][0] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][0]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2) );
//        // using vtx kinematics
//        fEtabJPsiVtxCT[fEtabN][0] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][0]]/fJPsiVtxP[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][0]]+xvecZ*fJPsiVtxPz[fEtabJPsiI[fEtabN][0]])/fJPsiVtxP[fEtabJPsiI[fEtabN][0]];
//        fEtabJPsiVtxCTxy[fEtabN][0] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][0]]/fJPsiVtxPt[fEtabJPsiI[fEtabN][0]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][0]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][0]])/fJPsiVtxPt[fEtabJPsiI[fEtabN][0]];
//
//        // J/Psi 2
//        // using muon kinematics
//        xvecX = fJPsiVx[fEtabJPsiI[fEtabN][1]]-fPvX[fEtabToRePvI[fEtabN]];
//        xvecY = fJPsiVy[fEtabJPsiI[fEtabN][1]]-fPvY[fEtabToRePvI[fEtabN]];
//        xvecZ = fJPsiVz[fEtabJPsiI[fEtabN][1]]-fPvZ[fEtabToRePvI[fEtabN]];
//        fEtabJPsiCT[fEtabN][1] = (fJPsiMass[fEtabJPsiI[fEtabN][1]]/fJPsiP[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][1]]+xvecZ*fJPsiPz[fEtabJPsiI[fEtabN][1]])/fJPsiP[fEtabJPsiI[fEtabN][1]];
//        fEtabJPsiCTxy[fEtabN][1] = (fJPsiMass[fEtabJPsiI[fEtabN][1]]/fJPsiPt[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiPy[fEtabJPsiI[fEtabN][1]])/fJPsiPt[fEtabJPsiI[fEtabN][1]];
//        fEtabJPsiToPVVtxErr[fEtabN][1] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecZ,2)*( pow(fJPsiVzE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvZe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2)+pow(xvecZ,2) );
//        fEtabJPsiToPVVtxErrxy[fEtabN][1] = sqrt( pow(xvecX,2)*( pow(fJPsiVxE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvXe[fEtabToRePvI[fEtabN]],2) ) + pow(xvecY,2)*( pow(fJPsiVyE[fEtabJPsiI[fEtabN][1]],2)+pow(fPvYe[fEtabToRePvI[fEtabN]],2) ) ) / sqrt( pow(xvecX,2)+pow(xvecY,2) );
//        // using vtx kinematics
//        fEtabJPsiVtxCT[fEtabN][1] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][1]]/fJPsiVtxP[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][1]]+xvecZ*fJPsiVtxPz[fEtabJPsiI[fEtabN][1]])/fJPsiVtxP[fEtabJPsiI[fEtabN][1]];
//        fEtabJPsiVtxCTxy[fEtabN][1] = (fJPsiVtxMass[fEtabJPsiI[fEtabN][1]]/fJPsiVtxPt[fEtabJPsiI[fEtabN][1]])*(xvecX*fJPsiVtxPx[fEtabJPsiI[fEtabN][1]]+xvecY*fJPsiVtxPy[fEtabJPsiI[fEtabN][1]])/fJPsiVtxPt[fEtabJPsiI[fEtabN][1]];
//      }
//
//      fEtabN++;
//    } //end loop over second dimu cand
//  } // end loop over first dimu cand
}


void PATEventTree::makeHiggsCand(const int startJet, const int endJet) {

  for(int ij1 = startJet; ij1 < endJet; ij1++) {
    if( fJtPt[ij1]<15.0  || fJtVeto[ij1] ) continue; // jet1 cuts
    if( fHN == HMAX ) break;

    for(int ij2 = ij1+1; ij2 <= endJet; ij2++) {
      if( fJtPt[ij2]<15.0 || fJtVeto[ij2] ) continue; // jet2 cuts
      if( fHN == HMAX ) break;

      float je1 = fJtEnergy[ij1], jpx1 = fJtPx[ij1], jpy1 = fJtPy[ij1], jpz1 = fJtPz[ij1], je2 = fJtEnergy[ij2], jpx2 = fJtPx[ij2], jpy2 = fJtPy[ij2], jpz2 = fJtPz[ij2];
      float he = je1+je2, hpx = jpx1+jpx2, hpy = jpy1+jpy2, hpz = jpz1+jpz2;
      float hmass = sqrt(he*he-hpx*hpx-hpy*hpy-hpz*hpz);
      if( hmass<50 || hmass>200 ) continue; // higgs cuts

      fHIndex[fHN] = fHN;
      fHPx[fHN] = hpx;
      fHPy[fHN] = hpy;
      fHPz[fHN] = hpz;
      fHPt[fHN] = sqrt(hpx*hpx+hpy*hpy);
      fHP[fHN] = sqrt(hpx*hpx+hpy*hpy+hpz*hpz);
      fHEt[fHN] = fJtEt[ij1]+fJtEt[ij2];
      fHEnergy[fHN] = he;
      fHMt[fHN] = fJtMt[ij1]+fJtMt[ij2];
      fHMass[fHN] = hmass;
      fHPhi[fHN] = (fJtPt[ij1]*fJtPhi[ij1]+fJtPt[ij2]*fJtPhi[ij2])/(fJtPt[ij1]+fJtPt[ij2]);
      fHTheta[fHN] = (fJtP[ij1]*fJtTheta[ij1]+fJtP[ij2]*fJtTheta[ij2])/(fJtP[ij1]+fJtP[ij2]);
      fHEta[fHN] = (fJtP[ij1]*fJtEta[ij1]+fJtP[ij2]*fJtEta[ij2])/(fJtP[ij1]+fJtP[ij2]);
      fHRapidity[fHN] = 0.5*log((he+hpz)/(he-hpz));
      fHVx[fHN] = (fJtPt[ij1]*fJtVx[ij1]+fJtPt[ij2]*fJtVx[ij2])/(fJtPt[ij1]+fJtPt[ij2]);
      fHVy[fHN] = (fJtPt[ij1]*fJtVy[ij1]+fJtPt[ij2]*fJtVy[ij2])/(fJtPt[ij1]+fJtPt[ij2]);
      fHVz[fHN] = (fJtP[ij1]*fJtVz[ij1]+fJtP[ij2]*fJtVz[ij2])/(fJtPz[ij1]+fJtPz[ij2]);
      fHJtI[fHN][0]=ij1;
      fHJtI[fHN][1]=ij2;
      fHN++;
    } //end loop over second jet
  } // end loop over first jet
}


void PATEventTree::fillTopology() {

  // ----------------------------------------------------------------------
  // -- Find Sphericity and Aplanarity
  // ----------------------------------------------------------------------
  TMatrixDSym S_Matrix(3);
  const double PI=3.14159265;
  double P, PX, PY, PZ, P2, PX2, PY2, PZ2, PXY, PXZ, PYZ, NP;
  P = PX = PY = PZ = P2 = PX2 = PY2 = PZ2 = PXY = PXZ = PYZ = NP = 0;
  int MuStart = 0;
  int MuEnd = MuStart+fMuN;
  int ElecStart = fMuN;
  int ElecEnd = ElecStart+fElecN;
  int PhotStart = fTkN;
  int PhotEnd = PhotStart+fPhotN;

  for (int i = MuStart; i < MuEnd; i++) {
    P = P + (double) fPcP[i];
    PX = PX + (double) fPcPx[i];
    PY = PY + (double) fPcPy[i];
    PZ = PZ + (double) fPcPz[i];
    P2 = P2 + (double) fPcP[i]*fPcP[i];
    PX2 = PX2 + (double) fPcPx[i]*fPcPx[i];
    PY2 = PY2 + (double) fPcPy[i]*fPcPy[i];
    PZ2 = PZ2 + (double) fPcPz[i]*fPcPz[i];
    PXY = PXY + (double) fPcPx[i]*fPcPy[i];
    PXZ = PXZ + (double) fPcPx[i]*fPcPz[i];
    PYZ = PYZ + (double) fPcPy[i]*fPcPz[i];
  }

  for (int i = ElecStart; i < ElecEnd; i++) {
    P = P + (double) fPcP[i];
    PX = PX + (double) fPcPx[i];
    PY = PY + (double) fPcPy[i];
    PZ = PZ + (double) fPcPz[i];
    P2 = P2 + (double) fPcP[i]*fPcP[i];
    PX2 = PX2 + (double) fPcPx[i]*fPcPx[i];
    PY2 = PY2 + (double) fPcPy[i]*fPcPy[i];
    PZ2 = PZ2 + (double) fPcPz[i]*fPcPz[i];
    PXY = PXY + (double) fPcPx[i]*fPcPy[i];
    PXZ = PXZ + (double) fPcPx[i]*fPcPz[i];
    PYZ = PYZ + (double) fPcPy[i]*fPcPz[i];
  }

  for (int i = PhotStart; i < PhotEnd; i++) {
    P = P + (double) fPcP[i];
    PX = PX + (double) fPcPx[i];
    PY = PY + (double) fPcPy[i];
    PZ = PZ + (double) fPcPz[i];
    P2 = P2 + (double) fPcP[i]*fPcP[i];
    PX2 = PX2 + (double) fPcPx[i]*fPcPx[i];
    PY2 = PY2 + (double) fPcPy[i]*fPcPy[i];
    PZ2 = PZ2 + (double) fPcPz[i]*fPcPz[i];
    PXY = PXY + (double) fPcPx[i]*fPcPy[i];
    PXZ = PXZ + (double) fPcPx[i]*fPcPz[i];
    PYZ = PYZ + (double) fPcPy[i]*fPcPz[i];
  }

  for (int i = 0; i < fJtStandN; i++) {
    P = P + (double) fJtP[i];
    PX = PX + (double) fJtPx[i];
    PY = PY + (double) fJtPy[i];
    PZ = PZ + (double) fJtPz[i];
    P2 = P2 + (double) fJtP[i]*fJtP[i];
    PX2 = PX2 + (double) fJtPx[i]*fJtPx[i];
    PY2 = PY2 + (double) fJtPy[i]*fJtPy[i];
    PZ2 = PZ2 + (double) fJtPz[i]*fJtPz[i];
    PXY = PXY + (double) fJtPx[i]*fJtPy[i];
    PXZ = PXZ + (double) fJtPx[i]*fJtPz[i];
    PYZ = PYZ + (double) fJtPy[i]*fJtPz[i];
  }

  S_Matrix(0,0) = PX2/P2; S_Matrix(0,1) = PXY/P2; S_Matrix(0,2) = PXZ/P2;
  S_Matrix(1,0) = PXY/P2; S_Matrix(1,1) = PY2/P2; S_Matrix(1,2) = PYZ/P2;
  S_Matrix(2,0) = PXZ/P2; S_Matrix(2,1) = PYZ/P2; S_Matrix(2,2) = PZ2/P2;

  TMatrixDSymEigen pTensor(S_Matrix);
  if (!std::isnan(pTensor.GetEigenValues()[0])&&!std::isnan(pTensor.GetEigenValues()[1])&&!std::isnan(pTensor.GetEigenValues()[2])) {
    double tmp = 0;
    fEvLambda[2] = (float) pTensor.GetEigenValues()[0];
    fEvLambda[1] = (float) pTensor.GetEigenValues()[1];
    fEvLambda[0] = (float) pTensor.GetEigenValues()[2];
    if (fEvLambda[2] < fEvLambda[0]) { tmp=fEvLambda[2]; fEvLambda[2]=fEvLambda[0]; fEvLambda[0]=tmp; }
    if (fEvLambda[2] < fEvLambda[1]) { tmp=fEvLambda[2]; fEvLambda[2]=fEvLambda[1]; fEvLambda[1]=tmp; }
    if (fEvLambda[1] < fEvLambda[0]) { tmp=fEvLambda[1]; fEvLambda[1]=fEvLambda[0]; fEvLambda[0]=tmp; }
    fEvSphericity = (fEvLambda[1]+fEvLambda[2]);
    fEvAplanarity = fEvLambda[2];
  }

  // ----------------------------------------------------------------------
  // -- Find Thrust, Major, and Minor)
  // ----------------------------------------------------------------------
  TVector3 n_tmp(0,0,0);
  TVector3 n(0,0,0);
  TVector3 nT(0,0,0);
  TVector3 nMinor(0,0,0);
  double Thrust_tmp = 0;
//  double highestNP=0;

  // Calculation of the Thrust
  for(unsigned int i=0; i<720; i++) { // iterate over Phi in half-degree increments
    for(unsigned int j=0; j<360; j++) { // iterate over Theta in half-degree increments
      n_tmp.SetX(cos((PI/360.)*i)*sin((PI/360.)*j));
      n_tmp.SetY(sin((PI/360.)*i)*sin((PI/360.)*j));
      n_tmp.SetZ(cos((PI/360.)*j));
      n_tmp = n_tmp.Unit();
      NP = 0;

      for(int k = MuStart; k < MuEnd; k++) NP = NP + fabs(n_tmp.x()*double(fPcPx[k]) + n_tmp.y()*double(fPcPy[k]) + n_tmp.z()*double(fPcPz[k]));
      for(int k = ElecStart; k < ElecEnd; k++) NP = NP + fabs(n_tmp.x()*double(fPcPx[k]) + n_tmp.y()*double(fPcPy[k]) + n_tmp.z()*double(fPcPz[k]));
      for(int k = PhotStart; k < PhotEnd; k++) NP = NP + fabs(n_tmp.x()*double(fPcPx[k]) + n_tmp.y()*double(fPcPy[k]) + n_tmp.z()*double(fPcPz[k]));
      for(int k = 0; k < fJtStandN; k++) NP = NP + fabs(n_tmp.x()*double(fJtPx[k]) + n_tmp.y()*double(fJtPy[k]) + n_tmp.z()*double(fJtPz[k]));
      Thrust_tmp = NP/P;

      if ( (float) Thrust_tmp > fEvThrust) {
        n = n_tmp;
        fEvThrust = (float) Thrust_tmp;
      }
    }
  }

  // Calculation of the Thrust Major:
  if ( (fMuN+fElecN+fPhotN+fJtStandN) > 1 ) {
    n_tmp = n.Orthogonal();
    n_tmp = n_tmp.Unit();
    for(unsigned int i=0; i<720; i++) { // rotate in half degree increments around n
      n_tmp.Rotate((PI/360.) * (double) i, n);
      NP = 0.;
      for (int j = MuStart; j < MuEnd; j++) NP = NP + fabs(n_tmp.x()*double(fPcPx[j]) + n_tmp.y()*double(fPcPy[j]) + n_tmp.z()*double(fPcPz[j]));
      for (int j = ElecStart; j < ElecEnd; j++) NP = NP + fabs(n_tmp.x()*double(fPcPx[j]) + n_tmp.y()*double(fPcPy[j]) + n_tmp.z()*double(fPcPz[j]));
      for (int j = PhotStart; j < PhotEnd; j++) NP = NP + fabs(n_tmp.x()*double(fPcPx[j]) + n_tmp.y()*double(fPcPy[j]) + n_tmp.z()*double(fPcPz[j]));
      for (int j = 0; j < fJtStandN; j++) NP = NP + fabs(n_tmp.x()*double(fJtPx[j]) + n_tmp.y()*double(fJtPy[j]) + n_tmp.z()*double(fJtPz[j]));
      Thrust_tmp = NP/P;

      if ( (float) Thrust_tmp > fEvThrust_Major) {
        nT = n_tmp;
        fEvThrust_Major = (float) Thrust_tmp;
        nMinor = nT.Cross(n);
      }
    }

    // Calculation of the Thrust Minor:
    nMinor = nMinor.Unit();
    NP = 0;
    for(int i = MuStart; i < MuEnd; i++) NP = NP + fabs(nMinor.x()*double(fPcPx[i]) + nMinor.y()*double(fPcPy[i]) + nMinor.z()*double(fPcPz[i]));
    for(int i = ElecStart; i < ElecEnd; i++) NP = NP + fabs(nMinor.x()*double(fPcPx[i]) + nMinor.y()*double(fPcPy[i]) + nMinor.z()*double(fPcPz[i]));
    for(int i = PhotStart; i < PhotEnd; i++) NP = NP + fabs(nMinor.x()*double(fPcPx[i]) + nMinor.y()*double(fPcPy[i]) + nMinor.z()*double(fPcPz[i]));
    for(int i = 0; i < fJtStandN; i++) NP = NP + fabs(nMinor.x()*double(fJtPx[i]) + nMinor.y()*double(fJtPy[i]) + nMinor.z()*double(fJtPz[i]));
    fEvThrust_Minor = (float) NP/P;
  }

  // ----------------------------------------------------------------------
  // -- Find Fox-Wolfram momenta (1st to 6th), modified for hadron collider and using a Legendre polynomials expansion
  // ----------------------------------------------------------------------
  for (int i = 0; i < 7; i++) fEvFW[i] = 0.0;
  float JtSumEt = 0.0;
  for (int i = 0; i < fJtStandN; i++) JtSumEt = JtSumEt + fJtEt[i];

  for (int i = 0; i < fJtStandN; i++) {
    for (int j = 0; j < fJtStandN; j++) {
      float ET_ij_over_ETSum2 = fJtEt[i]*fJtEt[j] / (JtSumEt*JtSumEt);
      float cosTheta_ij = (fJtPx[i]*fJtPx[j]+fJtPy[i]*fJtPy[j]+fJtPz[i]*fJtPz[j])/(fJtP[i]*fJtP[j]);
      fEvFW[0] += ET_ij_over_ETSum2;
      fEvFW[1] += ET_ij_over_ETSum2 * cosTheta_ij;
      fEvFW[2] += ET_ij_over_ETSum2 * 0.5   *(  3.0*pow(cosTheta_ij,2)-  1.0);
      fEvFW[3] += ET_ij_over_ETSum2 * 0.5   *(  5.0*pow(cosTheta_ij,3)-  3.0*cosTheta_ij);
      fEvFW[4] += ET_ij_over_ETSum2 * 0.125 *( 35.0*pow(cosTheta_ij,4)- 30.0*pow(cosTheta_ij,2)+ 3.0);
      fEvFW[5] += ET_ij_over_ETSum2 * 0.125 *( 63.0*pow(cosTheta_ij,5)- 70.0*pow(cosTheta_ij,3)+ 15.0*cosTheta_ij);
      fEvFW[6] += ET_ij_over_ETSum2 * 0.0625*(231.0*pow(cosTheta_ij,6)-315.0*pow(cosTheta_ij,4)+105.0*pow(cosTheta_ij,2)-5.0);
    }
  }

  // find reco jets corresponding to B-hadrons
  if (fIsMC&&(fGnBN>0)) {
    std::vector<int> JtdRMatchI, JtFiltdRMatchI;
    std::vector<float> JtdRValue, JtFiltdRValue;
    float JtdPhi, JtdEta, JtdR;
    for(int igb = 0; igb < fGnBN; igb++) {

      // match to standard jets
      JtdRMatchI.push_back(-9999); JtdRValue.push_back(9999.0);
      for(int ij = 0; ij < fJtStandN; ij++) {
        int jetI = fJtStandIndex[ij];
        // match jet by direction dR compared to B hadron
        JtdPhi = acos( (fGnPx[fGnBIndex[igb]]*fJtPx[jetI]+fGnPy[fGnBIndex[igb]]*fJtPy[jetI])/(fGnPt[fGnBIndex[igb]]*fJtPt[jetI]) );
        JtdEta = fGnEta[fGnBIndex[igb]]-fJtEta[jetI];
        JtdR = sqrt( JtdPhi*JtdPhi+JtdEta*JtdEta );
        if( JtdR<fJtdRMax[jetI] && JtdR<JtdRValue[igb] ) { JtdRMatchI[igb]=jetI; JtdRValue[igb]=JtdR; }
      } // end loop over jets
      if ( JtdRMatchI[igb] != -9999 ) {
        fJtBdRMatch[JtdRMatchI[igb]]=true;
        fJtBdRIndex[fJtBdRN]=JtdRMatchI[igb];
        fJtToBdRIndex[fJtBdRN]=fGnBIndex[igb];
        fJtBdR[fJtBdRN]=JtdRValue[igb];
        fJtBdRN++;
      }

      if (fUseFatJets) {
        // match to unfiltered subjets
        JtdRMatchI[igb]=-9999; JtdRValue[igb]=9999.0;
        for(int ij = 0; ij < fJtSubN; ij++) {
          int jetI = fJtSubIndex[ij];
          // match jet by direction dR compared to B hadron
          JtdPhi = acos( (fGnPx[fGnBIndex[igb]]*fJtPx[jetI]+fGnPy[fGnBIndex[igb]]*fJtPy[jetI])/(fGnPt[fGnBIndex[igb]]*fJtPt[jetI]) );
          JtdEta = fGnEta[fGnBIndex[igb]]-fJtEta[jetI];
          JtdR = sqrt( JtdPhi*JtdPhi+JtdEta*JtdEta );
          if ( JtdR<fJtdRMax[jetI] && JtdR<JtdRValue[igb] ) { JtdRMatchI[igb]=jetI; JtdRValue[igb]=JtdR; }
        } // end loop over jets
        if ( JtdRMatchI[igb] != -9999 ) {
          fJtBdRMatch[JtdRMatchI[igb]]=true;
          fJtBdRIndex[fJtBdRN]=JtdRMatchI[igb];
          fJtToBdRIndex[fJtBdRN]=fGnBIndex[igb];
          fJtBdR[fJtBdRN]=JtdRValue[igb];
          fJtBdRN++;
        }

        // match to filtered subjets
        JtdRMatchI[igb]=-9999; JtdRValue[igb]=9999.0;
        for(int ij = 0; ij < fJtFiltN; ij++) {
          int jetI = fJtFiltIndex[ij];
          // match jet by direction dR compared to B hadron
          JtdPhi = acos( (fGnPx[fGnBIndex[igb]]*fJtPx[jetI]+fGnPy[fGnBIndex[igb]]*fJtPy[jetI])/(fGnPt[fGnBIndex[igb]]*fJtPt[jetI]) );
          JtdEta = fGnEta[fGnBIndex[igb]]-fJtEta[jetI];
          JtdR = sqrt( JtdPhi*JtdPhi+JtdEta*JtdEta );
          if ( JtdR<fJtdRMax[jetI] && JtdR<JtdRValue[igb] ) { JtdRMatchI[igb]=jetI; JtdRValue[igb]=JtdR; }
        } // end loop over jets
        if ( JtdRMatchI[igb] != -9999 ) {
          fJtBdRMatch[JtdRMatchI[igb]]=true;
          fJtBdRIndex[fJtBdRN]=JtdRMatchI[igb];
          fJtToBdRIndex[fJtBdRN]=fGnBIndex[igb];
          fJtBdR[fJtBdRN]=JtdRValue[igb];
          fJtBdRN++; 
        }
      }
    } // end loop over end state B-hadrons
  }

  // -----------------------------------------------
  // -- Find JPsi and Etab 4-mom and interesting indices for signal events
  // -----------------------------------------------
  // Only for JPsi and Etab events
  if (fIsMC) {
    for(int ig = 0; ig < fGnN; ig++) {
      int PdgId = abs(fGnPdgId[ig]);

      // Find Etab, JPsi, muon indices
      if (fIsEtabJPsi&&fEtabI==-9999&&PdgId==551&&fGnNDaughters[ig]!=0&&abs(fGnPdgId[fGnDaughterIndex[ig][0]])==443&&abs(fGnPdgId[fGnDaughterIndex[ig][1]])==443) {
        fEtabI = ig;
      } else if (fIsJPsiMuMu&&fJPsiI[0]==-9999&&PdgId==443&&fGnNDaughters[ig]!=0&&abs(fGnPdgId[fGnDaughterIndex[ig][0]])==13&&abs(fGnPdgId[fGnDaughterIndex[ig][1]])==13) {
        fJPsiI[0] = ig;
        if (fGnPdgId[fGnDaughterIndex[ig][0]]==-13) { fMuI[0][0] = fGnDaughterIndex[ig][0]; fMuI[0][1] = fGnDaughterIndex[ig][1]; }
        else { fMuI[0][1] = fGnDaughterIndex[ig][0]; fMuI[0][0] = fGnDaughterIndex[ig][1]; }
      } else if (fIsJPsiMuMu&&fJPsiI[1]==-9999&&PdgId==443&&fGnNDaughters[ig]!=0&&abs(fGnPdgId[fGnDaughterIndex[ig][0]])==13&&abs(fGnPdgId[fGnDaughterIndex[ig][1]])==13) {
        fJPsiI[1] = ig;
        if (fGnPdgId[fGnDaughterIndex[ig][0]]==-13) { fMuI[1][0] = fGnDaughterIndex[ig][0]; fMuI[1][1] = fGnDaughterIndex[ig][1]; }
        else { fMuI[1][1] = fGnDaughterIndex[ig][0]; fMuI[1][0] = fGnDaughterIndex[ig][1]; }
      }
    } // end loop over gen particles

    if (fIsJPsiMuMu) {
      // Sort J/Psi and muons by pT 
      int tempI;
      // sort J/Psi by pT
      if( fJPsiI[0]!=-9999 && fJPsiI[1]!=-9999 && fGnPt[fJPsiI[0]]<fGnPt[fJPsiI[1]] ) {
        tempI=fJPsiI[1];  fJPsiI[1]=fJPsiI[0];   fJPsiI[0]=tempI;
        tempI=fMuI[1][0]; fMuI[1][0]=fMuI[0][0]; fMuI[0][0]=tempI;
        tempI=fMuI[1][1]; fMuI[1][1]=fMuI[0][1]; fMuI[0][1]=tempI;
      }
      for( int ijp = 0; ijp < 2; ijp++ ) {
        // sort muons within J/Psi by pT
        if( fMuI[ijp][0]!=-9999 && fMuI[ijp][1]!=-9999 && fGnPt[fMuI[ijp][0]]<fGnPt[fMuI[ijp][1]] ) {
          tempI=fMuI[ijp][1]; fMuI[ijp][1]=fMuI[ijp][0]; fMuI[ijp][0]=tempI;
        }
      }
      // sort muons by pT
      fMuByPtI[0] = fMuI[0][0]; fMuByPtI[1] = fMuI[0][1]; fMuByPtI[2] = fMuI[1][0]; fMuByPtI[3] = fMuI[1][1];
      // ensure unmatched entries fall to the back
      for( int im = 0; im < 3; im++ ) {
        if( fMuByPtI[im]==-9999 ) {
          for( int im2 = im+1; im2 < 4; im2++ ) fMuByPtI[im] = fMuByPtI[im2];
          fMuByPtI[3] = -9999;
        }
      }
      // sort muons so that highest pT always comes first
      for( int im = 0; im < 4; im++ ) {
        if( fMuByPtI[im]==-9999 ) continue;
        for( int im2 = im+1; im2 < 4; im2++ ) {
          if( fMuByPtI[im2]==-9999 ) continue;
          if( fGnPt[fMuByPtI[im]]<fGnPt[fMuByPtI[im2]] ) {
              tempI=fMuByPtI[im]; fMuByPtI[im]=fMuByPtI[im2]; fMuByPtI[im2]=tempI;
          }
        }
      }

    // matching reco particles to MC mu and b
      float Mu11dR, Mu12dR, Mu21dR, Mu22dR, Mu11dRMatch, Mu12dRMatch, Mu21dRMatch, Mu22dRMatch;
      Mu11dRMatch = Mu12dRMatch = Mu21dRMatch = Mu22dRMatch = 9999.0;
      for(int ip = 0; ip < fPcN; ip++) {
        // find reco muons from JPsi, matching by charge and smallest dR
        if ( fMuI[0][0]!=-9999 && fPcCharge[ip]==fGnCharge[fMuI[0][0]] ) {
          Mu11dR = sqrt( pow((fPcEta[ip]-fGnEta[fMuI[0][0]]),2)+pow((fPcPhi[ip]-fGnPhi[fMuI[0][0]]),2) );
          if (Mu11dR<Mu11dRMatch&&Mu11dR<0.5) { fMudRMatchI[0][0]=ip; Mu11dRMatch=Mu11dR; }
        }
        if ( fMuI[0][1]!=-9999 && fPcCharge[ip]==fGnCharge[fMuI[0][1]] ) {
          Mu12dR = sqrt( pow((fPcEta[ip]-fGnEta[fMuI[0][1]]),2)+pow((fPcPhi[ip]-fGnPhi[fMuI[0][1]]),2) );
          if (Mu12dR<Mu12dRMatch&&Mu12dR<0.5) { fMudRMatchI[0][1]=ip; Mu12dRMatch=Mu12dR; }
        }
        if ( fMuI[1][0]!=-9999 && fPcCharge[ip]==fGnCharge[fMuI[1][0]] ) {
          Mu21dR = sqrt( pow((fPcEta[ip]-fGnEta[fMuI[1][0]]),2)+pow((fPcPhi[ip]-fGnPhi[fMuI[1][0]]),2) );
          if (Mu21dR<Mu21dRMatch&&Mu21dR<0.5) { fMudRMatchI[1][0]=ip; Mu21dRMatch=Mu21dR; }
        }
        if ( fMuI[1][1]!=-9999 && fPcCharge[ip]==fGnCharge[fMuI[1][1]] ) {
          Mu22dR = sqrt( pow((fPcEta[ip]-fGnEta[fMuI[1][1]]),2)+pow((fPcPhi[ip]-fGnPhi[fMuI[1][1]]),2) );
          if (Mu22dR<Mu22dRMatch&&Mu22dR<0.5) { fMudRMatchI[1][1]=ip; Mu22dRMatch=Mu22dR; }
        }
      } // end loop over particles
      for( int im = 0; im < 4; im++ ) {
        if( fMuByPtI[im]==fMuI[0][0] ) fMuByPtMatchI[im] = fMudRMatchI[0][0];
        else if( fMuByPtI[im]==fMuI[0][1] ) fMuByPtMatchI[im] = fMudRMatchI[0][1];
        else if( fMuByPtI[im]==fMuI[1][0] ) fMuByPtMatchI[im] = fMudRMatchI[1][0];
        else if( fMuByPtI[im]==fMuI[1][1] ) fMuByPtMatchI[im] = fMudRMatchI[1][1];
      }

      // find J/Psi cand that best matches MC J/Psi
      for(int ijp = 0; ijp < fJPsiN; ijp++) {
        // match J/Psi cand. by mu dR match
        if ( fMudRMatchI[0][0]!=-9999&&fMudRMatchI[0][1]!=-9999&&( (fMudRMatchI[0][0]==fJPsiMuI[ijp][0]&&fMudRMatchI[0][1]==fJPsiMuI[ijp][1])||(fMudRMatchI[0][0]==fJPsiMuI[ijp][1]&&fMudRMatchI[0][1]==fJPsiMuI[ijp][0]) ) ) fJPsidRMatchI[0]=ijp;
        if ( fMudRMatchI[1][0]!=-9999&&fMudRMatchI[1][1]!=-9999&&( (fMudRMatchI[1][0]==fJPsiMuI[ijp][0]&&fMudRMatchI[1][1]==fJPsiMuI[ijp][1])||(fMudRMatchI[1][0]==fJPsiMuI[ijp][1]&&fMudRMatchI[1][1]==fJPsiMuI[ijp][0]) ) ) fJPsidRMatchI[1]=ijp;
      } // end loop over J/Psi cand.
    } // end if J/Psi

    if (fIsEtabJPsi) {

      // find Eta_b cand that best matches MC Eta_b
      for(int ie = 0; ie < fEtabN; ie++) {
        // match J/Psi cand. by mu dR match
        if ( (fJPsidRMatchI[0]==fEtabJPsiI[ie][0]&&fJPsidRMatchI[1]==fEtabJPsiI[ie][1])||(fJPsidRMatchI[0]==fEtabJPsiI[ie][1]&&fJPsidRMatchI[1]==fEtabJPsiI[ie][0]) ) fEtabdRMatchI=ie;
      } // end loop over Eta_b cand.

      // find 4 mom. of particles in J/Psi and Eta_b COM
      TLorentzVector EtabJPsi1, EtabJPsi2, JPsi1, JPsi2, Mu11, Mu12, Mu21, Mu22;
      EtabJPsi1.SetPxPyPzE(fGnPx[fEtabI],fGnPy[fEtabI],fGnPz[fEtabI],fGnEnergy[fEtabI]);
      EtabJPsi2.SetPxPyPzE(fGnPx[fEtabI],fGnPy[fEtabI],fGnPz[fEtabI],fGnEnergy[fEtabI]);
      JPsi1.SetPxPyPzE(fGnPx[fJPsiI[0]],fGnPy[fJPsiI[0]],fGnPz[fJPsiI[0]],fGnEnergy[fJPsiI[0]]);
      JPsi2.SetPxPyPzE(fGnPx[fJPsiI[1]],fGnPy[fJPsiI[1]],fGnPz[fJPsiI[1]],fGnEnergy[fJPsiI[1]]);
      Mu11.SetPxPyPzE(fGnPx[fMuI[0][0]],fGnPy[fMuI[0][0]],fGnPz[fMuI[0][0]],fGnEnergy[fMuI[0][0]]);
      Mu12.SetPxPyPzE(fGnPx[fMuI[0][1]],fGnPy[fMuI[0][1]],fGnPz[fMuI[0][1]],fGnEnergy[fMuI[0][1]]);
      Mu21.SetPxPyPzE(fGnPx[fMuI[1][0]],fGnPy[fMuI[1][0]],fGnPz[fMuI[1][0]],fGnEnergy[fMuI[1][0]]);
      Mu22.SetPxPyPzE(fGnPx[fMuI[1][1]],fGnPy[fMuI[1][1]],fGnPz[fMuI[1][1]],fGnEnergy[fMuI[1][1]]);
      TVector3 BoostBackToEtabCM = -(EtabJPsi1.BoostVector());
      TVector3 BoostBackToJPsi1CM  = -(JPsi1.BoostVector());
      TVector3 BoostBackToJPsi2CM  = -(JPsi2.BoostVector());
      TVector3 BoostForwardToJPsi1CM  = JPsi1.BoostVector();
      TVector3 BoostForwardToJPsi2CM  = JPsi2.BoostVector();
      JPsi1.Boost(BoostBackToEtabCM);
      JPsi2.Boost(BoostBackToEtabCM);
      Mu11.Boost(BoostBackToJPsi1CM);
      Mu12.Boost(BoostBackToJPsi1CM);
      Mu21.Boost(BoostBackToJPsi2CM);
      Mu22.Boost(BoostBackToJPsi2CM);
      EtabJPsi1.Boost(BoostForwardToJPsi1CM);
      EtabJPsi2.Boost(BoostForwardToJPsi2CM);
      fJPsi1_4MomEtabCM[0]=JPsi1.E(); fJPsi1_4MomEtabCM[1]=JPsi1.Px(); fJPsi1_4MomEtabCM[2]=JPsi1.Py(); fJPsi1_4MomEtabCM[3]=JPsi1.Pz();
      fJPsi2_4MomEtabCM[0]=JPsi2.E(); fJPsi2_4MomEtabCM[1]=JPsi2.Px(); fJPsi2_4MomEtabCM[2]=JPsi2.Py(); fJPsi2_4MomEtabCM[3]=JPsi2.Pz();
      fMu11_4MomJPsi1CM[0]=Mu11.E(); fMu11_4MomJPsi1CM[1]=Mu11.Px(); fMu11_4MomJPsi1CM[2]=Mu11.Py(); fMu11_4MomJPsi1CM[3]=Mu11.Pz();
      fMu12_4MomJPsi1CM[0]=Mu12.E(); fMu12_4MomJPsi1CM[1]=Mu12.Px(); fMu12_4MomJPsi1CM[2]=Mu12.Py(); fMu12_4MomJPsi1CM[3]=Mu12.Pz();
      fMu21_4MomJPsi2CM[0]=Mu21.E(); fMu21_4MomJPsi2CM[1]=Mu21.Px(); fMu21_4MomJPsi2CM[2]=Mu21.Py(); fMu21_4MomJPsi2CM[3]=Mu21.Pz();
      fMu22_4MomJPsi2CM[0]=Mu22.E(); fMu22_4MomJPsi2CM[1]=Mu22.Px(); fMu22_4MomJPsi2CM[2]=Mu22.Py(); fMu22_4MomJPsi2CM[3]=Mu22.Pz();
      fEtab_4MomJPsi1CM[0]=EtabJPsi1.E(); fEtab_4MomJPsi1CM[1]=EtabJPsi1.Px(); fEtab_4MomJPsi1CM[2]=EtabJPsi1.Py(); fEtab_4MomJPsi1CM[3]=EtabJPsi1.Pz();
      fEtab_4MomJPsi2CM[0]=EtabJPsi2.E(); fEtab_4MomJPsi2CM[1]=EtabJPsi2.Px(); fEtab_4MomJPsi2CM[2]=EtabJPsi2.Py(); fEtab_4MomJPsi2CM[3]=EtabJPsi2.Pz();
    }
  }
}


bool PATEventTree::isProgenitor(const int putativeMom, const int putativeKid) {

  if (fGnNMothers[putativeKid]==0||putativeMom>=putativeKid) return false;
  else {
    for(int im=0; im<fGnNMothers[putativeKid]; im++) {
      if (im==MOTHERMAX) break;
      if (putativeMom==fGnMotherIndex[putativeKid][im]) return true;
      else if (putativeKid==fGnMotherIndex[putativeKid][im]) continue; // avoid infinite loops
      else if (isProgenitor(putativeMom,fGnMotherIndex[putativeKid][im])) return true;
    }
  }
  return false;
}


bool PATEventTree::isDescendant(const int putativeMom, const int putativeKid) {

  if (fGnNDaughters[putativeMom]==0||putativeMom>=putativeKid) return false;
  else {
    for(int id=0; id<fGnNDaughters[putativeMom]; id++) {
      if (id==DAUGHTERMAX) break;
      if (fGnDaughterIndex[putativeMom][id]==putativeKid) return true;
      else if (putativeMom==fGnDaughterIndex[putativeMom][id]) continue; // avoid infinite loops
      else if (isDescendant(fGnDaughterIndex[putativeMom][id],putativeKid)) return true;
    }
  }
  return false;
}


// define this as a plug-in
DEFINE_FWK_MODULE(PATEventTree);

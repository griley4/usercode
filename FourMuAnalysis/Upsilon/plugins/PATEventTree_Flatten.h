#ifndef PATEventTree_h
#define PATEventTree_h

/** \class PATEventTree
 * ----------------------------------------------------------------------
 * PATEventTree
 * ---------
 * Summary: Create ntuple with event information from PAT
 *        
 * ----------------------------------------------------------------------
 * Send all questions, wishes and complaints to the 
 *
 * Author: Grant Riley 
 * ----------------------------------------------------------------------
 *
 *
 ************************************************************/

#include <map>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"


using namespace reco;
using namespace pat;

class TObject;
class TTree;
class TH1D;
class TFile;

class PATEventTree : public edm::EDAnalyzer {
 public:
  
  explicit PATEventTree(const edm::ParameterSet& ps);
  virtual ~PATEventTree();
  virtual void beginJob();
  virtual void endJob();
  virtual void beginRun(const edm::Run &run, const edm::EventSetup &iSetup);
  virtual void endRun(edm::Run const&run, edm::EventSetup const&iSetup);
  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);

 protected:
  void init();
  void fillHLTPath(const unsigned int psSet, const edm::Handle<edm::TriggerResults>& hHLTresults, const trigger::TriggerEvent& triggerEvent);
  void fillHLT(const pat::TriggerObjectStandAloneCollection& HLTObjects);
  void fillPrimaryVertices(const std::vector<Vertex>& vertices);
  void fillParticles(const std::vector<pat::Muon>& muons, const std::vector<reco::Track>& ctftracks);
  void fillJets(const std::vector<pat::Jet>& jets);
  void jetDisambiguation();
  void fillSecondaryVertices(const reco::SecondaryVertexTagInfo& svTagInfo, const bool IsGTV);
  void fillMET(const pat::METCollection& METColl);
  void fillGen(const std::vector<GenParticle>& genparticles);
  void fillDimuonCand(const reco::CompositeCandidateCollection& JPsiCands, const reco::MuonRefVector& goodMuons, std::vector<TransientTrack>& t_tks);
  void makeEtabCand(std::vector<TransientTrack>& t_tks);
  void fillTopology();
  bool isProgenitor(const int putativeMom, const int putativeKid);
  bool isDescendant(const int putativeMom, const int putativeKid);

 private:
  std::string     fRootFileName;
  bool            fHLT_Skim, fIsEtabJPsi, fIsJPsiMuMu, fIsHBB, fIsMC, fUseFatJets;
  edm::InputTag   fHLTPathLabel, fHLTFilterLabel, fHLTCollectionLabel, fPrimaryVertexCollectionLabel, fMuonCollectionLabel, fElectronCollectionLabel, fPhotonCollectionLabel, fTrackCollectionLabel, fJetCollectionLabel, fMETCollectionLabel, fGenCollectionLabel,fDimuonCandLabel, fFourmuonCandLabel,fDimuonInputLabel;
  std::vector<edm::InputTag> fFatJetCollectionLabel;
  edm::ESHandle<TransientTrackBuilder> theBuilder;


  TFile *fFile;
  TH1D  *fL1Thist, *fL1TThist, *fHLThist;
  TTree *fTree;

  bool  useEvent, fValidHLTConfig;
  int   nevt, fInit;
  HLTConfigProvider fHltConfig;

  // -- general stuff
  unsigned int fRun, fEvent, fLumiBlock;
  int          fBX, fOrbit;
  unsigned int fTimeLo, fTimeHi;
  float        fBz;

  // -- event topology
  float fEvSphericity, fEvAplanarity, fEvLambda[3], fEvThrust, fEvThrust_Major, fEvThrust_Minor, fEvFW[7];
  
  // -- HLT Path information taken directly from HLT (not PAT)
  // for the array: 0 = path was run or not, 1 = path passed or not, 2 = path encountered exception or not
  bool  fHLTP_DoubleMu3[3], fHLTP_DoubleMu6[3], fHLTP_DoubleMu7[3],fHLTP_Dimuon0_Upsilon_Muon[3], fHLTP_Dimuon0_Jpsi_Muon[3], fHLTP_Dimuon0_Jpsi[3], fHLTP_Dimuon10_Jpsi_Barrel[3], fHLTP_TripleMu5[3];
  // HLT prescalersb
  unsigned int fHLTP_DoubleMu3_PS, fHLTP_DoubleMu6_PS, fHLTP_DoubleMu7_PS,fHLTP_Dimuon0_Upsilon_Muon_PS, fHLTP_Dimuon0_Jpsi_Muon_PS, fHLTP_Dimuon0_Jpsi_PS, fHLTP_Dimuon10_Jpsi_Barrel_PS, fHLTP_TripleMu5_PS;
  // HLT filters passed
  bool  fHLTP_DoubleMu3_Filters[5], fHLTP_DoubleMu6_Filters[5], fHLTP_DoubleMu7_Filters[5], fHLTP_TripleMu5_Filters[5], fHLTP_Dimuon0_Jpsi_Filters[7],fHLTP_Dimuon0_Upsilon_Muon_Filters[7], fHLTP_Dimuon0_Jpsi_Muon_Filters[8], fHLTP_Dimuon10_Jpsi_Barrel_Filters[7];

  // -- HLT objects from PAT
  static const int HLTMAX = 1000;
  int   fHLTN;
  int   fHLT_Index[HLTMAX], fHLT_ToPc[HLTMAX], fHLT_ToJt[HLTMAX], fHLT_PdgId[HLTMAX];
  float fHLT_Mass[HLTMAX], fHLT_Energy[HLTMAX], fHLT_Et[HLTMAX], fHLT_P[HLTMAX], fHLT_Pt[HLTMAX], fHLT_Px[HLTMAX], fHLT_Py[HLTMAX], fHLT_Pz[HLTMAX], fHLT_Theta[HLTMAX], fHLT_Eta[HLTMAX], fHLT_Phi[HLTMAX];
  bool  fHLT_Mu[HLTMAX][2], fHLT_Mu12[HLTMAX][2], fHLT_Mu15[HLTMAX][2], fHLT_Mu20[HLTMAX][2], fHLT_Mu24[HLTMAX][2], fHLT_Mu30[HLTMAX][2], fHLT_IsoMu12[HLTMAX][2], fHLT_IsoMu15[HLTMAX][2], fHLT_IsoMu17[HLTMAX][2], fHLT_IsoMu24[HLTMAX][2], fHLT_IsoMu30[HLTMAX][2], fHLT_DoubleMu3[HLTMAX][2], fHLT_DoubleMu6[HLTMAX][2], fHLT_DoubleMu7[HLTMAX][2],fHLT_Dimuon0_Upsilon_Muon[HLTMAX][2], fHLT_Dimuon0_Jpsi_Muon[HLTMAX][2], fHLT_Dimuon0_Jpsi[HLTMAX][2], fHLT_Dimuon7_Jpsi_Displaced[HLTMAX][2], fHLT_Dimuon7_Jpsi_X_Barrel[HLTMAX][2], fHLT_Dimuon10_Jpsi_Barrel[HLTMAX][2], fHLT_TripleMu5[HLTMAX][2], fHLT_Jet[HLTMAX][2];

  // -- Particles
  static const int PARTMAX = 10000;
  int   fPcN, fTkN, fMuN, fElecN, fMiscTkN, fPhotN, fgsmN, fgsmmN,fgtmN, bestProb, bestProb1 ; //fHadrN, 
  int   fPcIndex[PARTMAX], fMuIndex[PARTMAX], fElecIndex[PARTMAX], fMiscTkIndex[PARTMAX], fPhotIndex[PARTMAX], fPcToGn[PARTMAX], fPcToTk[PARTMAX], fTkToPc[PARTMAX], fPcToPv[PARTMAX], fPcTkQuality[PARTMAX], fPcJtN[PARTMAX], fPcPdgId[PARTMAX], fPcPixHitN[PARTMAX], fPcPixLayN[PARTMAX], fPcStripHitN[PARTMAX], fPcStripLayN[PARTMAX]; //fHadrIndex[PARTMAX]
  float fPcCharge[PARTMAX], fPcChi2[PARTMAX], fPcNdof[PARTMAX], fPcEnergy[PARTMAX], fPcEt[PARTMAX], fPcP[PARTMAX], fPcPt[PARTMAX], fPcPx[PARTMAX], fPcPy[PARTMAX], fPcPz[PARTMAX], fPcTheta[PARTMAX], fPcEta[PARTMAX], fPcPhi[PARTMAX], fPcD0[PARTMAX], fPcDz[PARTMAX], fPcEtaErr[PARTMAX], fPcPhiErr[PARTMAX], fPcD0Err[PARTMAX], fPcDzErr[PARTMAX], fPcVx[PARTMAX], fPcVy[PARTMAX], fPcVz[PARTMAX], fPcEcalIso[PARTMAX], fPcHcalIso[PARTMAX], fPcTrackIso[PARTMAX], fPcIP[PARTMAX], fPcIPxy[PARTMAX];
  // -- muons
//  typedef std::vector<std::vector<int,int> > IntMatrix;
//  IntMatrix fMuChambers[PARTMAX]; 
  int   fMuHitN[PARTMAX], fMuMatchedN[PARTMAX], fMuMatchedNSegArb[PARTMAX],fMuMatchedNSegTrkArb[PARTMAX],fMuMatchedNSegTrkArbClean[PARTMAX],fMuHLTN[PARTMAX], fMuToHLT[PARTMAX];
  float fMuChi2[PARTMAX], fMuNdof[PARTMAX], fMuTkKink[PARTMAX], fMuGlbKink[PARTMAX], fMuGlbProb[PARTMAX], fMuTkSADist[PARTMAX], fMuTkSAdR[PARTMAX], fMuECALEnergy[PARTMAX], fMuHCALEnergy[PARTMAX], fMuCalCompat[PARTMAX];
  bool  fMuIsGlobal[PARTMAX], fMuIsTracker[PARTMAX], fMuIsStandalone[PARTMAX], fMuIsCalo[PARTMAX], fMuArbitrated[PARTMAX], fMuLastStationLoose[PARTMAX], fMuLastStationTight[PARTMAX], fMu2DCompatibilityLoose[PARTMAX], fMu2DCompatibilityTight[PARTMAX], fMuOneStationLoose[PARTMAX], fMuOneStationTight[PARTMAX], fMuHLTMatch[PARTMAX][2], fMuL3Match[PARTMAX], fMuTightMatch[PARTMAX], fMuIsHighPurity[PARTMAX], fgoodSoftMuon[PARTMAX], fgoodSoftMuonMod[PARTMAX], fgoodTightMuon[PARTMAX] ;

  // -- Primary Vertices
  static const int PVMAX = 300;
  int   fPvN, fRePvN, fAllPvN;
  int   fPvIndex[PVMAX], fPvTkN[PVMAX], fPvClosestI[PVMAX];
  float fPvX[PVMAX], fPvY[PVMAX],  fPvZ[PVMAX], fPvXe[PVMAX], fPvYe[PVMAX],  fPvZe[PVMAX], fPvPx[PVMAX], fPvPy[PVMAX], fPvPz[PVMAX], fPvPt[PVMAX], fPvP[PVMAX], fPvEnergy[PVMAX], fPvEta[PVMAX],  fPvChi2[PVMAX], fPvNdof[PVMAX], fPvMass[PVMAX];
  bool  fPvIsFake[PVMAX], fPvIsRefit[PVMAX];

  // -- Jets
  static const int JETMAX = 2000;
  static const int PARTINJETMAX = 15;
  static const int PARTTOJETMAX = 5;

  int JtShift; //used to differentiate jet collections
  int fJtN, fJtStandN, fJtFatN, fJtSubN, fJtFiltN, fJtBdRN, fJtBFlavN;
  int fJtIndex[JETMAX], fJtStandIndex[JETMAX], fJtFatIndex[JETMAX], fJtSubIndex[JETMAX], fJtFiltIndex[JETMAX], fJtToPv[JETMAX], fJtHLTN[JETMAX], fJtToHLT[JETMAX], fJtTkN[JETMAX], fJtSsvN[JETMAX], fJtGtvN[JETMAX], fJtnConstituents[JETMAX], fJtFlavour[JETMAX], fJtn60[JETMAX], fJtn90[JETMAX], fJtnChargedParticles[JETMAX], fJtnNeutralParticles[JETMAX], fJtnChargedHadrons[JETMAX], fJtnNeutralHadrons[JETMAX], fJtnPhotons[JETMAX], fJtnElectrons[JETMAX], fJtnMuons[JETMAX], fJtnHFHadrons[JETMAX], fJtnHFEMParticles[JETMAX], fJtRankTCHE[JETMAX], fJtRankTCHP[JETMAX], fJtRankP[JETMAX], fJtRankBP[JETMAX], fJtRankSSVHE[JETMAX], fJtRankSSVHP[JETMAX], fJtRankCSV[JETMAX], fJtRankCSVMVA[JETMAX], fJtRankGT[JETMAX], fJtRankSE[JETMAX], fJtRankSM[JETMAX];
  float fJtCharge[JETMAX], fJtDiscTCHE[JETMAX], fJtDiscTCHP[JETMAX], fJtDiscP[JETMAX], fJtDiscBP[JETMAX], fJtDiscSSVHE[JETMAX], fJtDiscSSVHP[JETMAX], fJtDiscCSV[JETMAX], fJtDiscCSVMVA[JETMAX], fJtDiscGT[JETMAX], fJtDiscSE[JETMAX], fJtDiscSM[JETMAX], fJtMaxDist[JETMAX], fJtPhi[JETMAX], fJtTheta[JETMAX], fJtEta[JETMAX], fJtRapidity[JETMAX], fJtP[JETMAX], fJtPt[JETMAX], fJtPx[JETMAX], fJtPy[JETMAX], fJtPz[JETMAX], fJtEnergy[JETMAX], fJtEt[JETMAX], fJtMass[JETMAX], fJtMt[JETMAX], fJtVx[JETMAX], fJtVy[JETMAX], fJtVz[JETMAX], fJtChargedEmEnergy[JETMAX], fJtNeutralEmEnergy[JETMAX], fJtChargedHadronEnergy[JETMAX], fJtNeutralHadronEnergy[JETMAX], fJtPhotonEnergy[JETMAX], fJtElectronEnergy[JETMAX], fJtMuonEnergy[JETMAX], fJtHFHadronEnergy[JETMAX], fJtHFEMEnergy[JETMAX], fJtdRMean[JETMAX], fJtdRMax[JETMAX], fJtPtRelMean[JETMAX], fJtPtRelMax[JETMAX], fJtPtRelSum[JETMAX], fJtPullPx[JETMAX], fJtPullPy[JETMAX], fJtPullPz[JETMAX];
  bool fJtIsStandard[JETMAX], fJtIsFat[JETMAX], fJtIsSub[JETMAX], fJtIsFilt[JETMAX], fJtBFromH[JETMAX], fJtBdRMatch[JETMAX], fJtHLTMatch[JETMAX][2], fJtVeto[JETMAX];

  // -- References between particle and jet
  int   fPcToJt[PARTMAX][PARTTOJETMAX], fJtToPc[JETMAX][PARTINJETMAX];

  // -- Fat and subjet specific variables
  int   fFatSubN[JETMAX], fFatFiltN[JETMAX], fSubToFat[JETMAX], fFiltToFat[JETMAX];

  // for jet matching to B
  int fJtBdRIndex[JETMAX], fJtToBdRIndex[JETMAX], fJtBFlavIndex[JETMAX];
  float fJtBdR[JETMAX];  // dR to B hadron

  // -- Secondary Vertices
  static const int SVMAX = 20;
  static const int TKINSVMAX = 20;
  static const int SVINJETMAX = 4;

  int   fSvN, fSsvN, fGtvN;
  int   fSvIndex[SVMAX], fSvTkN[SVMAX], fSvSeqInJt[SVMAX];
  float fSvX[SVMAX], fSvY[SVMAX], fSvZ[SVMAX], fSvXe[SVMAX], fSvYe[SVMAX],  fSvZe[SVMAX], fSvPx[SVMAX], fSvPy[SVMAX], fSvPz[SVMAX], fSvPt[SVMAX], fSvEta[SVMAX], fSvChi2[SVMAX], fSvNdof[SVMAX], fSvDist[SVMAX], fSvDistCM[SVMAX], fSvMass[SVMAX], fSvTau[SVMAX], fSvTauCM[SVMAX];
  bool  fSvIsGTV[SVMAX];

  // -- References between vertex and tracks
  int   fSvToPc[SVMAX][TKINSVMAX], fPcToSsv[PARTMAX], fPcToGtv[PARTMAX];
  // -- References between jet and SV
  int   fSvToJt[SVMAX], fJtToSsv[JETMAX][SVINJETMAX], fJtToGtv[JETMAX][SVINJETMAX];

  // -- MET information
  static const int METMAX = 10;

  int fMETN;
  int fMETIndex[METMAX];
  float fMETPhi[METMAX], fMETTheta[METMAX], fMETEta[METMAX], fMETRapidity[METMAX], fMETCharge[METMAX], fMETP[METMAX], fMETPt[METMAX], fMETPx[METMAX], fMETPy[METMAX], fMETPz[METMAX], fMETEnergy[METMAX], fMETEt[METMAX], fMETMass[METMAX], fMETMt[METMAX], fMETVx[METMAX], fMETVy[METMAX], fMETVz[METMAX];

  // -- JPsi->MuMu candidates
  static const int JPsiMAX = 500;

  int fJPsiN, fJPsiMuMuN, fJPsiMuTkN, fBaseJPsiI[2];
  int fJPsiIndex[JPsiMAX], fJPsiClosestPVinZ[JPsiMAX], fJPsiMuI[JPsiMAX][2], fJPsiMuCategory[JPsiMAX][2];
  float fJPsiCharge[JPsiMAX], fJPsiPhi[JPsiMAX], fJPsiTheta[JPsiMAX], fJPsiEta[JPsiMAX], fJPsiRapidity[JPsiMAX], fJPsiP[JPsiMAX], fJPsiPt[JPsiMAX], fJPsiPx[JPsiMAX], fJPsiPy[JPsiMAX], fJPsiPz[JPsiMAX], fJPsiEnergy[JPsiMAX], fJPsiEt[JPsiMAX], fJPsiMass[JPsiMAX], fJPsiMt[JPsiMAX], fJPsiChi2[JPsiMAX], fJPsiNdof[JPsiMAX], fJPsiVx[JPsiMAX], fJPsiVy[JPsiMAX], fJPsiVz[JPsiMAX], fJPsiVxE[JPsiMAX], fJPsiVyE[JPsiMAX], fJPsiVzE[JPsiMAX], fJPsiVtxPhi[JPsiMAX], fJPsiVtxTheta[JPsiMAX], fJPsiVtxEta[JPsiMAX], fJPsiVtxRapidity[JPsiMAX], fJPsiVtxP[JPsiMAX], fJPsiVtxPt[JPsiMAX], fJPsiVtxPx[JPsiMAX], fJPsiVtxPy[JPsiMAX], fJPsiVtxPz[JPsiMAX], fJPsiVtxEnergy[JPsiMAX], fJPsiVtxEt[JPsiMAX], fJPsiVtxMass[JPsiMAX], fJPsiVtxMt[JPsiMAX];
  bool fJPsiMuCutKin[JPsiMAX][2], fJPsiMuCutHLT[JPsiMAX][2], fJPsiMuCutIso[JPsiMAX][2], fJPsiMuCutSA[JPsiMAX][2], fJPsiMuCutTrk[JPsiMAX][2], fJPsiMuType[JPsiMAX][2][5], fJPsiBasicFilter[JPsiMAX];

  // -- Eta_b->2 J/Psi candidates
  static const int ETABMAX = 500;

  int fEtabN, fBaseEtabI, EtabBestVtxProbI;
  int fEtabIndex[ETABMAX], fEtabDuplicatesI[ETABMAX], fEtabJPsiI[ETABMAX][2], fEtabMuI[ETABMAX][4], fEtabMuN[ETABMAX], fEtabToRePvI[ETABMAX];
  float fEtabCharge[ETABMAX], fEtabPhi[ETABMAX], fEtabTheta[ETABMAX], fEtabEta[ETABMAX], fEtabRapidity[ETABMAX], fEtabP[ETABMAX], fEtabPt[ETABMAX], fEtabPx[ETABMAX], fEtabPy[ETABMAX], fEtabPz[ETABMAX], fEtabEnergy[ETABMAX], fEtabEt[ETABMAX], fEtabMass[ETABMAX], fEtabMt[ETABMAX], fEtabChi2[ETABMAX], fEtabNdof[ETABMAX], fEtabVx[ETABMAX], fEtabVy[ETABMAX], fEtabVz[ETABMAX], fEtabVxE[ETABMAX], fEtabVyE[ETABMAX], fEtabVzE[ETABMAX], fEtabVtxPhi[ETABMAX], fEtabVtxTheta[ETABMAX], fEtabVtxEta[ETABMAX], fEtabVtxRapidity[ETABMAX], fEtabVtxP[ETABMAX], fEtabVtxPt[ETABMAX], fEtabVtxPx[ETABMAX], fEtabVtxPy[ETABMAX], fEtabVtxPz[ETABMAX], fEtabVtxEnergy[ETABMAX], fEtabVtxEt[ETABMAX], fEtabVtxMass[ETABMAX], fEtabVtxMt[ETABMAX], fEtabCT[ETABMAX], fEtabCTxy[ETABMAX], fEtabVtxCT[ETABMAX], fEtabVtxCTxy[ETABMAX], fEtabJPsiDeltaL[ETABMAX], fEtabJPsiDeltaT[ETABMAX], fEtabJPsiVtxErr[ETABMAX], fEtabJPsiVtxErrxy[ETABMAX], fEtabJPsiProjX[ETABMAX][2], fEtabJPsiProjY[ETABMAX][2], fEtabJPsiProjZ[ETABMAX][2], fEtabJPsiCT[ETABMAX][2], fEtabJPsiCTxy[ETABMAX][2], fEtabJPsiToPVVtxErr[ETABMAX][2], fEtabJPsiToPVVtxErrxy[ETABMAX][2], fEtabJPsiVtxCT[ETABMAX][2], fEtabJPsiVtxCTxy[ETABMAX][2];
  bool fEtabBasicFilter[ETABMAX], fEtabDJFilter[ETABMAX],fEtabUpsFilter[ETABMAX];
  // isolation information
  int fEtabJPsiIsoTkN[ETABMAX][2], fEtabBestDJProbI, fEtabBestUpsProbI;
  float fEtabJPsiIso7PV[ETABMAX][2], fEtabJPsiIsoTkCA[ETABMAX][2];

  // -- H->bb candidates
  static const int HMAX = 100;

  int fHN;
  int fHIndex[HMAX], fHJtI[HMAX][2];
  float fHCharge[HMAX], fHPhi[HMAX], fHTheta[HMAX], fHEta[HMAX], fHRapidity[HMAX], fHP[HMAX], fHPt[HMAX], fHPx[HMAX], fHPy[HMAX], fHPz[HMAX], fHEnergy[HMAX], fHEt[HMAX], fHMass[HMAX], fHMt[HMAX], fHVx[HMAX], fHVy[HMAX], fHVz[HMAX];

  // -- Gen Particles
  static const int GENMAX = 3000;
  static const int MOTHERMAX = 5;
  static const int DAUGHTERMAX = 20;

  int fGnN, fGnBN;
  int fGnIndex[GENMAX], fGnBIndex[GENMAX], fGnIsJet[GENMAX], fGnLongLived[GENMAX], fGnPdgId[GENMAX], fGnNMothers[GENMAX], fGnNDaughters[GENMAX];
  float fGnCharge[GENMAX], fGnPhi[GENMAX], fGnTheta[GENMAX], fGnEta[GENMAX], fGnRapidity[GENMAX], fGnP[GENMAX], fGnPt[GENMAX], fGnPx[GENMAX], fGnPy[GENMAX], fGnPz[GENMAX], fGnEnergy[GENMAX], fGnEt[GENMAX], fGnMass[GENMAX], fGnMt[GENMAX], fGnVx[GENMAX], fGnVy[GENMAX], fGnVz[GENMAX], fGnDist[GENMAX], fGnDistCM[GENMAX], fGnTau[GENMAX], fGnTauCM[GENMAX];

  // -- References to daughter candidates
  int   fGnMotherIndex[GENMAX][MOTHERMAX], fGnDaughterIndex[GENMAX][DAUGHTERMAX];

  // -- Signal quantities (Etab and J/Psi information)
  int   fEtabI, fEtabdRMatchI, fJPsiI[2], fJPsidRMatchI[2], fMuI[2][2], fMudRMatchI[2][2], fMuByPtI[4], fMuByPtMatchI[4];
  float fMu11_4MomJPsi1CM[4], fMu12_4MomJPsi1CM[4], fMu21_4MomJPsi2CM[4], fMu22_4MomJPsi2CM[4], fJPsi1_4MomEtabCM[4], fJPsi2_4MomEtabCM[4], fEtab_4MomJPsi1CM[4], fEtab_4MomJPsi2CM[4];

};

#endif

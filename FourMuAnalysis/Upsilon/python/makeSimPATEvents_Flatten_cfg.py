import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

## Source
process.source = cms.Source("PoolSource",
#    skipEvents = cms.untracked.uint32(1021),
    fileNames  = cms.untracked.vstring(
      'file:B0ToPsiMuMu_AODSIM.root',
    )
)
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string('START42_V14A::All')
#process.GlobalTag.globaltag = cms.string('MC_38Y_V13::All')

## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## Turn off MC matching for real data
from PhysicsTools.PatAlgos.tools.coreTools import *
process.electronMatch.mcPdgId = cms.vint32(11,13,211,321,2212)
process.electronMatch.resolveByMatchQuality = True
process.muonMatch.mcPdgId = cms.vint32(11,13,211,321,2212)
process.muonMatch.resolveByMatchQuality = True
process.tauMatch.resolveByMatchQuality = True
process.photonMatch.resolveByMatchQuality = True
process.patJetPartonMatch.resolveByMatchQuality = True
process.patJetGenJetMatch.resolveByMatchQuality = True

## Turn on track collection
#from PhysicsTools.PatAlgos.tools.trackTools import *
#makeTrackCandidates(process,
#                    label        = 'TrackCands',
#                    tracks       = cms.InputTag('generalTracks'),
#                    particleType = 'pi+',
#                    preselection = '',
#                    selection    = '',
#                    isolation    = {'tracker':0.3, 'ecalTowers':0.3, 'hcalTowers':0.3},
#                    isoDeposits  = [],
#                    mcAs         = None
#                    )

## Switch jet collection
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('ak5PFJets'),   
                    doJTA            = True,            
                    doBTagging       = True,            
                    jetCorrLabel     = ('AK5PF', ['L2Relative', 'L3Absolute']),  
                    doType1MET       = True,            
                    genJetCollection = cms.InputTag("ak5GenJets"),
                    doJetID          = True,
                    jetIdLabel       = "ak5",
                    outputModule     = "")

process.patJets.addTagInfos     = True
process.patJets.tagInfoSources  = cms.VInputTag(
  cms.InputTag("secondaryVertexTagInfosAOD") )
process.patJetCorrFactors.useRho    = False
process.patJetCorrFactors.rho       = cms.InputTag('')

## Add MET from particle flow
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process, 'PF')

## Add trigger information
process.JetMatch = cms.EDProducer("PATTriggerMatcherDRLessByR", # match by DeltaR only, best match by DeltaR
  src     = cms.InputTag( "cleanPatJets" ),
  matched = cms.InputTag( "patTrigger" ), # defined in PhysicsTools/PatAlgos/python/triggerLayer1/triggerProducer_cfi.py
  andOr                      = cms.bool( False ),  # AND
  filterIdsEnum              = cms.vstring( '*' ), # wildcard, overlaps with 'filterIds'
  filterIds                  = cms.vint32( 0 ),    # wildcard, overlaps with 'filterIdsEnum'
  filterLabels               = cms.vstring( '*' ), # wildcard
  matchedCuts                = cms.string('type("TriggerJet")'),
  pathNames                  = cms.vstring('HLT_Jet30U_v*','HLT_Jet60_v*','HLT_Jet80_v*','HLT_Jet110_v*','HLT_Jet150_v*','HLT_Jet190_v*','HLT_Jet240_v*','HLT_Jet370_v*'),
  pathLastFilterAcceptedOnly = cms.bool( False ),  # select only trigger objects used in last filters of succeeding paths
  collectionTags             = cms.vstring( '*' ), # wildcard
  maxDeltaR                  = cms.double( 0.5 ),
  resolveAmbiguities         = cms.bool( True ),   # only one match per trigger object
  resolveByMatchQuality      = cms.bool( True )    # take best match found per reco object: by DeltaR here (s. above)
)

from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTriggerStandAlone( process, None, 'patDefaultSequence', 'HLT', '' )
switchOnTriggerMatchEmbedding( process, ['JetMatch'], 'patTrigger', 'patDefaultSequence', 'HLT', '' )

## Trigger match the Muons
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
import PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi
process.patMuonsWithoutTrigger = PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi.patMuons.clone()


from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import addMCinfo, changeRecoMuonInput, useL1MatchingWindowForSinglets, changeTriggerProcessName, switchOffAmbiguityResolution
# with some customization
addMCinfo(process)
# since we match inner tracks, keep the matching tight and make it one-to-one
process.muonMatch.maxDeltaR = 0.05
process.muonMatch.resolveByMatchQuality = True
#process.muonMatch.matched = "genMuons"
#changeRecoMuonInput(process, "mergedMuons")
useL1MatchingWindowForSinglets(process)
#changeTriggerProcessName(process, "REDIGI36X")
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
process.muonMatchHLTCtfTrack.maxDeltaR = 0.1
process.muonMatchHLTCtfTrack.maxDPtRel = 10.0
process.muonMatchHLTTrackMu.maxDeltaR = 0.1
process.muonMatchHLTTrackMu.maxDPtRel = 10.0

## Make JPsi and Higgs candidates
process.goodMuons = cms.EDFilter("MuonRefSelector",
    src = cms.InputTag("muons"),
    cut = cms.string(""),
)
process.JPsiToMuMu = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string('goodMuons@+ goodMuons@-'),
    cut = cms.string(''),
)

## Analyzer package
process.PATEventTree = cms.EDAnalyzer("PATEventTree",
    rootFileName                 = cms.untracked.string("DoubleJPsiToMuMu_Tree.root"),
    isEtabJPsi                   = cms.untracked.bool(False),
    isJPsiMuMu                   = cms.untracked.bool(True),
    isMC                         = cms.untracked.bool(True),
    useFatJets                   = cms.untracked.bool(False),
    PrimaryVertexCollectionLabel = cms.untracked.InputTag('offlinePrimaryVertices'),
    HLTCollectionLabel           = cms.untracked.InputTag('patTrigger'),
    MuonCollectionLabel          = cms.untracked.InputTag('cleanPatMuonsTriggerMatch'),
    ElectronCollectionLabel      = cms.untracked.InputTag('cleanPatElectrons'),
    PhotonCollectionLabel        = cms.untracked.InputTag('cleanPatPhotons'),
#    ParticleCollectionLabel      = cms.untracked.InputTag('cleanPatTrackCands'),
    TrackCollectionLabel         = cms.untracked.InputTag('generalTracks'),
    JetCollectionLabel           = cms.untracked.InputTag('cleanPatJetsTriggerMatch'),
    FatJetCollectionLabel        = cms.untracked.VInputTag(['cleanPatJetsPFFAT','cleanPatJetsPFSUB','cleanPatJetsPFFILTER']),
    METCollectionLabel           = cms.untracked.InputTag('patMETsPF'),
    JPsiInputLabel               = cms.untracked.InputTag('goodMuons'),
    JPsiCandLabel                = cms.untracked.InputTag('JPsiToMuMu'),
    GenCollectionLabel           = cms.untracked.InputTag('genParticles')
    )


## Run the actual sequence
process.p = cms.Path(
    process.patDefaultSequence*
    process.patMuonsWithTriggerSequence*
    process.goodMuons*
    process.JPsiToMuMu*
    process.PATEventTree
    )

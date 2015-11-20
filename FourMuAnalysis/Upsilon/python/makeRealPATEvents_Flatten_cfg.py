import FWCore.ParameterSet.Config as cms

process = cms.Process("flatten")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
     'file:/uscms_data/d3/griley4/UpsilonTest/HuntForMoreStatistics/CMSSW_5_3_7_patch5/src/RunD-2012-MuOnia/MuOnia_Run2012D_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim.root',
    )
)
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string('FT53_V21A_AN6::All')


## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")
##Switch on HLT?
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTriggerStandAlone( process, None, 'patDefaultSequence', 'HLT', '' )
#switchOnTriggerMatchEmbedding( process, [''], 'patTrigger', 'patDefaultSequence', 'HLT', '' )
## Turn off MC matching for real data
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, names=['All'],outputModules=[])
## Make JPsi and Higgs candidates
process.goodMuons = cms.EDFilter("MuonRefSelector",
    src = cms.InputTag("muons"),
    cut = cms.string(""),
)
process.Dimuon = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string('goodMuons@+ goodMuons@-'),
    cut = cms.string(''),
)
process.Fourmuon = cms.EDProducer("CandViewShallowCloneCombiner",
    decay= cms.string('Dimuon Dimuon'),
    cut = cms.string(''),
)

## Analyzer package
process.PATEventTree = cms.EDAnalyzer("PATEventTree",
    rootFileName                 = cms.untracked.string("TEST.root"),
    isMC                         = cms.untracked.bool(False),
    HLTCollectionLabel           = cms.untracked.InputTag('patTrigger'),
    MuonCollectionLabel          = cms.untracked.InputTag('patMuons'),
    JPsiInputLabel               = cms.untracked.InputTag('goodMuons'),
    DimuonCandLabel                = cms.untracked.InputTag('Dimuon'),
    FourmuonCandLabel                = cms.untracked.InputTag('Fourmuon'),
    GenCollectionLabel           = cms.untracked.InputTag('genParticles')
    )
## Run the actual sequence
process.p = cms.Path(
    process.goodMuons*
    process.Dimuon*
    process.Fourmuon*
    process.PATEventTree
    )

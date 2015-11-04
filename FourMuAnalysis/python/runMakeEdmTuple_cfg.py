import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.source = cms.Source("PoolSource",
                fileNames = cms.untracked.vstring(
                        "file:/uscms_data/d3/griley4/UpsilonTest/HuntForMoreStatistics/CMSSW_5_3_7_patch5/src/MuOnia_Run2012C_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_11_2_GAR.root"
                        )
                )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.MessageLogger = cms.Service("MessageLogger")

## ---
## This is an example of the use of the plain edm::Tuple dumper to analyze pat::Muons
process.edmEventTreeMaker = cms.EDAnalyzer("edmEventTree",
                rootFileName      = cms.untracked.string("MuOnia_2012_Data.root"),
                MuonCollectionLabel   = cms.untracked.InputTag('patMuons'),
                goodMuonInputLabel    = cms.untracked.InputTag('goodMuons'),
                DiMuCandLabel         = cms.untracked.InputTag('DiMuCand'),
                UpsCandLabel          = cms.untracked.InputTag('UpsCand'),
                FourMuCandLabel       = cms.untracked.InputTag('FourMuCand')

process.p = cms.Path(process.edmEventTreeMaker)

process.out = cms.OutputModule("PoolOutputModule",
                fileName = cms.untracked.string('edmTuple.root'),
                # save only events passing the full path
                SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                # save PAT Layer 1 output; you need a '*' to
                # unpack the list of commands 'patEventContent'
                outputCommands = cms.untracked.vstring('drop *', 'keep *_patMuonAnalyzer_*_*', 'keep *_patJpsiAnalyzer_*_*')
                )

process.outpath = cms.EndPath(process.out)

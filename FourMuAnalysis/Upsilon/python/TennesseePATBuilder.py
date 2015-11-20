#Grant Riley October 27 2015

## import skeleton process
from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.coreTools import *
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

process.source = cms.Source("PoolSource",
                duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                skipEvents = cms.untracked.uint32(0),
                fileNames = cms.untracked.vstring(
                        'file:/uscms_data/d3/griley4/UpsilonTest/HuntForMoreStatistics/CMSSW_5_3_7_patch5/src/C8A43BFC-058F-E211-8E2B-003048678FB8.root'
                        )
                )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.GlobalTag.globaltag = cms.string('FT_53_V21_AN6::All')
#remove MC Matching for Real data
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, names=['All'],outputModules=[])
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process, 
                    cms.InputTag('ak5PFJets'),   
#                    doJTA            = True,
#                    doBTagging       = True,
                    jetCorrLabel     = ('AK5PF', ['L2Relative', 'L3Absolute']),
#                    doType1MET       = False,
                    genJetCollection = cms.InputTag("ak5GenJets"),
#                    doJetID          = True,
                    jetIdLabel       = "ak5",
                    outputModules    = [])
# switch on PAT trigger info
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger( process )
#try to trigger skim?
process.triggerSelection = cms.EDFilter( "TriggerResultsFilter",
                triggerConditions = cms.vstring(
                        'HLT_Dimuon0_Upsilon_Muon_v*',
                        'HLT_Dimuon0_Jpsi_Muon_v*' ),
                hltResults = cms.InputTag( "TriggerResults", "", "HLT" ),
                l1tResults = cms.InputTag( "gtDigis" ),
                l1tIgnoreMask = cms.bool( False ),
                l1techIgnorePrescales = cms.bool( False ),
                daqPartitions = cms.uint32( 1 ),
                throw = cms.bool( True )
                )
process.TrigSkim = cms.Path(process.triggerSelection)
#make J/Psi cands from muons
##Add Muon candidates
from PhysicsTools.PatAlgos.tools.muonTools import *
process.goodMuons = cms.EDFilter("PATMuonSelector",
                src = cms.InputTag("patMuons"),
#                cut = cms.string(''),
                cut = cms.string("track.isNonnull && track.hitPattern.pixelLayersWithMeasurement > 0 ")

                )
process.makeGoodMuons = cms.Path(process.goodMuons)
process.UpsCand = cms.EDProducer("CandViewShallowCloneCombiner",
                decay = cms.string('goodMuons@+ goodMuons@-'),
                cut = cms.string('mass>=9.1 && mass<=9.75'),
                )
process.makeUpsCand = cms.Path(process.UpsCand)
process.DiMuCand = cms.EDProducer("CandViewShallowCloneCombiner",
                decay = cms.string('goodMuons@+ goodMuons@-'),
                cut = cms.string(''),
                )
process.makeDiMuCand = cms.Path(process.DiMuCand)
process.FourMuCand= cms.EDProducer("CandViewShallowCloneCombiner",
                decay = cms.string('DiMuCand DiMuCand'),
                cut = cms.string(''),
                )
process.makeFourMuCand = cms.Path(process.FourMuCand)
## let it run
process.pat = cms.Path(
                process.patDefaultSequence
                )

#produce output

process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('MuOnia_Run2012D_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim.root'),
## save only events passing the full path
                SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring("TrigSkim") ),
                ## save PAT output; you need a '*' to unpack the list of commands
#                outputCommands = cms.untracked.vstring('drop *', 'keep *_*_*_HLT', 'keep *L1*_*_*_*', 'keep *Trig*_*_*_*', 'keep *_*muons*_*_*', 'keep *_*Muons*_*_*', 'keep *_*Track*_*_*', 'keep *CompositeCandidate*_*_*_*')


                )
process.outpath = cms.EndPath(process.out)
# Schedule
process.schedule = cms.Schedule(process.TrigSkim,process.pat,process.makeGoodMuons,process.makeUpsCand,process.makeDiMuCand,process.makeFourMuCand,process.outpath)


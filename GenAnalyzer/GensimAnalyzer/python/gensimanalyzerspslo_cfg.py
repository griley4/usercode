import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:DoubleJPsiToMuMuDPS_GENSIM_1000_1_Nyw.root',
    )
)

process.demo = cms.EDAnalyzer('GensimAnalyzer',
#rootFileName                 = cms.untracked.string("GENEventTree_lhcb_fix.root")
#    rootFileName                 = cms.untracked.string("GENEventTree_tests.root")
#    rootFileName                 = cms.untracked.string("GENEventTree_xl21_fix.root")
    rootFileName                 = cms.untracked.string("GENEventTree_spslo.root")
)


process.p = cms.Path(process.demo)

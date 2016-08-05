import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(2) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:DoubleJPsiToMuMu_SPSold_GENSIM.root'
    )
)

process.demo = cms.EDAnalyzer('GensimAnalyzer'
)


process.p = cms.Path(process.demo)

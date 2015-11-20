import FWCore.ParameterSet.Config as cms

process = cms.Process("combinatorize")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#     'file:/uscms_data/d3/griley4/UpsilonTest/HuntForMoreStatistics/CMSSW_5_3_7_patch5/src/RunD-2012-MuOnia/MuOnia_Run2012D_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim.root',
*(

'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_100_1_ydA.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_101_1_Yi9.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_102_1_PUX.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_103_1_Ref.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_104_1_UqM.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_105_1_OCO.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_106_1_cNm.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_107_1_Qp3.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_108_1_RGu.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_109_1_snN.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_10_1_G7J.root ',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_110_1_tbJ.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_111_1_1MG.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_112_1_bEs.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_113_1_tW2.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_114_1_ZO7.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_115_1_I5e.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_116_1_RsT.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_117_1_bkv.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_118_1_9lM.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_119_1_b0T.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_11_1_ttm.root ',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_120_1_sp5.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_121_1_VvL.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_122_1_8R7.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_123_1_Vx7.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_124_1_YwM.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_125_2_3Zb.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_126_1_IZA.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_127_1_pzW.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_128_1_8sH.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_129_1_0mz.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_12_1_3nJ.root ',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_130_1_4Gb.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_131_1_1YL.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_132_1_sIq.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_133_1_738.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_134_2_tj1.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_135_2_8ma.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_136_1_GY9.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_137_2_au6.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_138_2_amL.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_139_2_uNn.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_13_1_jhL.root ',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_140_2_ulg.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_141_2_Aqw.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_142_1_jVC.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_143_2_PwE.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_144_2_1DE.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_145_1_9hU.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_146_1_QfW.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_147_1_1JU.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_148_2_uXA.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_149_1_9Cm.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_14_1_1SY.root ',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_150_1_cTQ.root',
'file:/data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012A-22Jan2013-v1_HLTSkim/MuOnia_Run2012A_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_151_1_Lii.root',
)
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
process.FourMuonCombiTree= cms.EDAnalyzer("FourMuonCombiTree",
    rootFileName                 = cms.untracked.string("Run2012Combinatorics.root"),
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
    process.FourMuonCombiTree
    )

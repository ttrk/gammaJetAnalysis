#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                                   std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   float cutphotonPt  = 35,  // default value dropped to 35GeV  for later photon energy smearing/scaling 
#                                   std::string outname = "testPhotonSkim.root",
#                                   sampleType colli=kPADATA,
#                                   bool doMix = false,
#                                   bool doJetResCorrection = 1,  // jet energy correction is done by default from Oct 19th (YS)     
#                                   float addJetEnergyRes = 0,
#                                   float addFlatJetEnergyRes = 0,
#                                   bool useGenJetColl = 0
#                                   )



#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5 



# pbpb data
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    35,  "yskim_HiForestPhoton-v7-noDuplicate.root",  0, 1)'

# pbpb MC // 20131112 yeonju
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root",           "/net/hidsk0001/d00/scratch/jazzitup/goyeonju/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons30.root", 1, 1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root",           "/net/hidsk0001/d00/scratch/jazzitup/goyeonju/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons50.root", 1, 1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons80.root",           "/net/hidsk0001/d00/scratch/jazzitup/goyeonju/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons80.root", 1, 1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons120.root",           "/net/hidsk0001/d00/scratch/jazzitup/goyeonju/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons120.root", 1, 1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/PbPb_pythiaHYDJET_forest_AllQCDPhotons/PbPb_pythiaHYDJET_forest_AllQCDPhotons170.root",           "/net/hidsk0001/d00/scratch/jazzitup/goyeonju/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_PbPb_pythiaHYDJET_forest_AllQCDPhotons170.root", 1, 1)'

# pp data 
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetNoSmearing.root",2,0,1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetSmearingCent5099.root",2,0, 1, 6.1024)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetSmearingCent3050.root",2,0, 1, 7.029)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetSmearingCent1030.root",2,0, 1, 8.219)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetSmearingCent0010.root",2,0, 1, 9.6876)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetSmearingCent3099.root",2,0, 1, 6.813)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetSmearingCent0030.root",2,0, 1, 8.8969)'


# pp MC. photon hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# pp MC. background hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet30to50_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet30to50_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet50to80_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet50to80_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet80to120_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet80to120_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet120to9999_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet120to9999_CMSSW538HIp2.root",3,0)'


#  pA data, photon hiForest                                                                                                                   
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root", "yskimmedFiles/minbiasSkim_MergedForest_withCones_MinBiasUPC_v71_1_16HFBin.root", 35,  "yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root",4,1)'
# pA MC.  photon hiForest                                                                                                                     
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton30to50_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85.root", 5,1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton50to80_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85.root", 5,1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton80to120_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85.root", 5,1)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", 5,1)'




#void yj_forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                                   std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   float maxpthat=30.,
#                                   float xSection=102400.0,
#                                   float cutphotonPt  = 35,  // default value dropped to 35GeV  for later photon energy smearing/scaling
#                                   std::string outname = "testPhotonSkim.root",
#                                   sampleType colli=kPADATA,
#                                   bool doMix = false,
#                                   bool doJetResCorrection = 1,  // = L2L3 * MC nonclosure correction  jet energy correction is done by default from Oct 19th (YS)
#                                   int smearingCentBin = -1, //0=0-10%, 1=10-30%, 2=30-50%, 3=50-100%, 4=0-30%, 5=30-100%  : Jet pT and phi smearing!
#                                   bool useGenJetColl = 0
: << 'comment2'
# pA MC 2013 for JEC closure
# after removing maxpthat, xSection
# using 30-50, 50-80, 80-120, 120-170, 170-9999 ptHatCutted sample
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/merged_allQCDPhoton30to50_CMSSW538HIp2.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton30to50_akPu3PF_AfterResCorr.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/merged_allQCDPhoton50to80_CMSSW538HIp2.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton50to80_akPu3PF_AfterResCorr.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/merged_allQCDPhoton80to120_CMSSW538HIp2.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton80to120_akPu3PF_AfterResCorr.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/merged_allQCDPhoton120to170_CMSSW538HIp2.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton120to170_akPu3PF_AfterResCorr.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/merged_allQCDPhoton170to9999_CMSSW538HIp2.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton170to9999_akPu3PF_AfterResCorr.root", 5,0)'
comment2

#: << 'comment1'
# pA MC 2013 for JEC closure
# after removing maxpthat, xSection
# using NOT ptHatCutted samples.
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton30.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton30to50_akPu3PF_AfterResCorr_final.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton50.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton50to80_akPu3PF_AfterResCorr_final.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton80.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton80to120_akPu3PF_AfterResCorr_final.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton120.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton120to170_akPu3PF_AfterResCorr_final.root", 5,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton170.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton170to9999_akPu3PF_AfterResCorr_final.root", 5,0)'
#comment1

: << 'comment'
# pA MC 2013 for JEC closure
# after removing maxpthat, xSection
# Do NOT RESIDUAL CORRECTION. NO ANY CORRECTION
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton30.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton30to50_akPu3PF_NoJetResCorr.root", 5,0,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton50.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton50to80_akPu3PF_NoJetResCorr.root", 5,0,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton80.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton80to120_akPu3PF_NoJetResCorr.root", 5,0,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton120.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton120to170_akPu3PF_NoJetResCorr.root", 5,0,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton170.root",	"no min bias", 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton170to9999_akPu3PF_NoJetResCorr.root", 5,0,0)'
comment

#pA MC 2013 for JEC closure
# before removing maxpthat, xSection
#root -l -q -b 'yj_forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton30.root",	"no min bias", 50, 102400.0, 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton30to50_ak3PF_doJetResCorr_NoSmearing.root", 5,0)'
#root -l -q -b 'yj_forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton50.root",	"no min bias", 80, 39565.0, 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton50to80_ak3PF_doJetResCorr_NoSmearing.root", 5,0)'
#root -l -q -b 'yj_forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton80.root",	"no min bias", 120, 10157.0, 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton80to120_ak3PF_doJetResCorr_NoSmearing.root", 5,0)'
#root -l -q -b 'yj_forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton120.root",	"no min bias", 170, 2517.0, 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton120to170_ak3PF_doJetResCorr_NoSmearing.root", 5,0)'
#root -l -q -b 'yj_forest2yskim_jetSkim_forestV3.C++("/u/user/goyeonju/files/forest/pA/forJEC/HiForest_pPb_MIX_AllQCDPhoton170.root",	"no min bias", 9999, 648.0, 40, "/u/user/goyeonju/files/yskimfiles/pA/yskim_HiForest_pPb_MIX_AllQCDPhoton170to9999_ak3PF_doJetResCorr_NoSmearing.root", 5,0)'


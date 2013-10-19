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
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    35,  "yskim_HiForestPhoton-v7-noDuplicate.root",  0, 1)'

# pbpb MC
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton30to50_genPhotonPtCut40_allCent.root",       "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", 1, 1)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton50to80_genPhotonPtCut40_allCent.root",       "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" ,   35,  "yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", 1, 1)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root",       "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", 1, 1)'

# pp data 
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetNoSmearing.root",2,0,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent5099.root",2,0, 1, 6.1024)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent3050.root",2,0, 1, 7.029)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent1030.root",2,0, 1, 8.219)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent0010.root",2,0, 1, 9.6876)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent3099.root",2,0, 1, 6.813)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent0030.root",2,0, 1, 8.8969)'


# pp MC. photon hiForest
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# pp MC. background hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet30to50_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_emDijet30to50_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet50to80_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_emDijet50to80_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet80to120_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_emDijet80to120_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet120to9999_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_emDijet120to9999_CMSSW538HIp2.root",3,0)'




# pA MC.  photon hiForest
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton30to50_forestv85.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85.root", 5,1)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton50to80_forestv85.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85.root", 5,1)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton80to120_forestv85.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85.root", 5,1)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85.root", 5,1)'

                          
#  pA data, photon hiForest 
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root", "", 35,  "yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root",4,0)'

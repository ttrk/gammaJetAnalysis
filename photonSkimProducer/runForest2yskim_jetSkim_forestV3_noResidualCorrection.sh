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


# MC Residual correction is done for PbPb, pp 
# Data driven L2L3 correction is done for pp pA data and MC 

# pbpb data
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    35,  "yskim_HiForestPhoton-v7-noDuplicate_noJetResCorr.root",  0, 1,0 )'

# pp data 
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskim_pp_photonSKimForest_v85_jetNoSmearing_noJetResCorr.root",2,0,0)'

#  pA data, photon hiForest                                                                                                                   
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root", "yskimmedFiles/minbiasSkim_MergedForest_withCones_MinBiasUPC_v71_1_16HFBin.root", 35,  "yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40_noJetResCorr.root",4,1,0)'
# pA MC.  photon hiForest                                                                                                                     
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton30to50_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton30to50_forestv85_noJetResCorr.root", 5,1,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton50to80_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton50to80_forestv85_noJetResCorr.root", 5,1,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton80to120_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton80to120_forestv85_noJetResCorr.root", 5,1,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/PA2013_pyquen_allQCDPhoton120to9999_forestv85.root",       "yskimmedFiles/minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_PA2013_pyquen_allQCDPhoton120to9999_forestv85_noJetResCorr.root", 5,1,0)'




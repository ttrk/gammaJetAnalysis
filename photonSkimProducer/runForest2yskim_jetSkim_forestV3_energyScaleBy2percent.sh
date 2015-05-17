#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                                   std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   float cutphotonPt  = 50,
#                                   std::string outname = "testPhotonSkim.root",
#                                   sampleType colli=kPADATA,
     #                              bool doMix = false,
    #                               bool doJetResCorrection = 0,
   #                                float addJetEnergyRes = 0,
  #                                 float addFlatJetEnergyRes = 0,
 #                                  float jetEnergyScale = 1,
#                                   bool useGenJetColl = 0
#                                   )
#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5 

# pbpb data
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    40,  "yskim_HiForestPhoton-v7-noDuplicate_jetScaleBy2percent.root",  0, 1, 1,-1,1.02)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    40,  "yskim_HiForestPhoton-v7-noDuplicate_jetScaleBy-2percent.root",  0, 1, 1,-1.,0.98)'

# pp data 
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetScaleBy2percent.root",2,0, 1,-1, 1.02)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetScaleBy-2percent.root",2,0, 1,-1, 0.98)'

#  pA data, photon hiForest 
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root", "", 40,  "yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40_jetScaleBy2percent.root",4,0, 1,-1,1.02)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root",   "", 40,  "yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40_jetScaleBy-2percent.root",4,0, 1,-1,0.98)'

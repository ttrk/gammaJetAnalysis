#void forest2yskim_minbias_forestV3(TString inputFile_="mergedFiles/forest_minbias-HYDJET-START44-V12-Aug29th.root",
#                                  std::string outname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   sampleType colli=kPADATA
#                                   )
                                                                                                               
#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};                                                          
#                   0 (X)    1 (x)  2       3       4        5                                                  

root -l -q -b 'forest2yskim_minbias_forestV3.C++("forestFiles/pA/MergedForest_withCones_MinBiasUPC_v71_1.root",                                                "minbiasSkim_MergedForest_withCones_MinBiasUPC_v71_1.root",   2 )'
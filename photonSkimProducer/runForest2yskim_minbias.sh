#void forest2yskim_minbias_forestV3(TString inputFile_="mergedFiles/forest_minbias-HYDJET-START44-V12-Aug29th.root",
#                                  std::string outname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   sampleType colli=kPADATA
#                                   int maxEvent = -1
#                                   )
                                                                                                               
#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};                                                          
#                   0 (X)    1 (x)  2       3       4        5                                                  


# PbPb
#root -l -q -b 'forest2yskim_minbias_forestV3.C+("forestFiles/pbpb/HIMinBias_merged_1_1000.root",    "minbiasSkim_HIMinBias_merged_1_1000.root",   0 , -1)'
root -l -q -b 'forest2yskim_minbias_forestV3.C+("forestFiles/pbpb/HydjetDrum03_HiForest_v05_merged_test02.root",    "minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",   1 , -1)'


# pA 
#root -l -q -b 'forest2yskim_minbias_forestV3.C+("forestFiles/pA/MergedForest_withCones_MinBiasUPC_v71_1.root",                                                "minbiasSkim_MergedForest_withCones_MinBiasUPC_v71_1.root",   4 , -1)'
#root -l -q -b 'forest2yskim_minbias_forestV3.C+("forestFiles/pA/H02_merged_hiforest_v68_prod12.root",                                                         "minbiasSkim_H02_merged_hiforest_v68_prod12.root",            5 , -1)'

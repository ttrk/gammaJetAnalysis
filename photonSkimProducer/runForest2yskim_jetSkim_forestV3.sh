#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                                  std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   float cutphotonPt  = 50,
#                                   std::string outname = "testPhotonSkim.root",
#                                   sampleType colli=kPADATA,
#                                   bool doMix = false
#                                   )

#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5 



# pA MC.  photon hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_pA_Pyquen_allQCDPhoton30_hiForest2_53x_2013-18-14-1922.root", 5,  1)'   
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_pA_Pyquen_allQCDPhoton50_hiForest2_53x_2013-18-14-1922.root", 5,  1)'   
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_pA_Pyquen_allQCDPhoton80_hiForest2_53x_2013-18-14-1922.root", 5,  1)'   
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_pA_Pyquen_allQCDPhoton120_hiForest2_53x_2013-18-14-1922.root", 5,  1)'   

                          
#  pA data, photon hiForest 
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",                                                      "minbiasSkim_MergedForest_withCones_MinBiasUPC_v71_1.root", 40,  "yskim_pA_photonSkimForest_v85.root",   4, 1)'

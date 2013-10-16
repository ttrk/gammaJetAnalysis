#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                                   std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   float cutphotonPt  = 50,
#                                   std::string outname = "testPhotonSkim.root",
#                                   sampleType colli=kPADATA,
#                                   bool doMix = false,
#                                   bool doJetResCorrection = 0,
#                                   float addJetEnergyRes = 0,
#                                   float addFlatJetEnergyRes = 0,   e.g. 10% => 0.1 
#                                   bool useGenJetColl = 0  
#                                   )
#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5 

# pbpb data
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    40,  "yskim_HiForestPhoton-v7-noDuplicate_jetResCorrected.root",  0, 1,1)'



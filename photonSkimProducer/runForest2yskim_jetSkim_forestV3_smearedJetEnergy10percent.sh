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

for it in 16 17 18 19 20
do
# pbpb data
    root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    40,  "yskim_HiForestPhoton-v7-noDuplicate_smearedBy10Flat_it'$it'.root",  0, 1, 0, 0.1)'
    
# pp data 
    root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_smearedBy10Flat_it'$it'.root",2,0,0,0.1)'
  #  pA data, photon hiForest 
    root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pA/pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40.root", "no minbias", 40,  "yskim_pA_photonSkimForest_v85_HLT_PAPhoton30_NoCaloIdVL_v1_highPtPhoton40_smearedBy10Flat_it'$it'.root",4,0,0,0.1)'
    
done
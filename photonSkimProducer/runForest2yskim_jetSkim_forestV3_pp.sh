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






# pp MC. photon hiForest
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# pp MC. background hiForest
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet30to50_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_emDijet30to50_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet50to80_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_emDijet50to80_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet80to120_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_emDijet80to120_CMSSW538HIp2.root",3,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet120to9999_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 40,  "yskim_emDijet120to9999_CMSSW538HIp2.root",3,0)'





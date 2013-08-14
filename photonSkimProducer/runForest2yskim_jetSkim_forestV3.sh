#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                          std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                          float cutphotonPt  = 50,
#                          std::string outname = "testPhotonSkim.root",
#                          sampleType colli=kPADATA
#                          )
#{
#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5 



# pA MC.  photon hiForest
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/PA2013_pyquen_allQCDPhoton30_forestv78.root",                                                     "", 40,  "yskim_PA2013_pyquen_allQCDPhoton30_forestv78.root", 5)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/PA2013_pyquen_allQCDPhoton50_forestv78.root",                                                     "", 40,  "yskim_PA2013_pyquen_allQCDPhoton50_forestv78.root", 5)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/PA2013_pyquen_allQCDPhoton80_forestv78.root",                                                     "", 40,  "yskim_PA2013_pyquen_allQCDPhoton80_forestv78.root", 5)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/PA2013_pyquen_allQCDPhoton120_forestv78.root",                                                     "", 40,  "yskim_PA2013_pyquen_allQCDPhoton120_forestv78.root", 5)'

                          
#  pA data, photon hiForest 
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",                                                      "", 50,  "yskim_pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",   4)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("forestFiles/pA/pA_photonSkimForest_v85.root",                                                      "", 40,  "yskim_pA_photonSkimForest_v85.root",   4)'

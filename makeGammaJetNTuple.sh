#!/bin/sh
#pp
PPFILE="/mnt/hadoop/cms/store/user/luck/pp_photonSkimForest_v85/pp_photonSKimForest_v85.root"
PAFILE="/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85/pA_photonSkimForest_v85.root"
PAMC="/mnt/hadoop/cms/store/user/luck/PA2013_pyquen_allQCDPhoton_forest_v85/pA_Pyquen_allQCDPhoton280_hiForest2_v85.root"

PPOUTFILE="gammaJets_inclusive_dphi7pi8_pp2013Data_v2.root"
PAOUTFILE="gammaJets_inclusive_dphi7pi8_pPbData_v2.root"
PAMCOUT="gammaJets_inclusive_dphi7pi8_allQCD_v2.root"

root -l -b -x -q makeGammaJetNTuple.C+\(\"$PAFILE\",0,\"$PAOUTFILE\"\)

root -l -b -x -q makeGammaJetNTuple.C+\(\"$PAMC\",1,\"$PAMCOUT\"\)

root -l -b -x -q makeGammaJetNTuple.C+\(\"$PPFILE\",0,\"$PPOUTFILE\"\)

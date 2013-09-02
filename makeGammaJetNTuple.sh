#!/bin/bash
#pp
# PPFILE="/mnt/hadoop/cms/store/user/luck/pp_photonSkimForest_v85/pp_photonSKimForest_v85.root"
# PAFILE="/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85/pA_photonSkimForest_v85.root"
# PAMC="/mnt/hadoop/cms/store/user/luck/PA2013_pyquen_allQCDPhoton_forest_v85/pA_Pyquen_allQCDPhoton280_hiForest2_v85.root"

# PPOUTFILE="gammaJets_inclusive_dphi7pi8_pp2013Data_v2.root"
# PAOUTFILE="gammaJets_inclusive_dphi7pi8_pPbData_v2.root"
# PAMCOUT="gammaJets_inclusive_dphi7pi8_allQCD_v2.root"

# root -l -b -x -q makeGammaJetNTuple.C+\(\"$PAFILE\",0,\"$PAOUTFILE\"\)

# root -l -b -x -q makeGammaJetNTuple.C+\(\"$PAMC\",1,\"$PAMCOUT\"\)

# root -l -b -x -q makeGammaJetNTuple.C+\(\"$PPFILE\",0,\"$PPOUTFILE\"\)


#COUNTER=0
MCWEIGHT=(1 0.0890448 0.0228245 0.00493548) #for pPb
PTHATS=(30 50 80 120 9999)
for COUNTER in 0 1 2 3
do
    INFILE="/mnt/hadoop/cms/store/user/goyeonju/pA/PA2013_pyquen_allQCDPhoton${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_forestv85.root"
    OUTFILE="gammaJets_pA_pythiaHIJING_allQCDPhoton${PTHATS[COUNTER]}_ntuple_v2.root"
    root -l -b -x -q makeGammaJetNTuple.C+\(\"$INFILE\",2,1,\"$OUTFILE\",${MCWEIGHT[$COUNTER]},$COUNTER\)
    #((COUNTER++))
done

hadd gammaJets_pA_merged_allQCDPhoton_ntuple_v2.root gammaJets_pA_pythiaHIJING_allQCDPhoton*_ntuple_v2.root

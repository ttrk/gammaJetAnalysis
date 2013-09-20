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
#MCWEIGHT=(1 0.0890448 0.0228245 0.00493548) #for pPb
# MCWEIGHT=(1 0.398507684312 0.109933481907)
# PTHATS=(30 50 80 9999)
# for COUNTER in 0 1 2 
# do
#     INFILE="/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_genPhotonPtCut40_allCent.root"
#     OUTFILE="gammaJets_PbPb_pythiaHydjet_allQCDPhoton${PTHATS[COUNTER]}_ntuple.root"
#     root -l -b -x -q makeGammaJetNTuple.C+\(\"$INFILE\",0,1,\"$OUTFILE\",${MCWEIGHT[$COUNTER]},$COUNTER\)
#     #((COUNTER++))
# done

# hadd "gammaJets_PbPb_pythiaHydjet_allQCDPhoton_ntuple.root" gammaJets_PbPb_pythiaHydjet_allQCDPhoton*_ntuple.root


MCWEIGHT=(1 0.0920352775378 0.0173632642937 0.00481466824957)
PTHATS=(30 50 80 120 9999)
for COUNTER in 0 1 2 3
do
    INFILE="/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pp/merged_allQCDPhoton${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_genPhotonPtCut30_CMSSW538HIp2.root"
    OUTFILE="gammaJets_pp_pythia_allQCDPhoton${PTHATS[COUNTER]}_ntuple.root"
    root -l -b -x -q makeGammaJetNTuple.C+\(\"$INFILE\",1,1,\"$OUTFILE\",${MCWEIGHT[$COUNTER]},$COUNTER\)
    #((COUNTER++))
done

hadd "gammaJets_pp_pythia_allQCDPhoton_ntuple.root" gammaJets_pp_pythia_allQCDPhoton*_ntuple.root

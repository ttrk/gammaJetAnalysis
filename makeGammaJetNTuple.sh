#!/bin/bash
g++ makeGammaJetNTuple.C $(root-config --cflags --libs) -Werror -Wall -g -o makeGammaJetNTuple.exe || exit 1

# #MC, with weights
# # old PbPb
# MCWEIGHT=(1 0.398507684312 0.109933481907)
# PTHATS=(30 50 80 9999)
# for COUNTER in 0 1 2
# do
#     INFILE="/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_genPhotonPtCut40_allCent.root"
#     OUTFILE="gammaJets_PbPb_MC_allQCDPhoton${PTHATS[COUNTER]}.root"
#     ./makeGammaJetNTuple.exe "$INFILE" 1 "$OUTFILE" ${MCWEIGHT[COUNTER]}
# done
# hadd -f "gammaJets_PbPb_MC_allQCDPhoton.root" gammaJets_PbPb_MC_allQCDPhoton*.root
# echo "done PbPb MC"

# pp
# MCWEIGHT=(1 0.0920352775378 0.0173632642937 0.00481466824957)
# PTHATS=(30 50 80 120 9999)
# for COUNTER in 0 1 2 3
# do
#     INFILE="/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pp/merged_allQCDPhoton${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_genPhotonPtCut30_CMSSW538HIp2.root"
#     OUTFILE="gammaJets_pp_MC_PUallQCDPhoton${PTHATS[COUNTER]}.root"
#     ./makeGammaJetNTuple.exe "$INFILE" 3 "$OUTFILE" ${MCWEIGHT[COUNTER]}
# done
# hadd -f "gammaJets_pp_MC_PUallQCDPhoton.root" gammaJets_pp_MC_PUallQCDPhoton*.root
# echo "done pp MC"

# # pp emDijet
# MCWEIGHT=(1 0.404961197098 0.141530314457 0.032841679188)
# PTHATS=(30 50 80 120 9999)
# for COUNTER in 0 1 2 3
# do
#     INFILE="/mnt/hadoop/cms/store/user/goyeonju/MC_Production/PYTHIA/pp_2760GeV/forest/pp2760_pyquen_emDijet${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_forestv85_20130915.root"
#     OUTFILE="gammaJets_pp_MC_EmEnrichedDijet${PTHATS[COUNTER]}.root"
#     ./makeGammaJetNTuple.exe "$INFILE" 3 "$OUTFILE" ${MCWEIGHT[COUNTER]}
# done
# hadd -f "gammaJets_pp_MC_EmEnrichedDijet.root" gammaJets_pp_MC_EmEnrichedDijet*.root
# echo "done pp MC"

#./makeGammaJetNTuple.exe "/mnt/hadoop/cms/store/user/goyeonju/MC_Production/PYTHIA/pp_2760GeV/forest/pp2760_pyquen_emDijet30to50_forestv85_20130915.root" 3 "test_out.root" 1

# pA
MCWEIGHT=(1 0.2748977252606957 0.0715241955868448 0.017885353733615463 0.0046474324546893235 )
PTHATS=(30 50 80 120 170 9999)
for COUNTER in 0 1 2 3 4
do
    INFILE="/export/d00/scratch/luck/yskimmedFiles/merged_allQCDPhoton${PTHATS[COUNTER]}to${PTHATS[COUNTER+1]}_genPtCut40_CMSSW5320.root"
    OUTFILE="gammaJets_pA_MC_allQCDPhoton${PTHATS[COUNTER]}.root"
    ./makeGammaJetNTuple.exe "$INFILE" 5 "$OUTFILE" ${MCWEIGHT[COUNTER]}
done
hadd -f "gammaJets_pA_MC_allQCDPhoton.root" gammaJets_pA_MC_allQCDPhoton*.root
echo "done pA MC"

# # Data
# # pp
# ./makeGammaJetNTuple.exe "SAMPLES/ppPhotonDATA.root" 2 "gammaJets_pp_Data.root"
# echo "Done pp data"

# pA
./makeGammaJetNTuple.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_DATA_photon30trig_localJEC_v1.root" 4 "gammaJets_pA_Data.root"
echo "Done pA data"

# # PbPb
# ./makeGammaJetNTuple.exe "SAMPLES/pbpbPhotonDATA.root" 0 "gammaJets_PbPb_Data.root"
# echo "Done PbPb Data"

#!/bin/sh
# pbpb MC
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton30to50_genPhotonPtCut40_allCent.root",       "minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", 1, 1)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton50to80_genPhotonPtCut40_allCent.root",       "minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" ,   35,  "yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", 1, 1)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root",       "minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", 1, 1)'

# pp smeared
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent30100.root",2, 0,0,3.37)'  # 0.001, 3.88
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 40,   "yskim_pp_photonSKimForest_v85_jetSmearingCent0030.root",2 ,0, 0, 5.16)'

# # pythia smeared
PTHATS=(30 50 80 120 9999)
OUTPUT=(0010 1030 3050 5099)
for centBin in 0 1 2 3
do
    for i in 0 1 2 3
    do
	root -l -q -b forest2yskim_jetSkim_forestV3.C++g\(\"forestFiles/pp/merged_allQCDPhoton${PTHATS[i]}to${PTHATS[i+1]}_genPhotonPtCut30_CMSSW538HIp2.root\",\"minbiasSkim_H02_merged_hiforest_v68_prod12.root\",35,\"yskim_merged_allQCDPhoton${PTHATS[i]}to${PTHATS[i+1]}_genPhotonPtCut30_CMSSW538HIp2_jetSmearingCent${OUTPUT[centBin]}.root\",3,0,${centBin},0\)
    done
done


# pythia no smearing
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12.root", 35,  "yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'

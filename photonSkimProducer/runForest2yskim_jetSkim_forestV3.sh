# shell script to skim all of the required files for HIN-13-006, using
# the nominal settings (not for systematic studies).

#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5

g++ forest2yskim_minbias_forestV3.C $(root-config --cflags --libs) -Wall -Wextra -g -o forest2yskim_minbias_forestV3.exe
g++ forest2yskim_jetSkim_forestV3.C $(root-config --cflags --libs) -Wall -Wextra -g -o forest2yskim_jetSkim_forestV3.exe

# # pbpb minbias skim, for mixing
###./forest2yskim_minbias_forestV3.exe "/mnt/hadoop/cms/store/user/luck/PbPb2011_photons_Data/HIMinBias_merged_1_1000.root" "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root" 0 -1
###./forest2yskim_minbias_forestV3.exe "/mnt/hadoop/cms/store/user/yetkin/MC_Production/HydjetDrum03/HydjetDrum03_HiForest_v05_merged_test02.root" "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" 1 -1

# # pbpb data
###./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/PbPb2011_photons_Data/HiForestPhoton-v7-noDuplicate.root" "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root" 35 "yskimmedFiles/yskim_HiForestPhoton-v7-noDuplicate.root" 0 1

# # pbpb MC
###./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton30to50_genPhotonPtCut40_allCent.root" "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" 35 "yskimmedFiles/yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root" 1 1
###./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton50to80_genPhotonPtCut40_allCent.root" "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" 35 "yskimmedFiles/yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root" 1 1
###./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/jazzitup/forestFiles/pbpb/qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root" "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" 35 "yskimmedFiles/yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root" 1 1

# # pp data
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetNoSmearing.root",2,0,1)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetSmearingCent5099.root",2,0, 1, 3)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetSmearingCent3050.root",2,0, 1, 2)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetSmearingCent1030.root",2,0, 1, 1)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetSmearingCent0010.root",2,0, 1, 0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetSmearingCent3099.root",2,0, 1, 5)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/pp_photonSKimForest_v85.root",       "no minbias", 35,   "yskimmedFiles/yskim_pp_photonSKimForest_v85_jetSmearingCent0030.root",2,0, 1, 4)'


# # pp MC. photon hiForest
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton30to50_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton50to80_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton80to120_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",       "no min bias", 35,  "yskim_merged_allQCDPhoton120to9999_genPhotonPtCut30_CMSSW538HIp2.root",3,0)'
# pp MC. background hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet30to50_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet30to50_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet50to80_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet50to80_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet80to120_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet80to120_CMSSW538HIp2.root",3,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pp/emDijet120to9999_CMSSW538HIp2.root",       "minbiasSkim_H02_merged_hiforest_v68_prod12_16HFBin.root", 35,  "yskim_emDijet120to9999_CMSSW538HIp2.root",3,0)'


#  pA data, photon hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_DATA_photon30trig_localJEC_v1.root", "", 0, 1, 35,  "yskimmedFiles/yskim_pA_DATA_photonForest.root",4,0)'
# pA MC.  photon hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton30.root", "", 50,  102400, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton3050.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton50.root", "", 80, 39656, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton5080.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton80.root", "", 120, 10157, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton80120.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton120.root", "", 170, 2517,35, "yskimmedFiles/yskim_pA_AllQCDPhoton120170.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton170.root", "", 9999, 649, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton1709999.root", 5,0)'

# 06/08/2015
# pA data, sample="2013 pPb photon-triggered", https://twiki.cern.ch/twiki/bin/viewauth/CMS/PhotonAnalyses2015#Data
###root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_Data_all_localJEC_v3_HiForest_nodupes.root", "", 35,  "/export/d00/scratch/luck/yskimmedFiles/yskim_pPb_Data_all_localJEC_v3_HiForest_nodupes.root",4,0)'
## for g++ compiled code
#./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_Data_all_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pPb_Data_all_localJEC_v3_HiForest_nodupes_g++.root" 4 0

# pp data, sample=" 2013 pp photon-triggered", https://twiki.cern.ch/twiki/bin/viewauth/CMS/PhotonAnalyses2015#Data
### root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root", "", 35, "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin0.root",2,0,1,0)'
### root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root", "", 35, "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin1.root",2,0,1,1)'
### root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root", "", 35, "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin2.root",2,0,1,2)'
### root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root", "", 35, "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin3.root",2,0,1,3)'
### root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root", "", 35, "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin4.root",2,0,1,4)'
### root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root", "", 35, "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin5.root",2,0,1,5)'
## for g++ compiled code
# ./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin0_g++.root" 2 0 1 0 1 0 0
# ./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin1_g++.root" 2 0 1 1 1 0 0
# ./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin2_g++.root" 2 0 1 2 1 0 0
# ./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin3_g++.root" 2 0 1 3 1 0 0
# ./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin4_g++.root" 2 0 1 4 1 0 0
# ./forest2yskim_jetSkim_forestV3.exe "/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_Data_localJEC_v3_HiForest_nodupes.root" "" 35 "/export/d00/scratch/luck/yskimmedFiles/yskim_pp_Data_localJEC_v3_HiForest_nodupes_smearingCentBin5_g++.root" 2 0 1 5 1 0 0

# 06/11/2015
# pp MC, sample="AllQCDPhoton", https://twiki.cern.ch/twiki/bin/viewauth/CMS/PhotonAnalyses2015
# inputDir="/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pp_MIX_localJEC_v3_pthatsorted/";
# outputDir="/export/d00/scratch/luck/yskimmedFiles/";
# ./forest2yskim_jetSkim_forestV3.exe $inputDir"pp_MC_AllQCDPhoton30to50_localJEC_53X.root" "" 35 $outputDir"yskim_pp_MC_AllQCDPhoton30to50_localJEC_53X.root" 3 0
# ./forest2yskim_jetSkim_forestV3.exe $inputDir"pp_MC_AllQCDPhoton50to80_localJEC_53X.root" "" 35 $outputDir"yskim_pp_MC_AllQCDPhoton50to80_localJEC_53X.root" 3 0
# ./forest2yskim_jetSkim_forestV3.exe $inputDir"pp_MC_AllQCDPhoton80to120_localJEC_53X.root" "" 35 $outputDir"yskim_pp_MC_AllQCDPhoton80to120_localJEC_53X.root" 3 0
# ./forest2yskim_jetSkim_forestV3.exe $inputDir"pp_MC_AllQCDPhoton120to999_localJEC_53X.root" "" 35 $outputDir"yskim_pp_MC_AllQCDPhoton120to999_localJEC_53X.root" 3 0

# 06/11/2015
# pA MC, sample="AllQCDPhoton", https://twiki.cern.ch/twiki/bin/view/CMS/PhotonAnalyses2015#pPb_centrally_produced
inputDir="/mnt/hadoop/cms/store/user/tatar/2015-photon-forests/pPb_Pbp_MIX_localJEC_v3_pthatsorted/";
outputDir="/export/d00/scratch/luck/yskimmedFiles/";
./forest2yskim_jetSkim_forestV3.exe $inputDir"merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_30_50.root" "" 35 $outputDir"yskim_merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_30_50.root" 5 0
./forest2yskim_jetSkim_forestV3.exe $inputDir"merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_50_80.root" "" 35 $outputDir"yskim_merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_50_80.root" 5 0
./forest2yskim_jetSkim_forestV3.exe $inputDir"merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_80_120.root" "" 35 $outputDir"yskim_merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_80_120.root" 5 0
./forest2yskim_jetSkim_forestV3.exe $inputDir"merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_120_9999.root" "" 35 $outputDir"yskim_merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3_ptHat_120_9999.root" 5 0


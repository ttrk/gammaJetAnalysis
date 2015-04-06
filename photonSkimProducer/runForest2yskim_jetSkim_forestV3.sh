#void forest2yskim_jetSkim_forestV3(TString inputFile_="forestFiles/pA/pA_photonSkimForest_v85_skimPhotonPt50_eta1.5.root",
#                                   std::string MinbiasFname = "skim_trackJet_minbiasTrackJet_mc.root",
#                                   float cutphotonPt  = 35,  // default value dropped to 35GeV  for later photon energy smearing/scaling
#                                   std::string outname = "testPhotonSkim.root",
#                                   sampleType colli=kPADATA,
#                                   bool doMix = false,
#                                   bool doJetResCorrection = 1,  // jet energy correction is done by default from Oct 19th (YS)
#				    int smearingCentBin = -1, //0=0-10%, 1=10-30%, 2=30-50%, 3=50-100%, 4=0-30%, 5=30-100%  : Jet pT and phi smearing!
#                                   float addFlatJetEnergyRes = 0,
#                                   bool useGenJetColl = 0
#                                   )



#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                       0    1      2       3       4        5



# # pbpb data
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/HiForestPhoton-v7-noDuplicate.root",       "yskimmedFiles/minbiasSkim_HIMinBias_merged_1_1000.root",    35,  "yskim_HiForestPhoton-v7-noDuplicate.root",  0, 1)'

# # pbpb MC
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton30to50_genPhotonPtCut40_allCent.root",       "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_qcdAllPhoton30to50_genPhotonPtCut40_allCent.root", 1, 1)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton50to80_genPhotonPtCut40_allCent.root",       "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root" ,   35,  "yskim_qcdAllPhoton50to80_genPhotonPtCut40_allCent.root", 1, 1)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("forestFiles/pbpb/qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root",       "yskimmedFiles/minbiasSkim_HydjetDrum03_HiForest_v05_merged_test02.root",    35,  "yskim_qcdAllPhoton80to9999_genPhotonPtCut40_allCent.root", 1, 1)'

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
####root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_DATA_photon30trig_localJEC_v2.root", "", 35,  "yskim_pA_DATA_photonForest_kaya.root",4,0)'
root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_DATA_photon30trig_localJEC_v2.root", "", 35,  "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_DATA_photonForest_kaya_noDuplicate.root",4,0)'

##########################
# inDirectory="/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/";
# outDirectory="/export/d00/scratch/tatar/output/yskimmed/";
# outFilePrefix="yskim_pA_photonSkimForest_v85_fromPromptReco_";

# mkdir -p $outDirectory

# for s ampleNum in `seq 0 89`
# do
#     inFile=$inDirectory$sampleNum".root";
#     outFile=$outDirectory$outFilePrefix$sampleNum".root";
#     progROOT="forest2yskim_jetSkim_forestV3.C++("\"$inFile\"", "\"\"", 35,  "\"$outFile\"",4,0)";
# #    echo $inFile
# #    echo $outFile
# #    echo  root -l -q -b \'$progROOT\'
# #    root -l -q -b $progROOT
# done
##########################

### yskim over the 1.1 TB true "old" sample
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C++("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/0.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_0.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/1.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_1.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/2.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_2.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/3.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_3.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/4.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_4.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/5.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_5.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/6.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_6.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/7.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_7.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/8.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_8.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/9.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_9.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/10.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_10.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/11.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_11.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/12.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_12.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/13.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_13.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/14.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_14.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/15.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_15.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/16.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_16.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/17.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_17.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/18.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_18.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/19.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_19.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/20.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_20.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/21.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_21.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/22.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_22.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/23.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_23.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/24.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_24.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/25.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_25.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/26.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_26.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/27.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_27.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/28.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_28.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/29.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_29.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/30.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_30.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/31.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_31.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/32.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_32.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/33.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_33.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/34.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_34.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/35.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_35.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/36.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_36.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/37.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_37.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/38.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_38.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/39.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_39.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/40.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_40.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/41.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_41.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/42.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_42.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/43.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_43.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/44.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_44.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/45.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_45.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/46.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_46.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/47.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_47.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/48.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_48.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/49.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_49.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/50.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_50.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/51.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_51.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/52.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_52.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/53.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_53.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/54.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_54.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/55.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_55.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/56.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_56.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/57.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_57.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/58.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_58.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/59.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_59.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/60.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_60.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/61.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_61.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/62.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_62.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/63.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_63.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/64.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_64.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/65.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_65.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/66.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_66.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/67.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_67.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/68.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_68.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/69.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_69.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/70.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_70.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/71.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_71.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/72.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_72.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/73.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_73.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/74.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_74.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/75.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_75.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/76.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_76.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/77.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_77.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/78.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_78.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/79.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_79.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/80.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_80.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/81.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_81.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/82.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_82.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/83.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_83.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/84.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_84.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/85.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_85.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/86.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_86.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/87.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_87.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/88.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_88.root",4,0)'
# root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge/89.root", "", 35, "/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco_89.root",4,0)'

# pA MC.  photon hiForest
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton30.root", "", 50,  102400, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton3050.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton50.root", "", 80, 39656, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton5080.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton80.root", "", 120, 10157, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton80120.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton120.root", "", 170, 2517,35, "yskimmedFiles/yskim_pA_AllQCDPhoton120170.root", 5,0)'
#root -l -q -b 'forest2yskim_jetSkim_forestV3.C+("/mnt/hadoop/cms/store/user/luck/2014-photon-forests/pPb_MIX_localJEC_v1/HiForest_pPb_MIX_AllQCDPhoton170.root", "", 9999, 649, 35, "yskimmedFiles/yskim_pA_AllQCDPhoton1709999.root", 5,0)'


 

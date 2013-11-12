root -l -q  'drawPP60GeV.C+("nominal",20131021)'  #done
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_nominal.root

root -l -q  'drawPP60GeV.C+("photonEnergyScale-0.015",20131020)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_photonEnergyScaleMinus.root

root -l -q  'drawPP60GeV.C+("photonEnergyScale0.015",20131020)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_photonEnergyScalePlus.root

root -l -q  'drawPP60GeV.C+("noElectronRejection",20131020)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_noElectronRejection.root

root -l -q  'drawPP60GeV.C+("noJetResCorr",20131020)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_noJetResCorr.root

root -l -q  'drawPP60GeVMC.C+("genOrReco0",20131022)'  #DONE
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_MCgenIso.root

root -l -q  'drawPP60GeVMC.C+("genOrReco1",20131022)'   #DONE
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_MCrecoIso.root

root -l -q  'drawPP60GeV.C+("photonPurityVaried",20131021)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_photonPurityVaried.root

root -l -q  'drawPP60GeV.C+("jetEnergySmearedBy10percent",20131022)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_jetEnergySmeared.root

root -l -q  'drawPP60GeV.C+("jetEnergyScale0.020",20131022)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_jetEnergyScalePlus.root

root -l -q  'drawPP60GeV.C+("jetEnergyScale-0.020",20131022)'
mv pp60GeV_resultHistograms.root  pp60GeV_resultHistograms_jetEnergyScaleMinus.root




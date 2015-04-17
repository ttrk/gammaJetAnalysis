root -l -q 'drawPtDependence.C+("nominal",20131023)'  #done
root -l -q 'drawPtDependencePA.C+("nominal",20131023)' 
mv resultHistograms.root  resultHistograms_nominal_vtxCentWeighted.root

root -l -q 'drawPtDependence.C+("photonEnergyScale-0.015",20131020)'
root -l -q 'drawPtDependencePA.C+("photonEnergyScale-0.015",20131020)'
mv resultHistograms.root  resultHistograms_photonEnergyScaleMinus.root

root -l -q 'drawPtDependence.C+("photonEnergyScale0.015",20131020)'
root -l -q 'drawPtDependencePA.C+("photonEnergyScale0.015",20131020)'
mv resultHistograms.root  resultHistograms_photonEnergyScalePlus.root

root -l -q 'drawPtDependence.C+("noElectronRejection",20131020)'
root -l -q 'drawPtDependencePA.C+("noElectronRejection",20131020)'
mv resultHistograms.root  resultHistograms_noElectronRejection.root

root -l -q 'drawPtDependence.C+("noJetResCorr",20131020)'
root -l -q 'drawPtDependencePA.C+("noJetResCorr",20131020)'
mv resultHistograms.root  resultHistograms_noJetResCorr.root

root -l -q 'drawPtDependenceMC.C+("genOrReco0",20131023)'  #DONE // vertex centrality reweighted
root -l -q 'drawPtDependencePAMC.C+("genOrReco0",20131023)' 
mv resultHistograms.root  resultHistograms_MCrecoIso.root

root -l -q 'drawPtDependenceMC.C+("genOrReco1",20131023)'   #DONE
root -l -q 'drawPtDependencePAMC.C+("genOrReco1",20131023)'
mv resultHistograms.root  resultHistograms_MCgenIso.root

root -l -q 'drawPtDependence.C+("photonPurityVaried",20131021)'
root -l -q 'drawPtDependencePA.C+("photonPurityVaried",20131021)'
mv resultHistograms.root  resultHistograms_photonPurityVaried.root

root -l -q 'drawPtDependence.C+("jetEnergySmearedBy10percent",20131022)'
root -l -q 'drawPtDependencePA.C+("jetEnergySmearedBy10percent",20131022)'
mv resultHistograms.root  resultHistograms_jetEnergySmeared.root

root -l -q 'drawPtDependence.C+("jetEnergyScale0.020",20131022)'
root -l -q 'drawPtDependencePA.C+("jetEnergyScale0.020",20131022)'
mv resultHistograms.root  resultHistograms_jetEnergyScalePlus.root

root -l -q 'drawPtDependence.C+("jetEnergyScale-0.020",20131022)'
root -l -q 'drawPtDependencePA.C+("jetEnergyScale-0.020",20131022)'
mv resultHistograms.root  resultHistograms_jetEnergyScaleMinus.root


root -l -q 'drawPtDependence.C+("nominal_Jet20GeV",20131021,20)'
root -l -q 'drawPtDependencePA.C+("nominal_Jet20GeV",20131021,20)'
mv resultHistograms.root  resultHistograms_nominal_Jet20GeV.root

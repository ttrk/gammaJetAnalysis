for scale in -0.015 0.015 
do
for i in  2 
do
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C++('$i', 40, 50, 30, 7,  '$scale')'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50, 60, 30, 7,  '$scale')'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60, 80, 30, 7,  '$scale')'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 80,9999, 30, 7,  '$scale')'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,9999, 30, 7,  '$scale')'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,9999, 30, 7,  '$scale')'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,9999, 30, 7,  '$scale')'
done

#PbPb data, MC                                                                                                                              
for i in  0
do
    for icent in 10030 13099 
    do
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,50, 30, '$icent',  '$scale')'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,60, 30,'$icent',  '$scale')'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,80, 30, '$icent',  '$scale')'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 80,9999, 30, '$icent',  '$scale')'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,9999, 30, '$icent',  '$scale')'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,9999, 30, '$icent',  '$scale')'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,9999, 30, '$icent',  '$scale')'
     done
done

for i in 4 5
do
    for icent in 1 #2 3 
   do
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,50, 30, '$icent',  '$scale')'
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,60, 30, '$icent',  '$scale')'
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,80, 30, '$icent',  '$scale')'
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 80,9999, 30, '$icent', '$scale')'
   done 
done

done
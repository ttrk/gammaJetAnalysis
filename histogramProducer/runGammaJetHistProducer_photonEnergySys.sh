for i in  2 3
do
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40, 50, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50, 60, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60, 80, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 100,9999, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 80,9999, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,9999, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,9999, 30, 7,  0.015)'
root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,9999, 30, 7,  0.015)'
done

#PbPb data, MC                                                                                                                              
for i in  0 1
do
    for icent in 10030 13099 10010 11030 13050 15099
    do
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,50, 30, '$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,60, 30,'$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,80, 30, '$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 100,9999, 30, '$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 80,9999, 30, '$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,9999, 30, '$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,9999, 30, '$icent',  0.015)'
        root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,9999, 30, '$icent',  0.015)'
     done
done

for i in 4 5
do
    for icent in 1 #2 3 
   do
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 40,50, 30, '$icent',  0.015)'
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 50,60, 30, '$icent',  0.015)'
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 60,80, 30, '$icent',  0.015)'
	root -l -b -q 'gammaJetHistProducer_photonEnergySys.C+('$i', 80,9999, 30, '$icent', 0.015)'
   done 
done


#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                  0        1      2        3      4        5
#void gammaJetHistProducer_jetEnergySmearedBy10percent(sampleType collision = kHIDATA, float photonPtThr=60, float photonPtThrUp=1000000, float jetPtThr=30, int icent =1)


#pp data 
for i in  2 
do
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 40, 50, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 50, 60, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 60, 80, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 100,9999, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 80,9999, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 60,9999, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 50,9999, 30, 7)'
root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 40,9999, 30, 7)'
done

#PbPb data
for i in  0 
do
    for icent in 10030 13099 10010 11030 13050 15099
    do
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 40,50, 30, '$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 50,60, 30,'$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 60,80, 30, '$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 100,9999, 30, '$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 80,9999, 30, '$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 60,9999, 30, '$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 50,9999, 30, '$icent')'
        root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 40,9999, 30, '$icent')'
     done
done




#pPb data 

for i in 4
do
    for icent in 1 #2 3 
   do
	root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 40,50, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 50,60, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 60,80, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer_jetEnergySmearedBy10percent.C+('$i', 80,9999, 30, '$icent')'
   done 
done


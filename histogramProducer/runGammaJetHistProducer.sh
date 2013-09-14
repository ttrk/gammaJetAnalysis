#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                  0        1      2        3      4        5
#void gammaJetHistProducer(sampleType collision = kHIDATA, float photonPtThr=60, float photonPtThrUp=1000000, float jetPtThr=30, int icent =1)


#pp data 
root -l -b -q 'gammaJetHistProducer.C+(2, 40, 50, 30, 4)'
root -l -b -q 'gammaJetHistProducer.C+(2, 50, 60, 30, 4)'
root -l -b -q 'gammaJetHistProducer.C+(2, 60, 80, 30, 4)'
root -l -b -q 'gammaJetHistProducer.C+(2, 80,9999, 30, 4)'
root -l -b -q 'gammaJetHistProducer.C+(2, 60,9999, 30, 4)'

#PbPb data, MC
for i in  0 1
do
    for icent in 10030 13099 
    do
	root -l -b -q 'gammaJetHistProducer.C+('$i', 40,50, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 50,60, 30,'$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 60,80, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 80,9999, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 60,9999, 30, '$icent')'
    done
done


#pPb data and MC
for i in 4 5 
do
    for icent in 1 #2 3 
   do
	root -l -b -q 'gammaJetHistProducer.C+('$i', 40,50, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 50,60, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 60,80, 30, '$icent')'
	root -l -b -q 'gammaJetHistProducer.C+('$i', 80,9999, 30, '$icent')'
   done 
done


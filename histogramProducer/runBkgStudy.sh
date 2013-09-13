#enum sampleType { kHIDATA, kHIMC, kPPDATA, kPPMC, kPADATA, kPAMC};
#                  0        1      2        3      4        5
#void gammaJetHistProducer(sampleType collision = kHIDATA, float photonPtThr=60, float photonPtThrUp=1000000, float jetPtThr=30, int icent =1)


#pp data 
for sigShift in 0 -0.00007
do
    for bkgShift in 0 30 40 50 60 70 80 90 100
    do
	root -l -b -q 'gammaJetPurity.C+(2,40,50,30,4,'$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(2,50,60,30,4,'$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(2,60,80,30,4,'$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(2,80,9999,30,4,'$bkgShift','$sigShift')'
    done
done

#PbPb data 
for icent in 10030 13099
do
    for sigShift in 0 -0.00007
    do
	for bkgShift in 0 30 40 50 60 70 80 90 100
	do
	    root -l -b -q 'gammaJetPurity.C+(0,40,50,30,'$icent','$bkgShift','$sigShift')'
	    root -l -b -q 'gammaJetPurity.C+(0,50,60,30,'$icent','$bkgShift','$sigShift')'
	    root -l -b -q 'gammaJetPurity.C+(0,60,80,30,'$icent','$bkgShift','$sigShift')'
	    root -l -b -q 'gammaJetPurity.C+(0,80,9999,30,'$icent','$bkgShift','$sigShift')'
	done
    done
done

#pPb data
for sigShift in 0 -0.00007
do
    for bkgShift in 0 30 40 50 60 70 80 90 100
    do
	root -l -b -q 'gammaJetPurity.C+(4, 40,50, 30, 1,  '$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(4, 50,60, 30, 1,  '$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(4, 60,80, 30, 1,  '$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(4, 80,9999, 30, 1,'$bkgShift','$sigShift')'
	root -l -b -q 'gammaJetPurity.C+(4, 40,9999, 30, 1,'$bkgShift','$sigShift')'
    done
done



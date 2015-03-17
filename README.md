gammaJetAnalysis
================

To prepare a gammaJetAnalysis area, and to re-use the photon skims that Alex has made, follow these directions.

```Shell
cmsrel CMSSW_5_3_20
cd CMSSW_5_3_20/src
cmsenv
git clone https://github.com/CmsHI/HiForestAnalysis.git
git clone https://github.com/CmsHI/gammaJetAnalysis.git
cd photonSkimProducer
yskimmedFiles ./
cd ..
cd histogramProducer
mkdir ffFiles
ln -s /export/d00/scratch/luck/yskimmedFiles ./
cd ..
cd drawFigures
ln -s ../histogramProducer/ffFiles/ ./
mkdir figures
```
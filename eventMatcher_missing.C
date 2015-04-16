/*
 * find events that are in file1 but not in file2
 * "event" must pass isolation cut + photon pt cut
 *
 * 10.04.2015
 * 	forget about using yPhotonTree which is huge and probably broken.
 * 	plot the sigmaIetaIeta distribution of events that are in file2 (old sample) but not in file1 (new sample)
 * 	in the old file only events that pass the isolation cut will be considered.
 * */
#include "photonSkimProducer/EventMatchingCMS.h"
#include "../HiForestAnalysis/hiForest.h"
#include "CutAndBinCollection2012.h"

#include <TLeaf.h>
#include <TObject.h>

using namespace std;

// necessary for GCC C++ Compiler to work
#include <string>
#include <iostream>
#include <iomanip>			// setprecision()
using  std::string;
using  std::cout;
using  std::endl;
//

const float cut_eta = 1.44;
// photon pt cut
const float cut_photon_pt = 40;
// Isolation
const float cut_ecalIso = 4.2;
const float cut_hcalIso = 2.2;
const float cut_trackIso = 2.0;
//const float cut_hadronicOverEm = 0.1;
const bool addEvents_passing_Iso = true;	// true : in the old file only events that pass the isolation cut will be considered.
const bool plot_sigmaIetaIeta    = false;	// true : plot the sigmaIetaIeta distribution of events
											// that are in file2 (old sample) but not in file1 (new sample)
											// sigmaIetaIeta ratio of new and old samples was <1 for sigmaIetaIeta > 0.01
											// this implied there could be missing events in the new sample
											// https://twiki.cern.ch/twiki/pub/CMS/PhotonAnalyses2015/150407_forest2yskim.pdf, slide 9

const bool check_forest = true ;			// look for missing events in Forest

// 34342
// 33635

int eventMatcher_missing_forest(TString inputFile_forest,
				   EventMatchingCMS* eventMatcherYSKIM,
				   int hlt_triggers_fired[3],
				   sampleType colli=kPADATA
				   );

void eventMatcher_missing(const TString fileName1, const TString fileName2)
{
	  cout << "fileName1 = " << fileName1 <<endl;
	  cout << "fileName2 = " << fileName2 <<endl;
	  cout << "addEvents_passing_Iso = " << addEvents_passing_Iso <<endl;

	  TFile* file1 = new TFile(fileName1, "READ");
	  TFile* file2 = new TFile(fileName2, "READ");

//	  TTree* yPhotonTree1 = (TTree*)file1->Get("yPhotonTree");
	  TTree* tgj1         = (TTree*)file1->Get("tgj");
//	  TTree* yPhotonTree2 = (TTree*)file2->Get("yPhotonTree");
	  TTree* tgj2         = (TTree*)file2->Get("tgj");

//	  TBranch* b_run1;
//	  TBranch* b_evt1;
//	  TBranch* b_lumi1;		// ignore lumi
	  TBranch* b_tgj_evt1;
	  Int_t run1;
	  Int_t evt1;
//	  Int_t lumi1;			// ignore lumi
	  Int_t lumi1=0;
	  b_tgj_evt1 = tgj1->GetBranch("evt");

	  TBranch* b_lpho1;
	  float photonEt1;
	  float photonEta1;
	  b_lpho1 = tgj1->GetBranch("lpho");

	  TBranch* b_iso1;
	  float ecalIso1;
	  float hcalIso1;
	  float trackIso1;
	  b_iso1 = tgj1->GetBranch("isolation");

	  TBranch* b_tgj_evt2;
	  Int_t run2;
	  Int_t evt2;
//	  Int_t lumi2;			// ignore lumi
	  Int_t lumi2=0;
	  b_tgj_evt2 = tgj2->GetBranch("evt");

	  TBranch* b_lpho2;
	  float photonEt2;
	  float photonEta2;
	  b_lpho2 = tgj2->GetBranch("lpho");

	  TBranch* b_iso2;
	  float ecalIso2;
	  float hcalIso2;
	  float trackIso2;
	  b_iso2 = tgj2->GetBranch("isolation");

	  float sigmaIetaIeta2;

	  Long64_t entries1 = tgj1->GetEntries();
	  Long64_t entries2 = tgj2->GetEntries();
	  Long64_t entries1_after_iso = 0;
	  Long64_t entries2_after_iso = 0;

	  cout << "events in new sample = " << entries1 << endl;
	  cout << "events in old sample = " << entries2 << endl;

	  EventMatchingCMS* eventMatcher1=new EventMatchingCMS();
	  EventMatchingCMS* eventMatcher2=new EventMatchingCMS();
	  EventMatchingCMS* eventsNotInFile1=new EventMatchingCMS();

	  cout << "creating the map of events in the new sample" << endl;
	  bool     eventAdded1;
	  Long64_t duplicateEvents1 = 0;
	  bool passed_iso1;
	  bool passed_photon1;
	  for( Long64_t i = 0; i < entries1; ++i)
	  {
//		  yPhotonTree1->GetEntry(i);	// do not use this.
		  b_tgj_evt1->GetEntry(i);
		  run1 = (int) ((TLeaf*)b_tgj_evt1->GetListOfLeaves()->At(0))->GetValue();
		  evt1 = (int) ((TLeaf*)b_tgj_evt1->GetListOfLeaves()->At(1))->GetValue();

		  if(addEvents_passing_Iso)
		  {
			  b_lpho1->GetEntry(i);
			  photonEt1  = (float) ((TLeaf*)b_lpho1->GetListOfLeaves()->At(0))->GetValue();
			  photonEta1 = (float) ((TLeaf*)b_lpho1->GetListOfLeaves()->At(2))->GetValue();

			  b_iso1->GetEntry(i);
			  ecalIso1  = (float) ((TLeaf*)b_iso1->GetListOfLeaves()->At(15))->GetValue();
			  hcalIso1  = (float) ((TLeaf*)b_iso1->GetListOfLeaves()->At(16))->GetValue();
			  trackIso1 = (float) ((TLeaf*)b_iso1->GetListOfLeaves()->At(17))->GetValue();

			  passed_photon1 = (TMath::Abs(photonEta1) < cut_eta       &&
					  	  	                photonEt1 > cut_photon_pt );
			  passed_iso1    = ( ecalIso1  < cut_ecalIso	 &&
			        		    hcalIso1  < cut_hcalIso	 &&
							    trackIso1 < cut_trackIso   );

			  if(passed_photon1 && passed_iso1)
			  {
				  entries1_after_iso++;

				  eventAdded1 = eventMatcher1->addEvent(evt1, lumi1, run1, i);
				  if(!eventAdded1)
				  {
					  duplicateEvents1++;
				  }
			  }
		  }
		  else
		  {
			  eventAdded1 = eventMatcher1->addEvent(evt1, lumi1, run1, i);
			  if(!eventAdded1)
			  {
				  duplicateEvents1++;
			  }
		  }
	  }

	  // in the new file try to find the events that are in the old file
	  long long    eventRetrieved;
	  Long64_t notRetrievedEvents = 0;
	  bool     eventAdded2;
	  Long64_t duplicateEvents2 = 0;
	  bool passed_iso2;
	  bool passed_photon2;
	  std::vector<int> entriesNotInFile1;		// missing events from file1 = events that are in file2, but not in file1
	  for( Long64_t i = 0; i < entries2; i++)
	  {

		  b_tgj_evt2->GetEntry(i);
		  run2 = (int) ((TLeaf*)b_tgj_evt2->GetListOfLeaves()->At(0))->GetValue();
		  evt2 = (int) ((TLeaf*)b_tgj_evt2->GetListOfLeaves()->At(1))->GetValue();

		  if(addEvents_passing_Iso)
		  {
			  b_lpho2->GetEntry(i);
			  photonEt2  = (float) ((TLeaf*)b_lpho2->GetListOfLeaves()->At(0))->GetValue();
			  photonEta2 = (float) ((TLeaf*)b_lpho2->GetListOfLeaves()->At(2))->GetValue();

			  b_iso2->GetEntry(i);
			  ecalIso2  = (float) ((TLeaf*)b_iso2->GetListOfLeaves()->At(15))->GetValue();
			  hcalIso2  = (float) ((TLeaf*)b_iso2->GetListOfLeaves()->At(16))->GetValue();
			  trackIso2 = (float) ((TLeaf*)b_iso2->GetListOfLeaves()->At(17))->GetValue();

			  passed_photon2 = (TMath::Abs(photonEta2) < cut_eta       &&
					  photonEt2 > cut_photon_pt );
			  passed_iso2    = ( ecalIso2  < cut_ecalIso	 &&
					  hcalIso2  < cut_hcalIso	 &&
					  trackIso2 < cut_trackIso   );

			  if(passed_photon2 && passed_iso2)
			  {
				  entries2_after_iso++;

				  eventRetrieved = eventMatcher1->retrieveEventNoErase(evt2, lumi2, run2);
				  if(eventRetrieved < 0)
				  {
					  cout << "photonEt2  = " << photonEt2 << endl;
					  cout << "photonEta2 = " << photonEta2 << endl;

					  cout << "ecalIso2   = " << ecalIso2  << endl;
					  cout << "hcalIso2   = " << hcalIso2  << endl;
					  cout << "trackIso2  = " << trackIso2 << endl;

					  cout << "Event in file2 could not be found in file1 : "
							  << " evt = "   << evt2
							  << " lumi = "  << lumi2
							  << " run = "   << run2
							  << " entry = " << i
							  << endl;

					  notRetrievedEvents++;

					  entriesNotInFile1.push_back(i);
					  eventsNotInFile1->addEvent(evt2, lumi2, run2, i);
				  }

				  eventAdded2 = eventMatcher2->addEvent(evt2, lumi2, run2, i);
				  if(!eventAdded2)
				  {
					  duplicateEvents2++;
				  }
			  }
		  }
		  else
		  {
			  eventRetrieved = eventMatcher1->retrieveEventNoErase(evt2, lumi2, run2);
			  if(eventRetrieved < 0)
			  {
				  cout << "photonEt2  = " << photonEt2 << endl;
				  cout << "photonEta2 = " << photonEta2 << endl;

				  cout << "ecalIso2   = " << ecalIso2  << endl;
				  cout << "hcalIso2   = " << hcalIso2  << endl;
				  cout << "trackIso2  = " << trackIso2 << endl;

				  cout << "Event in file2 could not be found in file1 : "
						  << " evt = "   << evt2
						  << " lumi = "  << lumi2
						  << " run = "   << run2
						  << " entry = " << i
						  << endl;

				  notRetrievedEvents++;

				  entriesNotInFile1.push_back(i);
				  eventsNotInFile1->addEvent(evt2, lumi2, run2, i);
			  }

			  eventAdded2 = eventMatcher2->addEvent(evt2, lumi2, run2, i);
			  if(!eventAdded2)
			  {
				  duplicateEvents2++;
			  }
		  }
	  }	  

	  if(plot_sigmaIetaIeta)
	  {
		  int j;
		  TFile* outFile=new TFile("eventMatcher_missing.root", "RECREATE");
		  TH1D* h_sigmaIetaIeta = new TH1D("sigmaIetaIeta", "sigmaIetaIeta for events in old sample but not in new sample" ,20, 0, 0.025);
		  for(int i=0; i<entriesNotInFile1.size(); i++)
		  {
			  j = entriesNotInFile1.at(i);
			  b_lpho2->GetEntry(j);

			  sigmaIetaIeta2 = (float) ((TLeaf*)b_lpho2->GetListOfLeaves()->At(6))->GetValue();
			  h_sigmaIetaIeta->Fill(sigmaIetaIeta2);
		  }
//		  TCanvas* c=new TCanvas();
		  h_sigmaIetaIeta->Write();
		  outFile->Close();
	  }

	  cout << "events in new sample = " << entries1 << endl;
	  cout << "events in old sample = " << entries2 << endl;
	  cout << "Duplicate events in new sample = " << duplicateEvents1 << endl;
	  cout << "Duplicate events in old sample = " << duplicateEvents2 << endl;

	  cout << "events in new sample that pass isolation cut = "    << entries1_after_iso << endl;
	  cout << "events in old sample that pass isolation cut = "    << entries2_after_iso << endl;
	  cout << "events in old sample that are not in new sample = " << notRetrievedEvents << endl;

	  file1->Close();
	  file2->Close();

	  if(check_forest)
	  {
		  // count of the times these triggers are fired.
		  int HLT_PAPhoton10_NoCaloIdVL_v1_count = 0;
		  int HLT_PAPhoton15_NoCaloIdVL_v1_count = 0;
		  int HLT_PAPhoton20_NoCaloIdVL_v1_count = 0;
		  int HLT_PAPhoton30_NoCaloIdVL_v1_count = 0;
		  int HLT_PAPhoton40_NoCaloIdVL_v1_count = 0;

		  int hlt_triggers_fired [5] = {0, 0, 0, 0, 0};

		  TString inputForest_name;
		  int match_count     = 0;
		  int match_count_tmp = 0;
		  const char* inputForest_prefix = "/mnt/hadoop/cms/store/user/luck/pA_photonSkimForest_v85_fromPromptReco_partialmerge";
		  for (int i=0; i<=89; i++)	// forest file names go from 0.root to 89.root
		  {
			  inputForest_name = Form("%s/%d.root",inputForest_prefix,i);
			  match_count_tmp = eventMatcher_missing_forest(inputForest_name, eventsNotInFile1, hlt_triggers_fired, kPADATA);
			  match_count    += match_count_tmp;

			  HLT_PAPhoton10_NoCaloIdVL_v1_count += hlt_triggers_fired[0];
			  HLT_PAPhoton15_NoCaloIdVL_v1_count += hlt_triggers_fired[1];
			  HLT_PAPhoton20_NoCaloIdVL_v1_count += hlt_triggers_fired[2];
			  HLT_PAPhoton30_NoCaloIdVL_v1_count += hlt_triggers_fired[3];
			  HLT_PAPhoton40_NoCaloIdVL_v1_count += hlt_triggers_fired[4];
		  }

		  cout << "events in new sample = " << entries1 << endl;
		  cout << "events in old sample = " << entries2 << endl;
		  cout << "Duplicate events in new sample = " << duplicateEvents1 << endl;
		  cout << "Duplicate events in old sample = " << duplicateEvents2 << endl;

		  cout << "events in new sample that pass isolation cut = "    << entries1_after_iso << endl;
		  cout << "events in old sample that pass isolation cut = "    << entries2_after_iso << endl;
		  cout << "events in old sample that are not in new sample = " << notRetrievedEvents << endl;

		  cout << "number of missing events matched in the whole forest = " << match_count      << endl;
		  cout << "Count of HLT Trigger fire values for events in old sample that are not in new sample :" <<endl;
		  cout << "HLT_PAPhoton10_NoCaloIdVL_v1_count = " << HLT_PAPhoton10_NoCaloIdVL_v1_count << endl;
		  cout << "HLT_PAPhoton15_NoCaloIdVL_v1_count = " << HLT_PAPhoton15_NoCaloIdVL_v1_count << endl;
		  cout << "HLT_PAPhoton20_NoCaloIdVL_v1_count = " << HLT_PAPhoton20_NoCaloIdVL_v1_count << endl;
		  cout << "HLT_PAPhoton30_NoCaloIdVL_v1_count = " << HLT_PAPhoton30_NoCaloIdVL_v1_count << endl;
		  cout << "HLT_PAPhoton40_NoCaloIdVL_v1_count = " << HLT_PAPhoton40_NoCaloIdVL_v1_count << endl;
	  }
}

/*
 check HLT values of events that are missing from the new sample : events that are in old sample but not in new sample
 * */
int eventMatcher_missing_forest(TString inputFile_forest,
				   EventMatchingCMS* eventMatcherYSKIM,
				   int hlt_triggers_fired[5],
				   sampleType colli /* =kPADATA */
				   )
{
  bool isMC=true;
  if ((colli==kPPDATA)||(colli==kPADATA)||(colli==kHIDATA))
    isMC=false;

  HiForest *c;
  if((colli==kPADATA)||(colli==kPAMC)) {
    c = new HiForest(inputFile_forest.Data(), "forest", cPPb, isMC );
  }
  else if  ((colli==kPPDATA)||(colli==kPPMC)) {
    c = new HiForest(inputFile_forest.Data(), "forest", cPP, isMC );
  }
  else if  ((colli==kHIDATA)||(colli==kHIMC)) {
    c = new HiForest(inputFile_forest.Data(), "forest", cPbPb, isMC );
    c->GetEnergyScaleTable("../photonEnergyScaleTable_lowPt_v6.root");
  }
  else {
    cout << " Error!  No such collision type" << endl;
    return -1;
  }

  //////// Kaya's modificiation ////////
  cout << "inputFile_forest         = " << inputFile_forest		<< endl;
  //////// Kaya's modificiation - END ////////

  c->LoadNoTrees();
  c->hasEvtTree = true;
  c->hasHltTree = true;

  c->InitTree();

  // Loop starts.
  int nentries = c->GetEntries();
  cout << "number of entries = " << nentries << endl;
  long long    eventRetrieved;
  int match_count = 0;
  int HLT_PAPhoton10_NoCaloIdVL_v1_count=0;
  int HLT_PAPhoton15_NoCaloIdVL_v1_count=0;
  int HLT_PAPhoton20_NoCaloIdVL_v1_count=0;
  int HLT_PAPhoton30_NoCaloIdVL_v1_count=0;
  int HLT_PAPhoton40_NoCaloIdVL_v1_count=0;

  for (Long64_t jentry = 0 ; jentry < nentries; jentry++) {

    if (jentry% 200000 == 0)  {
      cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;
    }

    c->GetEntry(jentry);

    //////// Kaya's modificiation ////////
    eventRetrieved = eventMatcherYSKIM->retrieveEventNoErase(c->evt.evt, 0, c->evt.run);	// eventMatcherYSKIM is not created using lumi values
    																						// "evt" and "run" should be enough to match the events.
    if(eventRetrieved>0)	// this event is inside eventMatcherYSKIM
    {
    	match_count++;

    	// get HLT triggers
    	cout << "this event is inside eventMatcherYSKIM" << endl;
    	cout << "jentry = " << jentry     << endl;
    	cout << "evt    = " << c->evt.evt << endl;
    	cout << "run    = " << c->evt.run << endl;
    	cout << "HLT_PAPhoton10_NoCaloIdVL_v1 = " << c->hlt.HLT_PAPhoton10_NoCaloIdVL_v1 << endl;
    	cout << "HLT_PAPhoton15_NoCaloIdVL_v1 = " << c->hlt.HLT_PAPhoton15_NoCaloIdVL_v1 << endl;
    	cout << "HLT_PAPhoton20_NoCaloIdVL_v1 = " << c->hlt.HLT_PAPhoton20_NoCaloIdVL_v1 << endl;
    	cout << "HLT_PAPhoton30_NoCaloIdVL_v1 = " << c->hlt.HLT_PAPhoton30_NoCaloIdVL_v1 << endl;
    	cout << "HLT_PAPhoton40_NoCaloIdVL_v1 = " << c->hlt.HLT_PAPhoton40_NoCaloIdVL_v1 << endl;

    	if(c->hlt.HLT_PAPhoton10_NoCaloIdVL_v1 > 0)
    	{
    		HLT_PAPhoton10_NoCaloIdVL_v1_count++;
    	}
    	if(c->hlt.HLT_PAPhoton15_NoCaloIdVL_v1 > 0)
    	{
    		HLT_PAPhoton15_NoCaloIdVL_v1_count++;
    	}
    	if(c->hlt.HLT_PAPhoton20_NoCaloIdVL_v1 > 0)
    	{
    		HLT_PAPhoton20_NoCaloIdVL_v1_count++;
    	}
    	if(c->hlt.HLT_PAPhoton30_NoCaloIdVL_v1 > 0)
    	{
    		HLT_PAPhoton30_NoCaloIdVL_v1_count++;
    	}
    	if(c->hlt.HLT_PAPhoton40_NoCaloIdVL_v1 > 0)
    	{
    		HLT_PAPhoton40_NoCaloIdVL_v1_count++;
    	}
    }
    //////// Kaya's modificiation - END ////////
  }
  hlt_triggers_fired[0]=HLT_PAPhoton10_NoCaloIdVL_v1_count;
  hlt_triggers_fired[1]=HLT_PAPhoton15_NoCaloIdVL_v1_count;
  hlt_triggers_fired[2]=HLT_PAPhoton20_NoCaloIdVL_v1_count;
  hlt_triggers_fired[3]=HLT_PAPhoton30_NoCaloIdVL_v1_count;
  hlt_triggers_fired[4]=HLT_PAPhoton40_NoCaloIdVL_v1_count;

  cout << "number of events matched = " << match_count      << endl;
  cout << "closing file             = " << inputFile_forest << endl;

  c->inf->Close();

  return match_count;
}

int main()
{
	const TString newSample_yskimmed="/export/d00/scratch/tatar/output/yskimmed/yskim_pA_DATA_photonForest_kaya_noDuplicate.root";
	const TString oldSample_yskimmed="/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco.root";

	eventMatcher_missing(newSample_yskimmed, oldSample_yskimmed);
//	eventMatcher_missing(oldSample_yskimmed, newSample_yskimmed);
}

void eventMatcher_missing()
{
	main();
}

/*
 * find events that are in file1 but not in file2
 * "event" must pass isolation cut + photon pt cut
 * */
#include "photonSkimProducer/EventMatchingCMS.h"
#include "../HiForestAnalysis/hiForest.h"

#include <TLeaf.h>

// necessary for GCC C++ Compiler to work
#include <string>
using  std::string;
using  std::cout;
using  std::endl;
//
const int MAXPHOTONS = 126;

const float cut_eta = 1.44;
// photon pt cut
const float cut_photon_pt = 40;
// Isolation
const float cut_ecalIso = 4.2;
const float cut_hcalIso = 2.2;
const float cut_trackIso = 2.0;
//const float cut_hadronicOverEm = 0.1;

// 34342
// 33635

void eventMatcher_missing(const TString fileName1, const TString fileName2)
{
	  cout << "fileName1 = " << fileName1 <<endl;
	  cout << "fileName2 = " << fileName2 <<endl;

	  TFile* file1 = new TFile(fileName1, "READ");
	  TFile* file2 = new TFile(fileName2, "READ");

	  TTree* yPhotonTree1 = (TTree*)file1->Get("yPhotonTree");
	  TTree* yPhotonTree2 = (TTree*)file2->Get("yPhotonTree");
	  TTree* tgj2         = (TTree*)file2->Get("tgj");	////////////////////////HERE

	  Int_t run1;
	  Int_t evt1;
	  Int_t lumi1;
	  yPhotonTree1->SetBranchAddress("run",&run1);
	  yPhotonTree1->SetBranchAddress("event",&evt1);
	  yPhotonTree1->SetBranchAddress("luminosityBlock",&lumi1);

	  Int_t run2;
	  Int_t evt2;
	  Int_t lumi2;
	  yPhotonTree2->SetBranchAddress("run",&run2);
	  yPhotonTree2->SetBranchAddress("event",&evt2);
	  yPhotonTree2->SetBranchAddress("luminosityBlock",&lumi2);

	  TBranch* b_lpho;
	  double photonEt;
	  Float_t photonEta;
	  Float_t ecalIso;
	  Float_t hcalIso;
	  Float_t trackIso;
	  b_lpho = tgj2->GetBranch("lpho");
//	  tgj2->SetBranchAddress("lpho.photonEt",&photonEt, );
//	  tgj2->SetBranchAddress("lpho",&photonEt, &b_lpho);
//	  b_lpho->GetLeaf("photonEt");


//	  tgj2->SetBranchAddress("lpho.photonEta",&photonEta);
//	  tgj2->SetBranchAddress("lpho.ecalIso",&ecalIso);
//	  tgj2->SetBranchAddress("lpho.hcalIso",&hcalIso);
//	  tgj2->SetBranchAddress("lpho.trackIso",&trackIso);

	  Long64_t entries1 = yPhotonTree1->GetEntries();
	  Long64_t entries2 = yPhotonTree2->GetEntries();
	  Long64_t entries2_after_iso = 0;

	  EventMatchingCMS* eventMatcher1=new EventMatchingCMS();
	  EventMatchingCMS* eventMatcher2=new EventMatchingCMS();

	  cout << "creating the map of events in the old sample" << endl;
	  bool     eventAdded1;
	  Long64_t duplicateEvents1 = 0;
	  for( Long64_t i = 0; i < 2; ++i)
	  {
		  yPhotonTree1->GetEntry(i);
		  cout << run1 << endl;
		  cout << evt1 << endl;
		  cout << lumi1 << endl;
		  //b_lpho->GetEntry(i);

//          photonEt = b_lpho->GetLeaf("photonEt")->GetValue(0);
//  cout << photonEt << endl;

		  eventAdded1 = eventMatcher1->addEvent(evt1, lumi1, run1, i);
		  if(!eventAdded1)
		  {
			  duplicateEvents1++;
		  }
	  }

	  // in the new file try to find the events that are in the old file
	  long long    eventRetrieved;
	  Long64_t notRetrievedEvents = 0;
	  bool passed_iso;
	  bool passed_photon;
	  for( Long64_t i = 0; i < 2; ++i)
	  {
		  yPhotonTree2->GetEntry(i);
		          tgj2->GetEntry(i);


		  passed_photon = (TMath::Abs(photonEta) < cut_eta       &&
				  	  	                photonEt > cut_photon_pt );
		  passed_iso    = ( ecalIso  < cut_ecalIso	 &&
		        		    hcalIso  < cut_hcalIso	 &&
						    trackIso < cut_trackIso   );

		  if(passed_photon && passed_iso)
		  {
			  entries2_after_iso++;

			  eventRetrieved = eventMatcher1->retrieveEventNoErase(evt2, lumi2, run2);
			  if(eventRetrieved < 0)
			  {
				  cout << "Event in file1 could not be found in file2 : "  << " evt = "   << evt2
						  << " lumi = "  << lumi2
						  << " run = "   << run2
						  << " entry = " << i
						  << endl;

				  notRetrievedEvents++;
			  }
		  }
	  }	  

	  cout << "events in old sample = " << entries2 << endl;
	  cout << "events in new sample = " << entries2 << endl;
	  cout << "Duplicate events in old sample = " << duplicateEvents1 << endl;

	  cout << "events in new sample that pass isolation cut = "    << entries2_after_iso << endl;
	  cout << "events in old sample that are not in new sample = " << notRetrievedEvents << endl;

	  file1->Close();
	  file2->Close();
}

int main()
{
	const TString oldSample_yskimmed="/export/d00/scratch/tatar/output/yskimmed/yskim_pA_photonSkimForest_v85_fromPromptReco.root";
	const TString newSample_yskimmed="/export/d00/scratch/tatar/output/yskimmed/yskim_pA_DATA_photonForest_kaya_noDuplicate.root";

	eventMatcher_missing(oldSample_yskimmed, newSample_yskimmed);
}

void eventMatcher_missing()
{
	main();
}

/*
 * find events that are in file1 but not in file2
 * "event" must pass isolation cut + photon pt cut
 * */
#include "photonSkimProducer/EventMatchingCMS.h"
#include "../HiForestAnalysis/hiForest.h"

#include <TLeaf.h>
#include <TObject.h>

// necessary for GCC C++ Compiler to work
#include <string>
#include <iostream>
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

	  TBranch* b_run1;
	  TBranch* b_evt1;
	  TBranch* b_lumi1;
	  Int_t run1;
	  Int_t evt1;
	  Int_t lumi1;
	  yPhotonTree1->SetBranchAddress("run",&run1, &b_run1);
	  yPhotonTree1->SetBranchAddress("event",&evt1, &b_evt1);
	  yPhotonTree1->SetBranchAddress("luminosityBlock",&lumi1, &b_lumi1);
//	  b_run1->SetAutoDelete(kTRUE);
//	  b_evt1->SetAutoDelete(kTRUE);
//	  b_lumi1->SetAutoDelete(kTRUE);

	  TBranch* b_run2;
	  TBranch* b_evt2;
	  TBranch* b_lumi2;
	  Int_t run2;
	  Int_t evt2;
	  Int_t lumi2;
	  yPhotonTree2->SetBranchAddress("run",&run2, &b_run2);
	  yPhotonTree2->SetBranchAddress("event",&evt2, &b_evt2);
	  yPhotonTree2->SetBranchAddress("luminosityBlock",&lumi2, &b_lumi2);

	  TBranch* b_lpho;
	  float photonEt;
	  float photonEta;
	  b_lpho = tgj2->GetBranch("lpho");
//	  b_lpho->SetBasketSize(128000);

	  TBranch* b_iso;
	  float ecalIso;
	  float hcalIso;
	  float trackIso;
	  b_iso = tgj2->GetBranch("isolation");
//	  b_iso->SetBasketSize(128000);

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

	  cout << "events in old sample = " << entries1 << endl;
	  cout << "events in new sample = " << entries2 << endl;

	  EventMatchingCMS* eventMatcher1=new EventMatchingCMS();

	  cout << "creating the map of events in the old sample" << endl;
	  bool     eventAdded1;
	  Long64_t duplicateEvents1 = 0;
	  for( Long64_t i = 0; i < 1100; ++i)
	  {
		  cout << "entry = " << i << endl;
//		  yPhotonTree1->GetEntry(i);	// do not use this.
		  try
		   {
//			  b_run1->GetEntry(i);
//			  b_evt1->GetEntry(i);
//			  b_lumi1->GetEntry(i);

			  if(i==1058)
			  {
				  cout << "braeasdasak  point" <<endl;
			  }

			  cout<<b_run1->GetEntry(i)<<endl;
			  cout<<b_evt1->GetEntry(i)<<endl;
			  cout<<b_lumi1->GetEntry(i)<<endl;

			  cout << run1 << endl;
			  cout << evt1 << endl;
			  cout << lumi1 << endl;

			  cout << b_run1->GetBasketSize() <<endl;
			  cout << b_evt1->GetBasketSize() <<endl;
			  cout << b_lumi1->GetBasketSize() <<endl;
		   }
		   catch (int e)
		   {
		     cout << "An exception occurred. Exception Nr. " << e << endl;
		   }
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

	  int b1, b2, b3, b4, b5;
	  for( Long64_t i = 0; i < 0; i++)
	  {
		  cout << "entry = " << i << endl;

//		  yPhotonTree2->GetEntry(i);	// do not use this.
		  b1=b_run2->GetEntry(i);
		  cout << b1 << " b1" <<endl;
		  b2=b_evt2->GetEntry(i);
		  cout << b2 << " b2" <<endl;
		  b3=b_lumi2->GetEntry(i);
		  cout << b3 << " b3" <<endl;

//		  tgj2->GetEntry(i);
		  b4=b_lpho->GetEntry(i);
		  cout << b4 << " b4" <<endl;
		  b5=b_iso ->GetEntry(i);
		  cout << b5 << " b5" <<endl;

		  photonEt  = (float) ((TLeaf*)b_lpho->GetListOfLeaves()->At(0))->GetValue();
		  photonEta = (float) ((TLeaf*)b_lpho->GetListOfLeaves()->At(2))->GetValue();

		  ecalIso  = (float) ((TLeaf*)b_iso->GetListOfLeaves()->At(15))->GetValue();
		  hcalIso  = (float) ((TLeaf*)b_iso->GetListOfLeaves()->At(16))->GetValue();
		  trackIso = (float) ((TLeaf*)b_iso->GetListOfLeaves()->At(17))->GetValue();

//		  cout << b_lpho->GetListOfLeaves()->At(0) <<endl;
//		  cout << *(b_lpho->GetListOfLeaves()->At(0)) <<endl;
//		  cout << *(b_lpho->GetListOfLeaves()->At(0)+1) <<endl;
//		  cout << *(b_lpho->GetListOfLeaves()->At(0)+2) <<endl;
//		  cout << *(b_lpho->GetListOfLeaves()->At(0)+3) <<endl;
//		  cout << *(b_lpho->GetListOfLeaves()->At(0)+4) <<endl;

//		  photonEt =(float) b_lpho->GetListOfLeaves()->At(0);
//		  photonEta=dynamic_cast<float>(b_lpho->GetListOfLeaves()->At(2));
//
//		  ecalIso =(Float_t)(b_iso->GetListOfLeaves()->At(15));
//		  hcalIso =(float)(b_iso->GetListOfLeaves()->At(16));
//		  trackIso=(float)(b_iso->GetListOfLeaves()->At(17));


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
				  cout << Form("%s = ", b_lpho->GetListOfLeaves()->At(0)->GetTitle()) << photonEt << endl;
				  cout << Form("%s = ", b_lpho->GetListOfLeaves()->At(2)->GetTitle()) << photonEta << endl;

				  cout << Form("%s = ", b_iso->GetListOfLeaves()->At(15)->GetTitle()) << ecalIso  << endl;
				  cout << Form("%s = ", b_iso->GetListOfLeaves()->At(16)->GetTitle()) << hcalIso  << endl;
				  cout << Form("%s = ", b_iso->GetListOfLeaves()->At(17)->GetTitle()) << trackIso << endl;

				  cout << "Event in file1 could not be found in file2 : "  << " evt = "   << evt2
						  << " lumi = "  << lumi2
						  << " run = "   << run2
						  << " entry = " << i
						  << endl;

				  notRetrievedEvents++;
			  }
		  }
	  }	  

	  cout << "events in old sample = " << entries1 << endl;
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

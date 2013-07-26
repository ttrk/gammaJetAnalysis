// uniquePhotons.C
// plot values from the gamma Jet ntuple using only one entry per event
// i.e. not nJets per event
// inspired by http://stackoverflow.com/questions/12002098/removing-duplicate-entries-in-a-root-ttree

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TEntryList.h"
#include <set>

void use_only_unique_events(TNtuple *inTuple, TString key="event")
{
  std::set<int> eventIds; // keep track of already seen event numbers
  Float_t KEY;
  Int_t KEY_int;
  Float_t epsilon = 0.01;
  Long64_t nEntries = inTuple->GetEntries();

  inTuple->SetBranchAddress(key,&KEY); // grab the event number from the tree

  TEntryList *tlist = new TEntryList(inTuple); // initialize entry list for 'TTree* tree'

  for (Long64_t j = 0; j < nEntries; ++j)
  {
    inTuple->GetEvent(j);

// if we have not seen this event yet, add it to the set
// and to the entry list
    KEY_int = (int) (KEY+epsilon);
    if (eventIds.count(KEY_int) == 0)
    {
      eventIds.insert(KEY_int);
      tlist->Enter(j,inTuple);
    }
  }

// apply the entry list to the tree
  inTuple->SetEntryList(tlist);

}

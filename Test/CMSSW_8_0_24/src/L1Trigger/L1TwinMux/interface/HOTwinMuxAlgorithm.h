# ifndef HOTwinMuxAlgorithm_H
# define HOTwinMuxAlgorithm_H


# include "DataFormats/HcalDigi/interface/HOTriggerPrimitiveDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackCand.h"
# include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"



namespace HOTwinMuxAlgorithm
{
    void addHOinfo(std::vector <L1MuDTChambPhDigi> *digis_L1MuDTChambPh, \
        const L1MuDTChambThContainer::The_Container *digis_L1MuDTChambTh, \
        edm::Handle <edm::SortedCollection <HOTriggerPrimitiveDigi> > hotpHandle);
}


# endif

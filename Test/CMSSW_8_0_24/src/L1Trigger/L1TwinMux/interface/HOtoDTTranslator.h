# ifndef HOtoDTTranslator_H
# define HOtoDTTranslator_H


# include "DataFormats/HcalDigi/interface/HOTriggerPrimitiveDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"


namespace HOtoDTTranslator
{
    L1MuDTChambPhDigi translate(L1MuDTChambPhDigi DTphiDigi, \
        HOTriggerPrimitiveDigi hotpDigi);
}


# endif

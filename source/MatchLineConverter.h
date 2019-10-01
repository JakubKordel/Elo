//
// Created by Jakub Kordel on 25.09.19.
//

#ifndef ELO_MATCHLINECONVERTER_H
#define ELO_MATCHLINECONVERTER_H

#include <string>
#include <iostream>
#include "Match.h"

class MatchLineConverter {
    std::string line;
    Match * match;
public:
    Player * p1;
    Player * p2;
    MatchLineConverter( const std::string & matchLine, const std::string & playersList );
    MatchLineConverter( const Match & m );

   ~MatchLineConverter();

   std::string getLine() const ;
   Match * getMatch() const ;
};


#endif //ELO_MATCHLINECONVERTER_H

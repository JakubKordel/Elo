//
// Created by Jakub Kordel on 24.09.19.
//

#ifndef ELO_MATCH_H
#define ELO_MATCH_H
#include <string>
#include "FilesFunctions.h"

class MatchLineConverter;
class Player;

class Match {
    Player &player1;
    int scr1;
    Player &player2;
    int scr2;
    std::string tourney;
    friend class MatchLineConverter;
	friend void changePlayerName(const std::string&, const std::string&, const std::string&, const std::string&);
public:
    Match( Player & firstPlayer, Player & secondPlayer, int firstPlayerScore, int secondPlayerScore );
    Match( Player & firstPlayer, Player & secondPlayer, int firstPlayerScore, int secondPlayerScore, const std::string & tourneyName );
    void report( const std::string & playersListFile, const std::string & matchesHistoryFile, const std::string & backupHistory ); //adds match to history, updates players elo
};


#endif //ELO_MATCH_H

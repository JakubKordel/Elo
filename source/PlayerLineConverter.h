//
// Created by Jakub Kordel on 24.09.19.
//

#ifndef ELO_PLAYERLINECONVERTER_H
#define ELO_PLAYERLINECONVERTER_H

#include <iostream>

class Player;

class PlayerLineConverter {
    std::string line;
    std::string nick;
    std::string playstyle;
    size_t position;
    int points;
    int wins;
    int ties;
    int loses;
    int topTenWins;
    std::string separator;

public:
    PlayerLineConverter( const std::string & playerLine );
    PlayerLineConverter( const Player & player );
    std::string getLine() const;
    std::string getNick() const;
    int getPoints() const;
    int getWins() const;
    int geTies() const;
    int getLoses() const;
    std::string getPlaystyle() const;
    size_t getPosition() const;
    int getTopTenWins() const;

};


#endif //ELO_PLAYERLINECONVERTER_H

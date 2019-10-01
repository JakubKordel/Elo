//
// Created by Jakub Kordel on 24.09.19.
//

#ifndef ELO_PLAYERSLIST_H
#define ELO_PLAYERSLIST_H

#include <string>

class Player;

class PlayersList {
    std::string playersFile;

public:
    PlayersList( const std::string & fileName );
    bool contains(const std::string & nick );
    void savePlayer( const Player & player );
    std::string findLine( const std::string & playerNick );
    void updatePositons();
    size_t countPlayers();
    void sort();
};


#endif //ELO_PLAYERSLIST_H

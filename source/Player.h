//
// Created by Jakub Kordel on 23.09.19.
//

#ifndef ELO_PLAYER_H
#define ELO_PLAYER_H

#include <string>

class Player {
protected:
    size_t position;
    std::string nick;
    std::string playstyle;
    int points;
    int wins;
    int ties;
    int loses;
    int topTenWins;


public:
    Player( const std::string & gameName );
    Player( const std::string & gameName, const int & eloPoints );
    Player( const std::string & gameName, const std::string & playersFile );
    Player( const std::string & gameName, const int & eloPoints, const int & w, const int & t, const int & l );

    void changeNick( const std::string & newNick );
    void setPoints( const int & newElo );
    std::string getNick() const ;
    int getPoints() const ;
    void save( const std::string & file ) const;
    void setWins(const int & newWins);
    void setTies( const int & newTies);
    void setLoses(const int & newLoses );
    void addWin();
    void addTie();
    void addLose();
    int getWins() const ;
    int getTies() const ;
    int getLoses() const ;
    size_t getPosition() const;
    void setPosition( const size_t newPosition);
    std::string getPlaystyle() const;
    void setPlaystyle( const std::string & newPlaystyle);
    int getTopTenWins() const;
    void setTopTenWins(const int & newTopTenWins );
    void addTopTenWin();
};


#endif //ELO_PLAYER_H

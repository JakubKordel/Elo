//
// Created by Jakub Kordel on 24.09.19.
//

#include "Match.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "PlayersList.h"
#include "MatchLineConverter.h"
#include "StringsBasicsFunctions.h"

bool isTopTenWinCounted( const std::string & file ){
    size_t counter = 0;
    std::ifstream inFile;
    inFile.open(file);
    std::string line;
    while (inFile.good()){
        getline(inFile, line);
        if (isGood(line)){
            ++counter;
        }
        if ( counter == 110 ) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

Match::Match( Player &firstPlayer, Player &secondPlayer, int firstPlayerScore, int secondPlayerScore ) : player1(firstPlayer), player2(secondPlayer) {
    scr1 = firstPlayerScore;
    scr2 = secondPlayerScore;
    tourney = "";
}

void Match::report(const std::string &playersListFile, const std::string &matchesHistoryFile, const std::string &backup) {
    bool topTenWin = false;
    std::string sgn1, sgn2;
    const double K = 40;
    const double L = 300;
    double r1 = pow( 10, player1.getPoints()/L );
    double r2 = pow( 10, player2.getPoints()/L );
    double e1 = r1/(r1+r2);
    double e2 = r2/(r1+r2);
    double s1;
    double s2;
    if (scr1 > scr2){
        player1.addWin();
        if ( player2.getPosition() <= 10 && player2.getPosition() > 0 && isTopTenWinCounted(backup) ) {
            player1.addTopTenWin();
            topTenWin = true;
        }
        player2.addLose();
        s1 = 1;
        s2 = 0;
    } else if (scr1 < scr2 ){
        player1.addLose();
        player2.addWin();
        if (player1.getPosition() <= 10 && player1.getPosition() > 0 && isTopTenWinCounted(backup) ){
            player2.addTopTenWin();
            topTenWin = true;
        }
        s1 = 0;
        s2 = 1;
    } else {
        player1.addTie();
        player2.addTie();
        s1 = 0.5;
        s2 = 0.5;
    }

    int diff1 = (int)(K*(s1 - e1));
    int diff2 = (int)(K*(s2 - e2));
    if ( diff1 >= 0 ) sgn1 = " + ";
    else sgn1 = " - ";
    if ( diff2 >= 0 ) sgn2 = " + ";
    else sgn2 = " - ";

    std::fstream file;
    file.open( matchesHistoryFile, std::ios::out|std::ios::app);

    file << player1.getNick() << "(" << player1.getPoints() << sgn1 << abs(diff1) << ")   "<< scr1 << " - " << scr2 << "   " <<
    player2.getNick() << "(" << player2.getPoints() << sgn2 << abs(diff2) << ")  " << tourney;
    if ( topTenWin ) file << "    Top10 Win ";
    file << std::endl;
    file.close();

    file.open( "PlayersHistory/" + player1.getNick() + ".txt", std::ios::out|std::ios::app);

    file << player1.getNick() << "(" << player1.getPoints() << sgn1 << abs(diff1) << ")   "<< scr1 << " - " << scr2 << "   " <<
         player2.getNick() << "(" << player2.getPoints() << sgn2 << abs(diff2) << ")  " << tourney;
    if ( topTenWin && scr1 > scr2) file << "    Top10 Win ";
    else if (topTenWin && scr1 < scr2) file << "    Top10 Lose ";
    file << std::endl;
    file.close();

    file.open( "PlayersHistory/" + player2.getNick() + ".txt", std::ios::out|std::ios::app);

    file << player1.getNick() << "(" << player1.getPoints() << sgn1 << abs(diff1) << ")   "<< scr1 << " - " << scr2 << "   " <<
         player2.getNick() << "(" << player2.getPoints() << sgn2 << abs(diff2) << ")  " << tourney;
    if ( topTenWin && scr1 < scr2) file << "    Top10 Win ";
    else if (topTenWin && scr1 > scr2) file << "    Top10 Lose ";
    file << std::endl;
    file.close();

    player1.setPoints( player1.getPoints() + diff1);
    player2.setPoints( player2.getPoints() + diff2); 
    player1.save(playersListFile);
    player2.save(playersListFile);
    PlayersList list(playersListFile);
    list.updatePositons();

    MatchLineConverter converter(*this);
    file.open( backup, std::ios::out|std::ios::app );
    file << converter.getLine() << std::endl;
    file.close();
}

Match::Match(Player &firstPlayer, Player &secondPlayer, int firstPlayerScore,
        int secondPlayerScore, const std::string & tourneyName) : Match( firstPlayer, secondPlayer, firstPlayerScore, secondPlayerScore) {
    tourney = tourneyName;
}

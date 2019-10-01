//
// Created by Jakub Kordel on 24.09.19.
//

#include "PlayerLineConverter.h"
#include "Player.h"
#include <cstdlib>
#include <string>
#include "StringsBasicsFunctions.h"

using std::to_string;

PlayerLineConverter::PlayerLineConverter(const std::string &playerLine) {
    separator = ":";
    size_t pos1 ;
    size_t pos2 ;
    line = playerLine;
    std::string workLine = removeSpaces(line);
    const int n = 8;
    std::string substrings[n];
    pos1 = 0;
    pos2 = workLine.find( separator );
    size_t separatorLen = 0;
    for ( int i = 0 ; i < n - 1 ; ++i){
        substrings[i] = workLine.substr(pos1 + separatorLen, pos2 - pos1 - separatorLen );
        pos1 = pos2;
        pos2 = workLine.find( separator, pos1 + 1 );
        separatorLen = 1;
    }
    substrings[n-1] = workLine.substr(pos1 + separatorLen, workLine.length() - pos1 - separatorLen );
    position = (size_t) std::stoi(substrings[0]);
    nick = substrings[1];
    points = std::stoi(substrings[2]);
    wins = std::stoi(substrings[3]);
    ties = std::stoi(substrings[4]);
    loses = std::stoi(substrings[5]);
    topTenWins = std::stoi(substrings[6]);
    if (!substrings[7].empty()) {
        playstyle = substrings[7];
    } else playstyle = "";
}

PlayerLineConverter::PlayerLineConverter(const Player & player) {
    separator = " : ";
    nick = player.getNick();
    points = player.getPoints();
    wins = player.getWins();
    ties = player.getTies();
    loses = player.getLoses();
    topTenWins = player.getTopTenWins();
    position = player.getPosition();
    playstyle = player.getPlaystyle();
    line =  toString(position) + separator + nick + separator + toString(points) + separator + toString(wins) + separator + toString(ties)
            + separator + toString(loses) + separator + toString(topTenWins) + separator + playstyle;
}

std::string PlayerLineConverter::getLine() const {
    return line;
}

std::string PlayerLineConverter::getNick() const {
    return nick;
}

int PlayerLineConverter::getPoints() const {
    return points;
}

int PlayerLineConverter::getWins() const {
    return wins;
}

int PlayerLineConverter::geTies() const {
    return ties;
}

int PlayerLineConverter::getLoses() const {
    return loses;
}

std::string PlayerLineConverter::getPlaystyle() const {
    return playstyle;
}

size_t PlayerLineConverter::getPosition() const {
    return position;
}

int PlayerLineConverter::getTopTenWins() const {
    return topTenWins;
}



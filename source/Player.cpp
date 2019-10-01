//
// Created by Jakub Kordel on 23.09.19.
//

#include "Player.h"

#include <fstream>
#include "PlayersList.h"
#include "PlayerLineConverter.h"

Player::Player(const std::string & gameName) : Player( gameName, 1000 ) {

}

Player::Player(const std::string &gameName, const int &eloPoints) : Player(gameName, eloPoints, 0, 0, 0 ) {

}

Player::Player(const std::string &gameName, const std::string &playersFile) {
    nick = gameName;
    PlayersList list( playersFile );
    std::string line = list.findLine( nick );
    if (line == ""){
        points = 1000;
        wins = 0;
        ties = 0;
        loses = 0;
        position = 0;
        playstyle = "";
        topTenWins = 0;
    } else {
        PlayerLineConverter converter(line);
        points = converter.getPoints();
        wins = converter.getWins();
        ties = converter.geTies();
        loses = converter.getLoses();
        position = converter.getPosition();
        playstyle = converter.getPlaystyle();
        topTenWins = converter.getTopTenWins();
    }
}

Player::Player(const std::string &gameName, const int &eloPoints, const int &w, const int & t, const int & l) {
    changeNick( gameName );
    setPoints( eloPoints );
    setWins(w);
    setTies(t);
    setLoses(l);
    setPosition(0);
    setTopTenWins(0);
    setPlaystyle("");
}

void Player::changeNick(const std::string &newNick) {
    nick = newNick;
}

void Player::setPoints(const int &newElo) {
    points = newElo;
}

std::string Player::getNick() const {
    return nick;
}

int Player::getPoints() const {
    return points;
}

void Player::save(const std::string & fileName) const {
    PlayersList list( fileName );
    list.savePlayer(*this);
}

void Player::setWins( const int & newWins ) {
    wins = newWins;
}

void Player::setTies(const int & newTies ) {
    ties = newTies;
}

void Player::setLoses(const int & newLoses ) {
    loses = newLoses;
}

void Player::addWin() {
    ++wins;
}

void Player::addTie() {
    ++ties;
}

void Player::addLose() {
    ++loses;
}

int Player::getWins() const {
    return wins;
}

int Player::getTies() const {
    return ties;
}

int Player::getLoses() const {
    return loses;
}

size_t Player::getPosition() const {
    return position;
}

void Player::setPosition(const size_t newPosition) {
    position = newPosition;
}

std::string Player::getPlaystyle() const {
    return playstyle;
}

void Player::setPlaystyle(const std::string &newPlaystyle) {
    playstyle = newPlaystyle;
}

int Player::getTopTenWins() const {
    return topTenWins;
}

void Player::setTopTenWins(const int &newTopTenWins) {
    topTenWins = newTopTenWins;
}

void Player::addTopTenWin() {
    ++topTenWins;
}




//
// Created by Jakub Kordel on 24.09.19.
//

#include "PlayersList.h"
#include <fstream>
#include <iostream>
#include "Player.h"
#include "PlayerLineConverter.h"
#include "StringsBasicsFunctions.h"

PlayersList::PlayersList( const std::string & fileName ) {
    playersFile = fileName;
}

bool PlayersList::contains(const std::string &nick) {
    std::ifstream infile;
    infile.open(playersFile, std::ios::in );
    std::string current;
    size_t pos = 0;
    while (infile.good()){
        getline(infile, current);
        current = removeSpaces(current);
        pos = current.find(":");
        if (current.find( ":" + nick + ":" ) == pos && pos != -1 ) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

void PlayersList::savePlayer(const Player &player ) {
    std::ifstream current;
    std::ofstream newFile;
    bool exist = false;
    current.open( playersFile );
    newFile.open("temp.txt");
    std::string line;
    std::string spaced;
    PlayerLineConverter converter(player);
    size_t pos;
    while (current.good()){
        getline(current,spaced);
        if (spaced.empty()) continue;
        line = removeSpaces( spaced );
        pos = line.find( ":");
        if (line.find(":" + player.getNick() + ":") == pos && pos != -1 ){
            newFile << converter.getLine() << std::endl;
            exist = true;
        } else if ( line.find( ":" ) >= 0 ){
            newFile << spaced << std::endl;
        }
    }

    if (!exist){
        newFile << converter.getLine();
    }

    current.close();
    newFile.close();
    std::remove(playersFile.c_str());
    std::rename( "temp.txt", playersFile.c_str());
}

std::string PlayersList::findLine(const std::string &playerNick) {
    std::ifstream file;
    file.open(playersFile);
    std::string line, spaced;
    size_t pos;
    while (file.good()){
        getline(file, spaced);
        line = removeSpaces(spaced);
        pos = line.find(":");
        if ( line.find( ":" + playerNick + ":") == pos && pos != -1 ){
              file.close();
              return spaced;
        }
    }
    file.close();
    return "";
}

void PlayersList::updatePositons(){
    size_t n = countPlayers();
    std::string line;
    size_t counter;
    for ( size_t i = 0; i < n ; ++i ){
        counter = 0;
        std::ifstream file;
        file.open(playersFile);
        for ( size_t j = 0; j < i ; ++j){
            if (line.empty()) --j;
            else {
                getline(file, line);
            }
        }
        getline(file, line);
        PlayerLineConverter info(line);
        file.close();
        Player player(info.getNick(), playersFile);
        file.open(playersFile);
        for (size_t j = 0 ; j < n ; ++j){
            getline(file, line);
            if (line.empty()) --j;
            else {
                PlayerLineConverter converter(line);
                if ( converter.getPoints() > player.getPoints() ){
                    ++counter;
                }
            }
        }
        file.close();
        player.setPosition( counter + 1 );
        player.save(playersFile);
    }
    sort();
}

size_t PlayersList::countPlayers(){
    size_t counter = 0;
    std::ifstream file;
    std::string line;
    file.open(playersFile);
    while (file.good()){
        getline(file, line);
        if ( line.empty()) continue;
        ++counter;
    }
	file.close();
    return counter;
}

void PlayersList::sort(){
    size_t n = countPlayers();
    std::ofstream temp;
    std::ifstream current;
    std::string line;
    temp.open("temp.txt");
    for (size_t i = 1; i < n + 1 ; ++i){
        current.open(playersFile);
        while (current.good()){
            getline(current, line);
            if ( !line.empty() ){
                PlayerLineConverter converter(line);
                if ( converter.getPosition() == i ){
                    temp << line << std::endl;
                }
            }
        }
        current.close();
    }
    temp.close();
    std::remove(playersFile.c_str());
    std::rename( "temp.txt", playersFile.c_str());
}





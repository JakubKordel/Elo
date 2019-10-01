//
// Created by Jakub Kordel on 25.09.19.
//

#ifndef ELO_MENU_H
#define ELO_MENU_H

#include <string>

void printMainMenu();
void options();
void reportScore();
void reportScoresFromBuilder();
void rebuildFromBackup();
bool printNewPlayers(const std::string & file1, const std::string &file2 ); //prints all players from file2 not contained in file1. false if nothing was printed
void clearWindow();
void addTourneyNotes(const std::string & buildFile, const std::string & tourney);
void reverseBuilder();
void clearBuf();
void changeName();



#endif //ELO_MENU_H

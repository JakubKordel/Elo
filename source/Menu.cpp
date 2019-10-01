//
// Created by Jakub Kordel on 25.09.19.
//

#include "Menu.h"
#include <iostream>
#include "Match.h"
#include "FilesFunctions.h"
#include "Player.h"
#include "HistoryBuilder.h"
#include "PlayersList.h"
#include "MatchLineConverter.h"
#include <limits>
#include <exception>
#include "BuilderReader.h"
#include <fstream>
#include "PlayerLineConverter.h"
#include "StringsBasicsFunctions.h"

const std::string playersList = "Players.txt";
const std::string backup = "Backup.txt";
const std::string customHistory = "History.txt";
const std::string builder = "Builder.txt";

void printMainMenu() {
	clearWindow();
	//clearBuf();
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "                           E L O                           " << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Report one score" << std::endl;
    std::cout << "2. Report all matches contained in Builder.txt" << std::endl;
    std::cout << "3. Reverse Builder.txt" << std::endl;
    std::cout << "4. Change player's name " << std::endl;
    std::cout << "5. Build from scratch using Backup.txt" << std::endl;
    std::cout << "q Quit" << std::endl << std::endl;
	std::cout << "Your choice: " << std::endl;
}

void options() {
    std::string choice = "";
    while ( choice.compare("q") != 0 ){
        printMainMenu();
        std::cin >> choice;
        if (choice.compare("1") == 0 ){
            reportScore();
        } else if (choice.compare("2") == 0 ){
            reportScoresFromBuilder();
        }else if (choice.compare("3") == 0 ){
			reverseBuilder();
		}
		else if (choice.compare("4") == 0) {
			changeName();
		}else if (choice.compare("5") == 0) {
			rebuildFromBackup();
        }
    }
}

void reportScore() {
	clearWindow();
	clearBuf();
    std::string p1;
    std::string p2;
    int scr1;
    int scr2;
    std::string tourney;
    std::cout << "Player1: ";
    std::cin >> p1;
    std::cout << "Player2: ";
    std::cin >> p2;
    std::cout << "Score1: ";
    while (!(std::cin >> scr1)){
        std::cout << "Must be a number: ";
        std::cin.clear();
        std::cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    };
    std::cout << "Score2: ";
    while(!(std::cin >> scr2)){
        std::cout << "Must be a number: ";
        std::cin.clear();
        std::cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    }
    std::cout << "Tournament: ";
    std::cin >> tourney;

    Player player1(p1, playersList );
    Player player2(p2, playersList );
    Match match(player1, player2, scr1, scr2, tourney);

    PlayersList list(playersList);
    std::string choice;
    if (!list.contains(p1) && !list.contains(p2)) {
        std::cout << std::endl << "New players " << p1 << " and " << p2 << " will be added!";
    } else if (!list.contains(p1)){
        std::cout << std::endl << "New player " << p1 << " will be added!";
    } else if (!list.contains(p2)){
        std::cout << std::endl << "New player " << p2 << " will be added!";
    }
    std::cout << std::endl << "Following match will be added: " << p1 << " " << scr1 << " - " << scr2 << " " << p2;

    std::cout << std::endl << "Do you accept? ( Y or N ): ";
    while (choice != "y" && choice != "Y" &&  choice != "n" && choice != "N")
        std::cin >> choice;
    if (choice == "y" || choice == "Y") match.report(playersList, customHistory, backup );
}

void reportScoresFromBuilder() {
	clearWindow();
	clearBuf();
    std::string testPlayers = "test.txt";
    std::string choice;
    std::string tourney;
    std::cout << "Tournament name for this build: ";
    std::cin >> tourney;

    bool build = true;
    try {
        BuilderReader(builder, testPlayers);
        std::cout << std::endl << "Following new players will be added: " << std::endl;
        if ( printNewPlayers(playersList, testPlayers) ){
            std::remove(testPlayers.c_str());
            build = false;
            std::cout << std::endl << "Do you accept? ( Y or N ): ";
            while (choice != "y" && choice != "Y" &&  choice != "n" && choice != "N")
                std::cin >> choice;
            if (choice == "y" || choice == "Y") build = true;
        } else {
            std::remove(testPlayers.c_str());
            std::cout << "NONE" <<std::endl;

        }

        if ( build ) {
            addTourneyNotes(builder, tourney );
            HistoryBuilder(builder, backup, playersList, customHistory);
            std::ofstream o;
            o.open(builder);
            o.close();
            std::cout << std::endl <<"SUCCESS" << std::endl;
            getchar();
        }
    }
    catch (std::exception & e ) {
        std::remove(testPlayers.c_str());
        std::cout <<std::endl << "WRONG BUILDER" << std::endl;
    }
}

void rebuildFromBackup() {
	clearWindow();
	clearBuf();
	std::cout << "Building . . . ";
    std::string testPlayers = "$test.txt";
    std::string playersListNew = "$PlayersNew.txt";
    std::string backupNew = "$BackupNew.txt";
    std::string customHistoryNew = "$HistoryNew.txt";
    try {
        BuilderReader(builder, testPlayers);
        removePlayersHistories(playersList);
        HistoryBuilder(backup, backupNew, playersListNew, customHistoryNew);
        std::remove(testPlayers.c_str());
        std::remove(backup.c_str());
        std::remove(playersList.c_str());
        std::remove(customHistory.c_str());
        std::rename(playersListNew.c_str(), playersList.c_str());
        std::rename(backupNew.c_str(), backup.c_str());
        std::rename(customHistoryNew.c_str(), customHistory.c_str());
		clearWindow();
		std::cout << std::endl << "SUCCESS" << std::endl << "Press enter" << std::endl;
		getchar();
    } catch (std::exception & e ) {
        std::remove(testPlayers.c_str());
        std::cout <<std::endl << "WRONG BACKUP FILE" << std::endl;
		std::cout << "Press enter" << std::endl;
		getchar();
    }
}

bool printNewPlayers(const std::string & file1, const std::string &file2 ){
    PlayersList list1(file1);
    std::ifstream inFile;
    inFile.open(file2);
    std::string line;
    bool printed = false;
    while (inFile.good()){
        getline(inFile, line);
        if (line.empty() || line == "") continue;
        PlayerLineConverter converter(line);
        if (!list1.contains(converter.getNick())) {
            std::cout << converter.getNick() << std::endl ;
            if (!printed) printed = true;
        }
    }
    inFile.close();
    return printed;
}

void clearWindow(){
	system("clear");
}

void addTourneyNotes(const std::string & buildFile, const std::string & tourney ){
    std::ifstream current;
    std::ofstream newFile;
    current.open( buildFile );
    newFile.open("$temp.txt");
    std::string line;
    while (current.good()){
        getline(current, line);
        newFile << line;
        if (isGood(line) && colonsNum(line) != 4 && line.find("$:") == -1) {
            newFile <<" $: " << tourney;
		}
		else if (colonsNum(line) == 3) {
			newFile << " : " << tourney;
		}
        newFile << std::endl;
    }
    current.close();
    newFile.close();
    std::remove(buildFile.c_str());
    std::rename( "$temp.txt", buildFile.c_str() );
}

void reverseBuilder() {
	clearWindow();
	clearBuf();
	reverseFileOrder(builder);
	std::cout << "Reversed Builder.txt lines order!" << std::endl;
	getchar();
}

void clearBuf() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
}

void changeName() {
	clearWindow();
	clearBuf();
	PlayersList list(playersList);
	std::string oldName;
	std::string newName;
	std::cout << "Current name: ";
	std::cin >> oldName;
	if (list.contains(oldName) && !list.contains(newName)) {
		std::cout << "New name: ";
		std::cin >> newName;
		try {
			changePlayerName(oldName, newName, backup, playersList);
			clearWindow();
			std::cout << "Succesfully changed player's name" << std::endl << "Enter" << std::endl;
			clearBuf();
			getchar();
		}
		catch (std::exception & e) {
			clearWindow();
			std::cout << "WARNING: Something gone wrong while changing player's name" << std::endl << "Enter" << std::endl;
			clearBuf();
			getchar();
		}
	}
	else {
		clearWindow();
		if (!list.contains(oldName)) std::cout << "Player " << oldName << " not exist " << std::endl << "Enter" << std::endl;
		else std::cout << "Player " << newName << " already exist! " << std::endl << "Enter" << std::endl;
		clearBuf();
		getchar();
	}
}

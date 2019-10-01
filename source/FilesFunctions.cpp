//
// Created by Jakub Kordel on 26.09.19.
//

#include "FilesFunctions.h"
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

void removePlayersHistories(const std::string& playersFile) {
	std::ifstream inFile;
	inFile.open(playersFile);
	std::string line;
	std::string filePath;
	while (inFile.good()) {
		getline(inFile, line);
		if (line.empty() || line == "") continue;
		PlayerLineConverter converter(line);
		filePath = "PlayersHistory/" + converter.getNick() + ".txt";
		std::remove(filePath.c_str());
	}
	inFile.close();
}

void reverseFileOrder(const std::string& file) {
	size_t counter = countLines(file);
	std::ofstream copy;
	std::string line;
	std::ifstream inFile;
	copy.open("$copy.txt");
	for (size_t i = 0; i < counter; ++i) {
		inFile.open(file);
		for (size_t j = 0; j < counter - i; ++j) {
			getline(inFile, line );
			if (line.empty()) line = "";
		}
		copy << line << std::endl;
		inFile.close();
	}
	copy.close();
	std::remove(file.c_str());
	std::rename("$copy.txt", file.c_str());
}

size_t countLines(const std::string& file) {
	size_t counter = 0;
	std::ifstream f;
	std::string line;
	f.open(file);
	while (f.good()) {
		getline(f, line);
		++counter;
	}
	f.close();
	return counter;
}

void changePlayerName(const std::string& name1, const std::string & name2, const std::string& backupFile, const std::string& playersFile ) {
	std::ofstream copy;
	std::ifstream orginal;
	std::string line;
	orginal.open(backupFile);
	copy.open("$backupCopy.txt");
	while (orginal.good()) {
		getline(orginal, line);
		if (!isGood(line)) {
			if (!line.empty()) copy << line << std::endl;
			continue;
		}
		MatchLineConverter matchConv(line, playersFile);
		if (matchConv.p1 ->getNick() == name1) {
			Player player(name1, playersFile);
			player.changeNick(name2);
			Match newMatch(player, *(matchConv.p2), matchConv.getMatch()->scr1, matchConv.getMatch() ->scr2, matchConv.getMatch() ->tourney );
			MatchLineConverter converter(newMatch);
			line = converter.getLine();
		}
		if (matchConv.p2->getNick() == name1) {
			Player player(name1, playersFile);
			player.changeNick(name2);
			Match newMatch(*(matchConv.p1), player , matchConv.getMatch()->scr1, matchConv.getMatch()->scr2, matchConv.getMatch()->tourney);
			MatchLineConverter converter(newMatch);
			line = converter.getLine();
		}
		copy << line << std::endl;
	}
	copy.close();
	orginal.close();
	std::remove(backupFile.c_str());
	std::rename("$backupCopy.txt", backupFile.c_str());

	Player player(name1, playersFile);
	player.changeNick(name2);
	PlayerLineConverter converter(player);

	orginal.open(playersFile);
	copy.open("$playersCopy.txt");
	while (orginal.good()) {
		getline(orginal, line);
		if (line.empty()) continue;
		PlayerLineConverter temp(line);
		if (temp.getNick() == name1) {
			line = converter.getLine();
		}
		copy << line << std::endl;
	}
	copy.close();
	orginal.close();
	std::remove(playersFile.c_str());
	std::rename("$playersCopy.txt", playersFile.c_str());
	line = "PlayersHistory/" + name1 + ".txt";
	std::string newPath = "PlayersHistory/" + name2 + ".txt";
	std::rename(line.c_str() , newPath.c_str());
}


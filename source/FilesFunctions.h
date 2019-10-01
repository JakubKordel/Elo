//
// Created by Jakub Kordel on 26.09.19.
//

#ifndef ELO_FILESFUNCTIONS_H
#define ELO_FILESFUNCTIONS_H

#include <string>
void removePlayersHistories(const std::string& playersFile);
void reverseFileOrder(const std::string& file);
size_t countLines(const std::string& file);
void changePlayerName(const std::string & name1, const std::string & name2, const std::string& backupFile, const std::string & playersFile);

#endif //ELO_FILESFUNCTIONS_H

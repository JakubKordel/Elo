//
// Created by Jakub Kordel on 25.09.19.
//

#ifndef ELO_HISTORYBUILDER_H
#define ELO_HISTORYBUILDER_H

#include <string>

class HistoryBuilder {
public:
    HistoryBuilder(const std::string & inputFile, const std::string & outputFile, const std::string  & playersFile, const std::string & customHistoryFile );
};


#endif //ELO_HISTORYBUILDER_H

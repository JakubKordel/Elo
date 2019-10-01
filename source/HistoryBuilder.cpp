//
// Created by Jakub Kordel on 25.09.19.
//

#include "HistoryBuilder.h"
#include <fstream>
#include "MatchLineConverter.h"
#include "Match.h"
#include "StringsBasicsFunctions.h"



HistoryBuilder::HistoryBuilder(const std::string &inputFile, const std::string &outputFile, const std::string & playersFile,
                               const std::string &customHistoryFile) {
    std::ifstream inFile;
    inFile.open(inputFile);
    std::string line;
    while (inFile.good()){
        getline(inFile, line);
        if (!isGood(line)) continue;
        MatchLineConverter converter(line, playersFile );
        converter.getMatch() ->report(playersFile, customHistoryFile, outputFile );
    }
    inFile.close();
}

//
// Created by Jakub Kordel on 26.09.19.
//

#include <fstream>
#include "MatchLineConverter.h"
#include "Match.h"
#include "StringsBasicsFunctions.h"
#include "BuilderReader.h"
#include <exception>
#include "Player.h"

BuilderReader::BuilderReader(const std::string &inputFile, const std::string &testPlayersFile ) {
    std::ifstream inFile;
    inFile.open(inputFile);
    std::string line;
    while (inFile.good()){
        getline(inFile, line);
        if (!isGood(line)) continue;
        try{
            MatchLineConverter converter(line, testPlayersFile);
            converter.p1 ->save(testPlayersFile);
            converter.p2 ->save(testPlayersFile);
        } catch(std::exception & e) {
            inFile.close();
            throw e;
        }
    }
    inFile.close();
}

//
// Created by Jakub Kordel on 25.09.19.
//

#include "StringsBasicsFunctions.h"
#include <algorithm>

std::string removeSpaces(std::string str){
    str.erase(std::remove(str.begin(), str.end() , ' '), str.end());
    return str;
}

size_t colonsNum(std::string line){
    size_t counter = 0 ;
    size_t pos = 0;
    pos = line.find(":", pos);
    while (pos != -1 ){
        ++pos;
        pos = line.find(":", pos);
        ++counter;
    }
    return counter;
}

size_t hyphensNum(std::string line){
    size_t counter = 0 ;
    size_t pos = 0;
    pos = line.find("-", pos);
    while (pos != -1 ){
        ++pos;
        pos = line.find("-", pos);
        ++counter;
    }
    return counter;

}

bool isGood(std::string line ){
    if (line.empty()) return false;
    if (hyphensNum(line) > 1) return false;
    if (colonsNum(line) == 4 ) return true;
    line = removeSpaces(line);
    if (line.find("Reporteda0-0tiefor") != -1 ) return false;
    if (line.find("Reporteda" ) != -1 && line.find("-") != -1 && (line.find("winfor") != -1 || line.find("tiefor") != -1) && (line.find("over") != -1 || line.find("vs.") != -1) )
        return true;

    return false;
}

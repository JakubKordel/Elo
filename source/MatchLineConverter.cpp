//
// Created by Jakub Kordel on 25.09.19.
//


#include "MatchLineConverter.h"
#include "StringsBasicsFunctions.h"
#include "Player.h"
#include <iostream>

MatchLineConverter::~MatchLineConverter() {
    delete match;
    delete p1;
    delete p2;
}

MatchLineConverter::MatchLineConverter(const std::string & matchLine, const std::string & playersList ) {
    std::string separator = ":";
    line = matchLine;
    size_t pos1 ;
    size_t pos2 ;
    std::string workLine = removeSpaces(line);
    const int n = 5;
    std::string substrings[n];
    if (colonsNum(workLine) == 4 ) {
        pos1 = 0;
        pos2 = workLine.find( separator );
        size_t separatorLen = 0;
        for (int i = 0; i < n - 1; ++i) {
            substrings[i] = workLine.substr(pos1 + separatorLen, pos2 - pos1 - separatorLen);
            pos1 = pos2;
            pos2 = workLine.find(separator, pos1 + 1);
            separatorLen = 1;
        }
        substrings[n - 1] = workLine.substr(pos1 + separatorLen, workLine.length() - pos1 - separatorLen);
        if (substrings[4].empty()) substrings[4] = "";
        p1 = new Player(substrings[0], playersList );
        p2 = new Player(substrings[1], playersList );
        match = new Match( *p1, *p2 , std::stoi(substrings[2]), std::stoi(substrings[3]), substrings[4] );
    }
    else{
        pos1 = workLine.find("Reporteda") + 9;
        pos2 = workLine.find("-");
        substrings[0] = workLine.substr(pos1, pos2 - pos1 );
        pos1 = workLine.find("-") + 1;
        pos2 = workLine.find("winfor");
        if (pos2 == -1) pos2 = workLine.find("tiefor");
        substrings[1] = workLine.substr(pos1, pos2 - pos1 );
        pos1 = workLine.find("winfor") + 6;
        if (pos1 == (-1 + 6)) pos1 = workLine.find("tiefor") + 6;
        pos2 = workLine.find("over");
        if (pos2 == -1) pos2 = workLine.find("vs.");
        substrings[2] = workLine.substr(pos1, pos2 - pos1 );
        pos1 = workLine.find("over") + 4;
        if (pos1 == (-1 + 4)) pos1 = workLine.find("vs.") + 3;
        pos2 = workLine.find("$:", pos1);
        if (workLine.find("$:", pos1) != -1 ) {
            substrings[3] = workLine.substr(pos1, pos2 - pos1);
            pos1 = pos2 + 2;
            substrings[4] = workLine.substr(pos1);
        } else {
            substrings[3] = workLine.substr(pos1);
            substrings[4] = "";
        }
        p1 = new Player(substrings[2], playersList );
        p2 = new Player(substrings[3], playersList );
        int scr1 = std::stoi(substrings[0]);
        int scr2 = std::stoi(substrings[1]);
        if (scr1 > scr2)
            match = new Match( *p1, *p2 , scr1, scr2, substrings[4] );
        else match = new Match( *p1, *p2 , scr2, scr1, substrings[4] );
        MatchLineConverter c(*match);
        line = c.getLine();
    }

}

MatchLineConverter::MatchLineConverter(const Match &m) {
    p1 = nullptr;
    p2 = nullptr;
    std::string sep = " : ";
    match = new Match( m.player1, m.player2, m.scr1, m.scr2, m.tourney );
    line = m.player1.getNick() + sep + m.player2.getNick() + sep + toString(m.scr1) + sep + toString(m.scr2) + sep + m.tourney;
}

std::string MatchLineConverter::getLine() const {
    return line;
}

Match *MatchLineConverter::getMatch() const {
    return match;
}

//
// Created by Jakub Kordel on 25.09.19.
//

#ifndef ELO_STRINGSBASICSFUNCTIONS_H
#define ELO_STRINGSBASICSFUNCTIONS_H
#include <string>
#include <sstream>

std::string removeSpaces(std::string str);
size_t colonsNum(std::string line);
size_t hyphensNum(std::string line);
bool isGood(std::string line);

template <typename T>
std::string toString(const T& value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

#endif //ELO_STRINGSBASICSFUNCTIONS_H

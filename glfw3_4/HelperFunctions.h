#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include<string>

class Helper {
public:
	static std::string GetNameOnly(const std::string fullName) {
		//add extract the string before the position of "."
		return fullName.substr(0, fullName.find('.'));
	}
};

#endif
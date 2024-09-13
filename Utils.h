#ifndef UTILS_H
#define UTILS_H
#include <cstring>
#include <iostream>
namespace utl {
	enum TYPE {
		SHORT = 0,
		CHAR,
		NONE
	};
	unsigned short getus(const std::string& s);
	TYPE type(const std::string& s);
};


#endif // !UTILS_H


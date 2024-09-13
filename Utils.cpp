#include "Utils.h"
#include <string>
#include <stdexcept>
#include <cstdlib>
unsigned short utl::getus(const std::string& s)
{
    return static_cast<unsigned short>(std::stoul(s));
}

utl::TYPE utl::type(const std::string& s)
{
    if (isalpha(s[0]) && s.size() < 1) {
        return TYPE::CHAR;
    }
    else if ((s.size() < 1 && isdigit(s[0])) ||
        (s.size() < 2 && (isdigit(s[0]) && isdigit(s[1])))) {
        return TYPE::SHORT;
    }
    return TYPE::NONE;
}



#pragma once

#include <iostream>

class Cmd {
public:
    std::string id;
    std::string s;
    std::string l;
    std::string usage;
    std::string params;
    friend std::ostream& operator<<(std::ostream& os, const Cmd& cmd);
};

inline std::ostream& operator<<(std::ostream& os, const Cmd& cmd)
{
    os << cmd.s << "," << cmd.l;
    if (cmd.params != "") {
        os << " " << cmd.params;
    }
    os << "\t" << cmd.usage;
    return os;
}

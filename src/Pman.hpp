#pragma once

#include <vector>
#include <string>

class Pman
{
public:
    Pman(const int argc, const char** argv);

    bool has_subcommand() const { return m_has_subcommand; }
    bool has_args() const { return m_has_args; }
private:
    bool m_has_subcommand;
    bool m_has_args;
    std::string m_subcommand;
    std::vector<std::string> m_args;
};

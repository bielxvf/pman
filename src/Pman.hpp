#pragma once

#include <vector>
#include <string>

#include "Cmd.hpp"

class Pman
{
public:
    Pman(int argc, char** argv);

    int exec();

private:
    bool has_subcommand() const { return m_has_subcommand; }
    bool has_args() const { return m_has_args; }
    bool subcommand_is(std::string id) const;
    void print_subcommand() const;
    void print_args() const;
    void parse();
    int subcmd_help();
    int subcmd_list();
    int m_argc;
    char** m_argv;
    bool m_has_subcommand;
    bool m_has_args;
    std::string m_subcommand;
    std::vector<std::string> m_args;
    std::vector<Cmd> m_cmds;
};

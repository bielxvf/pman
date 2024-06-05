#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include "Cmd.hpp"

class Pman
{
public:
    Pman(int argc, char** argv);

    int exec();

private:
    bool has_subcmd() const { return m_has_subcmd; }
    bool has_args() const { return m_has_args; }
    bool subcommand_is(std::string id) const;
    void print_subcmd() const;
    void print_args() const;
    void parse();
    int subcmd_help();
    int subcmd_list();

    int m_argc;
    char** m_argv;

    std::filesystem::path m_HOME;
    std::filesystem::path m_config_path;
    std::filesystem::path m_passwords_path;

    bool m_has_subcmd;
    bool m_has_args;

    std::string m_subcmd_id;
    std::vector<std::string> m_args;
    std::vector<Cmd> m_cmds;
};

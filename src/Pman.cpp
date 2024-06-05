#include "Pman.hpp"

#include <iostream>

Pman::Pman(int argc, char** argv)
{
    m_cmds.push_back(Cmd { .id = "help", .s = "h", .l = "help", .usage = "Print help message", .params = "" });
    m_cmds.push_back(Cmd { .id = "list", .s = "l", .l = "list", .usage = "List passwords", .params = "" });
    
    m_argc = argc;
    m_argv = argv;
    m_has_subcommand = false;
    m_has_args = false;
    if (m_argc == 1) {
        m_has_subcommand = false;
    }

    if (m_argc > 1) {
        m_has_subcommand = true;
    }
    
    if (m_argc > 2) {
        m_has_args = true;
    }
}

void Pman::parse()
{
    m_subcommand = "";
    if (Pman::has_subcommand()) {
        for (Cmd cmd : m_cmds) {
            if (m_argv[1] == cmd.s || m_argv[1] == cmd.l) {
                m_subcommand = cmd.id;
            }
        }
        if (m_subcommand == "") {
            m_has_subcommand = false;
        }
    }

    if (Pman::has_args()) {
        for (int i = 2; i < m_argc; i++) {
            m_args.push_back(m_argv[i]);
        }
    }
}

void Pman::print_subcommand() const
{
    if (Pman::has_subcommand()) {
        std::cerr << "Subcommand: " << m_subcommand << std::endl;
    }
}

void Pman::print_args() const
{
    if (Pman::has_args()) {
        std::cerr << "Args: ";
        for (std::string arg : m_args) {
            std::cerr << arg << " ";
        }
        std::cerr << std::endl;
    }
}

bool Pman::subcommand_is(std::string id) const
{
    return m_subcommand == id;
}

int Pman::subcmd_help()
{
    std::cerr << "Usage:" << std::endl;
    for (auto subcmd : m_cmds) {
        std::cerr << "\t" << subcmd << std::endl;
    }

    return 1;
}

int Pman::subcmd_list()
{
    // TODO: List ~/.config/pman/passwords
    // Might need to get env variables on the constructor
    return 0;
}

int Pman::exec()
{
    Pman::parse();

    if (!Pman::has_subcommand()) {
        std::cerr << "Error: No valid subcommand provided" << std::endl;
        return Pman::subcmd_help();
    }

    if (Pman::subcommand_is("help")) {
        Pman::subcmd_help();
        return 0;
    } else if (Pman::subcommand_is("list")) {
        return Pman::subcmd_list();
    }
    
    return 0;
}

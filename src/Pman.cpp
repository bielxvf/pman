#include "Pman.hpp"

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <exception>

#include "print_err.hpp"

Pman::Pman(int argc, char** argv)
{
    m_cmds.push_back(Cmd { .id = "help", .s = "h", .l = "help", .usage = "Print help message", .params = "" });
    m_cmds.push_back(Cmd { .id = "list", .s = "l", .l = "list", .usage = "List passwords", .params = "" });

    char* HOME = std::getenv("HOME");
    if (HOME == nullptr) {
        print_err("HOME environment variable not set");
        std::terminate();
    }

    m_HOME = HOME != nullptr ? std::filesystem::path(HOME) : std::filesystem::path("");

    m_config_path = m_HOME;
    m_config_path /= ".config";
    m_config_path /= m_program_name;
    
    m_passwords_path = m_config_path;
    m_passwords_path /= "passwords";

    Pman::mkconfig();
    
    m_argc = argc;
    m_argv = argv;
    m_has_subcmd = false;
    m_has_args = false;

    if (m_argc == 1) {
        m_has_subcmd = false;
    }

    if (m_argc > 1) {
        m_has_subcmd = true;
    }

    if (m_argc > 2) {
        m_has_args = true;
    }
}

void Pman::parse()
{
    m_subcmd_id = "";
    if (Pman::has_subcmd()) {
        for (Cmd cmd : m_cmds) {
            if (m_argv[1] == cmd.s || m_argv[1] == cmd.l) {
                m_subcmd_id = cmd.id;
            }
        }
        if (m_subcmd_id == "") {
            m_has_subcmd = false;
        }
    }

    if (Pman::has_args()) {
        for (int i = 2; i < m_argc; i++) {
            m_args.push_back(m_argv[i]);
        }
    }
}

void Pman::print_subcmd() const
{
    if (Pman::has_subcmd()) {
        std::cerr << "Subcommand: " << m_subcmd_id << std::endl;
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
    return m_subcmd_id == id;
}

void Pman::mkconfig() const
{
    if (!std::filesystem::exists(m_HOME)) {
        print_err("Home directory not found, creating");
        std::filesystem::create_directory(m_config_path);
    }

    if (!std::filesystem::exists(m_config_path)) {
        print_err("Config directory not found, creating");
        std::filesystem::create_directory(m_config_path);
    }

    if (!std::filesystem::exists(m_passwords_path)) {
        print_err("Passwords directory not found, creating");
        std::filesystem::create_directory(m_passwords_path);
    }
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
    std::cout << "Listing directory " << m_passwords_path.generic_string() << ": " << std::endl;
    std::filesystem::directory_iterator dir(m_passwords_path);
    for (auto const& entry : dir) {
        std::cout << entry.path() << std::endl;
    }
    
    return 0;
}

int Pman::exec()
{
    Pman::parse();

    if (!Pman::has_subcmd()) {
        print_err("No valid subcommand provided");
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

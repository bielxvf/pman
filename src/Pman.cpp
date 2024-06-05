#include "Pman.hpp"

Pman::Pman(const int argc, const char** argv)
{
    if (argc == 1) {
        m_has_subcommand = false;
    } else if (argc > 1) {
        m_has_subcommand = true;
    } else if (argc > 2) {
        m_has_args = true;
    }
}

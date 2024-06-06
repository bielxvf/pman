#include <string>
#include <iostream>

const std::string red = "\033[1;31m";
const std::string reset = "\033[0m";
const std::string underline = "\033[4m";

void print_err(std::string err)
{
    std::cerr << red << underline << "ERROR" << reset << red << ": " << reset;
    std::cerr << err << std::endl;
}

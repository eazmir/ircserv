#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>

#include <iomanip>
#include <sstream>
#include <iostream>

std::string center(const std::string &s, int W)
{
    int pad = W - (int)s.size();
    int left = pad / 2;
    int right = pad - left;
    return std::string(left, ' ') + s + std::string(right, ' ');
}

void sendHelp()
{
    const int W = 62;
    std::string eq(W, '_');
    std::string dash(W, '_');
    std::stringstream os;
    os << std::left;

    os << "+" << eq   << "+\r\n";
    os << "|" << center("Welcome to Our IRC Server!", W)                        << "|\r\n";
    os << "+" << dash  << "+\r\n";
    os << "|" << center("You connected successfully!", W)                       << "|\r\n";
    os << "|" << center("Complete your registration using the commands below.", W) << "|\r\n";
    os << "+" << eq   << "+\r\n";
    os << "|" << center("AVAILABLE COMMANDS", W)                                << "|\r\n";
    os << "+" << dash  << "+\r\n";
    os << "|  " << std::setw(14) << "nickname"    << ": " << std::setw(W - 18) << "/nick <nickname>"                     << "|\r\n";
    os << "|  " << std::setw(14) << "username"    << ": " << std::setw(W - 18) << "/user <username> <*> <0> :<realname>" << "|\r\n";
    os << "+" << eq   << "+\r\n";
    std::string str = os.str();
    std::cout << str << std::endl;
}

int main(void)
{
   sendHelp();
}
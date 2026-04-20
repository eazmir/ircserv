#include "server.hpp"
#include <iomanip>

class Utils 
{
public:
    static std::string strTrim(const std::string &str);
    static void printClientsInfo(const std::map<int, client> &clients);
    static int validatePort(const std::string &port);
    static int check_port(const std::string &port);
};
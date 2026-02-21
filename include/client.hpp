#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "server.hpp"

// Forward declaration
struct client; // forward declaration

class managerchannel
{
    private:
        std::map<int, client> &_clients;
        authentication auth;
    public:
        managerchannel(std::map<int, client> &clients,const std::string &pass);
        void handle_input(const std::string &input, client &c);
};
#endif

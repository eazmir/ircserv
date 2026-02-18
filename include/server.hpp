/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:09:01 by eazmir            #+#    #+#             */
/*   Updated: 2026/02/18 11:39:18 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <poll.h>
#include <vector>
#include <algorithm>
#include <string>
///////////////////////////////////////////////////////////
#define BUFFER_SIZE 1024
#define MAX_CLIENT 1000
///////////////////////////////////////////////////////////
struct  client
{
    std::string buffer;
    int     fd;
    int     status;
    bool    pass_ok;
    bool    user_ok;
    bool    regestred;
};
//////////////////////////////////////////////////////////
class  server
{
    private:
        int _port;
        int _fd_server;
        size_t _nfds;
        size_t _index;
        ///////////////////////////////////////////////////
        std::string _password;
        std::vector<client> _client;
        ///////////////////////////////////////////////////
        struct sockaddr_in _addr;
        struct pollfd _fds[1024];
    public:
        server();
        server(int port,std::string password);
        ///////////////////////////////////////////////////
        void handleEvent(void);
        void start_listning(void);
        void setup_address(void);
        void bind_socket(void);
        void create_socket(void);
        void setup_poll(void);
        void init(void);
        void accept_connection(void);
        void recv_data(void);
};
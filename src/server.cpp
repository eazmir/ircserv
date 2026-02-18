/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eazmir <eazmir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:09:17 by eazmir            #+#    #+#             */
/*   Updated: 2026/02/18 11:37:31 by eazmir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

server::server()
{
    this->_password.clear();
    this->_port = 0;
}

void server::setup_address()
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(_port);
}

void server::create_socket()
{
    this->_fd_server = socket(AF_INET, SOCK_STREAM, 0);
}

void server::start_listning()
{
    listen(this->_fd_server,10);
}

void server::bind_socket()
{
    bind(this->_fd_server,(struct sockaddr*)&_addr,sizeof(_addr));
}

void server::setup_poll()
{
    this->_fds[0].fd = this->_fd_server;
    this->_fds[0].events = POLLIN;
    this->_nfds = 1;
}

void server::init()
{
    this->setup_address();
    this->create_socket();
    this->bind_socket();
    this->start_listning();
    this->setup_poll();
}

server::server(int port,std::string password):_port(port),_password(password)
{
    this->init();
    this->handleEvent();
}

void server::handleEvent()
{
    while (true)
    {
        poll(_fds,_nfds,-1);
        for (size_t _index = 0; _index < _nfds;_index++)
        {
            if (this->_fds[_index].revents & POLLIN)
            {
                if (this->_fd_server == this->_fds[_index].fd)
                    this->accept_connection();
                else
                    this->recv_data();
            }
        }
    }
}

void server::accept_connection()
{
    client  _clnt;
    int     _clnt_;

    _clnt_ = accept(_fd_server,NULL,NULL);
    _fds[_nfds].fd = _clnt_;
    _fds[_nfds].events = POLLIN;
    _nfds++;
    std::cout << "New client connected. FD: " << _clnt_ << std::endl;
    ////////////////////////////////////////////////////////////////
    _clnt.fd = _clnt_;
    _clnt.pass_ok = false;
    _clnt.user_ok = false;
    _clnt.regestred = false;
    _client.push_back(_clnt);
}

void server::recv_data()
{
    client  _clnt;
    int     byte;
    char    buffer[1024];
    
    byte = recv(_client[_index].fd,buffer,sizeof(buffer),0);
    std::cout<<"\n";
    std::cout<<"message from: "<<_client[_index].fd;
    _clnt.buffer = buffer;
    _client.push_back(_clnt);
}
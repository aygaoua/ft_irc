#ifndef JOIN_HPP
#define JOIN_HPP

#include<iostream>
#include<string>
#include<vector>

#include "server.hpp"
#include "client.hpp"


class Client;
class Server;

void JoinConstruction(std::vector<std::string> command, int clientFd);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:21 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/29 11:10:57 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

Server::Server()
{
	
}
void	Server::config_server(int port_nbr,std::string str)
{
	this->port = port_nbr;
	this->pass = str;
	
	struct sockaddr_in server_addr;
	
	this->fd_s_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_s_socket == -1)
		throw "socker creation error";
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd_s_socket, (struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
		throw "Binding error";
	if (listen(fd_s_socket,SOMAXCONN) == -1)
		throw "listening error";
}

void	Server::acceptconnection()
{
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	this->fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
	if (fd_c_socket == -1)
		throw "Accept error";
}

void Server::receivemessage()
{
	int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, 0);

	if (bytes_read <= 0)
		throw ("Connection closed by client");
	buffer[bytes_read] = '\0';
	std::cout << "Client: " << buffer << std::endl;
	
	//--------------- UPDATE -----------------
	// int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, MSG_DONTWAIT); // Use MSG_DONTWAIT to make recv non-blocking
	// if (bytes_read > 0) {
    //         buffer[bytes_read] = '\0';
    //         std::cout << "Client: " << buffer << std::endl;
    //     } else if (bytes_read == 0) {
    //         throw "Connection closed by client";
    //     }
}
void	Server::sendmessage(char *message)
{
	if (send(fd_c_socket, message, strlen(message), 0) == -1) {
		throw "Send error";
	}
	
	//--------------- UPDATE -----------------
	// if (send(fd_c_socket, message, strlen(message), MSG_DONTWAIT) == -1) {
	// 	throw "Send error";
	// }
}

Server::~Server()
{
}
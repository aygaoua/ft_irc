/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:04:57 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/04/27 16:44:32 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"


//---------------------------

// const int BUFFER_SIZE = 1024;

void check_arg(char **argv) {
    std::string portstr(argv[1]);
    size_t portPos = portstr.find_first_not_of("0123456789");
    if (portPos != std::string::npos) {
        throw std::invalid_argument("Error: Invalid characters in port");
    }
    int port;
    std::stringstream portstream(portstr);
    portstream >> port;
    // if (portstream.fail()) {
    //     throw std::invalid_argument("Error: Failed to convert port to integer");
    // }
    if (port < 1024 || port > 65535) {
        throw std::out_of_range("Error: Invalid port number");
    }
        if (std::strlen(argv[2]) == 0) {
        throw std::invalid_argument("Error: Empty password");
    }
}

int main(int argc, char **argv) {
    try 
	{
		Server irc;
        if (argc != 3) {
            std::cout << "write: executable file  <port> <password>" << std::endl;
            return 1;
        }
        check_arg(argv);
		irc.config_server(std::atoi(argv[1]), argv[2]);
        std::cout << "Server started. Listening on port " << std::endl;
        irc.acceptconnection();
        while (true)
        {
            irc.receivemessage();
            std::cout << "Server: ";
            char inputMessage[BUFFER_SIZE];
            
            
            std::cin.getline(inputMessage, BUFFER_SIZE);
            irc.sendmessage(inputMessage);
        }
        
        // std::cout << "Arguments are valid." << std::endl;
    }
	catch (const std::invalid_argument& e) 
	{
        std::cerr << e.what() << std::endl;
        return 1;
    }
	catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (const char *error_message)
    {
        std::cerr << error_message << std::endl;
        return 1;
    }
	catch (...) 
	{
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    return 0;
}

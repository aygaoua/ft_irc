//---------  -----------



// #include <iostream>
// #include <cstdlib>
// #include <cstring>
// #include <unistd.h>
// #include <sstream>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <poll.h>
// #include <fcntl.h>
// #include <vector>
// #include <stdexcept>

// #define BUFFER_SIZE 1024

// class Server {
// private:
//     int port;
//     std::string pass;
//     int fd_s_socket;
//     std::vector<int> fd_c_sockets;
//     char buffer[BUFFER_SIZE];

// public:
//     Server();
//     void config_server(int port_nbr, std::string str);
//     void accept_connection();
//     void receive_message(int fd_c_socket);
//     void send_message(const char *message);
//     int get_client_socket_fd() const; // Method to retrieve client socket file descriptor
//     ~Server();
// };

// Server::Server() {}

// void Server::config_server(int port_nbr, std::string str) {
//     this->port = port_nbr;
//     this->pass = str;

//     struct sockaddr_in server_addr;
//     this->fd_s_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (fd_s_socket == -1)
//         throw "socket creation error";

//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(this->port);
//     server_addr.sin_addr.s_addr = INADDR_ANY;

//     if (bind(fd_s_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
//         throw "binding error";

//     if (listen(fd_s_socket, SOMAXCONN) == -1)
//         throw "listening error";

//     // Set server socket to non-blocking
//     fcntl(fd_s_socket, F_SETFL, O_NONBLOCK);
// }

// void Server::accept_connection() {
//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);

//     int fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
//     if (fd_c_socket == -1) {
//         // No pending connections
//         return;
//     }

//     // Connection accepted successfully
//     // Set client socket to non-blocking
//     fcntl(fd_c_socket, F_SETFL, O_NONBLOCK);
//     fd_c_sockets.push_back(fd_c_socket);
//     std::cout << "New client connected. fd: " << fd_c_socket << std::endl;
// }

// void Server::receive_message(int fd_c_socket) {
//     int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, 0);
//     if (bytes_read <= 0) {
//         std::cout << "Client disconnected. fd: " << fd_c_socket << std::endl;
//         close(fd_c_socket);
//         fd_c_sockets.erase(std::remove(fd_c_sockets.begin(), fd_c_sockets.end(), fd_c_socket), fd_c_sockets.end());
//     } else {
//         buffer[bytes_read] = '\0';
//         std::cout << "Client " << fd_c_socket << ": " << buffer << std::endl;
//     }
// }

// void Server::send_message(const char *message) {
//     for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
//         if (send(fd_c_sockets[i], message, strlen(message), 0) == -1) {
//             std::cerr << "Send error to client " << fd_c_sockets[i] << std::endl;
//         }
//     }
// }

// int Server::get_client_socket_fd() const {
//     return fd_c_sockets.empty() ? -1 : fd_c_sockets[0];
// }

// Server::~Server() {
//     close(fd_s_socket);
//     for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
//         close(fd_c_sockets[i]);
//     }
// }

// void check_arg(char **argv) {
//     std::string portstr(argv[1]);
//     size_t portPos = portstr.find_first_not_of("0123456789");
//     if (portPos != std::string::npos) {
//         throw std::invalid_argument("Error: Invalid characters in port");
//     }
//     int port;
//     std::stringstream portstream(portstr);
//     portstream >> port;
//     if (port < 1024 || port > 65535) {
//         throw std::out_of_range("Error: Invalid port number");
//     }
//     if (std::strlen(argv[2]) == 0) {
//         throw std::invalid_argument("Error: Empty password");
//     }
// }

// int main(int argc, char **argv) {
//     try {
//         Server irc;
//         if (argc != 3) {
//             std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
//             return 1;
//         }

//         int port = std::atoi(argv[1]);
//         std::string pass = argv[2];
//         irc.config_server(port, pass);
//         std::cout << "Server started. Listening on port " << port << std::endl;

//         while (true) {
//             irc.accept_connection();

//             struct pollfd fds[2];
//             memset(fds, 0, sizeof(fds));

//             fds[0].fd = 0; // stdin
//             fds[0].events = POLLIN;

//             int client_socket_fd = irc.get_client_socket_fd();
//             if (client_socket_fd != -1) {
//                 fds[1].fd = client_socket_fd;
//                 fds[1].events = POLLIN;
//             }

//             int ret = poll(fds, 2, -1);
//             if (ret == -1) {
//                 throw "poll error";
//             }

//             if (fds[0].revents & POLLIN) {
//                 char inputMessage[BUFFER_SIZE];
//                 std::cin.getline(inputMessage, BUFFER_SIZE);
//                 irc.send_message(inputMessage);
//             }

//             if (fds[1].revents & POLLIN) {
//                 irc.receive_message(client_socket_fd);
//             }
//         }
//     } catch (const char *error_message) {
//         std::cerr << error_message << std::endl;
//         return 1;
//     } catch (...) {
//         std::cerr << "Unknown error occurred" << std::endl;
//         return 1;
//     }

//     return 0;
// }







//------------------------------------------
////////////////-----------------------------




// #include <iostream>
// #include <cstdlib>
// #include <cstring>
// #include <unistd.h>
// #include <sstream>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <poll.h>
// #include <fcntl.h>
// #include <vector>
// #include <stdexcept>
// #include <algorithm>

// #define BUFFER_SIZE 1024

// class Server {
// private:
//     int port;
//     std::string pass;
//     int fd_s_socket;
//     std::vector<int> fd_c_sockets;
//     char buffer[BUFFER_SIZE];

// public:
//     Server();
//     void config_server(int port_nbr, std::string str);
//     void accept_connection();
//     void receive_message(int fd_c_socket);
//     void send_message(const char *message);
//     std::vector<int>& get_client_sockets(); // Provide access to client sockets
//     ~Server();
// };

// Server::Server() {}

// void Server::config_server(int port_nbr, std::string str) {
//     this->port = port_nbr;
//     this->pass = str;

//     struct sockaddr_in server_addr;
//     this->fd_s_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (fd_s_socket == -1)
//         throw "socket creation error";

//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(this->port);
//     server_addr.sin_addr.s_addr = INADDR_ANY;

//     if (bind(fd_s_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
//         throw "binding error";

//     if (listen(fd_s_socket, SOMAXCONN) == -1)
//         throw "listening error";

//     // Set server socket to non-blocking
//     fcntl(fd_s_socket, F_SETFL, O_NONBLOCK);
// }

// void Server::accept_connection() {
//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);

//     int fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
//     if (fd_c_socket != -1) {
//         // Connection accepted successfully
//         // Set client socket to non-blocking
//         fcntl(fd_c_socket, F_SETFL, O_NONBLOCK);
//         fd_c_sockets.push_back(fd_c_socket);
//         std::cout << "New client connected. fd: " << fd_c_socket << std::endl;
//     }
//     // else {
//     //     std::cerr << "Failed to accept connection" << std::endl;
//     // }
// }

// void Server::receive_message(int fd_c_socket) {
//     int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, 0);
//     if (bytes_read <= 0) {
//         std::cout << "Client disconnected. fd: " << fd_c_socket << std::endl;
//         close(fd_c_socket);
//         fd_c_sockets.erase(std::remove(fd_c_sockets.begin(), fd_c_sockets.end(), fd_c_socket), fd_c_sockets.end());
//     } else {
//         buffer[bytes_read] = '\0';
//         std::cout << "Client " << fd_c_socket << ": " << buffer << std::endl;
//     }
// }

// void Server::send_message(const char *message) {
//     for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
//         if (send(fd_c_sockets[i], message, strlen(message), 0) == -1) {
//             std::cerr << "Send error to client " << fd_c_sockets[i] << std::endl;
//         }
//     }
// }

// std::vector<int>& Server::get_client_sockets() {
//     return fd_c_sockets;
// }

// Server::~Server() {
//     close(fd_s_socket);
//     for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
//         close(fd_c_sockets[i]);
//     }
// }

// void check_arg(char **argv) {
//     std::string portstr(argv[1]);
//     size_t portPos = portstr.find_first_not_of("0123456789");
//     if (portPos != std::string::npos) {
//         throw std::invalid_argument("Error: Invalid characters in port");
//     }
//     int port;
//     std::stringstream portstream(portstr);
//     portstream >> port;
//     if (port < 1024 || port > 65535) {
//         throw std::out_of_range("Error: Invalid port number");
//     }
//     if (std::strlen(argv[2]) == 0) {
//         throw std::invalid_argument("Error: Empty password");
//     }
// }

// int main(int argc, char **argv) {
//     try {
//         Server irc;
//         if (argc != 3) {
//             std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
//             return 1;
//         }

//         int port = std::atoi(argv[1]);
//         std::string pass = argv[2];
//         irc.config_server(port, pass);
//         std::cout << "Server started. Listening on port " << port << std::endl;

//         while (true) {
//             // std::cout << "hello 1" <<std::endl;
//             irc.accept_connection();

//             std::vector<int>& fd_c_sockets = irc.get_client_sockets();
//             std::vector<pollfd> fds(fd_c_sockets.size() + 1); // Add 1 for stdin
//             memset(&fds[0], 0, sizeof(fds[0])); // Initialize the first element

//             fds[0].fd = 0; // stdin
//             fds[0].events = POLLIN;

//             for (size_t i = 0; i < fd_c_sockets.size(); i++) {
//                 fds[i + 1].fd = fd_c_sockets[i];
//                 fds[i + 1].events = POLLIN;
//             }

//             int ret = poll(&fds[0], fds.size(), -1);
//             // std::cout << "hello 2" <<std::endl;
//             if (ret == -1) {
//                 throw "poll error";
//             }

//             if (fds[0].revents & POLLIN) {
//                 char inputMessage[BUFFER_SIZE];
//                 std::cin.getline(inputMessage, BUFFER_SIZE);
//                 irc.send_message(inputMessage);
//             }

//             for (size_t i = 0; i < fd_c_sockets.size(); i++) {
//                 if (fds[i + 1].revents & POLLIN) {
//                     irc.receive_message(fd_c_sockets[i]);
//                 }
//             }
//         }
//     } catch (const char *error_message) {
//         std::cerr << error_message << std::endl;
//         return 1;
//     } catch (...) {
//         std::cerr << "Unknown error occurred" << std::endl;
//         return 1;
//     }

//     return 0;
// }







////////////////////////////////-------------------////////////////////////////////
////////////////////////////////-------------------////////////////////////////////
////////////////////////////////-------------------////////////////////////////////




#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include <fcntl.h>
#include <vector>
#include <stdexcept>
#include <algorithm>

#define BUFFER_SIZE 1024

class Server {
private:
    int port;
    std::string pass;
    int fd_s_socket;
    std::vector<int> fd_c_sockets;
    char buffer[BUFFER_SIZE];

public:
    Server();
    void config_server(int port_nbr, std::string str);
    void accept_connection();
    void receive_message(int fd_c_socket);
    void send_message(const char *message);
    std::vector<int>& get_client_sockets(); // Provide access to client sockets
    ~Server();
};

Server::Server() {}

void Server::config_server(int port_nbr, std::string str) {
    this->port = port_nbr;
    this->pass = str;
    int enable = 1;
    struct sockaddr_in server_addr;
    this->fd_s_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_s_socket == -1)
        throw "socket creation error";

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd_s_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        throw "binding error";
    if (listen(fd_s_socket, SOMAXCONN) == -1)
        throw "listening error";

    // Set server socket to non-blocking
    fcntl(fd_s_socket, F_SETFL, O_NONBLOCK);
}

void Server::accept_connection() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (fd_c_socket != -1) {
        // Connection accepted successfully
        // Set client socket to non-blocking
        fcntl(fd_c_socket, F_SETFL, O_NONBLOCK);
        fd_c_sockets.push_back(fd_c_socket);
        std::cout << "New client connected. fd: " << fd_c_socket << std::endl;
    }
}

// void Server::accept_connection() {
//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);

//     int fd_c_socket = accept(fd_s_socket, (struct sockaddr *)&client_addr, &client_addr_len);
//     if (fd_c_socket != -1) {
//         // Check if the client socket already exists in the list
//         if (std::find(fd_c_sockets.begin(), fd_c_sockets.end(), fd_c_socket) == fd_c_sockets.end()) {
//             // Connection accepted successfully and client socket is not already in the list
//             // Set client socket to non-blocking
//             fcntl(fd_c_socket, F_SETFL, O_NONBLOCK);
//             fd_c_sockets.push_back(fd_c_socket);
//             std::cout << "New client connected. fd: " << fd_c_socket << std::endl;
//         } else {
//             // Client socket already exists in the list, so it's a reconnection
//             std::cout << "Client reconnected. fd: " << fd_c_socket << std::endl;
//         }
//     }
//     // else {
//     //     std::cerr << "Failed to accept connection" << std::endl;
//     // }
// }


void Server::receive_message(int fd_c_socket) {
    int bytes_read = recv(fd_c_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_read <= 0) {
        std::cout << "Client disconnected. fd: " << fd_c_socket << std::endl;
        close(fd_c_socket);
        fd_c_sockets.erase(std::remove(fd_c_sockets.begin(), fd_c_sockets.end(), fd_c_socket), fd_c_sockets.end());
    } else {
        buffer[bytes_read] = '\0';
        std::cout << "Client " << fd_c_socket << ": " << buffer << std::endl;
    }
}

// void Server::send_message(const char *message) {
//     for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
//         if (send(fd_c_sockets[i], message, strlen(message), 0) == -1) {
//             std::cerr << "Send error to client " << fd_c_sockets[i] << std::endl;
//         }
//     }
// }

void Server::send_message(const char *message) {
    for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
        ssize_t bytes_sent = send(fd_c_sockets[i], message, strlen(message), 0);
        if (bytes_sent == -1) {
            // Handle send error
            std::cerr << "Send error to client " << fd_c_sockets[i] << std::endl;
        } else if (bytes_sent < strlen(message)) {
            // Handle partial send
            std::cerr << "Partial send to client " << fd_c_sockets[i] << std::endl;
        }
    }
}


std::vector<int>& Server::get_client_sockets() {
    return fd_c_sockets;
}

Server::~Server() {
    close(fd_s_socket);
    for (size_t i = 0; i < fd_c_sockets.size(); ++i) {
        close(fd_c_sockets[i]);
    }
}

void check_arg(char **argv) {
    std::string portstr(argv[1]);
    size_t portPos = portstr.find_first_not_of("0123456789");
    if (portPos != std::string::npos) {
        throw std::invalid_argument("Error: Invalid characters in port");
    }
    int port;
    std::stringstream portstream(portstr);
    portstream >> port;
    if (port < 1024 || port > 65535) {
        throw std::out_of_range("Error: Invalid port number");
    }
    if (std::strlen(argv[2]) == 0) {
        throw std::invalid_argument("Error: Empty password");
    }
}

int main(int argc, char **argv) {
    try {
        Server irc;
        if (argc != 3) {
            std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
            return 1;
        }

        int port = std::atoi(argv[1]);
        std::string pass = argv[2];
        irc.config_server(port, pass);
        std::cout << "Server started. Listening on port " << port << std::endl;

        while (true) {
            irc.accept_connection();

            std::vector<int>& fd_c_sockets = irc.get_client_sockets();
            std::vector<pollfd> fds(fd_c_sockets.size() + 1); // Add 1 for stdin
            memset(&fds[0], 0, sizeof(fds[0])); // Initialize the first element

            fds[0].fd = 0; // stdin
            fds[0].events = POLLIN;

            for (size_t i = 0; i < fd_c_sockets.size(); i++) {
                fds[i + 1].fd = fd_c_sockets[i];
                fds[i + 1].events = POLLIN;
            }

            int ret = poll(&fds[0], fds.size(), -1);
            
            if (ret == -1) {
                throw "poll error";
            }

            // if (fds[0].revents & POLLIN) {
                // Check if there is data available to be read from the client sockets, not stdin
                for (size_t i = 1; i < fds.size(); ++i) {
                    if (fds[i].revents & POLLIN) {
                        // std::cout << "ooooooooooo "  << std::endl;
                        char inputMessage[BUFFER_SIZE];
                        ssize_t bytes_read = recv(fds[i].fd, inputMessage, BUFFER_SIZE - 1, 0);
                        if (bytes_read <= 0) {
                            // Handle disconnection or error
                            std::cerr << "Error or client disconnected. fd: " << fds[i].fd << std::endl;
                            close(fds[i].fd);
                            fd_c_sockets.erase(std::remove(fd_c_sockets.begin(), fd_c_sockets.end(), fds[i].fd), fd_c_sockets.end());
                        } else {
                            inputMessage[bytes_read] = '\0'; // Null-terminate the received data
                            std::cout << "Client " << fds[i].fd << ": " << inputMessage << std::endl;
                        }
                    }
                }
            // }

            // Handle events for client sockets
            for (size_t i = 1; i < fds.size(); i++) {
                if (fds[i].revents & POLLIN) {
                    irc.receive_message(fd_c_sockets[i - 1]);
                }
            }
        }
    } catch (const char *error_message) {
        std::cerr << error_message << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    return 0;
}


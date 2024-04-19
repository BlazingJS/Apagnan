#include "server.hpp"

Server::Server()
{
    this->port = 8080;
}

Server::~Server()
{
    close(this->server_fd);
}

void Server::Start()
{
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_fd == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return;
    }

    if (listen(server_fd, 5) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return;
    }

    std::cout << "Server listening on port " << port << std::endl;

    while (true) {
        int addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }
        
        HandleClient(client_socket);
    }
}

void Server::HandleClient(int client_socket)
{
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;

    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    send(client_socket, response, strlen(response), 0);

    close(client_socket);
}
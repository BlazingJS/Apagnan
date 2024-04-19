#include "server/server.hpp"

Server::Server(int port, size_t buffer_size)
{
    this->port = port;
    this->buffer_size = buffer_size;

    this->logger = Logger();
    this->request = Request();

    this->methodHandlers["GET"] = &Server::handleGetRequest;
    this->methodHandlers["POST"] = &Server::handlePostRequest;
    this->methodHandlers["PUT"] = &Server::handlePutRequest;
    this->methodHandlers["OPTIONS"] = &Server::handleOptionsRequest;
    this->methodHandlers["DELETE"] = &Server::handleDeleteRequest;
    this->methodHandlers["PATCH"] = &Server::handlePatchRequest;
    this->methodHandlers["UPDATE"] = &Server::handleUpdateRequest;
}

Server::~Server()
{
    close(this->server_fd);
}

bool Server::CreateSocket()
{
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->server_fd == -1) {
        this->logger.Critical("socket creation failed");
        return (false);
    }

    return (true);
}

bool Server::Bind()
{
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(port);

    if (bind(this->server_fd, (struct sockaddr *)&this->address, sizeof(this->address)) < 0) {
        this->logger.Critical("bind failed");
        return (false);
    }

    return (true);
}

bool Server::Listen()
{
    if (listen(this->server_fd, 5) < 0) {
        this->logger.Critical("listen failed");
        return (false);
    }

    return (true);
}

void Server::Core()
{
    int addrlen = 0;
    int client_socket = 0;

    while (true) {
        addrlen = sizeof(this->address);
        client_socket = accept(
            this->server_fd, (struct sockaddr *)&this->address, (socklen_t*)&addrlen
        );
        if (client_socket < 0) {
            this->logger.Critical("accept failed");
            continue;
        }
        
        HandleClient(client_socket);
    }
}

void Server::Start()
{
    bool is_socket_created = CreateSocket();
    bool is_binded = Bind();
    bool is_listenning = Listen();

    this->logger.Information(std::format("socket: {}, binded: {}, listenning: {}", is_socket_created, is_binded, is_listenning));

    Core();
}

std::string Server::GetHttpMethod(const char *request)
{
    std::string method;
    std::istringstream iss(request);

    iss >> method;

    return (method);
}

void Server::HandleClient(int client_socket)
{
    char *buffer = new char[this->buffer_size];
    int valread = read(client_socket, buffer, this->buffer_size);

    this->logger.Information(std::format("received: {}", buffer));

    std::string method = GetHttpMethod(buffer);

    auto it = methodHandlers.find(method);

    if (it != methodHandlers.end()) {
        it->second(*this, client_socket);
    } else {
        handleGetRequest(client_socket);
    }


    close(client_socket);
}

void Server::handleGetRequest(int client_socket)
{
    std::vector<std::string> data = {
        "HTTP/1.1 200 OK",
        "Content-Type: text/plain",
        "Content-Length: 12\n",
        "GET request!"
    };
    const char *response = this->request.Send(
        "TEST",
        data
    );
    
    send(client_socket, response, strlen(response), 0);
}

void Server::handlePostRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handlePutRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handlePatchRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handleOptionsRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handleDeleteRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handleTraceRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handleUpdateRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

void Server::handleConnectRequest(int client_socket)
{
    // Handle POST request
    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nPOST request!";
    send(client_socket, response, strlen(response), 0);
}

// Implement handlers for other HTTP methods similarly

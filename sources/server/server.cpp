#include "server/server.hpp"

Server::Server(int port, size_t buffer_size)
{
    this->port = port;
    this->buffer_size = buffer_size;

    this->logger = Logger();
    this->request = Request();
}

Server::~Server()
{
    
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

void Server::Stop()
{
    close(this->server_fd);

    this->logger.Information("server stopped");
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

    std::vector<std::string> header = {
        "header"
    };


    this->request.GET(client_socket, header, 0);

    close(client_socket);
}


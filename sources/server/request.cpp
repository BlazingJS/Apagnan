#include "server/request.hpp"

Request::Request()
{

}

Request::~Request()
{

}

char *Request::Send(std::string method, std::vector<std::string> items)
{
    char *buffer = Build(items);

    return (buffer);
}


char *Request::Build(std::vector<std::string> items)
{
    std::string buffer = "";
    char *array = nullptr;

    for(const std::string& item : items) {
        buffer += item + '\n';
    }

    array = new char[buffer.size() + 1];
    std::strcpy(array, buffer.c_str());
    
    return array;
}

#include "middleware/validation.hpp"

Validation::Validation()
{
    this->logger = Logger();
}

Validation::~Validation()
{

}

void Validation::HandleRequest(std::string &request)
{
    std::string method;
    std::istringstream iss(request);
    std::vector<std::string> allowedMethods = {
        "GET",
        "POST",
        "PUT",
        "DELETE",
        "PATCH"
    };

    iss >> method;

    std::transform(method.begin(), method.end(), method.begin(), ::toupper);


    if (std::find(allowedMethods.begin(), allowedMethods.end(), method) != allowedMethods.end()) {
        this->logger.Information(std::format("Valid HTTP method: {}", method));
    } else {
        this->logger.Error(std::format("Invalid HTTP method: {}", method));
    }
}

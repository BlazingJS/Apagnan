#include <iostream>
#include <format>

class Logger
{
    public:
        Logger();
        ~Logger();

        void Information(std::string);
        void Debug(std::string);
        void Error(std::string);
        void Warning(std::string);
        void Critical(std::string);
};

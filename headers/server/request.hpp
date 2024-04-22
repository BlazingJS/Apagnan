#pragma once

    #include <iostream>
    #include <vector>
    #include <format>

    class Request
    {
        public:
            Request();
            ~Request();

            char *Send(std::string, std::vector<std::string>);

        private:
            char *Build(std::vector<std::string>);
    };

#include "tools/concat.hpp"

static std::string ConcatVector(const std::vector<std::string> &items)
{
    std::string result;

    for (const std::string& str : items) {
        result += str;
    }

    return (result);
}

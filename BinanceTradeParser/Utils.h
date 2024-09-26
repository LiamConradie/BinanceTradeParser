#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "TradeParser.h"


std::string to_utf8_string(const utility::string_t& input);

class Utils {
public:
    // TODO: Implement method to measure parsing speed
    static void measureParsingSpeed(const std::string& jsonData, TradeParser& parser);

private:
    // TODO: Add any necessary private methods or members
};

#endif // UTILS_H


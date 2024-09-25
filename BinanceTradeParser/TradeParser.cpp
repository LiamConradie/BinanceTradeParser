#include "TradeParser.h"
// Include JSON parsing library headers
// TODO: Include necessary headers for JSON parsing (e.g., nlohmann/json)

TradeParser::TradeParser() {
    // Constructor implementation (if needed)
}

std::vector<Trade> TradeParser::parse(const std::string& jsonData) {
    std::vector<Trade> trades;

    // TODO: Implement parsing logic
    // Parse jsonData into JSON objects
    // For each trade object, extract the fields and populate the Trade struct
    // Add each Trade to the trades vector

    return trades;
}

// Overload the output stream operator
std::ostream& operator<<(std::ostream& os, const Trade& trade) {
    os << "{" << std::endl;
    os << "  \"a\": " << trade.aggregateTradeId << "," << std::endl;
    os << "  \"p\": \"" << trade.price << "\"," << std::endl;
    os << "  \"q\": \"" << trade.quantity << "\"," << std::endl;
    os << "  \"f\": " << trade.firstTradeId << "," << std::endl;
    os << "  \"l\": " << trade.lastTradeId << "," << std::endl;
    os << "  \"T\": " << trade.timestamp << "," << std::endl;
    os << "  \"m\": " << (trade.isBuyerMaker ? "true" : "false") << std::endl;
    os << "}";
    return os;
}

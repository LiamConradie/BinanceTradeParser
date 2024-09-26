#ifndef TRADEPARSER_H
#define TRADEPARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <cpprest/json.h>  // For JSON parsing

// Trade struct to hold individual trade information
struct Trade {
    long long aggregateTradeId;
    std::string price;
    std::string quantity;
    long long firstTradeId;
    long long lastTradeId;
    long long timestamp;
    bool isBuyerMaker;

    // Overload the output stream operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const Trade& trade) {
        os << "[\n"
            << "{\n"
            << "\"a\": " << trade.aggregateTradeId << ",\n"
            << "\"p\": \"" << trade.price << "\",\n"
            << "\"q\": \"" << trade.quantity << "\",\n"
            << "\"f\": " << trade.firstTradeId << ",\n"
            << "\"l\": " << trade.lastTradeId << ",\n"
            << "\"T\": " << trade.timestamp << ",\n"
            << "\"m\": " << (trade.isBuyerMaker ? "true" : "false") << "\n"
            << "}\n"
            << "]";
        return os;
    }
};

// TradeParser class to handle parsing of trades
class TradeParser {
public:
    TradeParser() = default;

    // Parse the JSON response into a list of Trade structs and return it
    std::vector<Trade> parseTrades(const web::json::value& tradesJson);

private:
    // Add any necessary private methods or members if needed
};

#endif // TRADEPARSER_H

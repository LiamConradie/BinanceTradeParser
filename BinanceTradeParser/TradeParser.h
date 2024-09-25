#ifndef TRADEPARSER_H
#define TRADEPARSER_H

#include <string>
#include <vector>
#include <iostream>

struct Trade {
    long long aggregateTradeId;
    std::string price;
    std::string quantity;
    long long firstTradeId;
    long long lastTradeId;
    long long timestamp;
    bool isBuyerMaker;

    // Overload the output stream operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const Trade& trade);
};

class TradeParser {
public:
    TradeParser();

    // TODO: Parse the JSON response into a list of Trade structs
    std::vector<Trade> parse(const std::string& jsonData);

private:
    // TODO: Add any necessary private methods or members
};

#endif // TRADEPARSER_H


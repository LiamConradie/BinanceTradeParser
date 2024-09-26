#include "TradeParser.h"
#include "utils.h"
#include <cpprest/json.h>
#include <iostream>
#include <locale>
#include <codecvt>


std::vector<Trade> TradeParser::parseTrades(const web::json::value& tradesJson) {
    std::vector<Trade> trades;
    auto tradesArray = tradesJson.as_array();

    // Debugging: Print the number of trades received
    std::cout << "Number of trades received: " << tradesArray.size() << std::endl;

    // Loop through each trade in the array
    for (const auto& trade : tradesArray) {
        Trade parsedTrade;
        parsedTrade.aggregateTradeId = trade.at(U("a")).as_integer();  // Aggregate trade ID
        parsedTrade.price = to_utf8_string(trade.at(U("p")).as_string());  // Price
        parsedTrade.quantity = to_utf8_string(trade.at(U("q")).as_string());  // Quantity
        parsedTrade.firstTradeId = trade.at(U("f")).as_integer();  // First trade ID
        parsedTrade.lastTradeId = trade.at(U("l")).as_integer();   // Last trade ID
        parsedTrade.timestamp = trade.at(U("T")).as_number().to_int64();  // Timestamp
        parsedTrade.isBuyerMaker = trade.at(U("m")).as_bool();  // Buyer is maker?

        // Debugging: Print each parsed trade
        std::cout << "Parsed Trade: ["
            << "a: " << parsedTrade.aggregateTradeId << ", "
            << "p: " << parsedTrade.price << ", "
            << "q: " << parsedTrade.quantity << ", "
            << "f: " << parsedTrade.firstTradeId << ", "
            << "l: " << parsedTrade.lastTradeId << ", "
            << "T: " << parsedTrade.timestamp << ", "
            << "m: " << (parsedTrade.isBuyerMaker ? "true" : "false")
            << "]" << std::endl;

        trades.push_back(parsedTrade);
    }

    return trades;  // Return the vector of trades
}

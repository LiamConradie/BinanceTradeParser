// main.cpp
#include <iostream>
#include "HttpClient.h"
#include "TradeParser.h"
#include "Utils.h"

int main() {
    std::cout << "Starting Binance Trade Parser..." << std::endl;

    // TODO: Initialize HTTP client and connect to Binance API endpoint
    HttpClient httpClient;

    // TODO: Fetch trade data from Binance API
    std::string response = httpClient.get("/fapi/v1/aggTrades?symbol=BTCUSDT");

    // TODO: Parse the incoming trade data
    TradeParser parser;
    auto trades = parser.parse(response);

    // TODO: Measure parsing speed
    Utils::measureParsingSpeed(response, parser);

    // TODO: Print each trade in the specified format
    for (const auto& trade : trades) {
        std::cout << trade << std::endl; // Overload operator<< for Trade struct
    }

    return 0;
}

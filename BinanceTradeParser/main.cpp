#include <iostream>
#include "HttpClient.h"
#include "TradeParser.h"
#include "Utils.h"

int main() {
    std::cout << "Starting Binance Trade Parser..." << std::endl;

    // Initialize HTTP client with the base URL for Binance API
    HttpClient httpClient("https://fapi.binance.com");

    // Perform a GET request for the specific endpoint
    std::string endpoint = "/fapi/v1/aggTrades?symbol=BTCUSDT";
    auto responseTask = httpClient.get(endpoint);

    // Wait for the response
    responseTask.then([](std::string response) {
        // Limit the number of characters printed to 500
        if (response.length() > 500) {
            std::cout << "Response (truncated to 500 chars): " << response.substr(0, 500) << "..." << std::endl;
        }
        else {
            std::cout << "Response: " << response << std::endl;
        }
        }).wait();

    // TODO: Parse the incoming trade data
    //TradeParser parser;
   // auto trades = parser.parse(response);

    // TODO: Measure parsing speed
   // Utils::measureParsingSpeed(response, parser);

    // TODO: Print each trade in the specified format
    //for (const auto& trade : trades) {
   //     std::cout << trade << std::endl; // Overload operator<< for Trade struct
    //}

    return 0;
}

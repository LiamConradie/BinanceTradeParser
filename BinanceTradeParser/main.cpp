#include <iostream>
#include "HttpClient.h"
#include "TradeParser.h"
#include "Utils.h"

#include <crow.h>
#include "BinanceAPI.h"

int main() {
    std::cout << "Starting Binance Trade Parser..." << std::endl;

    //crow::SimpleApp app;
    BinanceAPI binanceAPI;

    std::string symbol = "BTCUSDT";

    // Retrieve the aggregated trades for the symbol
    std::string response = binanceAPI.getAggregatedTrades(symbol);

    // Output the parsed trades to the console
    std::cout << "Starting Binance Trade Parser..." << std::endl;
    binanceAPI.printParsedResponse(response);

    /*
    CROW_ROUTE(app, "/aggTrades/<string>")
        ([&binanceAPI](const std::string& symbol) {
        auto response = binanceAPI.getAggregatedTrades(symbol);
        binanceAPI.printParsedResponse(response);  // Parse and print the response
        return crow::response(response);           // Return raw response
            });

    app.port(18080).multithreaded().run();

    */



    /*

    // Initialize HTTP client with the base URL for Binance API
    HttpClient httpClient("https://fapi.binance.com");
    TradeParser tradeParser;

    // Set up a lambda function to handle incoming trades
    auto onTradesReceived = [&](const web::json::value& tradesJson) {
        std::cout << "Received JSON in main, calling parseTrades..." << std::endl;
        tradeParser.parseTrades(tradesJson);
        };

    // Debugging: Log when polling starts
    std::cout << "Polling the Binance API every 20 seconds..." << std::endl;

    // Poll the Binance API every 20 seconds and pass the trades to the trade parser
    httpClient.pollTrades("/fapi/v1/aggTrades?symbol=BTCUSDT", onTradesReceived, 20);

    */

    return 0;
}

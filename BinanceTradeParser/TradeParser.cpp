#include "TradeParser.h"
#include <thread>  // Include thread library for asynchronous execution
#include <chrono>  // Include chrono library for delays
#include <iostream>

// Function definition
void fetchAndParseTrades(BinanceAPI& binanceAPI, const std::string& symbol, long long& lastTradeId) {
    int i = 0;
    while (i < 5) { //Only poll twice, set to True for continuous polling
        // Retrieve the aggregated trades for the symbol from lastTradeId asynchronously
        std::string response = binanceAPI.getAggregatedTrades(symbol, lastTradeId);
        std::cout << "Fetching and parsing trades...\n";

        // Parse and print the trades asynchronously
        std::thread parseThread(&BinanceAPI::printParsedResponse, &binanceAPI, response, std::ref(lastTradeId));
        parseThread.detach();  // Detach the thread so it can run independently

        // Wait for 5 seconds before polling again (simulate streaming)
        std::this_thread::sleep_for(std::chrono::seconds(10));
        i++;
    }
}

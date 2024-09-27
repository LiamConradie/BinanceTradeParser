#include <iostream>
#include "BinanceAPI.h"
#include "TradeParser.h"

/**
 * @brief The entry point of the Binance Trade Polling application.
 *
 * This function initializes the BinanceAPI object and begins the polling process to fetch and parse
 * aggregated trades for the specified symbol (e.g., "BTCUSDT"). The polling is asynchronous, and
 * the function tracks the last processed trade ID to prevent duplicate trade fetching in subsequent
 * calls.
 *
 * @return int Program exit status.
 */
int main() {

    BinanceAPI binanceAPI;  // Object to interact with Binance API
    std::string symbol = "BTCUSDT";  // The symbol for which trades will be fetched (e.g., BTC/USDT)

    // Keep track of the last processed trade ID to avoid duplicate trades
    long long lastTradeId = -1;  // Initial value set to -1 to indicate that no trades have been processed yet

    // Begin the asynchronous polling of trades for the specified symbol
    std::cout << "Starting Binance Trade Polling...\n";

    // Function call to begin polling and parsing trades
    fetchAndParseTrades(binanceAPI, symbol, lastTradeId);  // Pass the BinanceAPI object and lastTradeId by reference

    return 0;  // Return 0 to indicate successful execution
}

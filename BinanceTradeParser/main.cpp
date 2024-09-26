#include <iostream>
#include "BinanceAPI.h"
#include "TradeParser.h"

int main() {

    BinanceAPI binanceAPI;
    std::string symbol = "BTCUSDT";

    // Keep track of the lastTradeId
    long long lastTradeId = -1;

    // Start asynchronous polling of trades
    std::cout << "Starting Binance Trade Polling...\n";
    fetchAndParseTrades(binanceAPI, symbol, lastTradeId);  // Pass the lastTradeId

    return 0;
}

#include <iostream>
#include "BinanceAPI.h"

int main() {

    BinanceAPI binanceAPI;

    std::string symbol = "BTCUSDT";

    // Retrieve the aggregated trades for the symbol
    std::string response = binanceAPI.getAggregatedTrades(symbol);

    // Output the parsed trades to the console
    std::cout << "Starting Binance Trade Parser..." << std::endl;
    binanceAPI.printParsedResponse(response);

    return 0;
}

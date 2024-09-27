#include "TradeParser.h"
#include <thread>  // For managing asynchronous execution
#include <chrono>  // For handling time delays
#include <iostream>
#include <conio.h>  // For keyboard input handling (_getch() on Windows)

/**
 * @brief Polls Binance API for aggregated trades, allowing manual or continuous polling.
 *
 * This function fetches and parses aggregated trades from the Binance API. The polling behavior can
 * be controlled by user input. The user can choose to manually poll (by pressing the spacebar),
 * enable continuous polling (by pressing '1'), or quit the polling loop (by pressing 'q').
 *
 * @param binanceAPI Reference to the BinanceAPI object used for fetching trades.
 * @param symbol The trading pair symbol (e.g., "BTCUSDT") for which trades are fetched.
 * @param lastTradeId Reference to the last processed trade ID to avoid duplicate fetching in subsequent polls.
 */
void fetchAndParseTrades(BinanceAPI& binanceAPI, const std::string& symbol, long long& lastTradeId) {
    bool continuousPolling = false;  // Flag to manage continuous streaming mode
    char input = ' ';  // Variable to capture user input for controlling polling behavior

    while (true) {  // Infinite loop to continuously poll the Binance API
        // If continuous polling is not enabled, wait for user input
        if (!continuousPolling) {
            std::cout << "Press Spacebar to poll, '1' to stream continuously, or 'q' to quit:\n";
            input = _getch();  // Wait for user input

            // Handle user input
            if (input == 'q') {
                std::cout << "Polling stopped by user.\n";
                break;  // Exit the polling loop when 'q' is pressed
            }
            else if (input == '1') {
                continuousPolling = true;  // Enable continuous streaming mode
                std::cout << "Continuous streaming mode enabled.\n";
            }
            else if (input != ' ') {
                continue;  // If the input is not ' ', '1', or 'q', ignore and wait for valid input
            }
        }

        // Fetch aggregated trades asynchronously from Binance API starting from lastTradeId
        std::string response = binanceAPI.getAggregatedTrades(symbol, lastTradeId);
        std::cout << "Fetching and parsing trades...\n";

        // Parse the retrieved trades and print them in a separate thread
        std::thread parseThread(&BinanceAPI::printParsedResponse, &binanceAPI, response, std::ref(lastTradeId));
        parseThread.detach();  // Detach the thread so it runs independently of the main execution

        // Delay the next poll by 5 seconds unless continuous streaming is enabled
        if (!continuousPolling) {
            std::this_thread::sleep_for(std::chrono::seconds(5));  // Pause for 5 seconds between manual polls
        }
    }
}

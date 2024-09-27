#ifndef TRADEPARSER_H
#define TRADEPARSER_H

#include "BinanceAPI.h"
#include <string>

/**
 * @brief Fetches and parses trades from the Binance API in a polling loop.
 *
 * This function continuously polls the Binance API to fetch aggregated trades for the given symbol.
 * It prints each trade in a formatted manner and keeps track of the last trade ID processed to avoid
 * duplicate fetching in subsequent calls.
 *
 * @param binanceAPI Reference to the BinanceAPI object for making API requests.
 * @param symbol The trading pair symbol (e.g., "BTCUSDT") for which to fetch trades.
 * @param lastTradeId Reference to a long long integer that holds the last processed trade ID.
 *                    This ensures that no trades are fetched more than once.
 *
 * @note The function is designed to support both manual and continuous polling based on user input.
 */
void fetchAndParseTrades(BinanceAPI& binanceAPI, const std::string& symbol, long long& lastTradeId);

#endif // TRADEPARSER_H

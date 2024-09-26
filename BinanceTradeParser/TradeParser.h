#ifndef TRADEPARSER_H
#define TRADEPARSER_H

#include "BinanceAPI.h"
#include <string>

// Function declaration
void fetchAndParseTrades(BinanceAPI& binanceAPI, const std::string& symbol, long long& lastTradeId);


#endif // TRADEPARSER_H

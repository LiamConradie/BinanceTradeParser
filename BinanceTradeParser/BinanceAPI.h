#ifndef BINANCE_API_H
#define BINANCE_API_H

#include <string>

class BinanceAPI {
public:
    BinanceAPI();
    ~BinanceAPI();
    std::string getAggregatedTrades(const std::string& symbol);
    void printParsedResponse(const std::string& response);

private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* s);
};

#endif // BINANCE_API_H

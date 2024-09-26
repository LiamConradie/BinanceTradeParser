#include "BinanceAPI.h"
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>  
#include <chrono>
#include <thread>  
#include <algorithm> 

using json = nlohmann::json;

// Callback function to handle response data
size_t BinanceAPI::writeCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

BinanceAPI::BinanceAPI() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

BinanceAPI::~BinanceAPI() {
    curl_global_cleanup();
}

std::string BinanceAPI::getAggregatedTrades(const std::string& symbol, long long fromId) {
    CURL* curl = curl_easy_init();
    std::ostringstream urlStream;
    urlStream << "https://fapi.binance.com/fapi/v1/aggTrades?symbol=" << symbol;

    // Add the fromId parameter if it's greater than -1
    if (fromId > -1) {
        urlStream << "&fromId=" << fromId;
    }

    std::string url = urlStream.str();

    if (curl) {
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, BinanceAPI::writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        return response;
    }

    return "";
}

// Parse and print the JSON response in the required format
void BinanceAPI::printParsedResponse(const std::string& response) {
    try {
        auto jsonArray = json::parse(response);

        long long lastSeenTradeId = -1;

        for (const auto& trade : jsonArray) {
            // Keep track of the highest trade ID in the response
            lastSeenTradeId = std::max<long long>(lastSeenTradeId, trade["a"].get<long long>());

            // Start timing the parsing of each trade
            auto start = std::chrono::high_resolution_clock::now();

            // Parse and print trade information
            std::cout << "{\n";
            std::cout << "\"a\": " << trade["a"] << ", // Aggregate tradeId\n";
            std::cout << "\"p\": \"" << trade["p"] << "\", // Price\n";
            std::cout << "\"q\": \"" << trade["q"] << "\", // Quantity\n";
            std::cout << "\"f\": " << trade["f"] << ", // First tradeId\n";
            std::cout << "\"l\": " << trade["l"] << ", // Last tradeId\n";
            std::cout << "\"T\": " << trade["T"] << ", // Timestamp\n";
            std::cout << "\"m\": " << (trade["m"] ? "true" : "false") << ", // Was the buyer the maker?\n";
            std::cout << "}\n\n";

            // End timing
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            // Output the time taken to parse this trade
            std::cout << "Trade parsed in: " << duration << " microseconds.\n\n";
        }

        // Update the lastTradeId after processing the trades
        if (lastSeenTradeId > -1) {
            std::cout << "Last Trade ID Processed: " << lastSeenTradeId << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
    }
}

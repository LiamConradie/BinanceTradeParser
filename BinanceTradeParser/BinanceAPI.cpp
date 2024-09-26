#include "BinanceAPI.h"
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

BinanceAPI::BinanceAPI() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

BinanceAPI::~BinanceAPI() {
    curl_global_cleanup();
}

std::string BinanceAPI::getAggregatedTrades(const std::string& symbol) {
    CURL* curl = curl_easy_init();
    std::string url = "https://fapi.binance.com/fapi/v1/aggTrades?symbol=" + symbol;

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

size_t BinanceAPI::writeCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

// Parse and print the JSON response in the required format
void BinanceAPI::printParsedResponse(const std::string& response) {
    try {
        auto jsonArray = json::parse(response);

        for (const auto& trade : jsonArray) {
            std::cout << "{\n";
            std::cout << "\"a\": " << trade["a"] << ", // Aggregate tradeId\n";
            std::cout << "\"p\": \"" << trade["p"] << "\", // Price\n";
            std::cout << "\"q\": \"" << trade["q"] << "\", // Quantity\n";
            std::cout << "\"f\": " << trade["f"] << ", // First tradeId\n";
            std::cout << "\"l\": " << trade["l"] << ", // Last tradeId\n";
            std::cout << "\"T\": " << trade["T"] << ", // Timestamp\n";
            std::cout << "\"m\": " << (trade["m"] ? "true" : "false") << ", // Was the buyer the maker?\n";
            std::cout << "}\n\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
    }
}

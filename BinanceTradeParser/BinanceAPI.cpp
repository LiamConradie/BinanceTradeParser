#include "BinanceAPI.h"
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>

using json = nlohmann::json;

/**
 * @brief Callback function used by cURL to handle incoming data.
 *
 * This function is invoked by cURL as data is received from the server. It writes the received
 * data into a string which is then returned to the caller for further processing.
 *
 * @param contents Pointer to the incoming data received by cURL.
 * @param size Size of each data block (usually 1 byte).
 * @param nmemb Number of data blocks received.
 * @param s Pointer to the string where data will be appended.
 * @return The total size of data processed (size * nmemb).
 */

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

// Fetch aggregated trades from Binance API and handle network timeouts and errors
std::string BinanceAPI::getAggregatedTrades(const std::string& symbol, long long fromId) {
    CURL* curl = curl_easy_init();
    std::ostringstream urlStream;
    urlStream << "https://fapi.binance.com/fapi/v1/aggTrades?symbol=" << symbol;

    // Add the fromId parameter if available
    if (fromId > -1) {
        urlStream << "&fromId=" << fromId;
    }

    // Set the limit to 1000 trades (the maximum allowed)
    urlStream << "&limit=1000";

    std::string url = urlStream.str();
    std::string response;

    if (curl) {
        // Set timeout for the request
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);  // Timeout after 10 seconds
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, BinanceAPI::writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Measure the time taken for the network request
        auto networkStart = std::chrono::high_resolution_clock::now();
        CURLcode res = curl_easy_perform(curl);
        auto networkEnd = std::chrono::high_resolution_clock::now();
        auto networkDuration = std::chrono::duration_cast<std::chrono::milliseconds>(networkEnd - networkStart).count();

        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            if (res == CURLE_OPERATION_TIMEDOUT) {
                std::cerr << "Error: Request timed out.\n";
            }
            curl_easy_cleanup(curl);
            return "";  // Return empty response on error
        }

        std::cout << "\nNetwork request took: " << networkDuration << " ms.\n";
        curl_easy_cleanup(curl);
    }

    return response;
}

// Parse and print the JSON response, handle invalid JSON and processing time
void BinanceAPI::printParsedResponse(const std::string& response, long long& lastSeenTradeId) {
    try {
        if (response.empty()) {
            throw std::runtime_error("Empty response received, skipping parsing.");
        }

        // Parse JSON response with error handling
        auto jsonArray = json::parse(response);
        long long firstTradeIdInBatch = -1;
        bool isFirstTrade = true;
        int batchSize = 0;  // Track the number of trades in the batch

        // Start measuring the combined time
        auto combinedStart = std::chrono::high_resolution_clock::now();

        for (const auto& trade : jsonArray) {
            batchSize++;  // Increment the batch size for each trade

            // Capture the first trade ID in the batch
            if (isFirstTrade) {
                firstTradeIdInBatch = trade["a"].get<long long>();
                isFirstTrade = false;
            }

            // Start timing the processing of each trade
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

            // Track the highest trade ID in the batch
            lastSeenTradeId = std::max<long long>(lastSeenTradeId, trade["a"].get<long long>());

            // End timing after the trade is processed
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::cout << "Trade processed in: " << duration << " microseconds.\n";
        }

        // End measuring the combined time after processing all trades
        auto combinedEnd = std::chrono::high_resolution_clock::now();
        auto combinedDuration = std::chrono::duration_cast<std::chrono::milliseconds>(combinedEnd - combinedStart).count();
        std::cout << "\nTotal Combined (Network + Processing) time for current batch: " << combinedDuration << " ms.\n";

        // Print the batch size (number of trades processed)
        std::cout << "Batch size: " << batchSize << " trades.\n";

        // Check if any trades were missed between polls
        if (firstTradeIdInBatch > lastSeenTradeId + 1) {
            long long missedTrades = firstTradeIdInBatch - (lastSeenTradeId + 1);
            std::cout << "Warning: Missed " << missedTrades << " trades between polls!\n";
        }
    }
    catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
    }
}

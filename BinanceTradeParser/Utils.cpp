#include "Utils.h"
#include <chrono>
#include <iostream>

void Utils::measureParsingSpeed(const std::string& jsonData, TradeParser& parser) {
    // TODO: Implement timing logic
    auto start = std::chrono::high_resolution_clock::now();

    // Parse the data
    auto trades = parser.parse(jsonData);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> parsingTime = end - start;

    // Calculate average time per trade
    double avgTimePerTrade = parsingTime.count() / trades.size();

    std::cout << "Parsed " << trades.size() << " trades in " << parsingTime.count() << " microseconds." << std::endl;
    std::cout << "Average time per trade: " << avgTimePerTrade << " microseconds." << std::endl;
}


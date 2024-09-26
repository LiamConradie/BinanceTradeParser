#include "Utils.h"
#include <chrono>
#include <iostream>
#include <cpprest/json.h>
#include <locale>
#include <codecvt>

void Utils::measureParsingSpeed(const std::string& jsonData, TradeParser& parser) {
    // Convert the input string into JSON
    web::json::value tradesJson = web::json::value::parse(jsonData);

    auto start = std::chrono::high_resolution_clock::now();

    // Parse the data (assuming TradeParser now returns a list of trades)
    parser.parseTrades(tradesJson);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> parsingTime = end - start;

    std::cout << "Parsing completed in " << parsingTime.count() << " microseconds." << std::endl;
}
// Define the helper function in one source file to avoid multiple definitions
std::string to_utf8_string(const utility::string_t& input) {
    std::wstring_convert<std::codecvt_utf8_utf16<utility::char_t>, utility::char_t> convert;
    return convert.to_bytes(input);
}
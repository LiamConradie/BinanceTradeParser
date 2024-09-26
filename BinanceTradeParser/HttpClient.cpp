#include "HttpClient.h"
#include "utils.h"
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <locale>
#include <codecvt>

using namespace web::http;
using namespace web::http::client;
using namespace utility;
using namespace web::json;



HttpClient::HttpClient(const std::string& base_url) : client(conversions::to_string_t(base_url)) {}

HttpClient::~HttpClient() {}

void HttpClient::pollTrades(const std::string& endpoint, std::function<void(const web::json::value&)> onTradesReceived, int interval_seconds) {
    while (true) {
        try {
            // Perform a GET request asynchronously and process the response
            client.request(web::http::methods::GET, conversions::to_string_t(endpoint))
                .then([&](web::http::http_response response) {
                std::cout << "Received response with status code: " << response.status_code() << std::endl;
                if (response.status_code() == web::http::status_codes::OK) {
                    return response.extract_json();
                }
                std::cerr << "Unexpected status code: " << response.status_code() << std::endl;
                return pplx::task_from_result(web::json::value());
                    })
                .then([&](web::json::value jsonResponse) {
                if (!jsonResponse.is_null()) {
                    // Debugging: Print the entire raw JSON response to investigate its structure
                    std::cout << "Raw JSON response: " << to_utf8_string(jsonResponse.serialize()) << std::endl;

                    // Pass the JSON response to the trade parser
                    std::cout << "Passing JSON to trade parser." << std::endl;
                    onTradesReceived(jsonResponse);
                }
                else {
                    std::cerr << "Received empty or null JSON response." << std::endl;
                }
                    }).wait();
        }
        catch (const std::exception& e) {
            std::cerr << "Error fetching trades: " << e.what() << std::endl;
        }

        // Wait for the specified interval before making the next request
        std::cout << "Waiting for " << interval_seconds << " seconds before the next request." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(interval_seconds));
    }
}



#include "HttpClient.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <pplx/pplxtasks.h>
#include <locale>
#include <codecvt>

using namespace web::http;
using namespace web::http::client;
using namespace utility; // For conversions::to_string_t
using namespace concurrency::streams;

HttpClient::HttpClient(const std::string& base_url) : client(conversions::to_string_t(base_url)) {}

HttpClient::~HttpClient() {}

pplx::task<std::string> HttpClient::get(const std::string& url) {
    // Convert std::string to utility::string_t (platform-dependent)
    utility::string_t converted_url = conversions::to_string_t(url);

    // Perform a GET request asynchronously
    return client.request(methods::GET, converted_url)
        .then([](http_response response) -> pplx::task<std::string> {
        if (response.status_code() == status_codes::OK) {
            // Extract the response as a wide string (utility::string_t, which is std::wstring on Windows)
            return response.extract_string()
                .then([](utility::string_t w_response) -> std::string {
                // Convert the std::wstring (or utility::string_t) to std::string
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
                return converter.to_bytes(w_response);
                    });
        }
        return pplx::task_from_result(std::string{});
            });
}

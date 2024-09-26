#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <string>
#include <functional>

class HttpClient {
public:
    // Constructor accepting a base URL
    HttpClient(const std::string& base_url);
    ~HttpClient();

    // Function to continuously poll the Binance API at a fixed interval
    void pollTrades(const std::string& endpoint, std::function<void(const web::json::value&)> onTradesReceived, int interval_seconds);


private:
    web::http::client::http_client client;
};

#endif // HTTPCLIENT_H


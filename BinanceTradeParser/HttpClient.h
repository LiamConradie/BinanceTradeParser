#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>

class HttpClient {
public:
    // Constructor accepting a base URL
    HttpClient(const std::string& base_url);
    ~HttpClient();

    // Perform GET request and return the response as a string
    pplx::task<std::string> get(const std::string& url);

private:
    web::http::client::http_client client;
};

#endif // HTTPCLIENT_H

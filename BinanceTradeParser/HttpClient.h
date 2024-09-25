#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    // TODO: Implement GET request method
    std::string get(const std::string& endpoint);

private:
    // TODO: Add any necessary private members for HTTP handling
};

#endif // HTTPCLIENT_H


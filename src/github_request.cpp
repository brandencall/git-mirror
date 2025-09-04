#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void sendRequest() {
    CURL *curl;
    CURLcode result;
    std::string response_data;

    std::string username = "brandencall";
    std::string url = "https://api.github.com/users/" + username + "/repos";

    curl = curl_easy_init();
    if (curl == NULL) {
        std::cerr << stderr << " HTTP request failed" << std::endl;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "C++ Github client");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (result != CURLE_OK) {
        std::cerr << "curl failed: " << curl_easy_strerror(result) << std::endl;
    }

    try {
        auto repos = json::parse(response_data);
        for (auto &repo : repos) {
            std::cout << repo["name"] << " -> " << repo["ssh_url"] << std::endl;
        }
    } catch (json::parse_error &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
}

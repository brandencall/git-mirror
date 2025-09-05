#include "Repo.h"
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <algorithm>

using json = nlohmann::json;

namespace utils_git {

static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::vector<Repo> getRepos(const std::vector<std::string> &exclude_repos) {
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
        std::vector<Repo> result;
        auto repos = json::parse(response_data);
        for (auto &repo : repos) {
            std::string repoName = repo["name"];
            if (std::find(exclude_repos.begin(), exclude_repos.end(), repoName) == exclude_repos.end()) {
                result.push_back(Repo(repoName, repo["ssh_url"]));
            }
        }
        return result;
    } catch (json::parse_error &e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    return std::vector<Repo>();
}
} // namespace utils_git

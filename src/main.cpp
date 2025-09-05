#include "utils_git/Repo.h"
#include "utils_git/github_request.h"
#include "utils_git/load_config.h"
#include <vector>

int main() {
    std::vector<std::string> excludeRepos = utils_git::loadRepoConfig("exclude_repos.conf");
    std::vector<utils_git::Repo> repos = utils_git::getRepos(excludeRepos);
    for (const auto &repo : repos) {
        repo.printRepo();
    }

    return 0;
}

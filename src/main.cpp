#include "utils_git/Repo.h"
#include "utils_git/github_request.h"
#include "utils_git/load_config.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const char *home_env = std::getenv("HOME");
    std::filesystem::path homePath = home_env;
    std::filesystem::path projectsDir = homePath / "projects";
    std::filesystem::create_directory(projectsDir);
    std::vector<std::string> excludeRepos = utils_git::loadRepoConfig("exclude_repos.conf");
    std::vector<utils_git::Repo> repos = utils_git::getRepos(excludeRepos);
    for (const auto &repo : repos) {
        std::filesystem::path repoPath = projectsDir / repo._name;
        if (!std::filesystem::is_directory(repoPath)) {
                std::string cmd = "cd " + projectsDir.string() + " && git clone " + repo._sshURL;
                std::cout << "Cloning: " << cmd << '\n';
                std::system(cmd.c_str());
        } else {
            std::string cmd = "cd " + repoPath.string() + " && git pull";
            std::cout << "Pulling: " << cmd << '\n';
            std::system(cmd.c_str());
        }
    }
    return 0;
}

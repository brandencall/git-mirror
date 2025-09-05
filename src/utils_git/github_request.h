#pragma once

#include "Repo.h"
#include <vector>
namespace utils_git {

std::vector<Repo> getRepos(const std::vector<std::string>& exclude_repos);

}

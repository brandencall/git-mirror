
#include "Repo.h"
#include <iostream>
namespace utils_git {

void Repo::printRepo() const { std::cout << "Name: " << _name << ", SSH URL: " << _sshURL << '\n'; }

} // namespace utils_git

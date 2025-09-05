#pragma once

#include <string>
namespace utils_git {
class Repo {
  public:
    std::string _name;
    std::string _sshURL;

    Repo(std::string name, std::string sshURL) : _name(name), _sshURL(sshURL) {}

    void printRepo() const;
};

} // namespace utils_git

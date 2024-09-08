#pragma once

#include <filesystem>
#include <string>
#include <cstdlib>

namespace soda
{
namespace util
{
class DirectoryFactory
{
public:
    static std::string build_path_from_home(const std::initializer_list<std::string>& directory_names);
    static std::string get_soda_dir(bool use_test_dir = false);
    static std::string get_database_dir(const std::string& database_name, bool use_test_dir = false);
    static std::string get_repository_dir(const std::string& database_name, const std::string& repository_name, bool use_test_dir = false);
private:
    static std::string get_home_dir();
    static char get_path_delim();
};

struct TestDirectoryFactory
{
    static std::string get_soda_dir();
    static std::string get_database_dir(const std::string& database_name);
    static std::string get_repository_dir(const std::string& database_name, const std::string& repository_name);
};
}
}
#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "util/DirectoryFactory.hpp"
#include "util/StringValidator.hpp"

namespace soda
{
namespace core
{
namespace api
{
namespace database
{
struct Database
{
    static void create(const std::string& name, bool use_test_dir = false);
    static void drop(const std::string& name, bool use_test_dir = false);
    static void rename(const std::string& old_name, const std::string& new_name, bool use_test_dir = false);
    static std::vector<std::string> list(bool use_test_dir = false);
    static bool check_exists(const std::string& name, bool use_test_dir) noexcept;
private:
    static bool validate_name(const std::string& name) noexcept;
};

struct TestDatabase
{
    static void create(const std::string& name);
    static void drop(const std::string& name);
    static void rename(const std::string& old_name, const std::string& new_name);
    static std::vector<std::string> list();
};
}
}
}
}

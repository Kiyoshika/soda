#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"

namespace soda
{
namespace core
{
namespace api
{
namespace repository
{
class Repository
{
private:
    typedef ::soda::core::data::schema::Schema Schema;
public:
    static void create(
        const std::string& database_name,
        const std::string& repository_name,
        const Schema& schema,
        bool use_test_dir);

    static void drop(
        const std::string& database_name,
        const std::string& repository_name,
        bool use_test_dir);

    static void rename(
        const std::string& database_name,
        const std::string& old_repository_name,
        const std::string& new_repository_name,
        bool use_test_dir);
private:
    static bool validate_name(const std::string& repository_name) noexcept;
};

class TestRepository
{
private:
    typedef ::soda::core::data::schema::Schema Schema;
public:
    static void create(
        const std::string& database_name,
        const std::string& repository_name,
        const Schema& schema);

    static void drop(
        const std::string& database_name,
        const std::string& repository_name);

    static void rename(
        const std::string& database_name,
        const std::string& old_repository_name,
        const std::string& new_repository_name);
};
}
}
}
}

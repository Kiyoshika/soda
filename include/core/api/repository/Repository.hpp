#pragma once

#include <string>
#include <vector>

#include "core/data/schema/SchemaField.hpp"

namespace soda
{
namespace core
{
namespace api
{
struct Repository
{
    static void create(
        const std::string& database_name,
        const std::string& repository_name,
        const std::vector<soda::core::data::schema::SchemaField>& schema_fields);

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
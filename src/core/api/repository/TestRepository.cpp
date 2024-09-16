#include "core/api/repository/Repository.hpp"
#include "core/data/schema/Schema.hpp"

using namespace soda::core::api::repository;
using namespace soda::core::data::schema;

void TestRepository::create(
    const std::string& database_name,
    const std::string& repository_name,
    const Schema& schema)
{
    return Repository::create(database_name, repository_name, schema, true);
}

void TestRepository::drop(
    const std::string& database_name,
    const std::string& repository_name)
{
    return Repository::drop(database_name, repository_name, true);
}

void TestRepository::rename(
    const std::string& database_name,
    const std::string& old_repository_name,
    const std::string& new_repository_name)
{
    return Repository::rename(database_name, old_repository_name, new_repository_name, true);
}

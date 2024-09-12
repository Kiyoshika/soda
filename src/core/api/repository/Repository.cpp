#include "core/api/repository/Repository.hpp"
#include "core/api/repository/Exceptions.hpp"
#include "core/api/database//Exceptions.hpp"
#include "util/DirectoryFactory.hpp"

using namespace soda::core::api::database;
using namespace soda::core::api::repository;
using namespace soda::util;

void Repository::create(
    const std::string& database_name,
    const std::string& repository_name,
    const Schema& schema,
    bool use_test_dir)
{
    std::string db_path = DirectoryFactory::get_database_dir(database_name, use_test_dir);
    if (!std::filesystem::exists(db_path))
        throw DatabaseNotFoundException(database_name);

    std::string repo_path = DirectoryFactory::get_repository_dir(database_name, repository_name, use_test_dir);
    if (std::filesystem::exists(repo_path))
        throw RepositoryAlreadyExistsException(database_name, repository_name);

    std::filesystem::create_directories(repo_path);

    std::string schema_path = DirectoryFactory::get_schema_path(database_name, repository_name, use_test_dir);
    std::ofstream schema_file(schema_path);
    if (!schema_file.is_open())
        throw RepositoryIOException(schema_path);

    schema_file << schema.to_string();
    schema_file.close();
}
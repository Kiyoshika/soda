#include "core/api/repository/Repository.hpp"
#include "core/api/repository/Exceptions.hpp"
#include "core/api/database/Database.hpp"
#include "core/api/database/Exceptions.hpp"
#include "util/DirectoryFactory.hpp"
#include "util/StringValidator.hpp"

using namespace soda::core::api::database;
using namespace soda::core::api::repository;
using namespace soda::util;

void Repository::create(
    const std::string& database_name,
    const std::string& repository_name,
    const Schema& schema,
    bool use_test_dir)
{
    if (!Database::check_exists(database_name, use_test_dir))
        throw DatabaseNotFoundException(database_name);

    if (Repository::check_exists(database_name, repository_name, use_test_dir))
        throw RepositoryAlreadyExistsException(database_name, repository_name);

    if (!Repository::validate_name(repository_name))
        throw InvalidRepositoryNameException(repository_name);

    std::string repo_path = DirectoryFactory::get_repository_dir(database_name, repository_name, use_test_dir);
    std::filesystem::create_directories(repo_path);

    std::string schema_path = DirectoryFactory::get_schema_path(database_name, repository_name, use_test_dir);
    std::ofstream schema_file(schema_path);
    if (!schema_file.is_open())
        throw RepositoryIOException(schema_path);

    schema_file << schema.to_string();
    schema_file.close();
}

void Repository::drop(
    const std::string& database_name,
    const std::string& repository_name,
    bool use_test_dir)
{
    if (!Database::check_exists(database_name, use_test_dir))
        throw DatabaseNotFoundException(database_name);

    if (!Repository::check_exists(database_name, repository_name, use_test_dir))
        throw RepositoryNotFoundException(repository_name);

    std::string path = DirectoryFactory::get_repository_dir(database_name, repository_name, use_test_dir);
    std::filesystem::remove_all(path);
}

void Repository::rename(
    const std::string& database_name,
    const std::string& old_repository_name,
    const std::string& new_repository_name,
    bool use_test_dir)
{
    if (!Repository::validate_name(new_repository_name))
        throw InvalidRepositoryNameException(new_repository_name);

    if (!Database::check_exists(database_name, use_test_dir))
        throw DatabaseNotFoundException(database_name);

    if (!Repository::check_exists(database_name, old_repository_name, use_test_dir))
        throw RepositoryNotFoundException(old_repository_name);

    if (Repository::check_exists(database_name, new_repository_name, use_test_dir))
        throw RepositoryAlreadyExistsException(database_name, new_repository_name);

    std::string old_path = DirectoryFactory::get_repository_dir(database_name, old_repository_name, use_test_dir);
    std::string new_path = DirectoryFactory::get_repository_dir(database_name, new_repository_name, use_test_dir);
    std::filesystem::rename(old_path, new_path);
}

bool Repository::check_exists(
    const std::string& database_name,
    const std::string& repository_name,
    bool use_test_dir) noexcept
{
    std::string repo_path = DirectoryFactory::get_repository_dir(database_name, repository_name, use_test_dir);
    return std::filesystem::exists(repo_path);
}

bool Repository::validate_name(const std::string& repository_name) noexcept
{
    return StringValidator::validate_alphanumeric(repository_name, { '-', '_' });    
}

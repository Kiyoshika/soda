#include "core/api/database/Database.hpp"
#include "core/api/database/DatabaseExceptions.hpp"

using namespace soda::util;
using namespace soda::core::api::database;

void Database::create(const std::string& name, bool use_test_dir)
{
    if (!Database::validate_name(name))
        throw InvalidDatabaseNameException(name);

    std::string db_path = DirectoryFactory::get_database_dir(name, use_test_dir);
    if (std::filesystem::exists(db_path))
        throw DatabaseAlreadyExistsException(name);

    std::filesystem::create_directories(db_path);
}

void Database::drop(const std::string& name, bool use_test_dir)
{
    if (!Database::validate_name(name))
        throw InvalidDatabaseNameException(name);

    std::string db_path = DirectoryFactory::get_database_dir(name, use_test_dir);
    if (!std::filesystem::exists(db_path))
        throw DatabaseNotFoundException(name);

    std::filesystem::remove_all(db_path);
}

void Database::rename(const std::string& old_name, const std::string& new_name, bool use_test_dir)
{
    if (!Database::validate_name(old_name))
        throw InvalidDatabaseNameException(old_name);

    if (!Database::validate_name(new_name))
        throw InvalidDatabaseNameException(new_name);

    std::string old_db_path = DirectoryFactory::get_database_dir(old_name, use_test_dir);
    if (!std::filesystem::exists(old_db_path))
        throw DatabaseNotFoundException(old_name);

    std::string new_db_path = DirectoryFactory::get_database_dir(new_name, use_test_dir);
    if (std::filesystem::exists(new_db_path))
        throw DatabaseAlreadyExistsException(new_name);

    std::filesystem::rename(old_db_path, new_db_path);
}

std::vector<std::string> Database::list(bool use_test_dir)
{
    std::vector<std::string> database_list;

    std::string soda_dir = DirectoryFactory::get_soda_dir(use_test_dir);
    for (const auto& entry : std::filesystem::directory_iterator(soda_dir))
    {
        const std::filesystem::path& path = entry.path();
        if (std::filesystem::exists(path))
        {
            const std::string& dir_name = path.filename().string();
            if (Database::validate_name(dir_name))
                database_list.push_back(dir_name);
        }
    }

    return database_list;
}

bool Database::validate_name(const std::string& name) noexcept
{
    return StringValidator::validate_alphanumeric(name, { '-', '_' });
}

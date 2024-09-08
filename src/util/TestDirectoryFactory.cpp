#include "util/DirectoryFactory.hpp"

using namespace soda::util;

std::string TestDirectoryFactory::get_soda_dir()
{
    return DirectoryFactory::get_soda_dir(true);
}

std::string TestDirectoryFactory::get_database_dir(const std::string& database_name)
{
    return DirectoryFactory::get_database_dir(database_name, true);
}

std::string TestDirectoryFactory::get_repository_dir(const std::string& database_name, const std::string& repository_name)
{
    return DirectoryFactory::get_repository_dir(database_name, repository_name, true);
}
#include "util/DirectoryFactory.hpp"

using namespace soda::util;

std::string DirectoryFactory::build_path_from_home(const std::initializer_list<std::string>& directory_names)
{
    std::string path = DirectoryFactory::get_home_dir() + DirectoryFactory::get_path_delim();
    for (const std::string& directory_name : directory_names)
        path += directory_name + DirectoryFactory::get_path_delim();

    return path;
}

std::string DirectoryFactory::get_home_dir()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return std::string(std::getenv("HOMEDRIVE")) + std::string(std::getenv("HOMEPATH"));
#else
    return std::string(std::getenv("HOME"));
#endif
}

char DirectoryFactory::get_path_delim()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return '\\';
#else
    return '/';
#endif
}

std::string DirectoryFactory::get_soda_dir()
{
    return DirectoryFactory::build_path_from_home({ "soda" });
}

std::string DirectoryFactory::get_database_dir(const std::string& database_name)
{
    return DirectoryFactory::build_path_from_home({ "soda", database_name });
}

std::string DirectoryFactory::get_repository_dir(const std::string& database_name, const std::string& repository_name)
{
    return DirectoryFactory::build_path_from_home({ "soda", database_name, repository_name });
}
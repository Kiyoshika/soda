#include "util/DirectoryFactory.hpp"

using namespace soda::util;

std::string DirectoryFactory::build_path_from_home(const std::vector<std::string>& directory_names, bool trailing_path_delim)
{
    std::string path = DirectoryFactory::get_home_dir() + DirectoryFactory::get_path_delim();
    if (directory_names.size() == 0)
        return path;

    std::size_t i = 0;
    for (; i < directory_names.size() - 1; ++i)
        path += directory_names[i] + DirectoryFactory::get_path_delim();

    path += directory_names[i];

    if (trailing_path_delim)
        path += + DirectoryFactory::get_path_delim();

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

std::string DirectoryFactory::get_soda_dir(bool use_test_dir)
{
    if (use_test_dir)
        return DirectoryFactory::build_path_from_home({ "soda-test" });

    return DirectoryFactory::build_path_from_home({ "soda" });
}

std::string DirectoryFactory::get_database_dir(const std::string& database_name, bool use_test_dir)
{
    if (use_test_dir)
        return DirectoryFactory::build_path_from_home({ "soda-test", database_name });

    return DirectoryFactory::build_path_from_home({ "soda", database_name });
}

std::string DirectoryFactory::get_repository_dir(const std::string& database_name, const std::string& repository_name, bool use_test_dir)
{
    if (use_test_dir)
        return DirectoryFactory::build_path_from_home({ "soda-test", database_name, repository_name });

    return DirectoryFactory::build_path_from_home({ "soda", database_name, repository_name });
}

std::string DirectoryFactory::get_schema_path(const std::string& database_name, const std::string& repository_name, bool use_test_dir)
{
    if (use_test_dir)
        return DirectoryFactory::build_path_from_home({ "soda-test", database_name, repository_name, "schema.txt" }, false);

    return DirectoryFactory::build_path_from_home({ "soda", database_name, repository_name, "schema.txt" }, false);
}
#pragma once

#include <stdexcept>
#include <string>

namespace soda
{
namespace core
{
namespace api
{
namespace repository
{
struct RepositoryAlreadyExistsException : public std::runtime_error
{
    RepositoryAlreadyExistsException(
        const std::string& database_name,
        const std::string& repository_name)
        : std::runtime_error("Repository '" + repository_name + "' in database '" + database_name + "' doesn't exist.") {}
};

struct RepositoryIOException : public std::runtime_error
{
    RepositoryIOException(const std::string& repository_path)
        : std::runtime_error("Problem writing to repository path: " + repository_path) {}
};

struct InvalidRepositoryNameException : public std::runtime_error
{
    InvalidRepositoryNameException(const std::string& name)
        : std::runtime_error("Repository name '" + name + "' is invalid. Name must be only alphanumeric characters, '-', or '_'.") {}
};

struct RepositoryNotFoundException : public std::runtime_error
{
    RepositoryNotFoundException(const std::string& name)
        : std::runtime_error("Repository '" + name + "' not found.") {}
};
}
}
}
}

#pragma once

#include <exception>
#include <string>

namespace soda
{
namespace core
{
namespace api
{
namespace database
{
struct DatabaseNotFoundException : public std::runtime_error
{
    DatabaseNotFoundException(const std::string& name) 
        : std::runtime_error("Database '" + name + "' not found.") {}
};

struct DatabaseAlreadyExistsException : public std::runtime_error
{
    DatabaseAlreadyExistsException(const std::string& name) 
        : std::runtime_error("Database '" + name + "' already exists.") {}
};

struct InvalidDatabaseNameException : public std::runtime_error
{
    InvalidDatabaseNameException(const std::string& name) 
        : std::runtime_error("Database name '" + name + "' is invalid. Name must only contain alphanumeric characters, '-' or '_'.") {}
};
}
}
}
}
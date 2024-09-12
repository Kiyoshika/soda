#pragma once

#include <stdexcept>
#include <string>

namespace soda
{
namespace core
{
namespace data
{
namespace schema
{
struct InvalidSchemaNameException : public std::runtime_error
{
    InvalidSchemaNameException(const std::string& name)
        : std::runtime_error("Schema name '" + name + "' is invalid. Name must only contain alphanumeric characters, '-' or '_'.") {}
};
}
}
}
}

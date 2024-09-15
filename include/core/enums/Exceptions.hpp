#pragma once

#include <stdexcept>
#include <string>

#include "core/enums/EDataType.hpp"

namespace soda
{
namespace core
{
namespace enums
{
struct InvalidTypeNameException : public std::runtime_error
{
    InvalidTypeNameException(const std::string& type)
        : std::runtime_error("Unknown data type '" + type + "'") {}
};

struct UnmappedTypeException : public std::runtime_error
{
    UnmappedTypeException()
        : std::runtime_error("EDataType value is not mapped to a string.") {}
};
}
}
}

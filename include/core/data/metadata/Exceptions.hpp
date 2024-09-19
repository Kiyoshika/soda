#pragma once

#include <stdexcept>
#include <string>

namespace soda
{
namespace core
{
namespace data
{
namespace metadata
{
struct ContentFileNotFoundException : public std::runtime_error
{
    ContentFileNotFoundException(const std::string& path)
        : std::runtime_error("Content file not found at path: " + path) {}
};

struct ContentParseException : public std::runtime_error
{
    ContentParseException()
        : std::runtime_error("Couldn't parse content metadata.") {}
};

struct UnknownKeyException : public std::runtime_error
{
    UnknownKeyException(const std::string& key)
        : std::runtime_error("Unknown key '" + key + "' encountered while parsing metadata.") {}
};
}
}
}
}

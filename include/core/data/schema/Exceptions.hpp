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

struct InvalidSchemaFieldNameException : public std::runtime_error
{
    InvalidSchemaFieldNameException(const std::string& name)
        : std::runtime_error("SchemaField name '" + name + "' is invalid. Name must only contain alphanumeric characters or '_'.") {}
};

struct InvalidSchemaFieldTypeException : public std::runtime_error
{
    InvalidSchemaFieldTypeException(const std::string& type)
        : std::runtime_error("Unknown SchemaField type '" + type + "'.") {}
};

struct InvalidSchemaFieldFormatException : public std::runtime_error
{
    InvalidSchemaFieldFormatException()
        : std::runtime_error("SchemaField format must be field_name:type or field_name:type?") {}
};

struct SchemaFieldNameAlreadyExistsException : public std::runtime_error
{
    SchemaFieldNameAlreadyExistsException(const std::string& name)
        : std::runtime_error("SchemaField name '" + name + "' already exists.") {}
};

struct SchemaFieldNameNotFoundException : public std::runtime_error
{
    SchemaFieldNameNotFoundException(const std::string& name)
        : std::runtime_error("SchemaField name '" + name + "' not found.") {}
};

struct SchemaIOException : public std::runtime_error
{
    SchemaIOException(const std::string& path)
        : std::runtime_error("Problem with Schema reading/writing to path: " + path) {}
};
}
}
}
}


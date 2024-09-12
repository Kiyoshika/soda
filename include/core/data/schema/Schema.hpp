#pragma once

#include <string>
#include <vector>

#include "core/data/schema/SchemaField.hpp"
#include "core/enums/EDataType.hpp"

namespace soda
{
namespace core
{
namespace data
{
namespace schema
{
class Schema
{
private:
    typedef ::soda::core::data::schema::SchemaField SchemaField;
    typedef ::soda::core::enums::EDataType EDataType;
public:
    Schema() = default;
    void add_field(const SchemaField& field) noexcept;
    // this is to be used to generate the schema.txt format
    std::string to_string() const noexcept;
private:
    std::vector<SchemaField> m_fields;
};
}
}
}
}
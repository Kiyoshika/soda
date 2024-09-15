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
    void rename_field(const std::string& old_name, const std::string& new_name);
    void change_type(const std::string& field_name, EDataType old_type, EDataType new_type);
    void remove_field(const std::string& name);

    void from_file(const std::string& path);
    void to_file(const std::string& path);

    std::string to_string() const noexcept;
private:
    std::vector<SchemaField> m_fields;
private:
    SchemaField* get_field(const std::string& field_name);
};
}
}
}
}
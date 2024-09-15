#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"
#include "core/data/schema/Exceptions.hpp"
#include "core/enums/EDataType.hpp"

using namespace soda::core::data::schema;
using namespace soda::core::enums;

void Schema::add_field(const SchemaField& field) noexcept
{
    m_fields.push_back(field);
}

void Schema::rename_field(const std::string& old_name, const std::string& new_name)
{
    SchemaField* field = get_field(new_name);
    if (field)
        throw SchemaFieldNameAlreadyExistsException(new_name);

    field->set_name(new_name);
}

void Schema::change_type(const std::string& field_name, EDataType old_type, EDataType new_type)
{
    SchemaField* field = get_field(field_name);
    if (!field)
        throw SchemaFieldNameNotFoundException(field_name);

    field->set_type(new_type);
}

void Schema::remove_field(const std::string& name)
{
    // TODO:
}

void from_file(const std::string& path)
{
    // TODO:
}

void to_file(const std::string& path)
{
    // TODO:
}

std::string Schema::to_string() const noexcept
{
    std::string str;
    for (const SchemaField& field : m_fields)
        str += field.to_string() + "\n";

    return str;
}

SchemaField* Schema::get_field(const std::string& field_name) noexcept
{
    for (auto& field : m_fields)
        if (field.get_name() == field_name)
            return &field;

    return nullptr;
}
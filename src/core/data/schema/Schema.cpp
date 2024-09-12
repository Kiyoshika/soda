#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"

using namespace soda::core::data::schema;

void Schema::add_field(const SchemaField& field) noexcept
{
    m_fields.push_back(field);
}

std::string Schema::to_string() const noexcept
{
    std::string str;
    for (const SchemaField& field : m_fields)
        str += field.to_string() + "\n";

    return str;
}
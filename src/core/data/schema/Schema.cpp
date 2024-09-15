#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"
#include "core/data/schema/Exceptions.hpp"
#include "core/enums/EDataType.hpp"

using namespace soda::core::data::schema;
using namespace soda::core::enums;

void Schema::add_field(const SchemaField& field)
{
    SchemaField* find_field = _get_field(field.get_name());
    if (find_field)
        throw SchemaFieldNameAlreadyExistsException(field.get_name());

    m_fields.push_back(field);
}

void Schema::rename_field(const std::string& old_name, const std::string& new_name)
{
    SchemaField* field = _get_field(new_name);
    if (field)
        throw SchemaFieldNameAlreadyExistsException(new_name);

    field = _get_field(old_name);
    if (!field)
        throw SchemaFieldNameNotFoundException(old_name);

    field->set_name(new_name);
}

void Schema::change_type(const std::string& field_name, EDataType new_type)
{
    SchemaField* field = _get_field(field_name);
    if (!field)
        throw SchemaFieldNameNotFoundException(field_name);

    field->set_type(new_type);
}

void Schema::remove_field(const std::string& name)
{
    SchemaField* field = _get_field(name);
    if (!field)
        throw SchemaFieldNameNotFoundException(name);

    const std::size_t idx = (field - &m_fields[0]) / sizeof(void*);
    m_fields.erase(m_fields.begin() + idx);
}

void Schema::from_file(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw SchemaIOException(path);

    m_fields.clear();

    std::string current_line;
    while (std::getline(file, current_line))
    {
        if (current_line.empty())
            continue;

        SchemaField field;
        field.parse(current_line);

        m_fields.push_back(field);
    }

    file.close();
}

void Schema::to_file(const std::string& path)
{
    std::ofstream file(path);
    if (!file.is_open())
        throw SchemaIOException(path);

    for (std::size_t i = 0; i < m_fields.size(); ++i)
    {
        file << m_fields[i].to_string();
        if (i < m_fields.size() - 1)
            file << "\n";
    }

    file.close();
}

std::string Schema::to_string() const noexcept
{
    std::string str;
    for (std::size_t i = 0; i < m_fields.size(); ++i)
    {
        str += m_fields[i].to_string();
        if (i < m_fields.size() - 1)
            str += '\n';
    }

    return str;
}

const SchemaField& Schema::get_field(const std::string& field_name)
{
    for (const auto& field : m_fields)
        if (field.get_name() == field_name)
            return field;

    throw SchemaFieldNameNotFoundException(field_name);
}

SchemaField* Schema::_get_field(const std::string& field_name) noexcept
{
    for (auto& field : m_fields)
        if (field.get_name() == field_name)
            return &field;

    return nullptr;
}

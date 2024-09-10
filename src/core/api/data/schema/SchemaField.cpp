#include "core/data/schema/SchemaField.hpp"
#include "core/enums/EDataType.hpp"

using namespace soda::core::data::schema;
using namespace soda::core::enums;

SchemaField::SchemaField(
    const std::string& name,
    EDataType type,
    bool is_nullable)
{
    if (!validate_name())
    {
        // TODO: throw InvalidSchemaFieldNameException
    }
    m_name = name;
    m_type = type;
    m_is_nullable = is_nullable;
}

// TODO: getter functions

std::string SchemaField::to_string() const noexcept
{
    std::string str = m_name + ':' + EDataTypeUtil::to_string(m_type);
    if (m_is_nullable)
        str += '?';

    return str;
}

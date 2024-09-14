#include "core/data/schema/SchemaField.hpp"
#include "core/data/schema/Exceptions.hpp"
#include "core/enums/EDataType.hpp"
#include "util/StringValidator.hpp"

#include <algorithm>

using namespace soda::core::data::schema;
using namespace soda::core::enums;
using namespace soda::util;

SchemaField::SchemaField(
    const std::string& name,
    EDataType type,
    bool is_nullable)
{
    std::string name_lower = name;
    std::transform(name_lower.begin(), name_lower.end(), name_lower.begin(), ::tolower);

    m_name = name_lower;
    m_type = type;
    m_is_nullable = is_nullable;

    if (!validate_name())
        throw InvalidSchemaFieldNameException(name);
}

const std::string& SchemaField::get_name() const noexcept
{
    return m_name;
}

EDataType SchemaField::get_type() const noexcept
{
    return m_type;
}

bool SchemaField::is_nullable() const noexcept
{
    return m_is_nullable;
}

std::string SchemaField::to_string() const noexcept
{
    std::string str = get_name() + ':' + EDataTypeUtil::to_string(get_type());
    if (is_nullable())
        str += '?';

    return str;
}

bool SchemaField::validate_name() const noexcept
{
    return StringValidator::validate_alphanumeric(get_name(), {'_'});
}

void SchemaField::parse(const std::string& str)
{
    // create a lowercase copy of str
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);

    if (lower_str.empty())
        throw InvalidSchemaFieldFormatException();

    // split the string on the first ':'
    std::string key;
    std::string value;
    for (std::size_t i = 0; i < lower_str.length(); ++i)
    {
        if (lower_str[i] == ':' && i < lower_str.length() - 1)
        {
            value = lower_str.substr(i + 1);
            break;
        }

        key += lower_str[i];
    }

    if (key.empty() || value.empty())
        throw InvalidSchemaFieldFormatException();

    m_name = key;
    if (!validate_name())
        throw InvalidSchemaFieldNameException(key);

    m_is_nullable = value[value.length() - 1] == '?';

    if (m_is_nullable)
        m_type = EDataTypeUtil::from_string(value.substr(0, value.length() - 1));
    else
        m_type = EDataTypeUtil::from_string(value);
}

#pragma once

#include <string>

#include "core/enums/EDataType.hpp"

namespace soda
{
namespace core
{
namespace data
{
namespace schema
{
class SchemaField
{
private:
    // shorten for convenience
    typedef ::soda::core::enums::EDataType EDataType;
public:
    SchemaField(
        const std::string& name,
        EDataType type,
        bool is_nullable);

    const std::string& get_name() const noexcept;
    const EDataType get_type() const noexcept;
    bool is_nullable() const noexcept;
    std::string to_string() const noexcept;


private:
    std::string m_name;
    EDataType m_type;
    bool m_is_nullable;
private:
    bool validate_name() const noexcept;
};
}
}
}
}
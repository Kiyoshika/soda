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
    typedef ::soda::core::enums::EDataType EDataType;
public:
    SchemaField() = default;

    SchemaField(
        const std::string& name,
        EDataType type,
        bool is_nullable);

    const std::string& get_name() const noexcept;
    void set_name(const std::string& name);

    EDataType get_type() const noexcept;
    void set_type(EDataType type) noexcept;


    bool is_nullable() const noexcept;
    void set_nullable(bool is_nullable) noexcept;

    void parse(const std::string& str);

    std::string to_string() const noexcept;


private:
    std::string m_name;
    EDataType m_type;
    bool m_is_nullable;
private:
    bool validate_name() const noexcept;
    bool validate_type_name(const std::string& type) const noexcept;
};
}
}
}
}

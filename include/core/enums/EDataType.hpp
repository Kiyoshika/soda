#pragma once

#include <string>
#include <utility>
#include <vector>

namespace soda
{
namespace core
{
namespace enums
{
enum class EDataType
{
    STRING,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT,
    DOUBLE,
    DATE,
    TIMESTAMP
};

class EDataTypeUtil
{
public:
    static std::string to_string(EDataType type);
    static EDataType from_string(const std::string& str);
private:
    static std::vector<std::tuple<std::string, EDataType>> m_str_type_pairs;
};
}
}
}
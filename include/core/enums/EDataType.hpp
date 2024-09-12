#pragma once

#include <string>

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
    static std::string to_string(EDataType type)
    {
        switch (type)
        {
            case EDataType::STRING:
                return "string";
            case EDataType::UINT8:
                return "uint8";
            case EDataType::UINT16:
                return "uint16";
            case EDataType::UINT32:
                return "uint32";
            case EDataType::UINT64:
                return "uint64";
            case EDataType::INT8:
                return "int8";
            case EDataType::INT16:
                return "int16";
            case EDataType::INT32:
                return "int32";
            case EDataType::INT64:
                return "int64";
            case EDataType::FLOAT:
                return "float";
            case EDataType::DOUBLE:
                return "double";
            case EDataType::DATE:
                return "date";
            case EDataType::TIMESTAMP:
                return "timestamp";
        }
    }
};
}
}
}
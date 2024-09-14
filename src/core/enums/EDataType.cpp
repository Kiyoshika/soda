#include "core/enums/EDataType.hpp"
#include "core/enums/Exceptions.hpp"

using namespace soda::core::enums;

std::vector<std::tuple<std::string, EDataType>> EDataTypeUtil::m_str_type_pairs = {
    { "string",     EDataType::STRING },
    { "uint8",      EDataType::UINT8 },
    { "uint16",     EDataType::UINT16 },
    { "uint32",     EDataType::UINT32 },
    { "uint64",     EDataType::UINT64 },
    { "int8",       EDataType::INT8 },
    { "int16",      EDataType::INT16 },
    { "int32",      EDataType::INT32 },
    { "int64",      EDataType::INT64 },
    { "float",      EDataType::FLOAT },
    { "double",     EDataType::DOUBLE },
    { "date",       EDataType::DATE },
    { "timestamp",  EDataType::TIMESTAMP }
};

EDataType EDataTypeUtil::from_string(const std::string& type)
{
    for (const auto& [key, value] : m_str_type_pairs)
        if (key == type)
            return value;

    throw InvalidTypeNameException(type);
}

std::string EDataTypeUtil::to_string(EDataType type)
{
    for (const auto& [key, value] : m_str_type_pairs)
        if (type == value)
            return key;

    throw UnmappedTypeException(type);
}

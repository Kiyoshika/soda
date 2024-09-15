#include "core/enums/EDataType.hpp"
#include "core/enums/Exceptions.hpp"

using namespace soda::core::enums;

const std::vector<std::tuple<std::string, EDataType>> EDataTypeUtil::m_str_type_pairs = {
    std::make_tuple("string", EDataType::STRING),
    std::make_tuple("uint8", EDataType::UINT8),
    std::make_tuple("uint16", EDataType::UINT16),
    std::make_tuple("uint32", EDataType::UINT32),
    std::make_tuple("uint64", EDataType::UINT64),
    std::make_tuple("int8",  EDataType::INT8),
    std::make_tuple("int16", EDataType::INT16),
    std::make_tuple("int32", EDataType::INT32),
    std::make_tuple("int64", EDataType::INT64),
    std::make_tuple("float", EDataType::FLOAT),
    std::make_tuple("double", EDataType::DOUBLE),
    std::make_tuple("date",  EDataType::DATE),
    std::make_tuple("timestamp", EDataType::TIMESTAMP)
};

EDataType EDataTypeUtil::from_string(const std::string& type)
{
    for (const auto& pair : m_str_type_pairs)
    {
        const auto& [key, value] = pair;
        if (key == type)
            return value;
    }

    throw InvalidTypeNameException(type);
}

std::string EDataTypeUtil::to_string(EDataType type)
{
    for (const auto& pair : m_str_type_pairs)
    {
        const auto& [key, value] = pair;
        if (type == value)
            return key;
    }

    throw UnmappedTypeException();
}

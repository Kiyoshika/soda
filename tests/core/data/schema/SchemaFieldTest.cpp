#include "core/data/schema/SchemaField.hpp"
#include "core/data/schema/Exceptions.hpp"
#include "core/enums/EDataType.hpp"
#include <cassert>
#include <iostream>

using namespace soda::core::data::schema;
using namespace soda::core::enums;

int main()
{
    SchemaField non_nullable("name", EDataType::STRING, false);
    assert(non_nullable.to_string() == "name:string");

    SchemaField nullable("name", EDataType::INT32, true);
    assert(nullable.to_string() == "name:int32?");

    try
    {
        SchemaField field("bad!name", EDataType::STRING, false);
        std::cerr << "Expected to throw exception for bad schema name.\n";
        return -1;
    }
    catch (const InvalidSchemaFieldNameException& ex) {}
    catch (const std::exception& ex)
    {
        std::cerr << "Expected different exception to be thrown.\n";
        return -1;
    }

    return 0;
}
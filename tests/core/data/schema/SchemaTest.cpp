#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"
#include "core/enums/EDataType.hpp"
#include <cassert>

using namespace soda::core::data::schema;
using namespace soda::core::enums;

int main()
{
    SchemaField f1("name", EDataType::STRING, false);
    SchemaField f2("name2", EDataType::INT32, true);

    Schema schema;
    schema.add_field(f1);
    schema.add_field(f2);

    assert(schema.to_string() == "name:string\nname2:int32?\n");

    return 0;
}
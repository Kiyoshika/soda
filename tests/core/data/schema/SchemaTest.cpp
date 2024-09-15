#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"
#include "core/data/schema/Exceptions.hpp"
#include "core/enums/EDataType.hpp"

#include "TestUtil.hpp"

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

    assert(schema.to_string() == "name:string\nname2:int32?");

    // ADD EXISTING NAME
    ASSERT_EXCEPTION(SchemaFieldNameAlreadyExistsException, {
        schema.add_field(f1);
    });

    // RENAME TO EXISTING NAME
    ASSERT_EXCEPTION(SchemaFieldNameAlreadyExistsException, {
        schema.rename_field("name", "name2");
    });

    // RENAME TO INVALID NAME
    ASSERT_EXCEPTION(InvalidSchemaFieldNameException, {
        schema.rename_field("name", "bad!name");
    });

    // RENAME TO VALID NAME
    ASSERT_NO_EXCEPTION({
        schema.rename_field("name", "name3");
    });

    // (after renaming 'name', it shouldn't exist anymore)
    ASSERT_EXCEPTION(SchemaFieldNameNotFoundException, {
        schema.get_field("name");
    });

    // CHANGING TYPE TO NON-EXISTANT FIELD
    ASSERT_EXCEPTION(SchemaFieldNameNotFoundException, {
        schema.change_type("noexist", EDataType::STRING);
    });

    // CHANGING TYPE OF EXISTING FIELD
    ASSERT_NO_EXCEPTION({
        schema.change_type("name3", EDataType::DOUBLE);
        assert(schema.get_field("name3").get_type() == EDataType::DOUBLE);
    });

    // REMOVING NON-EXISTANT FIELD
    ASSERT_EXCEPTION(SchemaFieldNameNotFoundException, {
        schema.remove_field("noexist");
    });
    
    // REMOVE EXISTING FIELD
    ASSERT_NO_EXCEPTION({
        schema.remove_field("name3");
    });

    // (after removing 'name', it shouldn't exist anymore)
    ASSERT_EXCEPTION(SchemaFieldNameNotFoundException, {
        schema.get_field("name3");
    });
    
    // TO STRING
    ASSERT_NO_EXCEPTION({
        schema.add_field(f1); // 'name' doesn't exist anymore so we can add it back
        assert(schema.to_string() == "name2:int32?\nname:string");
    });

    return 0;
}

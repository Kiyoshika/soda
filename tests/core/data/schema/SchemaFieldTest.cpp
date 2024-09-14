#include "core/data/schema/SchemaField.hpp"
#include "core/data/schema/Exceptions.hpp"
#include "core/enums/EDataType.hpp"
#include "core/enums/Exceptions.hpp"

#include "TestUtil.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace soda::core::data::schema;
using namespace soda::core::enums;

int main()
{
    SchemaField non_nullable("name", EDataType::STRING, false);
    assert(non_nullable.get_name() == "name");
    assert(non_nullable.get_type() == EDataType::STRING);
    assert(non_nullable.is_nullable() == false);
    assert(non_nullable.to_string() == "name:string");

    SchemaField case_insensitive("NAME", EDataType::STRING, false);
    assert(case_insensitive.get_name() == "name");
    assert(case_insensitive.get_type() == EDataType::STRING);
    assert(case_insensitive.is_nullable() == false);
    assert(case_insensitive.to_string() == "name:string");

    SchemaField nullable("name", EDataType::INT32, true);
    assert(nullable.get_name() == "name");
    assert(nullable.get_type() == EDataType::INT32);
    assert(nullable.is_nullable() == true);
    assert(nullable.to_string() == "name:int32?");

    ASSERT_EXCEPTION(InvalidSchemaFieldNameException, {
        SchemaField field("bad!name", EDataType::STRING, false);
    });

    SchemaField field;
    ASSERT_EXCEPTION(InvalidSchemaFieldFormatException, {
        field.parse("");
    });

    ASSERT_EXCEPTION(InvalidSchemaFieldFormatException, {
        field.parse("name:");
    });

    ASSERT_EXCEPTION(InvalidSchemaFieldFormatException, {
        field.parse(":value");
    });

    ASSERT_EXCEPTION(InvalidSchemaFieldFormatException, {
        field.parse("name");
    });

    /*
    The following macros VALIDATE_FIELD and VALIDATE_PARSE just help removing tons of copy-paste code
    to keep the test file readable.

    Essentially all we're doing is creating four test cases per data type where we check:
    - name:type
    - name:type?
    - NAME:TYPE
    - NAME:TYPE?

    And validate all the settings (name, type, nullable) are correct in each case.
    */
#define VALIDATE_FIELD(var, expected_name, expected_type, expected_nullable){\
        assert(var.get_name() == expected_name); \
        assert(var.get_type() == expected_type); \
        assert(var.is_nullable() == expected_nullable); \
    }

#define VALIDATE_PARSE(var, lower_type, upper_type){\
    var.parse("name:" #lower_type);\
    VALIDATE_FIELD(var, "name", EDataType::upper_type, false);\
    var.parse("name:" #lower_type "?");\
    VALIDATE_FIELD(var, "name", EDataType::upper_type, true);\
    var.parse("NAME:" #upper_type);\
    VALIDATE_FIELD(var, "name", EDataType::upper_type, false);\
    var.parse("NAME:" #upper_type "?");\
    VALIDATE_FIELD(var, "name", EDataType::upper_type, true);\
}

    ASSERT_NO_EXCEPTION({
        VALIDATE_PARSE(field, string, STRING);
        VALIDATE_PARSE(field, uint8, UINT8);
        VALIDATE_PARSE(field, uint16, UINT16);
        VALIDATE_PARSE(field, uint32, UINT32);
        VALIDATE_PARSE(field, uint64, UINT64);
        VALIDATE_PARSE(field, int8, INT8);
        VALIDATE_PARSE(field, int16, INT16);
        VALIDATE_PARSE(field, int32, INT32);
        VALIDATE_PARSE(field, int64, INT64);
        VALIDATE_PARSE(field, float, FLOAT);
        VALIDATE_PARSE(field, double, DOUBLE);
        VALIDATE_PARSE(field, date, DATE);
        VALIDATE_PARSE(field, timestamp, TIMESTAMP);
    });

    ASSERT_EXCEPTION(InvalidSchemaFieldNameException, {
        field.parse("bad!name:int8");
    });

    ASSERT_EXCEPTION(InvalidTypeNameException, {
        field.parse("name:unknowntype");
    });
    
    return 0;
}
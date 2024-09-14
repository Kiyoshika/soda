#include "core/api/repository/Repository.hpp"
#include "core/api/repository/Exceptions.hpp"

#include "core/api/database/Database.hpp"
#include "core/api/database/Exceptions.hpp"

#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"

#include "core/enums/EDataType.hpp"

#include "util/DirectoryFactory.hpp"

#include "TestUtil.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace soda::core::data::schema;
using namespace soda::core::api::repository;
using namespace soda::core::api::database;
using namespace soda::core::enums;
using namespace soda::util;

int main()
{
    Schema schema;
    schema.add_field(SchemaField("name", EDataType::STRING, false));
    schema.add_field(SchemaField("name2", EDataType::INT32, true));

    TestDatabase::create("testdb");

    // CREATE REPO WITHOUT EXISTING DB
    ASSERT_EXCEPTION(DatabaseNotFoundException, {
        TestRepository::create("mydb", "myrepo", schema);
    });

    // CREATE REPO WITH VALID DB
    ASSERT_NO_EXCEPTION({
        TestRepository::create("testdb", "myrepo", schema);
        assert(std::filesystem::is_directory(DirectoryFactory::build_path_from_home({ "soda-test", "testdb", "myrepo" })) == true);

        std::string schema_path = DirectoryFactory::build_path_from_home({ "soda-test", "testdb", "myrepo", "schema.txt" }, false);
        assert(std::filesystem::exists(schema_path) == true);

        // TODO: replace this raw read with Schema.from_file() and .to_string() to validate
        std::ifstream schema_file(schema_path);
        if (!schema_file.is_open())
        {
            std::cerr << "Couldn't open schema file '" << schema_path << "'.\n";
            return -1;
        }
        std::stringstream schema_stream;
        schema_stream << schema_file.rdbuf();
        std::string schema_content = schema_stream.str();

        schema_file.close();

        assert(schema_content == "name:string\nname2:int32?\n");
    });

    std::cerr << "FINISH REMAINING TESTS\n";
    return -1;

    // CREATE REPO WITH INVALID NAME

    // CREATE DUPLICATE REPO NAME IN SAME DB

    // CREATE SAME REPO NAME IN SEPARATE DBs

    return 0;
}
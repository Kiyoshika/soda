#include "core/api/repository/Repository.hpp"
#include "core/api/repository/Exceptions.hpp"

#include "core/api/database/Database.hpp"
#include "core/api/database/Exceptions.hpp"

#include "core/data/schema/Schema.hpp"
#include "core/data/schema/SchemaField.hpp"

#include "core/data/metadata/ContentMetadata.hpp"

#include "core/enums/EDataType.hpp"

#include "util/DirectoryFactory.hpp"

#include "TestUtil.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace soda::tests;
using namespace soda::core::data::schema;
using namespace soda::core::data::metadata;
using namespace soda::core::api::repository;
using namespace soda::core::api::database;
using namespace soda::core::enums;
using namespace soda::util;

int main()
{
    teardown();

    Schema schema;
    schema.add_field(SchemaField("name", EDataType::STRING, false));
    schema.add_field(SchemaField("name2", EDataType::INT32, true));

    TestDatabase::create("testdb");
    TestDatabase::create("testdb-2");

    // CREATE REPO WITHOUT EXISTING DB
    ASSERT_EXCEPTION(DatabaseNotFoundException, {
        TestRepository::create("mydb", "myrepo", schema);
    });

    // CREATE REPO WITH VALID DB
    std::string schema_path;
    std::string content_path;
    ASSERT_NO_EXCEPTION({
        TestRepository::create("testdb", "myrepo", schema);
        assert(std::filesystem::is_directory(DirectoryFactory::build_path_from_home({ "soda-test", "testdb", "myrepo" })) == true);

        schema_path = DirectoryFactory::build_path_from_home({ "soda-test", "testdb", "myrepo", "schema.txt" }, false);
        assert(std::filesystem::exists(schema_path) == true);
        
        content_path = DirectoryFactory::build_path_from_home({ "soda-test", "testdb", "myrepo", "content.txt" }, false);
        assert(std::filesystem::exists(content_path) == true);

        
    });

    // READ CREATED SCHEMA FROM API
    ASSERT_NO_EXCEPTION({
        Schema read;
        read.from_file(schema_path);
        assert(read.to_string() == "name:string\nname2:int32?");
    });

    // READ CONTENT METADATA AFTER SCHEMA IS SUCCESSFULLY CREATED
    ASSERT_NO_EXCEPTION({
        ContentMetadata metadata;
        metadata.from_file(content_path);

        assert(metadata.get_rows() == 0);
        assert(metadata.get_next_id() == 1);
        assert(metadata.get_repo_relationships().size() == 0);
    });

    // CREATE REPO WITH INVALID NAME
    ASSERT_EXCEPTION(InvalidRepositoryNameException, {
        TestRepository::create("testdb", "bad..name", schema);
    });

    // CREATE REPO WITH EXISTING NAME
    ASSERT_EXCEPTION(RepositoryAlreadyExistsException, {
        TestRepository::create("testdb", "myrepo", schema);
    });


    // CREATE SAME REPO NAME IN SEPARATE DBs
    ASSERT_NO_EXCEPTION({
        TestRepository::create("testdb-2", "myrepo", schema);
    });

    teardown();

    return 0;
}

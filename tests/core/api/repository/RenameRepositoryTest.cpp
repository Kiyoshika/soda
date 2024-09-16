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
#include <filesystem>

using namespace soda::tests;
using namespace soda::core::api::database;
using namespace soda::core::api::repository;
using namespace soda::core::data::schema;
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

    // RENAME NON-EXISTING REPOSITORY
    ASSERT_EXCEPTION(RepositoryNotFoundException, {
        TestRepository::rename("testdb", "noexist", "noexist2");
    });


    // RENAME VALID REPOSITORY
    ASSERT_NO_EXCEPTION({
        TestRepository::create("testdb", "myrepo", schema);
        TestRepository::rename("testdb", "myrepo", "newrepo");
        assert(std::filesystem::exists(TestDirectoryFactory::get_repository_dir("testdb", "myrepo")) == false);
        assert(std::filesystem::exists(TestDirectoryFactory::get_repository_dir("testdb", "newrepo")) == true);
    });

    // RENAME TO INVALID NAME
    ASSERT_EXCEPTION(InvalidRepositoryNameException, {
        TestRepository::rename("testdb", "newrepo", "bad!name");
    });

    // RENAME TO EXISTING REPOSITORY
    ASSERT_EXCEPTION(RepositoryAlreadyExistsException, {
        TestRepository::create("testdb", "anotherrepo", schema);
        TestRepository::rename("testdb", "anotherrepo", "newrepo");
    });
        
    teardown();
    return 0;
}


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

    // DROP FROM NON-EXISTING DB
    ASSERT_EXCEPTION(DatabaseNotFoundException, {
        TestRepository::drop("noexist", "repo");
    });

    // DROP NON-EXISTING REPO
    ASSERT_EXCEPTION(RepositoryNotFoundException, {
        TestRepository::drop("testdb", "noexist");
    });

    // DROP VALID REPO
    ASSERT_NO_EXCEPTION({
        TestRepository::create("testdb", "testrepo", schema);
        TestRepository::drop("testdb", "testrepo");
        assert(std::filesystem::exists(TestDirectoryFactory::get_repository_dir("testdb", "testrepo")) == false);
    });
    
    teardown();
    return 0;
}


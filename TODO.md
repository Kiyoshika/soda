# TODO
General todo items, in no particular order

## SchemaTest
* Implement tests for new Schema methods

## Repository API
* Implement remaining repository API functions
* When schema is created, create the page0.txt with metadata (and a PageMetadata structure with `parser`/`to_string` etc)

## CreateRepositoryTest
* Replace ifstream read with `Schema::from_file()` and `Schema::to_string()` for validating schema content
* Finish remaining tests

## DirectoryFactory
* Add a static constant for the main and test database path instead of hard coding it everywhere

## EDataTypeTest
* Add tests on converting from and to string/enum types
	* Exceptions are thrown if a str to enum or enum to str mapping is not found in vector tuple

## EDataType
* Add a `TIME` data type

# TODO
General todo items, in no particular order

## Schema
* Add `from_file()` method in parse schema from file
* Add `rename_field()` method to rename a field
* Add `change_type()` method to change field datatype
* Add `remove_field()` method to remove a field
* Throw exception when adding field with existing name
* Add a test to check for duplicate field names

## Repository API
* Implement remaining repository API functions
* When schema is created, create the page0.txt with metadata (and a PageMetadata structure with parser/to_string etc)

## CreateRepositoryTest
* Replace ifstream read with `Schema::from_file()` and `Schema::to_string()` for validating schema content
* Finish remaining tests

## DirectoryFactory
* Add a static constant for the main and test database path instead of hard coding it everywhere

## EDataTypeTest
* Add tests on converting from and to string/enum types
	* Exceptions are thrown if a str->enum or enum->str mapping is not found in vector tuple

## EDataType
* Add a `TIME` data type

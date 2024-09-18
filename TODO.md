# TODO
General todo items, in no particular order

## Repository API
* Add methods to insert/remove/edit records

## DirectoryFactory
* Add a static constant for the main and test database path instead of hard coding it everywhere
* Add `build_dir_path_from_home` and `build_file_path_from_home` to avoid passing the booleans in `build_path_from_home` to make it more clear

## EDataTypeTest
* Add tests on converting from and to string/enum types
	* Exceptions are thrown if a str to enum or enum to str mapping is not found in vector tuple

## EDataType
* Add a `TIME` data type
* Add support for array types, e.g., `int32[]` (can also be nullable)
* Add support for custom/object types (e.g., the type is another object - this will be handled much later, though)

# SODA - SQL Object Relational Database
This is an object relational database that uses familiar SQL syntax to interact with.

Instead of storing data as rows and columns, data is stored as general "objects" which is a set of properties.

Objects can be "joined" which will concatenate their properties together or there can be dependencies defined which will create nested objects (i.e., an object's property can be another object.)

For more information, see the [design](DESIGN.md) doc.

## Building
This is a standard CMake project. You can configure the following CMake flags when building:
* `DEBUG_MODE` (default: `OFF`)
* `COMPILE_TESTS` (default: `OFF`)

For example:
* `mkdir build && cd build`
* `cmake -DDEBUG_MODE=ON -DCOMPILE_TESTS=ON ..`
* `make`
* `make test` (run all CMake tests)

Or configure your IDE to add the CMake flags.

## Usage
TODO:

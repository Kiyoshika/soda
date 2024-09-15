# SODA - SQL Object Relational Database
This is an object relational database that uses familiar SQL syntax to interact with.

Instead of storing data as rows and columns, data is stored as general "objects" which is a set of properties.

Objects can be "joined" which will concatenate their properties together or there can be dependencies defined which will create nested objects (i.e., an object's property can be another object.)

For more information, see the [design](DESIGN.md) doc.

## Components
There are the major components that make up this database (some are not yet implemented):

### API
This is the communication layer that allows interaction with the underlying filesystem.

An API is built for each of the main services such as a database API, repository API, etc. to support the fundamental operations such as creating/removing/renaming and, in general, interacting with the underlying data on the server.

Both the engine and the CLI would communicate with the API to perform operations on the database - this way, we don't have to duplicate implementations and instead use this "communication layer."

### Engine
This is the primary "SQL Engine" which is responsible for taking a query, parsing it and translating it into instructions that can be passed to the corresponding database/repository API to interact with the underlying data - whether it be fetching or updating records, modifying a schema or creating a new database.

### CLI (Command Line Interface)
This is the primary "front end" to communicate with the database/repository API as a user. 

There will be basic built-in commands to handle common operations such as creating/modifying databases/repositories and also allow the execution of SQL and printing or logging the output into a file.

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

# SODA Design
## How data is stored
On first usage, a `soda` directory will be created in the user's home directory: `~/soda`.

Creating a new database will create a subdirectory, e.g., `~/soda/mydb`.

Instead of "tables", data is stored in "repositories"
* A `repositories` directory will also be created: `~/soda/mydb/repositories`.
* When creating a new repository, it will be created as a subdirectory: `~/soda/mydb/repositories/my_repository`
* Each repository has a `schema.txt` file which defines the properties and datatypes for each property

## Repositories
### Definition
A repository represents **one** object entity. For instance, a person repository:
```
// ~/soda/mydb/repositories/person/schema.txt
name:string
age:uint8
```

All records are stored in one file named `content.txt` within the repository for now. It needs to be benchmarked whether this or reading smaller pages on multiple threads is faster depending on storage type, architecture, etc.
Some example records:
```
// ~/soda/mydb/repositories/person/content.txt
rows:3,nextid:4,relationships:
_id:1,name:"zach",age:25
_id:2,name:"josh",age:30
_id:3,name:"christopher",age:21
```

Every repository contains some basic metadata at the top of the file:
* `rows` stores the current row count
* `nextid` stores the next unique ID for a new record
* `relationships` a (possibly empty) pipe `|` delimited list of repositories that are a dependency to this repository

Every record starts with an `_id` field which is a `uint64` to uniquely identify a record. In the (very) rare event that `nextid` equals `2^64 - 1`, all IDs will be "rebalanced" starting from `1`. If the records contain dependencies on other repositories, those will be searched so the ID can be updated in the other repositories as well to maintain the proper mapping.

The top of the content contains metadata about the number of rows. Ideally, this data should be compressed due to many repeated values for the keys.

The format of the data itself is similar to a CSV format but with key value pairs instead of raw values. This is to support arbitrary changes in the schema.

### Modifying Schema
If we decide we no longer want the age field and drop it from the schema, all records will be rewritten to prevent orphaned fields and any indexes using the deleted field will also be invalidated and deleted.

When adding a new field to a schema, there are some considerations to make:
* If we add a nullable field, e.g., `salary:double?` - this will simply add the new field to all new or updated records. Querying older records will show `salary` is null
* If we add a non-nullable field, e.g., `salary:double` - this will require a default value to be provided if the repository is non-empty otherwise an error will be thrown

Below is an example if we added a new nullable field, `salary:double?` to the schema and inserted a new record with the new field.

```
// ~/soda/mydb/repositories/person/content.txt
rows:4,nextid:5,relationships:
_id:1,name:"zach",age:25
_id:2,name:"josh",age:30
_id:3,name:"christopher",age:21
_id:4,name:"kyle",age:23,salary:65784.12
```

Since it's nullable, the older records don't contain the property and would display `null` for `salary` when querying them.

We can also update older records to add the new field if needed:
```sql
UPDATE person
SET salary = 12345.10
WHERE name = 'zach'
AND age = 25;
```

Which will append the salary:
```
// ~/soda/mydb/repositories/person/content.txt
rows:4,nextid:5,relationships:
_id:1,name:"zach",age:25,salary:12345.10
_id:2,name:"josh",age:30
_id:3,name:"christopher",age:21
_id:4,name:"kyle",age:23,salary:65784.12
```

Trying to insert a field not defined in the schema results in an error:
```sql
/* errors because 'somefield' isn't defined */
UPDATE person
SET somefield = 'hello'
WHERE name = 'zach'
AND age = 25;
```

This makes a repository flexible to schema changes, but not so flexible where you introduce unexpected data.

### Querying
When querying repositories, you can select any field defined in the schema. If records don't contain a value, they will have `null` attached:
```sql
SELECT * FROM person
```

Returns:
```json
[
    {
        "name": "zach",
        "age": 25,
        "salary": 12345.10
    },

    {
        "name": "josh",
        "age": 30,
        "salary": null
    },

    {
        "name": "christopher",
        "age": 21,
        "salary": null
    },

    {
        "name": "kyle",
        "age": 23,
        "salary": 65784.12
    }
]
```

### Dependent Repositories
Often, we'll have objects that depend on each other. For instance, let's say we have a `cart`, `product` and `cart_item` repository representing a shopping cart and a product in an e-commerce context. We might have the following schemas:
```
// ~/soda/mydb/repositories/product/schema.txt
name:string
category:string
price:double

// ~/soda/mydb/repositories/cart_item/schema.txt
product:product
quantity:uint32

// ~/soda/mydb/repositories/cart/schema.txt
username:string
products:cart_item[]
total_price:double
```

We can see that `cart_item` is a tuple containing a `product` and a quantity, and `cart` has an array of `cart_item`s.

Some example records:
```
// ~/soda/mydb/repositories/product/content.txt
rows:2,nextid:3,relationships:
_id:1,name:"keyboard",category:"tech",price:100.00
_id:2,name:"mouse",category:"tech",price:32.12

// ~/soda/mydb/repositories/cart_item/content.txt
rows:3,nextid:4,relationships:product
_id:1,product:product:1,quantity:2
_id:2,product:product:1,quantity:1
_id:3,product:product:2,quantity:1

// ~/soda/mydb/repositories/cart/content.txt
rows:2,nextid:3,relationships:cart_item
_id:1,username:"zach",products:[cart_item:1],total_price:200.00
_i2:2,username:"john",products:[cart_item:2,cart_item:3],total_price:132.12
```

In the `cart_item` records, `product:1` refers to a `product` object for `_id:1`.

It's important to update all IDs associated with an object when they change (e.g., due to rebalancing or deletions.) This is why the `relationships` metatadata exists to know exactly which repositories have direct dependencies to ensure the mappings are correctly preserved upon changes.

If an object record is deleted, the corresponding relationship will be removed. In the above example, we have `products:[cart_item:1]` - however, if we deleted the first cart item (e.g., customer removed that item from their cart), we would find this `cart_item:1` reference and remove it, reducing it to `products:[]` a now empty array.

Querying data with dependent objects will result in nested data. See the following query:
```sql
SELECT * from cart
```

Result:
```json
[
    {
        "username": "zach",
        "products: [
            {
                "product: {
                    "name": "keyboard",
                    "category": "tech",
                    "price": 100.00
                },
                "quantity": 2
            }
        ],
        "total_price": 200.00
    },

    {
        "username": "john",
        "products": [
            {
                "product": {
                    "name": "keyboard",
                    "category": "tech",
                    "price": 100.00
                },
                "quantity": 1
            },

            {
                "product": {
                    "name": "mouse",
                    "category": "tech",
                    "price": 32.12
                },
                "quantity": 1
            }
        ],
        "total_price": 132.12
    }
]
```
### Joining Objects in SQL
In cases where we want to join objects together via query but not necessarily define dependencies between then, we can use joins. Consider the following schemas:
```
// ~/soda/mydb/repositories/product/schema.txt
name:string

// ~/soda/mydb/repositories/product_detail/schema.txt
product_name:string
weight:double
category:string
```

We can join these two schemas like so:
```sql
SELECT p.*, pd.weight, pd.category FROM product AS p
INNER JOIN product_detail AS pd
ON p.name = pd.product_name
```

Result:
```json
[
    {
        "name": "<name>",
        "weight": <weight>,
        "category": "<category>"
    },

    {
        "name": "<name>",
        "weight": <weight>,
        "category": "<category>"
    },

    ...
]
```

We can see that joining repositories will combine the fields into one object, whereas defining dependencies will create nested objects.

When using left/right joins, all fields that can't be matched will result in `null` similar to how a regular relational database operates.

### Indexing
By default, scanning data will start from the beginning of the file to the end. For instance, if we are applying a simple filter:
```sql
SELECT * FROM repository
WHERE field = 'hello'
```

This will scan every row linearly checking if every record's `field` value is `hello`.

It may be helpful to create an index for `field`.

When creating an index, a new directory called `indexes` will be created in the given repository. This will contain files of the format: `<field1>-<field2>-...-<fieldN>.txt` where each field name in the list is *sorted ascending*.

For each index, we have a file containing the sorted indexed field values (concatenated) along with a pointer to the original row of data (which may be *different* than the `_id`) so we can seek to the exact position the record is.

```
// ~/soda/mydb/repositories/example/content.txt
rows:4,nextid:5,relationships:
_id:1,value:"hello"
_id:2,value:"goodbye"
_id:3,value:"sandwich"
_id:4,value:"hello"

// ~/soda/mydb/repositories/example/indexes/value.txt
"goodbye",2
"hello",1
"hello",4
"sandwich",3
```

In this example, if we run the query from the beginning of the section, we can binary search and find our record is in rows 1 and 4 of the original data.

For a composite key, the index concatenates values into one string in the order specified in the file name.

```
// ~/soda/mydb/repositories/example/content.txt
rows:4,nextid:5,relationships:
_id:1,value:"hello",num:3
_id:2,value:"goodbye",num:1
_id:3,value:"sandwich",num:5
_id:4,value:"hello",num:1

// ~/soda/mydb/repositories/example/num-value.txt
1"goodbye",2
1"hello",4
3"hello",1
5"sandwich",3
```

The index is created on `value` and `num` which concatenates their values together as a string. Then if we have the query:
```sql
SELECT * FROM example
WHERE value = 'hello' AND num = 1
```

It will check if the index `num-value.txt` exists, read the contents, perform a binary search and return the records the index points to.

Note that if we have multiple filter conditions, we'd have to find the index that uses the most composite keys we can.

It's important that any updates or deletions to a repository MUST be reflected in the appropriate indexes. Especially if we have overlapping ones (e.g., `value.txt` and `num-value.txt` - both of these would have to be updated.) This causes a tradeoff between creating many indexes to optimize read time versus slower update/insert/delete times.


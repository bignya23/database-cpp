# Database-Cpp

A lightweight relational database engine written in C++ with support for a **command-line interface (CLI)** to handle SQL-like commands. This project currently supports:
- Creating tables with specified schemas.
- Inserting rows into tables.

The database engine uses a **B+ Tree** as its underlying data structure for efficient key-value storage.

---

## Features

1. **CREATE TABLE**:
   - Create a new table with a specified schema.
   - Example:
     ```sql
     CREATE TABLE tablename (id INT, name STRING, email STRING);
     ```

2. **INSERT INTO**:
   - Insert a row into a table.
   - Example:
     ```sql
     INSERT INTO tablename (1, Ravi, ravi@example.com);
     INSERT INTO tablename (2, John, john@example.com);
     ```
3. **SHOW ENTRIES**:
   - Show all the entries that is present in that particular table
     ```bash
     SHOW ENTREIS FROM tablename
3. **B+ Tree Integration**:
   - Tables are stored as `B+ Tree` structures for efficient data management and retrieval.



## Getting Started

### Prerequisites
- A C++ compiler supporting C++17 or later (e.g., g++, clang, MSVC).
- [CMake](https://cmake.org/) for build automation (optional).



### Building the Project

#### Using CMake:
1. Clone the repository:
   ```bash
   git clone https://github.com/bignya23/database-cpp.git
   cd database-cpp
   ```
2. Create a build directory and build:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the executable:
   ```bash
   ./database-cpp
   ```



## Contributing

Contributions are Welcome! Fork the repo and submit pull requests.



## License

This project is licensed under the [MIT License](LICENSE.txt).

---



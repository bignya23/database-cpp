# Database-Cpp

A lightweight relational database engine written in C++ with support for a **command-line interface (CLI)** to handle SQL-like commands. This project currently supports:
- Creating tables with specified schemas.
- Inserting rows into tables.

The database engine uses a **B+ Tree** as its underlying data structure for efficient key-value storage.

---

## Features

### Current Functionality
1. **CREATE TABLE**:
   - Create a new table with a specified schema.
   - Example:
     ```sql
     CREATE TABLE Users (id INT, name STRING, email STRING);
     ```

2. **INSERT INTO**:
   - Insert a row into a table.
   - Example:
     ```sql
     INSERT INTO Users (1, "Alice", "alice@example.com");
     INSERT INTO Users (2, "Bob", "bob@example.com");
     ```

3. **B+ Tree Integration**:
   - Tables are stored as `B+ Tree` structures for efficient data management and retrieval.

---

## Getting Started

### Prerequisites
- A C++ compiler supporting C++17 or later (e.g., g++, clang, MSVC).
- [CMake](https://cmake.org/) for build automation (optional).

---

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

---

### Example Usage

1. Start the CLI by running the built executable.
2. Enter the following commands:

#### Creating a Table
```plaintext
CREATE TABLE Users (id INT, name STRING, email STRING);
```

#### Inserting Rows
```plaintext
INSERT INTO Users (1, "Alice", "alice@example.com");
INSERT INTO Users (2, "Bob", "bob@example.com");
```


## Contributing

Contributions are Welcome! Fork the repo and submit pull requests.



## License

This project is licensed under the [MIT License](LICENSE).

---



#include <iostream>
#include <sqlite3.h> // Include the SQLite header file

int main() {
    sqlite3* db; // Declare a pointer to SQLite database

    // Open a connection to the SQLite database
    int rc = sqlite3_open("database.db", &db);

    // Check if the connection was successful
    if (rc) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "SQLite database connected successfully!" << std::endl;
    }

    // Further database operations (e.g., create table, insert data, query, etc.) would go here

    // Close the database connection when done
    sqlite3_close(db);

    return 0;
}

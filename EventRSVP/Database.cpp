#include "Database.h"
#include <iostream>

Database::Database() : Database("events.db") {}

Database::Database(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "❌ Error opening DB: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
    else {
        std::cout << "✅ Database connected!" << std::endl;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        std::cout << "🔒 Database closed." << std::endl;
    }
}

bool Database::execute(const std::string& query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "⚠️ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg); 
        return false;
    }
    return true;
}

bool Database::addGuest(const std::string& name, bool rsvp) {
    if (!db) return false; 

    std::string query =
        "INSERT INTO Guests (name, attending) VALUES ('" + name + "', " +
        std::to_string(rsvp ? 1 : 0) + ");";

    return execute(query);
}
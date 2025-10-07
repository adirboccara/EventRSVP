#include "Database.h"
#include <iostream>

Database::Database() : Database("events.db") {}

Database::Database(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
    else {
        std::cout << "Database connected!" << std::endl;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Database closed." << std::endl;
    }
}

bool Database::execute(const std::string& query) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
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

void Database::getAllGuests() {
    std::string query = "SELECT id, name, attending FROM Guests;";
    sqlite3_stmt* stmt;   

    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "\nGuest List:\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);                    
        const unsigned char* name = sqlite3_column_text(stmt, 1); 
        int attending = sqlite3_column_int(stmt, 2);             

        std::cout << "ID: " << id
            << " | Name: " << name
            << " | Attending: " << (attending ? "Yes" : "No")
            << std::endl;
    }
    sqlite3_finalize(stmt);
}

bool Database::updateRSVP(int id, bool rsvp) {
    if (!db) return false;

    std::string sql = "UPDATE Guests SET attending = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, rsvp ? 1 : 0);
    sqlite3_bind_int(stmt, 2, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to update RSVP: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "RSVP updated for guest ID " << id << std::endl;
    return true;
}

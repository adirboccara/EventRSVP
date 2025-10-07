#pragma once
#include <string>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;
public:
    Database();
    Database(const std::string& dbName);
    ~Database();


    bool execute(const std::string& query);
    bool addGuest(const std::string& name, bool rsvp);
    void getAllGuests();
    bool updateRSVP(int id, bool rsvp);


};

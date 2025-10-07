#include "Database.h"
#include <iostream>

int main() {
    Database db("events.db");

    // נוודא שהטבלה קיימת
    db.execute(
        "CREATE TABLE IF NOT EXISTS Guests ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "attending INTEGER"
        ");"
    );

    // נוסיף אורחים
    db.addGuest("Adir Boccara", true);
    db.addGuest("Hodaya Liebovich", false);
    db.addGuest("Howard Freedberg", true);

    std::cout << "✅ Guests added successfully!" << std::endl;

    return 0;
}


#include "Database.h"
#include "ApiHandler.h"

int main() {
    Database db("event.db");
    ApiHandler api;

    db.execute("CREATE TABLE IF NOT EXISTS Guests ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT, "
        "phone TEXT, "
        "attending INTEGER);");

    db.addGuest("Adir Boccara", "0541234567", true);
    db.addGuest("Hodaya Liebovich", "0549876543", false);

    db.getAllGuests();
    api.sendInvitations(db);

    return 0;
}

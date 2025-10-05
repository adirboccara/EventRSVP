#include <iostream>
#include "Event.h"
#include "WhatsAppAPI.h"

int main() {
    Event wedding("Adir & Hodaya Wedding");

    // ניצור אורחים
    Guest g1("Yarin Arama", "972502222222");
    Guest g2("Ilay Weizman", "972503333333");
    Guest g3("Hodaya Leibovitz", "972504444444");

    // נוסיף אותם לרשימת האורחים
    wedding.addGuest(g1);
    wedding.addGuest(g2);
    wedding.addGuest(g3);

    // ניצור את מערכת הוואטסאפ
    WhatsAppAPI api;

    // נשלח לכולם הודעה אחידה
    wedding.sendInvitations(api);

    return 0;
}

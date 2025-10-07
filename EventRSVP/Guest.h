#ifndef GUEST_H
#define GUEST_H

#include <string>

class Guest {
private:
    std::string name;
    std::string phone;
    bool attending;
    int numGuests;
    bool needTransport;
    std::string transportLoc;

public:
    Guest(std::string name, std::string phone);

    void confirmAttendance(int guests, bool wantsTransportation, std::string transportLoc);

    void print() const;

    std::string getPhone() const { return phone; }

    std::string getName() const { return name; }

    bool isAttending() const { return attending; }

};

#endif

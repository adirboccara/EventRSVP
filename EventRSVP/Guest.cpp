#include "Guest.h"
#include <iostream>

Guest::Guest(std::string name, std::string phone) {
    this->name = name;
    this->phone = phone;
    this->attending = false;
    this->numGuests = 1;
    this->needTransport = false;
    this->transportLoc = "None";
}

void Guest::confirmAttendance(int guests, bool wantsTransportation, std::string transportLoc) {
    this->attending = true;
    this->numGuests = guests;
    this->needTransport = wantsTransportation;

    if (wantsTransportation)
        this->transportLoc = transportLoc;
    else
        this->transportLoc = "None";
}

void Guest::print() const {
    std::cout << "Name: " << this->name
        << " | Phone: " << this->phone
        << " | Attending: " << (this->attending ? "Yes" : "No")
        << " | Guests: " << this->numGuests
        << " | Needs Transport: " << (this->needTransport ? "Yes" : "No")
        << " | Transportation: " << this->transportLoc
        << std::endl;
}



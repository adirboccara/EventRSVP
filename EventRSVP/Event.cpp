#include "Event.h"
#include <iostream>

Event::Event(const std::string& name) {
	this->eventName = name;
}

Event::Event() : db("events.db"){}

void Event:: addGuest(const Guest& guest)  {
	guests.push_back(guest);
	db.addGuest(guest.getName(), guest.isAttending());
}

void Event::confirmGuest(const std::string& phone, int guestsCount, bool wantsTransport, const std::string& transportLoc) {
	for (auto& g : guests) {
		if (g.getPhone() == phone) {
			g.confirmAttendance(guestsCount, wantsTransport, transportLoc);
			std::cout << "Guest " << phone << " updated successfully.\n";
			return;
		}
	}
	std::cout << "Guest not found: " << phone << std::endl;
}

void Event::printAllGuests() const {
	std::cout << "\n===== Guest List for " << eventName << " =====\n";
	for (const auto& g : guests) {
		g.print();
	}
	std::cout << "=====================================\n";
}

std::string Event::getEventName() const {
	return eventName;
}

void Event::sendInvitations(const WhatsAppAPI& api) const {
	for (const auto& g : guests) {
		std::string message = "Hey! " + g.getName() + " Please confirm your attendance to " + eventName + " 🎉";
		api.sendMessage(g.getPhone(), message);
	}
}

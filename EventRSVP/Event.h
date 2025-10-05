#ifndef EVENT_H
#define EVENT_H
#include "WhatsAppAPI.h"

#include <vector>
#include "Guest.h"
#include "WhatsAppAPI.h"

class Event {
private:
	std::string eventName;
	std::vector<Guest> guests;
public:
	Event(const std::string& name);

	void addGuest(const Guest& guest);

	void confirmGuest(const std::string& phone, int guestsCount, bool wantsTransport, const std::string& transportLoc);

	void printAllGuests() const;

	std::string getEventName() const;

	void sendInvitations(const WhatsAppAPI& api) const;	

};



#endif
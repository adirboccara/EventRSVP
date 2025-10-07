#ifndef GUEST_RESPONSE_H
#define GUEST_RESPONSE_H

#include <string>

struct GuestResponse {
	std::string phone;
	bool attending;
	int numGuests;
	bool needTransport;
	std::string transportLoc;
};

#endif
#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <string>
#include <vector>
#include "GuestResponse.h"

class APIHandler {
public:
	void fetchData(const std::string& url) const;

	std::vector<GuestResponse> parseResponses(const std::string& jsonData) const;

};

#endif
#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <string>
#include <vector>
#include "GuestResponse.h"
#include "Database.h"

class ApiHandler {
public:
	ApiHandler();  
	~ApiHandler();
	void fetchData(const std::string& url) const;
	void readExampleAPI();

	std::vector<GuestResponse> parseResponses(const std::string& jsonData) const;
	void sendInvitations(Database& db);
};

#endif
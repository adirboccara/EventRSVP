#ifndef WHATSAPPAPI_H
#define WHATSAPPAPI_H

#include <string>
#include <iostream>

class WhatsAppAPI {
public:
    void sendMessage(const std::string& phone, const std::string& message) const;
};

#endif

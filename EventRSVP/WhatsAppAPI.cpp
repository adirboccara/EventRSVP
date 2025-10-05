#include "WhatsAppAPI.h"
#include <iostream>
#include <cstdlib> 

void WhatsAppAPI::sendMessage(const std::string& phone, const std::string& message) const {
    std::string formattedMessage = message;
    for (size_t i = 0; i < formattedMessage.size(); ++i) {
        if (formattedMessage[i] == ' ')
            formattedMessage.replace(i, 1, "%20");
    }

    std::string url = "https://wa.me/" + phone + "?text=" + formattedMessage;

    std::cout << "[WhatsAppAPI] Opening WhatsApp link: " << url << std::endl;

#ifdef _WIN32
    system(("start " + url).c_str()); 
#endif
}

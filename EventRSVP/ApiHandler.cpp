#include "APIHandler.h"
#include <iostream>
#include <curl/curl.h>          
#include <nlohmann/json.hpp>
#include <sqlite3.h>
using json = nlohmann::json;

#include <sqlite3.h>

ApiHandler::ApiHandler() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::cout << "API Handler initialized.\n";
}

ApiHandler::~ApiHandler() {
    curl_global_cleanup();
    std::cout << "API Handler cleaned up.\n";
}

void ApiHandler::sendInvitations(Database& db) {
    std::string query = "SELECT name, phone, attending FROM Guests;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db.getDB(), query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare SELECT statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return;
    }

    std::cout << "\nSending invitations via API (httpbin.org)...\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        bool attending = sqlite3_column_int(stmt, 2);

        std::string message = "Hello " + name + "! This is a test RSVP message. Status: " + (attending ? "Yes" : "No");

        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/post");

            std::string postData = "phone=" + phone + "&message=" + message;
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

            CURLcode res = curl_easy_perform(curl);
            if (res == CURLE_OK)
                std::cout << "Message sent to " << name << " (" << phone << ")\n";
            else
                std::cerr << "Failed to send to " << name << ": " << curl_easy_strerror(res) << "\n";

            curl_easy_cleanup(curl);
        }
    }

    sqlite3_finalize(stmt);
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void ApiHandler::readExampleAPI() {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get"); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        std::cout << "API Response:\n" << readBuffer << std::endl;
    }
    else {
        std::cerr << "Failed to read API: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
}

void ApiHandler::readExampleAPI() {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    std::string readBuffer;

    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        json response = json::parse(readBuffer);
        std::cout << "API Response:\n" << response.dump(2) << std::endl;

        std::string origin = response["origin"];
        std::string url = response["url"];
        std::cout << "Origin: " << origin << "\n URL: " << url << std::endl;
    }
    else {
        std::cerr << "Failed to read API: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
}

#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdlib.h>
#include <string>

using json = nlohmann::json;

std::string shortenURL(const std::string &longURL,
                       const std::string &accessToken) {
  // Bitly API endpoint for shortening URLs
  std::string url = "https://api-ssl.bitly.com/v4/shorten";

  // JSON payload for the API request
  json payload = {{"long_url", longURL}};

  // Convert JSON payload to string
  std::string payloadString = payload.dump();

  // Initialize CURL
  CURL *curl = curl_easy_init();
  if (curl) {
    // Set request options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadString.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER,
                     "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_USERPWD, (accessToken + ":").c_str());

    // Perform the request
    std::string response;
    curl_easy_setopt(
        curl, CURLOPT_WRITEFUNCTION,
        [](char *ptr, size_t size, size_t nmemb, std::string *data) {
          data->append(ptr, size * nmemb);
          return size * nmemb;
        });
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
      return "";
    }

    // Clean up
    curl_easy_cleanup(curl);

    // Parse JSON response
    json jsonResponse = json::parse(response);
    return jsonResponse["link"];
  } else {
    std::cerr << "Error initializing CURL." << std::endl;
    return "";
  }
}
void cleanUpInput(std::string &input) {
  size_t pos = 0;
  while ((pos = input.find('\x08', pos)) != std::string::npos) {
    input.erase(pos, 1); // Erase backspace character
  }
  std::string escape_seq = "\x1b[?25l";
  pos = input.find(escape_seq);
  if (pos != std::string::npos) {
    input.erase(pos, escape_seq.length()); // Erase escape sequence
  }
}

int main() {
  // Input Bitly access token
  std::string accessToken = std::getenv("BITLY_ACCESS_TOKEN");

  if (accessToken.empty()) {
    std::cerr << "Error: BITLY_ACCESS_TOKEN environment variable not set."
              << std::endl;
    return 1;
  }

  // Input URL from the user
  std::string longURL;
  std::cout << "Enter the URL: ";
  std::getline(std::cin, longURL);
  cleanUpInput(longURL);

  // Shorten the URL
  std::string shortenedURL = shortenURL(longURL, accessToken);
  std::cout << "Shortened URL: " << shortenedURL << std::endl;

  return 0;
}

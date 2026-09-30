#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using std::string;
using json = nlohmann::json;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t total = size * nmemb;

  std::string *response = static_cast<std::string *>(userdata);

  response->append(ptr, total);

  return total;
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Enter a wiki to search for.\n";
    return 1;
  }

  string search;

  for (int i = 1; i < argc; ++i) {
    search += argv[i];

    if (i < argc - 1) {
      search += " ";
    }
  }
  CURL *curl = curl_easy_init();
  std::string encoded_search;

  char *encoded = curl_easy_escape(curl, search.c_str(), 0);

  if (encoded) {
    encoded_search = encoded;
    curl_free(encoded);
  }
  std::string apiurl =
      "https://en.wikipedia.org/w/api.php"
      "?action=query"
      "&prop=extracts"
      "&explaintext=1"
      "&redirects=1"
      "&format=json"
      "&titles=" + encoded_search;
  if (!curl) {
      std::cerr<<"Failed to initalize curl.\n";
      return 1;
  }
  string response;
    curl_easy_setopt(curl, CURLOPT_URL, apiurl.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "folio/0.1");

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  CURLcode result = curl_easy_perform(curl);
  if (result != CURLE_OK) {
      std::cerr << curl_easy_strerror(result)<<'\n';
      return 1;
  }
  else {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      if (response_code == 404) {
          std::cerr << "No Wikipedia page found for \"" << search << "\".\n";
          curl_easy_cleanup(curl);
          return 1;
      }
      if (response_code != 200) {
          std::cerr << "Wikipedia request failed. HTTP " << response_code << '\n';
          curl_easy_cleanup(curl);
          return 1;
      }
      json data = json::parse(response);
      auto &pages = data["query"]["pages"];
      auto page = pages.begin().value();

      std::string title = page["title"];
      std::string extract = page["extract"].get<std::string>();
      if (extract.length() > 800) {
          size_t end = extract.rfind('.', 800);

          if (end != std::string::npos) {
              extract = extract.substr(0, end + 1);
          } else {
              extract = extract.substr(0, 800) + "...";
          }
      }
      char option{};
      std::string article_title = title;

      for (char &c : article_title) {
        if (c == ' ') {
          c = '_';
        }
      }

      std::string article_url =
          "https://en.wikipedia.org/wiki/" + article_title;
      std::cout<<title<<'\n';
      std::cout << std::string(title.length(), '-') << '\n';
      std::cout<<extract<<'\n';
      std::cout<<'\n';
      std::cout<<"Do you want the URL? (y/n) ";
      std::cin>>option;
      if (option == 'y') {
      std::cout<<"Url: "<<article_url<<'\n';
     }
      else {
      return 0;
  }
   }
}
// linux wiki url: https://en.wikipedia.org/wiki/Linux

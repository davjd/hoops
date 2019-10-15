#ifndef LOADER_H_
#define LOADER_H_

#include <curl/curl.h>
#include <functional>
#include <string>
#include <unordered_map>

namespace hoops {

class Loader {
 public:
  // Contains metadata about a webpage.
  struct Page {
    std::string url;
    std::string body;
    std::string time;
  };

  ~Loader();
  Loader() = default;
  explicit Loader(const std::string& url);
  std::string GetContent(const std::string& url);
  std::string Retrieve();

  bool Load(const std::string& url, bool save,
            std::function<std::string(const std::string&)> get_path,
            std::function<bool(const std::string&)> does_file_exist);

  // Loads an index page. Makes a request and writes output to disk if needed.
  bool LoadIndexPage(const std::string& url);

  // Loads a profile page. Makes a request and writes output to disk if needed.
  bool LoadProfilePage(const std::string& url);

  // Reads and returns the content for the given filename.
  static std::string GetPage(const std::string& file_name);

  // Checks whether a file exists for a given url.
  static bool DoesUrlFileExist(
      const std::string& url,
      std::function<std::string(const std::string&)> getter_fun);

  // Checks if a file exists for an index url.
  static bool DoesIndexFileExist(const std::string& url);

  // Checks if a file exists for a profile("/players/./...") url.
  static bool DoesProfileUrlExist(const std::string& url);

  // Delete file for a given filename.
  static bool RemoveFile(const std::string& file_name);

  Page LastRetrieved();

 private:
  std::string buffer_;  // last loaded url.
  std::string file_name_;
  std::unordered_map<std::string, std::string>
      url_to_content_;  // in mem copy of page content.
  CURL* curl_instance_;
  bool curl_on_;
  Page current_page_;

  bool SavePlayerToDB();
};

}  // namespace hoops

#endif
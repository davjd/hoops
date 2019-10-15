#include "loader.h"
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "env_namespace.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                            void* userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

namespace hoops {

Loader::~Loader() {
  if (curl_on_) {
    curl_easy_cleanup(curl_instance_);
  }
}

Loader::Loader(const std::string& url) : curl_on_(false) {
  if (LoadIndexPage(url)) std::cout << "successful!\n";
}

std::string Loader::GetContent(const std::string& url) {
  auto content = url_to_content_.find(url);
  if (content != url_to_content_.end()) {
    return content->second;
  }
  return "";
}

std::string Loader::Retrieve() { return buffer_; }

bool Loader::Load(const std::string& url, bool save,
                  std::function<std::string(const std::string&)> get_path,
                  std::function<bool(const std::string&)> does_file_exist) {
  std::fstream file;
  std::string file_path = get_path(url);
  if (does_file_exist(url)) {
    // This page has been saved before, so we only need to read from it.
    file.open(file_path, std::fstream::in);
    std::string header;
    file >> header;

    // Check to see that the header of the file is the url. If not, then this
    // file may have the wrong content for the url.
    if (url != header) {
      // Maybe rename this file with a "tag" so it's known to be an incorrectly
      // formatted file.
      std::cout << "file_name has the wrong url header.\n";
      return false;
    } else {
      if (save) {
        // Copy the content into a string and have a cache for it if needed.
        std::stringstream content_stream;
        content_stream << file.rdbuf();
        buffer_ = std::move(content_stream.str());
        url_to_content_[url] = buffer_;
        current_page_.url = url;
      }
      return true;
    }
  } else {
    // The file doesn't exist. Make a request and write the file to disk.
    file.open(file_path, std::fstream::out);
    CURLcode res;

    // Initialize CURL if we haven't used it.
    if (!curl_on_) {
      curl_instance_ = curl_easy_init();
      curl_on_ = true;
    }

    // Check that CURL is correctly instantiated.
    if (curl_instance_) {
      // Delete the buffer and make a request. Save the result to the buffer.
      buffer_.clear();
      curl_easy_setopt(curl_instance_, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl_instance_, CURLOPT_WRITEFUNCTION, ::WriteCallback);
      curl_easy_setopt(curl_instance_, CURLOPT_WRITEDATA, &buffer_);
      res = curl_easy_perform(curl_instance_);
      if (res) {
        std::cout << "Error occurred making CURL request.\n";
        return false;
      }

      // Write the buffered output to disk and store in-memory copy if needed.
      file << url << buffer_;
      if (save) {
        url_to_content_[url] = buffer_;
      }
      current_page_.url = url;
      std::cout << "url didn't exist, curl successful\n";
    } else {
      curl_on_ = false;
      std::cout << "curl wasn't successful\n";
      return false;
    }
  }
  return true;
}

std::string Loader::GetPage(const std::string& file_name) {
  std::fstream file;
  std::stringstream str_stream;
  file.open(file_name, std::fstream::in);
  str_stream << file.rdbuf();
  return str_stream.str();
}

bool Loader::DoesUrlFileExist(
    const std::string& url,
    std::function<std::string(const std::string&)> getter_fun) {
  return (access(getter_fun(url).c_str(), F_OK) != -1);
}

bool Loader::DoesIndexFileExist(const std::string& url) {
  return DoesUrlFileExist(url, env::filename::IndexFileName);
}

// Delete file.
bool Loader::RemoveFile(const std::string& file_name) {
  return !(remove(file_name.c_str()) != 0);
}

bool Loader::DoesProfileUrlExist(const std::string& url) {
  return DoesUrlFileExist(url, static_cast<std::string (*)(const std::string&)>(
                                   env::filename::ProfileFileName));
}

Loader::Page Loader::LastRetrieved() { return current_page_; }

bool Loader::LoadIndexPage(const std::string& url) {
  return Load(url, true, env::filename::IndexFileName, DoesIndexFileExist);
}

bool Loader::LoadProfilePage(const std::string& url) {
  return Load(url, false,
              static_cast<std::string (*)(const std::string&)>(
                  env::filename::ProfileFileName),
              DoesProfileUrlExist);
}

bool Loader::SavePlayerToDB() { return true; }

}  // namespace hoops
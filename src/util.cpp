#include "util.h"

#include <algorithm>
#include <cctype>

namespace hoops {

int letter_to_int(char letter) { return std::tolower(letter) - 'a'; }

std::string string_to_lower(const std::string& str) {
  std::string result;
  std::transform(
      str.begin(), str.end(), std::back_inserter(result),
      [](unsigned char c) -> unsigned char { return std::tolower(c); });
  return result;
}

void trim_new_line(std::string* str) {
  str->erase(std::remove_if(str->begin(), str->end(),
                            [](unsigned char c) { return c == '\n'; }),
             str->end());
}

bool is_number(const std::string& word) {
  return !word.empty() && std::find_if(word.begin(), word.end(), [](char c) {
                            return !std::isdigit(c);
                          }) == word.end();
}

float float_or_negative(const std::string& word) {
  if (!word.empty() && word.find('.') != std::string::npos) {
    return std::stof(word);
  }
  return -1;
}

int int_or_negative(const std::string& word) {
  if (word.empty() || !is_number(word)) {
    return -1;
  }
  return std::stoi(word);
}

std::vector<std::string> split(const std::string& str,
                               const std::string& delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
    token = str.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(str.substr(pos_start));
  return res;
}

}  // namespace hoops
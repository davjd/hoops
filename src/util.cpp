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
  if (word.empty() || !is_number(word)) {
    return -1;
  }
  return std::stof(word);
}

int int_or_negative(const std::string& word) {
  if (word.empty() || !is_number(word)) {
    return -1;
  }
  return std::stoi(word);
}

}  // namespace hoops
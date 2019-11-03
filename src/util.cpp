#include "util.h"

#include <algorithm>

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

}  // namespace hoops
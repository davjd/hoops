#ifndef UTIL_H_
#define UTIL_H_

#include <string>

namespace hoops {

int letter_to_int(char letter);

std::string string_to_lower(const std::string& str);

void trim_new_line(std::string* str);

}  // namespace hoops
#endif  // UTIL_H_
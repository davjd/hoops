#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include <vector>

namespace hoops {

int letter_to_int(char letter);

std::string string_to_lower(const std::string& str);

void trim_new_line(std::string* str);

bool is_number(const std::string& word);

float float_or_negative(const std::string& word);

int int_or_negative(const std::string& word);

std::vector<std::string> split(const std::string& str,
                               const std::string& delimiter = " ");

std::string collapse_vector(const std::vector<std::string>& command_vector);

}  // namespace hoops
#endif  // UTIL_H_
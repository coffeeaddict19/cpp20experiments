#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

namespace utility{
  std::vector<std::string> splitstringintotokens_byspace(const char* str);
  std::vector<unsigned long long> transform_delimlongstr(const std::string& str, char delim);
}

#endif

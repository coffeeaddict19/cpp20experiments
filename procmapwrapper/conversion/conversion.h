#ifndef CONVERSION_H
#define CONVERSION_H

#include <vector>
#include <cstdint>

template<typename T>
void append_integralorfloat_to_ubytesvector(
  std::vector<unsigned char>& vec,
  T value
);

template<typename T>
T ubtyes_to_integeralorfloat(
  std::array<unsigned char, sizeof(T)> barray
);

#include "conversion.cpp"
#endif

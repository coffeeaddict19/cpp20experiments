#ifndef INTEGERCONVERSION_H
#define INTEGERCONVERSION_H

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

#include "integerconversion.cpp"
#endif

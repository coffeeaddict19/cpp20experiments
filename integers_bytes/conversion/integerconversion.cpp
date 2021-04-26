#include <bit>
#include <array>
#include <type_traits>
#include <vector>

template<typename T>
void append_integralorfloat_to_ubytesvector(std::vector<unsigned char>& vec, T value){
  static_assert(
    std::is_integral<T>::value || std::is_floating_point<T>::value,
    "Integral or floating point type required."
  );
  const auto barray = std::bit_cast<std::array<unsigned char,sizeof(T)>>(value);
  for(const auto& b : barray){
    vec.push_back(b);
  }
}

template<typename T>
T ubtyes_to_integeralorfloat(
  std::array<unsigned char, sizeof(T)> barray
){
  static_assert(
    std::is_integral<T>::value || std::is_floating_point<T>::value,
    "Integral or floating point type required."
  );
  return std::bit_cast<T>(barray);
}

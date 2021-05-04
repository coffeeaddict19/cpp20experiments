#include "utility.h"
#include <string_view>
#include <ranges>
#include <sstream>
#include <iostream>

namespace utility{
  std::vector<std::string> splitstringintotokens_byspace(const char* str){
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::copy(
      std::istream_iterator<std::string>(iss),
      std::istream_iterator<std::string>(),
      back_inserter(tokens)
    );
    return tokens;
  }

  std::vector<unsigned long long> transform_delimlongstr(const std::string& str, char delim){
    std::vector<unsigned long long> output;
    for(const auto& viewintotoken : str | std::ranges::views::split(delim)){
      auto saneviewintotoken = viewintotoken | std::ranges::views::common;
      std::string token(saneviewintotoken.begin(), saneviewintotoken.end());
      if(!token.empty()){
        //std::cout<<"long long token: " << token;
        long long addressvalue = 0;
        try{
          addressvalue = std::stoull(token, nullptr, 16);
        }catch( std::out_of_range ex ){
          std::cout << "out of range on str to unsigned long long: " << token << std::endl;
        }
        output.push_back(addressvalue);
      }else{
        std::cout<<std::endl;
      }
    }
    return output;
  }
}

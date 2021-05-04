#include "mapsreader.h"
#include <fstream>
#include <cassert>
#include <sstream>

mapsreader::mapsreader(unsigned int pid){
  filename_ = getfilenamefrompid(pid);
  error_ = parse(filename_.c_str());
}

bool mapsreader::parse(const char* filename){
  const bool kFailedToParse = true;
  auto lines = read(filename);
  if(lines.has_value()){
    for(const auto& line : lines.value()){
      assert(("Parse line of file correctly.", parser_.parseline(line)));
    }
    return !kFailedToParse;
  }
  return kFailedToParse;
}

std::string mapsreader::getfilenamefrompid(unsigned int pid) const{
  // /proc/1583/maps
  std::ostringstream oss;
  oss<< "/proc/" << pid << "/maps";
  return oss.str();
}

std::optional<std::vector<std::string>> mapsreader::read(const char* filename) const{
  std::ifstream infile(filename);
  if(infile.is_open()){
    std::string line = "";
    std::vector<std::string> lines;
    while(std::getline(infile, line)){
      lines.push_back(line);
    }
    if(!infile.eof()){
      return std::nullopt;
    }else{
      return lines;
    }
  }
  return std::nullopt;
}

#ifndef MAPSREADER_H
#define MAPSREADER_H

#include "mapparser.h"
#include <string>
#include <vector>
#include <optional>

class mapsreader{
public:
  mapsreader(unsigned int pid);
  auto error() -> const bool& {
    return error_;
  }
  auto filename() -> const std::string& {
    return filename_;
  }
  auto getregionsbypathname(const char* pathname) -> std::vector<mapregion> const {
    return parser_.getregionsbypathname(pathname);
  }
  auto getuniquepathnames() -> std::set<std::string> {
    return parser_.getuniquepathnames();
  }
private:
  bool parse(const char* filename);
  std::string getfilenamefrompid(unsigned int pid) const;
  std::optional<std::vector<std::string>> read(const char* filename) const;
  std::string filename_;
  bool error_;
  mapparser parser_;
};

#endif

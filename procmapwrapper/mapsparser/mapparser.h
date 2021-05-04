#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <string>
#include <vector>
#include <set>
#include <sys/uio.h>
#include "mapregion.h"

class mapparser{
public:
  mapparser();
  bool parseline(const std::string line);
  std::vector<mapregion> getregionsbypathname(const char* pathname) const;
  std::set<std::string> getuniquepathnames() const;
private:
  std::vector<mapregion> regions_;
};

#endif

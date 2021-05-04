#include "mapparser.h"
#include "utility.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <string_view>
#include <ranges>

mapparser::mapparser(){
}

bool mapparser::parseline(const std::string line){
  //pidof bash
  //1665 1570 1374
  //cat /proc/1665/maps | tr " " "*"
  //address           perms offset  dev   inode       pathname (not in file)
  //where * means a space
  //562d310db000-562d3110a000*r--p*00000000*08:01*6294567********************/usr/bin/bash
  //562d31233000-562d3123e000*rw-p*00000000*00:00*0*
  //562d31f7b000-562d32123000*rw-p*00000000*00:00*0**************************[heap]
  auto linetokens = utility::splitstringintotokens_byspace(line.c_str());
  assert((
    "There are five or six columns in proc maps line.",
    linetokens.size() == 5 || linetokens.size() == 6
  ));
  if(!(linetokens.size() == 5 || linetokens.size() == 6)){
    return false;
  }

  mapregion region;
  auto addressvals = utility::transform_delimlongstr(linetokens.at(0), '-');
  assert((
    "There are two address numbers in the address range.",
    addressvals.size() == 2
  ));
  if(!(addressvals.size() == 2)){
    return false;
  }
  region.start_address = addressvals.at(0);
  region.end_address = addressvals.at(1);
  if(linetokens.size() == 6){
    region.pathname_ = linetokens.back();
  }else{
    region.pathname_ = "";
  }
  region.offset_ = std::stol(linetokens.at(2), nullptr, 16);
  regions_.push_back(region);
  return true;
}

std::vector<mapregion> mapparser::getregionsbypathname(const char* pathname) const{
  std::vector<mapregion> regions;
  for(auto const& region : regions_){
    if(region.pathname_.compare(pathname) == 0){
      regions.push_back(region);
    }
  }
  return regions;
}

std::set<std::string> mapparser::getuniquepathnames() const{
  std::set<std::string> paths;
  for(auto const& region : regions_){
    paths.insert(region.pathname_);
  }
  return paths;
}

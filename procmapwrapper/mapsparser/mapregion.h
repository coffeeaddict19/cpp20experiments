#ifndef MAPREGION_H
#define MAPREGION_H

#include <string>

class mapregion{
public:
  mapregion();
  unsigned long long start_address;
  unsigned long long end_address;
  bool permread_;
  bool permwrite_;
  bool permexecute_;
  bool permshared_;
  bool permprivate_;
  long offset_;
  int device_major;
  int device_minor;
  long inode_;
  std::string pathname_;
  auto error() -> bool {return error_;}
private:
  bool error_;
};

#endif

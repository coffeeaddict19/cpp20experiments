#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <sys/uio.h>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include "mapsreader.h"

namespace
{
  volatile std::sig_atomic_t gSignalStatus;
}

void signal_handler(int signal)
{
  gSignalStatus = signal;
}

unsigned int get_first_pid_of_process(const char* processname);
size_t readmemory_from_startingaddress(char* buf, pid_t pid, void* starting_address, size_t count);
void printerror();
void printprocessmaps(mapsreader&maps, const char* regionname);
void printprocesspaths(mapsreader&maps);
void write_tofile(char* buf, size_t length, const char* filename);

int main(int argc, char **argv){
  std::cout << "Welcome to 'procmapwrapper'. A live process memory monitoring tool." << std::endl;
  std::cout << "Specify a process name and region name to monitor (2 args)." << std::endl;
  unsigned int pid = 0;
  std::string regionname = "";
  if(argc > 1){
    pid = get_first_pid_of_process(static_cast<const char*>(argv[1]));
  }
  if(argc > 2){
    regionname = static_cast<const char*>(argv[2]);
  }
  if(pid > 0){
    std::cout << "Will monitor process with pid: " << pid << std::endl;
    mapsreader memmapreader(pid);
    if(memmapreader.error()){
      std::cout << "Error reading file map file: " << memmapreader.filename() << std::endl;
    }else{
      if(!regionname.empty()){
        std::cout << "Will monitor region: " << regionname << std::endl;
        if(memmapreader.error()){
          std::cout << "Error reading file map file: " << memmapreader.filename() << std::endl;
        }else{
          printprocessmaps(memmapreader, regionname.c_str());
          auto regionsvector = memmapreader.getregionsbypathname(regionname.c_str());
          if(regionsvector.size()>0){
            auto startaddress = regionsvector.at(0).start_address;
            auto bytecount = regionsvector.at(0).end_address - regionsvector.at(0).start_address;
            char* buf = new char[bytecount];
            if(buf != nullptr){
              auto cread = readmemory_from_startingaddress(buf, pid, (void*)startaddress, bytecount);
              if(cread == bytecount){
                write_tofile(buf, bytecount, "out.bin");
              }
              delete []buf;
              buf = nullptr;
            }
          }
        }
      }else{
        printprocesspaths(memmapreader);
      }
    }
  }
  std::cout << "Goodbye from 'procmapwrapper'." << std::endl;
  return 0;
}

void printprocessmaps(mapsreader&maps, const char* regionname){
  std::cout << "pathsnames..." << std::endl;
  for(auto pathname: maps.getuniquepathnames()){
    std::cout << "pathname: " << pathname << std::endl;
  }
  const std::vector<mapregion> regions = maps.getregionsbypathname(regionname);
  std::cout << "selected pathname..." << std::endl;
  for(const mapregion& region: regions){
    std::cout << "start: " << region.start_address;
    std::cout << " byte count: " << region.end_address - region.start_address;
    std::cout << " pathname: " << region.pathname_ << std::endl;
  }
}

void printprocesspaths(mapsreader&maps){
  std::cout << "pathsnames..." << std::endl;
  for(auto pathname: maps.getuniquepathnames()){
    std::cout << "pathname: " << pathname << std::endl;
  }
}

void write_tofile(char* buf, size_t length, const char* filename){
  std::ofstream outfile(filename, std::ios::out | std::ios::binary);
  outfile.write(buf, length);
  outfile.close();
}

unsigned int get_first_pid_of_process(const char* processname){
  std::ostringstream ss;
  char pidline[1024];
  char *pid;
  int i =0;
  int pid_number = 0;

  ss << "pidof " << processname;
  auto fp = popen(ss.str().c_str(),"r");
  if(nullptr == fp){
    std::cout << "popen failed. Could not get PID." << std::endl;
    return -1;
  }
  if(nullptr == fgets(pidline,1024,fp)){
    pclose(fp);
    std::cout << "fgets failed. Could not get PID." << std::endl;
    return -1;
  }
  std::cout << "PIDs for '" << processname << "' are (will return 1st): " << pidline;
  pid = strtok (pidline," ");
  if(nullptr == pid){
    std::cout << "strtok failed. Could not get PID." << std::endl;
    return -1;
  }
  pid_number = atoi(pid);
  pclose(fp);
  return pid_number;
}

size_t readmemory_from_startingaddress(char* buf, pid_t pid, void* starting_address, size_t count){
  struct iovec local[1];
  struct iovec remote[1];
  local[0].iov_base = buf;
  local[0].iov_len = count;
  remote[0].iov_base = starting_address;
  remote[0].iov_len = count;
  auto nread = process_vm_readv(pid, local, 1, remote, 1, 0);
  if(count == nread){
    std::cout << count << " bytes read from pid " << pid << std::endl;
  }else if(0 == nread){
    std::cout << "no bytes read but no error either" << std::endl;
  }else{
    printerror();
  }
  return nread;
}

void printerror(){
  switch (errno) {
      case EINVAL:
        std::cout << "ERROR: INVALID ARGUMENTS." << std::endl;
        break;
      case EFAULT:
        std::cout << "ERROR: UNABLE TO ACCESS TARGET MEMORY ADDRESS." << std::endl;
        break;
      case ENOMEM:
        std::cout << "ERROR: UNABLE TO ALLOCATE MEMORY." << std::endl;
        break;
      case EPERM:
        std::cout << "ERROR: INSUFFICIENT PRIVILEGES TO TARGET PROCESS." << std::endl;
        break;
      case ESRCH:
        std::cout << "ERROR: PROCESS DOES NOT EXIST." << std::endl;
        break;
      default:
        std::cout << "ERROR: Unknown: " << errno << std::endl;
  }
}

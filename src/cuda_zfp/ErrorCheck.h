#ifndef ERRORCHECK_H
#define ERRORCHECK_H
#include "gpu_portability.h"
#include <iostream>
#include <string>
#include <sstream>

using std::stringstream;
class ErrorCheck
{
public:
  ErrorCheck()
  {

  }

  void chk(std::string msg)
  {
    error = gpuGetLastError();
    if (error != gpuSuccess)
    {
      std::cout << msg << " : " << error;
      std::cout << " " << gpuGetErrorString(error) << std::endl;
    }
  }

  void chk()
  {
    chk(str.str());
    str.str("");
  }
  gpuError_t error;
  stringstream str;
};

#endif // ERRORCHECK_H

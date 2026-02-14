#ifndef CUZFP_POINTERS_CUH
#define CUZFP_POINTERS_CUH

#include "gpu_portability.h"
#include "ErrorCheck.h"
#include <iostream>


namespace cuZFP
{
// https://gitlab.kitware.com/third-party/nvpipe/blob/master/encode.c
bool is_gpu_ptr(const void *ptr)
{
  gpuPointerAttributes atts;
  const gpuError_t perr = gpuPointerGetAttributes(&atts, ptr);

  // clear last error so other error checking does
  // not pick it up
  gpuError_t error = gpuGetLastError();
#if GPU_PTR_ATTR_USE_TYPE
  return perr == gpuSuccess &&
                (atts.type == gpuMemoryTypeDevice ||
                 atts.type == gpuMemoryTypeManaged);
#else
  return perr == gpuSuccess && atts.memoryType == gpuMemoryTypeDevice;
#endif
}

} // namespace cuZFP

#endif

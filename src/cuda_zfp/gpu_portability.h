#ifndef GPU_PORTABILITY_H
#define GPU_PORTABILITY_H

/*
** GPU portability layer for CUDA/HIP.
**
** This header provides a set of macros that map GPU runtime API calls
** to either CUDA or HIP equivalents. All GPU backend code should use
** these macros instead of calling CUDA/HIP APIs directly.
**
** When ZFP_WITH_HIP is defined, all macros resolve to HIP calls.
** Otherwise (ZFP_WITH_CUDA), they resolve to CUDA calls.
*/

#if defined(ZFP_WITH_HIP)

#include <hip/hip_runtime.h>

/* Error types */
#define gpuError_t                    hipError_t
#define gpuSuccess                    hipSuccess

/* Memory management */
#define gpuMalloc                     hipMalloc
#define gpuFree                       hipFree
#define gpuMemcpy                     hipMemcpy
#define gpuMemset                     hipMemset
#define gpuMemcpyHostToDevice         hipMemcpyHostToDevice
#define gpuMemcpyDeviceToHost         hipMemcpyDeviceToHost

/* Device management */
#define gpuGetDeviceProperties        hipGetDeviceProperties
#define gpuDeviceProp                 hipDeviceProp_t
#define gpuDeviceSynchronize          hipDeviceSynchronize

/* Error handling */
#define gpuGetLastError               hipGetLastError
#define gpuGetErrorString             hipGetErrorString

/* Pointer attributes */
#define gpuPointerGetAttributes       hipPointerGetAttributes
#define gpuPointerAttributes          hipPointerAttribute_t
#define gpuMemoryTypeDevice           hipMemoryTypeDevice
#define gpuMemoryTypeManaged          hipMemoryTypeManaged

/* Events */
#define gpuEvent_t                    hipEvent_t
#define gpuEventCreate                hipEventCreate
#define gpuEventRecord                hipEventRecord
#define gpuEventSynchronize           hipEventSynchronize
#define gpuEventElapsedTime           hipEventElapsedTime

/* Streams */
#define gpuStreamSynchronize          hipStreamSynchronize

/*
** HIP always uses the .type member (like CUDA >= 10),
** so we define GPU_PTR_ATTR_USE_TYPE to simplify pointer
** attribute checks.
*/
#define GPU_PTR_ATTR_USE_TYPE 1

#elif defined(ZFP_WITH_CUDA)

/* Error types */
#define gpuError_t                    cudaError_t
#define gpuSuccess                    cudaSuccess

/* Memory management */
#define gpuMalloc                     cudaMalloc
#define gpuFree                       cudaFree
#define gpuMemcpy                     cudaMemcpy
#define gpuMemset                     cudaMemset
#define gpuMemcpyHostToDevice         cudaMemcpyHostToDevice
#define gpuMemcpyDeviceToHost         cudaMemcpyDeviceToHost

/* Device management */
#define gpuGetDeviceProperties        cudaGetDeviceProperties
#define gpuDeviceProp                 cudaDeviceProp
#define gpuDeviceSynchronize          cudaDeviceSynchronize

/* Error handling */
#define gpuGetLastError               cudaGetLastError
#define gpuGetErrorString             cudaGetErrorString

/* Pointer attributes */
#define gpuPointerGetAttributes       cudaPointerGetAttributes
#define gpuPointerAttributes          cudaPointerAttributes
#define gpuMemoryTypeDevice           cudaMemoryTypeDevice
#define gpuMemoryTypeManaged          cudaMemoryTypeManaged

/* Events */
#define gpuEvent_t                    cudaEvent_t
#define gpuEventCreate                cudaEventCreate
#define gpuEventRecord                cudaEventRecord
#define gpuEventSynchronize           cudaEventSynchronize
#define gpuEventElapsedTime           cudaEventElapsedTime

/* Streams */
#define gpuStreamSynchronize          cudaStreamSynchronize

/*
** For CUDA, pointer attribute access depends on CUDART_VERSION.
** CUDA >= 10 uses atts.type; older uses atts.memoryType.
*/
#if CUDART_VERSION >= 10000
  #define GPU_PTR_ATTR_USE_TYPE 1
#else
  #define GPU_PTR_ATTR_USE_TYPE 0
#endif

#else
  #error "gpu_portability.h requires either ZFP_WITH_CUDA or ZFP_WITH_HIP to be defined"
#endif

#endif /* GPU_PORTABILITY_H */

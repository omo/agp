
#include <iostream>
#include <cassert>
#include <dlfcn.h>
#include <CL/cl.h>
#include <CL/cl_egl.h>
#include <CL/cl_ext.h>
#include <CL/cl_gl.h>
#include <CL/cl_platform.h>

typedef cl_int(CL_API_CALL *PFN_clGetPlatformIDs)(
    cl_uint /* num_entries */, cl_platform_id * /* platforms */,
    cl_uint * /* num_platforms */) CL_API_SUFFIX__VERSION_1_0;
typedef cl_int(CL_API_CALL *PFN_clGetPlatformInfo)(
    cl_platform_id /* platform */, cl_platform_info /* param_name */,
    size_t /* param_value_size */, void * /* param_value */,
    size_t * /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;
typedef cl_int(CL_API_CALL *PFN_clGetDeviceIDs)(
    cl_platform_id /* platform */, cl_device_type /* device_type */,
    cl_uint /* num_entries */, cl_device_id * /* devices */,
    cl_uint * /* num_devices */) CL_API_SUFFIX__VERSION_1_0;


int main(int argc, char* argv[]) {
    std::cout << "Hello?" << std::endl;

    // TODO(morrita): Handle special casing. See https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/delegates/gpu/cl/opencl_wrapper.cc
    void* libopencl = dlopen("libOpenCL-pixel.so", RTLD_NOW | RTLD_LOCAL);
    if (!libopencl) {
        std::cout << "Failed to open libopencl!" << std::endl;
        return 1;
    }

    typedef void (*enableOpenCL_t)();
    enableOpenCL_t enableOpenCL =
        reinterpret_cast<enableOpenCL_t>(dlsym(libopencl, "enableOpenCL"));
    enableOpenCL();
    std::cout << "Enabled." << std::endl;

    // This is Pixel implementation specific (dlsym doesn't work on Pixel it seems.)
    typedef void* (*loadOpenCLPointer_t)(const char* name);
    loadOpenCLPointer_t loadOpenCLPointer = reinterpret_cast<loadOpenCLPointer_t>(dlsym(libopencl, "loadOpenCLPointer"));
    if (!loadOpenCLPointer) {
        std::cout << "Failed to open loadOpenCLPointer!" << std::endl;
        return 1;
    }

#define load_fn(fname) reinterpret_cast<decltype(fname)*>(loadOpenCLPointer(#fname))

    decltype(clGetPlatformIDs)* myclGetPlatformIDs = load_fn(clGetPlatformIDs);
    assert(myclGetPlatformIDs);
#undef load_fn

    std::cout << "Loaded!" << std::endl;

    std::cout << "closing..." << std::endl;
    dlclose(libopencl);

    return 0;
}
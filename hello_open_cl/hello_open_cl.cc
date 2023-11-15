
#include <iostream>
#include <dlfcn.h>

int main(int argc, char* argv[]) {
    std::cout << "Hello?" << std::endl;

    // TODO(morrita): Handle special casing. See https://github.com/tensorflow/tensorflow/blob/master/tensorflow/lite/delegates/gpu/cl/opencl_wrapper.cc
    void* libopencl = dlopen("libOpenCL-pixel.so", RTLD_NOW | RTLD_LOCAL);
    if (!libopencl) {
    std::cout << "Failed to open libopencl!" << std::endl;
        return 1;
    }

    std::cout << "Loaded!" << std::endl;
    dlclose(libopencl);

    return 0;
}
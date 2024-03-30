#include <iostream>
#include <CL/sycl.hpp>


int main() {
    sycl::default_selector device_selector;
    sycl::queue queue(device_selector);

    std::cout << "Running on " << queue.get_device().get_info<sycl::info::device::name>() << "\n";

    return 0;
}

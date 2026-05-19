#include "OrderGateway.h"
#include <chrono>
#include <iostream>

int main() {
    OrderGateway gateway("192.168.1.50", 8080);

    // Micro-benchmarking the gateway overhead
    auto start = std::chrono::high_resolution_clock::now();

    gateway.sendOrder(1001, 500);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Order routing overhead: " << duration << " nanoseconds.\n";
    return 0;
}

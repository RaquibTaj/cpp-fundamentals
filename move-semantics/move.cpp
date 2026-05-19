#include <iostream>
#include <chrono>
#include <utility>
#include <vector>

class MemoryBlock {
public:
    size_t size;
    int* data;

    // Standard Constructor
    MemoryBlock(size_t s) : size(s), data(new int[s]) {
        // Fill with dummy data to force physical memory allocation
        for (size_t i = 0; i < size; ++i) data[i] = 1;
    }

    // Destructor
    ~MemoryBlock() {
        delete[] data;
    }

    // 1. COPY CONSTRUCTOR (The Slow Path)
    // Allocates new memory and copies every single element.
    MemoryBlock(const MemoryBlock& other) : size(other.size), data(new int[other.size]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // 2. MOVE CONSTRUCTOR (The Fast, Quant Dev Path)
    // Steals the pointer directly. Zero allocations!
    // This expects an rvalue reference (&&), which is an xvalue.
    MemoryBlock(MemoryBlock&& other) noexcept : size(other.size), data(other.data) {
        // CRITICAL STEP: Orphan the original object's pointer 
        // so its destructor doesn't free our stolen memory!
        other.data = nullptr;
        other.size = 0;
    }
};

int main() {
    // Allocate 10 million integers (~40 Megabytes)
    const size_t ELEMENTS = 10'000'000;
    
    std::cout << "Allocating source block..." << std::endl;
    MemoryBlock source(ELEMENTS);

    // ==========================================
    // BENCHMARK 1: Copying (lvalue operation)
    // ==========================================
    auto start_copy = std::chrono::high_resolution_clock::now();
    
    MemoryBlock copied_block(source); // Triggers Copy Constructor
    
    auto end_copy = std::chrono::high_resolution_clock::now();
    auto copy_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_copy - start_copy).count();
    
    std::cout << "Copying took: " << copy_duration << " microseconds." << std::endl;

    // ==========================================
    // BENCHMARK 2: Moving (xvalue operation via std::move)
    // ==========================================
    auto start_move = std::chrono::high_resolution_clock::now();
    
    // std::move(source) casts 'source' to an xvalue, triggering the Move Constructor
    MemoryBlock moved_block(std::move(source)); 
    
    auto end_move = std::chrono::high_resolution_clock::now();
    auto move_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_move - start_move).count();
    
    std::cout << "Moving took: " << move_duration << " nanoseconds." << std::endl;

    // Verify move safety
    if (source.data == nullptr) {
        std::cout << "Verification: Source safely cleared to nullptr!" << std::endl;
    }

    return 0;
}

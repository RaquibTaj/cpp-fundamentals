# Cpp Fundamentals 

This is a fun challenge where I spend around 15 minutes a day for a month and see how much I can learn from it.

### Day 1
Avoid using raw pointers as they cause mem leaks if we don't use the delete keyword.  
Use std::unique_ptr as it provides zero overhead RAII (Resource Allocation Is Initialized), the moment it goes out of scope, it is freed.  
Compiling with g++ -O3 strips away smart pointer wrappers entirely, making it as fast as a raw pointers.

Results:  
- Stack allocation: ~35ns  
- Raw pointer allocation: ~600ns  
- Smart pointer allocation: ~1200ns  


### Day 3
Why shared_ptr is a massive bottleneck compared to unique_ptr?  
std::unique_ptr is the sole owner, just a raw pointer wrapped in RAII no extra footprint.  
std::shared_ptr is a shared owner, it allocates a hidden Control Block on the heap to track all the ref counts, every time there is a copy on the shared_ptr it triggers an internal atomic increment (something called xadd at the CPU level(?)) These atomic increments will stall the CPU pipeline.  

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

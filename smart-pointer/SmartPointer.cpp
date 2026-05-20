#include <iostream>
#include <memory>
#include <chrono>

struct Order {
  int id;
  int price;
  int quantity;
};

int main(){
  
  auto rawPointerTime = std::chrono::high_resolution_clock::now();
  // Raw pointer 
  Order* rawPointer = new Order{2, 200, 20};
  auto rawPointerTimeEnd = std::chrono::high_resolution_clock::now();
  // if we do no do delete rawPointer, there will be a mem leak!!

  auto smartPointerTime = std::chrono::high_resolution_clock::now();
  // smart pointer
  std::unique_ptr<Order> uniquePointer = std::make_unique<Order>(3, 300, 30);
  auto smartPointerTimeEnd = std::chrono::high_resolution_clock::now();
 
  auto stackTime = std::chrono::high_resolution_clock::now();
  // Stack allocation
  Order stackOrder{1, 100, 10};
  auto stackTimeEnd = std::chrono::high_resolution_clock::now();


  // allocation time
  std::cout << "Time taken by stack allocation: " << stackTime - stackTimeEnd
    << "\n\nTime taken by Raw pointer allocation: " << rawPointerTime - rawPointerTimeEnd
    << "\n\nTime taken by smart pointer allocation: " << smartPointerTime - smartPointerTimeEnd;
}

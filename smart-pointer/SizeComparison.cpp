#include <iostream>
#include <memory>

struct Order{
	int id;			//4 bytes
	int price;		//4 bytes
	int qty;		//4 bytes
};

// The total size of the struct is 12 bytes. (padded to 12 or 16 by the compiler)


int main(){
	// Raw pointer size
	std::cout<<"Raw pointer size: "<<sizeof(Order*) << " bytes\n";

	// Unique_ptr size
	std::cout<<"Unique pointer size: "<<sizeof(std::unique_ptr<Order>)<<" bytes\n";

	//Shared_ptr size
	std::cout<<"Shared pointer size: "<<sizeof(std::shared_ptr<Order>)<<" bytes\n";

	return 0;
}

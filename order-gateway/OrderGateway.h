#pragma sizeof(void*)
#include <memory>
#include <string>


class OrderGateway
{
public:
	OrderGateway(std::string ip, int port);
	~OrderGateway();

	void sendOrder(int orderId, int quantity);

private:
	// Forward declaration of the PImpl Idiom
	struct Impl;
	// the pointer to manage the private memebers and functions in the implementation.
	std::unique_ptr<Impl> pImpl;
};

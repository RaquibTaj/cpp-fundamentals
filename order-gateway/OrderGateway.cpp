#include "OrderGateway.h"
#include <iostream>
#include <chrono>


// Defination of the struct (pImpl)
// This is fully hidden from thos who include the Header file.
struct OrderGateway::Impl
{
	std::string ipAddress;
	int networkPort;
	int totalOrdersSent = 0;

	void connectToServer()
	{
		std::cout<<"Connecting to "<<ipAddress<<":"<<networkPort<<"\n";
	}

	void transmit(int id, int qty)
	{
		totalOrdersSent++;
		// IO operations are very poorly optimized
		//std::cout<<"Latency critical: transmitting Order: "<<id
		//	 << " [ Qty :" << qty <<"] via network stack. \n";
	}
};

// Constructor
OrderGateway::OrderGateway(std::string ip, int port) 
	: pImpl (std::make_unique<Impl>())
{
	pImpl->ipAddress = ip;
	pImpl->networkPort = port;

	pImpl->connectToServer();
}

OrderGateway::~OrderGateway() = default;

void OrderGateway::sendOrder(int orderId, int quantity)
{
	pImpl->transmit(orderId, quantity);
}

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

// Class representing the Order
class Order {
public:
	unordered_map<string, double> order;

	// Constructor
	Order();

	Order(unordered_map<string, double> order, bool is_bid);

	// operator() overloaded for priority queue sorting comparator
	bool operator()(Order& current, Order& next);

private:
	bool is_bid;
};

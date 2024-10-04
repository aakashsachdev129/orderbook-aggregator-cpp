#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
using namespace std;

class Order {
public:
	unordered_map<string, double> order;

	// Class representing the Order
	Order();

	Order(unordered_map<string, double> order, bool is_bid);

	bool operator()(Order& current, Order& next);

private:
	bool is_bid;
};

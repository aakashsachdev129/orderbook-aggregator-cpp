#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "../Header Files/Order.h"

using namespace std;

// Class representing the Order
Order::Order() {}

Order::Order(unordered_map<string, double> order, bool is_bid)
	: order(order), is_bid(is_bid) {}

bool Order::operator()(Order& current, Order& next) {
	double order_price = current.order["price"];
	double other_order_price = next.order["price"];
	return (current.is_bid ? order_price < other_order_price : order_price > other_order_price);
}

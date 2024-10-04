#pragma once
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "Order.h"

using namespace std;

// Class representing the OrderBook
class OrderBook {
private:
	priority_queue<Order, vector<Order>, Order> pq;

public:
	// Constructor
	OrderBook();

	// Function to update quantity of the top element of priority queue
	void update_min_quantity(double new_quantity);

	// Function to push to priority queue
	void push(Order& order);

	// Function to pop from priority queue
	void pop();

	// Function to get the top element from priority queue
	Order get_min();
};

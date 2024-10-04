#pragma once
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "Order.h"

using namespace std;

class OrderBook {
private:
	priority_queue<Order, vector<Order>, Order> pq;

public:
	OrderBook();

	void update_min_quantity(double new_quantity);

	void push(Order& order);

	void pop();

	Order get_min();
};

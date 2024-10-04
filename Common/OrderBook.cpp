#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "../Header Files/Order.h"
#include "../Header Files/OrderBook.h"

using namespace std;

// Constructor
OrderBook::OrderBook() {}

// Function to update quantity of the top element of priority queue
void  OrderBook::update_min_quantity(double new_quantity) {
	Order element = pq.top();
	element.order["quantity"] = new_quantity;
	pq.pop();
	pq.push(element);
}

// Function to push to priority queue
void OrderBook::push(Order& order) {
	pq.push(order);
}

// Function to pop from priority queue
void OrderBook::pop() {
	pq.pop();
}

// Function to get the top element from priority queue
Order OrderBook::get_min() {
	return pq.top();
}

#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include "../Header Files/Order.h"
#include "../Header Files/OrderBook.h"

using namespace std;

OrderBook::OrderBook() {}

void  OrderBook::update_min_quantity(double new_quantity) {
	Order element = pq.top();
	element.order["quantity"] = new_quantity;
	pq.pop();
	pq.push(element);
}

void OrderBook::push(Order& order) {
	pq.push(order);
}

void OrderBook::pop() {
	pq.pop();
}

Order OrderBook::get_min() {
	return pq.top();
}

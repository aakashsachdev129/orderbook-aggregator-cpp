#pragma once
#include "Exchange.h"
#include <vector>
#include <string>

using namespace std;

// Class representing the Kraken Exchange
class Kraken : public Exchange {
public:
	// Constructor
	Kraken(string name, string api_url,
		string query_params,
		int price_index, int quantity_index);

	// Function to get the product order book
	void get_product_orderbook() override;
};

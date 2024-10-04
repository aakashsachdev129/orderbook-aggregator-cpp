#pragma once
#include "Exchange.h"
#include <vector>
#include <string>

using namespace std;

// Class representing the Gemini Exchange
class Gemini : public Exchange {
public:
	// Constructor
	Gemini(string name, string api_url,
		string query_params,
		string price_key, string quantity_key);

	// Function to get the product order book
	void get_product_orderbook() override;
};

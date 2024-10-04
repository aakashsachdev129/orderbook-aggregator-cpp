#pragma once

#include <vector>
#include <string>
#include <curl/curl.h>
#include "OrderBook.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Class representing an Exchange
class Exchange {
public:
	// Constructor
	Exchange(string name, string api_url,
		string query_params,
		string price_key, string quantity_key);

	Exchange(string name, string api_url,
		string query_params,
		int price_index, int quantity_index);

	// Function to get the product order book
	virtual void get_product_orderbook() = 0;

	// Function to add the orders to the OrderBook
	void add_orders_to_orderbook(OrderBook& bids_q, OrderBook& offers_q);

	// Function to get data from REST API
	string http_get(string url);

protected:
	string api_url;
	string query_params;
	json orderbook;

private:
	string name;
	string price_key;
	string quantity_key;
	int price_index;
	int quantity_index;

	// Function to add bids to the OrderBook
	void add_bids_to_orderbook(OrderBook& bids_q);

	// Function to add offers to the OrderBook
	void add_offers_to_orderbook(OrderBook& offers_q);
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp);

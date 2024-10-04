#include <iostream>
#include <string>
#include <unordered_map>
#include <curl/curl.h>
#include "../Header Files/Exchange.h"
#include "../Header Files/Coinbase.h"
#include <vector>

Coinbase::Coinbase(string name, string api_url,
	string query_params,
	int price_index, int quantity_index) : Exchange(name, api_url, query_params, price_index, quantity_index) {}

void Coinbase::get_product_orderbook() {
	/** Function to get the product order book */
	string url = api_url + query_params;
	string response = http_get(url);
	json data = json::parse(response);

	orderbook = data;
}

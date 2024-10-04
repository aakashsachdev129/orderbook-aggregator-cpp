#include <iostream>
#include <string>
#include <unordered_map>
#include <curl/curl.h>
#include "../Header Files/Exchange.h"
#include "../Header Files/Coinbase.h"
#include <vector>

using namespace std;

// Constructor
Coinbase::Coinbase(string name, string api_url,
	string query_params,
	int price_index, int quantity_index) : Exchange(name, api_url, query_params, price_index, quantity_index) {}

// Function to get the product order book
void Coinbase::get_product_orderbook() {
	string url = api_url + query_params;
	string response = http_get(url);
	json data = json::parse(response);

	orderbook = data;
}

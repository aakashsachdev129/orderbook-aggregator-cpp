#include <iostream>
#include <string>
#include <unordered_map>
#include <curl/curl.h>
#include "../Header Files/Exchange.h"
#include "../Header Files/Gemini.h"
#include <vector>

Gemini::Gemini(string name, string api_url,
	string query_params,
	string price_key, string quantity_key) : Exchange(name, api_url, query_params, price_key, quantity_key) {}

void Gemini::get_product_orderbook() {
	/** Function to get the product order book */
	string url = api_url + query_params;
	string response = http_get(url);
	json data = json::parse(response);

	orderbook = data;
}

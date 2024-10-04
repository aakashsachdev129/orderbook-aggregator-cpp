#include <string>
#include <unordered_map>
#include <stdexcept>
#include "../Header Files/Exchange.h"
#include <curl/curl.h>
#include <iostream>

using namespace std;

// Constructor
Exchange::Exchange(string name, string api_url,
	string query_params,
	string price_key, string quantity_key)
	: name(name), api_url(api_url), query_params(query_params),
	price_key(price_key), quantity_key(quantity_key),
	price_index(0), quantity_index(1), orderbook({}) {}

Exchange::Exchange(string name, string api_url,
	string query_params,
	int price_index, int quantity_index)
	: name(name), api_url(api_url), query_params(query_params),
	price_index(price_index), quantity_index(quantity_index),
	price_key(""), quantity_key(""), orderbook({}) {}

// Function to get data from REST API
string Exchange::http_get(string url) {
	CURL* curl;
	CURLcode res;
	string readBuffer;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // Add this line
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	return readBuffer;
}


size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
	size_t totalSize = size * nmemb;
	userp->append((char*)contents, totalSize);
	return totalSize;
}

// Function to add the orders to the OrderBook
void Exchange::add_orders_to_orderbook(OrderBook& bids_q, OrderBook& offers_q) {
	add_bids_to_orderbook(bids_q);
	add_offers_to_orderbook(offers_q);
}

// Function to add bids to the OrderBook
void Exchange::add_bids_to_orderbook(OrderBook& bids_q) {
	for (const auto& bid : orderbook["bids"]) {

		string price = price_key == "" ? bid[price_index].get<string>() : bid[price_key].get<string>();
		string quantity = quantity_key == "" ? bid[quantity_index].get<string>() : bid[quantity_key].get<string>();

		unordered_map<string, double> order_dict = {
			{"price", stod(price)},
			{"quantity", stod(quantity)}
		};

		// Create an Order
		Order order(order_dict, true);

		// Add the Order to queue
		bids_q.push(order);
	}
}

// Function to add offers to the OrderBook
void Exchange::add_offers_to_orderbook(OrderBook& offers_q) {
	for (const auto& ask : orderbook["asks"]) {

		string price = price_key == "" ? ask[price_index].get<string>() : ask[price_key].get<string>();
		string quantity = quantity_key == "" ? ask[quantity_index].get<string>() : ask[quantity_key].get<string>();

		unordered_map<string, double> order_dict = {
			{"price", stod(price)},
			{"quantity", stod(quantity)}
		};

		// Create an Order
		Order order(order_dict, false);

		// Add the Order to queue
		offers_q.push(order);
	}
}

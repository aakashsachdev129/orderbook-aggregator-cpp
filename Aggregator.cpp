#include <iostream>
#include <string>
#include <fstream>
#include "Header Files/json.hpp"
#include "Header Files/OrderBook.h"
#include "Header Files/Coinbase.h"
#include "Header Files/Gemini.h"
#include "Header Files/Kraken.h"
#include "Header Files/Aggregator.h"

using namespace std;
using json = nlohmann::json;

Aggregator::Aggregator() {
	bids_q = OrderBook();
	offers_q = OrderBook();
}

void Aggregator::get_orderbooks(string add_kraken) {
	auto config = get_config("config.json");

	get_coinbase_orderbook(config);
	get_gemini_orderbook(config);

	if (add_kraken == "y") {
		get_kraken_orderbook(config);
	}
}

void Aggregator::get_coinbase_orderbook(json config) {
	try {
		string name = config["coinbase"]["name"];
		string api_url = config["coinbase"]["api_url"];
		string query_params = config["coinbase"]["query_params"];
		int price_index = config["coinbase"]["price_index"];
		int quantity_index = config["coinbase"]["quantity_index"];

		Coinbase coinbase(name, api_url, query_params, price_index, quantity_index);
		coinbase.get_product_orderbook();
		coinbase.add_orders_to_orderbook(bids_q, offers_q);
	}
	catch (exception e) {
		cerr << "An Error occurred while fetching coinbase orderbook: " << e.what() << endl;
	}
}

void Aggregator::get_gemini_orderbook(json config) {
	try {
		string name = config["gemini"]["name"];
		string api_url = config["gemini"]["api_url"];
		string query_params = config["gemini"]["query_params"];
		string price_key = config["gemini"]["price_key"];
		string quantity_key = config["gemini"]["quantity_key"];

		Gemini gemini(name, api_url, query_params, price_key, quantity_key);
		gemini.get_product_orderbook();
		gemini.add_orders_to_orderbook(bids_q, offers_q);
	}
	catch (exception e) {
		cerr << "An Error occurred while fetching gemini orderbook: " << e.what() << endl;
	}
}

void Aggregator::get_kraken_orderbook(json config) {
	try {
		string name = config["kraken"]["name"];
		string api_url = config["kraken"]["api_url"];
		string query_params = config["kraken"]["query_params"];
		int price_index = config["kraken"]["price_index"];
		int quantity_index = config["kraken"]["quantity_index"];

		Kraken kraken(name, api_url, query_params, price_index, quantity_index);
		kraken.get_product_orderbook();
		kraken.add_orders_to_orderbook(bids_q, offers_q);
	}
	catch (exception e) {
		cerr << "An Error occurred while fetching kraken orderbook: " << e.what() << endl;
	}
}

json Aggregator::get_config(string config_file) {
	ifstream jsonfile(config_file);
	json j;
	jsonfile >> j;
	return j;
}

pair<double, double> Aggregator::market_order(double quantity, bool is_buy) {
	if (is_buy) {
		return execute_order(quantity, offers_q);
	}
	else {
		return execute_order(quantity, bids_q);
	}
}

pair<double, double> Aggregator::execute_order(double quantity, OrderBook& orderbook) {
	double remaining_quantity = quantity;
	double total_cost = 0.0;

	try {
		while (remaining_quantity > 0) {
			try {
				auto current_order = orderbook.get_min();
				double current_order_price = current_order.order["price"];
				double current_order_quantity = current_order.order["quantity"];

				if (remaining_quantity >= current_order_quantity) {
					total_cost += current_order_price * current_order_quantity;
					orderbook.pop();
					remaining_quantity -= current_order_quantity;
				}
				else {
					total_cost += current_order_price * remaining_quantity;
					double reduced_order_quantity = current_order_quantity - remaining_quantity;
					orderbook.update_min_quantity(reduced_order_quantity);
					remaining_quantity = 0;
				}
			}
			catch (exception e) {
				cerr << "An Error occurred while fetching the next order from orderbook: " << e.what() << endl;
				throw;
			}
		}
	}
	catch (exception e) {
		cerr << "An Error occurred while executing the order: " << e.what() << endl;
	}

	return { total_cost, remaining_quantity };
}

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "OrderBook.h"
#include "Coinbase.h"
#include "Gemini.h"
#include "Kraken.h"

using namespace std;
using json = nlohmann::json;

// Class representing the orderbook aggregator
class Aggregator {
public:
	OrderBook bids_q;
	OrderBook offers_q;

	// Constructor
	Aggregator();

	// Function to get orderbooks from multiple exchanges
	void get_orderbooks(string add_kraken);

	// Function to get coinbase orderbook
	void get_coinbase_orderbook(json config);

	// Function to get gemini orderbook
	void get_gemini_orderbook(json config);

	// Function to get kraken orderbook
	void get_kraken_orderbook(json config);

	// Function to simulate a market order to calculate total cost
	pair<double, double> market_order(double quantity, bool is_buy);

private:
	// Function to read values from config file
	json get_config(string config_file);

	// Function to simulate execution of a market order to calculate total cost
	pair<double, double> execute_order(double quantity, OrderBook& orderbook);
};

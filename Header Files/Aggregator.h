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

class Aggregator {
public:
	OrderBook bids_q;
	OrderBook offers_q;

	Aggregator();

	void get_orderbooks(string add_kraken);

	void get_coinbase_orderbook(json config);

	void get_gemini_orderbook(json config);

	void get_kraken_orderbook(json config);

	pair<double, double> market_order(double quantity, bool is_buy);

private:
	json get_config(string config_file);

	pair<double, double> execute_order(double quantity, OrderBook& orderbook);
};

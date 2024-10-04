#pragma once
#include "Exchange.h"
#include <vector>
#include <string>
using namespace std;

class Kraken : public Exchange {
public:
	Kraken(string name, string api_url,
		string query_params,
		int price_index, int quantity_index);

	void get_product_orderbook() override;
};

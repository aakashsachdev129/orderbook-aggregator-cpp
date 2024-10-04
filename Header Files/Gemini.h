#pragma once
#include "Exchange.h"
#include <vector>
#include <string>
using namespace std;

class Gemini : public Exchange {
public:
	Gemini(string name, string api_url,
		string query_params,
		string price_key, string quantity_key);

	void get_product_orderbook() override;
};

#include <iostream>
#include <string>
#include "Header Files/Aggregator.h"

using namespace std;

// Function to print the BTC buy summary
void print_buy_summary(double buy_quantity, double total_buy_cost, double pending_buy_quantity) {
	cout << endl << "quantity to buy: " << buy_quantity << endl;

	double bought_quantity = buy_quantity - pending_buy_quantity;
	cout << endl << "quantity bought: " << bought_quantity << endl;

	if (pending_buy_quantity > 0) {
		cout << "pending buy quantity: " << pending_buy_quantity << endl;
	}

	cout << endl << "total cost of buying: " << total_buy_cost << endl;

	double average_buy_price = total_buy_cost / bought_quantity;
	cout << "average buying price: " << average_buy_price << endl;
}

// Function to print the BTC sell summary
void print_sell_summary(double sell_quantity, double total_sell_cost, double pending_sell_quantity) {
	cout << endl << "quantity to sell: " << sell_quantity << endl;

	double sold_quantity = sell_quantity - pending_sell_quantity;
	cout << endl << "quantity sold: " << sold_quantity << endl;

	if (pending_sell_quantity > 0) {
		cout << "pending sell quantity: " << pending_sell_quantity << endl;
	}

	cout << endl << "total cost of selling: " << total_sell_cost << endl;

	double average_sell_price = total_sell_cost / sold_quantity;
	cout << "average selling price: " << average_sell_price << endl;
}

// Function to get user input from console
tuple<double, double, string> get_input_arguments() {
	double buy_quantity, sell_quantity;
	string input_buy_quantity, input_sell_quantity, add_kraken;

	while (true) {
		cout << endl << "How much BTC do you want to buy?" << endl;
		cout << "BTC buy quantity: ";
		getline(cin, input_buy_quantity);

		try
		{
			buy_quantity = stod(input_buy_quantity);
			break;
		}
		catch (exception e)
		{
			cout << "Invalid BTC buy quantity. Please try again..." << endl;
		}
	}

	while (true) {
		cout << endl << "How much BTC do you want to sell?" << endl;
		cout << "BTC sell quantity: ";
		getline(cin, input_sell_quantity);

		try
		{
			sell_quantity = stod(input_sell_quantity);
			break;
		}
		catch (exception e)
		{
			cout << "Invalid BTC sell quantity. Please try again..." << endl;
		}
	}

	while (true) {
		cout << endl << "Do you want to add the Kraken exchange?" << endl;
		cout << "Add Kraken exchange (y/n): ";
		getline(cin, add_kraken);

		if (add_kraken == "y" || add_kraken == "n")
			break;
		else cout << "Invalid value provided. Only y/n accepted. Please try again..." << endl;
	}

	cout << endl << "Processing..." << endl;

	return { buy_quantity, sell_quantity, add_kraken };
}

// Entry point of the program
int main(int argc, char* argv[]) {

	double buy_quantity, sell_quantity;
	string add_kraken;

	tie(buy_quantity, sell_quantity, add_kraken) = get_input_arguments();

	// ---------------------------------------------------
	// ===================Get Orderbook===================
	// ---------------------------------------------------

	Aggregator aggregator;

	aggregator.get_orderbooks(add_kraken);

	// ---------------------------------------------
	// ===================Buy BTC===================
	// ---------------------------------------------

	double total_buy_cost, pending_buy_quantity;

	tie(total_buy_cost, pending_buy_quantity) = aggregator.market_order(buy_quantity, true);

	print_buy_summary(buy_quantity, total_buy_cost, pending_buy_quantity);

	// ----------------------------------------------
	// ===================Sell BTC===================
	// ----------------------------------------------

	double total_sell_cost, pending_sell_quantity;

	tie(total_sell_cost, pending_sell_quantity) = aggregator.market_order(sell_quantity, false);

	print_sell_summary(sell_quantity, total_sell_cost, pending_sell_quantity);

	return 0;
}

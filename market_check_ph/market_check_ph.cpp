#include <cpr/cpr.h>
#include <iostream>

#include "json.hpp"
#include "pse.hpp"
#include "crypto.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
	PseData pse;
	CryptoData crypto;
	// std::string res = pse.FetchStock("JFC");
	std::string res = crypto.GetMetrics("BTC");
	json j_complete = json::parse(res);
	std::cout << j_complete["data"]["market_data"]["price_usd"];
	return 0;
}

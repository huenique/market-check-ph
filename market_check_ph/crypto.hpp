#pragma once
#include <cpr/cpr.h>
#include <iostream>

#include "requests.hpp"

class CryptoData : public Http
{
protected:
	const cpr::Url &c_crypto_endpoint = cpr::Url{"https://data.messari.io/api/v1/assets"};

public:
	std::string GetMetrics(std::string symbol)
	{
		return Get(c_crypto_endpoint + cpr::Url{"/" + symbol + "/metrics"});
	}
};

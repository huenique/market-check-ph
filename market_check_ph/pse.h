#pragma once
#include <cpr/cpr.h>
#include <iostream>

class PseData {
public:
	const cpr::Url c_pse_endpoint = cpr::Url{ "http://pseapi.com/api/" };
	const cpr::Url c_psei_endpoint = cpr::Url{ "http://phisix-api.appspot.com/stocks" };

	std::string fetchStock(std::string stockSym, std::string date = "")
	{
		cpr::Url endpoint = c_psei_endpoint + cpr::Url{ "/" };
		cpr::Url urlPath;
		if (!date.empty())
		{
			urlPath = endpoint + cpr::Url(stockSym) + cpr::Url(".");
			urlPath = urlPath + cpr::Url(date) + cpr::Url(".json");
		}
		else
		{
			urlPath = endpoint + cpr::Url(stockSym) + cpr::Url(".json");
		}
		cpr::Response resp = cpr::Get(urlPath);
		return resp.text;
	}
};

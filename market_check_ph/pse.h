#pragma once
#include <cpr/cpr.h>
#include <iostream>

class PseData {
public:
	const std::string c_format_json = ".json";
	const cpr::Url c_pse_endpoint = cpr::Url{ "http://pseapi.com/api/" };
	const cpr::Url c_psei_endpoint = cpr::Url{ "http://phisix-api.appspot.com/stocks" };

	/* Perform get request */
	std::string get(cpr::Url const& urlPath) {
		cpr::Response resp = cpr::Get(urlPath);
		return resp.text;
	}

	/* Parse chucks of data. */
	std::string fetchBigData(
		std::string date = "",
		std::string from = "",
		std::string to = "",
		std::string dir = "")
	{
		cpr::Url endpoint = c_pse_endpoint + cpr::Url(dir);
		cpr::Url urlPath;
		if (!date.empty() && (from.empty() || to.empty())) {
			urlPath = endpoint + cpr::Url(date);
		}
		else if (date.empty() && (!from.empty() && !to.empty()))
		{
			urlPath = endpoint + cpr::Url(from + "/" + to);
		}
		return get(urlPath);
	}

	/* Get stock quote for the specified stock.*/
	std::string fetchStock(std::string const& stockSym, std::string date = "")
	{
		cpr::Url urlPath;
		if (!date.empty())
		{
			urlPath = c_psei_endpoint + cpr::Url("/" + stockSym + "." + date + c_format_json);
		}
		else
		{
			urlPath = c_psei_endpoint + cpr::Url("/" + stockSym + c_format_json);
		}
		return get(urlPath);
	}

	/* Get all stock quote. */
	std::string fetchAll()
	{
		return get(c_psei_endpoint + c_format_json);
	}

	/* Get market end of day report. */
	std::string fetchMarket(
		std::string date = "",
		std::string from = "",
		std::string to = "")
	{
		return fetchBigData(date, from, to, "Market/");
	}

	/* Get sectoral summary. */
	std::string fetchSector(
		std::string date = "",
		std::string from = "",
		std::string to = "")
	{
		return fetchBigData(date, from, to, "Sector/");
	}
};

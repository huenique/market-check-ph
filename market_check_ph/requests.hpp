#pragma once
#include <cpr/cpr.h>
#include <iostream>

class Http
{
public:
	// Perform a GET request
	std::string Get(cpr::Url const &urlPath)
	{
		cpr::Response resp = cpr::Get(urlPath);
		return resp.text;
	}
};

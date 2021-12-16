#pragma once
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>

#include "requests.hpp"

class ForexData : public Http
{
protected:
    const cpr::Url &c_forex_endpoint = cpr::Url{"http://api.currencylayer.com/live?access_key="};

public:
    std::string GetLive(std::string currencies)
    {
        std::string params = "&" + std::string("currencies=") + currencies;
        return Get(c_forex_endpoint + cpr::Url{"83920fb44a7e2a3e1b9d963eaacfdf0f" + params});
    }
};

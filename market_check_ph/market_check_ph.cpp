#include <cpr/cpr.h>
#include <iostream>

#include "pse.h"

int main(int argc, char** argv) {
    PseData api;
    // std::string res = api.fetchStock("JFC");
    std::string res = api.fetchMarket("", "03-15-2017", "12-01-2019");
    std::cout << res;
}

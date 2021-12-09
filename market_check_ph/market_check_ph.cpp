#include <cpr/cpr.h>
#include <iostream>

#include "pse.h"

int main(int argc, char** argv) {
    PseData api;
    std::string res = api.fetchStock("JFC");
    std::cout << res;
}

#pragma once
#include <cctype>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <windows.h>

#include "crypto.hpp"
#include "forex.hpp"
#include "json.hpp"
#include "pse.hpp"
#include "requests.hpp"

using json = nlohmann::json;

PseData pse;
CryptoData crypto;
ForexData forex;
Http http;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawMenu()
{
    gotoxy(20, 2);
    std::cout << "SELECT MARKET";
    gotoxy(20, 3);
    std::cout << "1. Philippine Stock Market";
    gotoxy(20, 4);
    std::cout << "2. Cryptocurrency Market";
    gotoxy(20, 5);
    std::cout << "3. Foreign Exchange";
    gotoxy(20, 6);
    std::cout << "4. Exit";
}

void DrawCryptoView()
{
    std::string cont;

    while (1)
    {
        std::string symbol;

        system("cls");
        gotoxy(20, 2);
        std::cout << "Enter cryptocurrency symbol: ";
        std::cin >> symbol;
        std::string res = crypto.GetMetrics(symbol);
        json j_complete = json::parse(res);

        // Basic info
        std::string name = j_complete["data"]["name"].get<std::string>();
        std::string sym = j_complete["data"]["symbol"].get<std::string>();

        // Market data
        double priceBtc = j_complete["data"]["market_data"]["price_btc"].get<double>();
        double priceEth = j_complete["data"]["market_data"]["price_eth"].get<double>();
        double priceUsd = j_complete["data"]["market_data"]["price_usd"].get<double>();
        double usdPhp = json::parse(http.Get("https://open.er-api.com/v6/latest/USD"))["rates"]["PHP"].get<double>();
        double volume24 = j_complete["data"]["market_data"]["volume_last_24_hours"].get<double>();
        double open = j_complete["data"]["market_data"]["ohlcv_last_1_hour"]["open"].get<double>();
        double high = j_complete["data"]["market_data"]["ohlcv_last_1_hour"]["high"].get<double>();
        double low = j_complete["data"]["market_data"]["ohlcv_last_1_hour"]["low"].get<double>();
        double close = j_complete["data"]["market_data"]["ohlcv_last_1_hour"]["close"].get<double>();
        double volume = j_complete["data"]["market_data"]["ohlcv_last_1_hour"]["volume"].get<double>();

        // Marketcap
        int rank = j_complete["data"]["marketcap"]["rank"].get<int>();
        double dominance = j_complete["data"]["marketcap"]["marketcap_dominance_percent"].get<double>();
        double capUsd = j_complete["data"]["marketcap"]["current_marketcap_usd"].get<double>();
        double cap50yr = j_complete["data"]["marketcap"]["y_2050_marketcap_usd"].get<double>();

        // Display cryptocurrency metrics
        gotoxy(70, 2);
        std::cout << name + " (" + sym + ") ";
        gotoxy(70, 4);
        std::cout << "------------";
        gotoxy(70, 5);
        std::cout << "MARKET DATA";
        gotoxy(70, 6);
        std::cout << "------------";
        gotoxy(70, 7);
        std::cout << "USD: " << std::fixed << std::setprecision(2) << priceUsd;
        gotoxy(70, 8);
        std::cout << "PHP: " << priceUsd * usdPhp << std::endl;
        gotoxy(70, 9);
        std::cout << "BTC: " << std::setprecision(20) << priceBtc;
        gotoxy(70, 10);
        std::cout << "ETH: " << priceEth;
        gotoxy(70, 11);
        std::cout << "Volume (24H): " << volume24;
        gotoxy(70, 12);
        std::cout << "OHLCV:";
        gotoxy(70, 13);
        std::cout << "> open:\t" << open;
        gotoxy(70, 14);
        std::cout << "> high:\t" << high;
        gotoxy(70, 15);
        std::cout << "> low:\t" << low;
        gotoxy(70, 16);
        std::cout << "> close:\t" << close;
        gotoxy(70, 17);
        std::cout << "> volume:\t" << volume;

        gotoxy(70, 19);
        std::cout << "------------";
        gotoxy(70, 20);
        std::cout << "MARKETCAP";
        gotoxy(70, 21);
        std::cout << "------------";
        gotoxy(70, 22);
        std::cout << "Rank: " << rank;
        gotoxy(70, 23);
        std::cout << "Dominance: " << std::setprecision(5) << dominance;
        gotoxy(70, 24);
        std::cout << "Current Marketcap (USD): " << capUsd;
        gotoxy(70, 25);
        std::cout << "Year 2050 Market cap (USD): " << cap50yr << std::endl;

        gotoxy(20, 3);
        std::cout << "Query another currency? [y/n]: ";
        std::cin >> cont;
        if (cont != "y" && cont != "Y")
        {
            system("cls");
            break;
        }
    }
}

void DrawPseView()
{
    std::string cont;

    while (1)
    {
        std::string symbol;

        system("cls");
        gotoxy(20, 2);
        std::cout << "Enter stock symbol: ";
        std::cin >> symbol;
        std::string res = pse.FetchStock(symbol);

        json j_complete = json::parse(res);

        std::string name = j_complete["stock"][0]["name"].get<std::string>();
        std::string currency = j_complete["stock"][0]["price"]["currency"].get<std::string>();
        double amount = j_complete["stock"][0]["price"]["amount"].get<double>();
        double change = j_complete["stock"][0]["percent_change"].get<double>();
        int volume = j_complete["stock"][0]["volume"].get<int>();
        std::string sym = j_complete["stock"][0]["symbol"].get<std::string>();
        std::string asof = j_complete["as_of"].get<std::string>();

        gotoxy(70, 2);
        std::cout << name << " (" + sym + ") ";
        gotoxy(70, 4);
        std::cout << "> As of " << asof;
        gotoxy(70, 5);
        std::cout << "> Price: " << currency << " " << std::fixed << std::setprecision(2) << amount << std::endl;
        gotoxy(70, 6);
        std::cout << "> Percent Change: " << change;
        gotoxy(70, 7);
        std::cout << "> Volume: " << volume;

        gotoxy(20, 3);
        std::cout << "Query another currency? [y/n]: ";
        std::cin >> cont;
        if (cont != "y" && cont != "Y")
        {
            break;
        }
    }
}

void DrawForexView()
{
    std::string cont;

    while (1)
    {
        std::string currency;
        std::vector<std::string> toQuote;

        system("cls");

        while (1)
        {

            // Clean up line
            gotoxy(20, 2);
            std::cout << "                                            ";

            gotoxy(20, 2);
            std::cout << "Enter currency (e.g. PHP), 'x' to stop: ";
            std::cin >> currency;

            if (currency == "x")
                break;

            toQuote.push_back(currency);
            gotoxy(68, 2);
            std::cout << "|";
            gotoxy(70, 2);
            for (std::string currency : toQuote)
                std::cout << currency << " ";
        }

        // Convert vector to string with delimiter ","
        std::string currencies = std::accumulate(std::begin(toQuote), std::end(toQuote), std::string(),
                                                 [](std::string &ss, std::string &s)
                                                 {
                                                     return ss.empty() ? s : ss + "," + s;
                                                 });

        json data = json::parse(forex.GetLive(currencies));
        json quotes = data["quotes"];

        for (int i = 0; i < toQuote.size(); i++)
        {
            gotoxy(68, 2);
            std::cout << "|";
            gotoxy(70, 3 + i);
            std::cout << "USD/" + toQuote[i] + " -> " << quotes["USD" + toQuote[i]] << std::endl;
        }

        gotoxy(20, 3);
        std::cout << "Query another pair? [y/n]: ";
        std::cin >> cont;
        if (cont != "y" && cont != "Y")
        {
            break;
        }
    }
}

void DrawInterface()
{
    int choice;

    while (1)
    {
        system("cls");
        DrawMenu();
        gotoxy(20, 8);

        std::cout << "Enter market ID: ";
        std::cin >> choice;

        if (choice == 1)
        {
            DrawPseView();
        }
        else if (choice == 2)
        {
            DrawCryptoView();
        }
        else if (choice == 3)
        {
            DrawForexView();
        }
        else
        {
            break;
        }
        // enter another choice
    }
}

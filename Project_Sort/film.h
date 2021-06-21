#pragma once
#include <iostream>
#include <string>

struct Film
{
    std::string tytul;
    int wynik;
    int id;
    Film() : tytul("brak"), wynik(0), id(0) {}
    //Film(std::string tyt, int wyn, float lp) : tytul(tyt), wynik(wyn), id(lp) {}
};

std::ostream& operator << (std::ostream& out, const Film& tab)
{
    std::cout << tab.id << "," << tab.tytul << "," << tab.wynik << std::endl;
    return out;
}
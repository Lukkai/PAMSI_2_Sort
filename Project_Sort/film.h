#pragma once
#include <iostream>
#include <string>

struct Film
{
    std::string tytul;
    int wynik;
    long id;
    Film() : tytul("brak"), wynik(0), id(0) {}
    //Film(std::string tyt, int wyn, float lp) : tytul(tyt), wynik(wyn), id(lp) {}
};
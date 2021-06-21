#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "film.h"
#include <regex>

using namespace std;

int main()
{
    cout << "Wpisz wielkosc danych do pozyskania : " << endl;
    int ROZMIAR;
    cin >> ROZMIAR;
    Film* sort;
    sort = new (nothrow) Film[ROZMIAR];

    ifstream file;
    file.open("test.txt");            //Otwarcie pliku

    if (!file.good())
    {                         //Funkcja sprawdza czy poprawnie wczytano plik
        cout << "Plik nie istnieje" << endl;
        file.close();
        exit(0);
    }
    string linia;
    char znak; //zczytany znak z linii
    long numer=0; //numer linii
    int dlugosc = 0; //dlugosc linii
    int odczyt = 0, odczyt2 = 0; //numery odczytanych kolumn
    int temp = 0; //zmienna pomocnicza do 
    char typ;
    int kolumna = 0;
    string sid, stytul, swynik;
    //long i = 1;
    while (numer < ROZMIAR && !file.eof())                                 //zczytuje aż do wersu w pliku ktory bedzie pusty
    {
        if (numer == 0)
        {            
            numer++;
            continue;
        }
        if (kolumna == 0)
        {
            getline(file, sid, ',');
            kolumna++;
        }
        if (kolumna == 1)
        {
            getline(file, stytul, ',');
            kolumna++;
        }
        if (kolumna == 2)
        {
            getline(file, swynik, '\n');
            kolumna++;
        }


        linia = sid + "," + stytul + "," + swynik;
        //cout << sid << endl;
        std::string s = ",,";
        //cout << stytul << endl;
        dlugosc = linia.size();
        if (sid == "" || swynik == "" || stytul == "")
        {
            kolumna = 0;
            numer++;
            continue;
        }

        sort[numer].id = atof(sid.c_str());
        sort[numer].tytul = stytul;                     
        sort[numer].wynik = atof(swynik.c_str());
        
        cout << "Ilosc tytułow :  " << sort[numer].id << " " << sort[numer].wynik<< " " << sort[numer].tytul << endl;       //Wyświetlanie zawartosci tablic
        
        numer++;
        if (kolumna == 3)
            kolumna = 0;
        else
            kolumna++;
    }


    file.close();


    //ofstream file2;
    //file2.open("C:\\Users\\lukas\\source\\repos\\Project2\\Project2\\projekt2_dane_sorted.txt");

    //cout << "Ilość tytułów :  " << numer << endl;       //Wyświetlanie zawartosci tablic

    //for (int i = 0; i < numer; i++) 
    //{
    //    file2 << sort[i].id << " ; " << sort[i].tytul << " ; " << sort[i].wynik << endl;
    //}

    //file2.close();

    return 0;
}
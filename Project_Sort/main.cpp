#include "film.h"
#include "sortowania.hpp"
#include <chrono>

using namespace std;

int main() {
    
    cout << "Wpisz wielkosc danych do pozyskania : " << endl;
    int ROZMIAR;
    cin >> ROZMIAR;
    Film* baza = new (nothrow) Film[ROZMIAR];

    ifstream file;
    file.open("projekt2_dane.csv");            //Otwarcie pliku

    if (!file.good())
    {                         //Funkcja sprawdza czy poprawnie wczytano plik
        cout << "Plik nie istnieje" << endl;
        file.close();
        exit(0);
    }
    string linia;
    int numer = -1; //numer linii, pierwsza linia ignorowana, -1 zeby uporzadkowac indeksy tablicy od 0
    int dlugosc = 0; //dlugosc linii
    int kolumna = 0; //kolumna pliku, oddzielona ','
    string sid, stytul, swynik; //dane odpowiednich kolumn
    //long i = 1;
    while (numer < ROZMIAR && !file.eof())   //zczytuje aż do wersu w pliku ktory bedzie pusty lub do ograniczenia
    {
        if (numer == -1)
        {
            getline(file, sid, '\n');
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
            size_t found = stytul.find("\"");
            if (found != string::npos)
            {
                string temp;
                getline(file, temp, '\"');
                string temp2;
                getline(file, temp2, ',');
                stytul = stytul + ',' + temp + '\"' + temp2;
            }
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

        baza[numer].id = (int)atof(sid.c_str());
        baza[numer].tytul = stytul;
        baza[numer].wynik = (int)atof(swynik.c_str());

        //cout << "Ilosc tytulow :  " << baza[numer].id << " " << baza[numer].tytul << " " << baza[numer].wynik << endl;       //Wyświetlanie zawartosci bazalic

        numer++;
        if (kolumna == 3)
            kolumna = 0;
        else
            kolumna++;
    }

    file.close();

    //cout << showpos <<baza[0].wynik << noshowpos << endl;

    int rozmiar2 = 0;
    for (int i = 0; i < ROZMIAR; i++)
    {
        if (baza[i].wynik > 0)
            rozmiar2++;
    }

    Film* lista_elementow = new Film[rozmiar2];

    int a = 0;
    for (int i = 0; i < ROZMIAR; i++)
    {
        if (baza[i].wynik > 0)
        {
            lista_elementow[a] = baza[i];
            a++;
        }
    }
    delete[] baza;
    Film* lista_do_sort = new Film[rozmiar2];
    

    /***************************************************/
    /*********        SORTOWANIE            ************/
    /***************************************************/

    std::chrono::steady_clock::time_point start, end;
    double czas_merge = 0;
    double czas_quick = 0;
    double czas_intro = 0;
    double czas_bucket = 0;
    double czas_insertion = 0;
    int opcja;
    std::cout << "Wybierz sortowanie: \n"
        "1. mergesort\n"
        "2. quicksort\n"
        "3. inrosort\n"
        "4. bucketsort\n"
        "5. bucketsort\n"
        "0. wszystkie\n";
    std::cin >> opcja;
    
    if (opcja == 1)
    {
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "juz posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        Sort_scal(lista_do_sort, 0, rozmiar2 - 1);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_merge = std::chrono::duration<double, std::milli>(end - start).count();
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "merge posortowane\n";
        cout << "Czas sortowania merge:" + to_string(czas_merge) << endl;
        
        delete[] lista_do_sort;
    }
    else if (opcja == 2)
    {
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        QuickSort(lista_do_sort, 0, rozmiar2 - 1);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_quick = std::chrono::duration<double, std::milli>(end - start).count();
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "quick posortowane\n";
        cout << "Czas sortowania quick:" + to_string(czas_quick) << endl;

        delete[] lista_do_sort;
        }
    else if (opcja == 3)
    {
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        //Sort_intro(lista_do_sort, 0, rozmiar2 - 1, 2 * log(rozmiar2));
        Sort_intro(lista_do_sort, 0, rozmiar2 - 1, 2000);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_quick = std::chrono::duration<double, std::milli>(end - start).count();
        for (int i = 0; i < rozmiar2; i++)
            cout << lista_do_sort[i] << endl;
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "intro posortowane\n";
        cout << "Czas sortowania intro:" + to_string(czas_quick) << endl;
        delete[] lista_do_sort;
    }
    else if (opcja == 4)
    {
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        bucketSort(lista_do_sort, rozmiar2);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_bucket = std::chrono::duration<double, std::milli>(end - start).count();
        /*for (int i = 0; i < rozmiar2; i++)
            cout << lista_do_sort[i] << endl;*/
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "bucket posortowane\n";
        cout << "Czas sortowania bucket:" + to_string(czas_bucket) << endl;
        delete[] lista_do_sort;
    }
    else if (opcja == 5)
    {
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        Sort_wst(lista_do_sort, rozmiar2);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_insertion = std::chrono::duration<double, std::milli>(end - start).count();
        for (int i = 0; i < rozmiar2; i++)
            cout << lista_do_sort[i] << endl;
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "insertion posortowane\n";
        cout << "Czas sortowania insertion:" + to_string(czas_insertion) << endl;
        delete[] lista_do_sort;
    }
    else if (opcja == 0)
    {
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "juz posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        Sort_scal(lista_do_sort, 0, rozmiar2 - 1);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_merge = std::chrono::duration<double, std::milli>(end - start).count();
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "merge posortowane\n";
        cout << "Czas sortowania merge:" + to_string(czas_merge) << endl;
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }

        std::cout << "KOLEJNE SORTOWANIE...\n";        
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "juz posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        QuickSort(lista_do_sort, 0, rozmiar2 - 1);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_quick = std::chrono::duration<double, std::milli>(end - start).count();
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "quick posortowane\n";
        cout << "Czas sortowania quick:" + to_string(czas_quick) << endl;
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }
        std::cout << "KOLEJNE SORTOWANIE...\n";        
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "juz posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        Sort_intro(lista_do_sort, 0, rozmiar2 - 1, 2 * log(rozmiar2));
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_intro = std::chrono::duration<double, std::milli>(end - start).count();
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "intro posortowane\n";
        cout << "Czas sortowania intro:" + to_string(czas_intro) << endl;
        for (int index = 0; index < rozmiar2; index++)
        {
            lista_do_sort[index] = lista_elementow[index];
        }

        std::cout << "KOLEJNE SORTOWANIE...\n";
        if (posortowane(lista_do_sort, rozmiar2))
        {
            cout << "juz posortowane\n";
            return 0;
        }
        start = std::chrono::high_resolution_clock::now();   //start clock
        bucketSort(lista_do_sort, rozmiar2);
        end = std::chrono::high_resolution_clock::now();     //stop clock
        czas_bucket = std::chrono::duration<double, std::milli>(end - start).count();     
        if (posortowane(lista_do_sort, rozmiar2))
            cout << "bucket posortowane\n";

        delete[] lista_do_sort;
        std::cout << "KONIEC SORTOWAN" << endl;
        cout << "Czas sortowania bucket:" + to_string(czas_bucket) << endl;
    }


    
    ofstream file2;
    file2.open("C:\\Users\\lukas\\source\\repos\\Project2\\Project2\\projekt2_dane_sorted.txt");

    cout << "Sortowanie merge:  " << czas_merge << endl;       //Wyświetlanie zawartosci bazalic
    cout << "Sortowanie quick:  " << czas_quick << endl;       //Wyświetlanie zawartosci bazalic
    cout << "Sortowanie  insertion:  " << czas_intro << endl;       //Wyświetlanie zawartosci bazalic
    cout << "Sortowanie bucket:  " << czas_bucket << endl;       //Wyświetlanie zawartosci bazalic

    file2.close();

    return 0;
}
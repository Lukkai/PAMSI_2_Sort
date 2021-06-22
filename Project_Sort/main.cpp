#include "film.h"
#include "sortowania.hpp"
#include <chrono>

#define MAX_SIZE 1010194
using namespace std;

int main() {

	cout << "Wpisz wielkosc danych do pozyskania : " << endl;
	int ROZMIAR;
	cin >> ROZMIAR;
	if (ROZMIAR > MAX_SIZE)
		ROZMIAR = MAX_SIZE;
	Film* baza = new (nothrow) Film[ROZMIAR];

	std::chrono::steady_clock::time_point start, end; //pobranie pomiaru czasu startu i konca wykonywania sortowania
	start = std::chrono::high_resolution_clock::now();   //start clock
	double czas_przeszukiwania = 0;

	ifstream file;
	file.open("projekt2_dane.csv");         //Otwarcie pliku

	if (!file.good())
	{                                       //Funkcja sprawdza czy poprawnie wczytano plik
		cout << "Plik nie istnieje" << endl;
		file.close();
		exit(0);
	}
	string linia;
	int numer = -1;                         //numer linii, pierwsza linia ignorowana, -1 zeby uporzadkowac indeksy tablicy od 0
	int dlugosc = 0;                        //dlugosc linii
	int kolumna = 0;                        //kolumna pliku, oddzielona ','
	string sid, stytul, swynik;             //dane odpowiednich kolumn
	while (numer < ROZMIAR && !file.eof())  //zczytuje aż do wersu w pliku ktory bedzie pusty lub do ograniczenia
	{
		if (numer == -1)
		{
			getline(file, sid, '\n');                       //pomin linie, jesli tytulowa
			numer++;
			continue;
		}
		if (kolumna == 0)
		{
			getline(file, sid, ',');                        //pobierz kolumne id
			kolumna++;
		}
		if (kolumna == 1)
		{
			getline(file, stytul, ',');                     //pobierz kolumne tytuly
			size_t found = stytul.find("\"");               //wyszukanie czy string zawiera tytuly w cudzyslowiu
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
			getline(file, swynik, '\n');                    //pobierz kolumne wynik
			kolumna++;
		}


		linia = sid + "," + stytul + "," + swynik;          //sprawdzenie jak wyglada zparsowana linia
		//cout << sid << endl;
		std::string s = ",,";
		//cout << stytul << endl;
		dlugosc = linia.size();
		if (sid == "" || swynik == "" || stytul == "")      //jesli ktoras z kolumn jest pusta, to pomin wpis
		{
			kolumna = 0;
			numer++;
			continue;
		}
		//przypisanie wartosci kolumn do struktury bazy filmowej
		baza[numer].id = (int)atof(sid.c_str());
		baza[numer].tytul = stytul;
		baza[numer].wynik = (int)atof(swynik.c_str());

		//cout << "Ilosc tytulow :  " << baza[numer].id << " " << baza[numer].tytul << " " << baza[numer].wynik << endl;       //Wyświetlanie zawartosci bazalic

		numer++;
		if (kolumna == 3)
			kolumna = 0;
		else
			kolumna++;          //
	}

	file.close();
	end = std::chrono::high_resolution_clock::now();     //stop clock
	czas_przeszukiwania = std::chrono::duration<double, std::milli>(end - start).count();
	cout <<"Czas przeszukiwania bazy w ms: " << czas_przeszukiwania << endl;

	//cout << showpos <<baza[0].wynik << noshowpos << endl;

	int rozmiar2 = 0;                           //zlicz ile pozycji poprzedniej tablicy jest wypelnionych
	for (int i = 0; i < ROZMIAR; i++)
	{
		if (baza[i].wynik > 0)
			rozmiar2++;
	}

	Film* lista_elementow = new Film[rozmiar2];

	int a = 0;
	for (int i = 0; i < ROZMIAR; i++)               //przypisz wartosci wypelnionych pozycji poprzedniej tablicy do nowej 
	{                                               //tablicy, ktora jest jednolicie zapelniona elementami
		if (baza[i].wynik > 0)
		{
			lista_elementow[a] = baza[i];
			a++;
		}
	}
	
	delete[] baza;
	Film* lista_do_sort = new Film[rozmiar2];       //lista do sortowania elemntow

	/***************************************************/
	/*********        SORTOWANIE            ************/
	/***************************************************/

	
	double czas_merge = 0;                            //czasy w ms dla kazdego z sortowan
	double czas_quick = 0;
	double czas_intro = 0;
	double czas_bucket = 0;
	double czas_insertion = 0;
	double czas_heap = 0;
	double czas_rev_quick = 0;
	int opcja;
	std::cout << "Wybierz sortowanie: \n"
		"1. mergesort\n"
		"2. quicksort\n"
		"3. inrosort\n"
		"4. bucketsort\n"
		"5. insertionsort\n"
		"6. heapsort\n"
		"7. revquicksort\n"
		"0. merge, quick, intro, bucket\n";
	std::cin >> opcja;

	if (opcja == 1)											//sortowanie przez scalanie
	{
		for (int index = 0; index < rozmiar2; index++)			//przed startem sortowania 
		{														//wypelnienie sortowanej listy nieposortowanymi elementami
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
	else if (opcja == 2)								//sortowanie szybkie
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
	else if (opcja == 3)								//sortowanie introspektywne
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
		Sort_intro(lista_do_sort, 0, rozmiar2 - 1, (int)log(rozmiar2) * 2);
		//Sort_intro(lista_do_sort, 0, rozmiar2 - 1, 2000);
		end = std::chrono::high_resolution_clock::now();     //stop clock
		czas_intro = std::chrono::duration<double, std::milli>(end - start).count();
		for (int i = 0; i < rozmiar2; i++)
			cout << lista_do_sort[i] << endl;
		if (posortowane(lista_do_sort, rozmiar2))
			cout << "intro posortowane\n";

		cout << "Czas sortowania intro:" + to_string(czas_intro) << endl;
		delete[] lista_do_sort;
	}
	else if (opcja == 4)									//sortowanie kubelkowe
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
	else if (opcja == 5)									//sortowanie przez wstawianie
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
	else if (opcja == 6)									//sortowanie przez kopcowanie
	{
		for (unsigned int index = 0; index < rozmiar2; index++)
		{
			lista_do_sort[index] = lista_elementow[index];
		}
		if (posortowane(lista_do_sort, rozmiar2))
		{
			cout << "posortowane\n";
			return 0;
		}

		start = std::chrono::high_resolution_clock::now();   //start clock
		Sort_kopc(lista_do_sort, 0, rozmiar2-1);
		end = std::chrono::high_resolution_clock::now();     //stop clock
		czas_heap = std::chrono::duration<double, std::milli>(end - start).count();
		for (int i = 0; i < rozmiar2; i++)
			cout << lista_do_sort[i] << endl;
		if (posortowane(lista_do_sort, rozmiar2))
			cout << "heap posortowane\n";

		cout << "Czas sortowania heap:" + to_string(czas_heap) << endl;
		delete[] lista_do_sort;
	}
	else if (opcja == 7)
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
		revQuickSort(lista_do_sort, 0, rozmiar2 - 1);
		end = std::chrono::high_resolution_clock::now();     //stop clock		
		czas_rev_quick = std::chrono::duration<double, std::milli>(end - start).count();
		if (odwrotniePosortowane(lista_do_sort, rozmiar2))
			cout << "revquick posortowane\n";

		cout << "Czas sortowania revquick:" + to_string(czas_rev_quick) << endl;
		delete[] lista_do_sort;
	}
	else if (opcja == 0)								//sortowanie przez scalanie, szybkie, introspektywne, kubelkowe
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
		std::cout << "KOLEJNE SORTOWANIE...\n";


		for (unsigned int index = 0; index < rozmiar2; index++)
		{
			lista_do_sort[index] = lista_elementow[index];
		}
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
		std::cout << "KOLEJNE SORTOWANIE...\n";


		for (unsigned int index = 0; index < rozmiar2; index++)
		{
			lista_do_sort[index] = lista_elementow[index];
		}
		if (posortowane(lista_do_sort, rozmiar2))
		{
			cout << "juz posortowane\n";
			return 0;
		}
		start = std::chrono::high_resolution_clock::now();   //start clock
		Sort_intro(lista_do_sort, 0, rozmiar2 - 1, 2 * (int)log(rozmiar2));
		end = std::chrono::high_resolution_clock::now();     //stop clock
		czas_intro = std::chrono::duration<double, std::milli>(end - start).count();
		if (posortowane(lista_do_sort, rozmiar2))
			cout << "intro posortowane\n";
		cout << "Czas sortowania intro:" + to_string(czas_intro) << endl;
		std::cout << "KOLEJNE SORTOWANIE...\n";


		for (unsigned int index = 0; index < rozmiar2; index++)
		{
			lista_do_sort[index] = lista_elementow[index];
		}
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
		cout << "Czas sortowania bucket:" + to_string(czas_bucket) << endl;

		delete[] lista_do_sort;
		std::cout << "KONIEC SORTOWAN" << endl;
	}
	else
		cout << "Bledny wybor" << endl;


		/**************			STATYSTYKA		  *********************/

		double mediana = 0;
		std::cout << std::endl;
		std::cout << "=======MEDIANA==============" << std::endl;
		if (rozmiar2 % 2 == 1)
		{
			mediana = lista_elementow[rozmiar2 / 2].wynik;         //jak nieparzysta liczba danych to mediana to wartosc srodkowa
			std::cout << mediana << std::endl;
		}
		else
		{
			mediana = lista_elementow[rozmiar2 / 2 - 1].wynik + lista_elementow[rozmiar2 / 2].wynik;
			mediana = mediana / 2;        //jak parzysta liczba danych to mediana to suma dwoch srodkowych podzielona na dwa
			std::cout << mediana << std::endl;
		}
		double srednia = 0;
		for (int i = 0; i < rozmiar2; i++)
		{
			srednia += lista_elementow[i].wynik;    //sumuje wszystkie rankingi
		}
		std::cout << "========WARTOSC SREDNIA===============" << std::endl;
		std::cout << srednia / rozmiar2 << std::endl;    //dzielenie sumy wszystkich rankingow przez ilosc danych aby uzyskac wartosc srednia rankingow

		

	ofstream file2("projekt2_dane_sorted.txt");					//zapisanie wynikow do pliku

	file2 << "Rozmiar rzeczywiscie przeskanowanych danych:  " << numer << endl;		//Wyswietlanie zawartosci bazalic
	file2 << "Czas przeszukiwania bazy w ms: " << czas_przeszukiwania << endl;		//wyswietlanie czasu przeszukiwania bazy
	file2 << "Sortowanie merge:  " << czas_merge << " ms" << endl;					//Wyswietlanie czasow sortowania
	file2 << "Sortowanie quick:  " << czas_quick << " ms" << endl;      
	file2 << "Sortowanie  intro:  " << czas_intro << " ms" << endl;       
	file2 << "Sortowanie bucket:  " << czas_bucket << " ms" << endl;       
	file2 << "Mediana rankingu:  " << mediana << endl;       
	file2 << "Srednia rankingu:  " << srednia << endl;       

	file2.close();

	return 0;
}
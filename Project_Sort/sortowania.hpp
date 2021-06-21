#pragma once
#include "film.h"
#include "heap.hh"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <vector>

/*Zwraca wartosc boolean dla zapytania czy tablica jest posortowana*/
bool posortowane(Film* tablica, int& rozmiar) {
	for (int i = 0; i < rozmiar - 1; i++)
		if (tablica[i].wynik > tablica[i + 1].wynik)
			return false;
	return true;
}

/*Zamienia miejscami elementy*/
template <typename T>
void swapElements(T& elem1, T& elem2) {
	T temp = elem1;
	elem1 = elem2;
	elem2 = temp;
}
/*Funkcja podmieniająca wartości w tablicy o indeksach ind1 oraz ind2*/
void Podmien(Film* tab, int ind1, int ind2) {
	Film temp;                     //zmienna pomocnicza
	temp = tab[ind1];
	tab[ind1] = tab[ind2];
	tab[ind2] = temp;
}

/*****SORTOWANIE PRZEZ SCALANIE*****/
//Sortowanie przez scalanie tablicy tab
//lewa- poczatek tablicy (lewa strona)
//prawa- koniec tablicy (prawa strona)
void Scal(Film* tab, int lewa, int srodek, int prawa);
void Sort_scal(Film* tab, int lewa, int prawa)
{
	if (lewa < prawa)
	{
		int srodek = (lewa + prawa) / 2;
		Sort_scal(tab, lewa, srodek);
		Sort_scal(tab, srodek + 1, prawa);
		Scal(tab, lewa, srodek, prawa);
	}
}

void Scal(Film* tab, int lewa, int srodek, int prawa)
{
	int rozm_lewa = srodek - lewa + 1;
	int rozm_prawa = prawa - srodek;

	Film* lewa_pomoc = new Film[rozm_lewa];
	Film* prawa_pomoc = new Film[rozm_prawa];
	int indexL, indexR, currIndex;

	for (indexL = 0; indexL < rozm_lewa; indexL++)
		lewa_pomoc[indexL] = tab[lewa + indexL];                              //uzupelnianie lewej tablicy

	for (indexR = 0; indexR < rozm_prawa; indexR++)
		prawa_pomoc[indexR] = tab[srodek + 1 + indexR];                              //uzupelnianie prawej tablicy

	indexL = 0; indexR = 0; currIndex = lewa;
	while (indexL < rozm_lewa && indexR < rozm_prawa)
	{
		if (lewa_pomoc[indexL].wynik <= prawa_pomoc[indexR].wynik)       //sprawdzanie wartości 
		{
			tab[currIndex] = lewa_pomoc[indexL];                                       //jesli ocena rowna badz mniejsza z lewej tablicy to ja wstawiamy do listy filmow 
			indexL++;
		}
		else
		{
			tab[currIndex] = prawa_pomoc[indexR];                                      //jesli ocena jest wieksza z prawej tablicy to ja wstawiamy do listy filmow 
			indexR++;
		}
		currIndex++;
	}


	while (indexL < rozm_lewa)                                                       //jesli poprzednia petla while nie wyczerpala indeksow z lewej tablicy
	{                                                                        //to przypisuje wartość do listy filmow
		tab[currIndex] = lewa_pomoc[indexL];
		indexL++; currIndex++;
	}


	while (indexR < rozm_prawa)
	{                                                                        //jesli poprzednia petla while nie wyczerpala indeksow z prawej tablicy
		tab[currIndex] = prawa_pomoc[indexR];                                         //to przypisuje wartość do listy filmow
		indexR++; currIndex++;
	}

	delete[] lewa_pomoc;
	delete[] prawa_pomoc;
}


/*************QUICKSORT*************/
//szybkie sortowanie tablicy tab
//lewa- poczatek tablicy (lewa strona)
//prawa- koniec tablicy (prawa strona)
int Partition(Film* tab, int start, int end) // wektor, początek partycji[Index], koniec partycji[Index]
{
	int k = (start + end) / 2;  //jako PIVOT wybieramy wartość o środkowym indeksie
	//int k=end-1;            //Jako PIVOT wybieramy wartość o przedostatnim indeksie
	int pivot = tab[k].wynik;
	int s = start;// zawsze na lewo
	int e = end;// zawsze na prawo
	while (true)
	{
		while (tab[e].wynik > pivot)// Idziemy od końca w lewo if (koniec > pivota) dopóki zaczynamy od pierwszyego elem
			e--;

		while (tab[s].wynik < pivot)
			s++;

		if (s < e) // zamieniamy miejscami gdy i < j na lewo od pivota dajemy elem. mniejsze od pivota, na prawo zaś większe od pivota elem. 
		{
			swapElements(tab[s], tab[e]);
			s++;
			e--;
		}
		else
			return e;// gdy i >= j zwraca j jako oś podziału tablicy (no jak się indeksy spotkają, że tak powiem)
	}

}

void QuickSort(Film* tab, int start, int end) {// sortowanie szybkie

	if (start < end) {
		int p = Partition(tab, start, end);// dziele tablice na dwie czesci, gdzie end to punkt podzialu
		QuickSort(tab, start, p);// rekurencyjnie quicksort dla pierwszej (lewej) czesci tablicy
		QuickSort(tab, p + 1, end);// rekurencyjnie quicksort dla drugiej (prawej) czesci tablicy
	}
}

void Sort_wst(Film* tab, int rozm) {
	Film pomoc;
	int j;
	for (int i = 1; i < rozm; i++) {
		pomoc = tab[i];
		j = i;
		while (j > 0 && tab[j - 1].wynik > pomoc.wynik) {
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = pomoc;
	}
}

//HEAPSORT POTRZEBNY DO INTROSORT
/****SORTOWANIE PRZEZ KOPCOWANIE****/
//Sortowanie przez kopcowanie tablicy tab
//rozm- rozmiar tablicy
//korzen- poczatek tablicy (root)
void Utworz_Kopiec(Film* tab, int rozm, int korzen) {
	int Max = korzen;
	int lewysyn = 2 * korzen + 1;
	int prawysyn = 2 * korzen + 2;

	if (lewysyn<rozm && tab[lewysyn].wynik >tab[Max].wynik) Max = lewysyn;
	if (prawysyn<rozm && tab[prawysyn].wynik>tab[Max].wynik) Max = prawysyn;

	if (Max != korzen) {
		Podmien(tab, Max, korzen);

		Utworz_Kopiec(tab, rozm, Max);
	}
}

/****SORTOWANIE PRZEZ WSTAWIANIE****/
//Sortowanie przez wstawianie tablicy tab
//rozm- rozmiar tablicy
void Sort_kopc(Film* tab, int rozm) {
	for (int i = rozm / 2 - 1; i >= 0; i--)
		Utworz_Kopiec(tab, rozm, i);

	for (int i = rozm - 1; i >= 0; i--) {
		Podmien(tab, 0, i);

		Utworz_Kopiec(tab, i, 0);
	}
}



/***********INTROSPEKTYWNE**********/
//Sortowanie introspektywne tablicy tab
//lewa- poczatek tablicy (lewa strona)
//prawa- koniec tablicy (prawa strona)
//glebokosc- maksymalna glebokosc rekursji
int Podziel(Film* tab, int lewa, int prawa) {

	int i = lewa, j = prawa;

	int pkt_od = tab[(lewa + prawa) / 2].wynik;
	i--;
	j++;
	while (1)
	{
		while (pkt_od > tab[++i].wynik);
		while (pkt_od < tab[--j].wynik);
		if (i <= j)
			Podmien(tab, i, j);
		else
			return j;
	}
}

void Sort_intro(Film* tab, int lewa, int prawa, int glebokosc) {
	if ((prawa - lewa) < 16)   Sort_wst(tab, prawa - lewa + 1);
	else if (glebokosc == 0) Sort_kopc(tab, prawa - lewa + 1);
	else {
		int pkt_od = Podziel(tab, lewa, prawa);
		Sort_intro(tab, lewa, pkt_od - 1, glebokosc - 1);
		Sort_intro(tab, pkt_od + 1, prawa, glebokosc - 1);
	}
}

//void bucketSort(Film* tab, int rozmiar)
//{
//   
//    int tablica_koszy[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
//    Film** kubelki = new Film* [11];
//
//    for (int i = 0; i < 11; i++)                                         //tworzenie kubełków
//    {
//        kubelki[i] = new Film[rozmiar];
//    }
//    
//    for (int i = 0; i < rozmiar; i++)                             //przypisywanie filmów kubełkom
//    {
//        for (int a = 0; a < 11; a++)
//        {
//            if (tab[i].wynik == a)
//            {
//                kubelki[a][tablica_koszy[a]] = tab[i];
//                tablica_koszy[a]++;
//            }
//        }
//    }
//
//    int przypisany_kosz = 0;
//
//    for (int i = 0; i < 11; i++)                                   //przypisywanie wartości kubełków do listy filmów
//    {
//        for (int a = 0; a < tablica_koszy[i]; a++)
//        {
//            tab[przypisany_kosz] = kubelki[i][a];
//            przypisany_kosz++;
//        }
//    }
//
//    delete[] kubelki;
//}


/***************************************
 ******    BUCKETSORT   ****************
 **************************************/
void bucketSort(Film* tab, int rozmiar)
{
	/*
	* Szukamy minimalnej i maksymalnej wartosci w tablicy
	*/
	long int minWartosc = tab[0].wynik, maxWartosc = tab[0].wynik;

	for (int i = 1; i < rozmiar; i++) {
		if (tab[i].wynik > maxWartosc)
			maxWartosc = tab[i].wynik;
		if (tab[i].wynik < minWartosc)
			minWartosc = tab[i].wynik;
	}

	/*
	 *      bucketLength - ile koszykow utowrzyc
	 */
	int dlugoscKoszyka = maxWartosc - minWartosc + 1;
	/*
	 * Dynamiaczna tablica vectora bucket
	 */
	vector<Film>* koszyk = new vector<Film>[dlugoscKoszyka];
	for (int i = 0; i < dlugoscKoszyka; i++)
		koszyk[i] = vector<Film>();


	/*
	 * Wrzucamy do koszykow odpowiednie wartosci
	 */
	for (long int i = 0; i < rozmiar; i++)
		koszyk[tab[i].wynik - minWartosc].push_back(tab[i]);

	/*
	 * kolejne koszyki sa laczone i ich wartosci przypiswyane do tablicy
	 */
	long int k = 0;
	for (int i = 0; i < dlugoscKoszyka; i++) {
		if (koszyk[i].size() > 0) {
			for (long int j = 0; j < koszyk[i].size(); j++, k++) {
				tab[k] = koszyk[i][j];
			}
		}
	}
	delete[] koszyk;
}
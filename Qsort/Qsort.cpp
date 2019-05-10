// Qsort.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <windows.h>

using namespace std;
using namespace sf;

//RenderWindow window(VideoMode(1000, 500), "SFML works!");
const int N = 1000;
int tab[N];

void losuj() // losowanie tablicy
{
	srand(time(0));

	for (int i = 0; i < N; i++)
	{
		int k;
		bool test;
		do {
			k = rand() % N;
			test = true;

			for (int j = 0; j < i; j++) //Mechanizm przeciw powatarzaniu się
			{
				if (tab[j] == k) test = false;
			}
		} while (test == false);
		tab[i] = k;
	}
}

void pokaz(RenderWindow &window) //funkcja pokazujaca tablice w formie 
{
	window.clear(Color::Red);
	vector <RectangleShape> eh;
	
	Vector2f hh(1,0);

	for (int i = 0; i < N; i++)
	{
		
		hh.y = tab[i];
		RectangleShape test(hh);
		test.setSize(hh);
		test.setPosition(i,0);
		test.setFillColor(Color::Black);
		eh.push_back(test);
	}
	for (int i = 0; i < N; i++)
		window.draw(eh[i]);
	window.display();
//TO DO
}

void zamien(int i, int j) // zamieniamy  wartosci w dwoch miejscach
{
	int pom = tab[i];
	tab[i] = tab[j];
	tab[j] = pom;
}

int PodzielTablice(int Lew, int Pra)
{
	int Podzial = (Lew + (Pra - 1)) / 2;
	int wartoscPodzialu = tab[Podzial]; //znamy wartosc podzialu

	zamien(Podzial, Pra); //przerzucamy podzial na koniec tablicy
	int AktualnaP = 0;

	for (int i = 0; i < Pra; i++)
	{
		if (tab[i] > wartoscPodzialu)
			//jezeli element mniejszy niz wartoscpodzialu przerzuc na lewo 
			// w przeciwnym wypadku zostaw na prawej stronie
		{
			zamien(i, AktualnaP);
			AktualnaP++;
		}
	}
	zamien(AktualnaP, Pra);
	return AktualnaP;
}

void SzybkieSort(int Lew, int Pra, RenderWindow &window)
{
	int i;
	if (Lew < Pra) // jesli fragment dluzszy niz 1 element
	{
		//Sleep(10);
		pokaz(window);
		i = PodzielTablice(Lew, Pra);
		// podziel tablice na 2 czesci i podziel elementy na wieksze i mniejsze wedlug podzialku
		SzybkieSort(Lew, i - 1, window);
		SzybkieSort(i + 1, Pra, window);
	}
}


int main() 
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	losuj();
	bool sort = false;
	window.setFramerateLimit(0);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		losuj();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if(sort==false)
			SzybkieSort(0, N-1, window);
		sort = true;
	}

	return 0;
}
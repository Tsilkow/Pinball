#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include "kulka.hpp"
#include "odbijacz.hpp"


class Plansza
{
    private:
    std::vector<std::shared_ptr<Kulka>> kulki;
    std::vector<std::shared_ptr<Kulka>> zastopowane;
    std::vector<std::shared_ptr<Odbijacz>> odbijacze;
    int liczbaTur;
    int szerokosc;
    int wysokosc;
    int czasDoWybuchu;
    int obecnaTura;
    
    public:
    // Plansza bez szerokości i wysokości nie jest Planszą
    Plansza() = delete;

    // Ponieważ wszystkie zmienne Planszy są proste albo kontenerami z STLa, to destruktor domyślny w pełni wystarcza
    ~Plansza() = default;

    Plansza(const Plansza& oryginal) = default;

    void operator= (const Plansza& wartosc) = delete;

    // Konstruktor Planszy
    Plansza(int _liczbaTur, int _szerokosc, int _wysokosc, int _czasDoWybuchu):
	liczbaTur(_liczbaTur),
	szerokosc(_szerokosc),
	wysokosc(_wysokosc),
	czasDoWybuchu(_czasDoWybuchu),
	obecnaTura(0)
	{;}
    
    bool dodajKulke(std::pair<int, int> pozycja, char typ);
    
    bool dodajOdbijacz(std::pair<int, int> pozycja, char typ);
    
    bool zrobTure();

    // Wypisuje status kulki
    void status();
};

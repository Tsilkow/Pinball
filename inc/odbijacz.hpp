#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include "kulka.hpp"


class Odbijacz
{
    protected:
    std::pair<int, int> pozycja;
    public:
    // Odbijacz bez określonej pozycji nie istnieje
    Odbijacz() = delete;

    // Ponieważ jedyną zmienną Odbijacza jest kontener z STL, to destruktor domyślny w pełni wystarczy
    ~Odbijacz() = default;

    // Konstruktor Odbijacza
    Odbijacz(std::pair<int, int> _pozycja): pozycja(_pozycja) {;}

    // Wirtualna metoda, bo odbijacze mogą robić skrajnie różne rzeczy; zwraca czy Odbijacz i Kulka przeżyły odbicie (w tej kolejności)
    virtual std::pair<bool, bool> odbij(std::shared_ptr<Kulka>& kulka) = 0;

    // Wypisuje status odbijacza
    void status(bool enter=true);

    const std::pair<int, int>& getPozycja() const {return pozycja; }
};

class Ukosny: public Odbijacz
{
    private:
    int skos; // 0 = \, 1 = /
    public:
    Ukosny(std::pair<int, int> _pozycja, int _skos): Odbijacz(_pozycja), skos(_skos) {;}
    std::pair<bool, bool> odbij(std::shared_ptr<Kulka>& kulka);
};
    
class Losowy: public Odbijacz
{
    public:
    Losowy(std::pair<int, int> _pozycja): Odbijacz(_pozycja) {;}
    std::pair<bool, bool> odbij(std::shared_ptr<Kulka>& kulka);
};
  
class Zjadajacy: public Odbijacz
{
    public:
    Zjadajacy(std::pair<int, int> _pozycja): Odbijacz(_pozycja) {;}
    std::pair<bool, bool> odbij(std::shared_ptr<Kulka>& kulka);
};
    
class Predkosciowy: public Odbijacz
{
    private:
    bool przyspieszajacy;
    public:
    Predkosciowy(std::pair<int, int> _pozycja, bool _przyspieszajacy):
	Odbijacz(_pozycja), przyspieszajacy(_przyspieszajacy) {;}
    std::pair<bool, bool> odbij(std::shared_ptr<Kulka>& kulka);
};
  
class Mglowy: public Odbijacz
{
    public:
    Mglowy(std::pair<int, int> _pozycja): Odbijacz(_pozycja) {;}
    std::pair<bool, bool> odbij(std::shared_ptr<Kulka>& kulka);
};

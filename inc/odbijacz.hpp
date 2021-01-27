#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include "kulka.hpp"


class Odbijacz
{
    protected:
    std::pair<int, int> pozycja;
    bool zniszczony;
    public:
    // Odbijacz bez określonej pozycji nie istnieje (tak samo dla klas dziedziczących)
    Odbijacz() = delete;

    // Ponieważ jedyną zmienną Odbijacza jest kontener z STL, to destruktor domyślny w pełni wystarczy (tak samo dla klas dziedziczących)
    ~Odbijacz() = default;

    Odbijacz(const Odbijacz& oryginal) = default;

    void operator= (const Odbijacz&) = delete;

    // Konstruktor Odbijacza
    Odbijacz(std::pair<int, int> _pozycja): pozycja(_pozycja), zniszczony(false) {;}

    // Wirtualna metoda, bo odbijacze mogą robić skrajnie różne rzeczy; zwraca czy Odbijacz i Kulka przeżyły odbicie (w tej kolejności)
    virtual void odbij(const std::shared_ptr<Kulka>& kulka) = 0;

    // Wypisuje status odbijacza
    void status(bool enter=true);

    const std::pair<int, int>& getPozycja() const {return pozycja; }
    const bool czyZniszczony() const {return zniszczony; }
};

class Ukosny: public Odbijacz
{
    private:
    int skos; // 0 = \, 1 = /
    public:
    Ukosny(std::pair<int, int> _pozycja, int _skos): Odbijacz(_pozycja), skos(_skos) {;}
    void odbij(const std::shared_ptr<Kulka>& kulka) override;
};
    
class Losowy: public Odbijacz
{
    public:
    Losowy(std::pair<int, int> _pozycja): Odbijacz(_pozycja) {;}
    void odbij(const std::shared_ptr<Kulka>& kulka) override;
};
  
class Zjadajacy: public Odbijacz
{
    public:
    Zjadajacy(std::pair<int, int> _pozycja): Odbijacz(_pozycja) {;}
    void odbij(const std::shared_ptr<Kulka>& kulka) override;
};
    
class Predkosciowy: public Odbijacz
{
    private:
    bool przyspieszajacy;
    public:
    Predkosciowy(std::pair<int, int> _pozycja, bool _przyspieszajacy):
	Odbijacz(_pozycja), przyspieszajacy(_przyspieszajacy) {;}
    void odbij(const std::shared_ptr<Kulka>& kulka) override;
};
  
class Mglowy: public Odbijacz
{
    public:
    Mglowy(std::pair<int, int> _pozycja): Odbijacz(_pozycja) {;}
    void odbij(const std::shared_ptr<Kulka>& kulka) override;
};

#pragma once

#include <iostream>
#include <memory>


class Kulka
{
    protected:
    std::pair<int, int> pozycja;
    int odwrotnoscPredkosci;
    int kierunek;
    int postep;
    int typ;
    
    public:
    Kulka() = delete;
    Kulka(std::pair<int, int> _pozycja, int s, int w, int _typ);
    virtual bool zrobRuch() = 0; // zwraca czy jest na nowej pozycji
    bool czyWRamach(int s, int w);
    virtual void zderzenie(std::shared_ptr<Kulka>& kulka)=0;
    int getTyp() {return typ; }
    void status(bool enter = true);

    const std::pair<int, int>& getPozycja() const {return pozycja; }
    const int& getOdwPredkosci() const {return odwrotnoscPredkosci; }
    const int& getKierunek() const {return kierunek; }
    const int& getPostep() const {return postep; }
    void setOdwPredkosci(int wartosc) {odwrotnoscPredkosci = wartosc; }
    void setKierunek(int wartosc) {kierunek = wartosc; }
    void setPostep(int wartosc) {postep = wartosc; }
};

class Zwykla: public Kulka
{
    public:
    Zwykla(std::pair<int, int> _pozycja, int s, int w): Kulka(_pozycja, s, w, 0) {;}
    bool zrobRuch(); // zwraca czy jest na nowej pozycji
    void zderzenie(std::shared_ptr<Kulka>& kulka);
};

class Taran: public Kulka
{
    public:
    Taran(std::pair<int, int> _pozycja, int s, int w): Kulka(_pozycja, s, w, 1) {;}
    bool zrobRuch(); // zwraca czy jest na nowej pozycji
    void zderzenie(std::shared_ptr<Kulka>& kulka);
};

class Wybuchowa: public Kulka
{
    private:
    int czasDoWybuchu;
    public:
    Wybuchowa(std::pair<int, int> _pozycja, int s, int w, int _czasDoWybuchu):
	Kulka(_pozycja, s, w, 2),
	czasDoWybuchu(_czasDoWybuchu)
	{;}
    bool zrobRuch(); // zwraca czy jest na nowej pozycji
    void zderzenie(std::shared_ptr<Kulka>& kulka);
    bool czyWybuchla() {return (czasDoWybuchu <= 0); }
};

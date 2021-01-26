#pragma once

#include <iostream>
#include <memory>


enum TypKulki {zwykla, taran, wybuchowa};

class Kulka
{
    protected:
    std::pair<int, int> pozycja;
    TypKulki typ;
    int odwrotnoscPredkosci;
    int kierunek;
    int postep;
    bool nowaKratka;
    
    public:
    // Kulka bez określonej pozycji i typu nie istnieje
    Kulka() = delete;

    // Ponieważ wszystkie zmienne Kulki są proste albo kontenerami z STLa, to destruktor domyślny w pełni wystarcza
    ~Kulka() = default;

    // Konstruktor Kulki, zmienne s i w (szerokość i wysokość), aby kulka mogła od razu stwierdzić w jakim kierunku ma się poruszać
    Kulka(std::pair<int, int> _pozycja, int s, int w, TypKulki _typ);

    virtual bool zrobRuch() = 0;

    bool czyWRamach(int s, int w);

    virtual void zderzenie(std::shared_ptr<Kulka>& kulka)=0;

    // Zwraca jakiego typu jest kulka. Niestety jest to potrzebne, dla kulek których działania wykracza poza samą kulkę
    TypKulki getTyp() {return typ; }

    // Wypisuje status kulki
    void status(bool enter = true);

    const std::pair<int, int>& getPozycja() const {return pozycja; }
    const int& getOdwPredkosci() const {return odwrotnoscPredkosci; }
    const int& getKierunek() const {return kierunek; }
    const int& getPostep() const {return postep; }
    const bool WNowejKratce() {return nowaKratka; }
    void setOdwPredkosci(int wartosc) {odwrotnoscPredkosci = wartosc; }
    void setKierunek(int wartosc) {kierunek = wartosc; }
    void setPostep(int wartosc) {postep = wartosc; }
};

class Zwykla: public Kulka
{
    public:
    Zwykla(std::pair<int, int> _pozycja, int s, int w): Kulka(_pozycja, s, w, TypKulki::zwykla) {;}
    bool zrobRuch();
    void zderzenie(std::shared_ptr<Kulka>& kulka);
};

class Taran: public Kulka
{
    public:
    Taran(std::pair<int, int> _pozycja, int s, int w): Kulka(_pozycja, s, w, TypKulki::taran) {;}
    bool zrobRuch();
    void zderzenie(std::shared_ptr<Kulka>& kulka);
};

class Wybuchowa: public Kulka
{
    private:
    int czasDoWybuchu;
    public:
    Wybuchowa(std::pair<int, int> _pozycja, int s, int w, int _czasDoWybuchu):
	Kulka(_pozycja, s, w, TypKulki::wybuchowa),
	czasDoWybuchu(_czasDoWybuchu)
	{;}
    bool zrobRuch();
    void zderzenie(std::shared_ptr<Kulka>& kulka);
    bool czyWybuchla() {return (czasDoWybuchu <= 0); }
};

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
    bool koliduje;
    bool zniszczona;
    
    public:
    // Kulka bez określonej pozycji i typu nie istnieje (tak samo dla klas dziedziczących)
    Kulka() = delete;

    // Ponieważ wszystkie zmienne Kulki są proste albo kontenerami z STLa, to destruktor domyślny w pełni wystarcza (tak samo dla klas dziedziczących)
    ~Kulka() = default;

    Kulka(const Kulka& oryginal) = default;

    void operator= (const Kulka& wartosc) = delete;

    // Konstruktor Kulki, zmienne s i w (szerokość i wysokość), aby kulka mogła od razu stwierdzić w jakim kierunku ma się poruszać
    Kulka(std::pair<int, int> _pozycja, int s, int w, TypKulki _typ);

    virtual bool zrobRuch();

    // Funkcja pomocnicza do samego wykonywania ruchu w zadanym kierunku
    bool krokWKierunku();

    bool czyWRamach(int s, int w);

    virtual void zderzenie(const std::shared_ptr<Kulka>& kulka)=0;

    // Zwraca jakiego typu jest kulka. Niestety jest to potrzebne, dla kulek których działania wykracza poza samą kulkę
    TypKulki getTyp() {return typ; }

    // Wypisuje status kulki
    void status(bool enter = true);

    // Zapisuje, że kulka została zniszczona
    void zniszcz() {zniszczona = true; }

    const std::pair<int, int>& getPozycja() const {return pozycja; }
    const int& getOdwPredkosci() const {return odwrotnoscPredkosci; }
    const int& getKierunek() const {return kierunek; }
    const int& getPostep() const {return postep; }
    virtual const bool czyZniszczona() const {return zniszczona; }
    const bool czyKoliduje() {return koliduje; }
    void setOdwPredkosci(int wartosc) {odwrotnoscPredkosci = wartosc; }
    void setKierunek(int wartosc) {kierunek = wartosc; }
    void setPostep(int wartosc) {postep = wartosc; }
};

class Zwykla: public Kulka
{
    public:
    Zwykla(std::pair<int, int> _pozycja, int s, int w): Kulka(_pozycja, s, w, TypKulki::zwykla) {;}
    void zderzenie(const std::shared_ptr<Kulka>& kulka) override;
};

class Taran: public Kulka
{
    public:
    Taran(std::pair<int, int> _pozycja, int s, int w): Kulka(_pozycja, s, w, TypKulki::taran) {;}
    void zderzenie(const std::shared_ptr<Kulka>& kulka) override;
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
    void zderzenie(const std::shared_ptr<Kulka>& kulka) override;
    const bool czyZniszczona() const override {return zniszczona || (czasDoWybuchu < 0); }
};

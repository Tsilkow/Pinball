#pragma once


class Kulka
{
    protected:
    std::pair<int, int> pozycja;
    int odwrotnoscPredkosci;
    int kierunek;
    int postep;
    
    public:
    Kulka() = delete;
    Kulka(std::pair<int, int> _pozycja, int s, int w);
    virtual bool zrobRuch() = 0; // zwraca czy jest na nowej pozycji
    bool czyWRamach(int s, int w);
    virtual void zderzenie(std::shared_ptr<Kulka>& kulka) = 0;
};

class Zwykla: public Kulka
{
    public:
    Zwykla(std::pair<int, int> _pozycja, int s, int w): Kulka(pozycja, s, w)
    bool zrobRuch(); // zwraca czy jest na nowej pozycji
    void zderzenie(std::shared_ptr<Kulka>& kulka);
};

class Taran: public Kulka
{
    public:
    Taran(std::pair<int, int> _pozycja, int s, int w): Kulka(pozycja, s, w)
    bool zrobRuch(); // zwraca czy jest na nowej pozycji
    void zderzenie(std::shared_ptr<Kulka>& kulka);
};

class Wybuchowa: public Kulka
{
    private:
    int czasDoWybuchu;
    public:
    Wybuchowa(std::pair<int, int> _pozycja, int _czasDoWybuchu);
    bool zrobRuch(); // zwraca czy jest na nowej pozycji
    void zderzenie(std::shared_ptr<Kulka>& kulka);
}

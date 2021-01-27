#include "kulka.hpp"


Kulka::Kulka(std::pair<int, int> _pozycja, int s, int w, TypKulki _typ):
    pozycja(_pozycja),
    typ(_typ),
    odwrotnoscPredkosci(1),
    postep(0),
    koliduje(true),
    zniszczona(false)
{
    if(pozycja.first == -1) // lewa strona planszy
    {
	if     (pozycja.second == -1) kierunek = 3; // lewy górny narożnik
	else if(pozycja.second == w ) kierunek = 1; // lewy dolny narożnik
	else                          kierunek = 2; // lewa ściana
    }
    else if(pozycja.first == s) // prawa strona planszy
    {
	if     (pozycja.second == -1) kierunek = 5; // prawy górny narożnik
	else if(pozycja.second == w ) kierunek = 7; // prawy dolny narożnik
	else                          kierunek = 6; // prawa ściana
    }
    else if(pozycja.second == -1) kierunek = 4; // górna ściana
    else if(pozycja.second == w ) kierunek = 0; // dolna ściana
    else std::cout << "!BŁĄD! Kulka nie startuje na krawędzi planszy!" << std::endl;
}

bool Kulka::czyWRamach(int s, int w)
{
    return (pozycja.first >= 0 && pozycja.first < s && pozycja.second >= 0 && pozycja.second < w);
}

bool Kulka::krokWKierunku()
{
    ++postep;
    if(postep >= odwrotnoscPredkosci)
    {
	postep = 0;
	switch(kierunek)
	{
	    case 0:                  --pozycja.second; break; // północ
	    case 1: ++pozycja.first; --pozycja.second; break; // północny zachód
	    case 2: ++pozycja.first;                 ; break; // zachód
	    case 3: ++pozycja.first; ++pozycja.second; break; // południowy zachód
	    case 4:                  ++pozycja.second; break; // południe
	    case 5: --pozycja.first; ++pozycja.second; break; // południowy wschód
	    case 6: --pozycja.first;                 ; break; // wschód
	    case 7: --pozycja.first; --pozycja.second; break; // północny wschód
	}
	koliduje = true;
    }
    else koliduje = false;
    
    return koliduje;
}

bool Kulka::zrobRuch()
{
    return krokWKierunku();
}

void Kulka::status(bool enter)
{
    std::cout << "{";
    switch(typ)
    {
	case zwykla:    std::cout << "Zwykla"; break;
	case taran:     std::cout << "Taran"; break;
	case wybuchowa: std::cout << "Wybuchowa"; break;
    }
    std::cout << ", (" << pozycja.first << ", " << pozycja.second << "), "
	      << odwrotnoscPredkosci << ", " << kierunek << ", " << postep << "}";
    if(enter) std::cout << "\n";
}

void Zwykla::zderzenie(const std::shared_ptr<Kulka>& kulka)
{
    // Ponieważ w Planszy kulki są trzymane w takiej kolejności, że zwykła kulka nie będzie pierwsza w parze z inną niż zwykła kulka, to tutaj nie ma potrzeby obsługiwać innych zderzeń niż ze zwykłą kulką
    
    int tempP = odwrotnoscPredkosci;
    int tempK = kierunek;
    int tempPo = postep;
    odwrotnoscPredkosci = kulka->getOdwPredkosci();
    kierunek = kulka->getKierunek();
    postep = kulka->getPostep();

    kulka->setOdwPredkosci(tempP);
    kulka->setKierunek(tempK);
    kulka->setPostep(tempPo);
}

void Taran::zderzenie(const std::shared_ptr<Kulka>& kulka)
{
    kulka->zniszcz();
    if(kulka->getTyp() == TypKulki::taran) zniszczona = true;
}

bool Wybuchowa::zrobRuch()
{
    --czasDoWybuchu;
    if(czasDoWybuchu >= 0)
    {
	return krokWKierunku();
    }
    return true;
}

void Wybuchowa::zderzenie(const std::shared_ptr<Kulka>& kulka)
{
    if(czasDoWybuchu >= 0)
    {
	// Nie muszę robić oddzielnego przypadku, kiedy druga kulka jest wybuchowa, bo wszystkie wybuchają w tym samym czasie
        if(kulka->getTyp() == TypKulki::taran) zniszczona = true;
	else
	{
	    int tempP = odwrotnoscPredkosci;
	    int tempK = kierunek;
	    int tempPo = postep;
	    odwrotnoscPredkosci = kulka->getOdwPredkosci();
	    kierunek = kulka->getKierunek();
	    postep = kulka->getPostep();

	    kulka->setOdwPredkosci(tempP);
	    kulka->setKierunek(tempK);
	    kulka->setPostep(tempPo);
	}
    }
    else
    {
	zniszczona = true;
	kulka->zniszcz();
    }    
}

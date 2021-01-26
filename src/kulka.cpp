#include "kulka.hpp"


Kulka::Kulka(std::pair<int, int> _pozycja, int s, int w, TypKulki _typ):
    pozycja(_pozycja),
    typ(_typ),
    odwrotnoscPredkosci(1),
    postep(0),
    nowaKratka(true)
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

bool Zwykla::zrobRuch()
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
	nowaKratka = true;
    }
    else nowaKratka = false;
    
    return nowaKratka;
}

void Zwykla::zderzenie(std::shared_ptr<Kulka>& kulka)
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


bool Taran::zrobRuch()
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
	return true;
    }
    return false;
}

void Taran::zderzenie(std::shared_ptr<Kulka>& kulka)
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

bool Wybuchowa::zrobRuch()
{
    --czasDoWybuchu;
    if(czasDoWybuchu >= 0)
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
	    return true;
	}	
    }
    return false;
}

void Wybuchowa::zderzenie(std::shared_ptr<Kulka>& kulka)
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

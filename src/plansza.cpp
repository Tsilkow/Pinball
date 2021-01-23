#include "plansza.hpp"

bool Plansza::dodajKulke(std::pair<int, int> pozycja, char typ)
{
    switch(typ)
    {
	case 'z': kulki.emplace_back(std::make_shared<Zwykla>(pozycja, szerokosc, wysokosc)); break;
	case 't': kulki.emplace_back(std::make_shared<Taran>(pozycja, szerokosc, wysokosc)); break;
	case 'w': kulki.emplace_back(std::make_shared<Wybuchowa>(pozycja, szerokosc, wysokosc, czasDoWybuchu)); break;
	default: return false;
    }
    return true;
}

bool Plansza::dodajOdbijacz(std::pair<int, int> pozycja, char typ)
{
    switch(typ)
    {
	case 'u': odbijacze.emplace_back(std::make_shared<Ukosny>(pozycja, 0)); break;
	case 'U': odbijacze.emplace_back(std::make_shared<Ukosny>(pozycja, 1)); break;
	case 'l': odbijacze.emplace_back(std::make_shared<Losowy>(pozycja)); break;
	case 'z': odbijacze.emplace_back(std::make_shared<Zjadajacy>(pozycja)); break;
	case 's': odbijacze.emplace_back(std::make_shared<Predkosciowy>(pozycja, false)); break;
	case 'm': odbijacze.emplace_back(std::make_shared<Mglowy>(pozycja)); break;
	case 'p': odbijacze.emplace_back(std::make_shared<Predkosciowy>(pozycja, true)); break;
	default: return false;
    }
    return true;
}

bool Plansza::zrobTure()
{
    std::set< std::pair<int, int> > wybuchy;
    
    for(auto it = kulki.begin(); it != kulki.end(); ++it)
    {
	(*it)->zrobRuch();
	if(typeid(it->get()).name() == "Wybuchowa" && std::static_pointer_cast<Wybuchowa>(*it)->czyWybuchla())
	{
	    wybuchy.insert((*it)->getPozycja());
	}
    }

    for(auto it = kulki.begin(); it != kulki.end();)
    {
	if(wybuchy.find((*it)->getPozycja()) != wybuchy.end())
	{
	    it = kulki.erase(it);
	}
	else ++it;
    }

    for(auto it = kulki.begin(); it != kulki.end(); ++it)
    {
	for(auto jt = it+1; jt != kulki.end(); ++jt)
	{
	    if((*it)->getPozycja() == (*jt)->getPozycja()) (*it)->zderzenie(*jt);
	}
    }

    for(auto it = odbijacze.begin(); it != odbijacze.end(); ++it)
    {
	for(auto jt = kulki.begin(); jt < kulki.end(); ++jt)
	{
	    if((*it)->getPozycja() == (*jt)->getPozycja())
	    {
		std::pair<bool, bool> wynik = (*it)->odbij(*jt);

		if(wynik.first == false) it = odbijacze.erase(it);
		if(wynik.second == false) jt = kulki.erase(jt);
	    }
	}
    }

    ++obecnaTura;
    if(obecnaTura >= liczbaTur) return false;
    return true;
}

void Plansza::status()
{
    std::cout << "======STATUS======\n";
    std::cout << "Kulki: \n";
    for(auto it = kulki.begin(); it != kulki.end(); ++it)
    {
	(*it)->status(true);
    }
    
    std::cout << "Odbijacze: \n";
    for(auto it = odbijacze.begin(); it != odbijacze.end(); ++it)
    {
	(*it)->status(true);
    }
    std::cout << "==================\n";
}

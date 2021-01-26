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

    // wykonywanie ruchów, sprawdzanie czy kulka wciąż na planszy i rejestrowanie wybuchów
    for(auto it = kulki.begin(); it != kulki.end();)
    {
	(*it)->zrobRuch();
	if(!(*it)->czyWRamach(szerokosc, wysokosc))
	{
	    zastopowane.push_back(*it);
	    it = kulki.erase(it);
	}
	else if((*it)->getTyp() == TypKulki::wybuchowa &&
		std::static_pointer_cast<Wybuchowa>(*it)->czyWybuchla())
	{
	    std::cout << "WYBUCH W " << (*it)->getPozycja().first << " "
		      << (*it)->getPozycja().second << "\n";
	    wybuchy.insert((*it)->getPozycja());
	    it = kulki.erase(it);
	}
	else ++it;
    }

    // niszczenie kulek na polach z wybuchem
    for(auto it = kulki.begin(); it != kulki.end();)
    {
	if(wybuchy.find((*it)->getPozycja()) != wybuchy.end())
	{
	    it = kulki.erase(it);
	}
	else ++it;
    }

    // niszczenie odbijaczy na polach z wybuchem
    for(auto it = odbijacze.begin(); it != odbijacze.end();)
    {
	if(wybuchy.find((*it)->getPozycja()) != wybuchy.end())
	{
	    it = odbijacze.erase(it);
	}
	else ++it;
    }

    // obsługa zderzeń kulek: kulki zderzają się ze sobą parami
    for(auto it = kulki.begin(); it != kulki.end(); ++it)
    {
	if((*it)->WNowejKratce())
	{
	    for(auto jt = kulki.begin(); jt != kulki.end(); ++jt)
	    {
		if(it != jt && (it < jt || !(*jt)->WNowejKratce()) &&
		   (*it)->getPozycja() == (*jt)->getPozycja())
		{
		    std::cout << "ZDERZENIE KULEK W " << (*it)->getPozycja().first << " "
			      << (*it)->getPozycja().second << "\n";
		    (*it)->zderzenie(*jt);
		}
	    }
	}
    }

    // obsługa odbić kulek
    for(auto it = odbijacze.begin(); it != odbijacze.end();)
    {
	bool zniszczony = false;
	for(auto jt = kulki.begin(); !zniszczony && jt != kulki.end();)
	{
	    if((*it)->getPozycja() == (*jt)->getPozycja())
	    {
		std::cout << "ODBICIE W " << (*it)->getPozycja().first << " "
			  << (*it)->getPozycja().second << "\n";
		std::pair<bool, bool> wynik = (*it)->odbij(*jt);

		// jeśli odbicie zniszczyło odbijacz
		if(wynik.first == false)
		{
		    it = odbijacze.erase(it);
		    zniszczony = true;
		}
		// jeśli odbicie znisczyło kulkę
		if(wynik.second == false) jt = kulki.erase(jt);
		else ++jt;
	    }
	    else ++jt;
	}
	if(!zniszczony) ++it;
    }

    ++obecnaTura;
    if(obecnaTura >= liczbaTur) return false;
    return true;
}

void Plansza::status()
{
    std::cout << "======STATUS======\n";
    std::cout << "Kulki aktywne: \n";
    for(auto it = kulki.begin(); it != kulki.end(); ++it)
    {
	(*it)->status(true);
    }
    
    std::cout << "Kulki poza planszą: \n";
    for(auto it = zastopowane.begin(); it != zastopowane.end(); ++it)
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

// Tsilkow

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <limits>
#include <memory>
#include <math.h>
#include <unistd.h>

#include "kulka.hpp"
#include "odbijacz.hpp"
#include "plansza.hpp"


using namespace std;

bool wczytajZPliku(std::shared_ptr<Plansza>& plansza, std::string nazwa, int czasDoWybuchu)
{
    fstream plik(nazwa, std::fstream::in);

    if(plik.is_open())
    {
	int tur;
	int szerokosc;
	int wysokosc;

	plik >> tur >> szerokosc >> wysokosc;
	// przejście do następnej linii
	plik.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	plansza = std::make_shared<Plansza>(tur, szerokosc, wysokosc, czasDoWybuchu);

	for(int y = 0; y < wysokosc+2; ++y)
	{
	    std::string linia;
	    if(!getline(plik, linia))
	    {
		std::cout << "!BŁĄD! Za mało linii opisu sytuacji wejściowej w pliku!\n";
		return false;
	    }
	    else if(((int)linia.size()) != szerokosc+2)
	    {
		std::cout << "!BŁĄD! Linia " << y+2 << " w pliku opisu sytaucji wejściowej ma niepoprawną długość!\n";
		return false;
	    }

	    for(int x = 0; x < szerokosc+2; ++x)
	    {
		if(linia.substr(x, 1) != " ")
		{
		    if(x == 0 || x == szerokosc+1 || y == 0 || y == wysokosc+1)
		    {
			if(!plansza->dodajKulke(std::make_pair(x-1, y-1), linia[x]))
			{
			    std::cout << "!BŁĄD! W pozycji (" << x << ", " << y << ") podano niewłaściwy symbol kulki!\n";
			    return false;
			}
		    }
		    else
		    {
			if(!plansza->dodajOdbijacz(std::make_pair(x-1, y-1), linia[x]))
			{
			    std::cout << "!BŁĄD! W pozycji (" << x << ", " << y << ") podano niewłaściwy symbol odbijacza!\n";
			    return false;
			}
		    }
		}
	    }
	}
	
	plik.close();
	return true;
    }
    else
    {
	std::cout << "!BŁĄD! Nie można otworzyć pliku wejściowego!\n";
	plik.close();
	return false;
    }
}

int main()
{
    srand(time(NULL));

    const int czasDoWybuchu = 7;
    
    std::shared_ptr<Plansza> plansza;

    if(wczytajZPliku(plansza, "wejscie", czasDoWybuchu))
    {
	//plansza->status();
	while(plansza->zrobTure())
	{
	    ;//plansza->status();
	}
	plansza->status();
    }
    
    return 0;
}

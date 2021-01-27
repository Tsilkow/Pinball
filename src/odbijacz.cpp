#include "odbijacz.hpp"


void Odbijacz::status(bool enter)
{
    std::cout << "{ " << typeid(*this).name() << ", (" << pozycja.first << ", " << pozycja.second << ") }";
    if(enter) std::cout << "\n";
}

void Ukosny::odbij(const std::shared_ptr<Kulka>& kulka)
{
    if(kulka->getTyp() == TypKulki::taran) zniszczony = true;
    else
    {
	if(kulka->getKierunek() % 2 == 1) kulka->setKierunek((kulka->getKierunek()+4) % 8);
	else
	{
	    switch(skos)
	    {
		case 0: // 0 = \,
		    switch(kulka->getKierunek())
		    {
			case 0: kulka->setKierunek(2); break;
			case 2: kulka->setKierunek(0); break;
			case 4: kulka->setKierunek(6); break;
			case 6: kulka->setKierunek(4); break;
		    }
		    break;
		
		case 1: // 1 = /,
		    switch(kulka->getKierunek())
		    {
			case 0: kulka->setKierunek(6); break;
			case 2: kulka->setKierunek(4); break;
			case 4: kulka->setKierunek(2); break;
			case 6: kulka->setKierunek(0); break;
		    }
		    break;
	    }
	}
    }
}

void Losowy::odbij(const std::shared_ptr<Kulka>& kulka)
{
    if(kulka->getTyp() == TypKulki::taran) zniszczony = true;   
    else kulka->setKierunek(rand() % 8);
}

void Zjadajacy::odbij(const std::shared_ptr<Kulka>& kulka)
{
    if(kulka->getTyp() == TypKulki::taran) zniszczony = true;
    else kulka->zniszcz();
}

void Predkosciowy::odbij(const std::shared_ptr<Kulka>& kulka)
{
    if(kulka->getTyp() == TypKulki::taran) zniszczony = true;
    else
    {
	if(przyspieszajacy) kulka->setOdwPredkosci(std::max(1, kulka->getOdwPredkosci()/2));
	else kulka->setOdwPredkosci(kulka->getOdwPredkosci()*2);
    }
}

void Mglowy::odbij(const std::shared_ptr<Kulka>& kulka)
{
    if(kulka->getTyp() == TypKulki::taran) zniszczony = true;
}

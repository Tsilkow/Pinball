#include "odbijacz.hpp"


void Odbijacz::status(bool enter)
{
    std::cout << "{ " << typeid(*this).name() << ", (" << pozycja.first << ", " << pozycja.second << ") }";
    if(enter) std::cout << "\n";
}

std::pair<bool, bool> Ukosny::odbij(std::shared_ptr<Kulka>& kulka)
{
    if(typeid(kulka.get()).name() == "Taran") return std::make_pair(false, true);

    if(kulka->getKierunek() % 2 == 1) kulka->setKierunek((kulka->getKierunek()+4) % 8);
    else
    {
	switch(skos)
	{
	    case 0:
		switch(kulka->getKierunek())
		{
		    case 0: kulka->setKierunek(2); break;
		    case 2: kulka->setKierunek(0); break;
		    case 4: kulka->setKierunek(6); break;
		    case 6: kulka->setKierunek(4); break;
		}
		break;
		
	    case 1:
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

    return std::make_pair(true, true);
}

std::pair<bool, bool> Losowy::odbij(std::shared_ptr<Kulka>& kulka)
{
    if(typeid(kulka.get()).name() == "Taran") return std::make_pair(false, true);
    
    kulka->setKierunek(rand() % 8);

    return std::make_pair(true, true);
}

std::pair<bool, bool> Zjadajacy::odbij(std::shared_ptr<Kulka>& kulka)
{
    if(typeid(kulka.get()).name() == "Taran") return std::make_pair(false, false);
    return std::make_pair(true, false);
}

std::pair<bool, bool> Predkosciowy::odbij(std::shared_ptr<Kulka>& kulka)
{
    if(typeid(kulka.get()).name() == "Taran") return std::make_pair(false, true);

    if(przyspieszajacy) kulka->setOdwPredkosci(std::min(1, kulka->getOdwPredkosci()/2));
    else kulka->setOdwPredkosci(kulka->getOdwPredkosci()*2);

    return std::make_pair(true, true);
}

std::pair<bool, bool> Mglowy::odbij(std::shared_ptr<Kulka>& kulka)
{
    if(typeid(kulka.get()).name() == "Taran") return std::make_pair(false, true);

    return std::make_pair(true, true);
}

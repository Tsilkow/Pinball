// Tsilkow

#include <iostream>
#include <vector>
#include <time.h>
#include <memory>
#include <math.h>

#include "kulka.hpp"
#include "odbijacz.hpp"


using namespace std;

int main()
{
    srand(time(NULL));
    
    vector<shared_ptr<Kulka>> kulki;

    vector<shared_ptr<Odbijacz>> odbijacze;

    kulki.emplace_back(make_shared<Zwykla>(make_pair(1, 0), 10, 10));
    kulki.emplace_back(make_shared<Taran>(make_pair(0, 1), 10, 10));
    kulki.emplace_back(make_shared<Wybuchowa>(make_pair(10, 10), 10, 10, 20));

    odbijacze.emplace_back(make_shared<Ukosny>(make_pair(5, 5), 0));
    odbijacze.emplace_back(make_shared<Ukosny>(make_pair(6, 5), 1));
    odbijacze.emplace_back(make_shared<Losowy>(make_pair(4, 5)));
    odbijacze.emplace_back(make_shared<Zjadajacy>(make_pair(3, 5)));
    odbijacze.emplace_back(make_shared<Predkosciowy>(make_pair(3, 4), false));
    odbijacze.emplace_back(make_shared<Predkosciowy>(make_pair(4, 4), true));
    odbijacze.emplace_back(make_shared<Mglowy>(make_pair(5, 4)));
    
    return 0;
}

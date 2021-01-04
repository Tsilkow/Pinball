// Tsilkow

#include <iostream>
#include <vector>
#include <time.h>
#include <memory>
#include <math.h>

#include "kulka.hpp"


using namespace std;

int main()
{
    vector<shared_ptr<Kulka>> kulki;

    kulki.emplace_back(make_shared<Zwykla>(make_pair(1, 0), 10, 10));
    kulki.emplace_back(make_shared<Taran>(make_pair(0, 1), 10, 10));
    kulki.emplace_back(make_shared<Wybuchowa>(make_pair(10, 10), 10, 10, 20));
    
    return 0;
}

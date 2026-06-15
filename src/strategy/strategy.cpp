#include <iostream>
#include "strategy.h"

using std::cout, std::endl;

void Strategy::strategy()
{
    cout << "This is the default strategy" << endl;

    grid_map.map_Info();
}
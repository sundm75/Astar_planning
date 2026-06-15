#include <iostream>
#include "main.h"
#include "strategy.h"
#include "graphics.h"

using std::cout, std::endl;

int main()
{
    cout << "main starting" << endl;

    Strategy strategy;
    strategy.strategy();

    initgraph(1000, 1000);
    setbkcolor(WHITE);
    cleardevice();

    std::cout<<"draw circles: "<<std:: endl;
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 4);
    circle(500, 500, 400);
    circle(500, 500, 300);

    system("pause   ");
    
    return 0;

}
#include <iostream>
#include "main.h"


using std::cout, std::endl;
using namespace NAVIGATION;

namespace NAVIGATION
{
    Navigation::Navigation()
    {
        Node start_node(6, 5, NodeType::start);//起点
        Node end_node(28, 40, NodeType::end);//终点
        grid_map_ptr = make_unique<GridMap>(start_node, end_node);//创建地图   

        system("pause");
    }

    bool Navigation::process(const int &h_type_, const int &algo_type_)
    {
        strategy_ptr = make_unique<Astar>(h_type_, algo_type_);//创建规划方法， 父类指针指向子类对象
        return strategy_ptr->search(grid_map_ptr, result_nodes);
    }

}//end of namespace NAVIGATION

int main()
{
    initgraph(WIDTH,HEIGHT, EW_SHOWCONSOLE);

    unique_ptr<NAVIGATION::Navigation> navigation_ptr = make_unique<NAVIGATION::Navigation>();//创建导航任务

    if(navigation_ptr->process(NAVIGATION::HType::Manhattan, NAVIGATION::AlgoType::BFS)) //AStar Dijkstra  BFS
    {
        cout << "导航完成!" << endl; 
    }

    system("pause");
    closegraph();
    return 0;
}
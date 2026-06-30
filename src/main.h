#pragma

#include "strategy.h"
#include "grid_map.h"
#include "config.h"


namespace NAVIGATION
{
    class Navigation //导航器
    {
    public:
        Navigation();
        bool process(const int & h_type_, const int& algo_type_);
    public:
        vector<Node*> result_nodes;//结果路径
        unique_ptr<GridMapBase> grid_map_ptr;//地图父类指针
        unique_ptr<StrategyBase> strategy_ptr;//全局规划方法指针
    };
    
}//end of namespace NAVIGATION

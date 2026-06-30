#pragma once
#include <queue>
#include <cmath>
#include "grid_map.h"

using std::priority_queue, std::pair;

namespace NAVIGATION
{
    enum HType //H距离类型
    {
        Euclidean, //欧氏距离
        Manhattan, //曼哈顿距离
        Chebyshev  //切比雪夫距离
    };

    enum AlgoType //算法类型
    {
        AStar, //A*算法
        Dijkstra, //Dijkstra算法
        BFS //最佳优先搜索
    };

    class StrategyBase//策略父类
    {
        public:
            virtual bool search(const unique_ptr<GridMapBase>& map, vector<Node*> & result_nodes) = 0;//搜索过程 纯虚函数
    };

    class Astar : public StrategyBase //Astar策略
    {
        public:
        Astar(const int& h_type_, const int& algo_type_);
		bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) override;//输入map，输出result_nodes_output 
		int heuristicDis(const Node& node1, const Node& node2);//启发代价
		void calCost(const Node& current_node, Node& next_node, const Node& end_node);//计算代价
		void printResult(const vector<Node*>& result_nodes);//打印结果
		void drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time);//单步绘制节点
		void drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes);//绘制结果


        public:
            priority_queue<Node> open_queue; //open表，小顶堆， 能自动把最小值作为堆顶，省去查找最小f值的过程 //因为要排序 所以不存指针
            unordered_set<Node*> open_set; //open表具备 快速查找 功能， 用 哈希表 实现,和open_queue保持同步
            unordered_set<Node*> close_set; //close表， 也就是探索过的节点，用哈希表实现

            int h_type = HType::Manhattan; //默认为曼哈顿距离
            int algo_type = AlgoType::AStar; //默认为A*算法
            int final_length = 0; //最终路径长度
            int step_len = 0; //单步步长

    };

} // namespace NAVIGATION


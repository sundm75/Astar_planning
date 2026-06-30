#pragma once
#include <iostream>
#include "graphics.h"
#include <vector>
#include <ctime>
#include <assert.h>
#include <unordered_set>
#include <memory>
#include "config.h"


//using namespace std;
using std::cout, std::endl; //项目->属性里设置成C++17以上
using std::vector, std::unordered_set, std::unique_ptr, std::make_unique;

namespace NAVIGATION
{
    enum NodeType
    {
        normal, 
        start,
        end,
        obs,
        result_way,
    };

    class Node
    {
    public:
        Node() = default;
        Node(const int& r , const int& c, const int& type = NodeType::normal);//有参构造
        void drawNode() const;

        bool operator<(const Node& other_node) const {return this->f > other_node.f;}//重载< ,用于创建小顶堆

    public:
        int row = 0;
        int col = 0;

        int f = 0;
        int g = 0;
        int h = 0;

        int node_type = NodeType::normal;   
        Node* parent = nullptr;    
    };

    class GridMapBase //栅格地图基类
    {
        public:
        bool GridMapInit(const Node& start, const Node& end); //初始化地图 传入参数是只读
        void printMap() const; //打印地图 只读 不会修改类里的成员变量
        void drawMap() const; //绘制地图
        bool outOfMap(const Node& node) const; //判断是否越界
        virtual void addObs() = 0; //添加障碍物 纯虚函数 子类实现
    public:
        vector<vector<Node>> grid_map; //二维数组，存储栅格地图
        Node* start_node = nullptr; //起始点
        Node* end_node = nullptr; //终点
        unordered_set<Node*> obs_nodes; //障碍物 指向哈希表指针  
    };

    class GridMap : public GridMapBase//栅格地图子类，可以添加障碍物
    {
    public:
        GridMap(const Node& start, const Node& end); //构造函数 地图初始化
        void addObs() override; //添加障碍物 纯虚函数 子类实现
    };
}//end of namespace NAVIGATION


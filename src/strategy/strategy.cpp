#include "strategy.h"
#include <algorithm>

namespace NAVIGATION
{
    void delay (const int &time)//延时函数 单位ms
    {
        clock_t start = clock();
        while (clock() - start < time);
        {
        
        }
    }

    Astar::Astar(const int &h_type_, const int &algo_type_): h_type(h_type_), algo_type(algo_type_)
    {
       


    }

    bool Astar::search(const unique_ptr<GridMapBase> &map, vector<Node *> &result_nodes)
    {
         //初始化起点
        open_queue.emplace(*map->start_node);//起点放入open表
        open_set.insert(map->start_node);//起点放入open表中
        Node* current_node = map->start_node ;//把起点设置为当前点

        //设置单步移动方向 用容器存储8个方向 存储键值对
        vector<pair<int, int>> move_step = 
        {
            pair<int, int>(0, 1),            
            pair<int, int>(0, -1),
            pair<int, int>(1, 0),
            pair<int, int>(-1, 0),
            pair<int, int>(-1, 1),
            pair<int, int>(-1, -1),
            pair<int, int>(1, -1),
            pair<int, int>(1, 1)
        };

        //搜索过程
        while(!open_queue.empty())
        {
            //当前点处理
            int r = open_queue.top().row;//行数
            int c = open_queue.top().col;//列数
            current_node = &map->grid_map[r][c];//当前节点移动到f最小的下个节点
            cout<<"current_node->f = "<<current_node->f<<",current_node->r = "<< r <<",current_node->c = "<< c <<endl;

            //绘制close点
            setfillcolor(YELLOW);
            drawNodeStep(map->start_node, map->end_node, current_node,DELAYTIME_SEARCH);
            
            open_queue.pop();//当前节点出队
            open_set.erase(current_node);//当前节点出open表
            close_set.insert(current_node);//当前节点入close表

            //判断是否到达终点
            if(current_node == map->end_node)//如果已经到终点
            {
                final_length = current_node->g;//   记录路径长度    

                //回溯路径 沿指针逆序存入rusult_nodes
                while(current_node->parent)
                {
                    current_node->node_type = NodeType::result_way;//更新类型
                    result_nodes.emplace_back(current_node);//存入结果 给后面模块用的
                    current_node = current_node->parent;//回溯 父结点移动
                }
                reverse(result_nodes.begin(), result_nodes.end());//逆序 因为上面是逆序存入的
                cout<<"Astar search success! "<<endl;
                
                //恢复起点终点类型
                map->start_node->node_type = NodeType::start;
                map->end_node->node_type = NodeType::end;

                //结果展示 
                printResult(result_nodes);
                map->printMap();
                drawResult(map->start_node, map->end_node, result_nodes);                
                return true;
            }
            //一般搜索
            for(auto it = move_step.begin(); it != move_step.end(); it++)
            {
                Node node_tmp(r + it->first, c + it->second );//获取下个节点位置
                if(map->outOfMap(node_tmp))//如果超出越界 ,则跳过
                {
                    continue;                
                }
                Node* next_node = &map->grid_map[node_tmp.row][node_tmp.col];//如果没有出界 ，则创建下个节点指针
                if(close_set.find(next_node) != close_set.end()
                || map->obs_nodes.find(next_node) != map->obs_nodes.end())//走过或者是障碍物，则跳过
                {
                    continue;
                }    
                //可以走的节点
                step_len = abs(it->first) == abs(it->second)?XLEN : LEN;//单步步长， 如果是走斜线就是XLEN，否则是LEN
                if(open_set.find(next_node) != open_set.end())//如果已经在open_set中，则判断是否需要更新
                {
                    if(current_node->g + step_len < next_node->g)//如果累加g值小于现有的g值，则更新
                    {
                        calCost(*current_node, *next_node,*map->end_node);//计算g,h,f值
                        next_node->parent = current_node;//更新父节点
                    }
                }
                else//如果不在open_set中，则直接加入
                {
                    calCost(*current_node, *next_node,*map->end_node);//计算g,h,f值
                    next_node->parent = current_node;//更新父节点  
                    
                    open_queue.emplace(*next_node);//加入open_set
                    open_set.insert(next_node);//加入open_set

                    //绘制open点
                    setfillcolor(LIGHTCYAN);
                    drawNodeStep(map->start_node, map->end_node, current_node,DELAYTIME_SEARCH);                    
                }
            }

        }

        //搜索失败的处理
        cout<<"Astar search failed!"<<endl;
        drawResult(map->start_node, map->end_node, result_nodes);
        return false;
    }

    int Astar::heuristicDis(const Node &node1, const Node &node2) //启发代价
    {
        if(h_type == HType::Euclidean)
        {
            return hypot(node1.col - node2.col, node1.row - node2.row)*LEN;
        }
        else if(h_type == HType::Manhattan)
        {
            return abs(node1.col - node2.col)*LEN + abs(node1.row - node2.row)*LEN;
        }
        else if(h_type == HType::Chebyshev)
        {
 			int len_col = abs(node1.col - node2.col);
			int len_row = abs(node1.row - node2.row);
			int x_step = std::min(len_col, len_row);
			int res_step = abs(len_col - len_row);
			return x_step * XLEN + res_step * LEN;           
        }

        return 0;
    }

    void Astar::calCost(const Node &current_node, Node &next_node, const Node &end_node)
    {
        next_node.g = current_node.g + step_len;//更新g值
        next_node.h = heuristicDis(next_node, end_node);//更新h值

        if(algo_type == AlgoType::Dijkstra)
        {
             next_node.h = 0;
        }
        else if(algo_type == AlgoType::BFS)
        {
            next_node.g = 0;
        }
        next_node.f = next_node.g + next_node.h;//计算f值
        cout<<"f="<<next_node.f<<" g="<<next_node.g<<" h="<<next_node.h<<endl;
    }

    void Astar::printResult(const vector<Node *> &result_nodes)//打印结果
    {
        cout<<"路径点数: "<<result_nodes.size()<<endl;
        cout<<"探索点数: "<<close_set.size()<<endl;
        cout<<"路径长度:  "<<final_length<<endl;
        for(const auto&result_nodes:result_nodes)
        {
            cout<<"("<<result_nodes->row<<", "<<result_nodes->col<<"),"<<endl
            <<" f: "<<result_nodes->f<<", "
            <<" g: "<<result_nodes->g<<", "
            <<" h: "<<result_nodes->h<<endl;
        }
    }

    void Astar::drawNodeStep(Node *const start, Node *const end, Node *const node, const int &time)
    {
        if(node != start && node != end)//不绘制起点和终点
        {
        	BeginBatchDraw();
			node->drawNode();
			delay(time);
			EndBatchDraw();
        }
    }

    void Astar::drawResult(Node *const start, Node *const end, const vector<Node *> &result_nodes)
    {
        setfillcolor(GREEN);//设置填充颜色为绿色
        for(const auto&result_nodes:result_nodes)
        {
            drawNodeStep(start, end, result_nodes, DELAYTIME_RESULT);
        }
    }

} // end of namespace NAVIGATION

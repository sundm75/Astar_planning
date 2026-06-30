#include "grid_map.h"
#include <iostream>
#include <assert.h>

using std::cout, std::endl;
namespace NAVIGATION
{
    Node::Node(const int &r, const int &c, const int &type)
    : row(r), col(c), node_type(type)//有参构造，传入行、列、类型
    {
    }

    void Node::drawNode() const
    {
        int left = ORIX + col * LEN;
        int right = left + LEN;
        int top = ORIY + row * LEN;
        int bottom = top + LEN;
        fillrectangle(left, top, right, bottom);//绘制矩形 左 上 右 下
    }

    bool GridMapBase::GridMapInit(const Node &start, const Node &end)
    {
        if(outOfMap(start) || outOfMap(end))
        {
            cout << "start or end out of map" << endl;
            return false;
        }

        // 构建 地图
        for(int i = 0; i < ROWS; i++)
        {
            vector<Node> row_tmp;
            for(int j = 0; j < COLS; j++)
            {
                Node node_tmp(i, j);
                row_tmp.emplace_back(node_tmp);
            }
            grid_map.emplace_back(row_tmp);
        }
        //更新起点终点
        grid_map[start.row][start.col].node_type = NodeType::start;//更新地图中起点终点的类型
        grid_map[end.row][end.col].node_type = NodeType::end; 
        start_node = &grid_map[start.row][start.col];
        end_node = &grid_map[end.row][end.col];        
        return true;
    }

    void GridMapBase::printMap() const
    {
        cout<<"grid_map rows: "<<ROWS<<" map cols: "<<COLS<<endl;
        cout<<"start rows:"<<start_node->row<<" cols:"<<start_node->col<<endl
        <<"end rows:"<<end_node->row<<" cols:"<<end_node->col<<endl;
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                if(grid_map[i][j].node_type == NodeType::normal)
                {
                    cout<<" ";
                }
                else 
                {
                    cout<<grid_map[i][j].node_type<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void GridMapBase::drawMap() const
    {
        initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);

        setbkcolor(WHITE);
        setlinecolor(BLACK);
        setlinestyle(PS_SOLID, 2);
        cleardevice();

        BeginBatchDraw();
        setfillcolor(WHITE);
        for(int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                grid_map[i][j].drawNode();
            }
            
        }
        //起点和终点
        setfillcolor(RED);
        start_node->drawNode();

        setfillcolor(BLUE);
        end_node->drawNode();

        setfillcolor(BROWN);
        for(const auto &obs_node : obs_nodes)
        {
            obs_node->drawNode();
        }

        EndBatchDraw();
    }

    bool GridMapBase::outOfMap(const Node &node) const
    {
        return (node.row < 0 || node.row >= ROWS || node.col < 0 || node.col >= COLS);
    }

    GridMap::GridMap(const Node &start, const Node &end)
    {
        assert(GridMapInit(start, end));
        addObs();
        printMap();
        drawMap();
        
    }

    void GridMap::addObs()
    {
        Node* node_tmp;
        for (int i = 10; i < 35; i++)
        {
            node_tmp = &grid_map[10][i];
            obs_nodes.insert(node_tmp);
            node_tmp->node_type = NodeType::obs;
        }
 
        for (int i = 10; i < 35; i++)
        {
            node_tmp = &grid_map[10][i];
            obs_nodes.insert(node_tmp);
            node_tmp->node_type = NodeType::obs;
        }

        for (int i = 10; i < 35; i++)
        {
            node_tmp = &grid_map[i][35];
            obs_nodes.insert(node_tmp);
            node_tmp->node_type = NodeType::obs;
        }

        for (int i = 10; i < 35; i++)
        {
            node_tmp = &grid_map[34][i];
            obs_nodes.insert(node_tmp);
            node_tmp->node_type = NodeType::obs;
        }
    }

} // end namespace NAVIGATION
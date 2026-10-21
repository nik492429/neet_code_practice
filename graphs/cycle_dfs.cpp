#include <iostream>
#include <vector>
using namespace std;

using Adjacency = vector<vector<int>>;

enum Status
{
    UNVISITED = 0,
    VISITING = 1,
    VISITED = 2
};

void dfs(int node, int parent, Adjacency &adj_list, vector<Status> & node_status)
{
    if(node_status[node] == UNVISITED)
    {
        node_status[node] = VISITING; 
        for(auto temp : adj_list[node])
        {
            if(temp != parent)
            {
                dfs(temp, node, adj_list, node_status);
            }
        }
        node_status[node] = VISITED;
    }
    else if(node_status[node] == VISITING)
    {
        std::cout << "Cycle detected" << std::endl;
    }
}

int main()
{
    // Test graph:
    //
    //     0 ----- 1
    //     |       |
    //     3 ----- 2 ----- 4
    //
    // This contains the cycle 0-1-2-3-0.
    const int n = 5;
    Adjacency adj_list = {
        {1},
        {0, 2},
        {1, 3, 4},
        {2},
        {2}
    };

    vector<Status> node_status(n, UNVISITED);
    for(int i = 0; i < n; i++)
    {
        if(node_status[i] == UNVISITED)
        {
            dfs(i, -1, adj_list, node_status);
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <array>
using namespace std;

enum NodeState 
{
    UNVISITED,
    VISITING,
    VISITED
};

class Node 
{
public:
    Node(int course)
    {
        Course = course;
        State = UNVISITED;      
    };
    int Course;
    NodeState State;
    std::vector<Node*> Prerequisites;
};

using AdjList = std::vector<std::unique_ptr<Node>>;


std::vector<int> CourseOrder;

bool DFS(Node *node)
{
    std::cout << "Visiting node: " << node->Course << std::endl;
    if(node->State == VISITED)
    {
        return true;
    }
    else if(node->State == VISITING)
    {
        return false;
    }
    else
    {
        node->State = VISITING;
        for(auto & adjNode : node->Prerequisites)
        {
            if(!DFS(adjNode))
            {
                return false;
            }
        }
        node->State = VISITED;
        CourseOrder.push_back(node->Course);
        return true;
    }
}


void TraverseAdjList(AdjList &adjList)
{
    for(auto &node : adjList)
    {
        std::cout << "*********** Traversing node: " << node->Course << std::endl;
        if(!DFS(node.get()))
        {
            std::cout << "Cycle detected in the graph. Cannot complete all courses." << std::endl;
            return;
        }
    }
    std::cout << "No cycles detected. All courses can be completed." << std::endl;
}


void BuildAdjacencyList(AdjList &adjList, int numCourses, std::vector<std::array<int, 2>> &prerequisitesList)
{
    for(int i =0; i<numCourses; i++)
    {
        adjList.push_back(std::make_unique<Node>(i));
    }
    for(auto preq : prerequisitesList)
    {
        auto &node = adjList[preq[0]];
        node->Prerequisites.push_back(adjList.at(preq[1]).get());
    }
}

void printAdjacencyList(const AdjList &adjList)
{
    for(auto &node : adjList)
    {
        std::cout << "Course: " << node->Course << " Prerequisites: ";
        for(auto preq : node->Prerequisites)
        {
            std::cout << preq->Course << " ";
        }
        std::cout << std::endl;
    }
}

void PrintCourseOrder()
{
    std::cout << "Course order to complete all courses: ";
    for(auto course : CourseOrder)
    {
        std::cout << course << " ";
    }
    std::cout << std::endl;
}

int main()
{
    AdjList adjList;
    int numCourses = 12;
    std::vector<std::array<int, 2>> prerequisitesList = {
        {1, 0},
        {2, 0}, {2, 1},
        {3, 1},
        {4, 1}, {4, 2},
        {5, 2}, {5, 3},
        {6, 3}, {6, 4},
        {7, 4}, {7, 5},
        {8, 5}, {8, 6},
        {9, 6}, {9, 7},
        {10, 7}, {10, 8},
        {11, 8}, {11, 9}, {11, 10}
    };
    BuildAdjacencyList(adjList, numCourses, prerequisitesList);
    printAdjacencyList(adjList);
    TraverseAdjList(adjList);
    PrintCourseOrder();
    return 0;
}


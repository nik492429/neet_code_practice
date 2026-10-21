#include <iostream>
#include <vector>

struct Node
{
    int val;
    int position;
};


class MaxHeap
{
public:
    void AddElement(int val, int position);
    void RemoveRoot();
    bool IsMaxWithinWindow(int left, int right);
    int GetMax();

private:
    std::vector<struct Node*> Heap;
};

void MaxHeap::AddElement(int val, int position)
{
    struct Node* node = new Node();
    node->val = val;
    node->position = position;
    Heap.push_back(node);
    int index = Heap.size()-1;
    while(index > 0)
    {
        int parent = (index-1)/2;
        if(Heap[parent]->val < Heap[index]->val)
        {
            std::swap(Heap[parent], Heap[index]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void MaxHeap::RemoveRoot()
{
    if(Heap.size() == 0)
    {
        return;
    }
    else if(Heap.size() == 1)
    {
        Heap.pop_back();
        return;
    }
    else
    {
        std::swap(Heap[0], Heap[Heap.size()-1]);
        Heap.pop_back();
        int index = 0;
        while(index < Heap.size())
        {
            int left = 2*index + 1;
            int right = 2*index + 2;
            int largest = index;

            if(left < Heap.size() && Heap[left]->val > Heap[largest]->val)
            {
                largest = left;
            }
            if(right < Heap.size() && Heap[right]->val > Heap[largest]->val)
            {
                largest = right;
            }
            if(largest != index)
            {
                std::swap(Heap[index], Heap[largest]);
                index = largest;
            }
            else
            {
                break;
            }
        }
    }
}

bool MaxHeap::IsMaxWithinWindow(int left, int right)
{
    if(Heap.size() == 0)
    {
        return false;
    }
    int maxPos = Heap[0]->position;
    return maxPos >= left && maxPos <= right;
}

int MaxHeap::GetMax()
{
    if(Heap.size() == 0)
    {
        return -1; // or throw an exception
    }
    return Heap[0]->val;
}


int main()
{
    MaxHeap maxHeap;
    std::vector<int> v = {1,2,1,0,4,2,6};
    int window_len = 3;
    std::vector<int> max_at_each_pos;
    int index = 0;
    for(int i=0; i<window_len-1; i++)
    {
        maxHeap.AddElement(v.at(i), i);
    }
    int start_index = 0;
    for(int i=window_len-1; i<v.size(); i++)
    {
        maxHeap.AddElement(v.at(i), i);
        while(!maxHeap.IsMaxWithinWindow(start_index, i))
        {
            maxHeap.RemoveRoot();
        }
        max_at_each_pos.push_back(maxHeap.GetMax());
        
    }

    for(auto e : max_at_each_pos)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    return 0; 
}



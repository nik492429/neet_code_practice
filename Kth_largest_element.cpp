#include <iostream>
#include <vector>
#include <array>

#define K 5

void swap(int *arr, int pos1, int pos2)
{
    auto temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
}

void heapify_up(int *arr, int index)
{
    while(index > 0)
    {
        int parent = (index-1)/2;
        if(arr[parent] > arr[index])
        {        
            swap(arr, parent, index);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void heapify_down(int *arr, int index, int size)
{
    while(index < size)
    {
        int left = 2*index + 1;
        int right = 2*index + 2;
        int smallest = index;

        if(left < size && arr[left] < arr[smallest])
        {
            smallest = left;
        }
        if(right < size && arr[right] < arr[smallest])
        {
            smallest = right;
        }
        if(smallest != index)
        {
            swap(arr, index, smallest);
            index = smallest;
        }
        else
        {
            break;
        }
    }
}

void print_heap(std::vector<int> &v)
{
    for(auto &elem : v)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> input_arr = {
        3, 2, 1, 5, 6, 4, 8, 7, 9, 10
    };
    std::array<int, K> heap;
    int index = 0;
    for (auto elem : input_arr)
    {
        if(index < K)
        {
            heap[index] = elem;
            heapify_up(heap.data(), index);
            index++;
        }
        else
        {
            if(elem < heap[0])
            {
                continue;
            }
            else if(elem > heap[0])
            {
                heap[0] = elem;
                heapify_down(heap.data(), 0, K);
            }
        }
    }
    std::cout << "Kth largest element is: " << heap[0] << std::endl;
}


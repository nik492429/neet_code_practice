#include <iostream>
#include <vector>


int binary_search(int *arr, int first, int last)
{
    if(first >= last)
    {
        return first;
    }
    else
    {
        int mid = (first + last)/2;
        if(arr[mid] < arr[last])
        {
            return binary_search(arr, first, mid);
        }
        else
        {
            return binary_search(arr, mid+1, last);
        }
    }
}

int main()
{
    std::vector<int> arr = {4,5,6,7,1,2,3};
    int result = binary_search(arr.data(), 0, arr.size()-1);
    std::cout << "Minimum element: " << arr[result] << std::endl;
}

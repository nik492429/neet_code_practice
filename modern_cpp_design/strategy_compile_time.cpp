#include <iostream>
#include <concepts>
#include <vector>
using namespace std;

template <template<typename> class SortingType, typename ElementType>
concept SortingStrategy = requires(SortingType<ElementType> t, vector<ElementType> &v) 
{
    t.sort(v);
};

template<typename T>
class MergeSort
{
    public:
    using value_type = T;
    void sort(vector<T> &v) 
    {
        std::cout << "Merge sort" << std::endl;
    }
};

template<typename T>
class QuickSort
{
    public:
    using value_type = T;
    void sort(vector<T> &v) 
    {
        cout << "QuickSort" << endl;
    }
};


template <template<typename> class SortingType, typename T>
requires(SortingStrategy<SortingType, T>)
class Database 
{
    public:
    SortingType<T> type;
    void custom_sort(vector<T> &v) 
    {
        type.sort(v);
    }
};

int main() 
{
    vector<int> v = {1, 2, 3, 4, 5};
    Database<MergeSort, int> dbMerge;
    Database<QuickSort, int> dbQuick;
    dbMerge.custom_sort(v);
    dbQuick.custom_sort(v);
}






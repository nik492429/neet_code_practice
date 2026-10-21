#include <iostream>
#include <unordered_map>

struct Node
{
    int key;
    int val;
    struct Node *prev;
    struct Node *next;
    Node(int k, int v) 
    : key(k)
    , val(v)
    , prev(nullptr), next(nullptr) 
    {}
};

using Node_T = struct Node;

class LRUCache
{
public:    
    LRUCache(int capacity);
    int Get(int key);
    void Put(int key, int val);

private:
    void AddToCache(Node_T *node);
    void UpdateCache(Node_T *node);
    const int Capacity;
    int Size;
    std::unordered_map<int, Node_T*> Hash_Map;
    Node_T *Head;
    Node_T *Tail;
};

LRUCache::LRUCache(int capacity)
    : Capacity(capacity)
    , Size(0)
    , Head(nullptr)
    , Tail(nullptr)
{
}

void LRUCache::AddToCache(Node_T *node)
{
    Size++;
    Hash_Map[node->key] = node;
    if(Head == nullptr)
    {
        Head = node;
        Tail = node;
    }
    else if(Head == Tail)
    {
        Head->next = node;
        node->prev = Head;
        Tail = node;
    }
    else
    {
        Tail->next = node;
        node->prev = Tail;
        Tail = node;
    }

    if(Size > Capacity)
    {
        Node_T *leastUsed = Head;
        Head = leastUsed->next;
        Head->prev = nullptr;
        std::cout << "Removed key = " << leastUsed->key << std::endl;
        Hash_Map.erase(leastUsed->key);
        Size--;
        delete leastUsed;
    }
}

void LRUCache::UpdateCache(Node_T *node)
{
    if(node == Tail)
    {
        return;
    }
    else if(node == Head)
    {
        Head = node->next;
        Head->prev = nullptr;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    Tail->next = node;
    node->prev = Tail;
    node->next = nullptr;
    Tail = node;
}


int LRUCache::Get(int key)
{
    if(Hash_Map.find(key) != Hash_Map.end())
    {
        Node_T* node = Hash_Map.at(key);
        UpdateCache(node);
        return node->val;
    }
    else
    {
        return -1;
    }
}

void LRUCache::Put(int key, int val)
{
    if(Hash_Map.find(key) != Hash_Map.end())
    {
        Node_T* node = Hash_Map.at(key);
        node->val = val;
        UpdateCache(node);
    }
    else
    {
        Node_T* node = new Node_T(key, val);
        AddToCache(node);
    }
}

int main()
{
    LRUCache cache(3);
    cache.Put(1, 10);
    cache.Put(2, 20);
    cache.Put(3, 30);
    std::cout << "Get key 2: " << cache.Get(2) << std::endl;
    cache.Put(4, 40);
    cache.Put(1, 60);
    std::cout << "Get key 1: " << cache.Get(1) << std::endl;
    std::cout << "Get key 3: " << cache.Get(3) << std::endl;
    std::cout << "Get key 4: " << cache.Get(4) << std::endl;
}
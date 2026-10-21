#include <iostream>
#include <vector>

static const int K = 5;
static int cnt = 0;

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int v)
        : val(v)
        , left(nullptr), right(nullptr)
    {}
};


class BinarySearchTree
{
public:
    BinarySearchTree() = default;    
    void Insert(int val);
    void TraverseTree();

private:
    void InOrderTraversal(Node* node); 
    Node *Root = nullptr;
};

void BinarySearchTree::Insert(int val)
{
    Node *node = new Node(val);
    if(Root == nullptr)
    {
        std::cout << "Inserting root: " << val << std::endl;
        Root = node;
    }
    else
    {
        Node *currentNode = Root;
        Node *prev_node = nullptr;
        while(currentNode != nullptr)
        {
            prev_node = currentNode;
            if(currentNode->val > node->val)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode = currentNode->right;
            }
        }
        if(prev_node->val > node->val)
        {
            prev_node->left = node;
        }
        else
        {
            prev_node->right = node;
        }
    }
}

void BinarySearchTree::TraverseTree()
{
    InOrderTraversal(Root);
    std::cout << std::endl;
}

void BinarySearchTree::InOrderTraversal(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    InOrderTraversal(node->left);
    cnt++;
    if(cnt == K)
    {
        std::cout << "Kth smallest element: " << node->val << std::endl;
    }
    InOrderTraversal(node->right);
}

int main()
{
    BinarySearchTree bst;
    std::vector<int> arr = {5, 3, 7, 2, 4, 6, 8};
    for(auto e : arr)
    {
        std::cout << "Inserting: " << e << std::endl;
        bst.Insert(e);
    }
    bst.TraverseTree();
    return 0;
}

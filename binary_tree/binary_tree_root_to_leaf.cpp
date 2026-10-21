#include <iostream>
#include <vector>

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int value)
    : val(value)
    , left(nullptr)
    , right(nullptr)
    {
    }
};

std::vector<int> path;
int NODE_VALUE;

bool PostOrder(Node* node)
{
    if(node->left==nullptr && node->right==nullptr)
    {
        if(node->val == NODE_VALUE)
        {
            path.push_back(node->val);
            return true;
        }
        else
        {
            return false;   
        }
    }
    path.push_back(node->val);
    bool ret = false;
    if(node->left)
    {
        ret = PostOrder(node->left);
    }
    if(!ret && node->right)
    {
        ret = PostOrder(node->right);
    }
    if(!ret)
    {
        path.pop_back();
    }
    return ret;
}

int main()
{
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    NODE_VALUE = 6;
    if(PostOrder(root))
    {
        for(int val : path)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
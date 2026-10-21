#include <iostream>
#include <vector>

struct Node
{
    int val;
    Node *left;
    Node *right;
    bool flag;
    Node(int value)
    : val(value)
    , left(nullptr)
    , right(nullptr)
    , flag(false)
    {
    }
};

int LCA;

bool isRequiredNode(int val, int n1=6, int n2=7)
{
    return (val == n1 || val == n2);
}

void lca(Node* node)
{
    if(node->left == nullptr && node->right == nullptr)
    {
        if(isRequiredNode(node->val))
        {
            node->flag = true;
        }
        return;
    }
    lca(node->left);
    lca(node->right);

    if(node->left->flag == true && node->right->flag == true)
    {
        LCA = node->val;
    }
    if(node->left->flag == true || node->right->flag == true)
    {
        node->flag = true;
    }
}

int main()
{
     Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(5);
    root->left->left = new Node(3);
    root->left->right = new Node(4);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    lca(root);
    std::cout << "LCA: " << LCA << std::endl;
    return 0;
}

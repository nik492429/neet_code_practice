#include <iostream>
#include <algorithm>

int MAX_LENGTH = 0;
struct Node
{
    int val;
    int maxPathSum;
    Node *left;
    Node *right;
    Node(int value)
    : val(value)
    , maxPathSum(value)
    , left(nullptr)
    , right(nullptr)
    {}
};

void PostOrderTraverse(Node *node)
{
    if(node->left == nullptr && node->right == nullptr)
    {
        node->maxPathSum = node->val;
        return;
    }
    if(node->left)
    {
        PostOrderTraverse(node->left);
    }
    if(node->right)
    {
        PostOrderTraverse(node->right);
    }
    int leftLength = node->left ? node->left->maxPathSum : 0;
    int rightLength = node->right ? node->right->maxPathSum : 0;
    int treeLength = leftLength + rightLength + node->val;
    if(treeLength > MAX_LENGTH)
    {
        MAX_LENGTH = treeLength;
    }
    node->maxPathSum = std::max(leftLength, rightLength) + node->val;
};

int main()
{
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    Node *root = new Node(1);
    root->left = new Node(14);
    root->right = new Node(2);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(1);
    root->right->right = new Node(1);

    PostOrderTraverse(root);
    // MAX_LENGTH = std::max(MAX_LENGTH, root->maxPathSum);
    std::cout << "Maximum path sum: " << MAX_LENGTH << '\n';

    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}






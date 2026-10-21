#include <iostream>
#include <stack>

struct Node
{
    int val;
    struct Node* next;
    Node(int v)
    : val(v)
    , next(nullptr)
    {
    }
};


struct Node* ReverseKNodes(struct Node* node, int K)
{
    struct Node* head = nullptr;
    struct Node* current = nullptr;
    std::stack<struct Node*> nodeStack;
    while(node != nullptr)
    {
        nodeStack.push(node);
        node = node->next;
        if(nodeStack.size() == K)
        {
            auto next_list_ptr = nodeStack.top()->next;
            while(!nodeStack.empty())
            {
                auto temp = nodeStack.top();
                nodeStack.pop();
                if(head == nullptr)
                {
                    head = temp;
                }
                if(current != nullptr)
                {
                    current->next = temp; 
                }
                current = temp;
            }
            current->next = next_list_ptr;
        }

    } 
    return head;
}

void PrintList(struct Node* node)
{
    while(node != nullptr)
    {
        std::cout << node->val << " ";
        node = node->next;
    }
    std::cout << std::endl;
}


int main()
{
    // create a list with 13 nodes: 1 -> 2 -> ... -> 13
    struct Node* head = new Node(1);
    struct Node* tail = head;
    for(int i = 2; i <= 13; ++i)
    {
        tail->next = new Node(i);
        tail = tail->next;
    }

    int K = 5;
    head = ReverseKNodes(head, K);
    PrintList(head);
}



#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    ListNode *head = new ListNode(3);
    ListNode *current = head;
    ListNode *cycleStart = nullptr;

    for (int i = 1; i < 20; ++i) {
        current->next = new ListNode(i);
        current = current->next;

        if (i == 5) {
            cycleStart = current;
        }
    }

    current->next = cycleStart; // connects the tail back 14 nodes

    Solution sol;
    std::cout << (sol.hasCycle(head) ? "Cycle detected" : "No cycle") << std::endl;

    return 0;
}

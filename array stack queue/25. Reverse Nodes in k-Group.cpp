/**
* Definition for singly-linked list.
**/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
 * First pass, get the length of the list.
 * Second pass, swap in groups.
 * Time: O(n), space: o(1)
 */
ListNode *reverseKGroup(ListNode *head, int k) {
    if (!head || k == 1) return head;
    ListNode dummy(0);
    dummy.next = head;
    int len = 1;
    while (head = head->next) len++;
    ListNode* pre = &dummy;
    for (int l = 0; l + k <= len; l += k) {
        ListNode* cur = pre->next;
        ListNode* nxt = cur->next;
        for (int i = 1; i < k; ++i) {
            cur->next = nxt->next;
            nxt->next = pre->next;
            pre->next = nxt;
            nxt = cur->next;
        }
        pre = cur;
    }
    return dummy.next;
}

int main()
{
    ListNode node4(4);
    ListNode node3(3, &node4);
    ListNode node2(2, &node3);
    ListNode node1(1, &node2);

    reverseKGroup(&node1, 2);

    return 0;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
//Store the m – 1 and m-th item as prev and tail before reversing
//Reverse the m to n, return the head and tail->next of the reversed list
//Reconnect prev and head, tail and tail->next

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(!head->next || left == right)
            return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *p = &dummy;
        // Find the m-1 node
        for(int i = 0; i < left-1; ++i){
            p = p->next;
        }
        // Process node m
        ListNode *prev = p;
        ListNode *cur = p->next;
        ListNode *tail = cur;
        // Reverse from m to n
        for(int i = left; i <= right; ++i){
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        // connect three parts
        p->next = prev;
        tail->next = cur;
        return dummy.next;
//         if(!head->next || left == right)
//             return head;
//         ListNode *pre(0), *cur=head, *nxt=head->next, *end, *start;
//         int idx = 1;
//         while(cur){
//             printf("idx:%d, node: %d\n", idx, cur->val);
//             if(idx == left){
//                 start = pre;
//                 end = cur;
//             }
//             if(idx > left && idx <= right)
//                 cur->next = pre;

//             if(idx == right){
//                 if(start) start->next = cur;
//                 end->next = nxt;
//                 break;
//             }
//             pre = cur;
//             cur = nxt;
//             if(nxt) nxt = nxt->next;


//             idx++;
//         }
//         return start ? head : cur;
    }
};
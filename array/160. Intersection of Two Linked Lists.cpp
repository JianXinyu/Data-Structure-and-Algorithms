/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return nullptr;
        ListNode *p = headA, *q = headB;
        while(p != q){
            if(!p) p = headB;
            else
                p = p->next;
            if(!q) q = headA;
            else
                q = q->next;
        }
        return p;
    }
};
// class Solution {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         if(!headA || !headB) return nullptr;
//         ListNode *cur = headA;
//         while(cur){
//             cur->val -= 1e5;
//             cur = cur->next;
//         }

//         ListNode *ans = headB;
//         while(ans && ans->val > 0){
//             ans = ans->next;
//         }

//         cur = headA;
//         while(cur){
//             cur->val += 1e5;
//             cur = cur->next;
//         }
//         return ans;
//     }
// };
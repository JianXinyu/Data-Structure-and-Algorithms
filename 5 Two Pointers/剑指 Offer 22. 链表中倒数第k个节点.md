```cpp
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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head;
        ListNode* slow = head;
        for(int i = 0; i < k-1; i++){
            fast = fast->next;
        }
        while( fast->next ){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

----        
		while( fast && k>0 ){
            fast = fast->next;
            k--;
        }
        while( fast ){
            fast = fast->next;
            slow = slow->next;
        }

```
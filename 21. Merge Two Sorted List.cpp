// recursion
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(!l1 || !l2)
        return l1 ? l1 : l2;

    if(l1->val <= l2->val){
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else{
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
// own solution - wrong
ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2) {
    ListNode *lst1 = nullptr, *cur1 = l1;
    ListNode *lst2 = nullptr, *cur2 = l2;

    // If one of the list is emptry, return the other one.
    if(!l1 || !l2)
        return l1 ? l1 : l2;

    while(cur1 && cur2){
//        ListNode *next1 = cur1->next, *next2 = cur2->next;

        if(cur1->val <= cur2->val){
            lst1 = cur1;
            cur1 = cur1->next;
        }

        else{
            if(!lst1) {
                lst1 = cur1;
            }
            else{
                lst1->next = cur2;
            }
            lst2 = cur2;
            cur2 = cur2->next;
            lst2->next = cur1;
        }
    }

    if(!cur1) lst1->next = cur2;

    return l1->val <= l2->val ? l1 : l2;
}

void printList(ListNode *l){
    while(l){
        cout << l->val << ' ';
        l = l->next;
    }
}
int main()
{
    ListNode l11(5);
    ListNode l23(4);
    ListNode l22(2, &l23);
    ListNode l21(1, &l22);
    ListNode *ret = mergeTwoLists(&l11, &l21);
    printList(ret);
    return 0;
}
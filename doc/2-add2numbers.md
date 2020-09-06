初次解法：

​	逻辑: 先转为numbers相加，再将和转为list

​	问题：当numbers很大时，超出int范围

```C++
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
#include <math.h>

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int num1, num2, sum;
        num1 = List2Num(l1);
        num2 = List2Num(l2);
        sum = num1 + num2;
        return Num2List(sum);
    }
    
private:
    int List2Num(ListNode* list)
    {
        int num = 0;
        int idx = 0;
        while(list->next)
        {
            num += list->val * pow(10,idx);
            idx ++;
            list = list->next;
        }
        num += list->val * pow(10, idx);
        return num;        
    }
    
    ListNode* Num2List(int num)
    {
        ListNode* result;
        if(num < 10)
        {
            result = new ListNode(num);
        }
        else
        {   
            result = new ListNode(num%10, Num2List(num/10));
        }
        return result;
    }
};
```

第二次尝试：

​	逻辑：先无脑按位相加，再将大于9的位取模进一。

​	问题：虽运行快，但内存占用过多。

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum = l1->val + l2->val;
        ListNode *result;
        ListNode *tmp;
        tmp = add(l1,l2);
        result = reorganize(tmp);
        return result;
    }
    
private:
    ListNode* add(ListNode* l1, ListNode* l2)
    {
        int sum = l1->val + l2->val;
        ListNode *result;
        if(l1->next && l2->next)
            result = new ListNode(sum, add(l1->next, l2->next));
        else if(!l1->next && l2->next)
            result = new ListNode(sum, l2->next);
        else if(l1->next && !l2->next)
            result = new ListNode(sum, l1->next);
        else 
            result = new ListNode(sum);
        return result;
    }
    
    ListNode* reorganize(ListNode* ln, int carray = 0)
    {
        ListNode *result;
        ln->val+=carray;
        carray = ln->val / 10;
        ln->val %= 10;
        if(ln->next)
            result = new ListNode(ln->val, reorganize(ln->next, carray));
        else 
            if(carray > 0)
                result = new ListNode(ln->val, new ListNode(carray));
            else
                result = new ListNode(ln->val);
        return result;
    }
};
```

Others' solution

```C++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum=0;
        ListNode *l3=NULL;
        ListNode **node=&l3;//! clever, using double pointer
        while(l1!=NULL||l2!=NULL||sum>0)
        {
            if(l1!=NULL)
            {
                sum+=l1->val;
                l1=l1->next;
            }
            if(l2!=NULL)
            {
                sum+=l2->val;
                l2=l2->next;
            }
            (*node)=new ListNode(sum%10);
            sum/=10;
            node=&((*node)->next);
        }        
        return l3;
    }
};
```


# The List ADT
## Implementation
### Array
### Linked list

## `vector` and `list` in the STL
- `vector`: a growable array implementation of the List ADT. internally stores an array, allows the array to grow by doubling its capacity when needed 
	- Pros: indexable in constant time
	- Cons: insertion of new items and removal of existing items  are expensive==exact complexity?==, unless the changes are made at the end of the `vector`.
- `list`: a doubly linked list implementation of the List ADT
	- Pros: insertion of new items and removal of existing items are cheap, provided that the position of the changes is know
	- Cons: isn't easily indexable

Both `vector` and `list` are inefficient for searches.
list refers to the more general List ADT.

## Vector
a first-class type, unlike primitive arrays

>- The array is simply a pointer variable to a block of memory; the actual array size must be maintained separately by the programmer.
>- The block of memory can be allocated via new[] but then must be freed via delete[].
>- The block of memory cannot be resized (but a new, presumably larger block can be

To avoid ambiguities with the `vector` class in STL, we will name our class template *Vector*. The *Vector* will:
1. maintain the primitive array (via a pointer variable to the block of allocated memory), the array **capacity**, and the current number of items stored in the *Vector*.
2. implement the Big-Five to provide:
	- deep-copy semantics for the copy constructor and operator=, 
	- a destructor to reclaim the primitive array.
	- move semantics.
3. provide 
	1. a resize routine that will change (generally to a larger number) the size of the *Vector* 
	2. a reserve routine that will change (generally to a larger number) the capacity of the *Vector*. The capacity is changed by obtaining a new block of memory for the primitive array, copying the old block into the new block, and reclaiming the old block.[^sizecapacity]
4. provide an implementation of [[Using matrices#Operator]] \[ \](both an accessor and mutator version).
5. provide basic routines, such as **size**, **empty**, **clear** (which are typically one-liners), **back**, **pop_back**, and **push_back**. The push_back routine will call reserve if the size and capacity are same.
6. provide support for the nested types **iterator** and **const_iterator**, and associated **begin** and **end** methods.

[code](./code/Vector.h)
don't quiet understand copy constructor and operator = 

Implementation of the *copy assignment operator=* using a *copy constructor* and *swap*, while simple, is certainly <u>not the most efficient method</u>, especially in the case where both Vectors have the same size. In that special case, which can be tested for, it can be more efficient to simply copy each element one by one using *Object’s operator=*.

[^sizecapacity]:  **Size** is the number of items **currently** in the vector. **Capacity** how many items can be fit in the vector before it is "full". Once full, adding new items will result in a new, larger block of memory being allocated and the existing items being copied to it

-------------------------
# Stack
LIFO(Last In First Out)
栈的常用操作: 
- push. O(1)
- pop. O(1)
- top
- isEmpty

实现：数组栈，链表栈

应用：
- 函数调用栈
- 浏览器前进后退
- 匹配括号
- 单调栈用来寻找下一个更大（更小）元素

题目推荐：
-   [[394. Decode String]]
-   [[946. Validate Stack Sequences]]
-   [[1381. Design a Stack With Increment Operation]]


### Postfix Expressions

我们正常使用的数学计算式成为中缀表达式(infix expression)，比如 $1+2+3*4$ 。常见的科学计算器计算的结果都是15，因为考虑了运算优先级，相当于自动加上了括号。但是早期简单的计算器只会按顺序无脑计算，计算结果变成24。所以我们应想办法用顺序的表达式来实现这样的计算(evaluate)顺序：计算1+2的和记为A1，计算3*4记为A2，将A1+A2，最后将其和存在A1。据此我们将表达式写为：$1\quad 2+\quad 3\quad 4 \* +$ 。 这种表达式成为后缀表达式(postfix expression)，又称为Reverse Polish Notation(RPN)。

用Stack最容易evaluate RPN:
- 看到数(operand)时，push into stack;
- 看到运算(operator)符时，把最后两个数从stack中pop出来计算，再将计算结果push into stack。
the time to evaluate a postfix expression is $O(N)$，because processing each element in the input consists of stack operations and therefore takes constant time.
pros of postfix expression: 不需要知道任何先验规则，诸如运算优先级。

下面给出实现:

```C++
/**
 * conduct operation
 * @param a, b: operands
 * @param oper: operator
 * @return calculation result
 * if the operator is wrong, return negative infinity
 */
float calculation(float a, float b, char oper)
{
    if(oper == '+')
        return a + b;
    else if(oper == '-')
        return a - b;
    else if(oper == '*')
        return a * b;
    else if(oper == '/')
        return a / b;
    else if(oper == '^')
        return std::pow(a, b);
    else
        return INT_MIN;
}

/**
 * calculate a postfix expression using reverse Polish notation (RPN)
 * Logic:   find numbers and store in the stack;
 *          find operand, conduct calculation and store the result
 * @param iterators
 * @return calculation result
 */
float RPN(const std::vector<std::string> &expr)
{
    std::stack<float> numPool;
    for(const auto& i : expr)
    {
        char ch = i[0];
        //if operand
        if(ch >= '0' && ch <= '9')
        {
            //store the number
            numPool.push(float(ch - '0'));
        }
        //if operator
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        {
            //get and delete the last number
            float num2 = numPool.top();
            numPool.pop();
            //get and delete the second last number
            float num1 = numPool.top();
            numPool.pop();
            //store the result
            numPool.push(calculation(num1, num2, ch));
        }
    }

    return numPool.top();
}

int main()
{
    std::vector<std::string> expr = { "1", "2", "+", "3", "*"};
    std::cout << R"(Result of { "1", "2", "+", "3", "*" } is: )" << RPN(expr) << '\n';
    
    return 0;
}
```

### Infix to Postfix Conversion
stack不仅可以用来计算后缀表达式(evaluate a **postfix** expression)，也可以用来将中缀(**infix**)表达式转为后缀。
为方便阐述，我们只考虑+、\*。 
- infix expression: $a+b*c+(d*e+f)*g$
- postfix expression: $a\quad b\quad c *  + d\quad e* f+g*+$
  （空格只用于区分不同的数）
  步骤如下：
  1. 读到operand时，立即放入output
  2. 读到operator和左括号时，先放到一个stack里
  3. 如果读到右括号，pop the stack, writing symbols until we encounter a corresponding left parenthesis, which is popped but not output. 如果读到其他symbol，如+、-、(，then we pop entries from the stack until we find an entry of lower priority.  One exception is that we never remove a ( from the stack except when processing a ). For the purposes of this operation, + has lowest priority and **( highest**. When the popping is done, we push the operator onto the stack.
  4. Finally, if we read the end of input, we pop the stack until it is empty, writing symbols onto the output.
  
  实现参考自[Rosetta Code](https://rosettacode.org/wiki/Parsing/Shunting-yard_algorithm#C.2B.2B)，写的实在是太漂亮了！仅仅做了少许改动，去掉了异常处理（编译器不支持），改了一些表述使其更符合规范。 限于篇幅，请见我的[Github](https://github.com/JianXinyu/ENGI-4892-Data-Structure-and-Algorithms/blob/master/Exercises/5StackQueue/mathExpression.cpp#L77).


## 单调栈
单调栈要求栈中的元素是单调递增或单调递减的。是否是严格单调递增/递减要看实际情况。注意这里的单调顺序指的是从栈顶到栈底的顺序，i.e., 出栈顺序。其实顺序不重要，理解就行
- \[1,2,3,4\] 是一个单调递减栈，因为此时的出栈顺序是 4，3，2，1。
- \[3,2,1\] 是一个单调递增栈
- \[1,3,2\] 不是单调栈

**适用情况**
> 对数列中的每个元素，寻找其右侧/左侧第一个比它大/小的元素位置。
- 单调递增栈：比栈顶元素小的才入栈，否则就pop。适用于求解第一个大于栈顶元素的数。
- 单调递减栈：比栈顶元素大的才入栈，否则就pop。适用于求解第一个小于栈顶元素的数。

这个算法的过程用一句话总结就是，**如果压栈之后仍然可以保持单调性，那么直接压。否则先弹出栈的元素，直到压入之后可以保持单调性。**  
这个算法的原理用一句话总结就是，**被弹出的元素都是大于当前元素的，并且由于栈是单调减的，因此在被弹出元素之后小于其本身的最近的就是当前元素了**

### Example
比如依次将数组 \[1,3,4,5,2,9,6\] 压入单调递减栈。
1.  首先压入 1，此时的栈为：\[1\]
2.  继续压入 3，此时的栈为：\[1,3\]
3.  继续压入 4，此时的栈为：\[1,3,4\]
4.  继续压入 5，此时的栈为：\[1,3,4,5\]
5.  **如果**继续压入 2，此时的栈为：\[1,3,4,5,2\] 不满足单调递减栈的特性， 因此需要调整。如何调整？由于栈只有 pop 操作，因此我们只好不断 pop，直到满足单调递减为止。
6.  上面其实我们并没有压入 2，而是先 pop，pop 到压入 2 依然可以保持单调递减再 压入 2，此时的栈为：\[1,2\]
7.  继续压入 9，此时的栈为：\[1,2,9\]
8.  **如果**继续压入 6，则不满足单调递减栈的特性， 我们故技重施，不断 pop，直到满足单调递减为止。此时的栈为：\[1,2,6\]

注意这里的栈仍然是非空的，如果有的题目需要用到所有数组的信息，那么很有可能因没有考虑边界而不能通过所有的测试用例。 这里介绍一个技巧 - **哨兵法**，这个技巧经常用在单调栈的算法中。

对于上面的例子，我可以在原数组 \[1,3,4,5,2,9,6\] 的右侧添加一个小于数组中最小值的项即可，比如 -1。此时的数组是 \[1,3,4,5,2,9,6,-1\]。这种技巧可以简化代码逻辑，大家尽量掌握。

上面的例子如果你明白了，就不难理解为啥单调栈适合求解**下一个大于 xxx**或者**下一个小于 xxx**这种题目了。比如上面的例子，我们就可以很容易地求出**在其之后第一个小于其本身的位置**。比如 3 的索引是 1，小于 3 的第一个索引是 4，2 的索引 4，小于 2 的第一个索引是 0，但是其在 2 的索引 4 之前，因此不符合条件，也就是不存在**在 2 之后第一个小于 2 本身的位置**。

上面的例子，我们在第 6 步开始 pop，第一个被 pop 出来的是 5，因此 5 之后的第一个小于 5 的索引就是 4。同理被 pop 出来的 3，4，5 也都是 4。

第 8 步，我们又开始 pop 了。此时 pop 出来的是 9，因此 9 之后第一个小于 9 的索引就是 6。

实际上我们更常用的是用单调栈保存元素的**下标**，而非其值。

如果用 ans 来表示**在其之后第一个小于其本身的位置**，ans\[i\] 表示 arr\[i\] 之后第一个小于 arr\[i\] 的位置， ans\[i\] 为 -1 表示这样的位置不存在，比如前文提到的 2。在上面的例子中， 如果位置指的是绝对位置, i.e., index, 那么ans 是 \[-1,4,4,4,-1, 6,-1\]；如果位置指的是相对位置, i.e., offset, 那么ans是\[-1, 3, 2, 1, -1, 1, -1\]

### Code
```python
from typing import List
def monostoneStack(T: List[int]) -> List[int]:
    stack = [] # stack存放是的index,而不是原数组的value
    ans = [-1] * len(T)
    for i in range(len(T)):
        # while stack and T[i] < T[stack[-1]]: # 单调递减栈
        while stack and T[i] > T[stack[-1]]: # 单调递增栈
            peek = stack.pop(-1)
            # ans[peek] = i # 记录index
            ans[peek] = i - peek # 记录距离
        stack.append(i)
    return ans, stack
    
mylist = [1,3,4,5,2,9,6]
(ans, stack) = monostoneStack(mylist)
# print(ans)

print ("[", end=' ', flush=True)
for i in stack:
    print(mylist[i], end=' ', flush=True)
print(']', flush=True)
```

```cpp
for(int i=1;i<=n;i++)
{
    while(!sta.empty()&&a[sta.top()]>=a[i]) sta.pop();
    sta.push(i);
}//c++ stl版
for(int i=1;i<=n;i++)
{
    while(top>0&&a[sta[top]]>=a[i]) top--;
    sta[++top]=i;
}//数组版
```

**复杂度分析**
N 为数组长度
-   时间复杂度：由于 arr 的元素最多只会入栈，出栈一次，因此时间复杂度仍然是 $O(N)$
-   空间复杂度：由于使用了栈， 并且栈的长度最大是和 arr 长度一致，因此空间复杂度是 $O(N)$

### 题目
-   去除重复字母
-   移掉 K 位数字
-   下一个更大元素 I
-   最短无序连续子数组
-   股票价格跨度

medium:
-   [[739. Daily Temperatures]]
-   [[42. Trapping Rain Water]]
hard:
-   [[84. Largest Rectangle in Histogram]]

- [[768. Max Chunks To Make Sorted II]]
- [[239. Sliding Window Maximum]]

#### 拓展
如何寻找左侧第二个比当前元素大的元素位置？

题目大意：一列人在排队，身高有高有矮，每个人可以插队无限次比自己矮的人，仅可以插队一次比自己高的人，问如果只有一个人插队，这个人最多能排到多前面？ 答案实际上就是左侧第二个比当前元素大的元素位置+1。

用单调栈可以简单快速求解出第一个，但第二个却并不能直接用单调栈求解。我们可能会想到，维护**两个单调栈**！当元素被第一个单调栈弹出时，塞进第二个单调栈，当其再次被弹出时遇到的就是答案。但第二个单调栈的单调性就不能简单粗暴地去维护，而需要一些技巧——因为栈先进后出的特性，我们需要把取出的元素先塞进一个临时栈，然后再从临时栈塞进第二个单调栈，以维持其单调性。

每个元素最多被塞入三次栈，弹出三次栈，总时间复杂度依旧是O(n)的，当然，常数可能比较大。
```
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define sz size()
#define pii pair<int,long long>
#define mkp make_pair
using namespace std;
const int N=1e6+10;
stack<int>st1,st2,st3;
int a[N],ans[N];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=n;i>=1;i--)
    {
        while(!st2.empty()&&a[st2.top()]<a[i])
        {
            ans[st2.top()]=i+1;
            st2.pop();
        }
        while(!st1.empty()&&a[st1.top()]<a[i])
        {
            st3.push(st1.top());
            st1.pop();
        }
        st1.push(i);
        while(!st3.empty()) st2.push(st3.top()),st3.pop();
    }
    while(!st1.empty()) ans[st1.top()]=1,st1.pop();
    while(!st2.empty()) ans[st2.top()]=1,st2.pop();
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}
```




# Queue

就像stack，queue也是list。 但与stack不同的是，queue在一端插入，却在另一端删除。

queue的基本操作有:

- enqueue: inserts an element at the end of the list (called the rear)
- dequeue: deletes (and returns) the element at the start of the list (called the front)


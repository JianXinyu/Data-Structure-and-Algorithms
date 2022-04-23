# Question
一维扫雷，给一个一维数组，每个数字代表它左下、正下、右下的雷的数量总和（边界记为0），要求返回所有雷的可能组合。可以理解为有两行数组，第一行是索引，第二行是对应位置的地雷的数量，0是没有雷，1是有雷；第一行是左下、正下、右下的雷的数量和，取值范围0-3。

Ex 1. 输入[1,1]，返回[[0,1],[1,0]]
Ex2. 输入[1, 2, 3, 2, 1]，返回[[0, 1, 1, 1, 0]]

# Analysis
$$
\begin{aligned}
	0+x0+x1 &=m0\\
	x0+x1+x2 &=m1\\
	\cdots\\
	x_{n-2}+x_{n-1}+0 &=m_{n-1}
\end{aligned}
$$
上下两式相减：
$$
\begin{aligned}
	x_2 - 0 &= m_1 - m_0\\
	x_3 - x_0 &= m_2 - m_1\\
	\cdots\\
	0 - x_{n-3} &= m_{n-1} - m_{n-2}
\end{aligned}
$$
只需要确定$x_0, x_1, x_2$即可，其中$x_2$可以唯一确定。实际上最多只有两种情况
n=1时只有{1}, {0} 两种情况 
n=2时只有 {0, 0}, {1, 1}, {2, 2} 三种情况
```cpp
vector<vector<int>> mines(vector<int> &input) {  
    const int n = input.size();  
    if (n == 1) // 只有 {1}, {0} 两种情况  
        return {input};  
  
    int x2 = input[1] - input[0];  
    function<vector<int>(int, int)> calc_mines = [&](int x0, int x1) -> vector<int> {  
        vector<int> vec(n);  
        vec[0] = x0, vec[1] = x1;  
        if (n > 2) vec[2] = x2;  
        for (int i = 3; i < n; i++) {  
            vec[i] = input[i - 1] - input[i - 2] + vec[i - 3];  
            if (vec[i] != 0 && vec[i] != 1) return {};  
        }  
        return vec;  
    };  
    vector<vector<int>> ans;  
    if (input[0] == 0) {ans.push_back(calc_mines(0, 0));}  
    else if (input[0] == 2) {ans.push_back(calc_mines(1, 1));}  
    else {  
        auto vec1 = calc_mines(0, 1);  
        auto vec2 = calc_mines(1, 0);  
        if (!vec1.empty()) ans.push_back(vec1);  
        if (!vec2.empty()) ans.push_back(vec2);  
    }  
    return ans;  
}
```
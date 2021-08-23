// stack
// 注意map的设计很巧妙
// 最后不能返回true，而是.empty()
bool isValid(string s) {
    stack<int> stk;
    map<char, char> p{{')', '('}, {']', '['}, {'}', '{'}};

    for(char c : s){
        if(!p.count(c))
            stk.push(c);
        else{
            if(stk.empty() || p[c] != stk.top()) return false;
            stk.pop();
        }
    }
    return stk.empty();
}
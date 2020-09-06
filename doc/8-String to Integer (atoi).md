time: 30min, submit twice;

Runtime: 8 ms, faster than 40.10% of C++ online submissions for String to Integer (atoi).

Memory Usage: 6.4 MB, less than 23.54% of C++ online submissions for String to Integer (atoi).

```C++
class Solution {
public:
    int myAtoi(string str) {
        int n = str.size();
        int output = 0;
        int idx = 0;
        while(str[idx] == ' ')
        {
            if(idx < n-1) idx++;
            else if(idx == n-1) return 0;
        }

        if(str[idx] == '-')
        {
            if(idx == n-1) return 0;
            while(isdigit(str[++idx]))
            {
                int tmp = str[idx] - '0';
                if(output < INT_MIN / 10 || (output == INT_MIN / 10 && tmp > 8))
                {
                    return INT_MIN;
                }
                else 
                    output = output * 10 - tmp;
                if(idx == n-1) break;
            }
        }
        else if(str[idx] == '+')
        {
            if(idx == n-1) return 0;
            while(isdigit(str[++idx]))
            {
                int tmp = str[idx] - '0';
                if(output > INT_MAX / 10 || (output == INT_MAX / 10 && tmp > 7))
                {
                    return INT_MAX;  
                }
                else 
                    output = output * 10 + tmp;
                if(idx == n-1) break;
            }
        }
        else if(isdigit(str[idx]))
        {
            while(isdigit(str[idx]))
            {
                int tmp = str[idx] - '0';
                if(output > INT_MAX / 10 || (output == INT_MAX / 10 && tmp > 7))
                {
                    return INT_MAX; 
                }
                else 
                    output = output * 10 + tmp;
                if(idx == n-1) break;
                else ++idx;
            }
        }
        else return 0;
        
        return output;
    }
};
```

评价：速度一般，占用内存，代码复用率太高，不简洁。



improved version:

Runtime: 4 ms, faster than 85.20% of C++ online submissions for String to Integer (atoi).

Memory Usage: 6.2 MB, less than 81.12% of C++ online submissions for String to Integer (atoi).

```C++
class Solution {
public:
    int myAtoi(string str) {
        int n = str.size();
        int output = 0;
        int idx = 0;
        int sign = 1; // 1 is positive, -1 is negative
        //Discard whitespaces in the beginning
        while(idx < n && str[idx] == ' ')
        {
            idx++;
        }
        
        //Check if optional sign exits
        if(idx < n && (str[idx] == '-' || str[idx] == '+'))
        {
            sign = (str[idx++] == '-') ? -1 : 1;
        }
        
        //Construct the output integer
        while(idx < n && isdigit(str[idx]))
        {
            int tmp = str[idx] - '0';
            if(output > INT_MAX / 10 || (output == INT_MAX / 10 && tmp > 7))
            {
                return INT_MAX; 
            }
            else if(output < INT_MIN / 10 || (output == INT_MIN / 10 && tmp > 8))
            {
                return INT_MIN;
            }
            else 
                output = output * 10 + sign * tmp;
            ++idx;
        }
        //if the first non-white space character is not sign or digit, the output is 0
        return output;
    }
};
```




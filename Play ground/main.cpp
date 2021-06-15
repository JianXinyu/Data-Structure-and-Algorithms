#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "A()" << endl; }
    A(const A& a) { cout << "copy A()" << endl; }
    ~A() { cout << "~A()" << endl; }
    A& operator=(const A& a) {
        cout << "operator=" << endl;
        return *this;
    }
};
class B {
public:
    B(A a) { mA = a; }
private:
    A mA;
};
int main(){
    A a;
    B b(a);
}
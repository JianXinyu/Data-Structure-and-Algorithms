#include <iostream>
using namespace std;

class A{
public:
    A(){cout << "CA" << endl;}
    virtual void show(){
        cout << "A" << endl;
    }
    ~A(){cout << "DA" << endl;}
};
class B : public A{
public:
    B(){cout << "CB" << endl;}
    ~B(){cout << "DB" << endl;}
    void show() override{
        cout << "B" << endl;
    }
};
int main(){
    A* ptr = new B();
    ptr->show();
    delete ptr;
    return 0;
}
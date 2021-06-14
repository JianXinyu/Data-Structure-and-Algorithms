#include <iostream>
#include "methods.h"
#include "nodes.h"

#include <memory>
#include <new>

using namespace std;

namespace obj_new_delete{
    class Obj{
    public:
        Obj():mCount(0) { cout << "Obj ctor" << endl; }
        ~Obj() { cout << "~Obj dtor" << endl; }

    private:
        int mCount;
    };

    void test_new_obj(){
        Obj *obj = new Obj();
    delete obj;
    }
}

int main(){
    obj_new_delete::test_new_obj();
    return 0;
}

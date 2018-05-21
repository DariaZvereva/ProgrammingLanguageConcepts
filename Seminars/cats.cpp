#include <iostream>

struct A {
    int a = 0;
    virtual ~A() {
        std::cout << "destroy A" << std::endl;
    }
};

struct B : A {
    int b = 1;
};

struct C : A {
    int c = 2;
};

struct D : A, B {
    int d = 3;
};

int main() {

    A* ptrA = new D;
    B* ptrB = static_cast<B*>(ptrA);
    std::cout << ptrB << std::endl;
    B* ptrBB = dynamic_cast<B*>(ptrA);
    std::cout << ptrBB << std::endl;
    //B* ptrB = dynamic_cast<B*>(ptrD);
    //C* ptrC = dynamic_cast<C*>(ptrD);

    system("pause");
    return 0;
}
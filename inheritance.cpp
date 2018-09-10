/* In case you want to have an array of objects of different type, 
Think wisely how not to get confused.
*/
#include <iostream>

using namespace std;

/* Here we have two classes - B and C - inheritting from class A,
and two functions - getX() in class B and getY() in class C - returning
values of private block (you can think of x (in B) and y (in C) as elements' IDs).
*/

class A {
public:
    A() {}
    virtual ~A() {}
    int get10() {return 10;}
};

class B: public A {
public:
    B(int _x) : A(), x(_x) {}
    virtual ~B() {}
    int get20() {return 20;}
    int getX() {return x;}
private:
    int x;
};

class C: public A {
public:
    C(int _y) : A(), y(_y) { m_val = 5;}
    virtual ~C() {}
    int getY() {return y;}
    int getMVal() {return m_val;}
private:
    int y;
    int m_val;
};

int main()
{
    A* p_b = new B(1);
    A* p_c = new C(2);
    /* Some fellow programmers (like me ;) might think that 
    the following line will produce an exception, as far as object p_b
    does not have function getY(). */
    if (static_cast<C*>(p_b)->getY() == 1) {
        cout << "It's B" << endl; //this output will be hit
    }
    else {
        cout << "It's C" << endl;
    }
    if (static_cast<B*>(p_c)->getX() == 1) {
        cout << "It's B" << endl;
    }
    else {
        cout << "It's C" << endl; //this output will be hit
    }
    /* First think you have to understand is: functions are not stored inside objects,
    they are placed somewhere and lines like 'p_c->getY()' at compile time places the correct address in memory.
    If you try to trick syntaxic checks like I did here, you will get to the function that returns an attribute.
    And here comes the Second point: how is the value returned? Well, if you ran 'static_cast<C*>(p_b)->getY()',
    you came to the point of function getY(), that returns a value of object at it's offset corresponding to y.
    Which is accidently pointing to x. Basicly because we inherit fron she same class A in both cases, our private
    blocks are starting at the same address. if we place m_val above y in class C, operation 
    'static_cast<B*>(p_c)->getX()' will return value of m_val;
    */
    return 0;
}

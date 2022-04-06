# include <iostream>


class A {};
class B {};

struct  test {

    test( void ) {}
    ~test( void ) {}

    void    tesst(A *a) {
    
        std::cout << "A\n";
    }
    void    tesst(B *a) {
    
        std::cout << "B\n";
    }

};

int main() {

    test a;
    A *t;
    B *c;

    a.tesst(t);
    a.tesst(c);
    return 0;
}
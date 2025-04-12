// C++ supports Multiple Inheritance but throws an ambiguity error if it faces diamond of death

#include <iostream>

class Hello{
    public:
        void sayHello(){
            std::cout << "Hello\n";
        }
};


class Bye{
    public:
        void sayBye(){
            std::cout << "Bye\n";
        }
};

class Greet: public Hello, public Bye{
    public:
        void greet(){
            sayHello();
            sayBye();
        }
};
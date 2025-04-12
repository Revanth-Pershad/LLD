// A class can be derived from on class that is already derived from another class

#include <iostream>

class GrandParent{
    public:
        void sayHello(){
            std::cout << "Hello";
        }
};

class Parent : public GrandParent{
    public:
        void sayBye(){
            std:: cout << "Bye";
        }
};

class Child : public Parent{
    public: 
        void meet(){
            sayHello();
            sayBye();
        }
};
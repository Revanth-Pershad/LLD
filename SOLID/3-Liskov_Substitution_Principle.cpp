/*
    **Derived classes should be replaceable for their base class without breaking functionality.**

- Objects of a subclass should behave like objects of the base class.
- That is -
    - If class B is a child of class A
    - There is a function that takes an Object of Class A to function.
    - Then if we pass it the object of the Class B it should process properly.
*/

// Bad Example
class Bird {
public:
    virtual void fly() {
        // General flying logic
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        throw std::logic_error("Penguins can't fly!");
    }
};

// Correct Example
class Bird {
public:
    virtual void move() = 0;
};

class FlyingBird : public Bird {
public:
    void move() override {
        // Flying logic
    }
};

class Penguin : public Bird {
public:
    void move() override {
        // Swimming logic
    }
};
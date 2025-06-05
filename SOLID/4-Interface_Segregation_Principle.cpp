/*
    **A class should not be forced to implement interfaces it does not use.**

- Instead of a large interface, create smaller, specific interfaces.
*/

// Bad Example
class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
};

class Robot : public Worker {
public:
    void work() override {
        // Work logic
    }

    void eat() override {
        throw std::logic_error("Robots don't eat!"); // This is an unnecessary function
    }
};

// Good Example
class Workable {
public:
    virtual void work() = 0;
};

class Eatable {
public:
    virtual void eat() = 0;
};

class Human : public Workable, public Eatable {
public:
    void work() override {
        // Work logic
    }
    void eat() override {
        // Eat logic
    }
};

class Robot : public Workable {
public:
    void work() override {
        // Work logic
    }
};
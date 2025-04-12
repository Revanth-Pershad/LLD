// ACCESS Modifiers in C++
/* 
    Private : Available only in the Current Class cannot call outside
    Public : Can be called by anyone
    Protected : Can be accisible to Derived Classes and friend functions
*/

// Modified Inheritance
/*
    class Child : public Parent -- Means all the public methods in the parent method are public in child (remaining same)
    class Child : protected Parent --  Public are inherited as protected
    class Child : private Parent -- Both public and protected are inherited as private
*/

// Example
class Parent{
    public:
        void A();
    private:
        void B();
    protected:
        void C();
};

class Child_Public : public Parent{
    // A -> Public;
    // B -> private (Cannot Use as the parent is private)
    // C -> Protected
};

class Child_Protected : protected Parent{
    // A -> protected
    // B -> private (Cannot Use)
    // C -> Protected
};

class Child_Private : private Parent{
    // A -> Private
    // B -> private (Cannot Use)
    // C -> private
};


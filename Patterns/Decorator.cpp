/*
 ----------------------------------------------------------------------------
  DECORATOR PATTERN – QUICK RECAP
  ----------------------------------------------------------------------------
  • Intent : Attach additional responsibilities to an object **dynamically**
             while keeping the same interface.  A flexible alternative to
             subclassing for extending functionality.
  • Typical Uses
        – GUI: adding scrollbars, borders, shadows to a widget
        – I/O streams: buffering, compression, encryption layers
        – Logging / metrics: wrap a service call with tracing
 ----------------------------------------------------------------------------
*/

#include <iostream>
#include <string>

/* =========================================================
   1. Component – the common interface that both core
      objects and decorators share.
   ---------------------------------------------------------*/
class Beverage {
public:
    virtual std::string description() const = 0;
    virtual double      cost()        const = 0;
    virtual ~Beverage() = default;
};

/* =========================================================
   2. Concrete Component – the object we’ll decorate.
   ---------------------------------------------------------*/
class Espresso : public Beverage {
public:
    std::string description() const override { return "Espresso"; }
    double      cost()        const override { return 110.0; } // ₹
};

/* =========================================================
   3. Decorator Base – maintains a pointer to a Beverage and
      forwards calls; subclasses add extra behavior.
   ---------------------------------------------------------*/
class AddOnDecorator : public Beverage {
protected:
    Beverage* wrapped;            // raw pointer for demo simplicity
public:
    explicit AddOnDecorator(Beverage* b) : wrapped(b) {}
    // Default forwarding (may be overridden)
    std::string description() const override { return wrapped->description(); }
    double      cost()        const override { return wrapped->cost(); }
};

/* =========================================================
   4. Concrete Decorators – extend behavior incrementally.
   ---------------------------------------------------------*/
class Milk : public AddOnDecorator {
public:
    explicit Milk(Beverage* b) : AddOnDecorator(b) {}
    std::string description() const override { return wrapped->description() + ", Milk"; }
    double      cost()        const override { return wrapped->cost() + 15.0; }
};

class Mocha : public AddOnDecorator {
public:
    explicit Mocha(Beverage* b) : AddOnDecorator(b) {}
    std::string description() const override { return wrapped->description() + ", Mocha"; }
    double      cost()        const override { return wrapped->cost() + 20.0; }
};

/* =========================================================
   Client code – stacks decorators using `new`.
   ---------------------------------------------------------*/
int main() {
    // Base drink
    Beverage* order = new Espresso();                 // Espresso

    // Dynamically add milk
    order = new Milk(order);                          // Espresso + Milk

    // Add mocha on top of that
    order = new Mocha(order);                         // Espresso + Milk + Mocha

    std::cout << order->description() << "\n";
    std::cout << "Total : ₹" << order->cost() << '\n';

    /* -----------------------------------------------------
       Memory cleanup – with raw pointers you must delete
       the outer-most decorator *once*.  Its destructor will
       automatically delete the wrapped object (implement
       that if you need).  For brevity in this demo:
    -----------------------------------------------------*/
    delete order;   // ❗ In real code prefer smart pointers
}

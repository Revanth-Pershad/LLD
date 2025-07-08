/*
 ----------------------------------------------------------------------------
  FACTORY METHOD PATTERN – QUICK RECAP
  ----------------------------------------------------------------------------
  • Intent            : Define an interface for creating an object, but let
                        subclasses decide which class to instantiate. Rather than client having the if-else statement
                        we have those in our library which makes it much more extensible when we add a new object to 
                        the library.
                        Like a Shape -
                        Suppose we have Circle, Square right now
                        we want to add Triangle later we add it in our factory rather than having the client have the if else 
                        statements.
  • Typical Use Cases : 
        – GUI toolkits that must create platform-specific widgets
        – Parsers that produce concrete AST nodes depending on token type
        – Notification senders (Email / SMS / Push) chosen at runtime
  • Roles
        1. Product (interface)           – the common API clients rely on
        2. ConcreteProduct (implementor) – actual objects returned
        3. Creator (interface / base)    – declares factoryMethod()
        4. ConcreteCreator               – overrides factoryMethod()
 ----------------------------------------------------------------------------
*/

#include <iostream>
#include <memory>
#include <string>

/* =========================================================
   1. Product – an abstract base class (interface).
   ---------------------------------------------------------*/
class Shape {
public:
    virtual void draw() const = 0;           // “Business” operation
    virtual ~Shape() = default;              // Always virtual!
};

/* =========================================================
   2. Concrete Products – specific shapes returned by the
      factory method.
   ---------------------------------------------------------*/
class Circle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Circle\n"; }
};

class Square : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Square\n"; }
};

/* =========================================================
   3. Creator – declares *factoryMethod()* that returns a
      `Shape`.  It may also provide default (virtual) logic
      that uses the product.
   ---------------------------------------------------------*/
class ShapeCreator {
public:
    // ***Factory Method*** : *decouples* client code from
    //                        concrete classes.
    virtual std::unique_ptr<Shape> factoryMethod() const = 0;

    // A generic operation that **depends only on the Product
    // interface**, not its concrete type.
    void drawShape() const {
        auto shape = factoryMethod();   // created here
        shape->draw();                  // used via interface
    }

    virtual ~ShapeCreator() = default;
};

/* =========================================================
   4. Concrete Creators – override factoryMethod() to decide
      which concrete product to instantiate.
   ---------------------------------------------------------*/
class CircleCreator : public ShapeCreator {
public:
    std::unique_ptr<Shape> factoryMethod() const override {
        return std::make_unique<Circle>();
    }
};

class SquareCreator : public ShapeCreator {
public:
    std::unique_ptr<Shape> factoryMethod() const override {
        return std::make_unique<Square>();
    }
};

/* =========================================================
   Client code – works **only with the Creator interface**.
   It does not know or care which concrete product it gets.
   ---------------------------------------------------------*/
int main() {
    std::unique_ptr<ShapeCreator> creator;

    // Decide at runtime (could be based on config, user input, etc.)
    std::string choice = "circle";

    if (choice == "circle")  creator = std::make_unique<CircleCreator>();
    else                     creator = std::make_unique<SquareCreator>();

    // Draw via the factory-supplied object
    creator->drawShape();
}

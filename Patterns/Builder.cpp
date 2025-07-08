/*
 ----------------------------------------------------------------------------
  BUILDER PATTERN – QUICK RECAP
  ----------------------------------------------------------------------------
  • Intent            : Separate the construction of a complex object from
                        its representation, so the same construction process
                        can create different representations.
  • Typical Use Cases :
        – Creating immutable objects with many optional fields (e.g., HTTP
          requests, database queries, DTOs)
        – Building hierarchical structures (e.g., XML, JSON)
        – UI or game level creation where step order matters
  • Roles
        1. Product               – the complex object being built
        2. Builder (interface)   – declares build steps
        3. ConcreteBuilder       – implements the steps + returns the product
        4. Director (optional)   – orchestrates standard building sequences
 ----------------------------------------------------------------------------
*/

#include <iostream>
#include <memory>
#include <string>

/* =========================================================
   1. Product – the “complex” object.
   ---------------------------------------------------------*/
class Car {
public:
    std::string engine;
    std::string color;
    bool        hasGPS   = false;
    bool        hasAudio = false;

    void specs() const {
        std::cout << "Car specs:\n"
                  << "  Engine : " << engine << '\n'
                  << "  Color  : " << color  << '\n'
                  << "  GPS    : " << (hasGPS   ? "Yes" : "No") << '\n'
                  << "  Audio  : " << (hasAudio ? "Yes" : "No") << '\n';
    }
};

/* =========================================================
   2. Builder – defines the fluent API for setting parts.
   ---------------------------------------------------------
   We return *this to chain calls (“fluent interface”).
   build() hands the fully-constructed product back to the
   caller, usually via std::unique_ptr or by value.
   ---------------------------------------------------------*/
class CarBuilder {
private:
    // Hold a working copy; starts with sensible defaults
    std::unique_ptr<Car> car = std::make_unique<Car>();

public:
    CarBuilder& setEngine(const std::string& type) {
        car->engine = type;
        return *this;
    }
    CarBuilder& setColor(const std::string& c) {
        car->color = c;
        return *this;
    }
    CarBuilder& addGPS() {
        car->hasGPS = true;
        return *this;
    }
    CarBuilder& addAudio() {
        car->hasAudio = true;
        return *this;
    }

    // ***Final step*** – give away ownership of the product.
    // Could also return by value if Car is small/cheap to copy.
    std::unique_ptr<Car> build() {
        return std::move(car);
    }
};

/* =========================================================
   3. (Optional) Director – supplies canned build recipes.
   ---------------------------------------------------------
   Useful when you have standard variants (e.g., “Sports Car”,
   “City Car”) that clients can request without knowing steps.
   ---------------------------------------------------------*/
class CarDirector {
public:
    static std::unique_ptr<Car> makeSportsCar() {
        return CarBuilder()
                .setEngine("V8")
                .setColor("Red")
                .addGPS()
                .addAudio()
                .build();
    }

    static std::unique_ptr<Car> makeEconomyCar() {
        return CarBuilder()
                .setEngine("Inline-4")
                .setColor("White")
                .build();               // no extras
    }
};

/* =========================================================
   Client code – chooses either the fluent builder directly
   or one of the Director’s predefined recipes.
   ---------------------------------------------------------*/
int main() {
    // 1️⃣  Build step-by-step (fluent interface)
    auto custom = CarBuilder()
                    .setEngine("Electric")
                    .setColor ("Midnight Black")
                    .addGPS()
                    .build();
    custom->specs();
    std::cout << '\n';

    // 2️⃣  Get a ready-made “Sports Car” via Director
    auto sports = CarDirector::makeSportsCar();
    sports->specs();
}

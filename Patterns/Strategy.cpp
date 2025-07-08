/*
 ----------------------------------------------------------------------------
  STRATEGY PATTERN – QUICK RECAP
  ----------------------------------------------------------------------------
  • Intent            : Encapsulate a family of algorithms, make them
                        interchangeable, and let the client choose one
                        at runtime without changing the code that uses it.
  • Typical Use Cases :
        – Sorting (choose QuickSort, MergeSort, InsertionSort)
        – Compression (ZIP, RAR, 7z)
        – Payment methods (Credit-Card, UPI, PayPal, Crypto)
        – Path-finding (Dijkstra, A*, BFS) in games/GPS
  • Roles
        1. Strategy (interface)          – declares a single algorithm API
        2. ConcreteStrategy              – each implements the API
        3. Context                       – owns a Strategy pointer and
                                           delegates the work to it
 ----------------------------------------------------------------------------
*/

#include <iostream>
#include <memory>
#include <string>

/* =========================================================
   1. Strategy – the algorithm interface.
   ---------------------------------------------------------*/
class PaymentStrategy {
public:
    virtual void pay(double amount) const = 0;
    virtual ~PaymentStrategy() = default;
};

/* =========================================================
   2. Concrete Strategies – different algorithms.
   ---------------------------------------------------------*/
class CreditCardStrategy : public PaymentStrategy {
    std::string cardNumber;
public:
    explicit CreditCardStrategy(std::string num) : cardNumber(std::move(num)) {}
    void pay(double amount) const override {
        std::cout << "Paid ₹" << amount << " using Credit Card " << cardNumber << '\n';
    }
};

class UPIStrategy : public PaymentStrategy {
    std::string upiId;
public:
    explicit UPIStrategy(std::string id) : upiId(std::move(id)) {}
    void pay(double amount) const override {
        std::cout << "Paid ₹" << amount << " via UPI (" << upiId << ")\n";
    }
};

class CryptoStrategy : public PaymentStrategy {
    std::string wallet;
public:
    explicit CryptoStrategy(std::string addr) : wallet(std::move(addr)) {}
    void pay(double amount) const override {
        std::cout << "Paid ₹" << amount << " with crypto wallet " << wallet << '\n';
    }
};

/* =========================================================
   3. Context – holds a Strategy and delegates calls.
   ---------------------------------------------------------
   It’s completely agnostic about *which* algorithm it uses.
   Clients can swap strategies on the fly via setStrategy().
   ---------------------------------------------------------*/
class PaymentContext {
    std::unique_ptr<PaymentStrategy> strategy;
public:
    explicit PaymentContext(std::unique_ptr<PaymentStrategy> s)
        : strategy(std::move(s)) {}

    void setStrategy(std::unique_ptr<PaymentStrategy> s) {
        strategy = std::move(s);
    }
    void checkout(double amount) const {
        strategy->pay(amount);  // delegate to current algorithm
    }
};

/* =========================================================
   Client code – chooses strategies at runtime.
   ---------------------------------------------------------*/
int main() {
    PaymentContext ctx(std::make_unique<CreditCardStrategy>("1234-5678-9012-3456"));
    ctx.checkout(2500.0);               // pay by card

    ctx.setStrategy(std::make_unique<UPIStrategy>("revanth@upi"));
    ctx.checkout(1800.0);               // now pay via UPI

    ctx.setStrategy(std::make_unique<CryptoStrategy>("0xABCDEF4321"));
    ctx.checkout(5000.0);               // pay in crypto
}

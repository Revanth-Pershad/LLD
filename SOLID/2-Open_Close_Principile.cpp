/*
    Any class should be able to add more functionaliy but should not be modified
*/

#include <iostream>

using namespace std;

class PaymentProcessor {
public:
    void processPayment(std::string paymentType) {
        if (paymentType == "CreditCard") {
            // Process credit card payment
        } else if (paymentType == "PayPal") {
            // Process PayPal payment
        } 
    }
};

interface Payment {
public:
    void process() = 0;
};

class CreditCardPayment : public Payment {
public:
    void process() override {
        // Process credit card payment
    }
};

class PayPalPayment : public Payment {
public:
    void process() override {
        // Process PayPal payment
    }
};

class PaymentProcessor {
public:
    void processPayment(Payment* payment) {
        payment->process();
    }
};
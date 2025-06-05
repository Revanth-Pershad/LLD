/*
    Each class should only focus on one functionality
*/

#include <iostream>

using namespace std;

// Bad Use
class Invoice{
    int calcPrice();
    int savetoDb();
    int printInvoice();
};

// Better divide in 3 classes
class Bill{
    int calcPrice();
};

class PrintData{
    void printVoice();
};

class SaveData{
    void saveToDb(Bill b);
};

// Dividing it into 3 classes keep it more easy to extent the data
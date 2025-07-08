/*
    The adapter serves as the middle man to call external service for the client code: 
    It’s main duty is simply relaying the service request and pass in the result, 
    but it doesn’t do any of the heavy lifting. Think of a translator translating a conversation between 
    an English speaking and a Chinese speaking person.
*/

#include <iostream>

using namespace std;

// Bad Example
class DataStorage {
public: 
    int data;
};

class USB : DataStorage {
public:
    USB(int data) {
        data_ = num;
    }

    int USB_Transmit() {
        std::cout << "Transmit data from USB Device" << std::endl;
        return data_;
    }
};

class SDCard: DataStorage {
public: 
    SDCard(int data) {
        data_ = data;
    }

    int SDCard_Transmit() {
        std::cout << "Transmit data from SDCard Device" << std::endl;
        return data_;
    }
};

int main() {
    DataReader reader;
    
    USB* usb = new USB(5);
    reader.ReadDataFromStorage(usb);

    SDCard* sdcard = new SDCard(10);
    reader.ReadDataFromStorage(sdcard); // error due to incompatible Interface

    return 0;
}

/*
    Thus as we can see above we need to create an adapter for DataReader class 
    that implements the USB* interface methods that are read by the DataReader class 
*/

class SDCard_USB_Adapter : public USB {
private:
    SDCard* sdcard;
public:
    SDCard_USB_Adapter(SDCard* sdcard) : USB(-1) {
        this->sdcard = sdcard;
    }
    int USB_Transmit() override {
        return sdcard->SDCard_Transmit();
    };
};
/*
    Make sure to implement all the methods of the interface in the Adapter
    The adapter should delegate most of the real work to the service reference stored, 
    and handling only the interface or data format conversion. 
    In the overridden USB_Transmit() method, it’s simply invoking a call to the SDCard method.
*/

int main() {
    DataReader reader;
    SDCard* sdcard = new SDCard(10);
    USB* adapter = new SDCard_USB_Adapter(sdcard);
    reader.ReadDataFromStorage(adapter); 

    return 0;
}

/*
    For the Client, it doesn’t know that the adapter is passed into its read function, 
    ReadDataFromStorage (other than the fact that the adapter is named “adapter”). 
    The read function treats the passed in object just as a normal USB pointer.
*/
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

/*
    Required Flows:
        - Find the closest Spot for the Vehicle
        - Park the Vehicle & Mark the Spot Occupied
        - Exit the Vehicle and free Up the Space
        - Calculate the price and Time

    Components:
        - Ticket
            - Stores the information of the Parking
        
        - Vehicle
            - Bike, Car, Bus

        - Parking (Multi Floor)
            - Each Floor has a Row
*/


/*
    - Entry Time
    - Vehicle Number
    - Space Occupied
*/
class Vehicle {
protected:
    string VehicleNumber;
    int spaceReq, cost;
public:
    virtual int getSpace() {
        return spaceReq;
    }

    virtual string getVehicleNum() {
        return VehicleNumber;
    }

    virtual int getCost() {
        return cost;
    }

    virtual ~Vehicle() = default;
};

class Bike : public Vehicle {
public:
    Bike(string vehNum) {
        VehicleNumber = vehNum;
        spaceReq = 1;
        cost = 1;
    }
};

class Car : public Vehicle {
public:
    Car(string vehNum) {
        VehicleNumber = vehNum;
        spaceReq = 2;
        cost = 2;
    }
};

class Bus : public Vehicle {
public:
    Bus(string vehNum) {
        VehicleNumber = vehNum;
        spaceReq = 4;
        cost = 4;
    }
};

class Ticket{
    int id;
    string plate;
    int floor;
    int startSpot;
    int length;
    chrono::time_point<chrono::system_clock> entryTime;
    int costPerMin; 
    public:
        Ticket(
            int id_,
            string plate_,
            int floor_,
            int startSpot_,
            int length_,
            int costPerMin_
        ){
            id = id_;
            plate = plate_;
            floor = floor_;
            startSpot = startSpot_;
            length = length_;
            entryTime = chrono::system_clock::now();
            costPerMin = costPerMin_;
        }

        int getCost(){
            auto duration = chrono::system_clock::now() - entryTime;
            int mins = chrono::duration_cast<chrono::minutes>(duration).count();

            return mins * costPerMin;
        }

        int getId(){ return id; }
        int getFloor(){ return floor; }
        int getSpot(){ return startSpot; }
        int getLen(){ return length; }
};

class ParkingLot {
    int floors, spots;
    vector<vector<string>> parkingMap;
    unordered_map<string, Ticket*> number_mapping;
    unordered_map<int, Ticket*> ticket_mapping;
    int nextId;

public:
    ParkingLot(int flr, int spts) {
        floors = flr;
        spots = spts;
        parkingMap.resize(floors, vector<string>(spots, "#"));
        nextId = 1;
    }

    /*
        Enter a Vehicle
        Return the String in form : "Vehicle Parked! Ticket Id - <tid>"
    */
    string EnterVehicle(Vehicle &vh) {
        int need = vh.getSpace();
        int atFloor = -1, atSpot = -1;

        for(int i = 0; i < floors; i++){
            int curr = 0;
            for(int j = 0; j < spots; j++){
                if(parkingMap[i][j] == "#")curr++;
                else curr = 0;

                if(curr == need){
                    atFloor = i;
                    atSpot = j;
                    break;
                }
            }
            if(atFloor != -1)break;
        }

        if (atFloor == -1)
            return "No Spot Available!";

        int first = atSpot - need + 1;

        for (int s = first; s < first + need; ++s)
            parkingMap[atFloor][s] = vh.getVehicleNum();

        Ticket* temp_tk = new Ticket(
            nextId++, vh.getVehicleNum(),
            atFloor, first, need, vh.getCost());

        number_mapping[vh.getVehicleNum()] = temp_tk;
        ticket_mapping[temp_tk->getId()] = temp_tk;

        return "Vehicle Parked! Ticket Id - " + to_string(temp_tk->getId());
    }

    /*
        Exit the Vehicle
        Frees the spots and calculates the price.
    */
    string ExitVehicle(string vehNum) {
        auto it = number_mapping.find(vehNum);
        if (it == number_mapping.end()) return "Vehicle Not Found";

        Ticket *tk = it->second;

        int first = tk->getSpot();
        for (int s = first; s < first + tk->getLen(); ++s)
            parkingMap[tk->getFloor()][s] = "#";

        int price = tk->getCost();

        ticket_mapping.erase(tk->getId());
        number_mapping.erase(it);
        delete tk;

        return "Vehicle " + vehNum + " exited. Price to pay: " + to_string(price);
    }

    void display() {
        cout << "\nParking Lot Status \n";
        for (int i = 0; i < floors; i++) {
            cout << "Floor " << i << ": ";
            for (int j = 0; j < spots; j++) {
                cout << parkingMap[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    ParkingLot pl(2, 6);

    Bike b1("B123");
    Car c1("C456");
    Bus bus1("BUS789");
    Bus bus2("BUS235");

    cout << pl.EnterVehicle(b1) << endl;
    pl.display();

    cout << pl.EnterVehicle(c1) << endl;
    pl.display();

    cout << pl.EnterVehicle(bus1) << endl;
    pl.display();

    cout << pl.EnterVehicle(bus2) << endl;

    cout << pl.ExitVehicle("C456") << endl;
    pl.display();

    cout << pl.ExitVehicle("B123") << endl;
    pl.display();
}
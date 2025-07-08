/*
    This is an Publisher-Consumer Pattern ie one class publishes events and multiple subscribers consume the event

    The different types of classes are -
        - Observer Interface : This is needed since we want to make sure the class that observers our Publisher implements what 
         what to do on recieving the event
        
        - Observer Concrete Class : The actual consumer of the Event
        - Subject/Publisher : Class that maintains a set of observers to send the event

        Optional:
            - Event : It is the data structure that implements the event & its corresponding payload
*/

#include <bits/stdc++.h>

using namespace std;

class ObserverInterface{
    public:
        virtual void update(string event) = 0; // Enforces that this method is implemented in the child classes
};

class ObserverConcrete : public ObserverInterface{
    public:
        void update(string event){ // Now has more freedom to implement this however they want
            cout << "Event Recieved : " << event << endl;
        }
};

class Publisher{
    unordered_set<ObserverInterface *> st; // Makes it More Extensable
    public:
        void publish(string event){
            for(auto x : st)
                x->update(event);
        }

        void addObserver(ObserverInterface *obs){
            st.insert(obs);
        }

        void rmvObserver(ObserverInterface *obs){
            st.erase(st.find(obs));
        }
};

int main(){
    Publisher pb = Publisher();
    ObserverConcrete *obs1 = new ObserverConcrete();
    ObserverConcrete *obs2 = new ObserverConcrete();

    pb.addObserver(obs1);
    pb.addObserver(obs2);

    pb.publish("Event 1");
    pb.rmvObserver(obs2);

    pb.publish("Event 2");
}
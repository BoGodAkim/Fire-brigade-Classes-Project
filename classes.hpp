#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <bits/stdc++.h>

using std::queue;
using std::string;
using std::vector;
class FireBrigade;

class FireStation
{
private:
    string name;                       // name of the fire station
    string address;                    // address of the fire station
    string phone;                      // phone number of the fire station
    vector<FireBrigade> fire_brigades; // vector of fire brigades
    int free_fire_brigades;            // number of free fire brigades
    queue<Call> calls;                 // queue of calls
    void add_fire_brigade();           // add a fire brigade with parameters from the duty manager
    void remove_fire_brigade();        // Function which call FireBrigade* chooseFireBrigade() and delete the fire brigade
    void manage_fire_brigade();        // Function which call FireBrigade* chooseFireBrigade() and call FireBrigade::enter_menu()
    void print_fire_brigades();        // Function which print all fire brigades in the vector
    void print_calls();                // Function which print all calls in the queue
    void add_call();                   // Function add a call to the queue with parameters from the duty manager
    void remove_call();                // Function which call Call* chooseCall() and delete the call
    void send_brigades();              // Function which call Call* chooseCall() and FireBrigade* chooseFireBrigade() and call FireBrigade::send_brigade(Call) and Call::add_fire_brigade(FireBrigade)
    FireBrigade *choose_brigade();     // Function which call print_fire_brigades() and ask the duty manager to choose a fire brigade
    Call *choose_call();               // Function which call print_calls() and ask the duty manager to choose a call

public:
    FireStation();     // Constructor
    void enter_menu(); // Function which ask the duty manager to choose an option and call the function which correspond to the option
};

class FireBrigade
{
private:
    vector<FireTruck> truck;       // vector of fire trucks
    vector<Person> personal;       // vector of persons
    Call *call = nullptr;          // pointer to the call which the fire brigade is assigned to
    void add_truck();              // add a fire truck with parameters from the duty manager
    void remove_truck();           // Function which call FireTruck* chooseTruck() and delete the fire truck
    void add_person();             // add a person with parameters from the duty manager
    void remove_person();          // Function which call Person* choosePerson() and delete the person
    void manage_trucks();          // Function which call FireTruck* chooseTruck() and call FireTruck::update_truck_data()
    void manage_personal();        // Function which call Person* choosePerson() and call Person::update_person_data()
    FireTruck *choose_truck();     // Function which call print_trucks() and ask the duty manager to choose a fire truck
    Person *choose_person();       // Function which call print_personal() and ask the duty manager to choose a person
    void print_trucks();           // Function which print all fire trucks in the vector
    void print_personal();         // Function which print all persons in the vector
    void print_call();             // Function which print the call which the fire brigade is assigned to
    void return_to_station();      // Function which return the fire brigade to the fire station
    void send_brigade(Call *call); // Function which send the fire brigade to the call

public:
    FireBrigade();     // Constructor
    void enter_menu(); // Function which ask the duty manager to choose an option and call the function which correspond to the option
};

class Person
{
private:
    string name;            // name of the person
    string surname;         // surname of the person
    string phone;           // phone number of the person
    string address;         // address of the person
    string email;           // email of the person
    string birth_date;      // birth date of the person
    string passport_number; // passport number of the person

public:
    Person();                                                                                                                   // Constructor
    Person(string name, string surname, string phone, string address, string email, string birth_date, string passport_number); // Constructor with parameters
    void update_person_data();                                                                                                  // Function which ask the duty manager to update the person data
    void print_person_data();                                                                                                   // Function which print the person data
};

class FireTruck
{
private:
    string model; // model of the fire truck
    int number;   // number of the fire truck
    int year;     // year of the fire truck
    string VIN;   // VIN of the fire truck
    int mileage;  // mileage of the fire truck

public:
    FireTruck();                                                            // Constructor
    FireTruck(string model, int number, int year, string VIN, int mileage); // Constructor with parameters
    void update_truck_data();                                               // Function which ask the duty manager to update the fire truck data
    void print_truck_data();                                                // Function which print the fire truck data
};

class Call
{
private:
    string address;                     // address of the call
    string type;                        // type of fire
    int priority;                       // priority of the call
    vector<FireBrigade *> fireBrigades; // vector of fire brigades which are assigned to the call

public:
    Call();                                          // Constructor
    ~Call();                                         // Destructor
    Call(string address, string type, int priority); // Constructor with parameters
    void add_fire_brigade(FireBrigade *fireBrigade); // Function which add a fire brigade which is assigned to the call
    void remove_fire_brigade();                      // Function which delete the fire brigade which is assigned to the call and call FireBrigade::return_to_station()
    FireBrigade *choose_fire_brigade();              // Function which call print_fire_brigades() and ask the duty manager to choose a fire brigade
    void print_fire_brigades();                      // Function which print all fire brigades which are assigned to the call
    void print_call();                               // Function which print the call
};

#endif // CLASSES_HPP
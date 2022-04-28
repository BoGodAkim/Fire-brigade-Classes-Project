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
    vector<FireBrigade> fire_brigades;
    int free_fire_brigades;
    queue<Call> calls;
    void add_fire_brigade();
    void remove_fire_brigade();
    void manage_fire_brigades();
    void print_fire_brigades();
    void print_calls();
    void add_call();
    void remove_call();
    void send_brigades();
    FireBrigade *choose_brigade();
    Call *choose_call();
public:
    void enter_menu();
};

class FireBrigade
{
private:
    vector<FireTruck> truck;
    vector<Person> personal;
    Call *call=nullptr;
    void add_truck();
    void remove_truck();
    void add_person();
    void remove_person();
    void manage_trucks();
    void manage_personal();
    FireTruck *choose_truck();
    Person *choose_person();
    void print_trucks();
    void print_personal();
    void print_call();
    void return_to_station();
    void send_brigade(Call *call);
public:
    void enter_menu();
};

class Person
{
private:
    string name;
    string surname;
    string phone;
    string address;
    string email;
    string birth_date;
    string passport_number;
public:
    Person();
    Person(string name, string surname, string phone, string address, string email, string birth_date, string passport_number);
    void update_person_data();
    void print_person_data();
};

class FireTruck
{
private:
    string model;
    int number;
    int year;
    string VIN;
    int mileage;
public:
    FireTruck();
    FireTruck(string model, int number, int year, string VIN, int mileage);
    void update_truck_data();
    void print_truck_data();
};

class Call
{
private:
    string address;
    vector<FireBrigade *> fireBrigades;
public:
    Call();
    Call(string address);
    void add_fire_brigade(FireBrigade *fireBrigade);
    void remove_fire_brigade();
    FireBrigade *choose_fire_brigade();
    void print_fire_brigades();
    void print_call();
};

#endif // CLASSES_HPP
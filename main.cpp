#include <bits/stdc++.h>
#include "classes.hpp"
using namespace std;

FireStation::FireStation()
{
    cout << "Enter the name of the fire station: ";
    getline(cin, name);
    cout << "Enter the address of the fire station: ";
    getline(cin, address);
    cout << "Enter the phone number of the fire station: ";
    getline(cin, phone);
    free_fire_brigades = 0;
    enter_menu();
}

void FireStation::enter_menu()
{
    int option;
    while (true)
    {
        cout << "Fire station menu:\n";
        cout << "1. Add a fire brigade\n";
        cout << "2. Remove a fire brigade\n";
        cout << "3. Manage a fire brigade\n";
        cout << "4. Print fire brigades\n";
        cout << "5. Add a call\n";
        cout << "6. Remove a call\n";
        cout << "7. Send brigades\n";
        cout << "8. Print calls\n";
        cout << "0. Return to the main menu\n";
        cout << "Enter your option: ";
        cin >> option;
        cin.ignore();
        switch (option)
        {
        case 1:
            add_fire_brigade();
            break;
        case 2:
            remove_fire_brigade();
            break;
        case 3:
            manage_fire_brigade();
            break;
        case 4:
            print_fire_brigades();
            break;
        case 5:
            add_call();
            break;
        case 6:
            remove_call();
            break;
        case 7:
            send_brigades();
            break;
        case 8:
            print_calls();
            break;
        case 0:
            return;
        default:
            cout << "Invalid option. Try again.\n";
            break;
        }
    }
}

void FireStation::add_fire_brigade()
{
    string name;
    cout << "Enter the name of the fire brigade: ";
    getline(cin, name);
    this->fire_brigades.push_back(FireBrigade(name));
    this->free_fire_brigades++;
    this->fire_brigades.back().enter_menu();
}

void FireStation::remove_fire_brigade()
{
    cout << "Choose the fire brigade to remove: ";
    print_free_fire_brigades();
    auto it_fire_brigade = this->choose_brigade();
    if (!it_fire_brigade->is_free())
    {
        cout << "The fire brigade is not free.\n";
        return;
    }
    this->fire_brigades.erase(it_fire_brigade);
    this->free_fire_brigades--;
}

void FireStation::manage_fire_brigade()
{
    cout << "Choose the fire brigade to manage: ";
    print_free_fire_brigades();
    auto it_fire_brigade = this->choose_brigade();
    if (!it_fire_brigade->is_free())
    {
        cout << "The fire brigade is not free.\n";
        return;
    }
    it_fire_brigade->enter_menu();
}

void FireStation::print_fire_brigades()
{
    cout << "Fire brigades:\n";
    int number = 1;
    for (auto it_fire_brigade : this->fire_brigades)
    {
        cout << endl
             << number << endl;
        it_fire_brigade.print_brigade();
        number++;
    }
}

void FireStation::print_free_fire_brigades()
{
    cout << "Free fire brigades:\n";
    int number = 1;
    for (auto it_fire_brigade : this->fire_brigades)
    {
        if (it_fire_brigade.is_free())
        {
            cout << endl
                 << number << endl;
            it_fire_brigade.print_brigade();
        }
        number++;
    }
}

void FireStation::add_call()
{
    string address;
    string type;
    int priority;
    cout << "Enter the address of the call: ";
    getline(cin, address);
    cout << "Enter the type of the call: ";
    getline(cin, type);
    cout << "Enter the priority of the call: ";
    cin >> priority;
    cin.ignore();
    this->calls.push_back(Call(address, type, priority));
}

void FireStation::remove_call()
{
    cout << "Choose the call to remove: ";
    auto it_call = this->choose_call();
    this->free_fire_brigades += it_call->number_of_fire_brigades();
    this->calls.erase(it_call);
}

void FireStation::send_brigades()
{
    if (this->free_fire_brigades == 0)
    {
        cout << "There are no free fire brigades.\n";
        return;
    }
    cout << "Choose the call to send brigades: ";
    auto it_call = this->choose_call();
    if (it_call == this->calls.end())
    {
        return;
    }
    this->print_free_fire_brigades();
    cout << "Choose number of brigades to send: ";
    int brigades_number;
    cin >> brigades_number;
    while (brigades_number > this->free_fire_brigades)
    {
        cout << "There are not enough free fire brigades.\n";
        cout << "Choose number of brigades to send: ";
        cin >> brigades_number;
    }
    cin.ignore();
    for (int i = 0; i < brigades_number; i++)
    {
        this->print_free_fire_brigades();
        auto it_fire_brigade = this->choose_brigade();
        while (!it_fire_brigade->is_free())
        {
            cout << "The fire brigade is not free.\n";
            cout << "Choose another fire brigade: ";
            it_fire_brigade = this->choose_brigade();
        }
        it_fire_brigade->send_brigade(&*it_call);
        it_call->add_fire_brigade(&*it_fire_brigade);
    }
    this->free_fire_brigades -= brigades_number;
}

void FireStation::print_calls()
{
    cout << "Calls:\n";
    int number = 1;
    for (auto it_call : this->calls)
    {
        cout << endl
             << number << endl;
        it_call.print_call();
        number++;
    }
}

list<FireBrigade>::iterator FireStation::choose_brigade()
{
    cout << "Choose the fire brigade:" << endl
         << "1. By name" << endl
         << "2. By number" << endl;
    int option;
    cin >> option;
    cin.ignore();
    string name;
    switch (option)
    {
    case 1:
        cout << "Enter the name of the fire brigade: ";
        getline(cin, name);
        for (auto it_fire_brigade = this->fire_brigades.begin(); it_fire_brigade != this->fire_brigades.end(); it_fire_brigade++)
        {
            if (it_fire_brigade->get_name() == name)
            {
                return it_fire_brigade;
            }
        }
        cout << "Fire brigade not found.\n";
        return this->choose_brigade();
    case 2:
        cout << "Enter the number of the fire brigade: ";
        int number;
        cin >> number;
        cin.ignore();
        if (number > this->fire_brigades.size() || number < 1)
        {
            cout << "Fire brigade not found.\n";
            return this->choose_brigade();
        }
        auto it_fire_brigade = this->fire_brigades.begin();
        advance(it_fire_brigade, number - 1);
        return it_fire_brigade;
    default:
        cout << "Invalid option. Try again.\n";
        return this->choose_brigade();
    }
}

list<Call>::iterator FireStation::choose_call()
{
    int index;
    cout << "Choose the call: ";
    cin >> index;
    cin.ignore();
    if (index > this->calls.size() || index < 1)
    {
        cout << "Call not found.\n";
        return this->choose_call();
    }
    auto it_call = this->calls.begin();
    advance(it_call, index - 1);
    return it_call;
}

FireBrigade::FireBrigade(string name)
{
    this->name = name;
}

bool FireBrigade::is_free()
{
    return this->call == nullptr;
}

void FireBrigade::send_brigade(Call *call)
{
    this->call = call;
}

string FireBrigade::get_name()
{
    return this->name;
}

void FireBrigade::print_brigade()
{
    cout << "Fire brigade: " << this->name << endl
         << "Number of trucks: " << this->trucks.size() << endl
         << "Number of firefighters: " << this->personal.size() << endl
         << "Is free: " << this->is_free() << endl;
}

void FireBrigade::add_truck()
{
    string model;
    string number;
    int year;
    string VIN;
    int mileage;
    cout << "Enter the model of the truck: ";
    getline(cin, model);
    cout << "Enter the number of the truck: ";
    getline(cin, number);
    cout << "Enter the year of the truck: ";
    cin >> year;
    cin.ignore();
    cout << "Enter the VIN of the truck: ";
    getline(cin, VIN);
    cout << "Enter the mileage of the truck: ";
    cin >> mileage;
    cin.ignore();
    this->trucks.push_back(FireTruck(model, number, year, VIN, mileage));
}

void FireBrigade::add_person()
{
    string name;
    string surname;
    string rank;
    string phone;
    string address;
    string email;
    string birth_date;
    string passport_number;
    cout << "Enter the name of the person: ";
    getline(cin, name);
    cout << "Enter the surname of the person: ";
    getline(cin, surname);
    cout << "Enter the rank of the person: ";
    getline(cin, rank);
    cout << "Enter the phone of the person: ";
    getline(cin, phone);
    cout << "Enter the address of the person: ";
    getline(cin, address);
    cout << "Enter the email of the person: ";
    getline(cin, email);
    cout << "Enter the birth date of the person: ";
    getline(cin, birth_date);
    cout << "Enter the passport number of the person: ";
    getline(cin, passport_number);
    this->personal.push_back(Person(name, surname, rank, phone, address, email, birth_date, passport_number));
}

void FireBrigade::print_trucks()
{
    cout << "Trucks:\n";
    int number = 1;
    for (auto it_truck : this->trucks)
    {
        cout << endl
             << number << endl;
        it_truck.print_truck_data();
        number++;
    }
}

void FireBrigade::print_personal()
{
    cout << "Personal:\n";
    int number = 1;
    for (auto it_person : this->personal)
    {
        cout << endl
             << number << endl;
        it_person.print_person_data();
        number++;
    }
}

void FireBrigade::remove_truck()
{
    this->print_trucks();
    auto it_truck = this->choose_truck();
    this->trucks.erase(it_truck);
}

void FireBrigade::remove_person()
{
    this->print_personal();
    auto it_person = this->choose_person();
    this->personal.erase(it_person);
}

void FireBrigade::print_call()
{
    if (this->call != nullptr)
    {
        cout << "Call:\n";
        this->call->print_call();
    }
    else
    {
        cout << "No call.\n";
    }
}

void FireBrigade::return_to_station()
{
    this->call = nullptr;
}

void FireBrigade::manage_truck()
{
    this->print_trucks();
    auto it_truck = this->choose_truck();
    int option;
    cout << "Choose the option: " << endl
         << "1. Update number" << endl
         << "2. Update mileage" << endl
         << "0. Back" << endl;
    cin >> option;
    cin.ignore();
    switch (option)
    {
    case 1:
        cout << "Enter the new number: ";
        getline(cin, it_truck->number);
        break;
    case 2:
        int mileage;
        cout << "Enter the new mileage: ";
        cin >> mileage;
        cin.ignore();
        while (mileage < it_truck->mileage)
        {
            cin >> mileage;
            cin.ignore();
            if (mileage < it_truck->mileage)
            {
                cout << "Mileage can't be less than the current mileage.\n";
            }
        }
        it_truck->mileage = mileage;
        break;
    case 0:
        break;
    default:
        cout << "Invalid option. Try again.\n";
        this->manage_truck();
    }
}

void FireBrigade::manage_person()
{
    this->print_personal();
    auto it_person = this->choose_person();
    int option;
    cout << "Choose the option: " << endl
         << "1. Update name" << endl
         << "2. Update surname" << endl
         << "3. Update rank" << endl
         << "4. Update phone" << endl
         << "5. Update address" << endl
         << "6. Update email" << endl
         << "7. Update birth date" << endl
         << "8. Update passport number" << endl
         << "0. Back" << endl;
    cin >> option;
    cin.ignore();
    switch (option)
    {
    case 1:
        cout << "Enter the new name: ";
        getline(cin, it_person->name);
        break;
    case 2:
        cout << "Enter the new surname: ";
        getline(cin, it_person->surname);
        break;
    case 3:
        cout << "Enter the new rank: ";
        getline(cin, it_person->rank);
        break;
    case 4:
        cout << "Enter the new phone: ";
        getline(cin, it_person->phone);
        break;
    case 5:
        cout << "Enter the new address: ";
        getline(cin, it_person->address);
        break;
    case 6:
        cout << "Enter the new email: ";
        getline(cin, it_person->email);
        break;
    case 7:
        cout << "Enter the new birth date: ";
        getline(cin, it_person->birth_date);
        break;
    case 8:
        cout << "Enter the new passport number: ";
        getline(cin, it_person->passport_number);
        break;
    case 0:
        break;
    default:
        cout << "Invalid option. Try again.\n";
        this->manage_person();
    }
}

list<FireTruck>::iterator FireBrigade::choose_truck()
{
    int number;
    cout << "Enter the number of the truck: ";
    cin >> number;
    cin.ignore();
    while (number < 1 || number > this->trucks.size())
    {
        cout << "Wrong number.\n";
        cout << "Enter the number of the truck: ";
        cin >> number;
        cin.ignore();
    }
    auto it_truck = this->trucks.begin();
    advance(it_truck, number - 1);
    return it_truck;
}

void FireBrigade::enter_menu()
{
    int option;
    cout << "Choose the option: " << endl
         << "1. Add truck" << endl
         << "2. Add person" << endl
         << "3. Remove truck" << endl
         << "4. Remove person" << endl
         << "5. Manage truck" << endl
         << "6. Manage person" << endl
         << "7. Print trucks" << endl
         << "8. Print personal" << endl
         << "9. Print call" << endl
         << "10. Return to station" << endl
         << "0. Exit" << endl;
    cin >> option;
    cin.ignore();

        switch (option)
        {
        case 1:
            this->add_truck();
            break;
        case 2:
            this->add_person();
            break;
        case 3:
            this->remove_truck();
            break;
        case 4:
            this->remove_person();
            break;
        case 5:
            this->manage_truck();
            break;
        case 6:
            this->manage_person();
            break;
        case 7:
            this->print_trucks();
            break;
        case 8:
            this->print_personal();
            break;
        case 9:
            this->print_call();
            break;
        case 10:
            this->return_to_station();
            break;
        case 0:
            break;
        default:
            cout << "Wrong option.\n";
            this->enter_menu();
            break;
        }
}

Person::Person(string name, string surname, string rank, string phone, string address, string email, string birth_date, string passport_number)
{
    this->name = name;
    this->surname = surname;
    this->rank = rank;
    this->phone = phone;
    this->address = address;
    this->email = email;
    this->birth_date = birth_date;
    this->passport_number = passport_number;
}

void Person::print_person_data()
{
    cout << "Name: " << this->name << endl
         << "Surname: " << this->surname << endl
         << "Rank: " << this->rank << endl
         << "Phone: " << this->phone << endl
         << "Address: " << this->address << endl
         << "Email: " << this->email << endl
         << "Birth date: " << this->birth_date << endl
         << "Passport number: " << this->passport_number << endl;
}

FireTruck::FireTruck(string model, string number, int year, string VIN, int mileage)
{
    this->model = model;
    this->year = year;
    this->VIN = VIN;
    this->number = number;
    this->mileage = mileage;
}

void FireTruck::print_truck_data()
{
    cout << "Model: " << this->model << endl
         << "Year: " << this->year << endl
         << "VIN: " << this->VIN << endl
         << "Number: " << this->number << endl
         << "Mileage: " << this->mileage << endl;
}

Call::Call(string address, string type, int priority)
{
    this->address = address;
    this->type = type;
    this->priority = priority;
}

void Call::print_call()
{
    cout << "Address: " << this->address << endl
         << "Type: " << this->type << endl
         << "Priority: " << this->priority << endl;
}

int Call::number_of_fire_brigades()
{
    return fireBrigades.size();
}

void Call::print_fire_brigades()
{
    for(auto it_fire_brigade : this->fireBrigades)
    {
        it_fire_brigade->print_brigade();
    }
}

void Call::add_fire_brigade(FireBrigade *fire_brigade)
{
    this->fireBrigades.push_back(fire_brigade);
}

void Call::remove_fire_brigades()
{
    for(auto it_fire_brigade : this->fireBrigades)
    {
        it_fire_brigade->return_to_station();
    }
    this->fireBrigades.clear();
}

Call::~Call()
{
    this->remove_fire_brigades();
}
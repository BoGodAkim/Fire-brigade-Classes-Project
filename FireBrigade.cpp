#include "classes.hpp"

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
    if (this->trucks.size() == 0)
    {
        cout << "No trucks to remove.\n";
        return;
    }
    this->print_trucks();
    auto it_truck = this->choose_truck();
    this->trucks.erase(it_truck);
}

void FireBrigade::remove_person()
{
    if (this->personal.size() == 0)
    {
        cout << "No persones to remove.\n";
        return;
    }
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
    if (this->trucks.size() == 0)
    {
        cout << "No trucks to manage.\n";
        return;
    }
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
            cout << "Mileage can't be less than the current mileage." << endl
                 << "Enter the new mileage: ";
            cin >> mileage;
            cin.ignore();
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
    if (this->personal.size() == 0)
    {
        cout << "No persones to manage.\n";
        return;
    }
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

list<Person>::iterator FireBrigade::choose_person()
{
    int number;
    cout << "Enter the number of the person: ";
    cin >> number;
    cin.ignore();
    while (number < 1 || number > this->personal.size())
    {
        cout << "Wrong number.\n";
        cout << "Enter the number of the person: ";
        cin >> number;
        cin.ignore();
    }
    auto it_person = this->personal.begin();
    advance(it_person, number - 1);
    return it_person;
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
        this->enter_menu();
        break;
    case 2:
        this->add_person();
        this->enter_menu();
        break;
    case 3:
        this->remove_truck();
        this->enter_menu();
        break;
    case 4:
        this->remove_person();
        this->enter_menu();
        break;
    case 5:
        this->manage_truck();
        this->enter_menu();
        break;
    case 6:
        this->manage_person();
        this->enter_menu();
        break;
    case 7:
        this->print_trucks();
        this->enter_menu();
        break;
    case 8:
        this->print_personal();
        this->enter_menu();
        break;
    case 9:
        this->print_call();
        this->enter_menu();
        break;
    case 10:
        this->return_to_station();
        this->enter_menu();
        break;
    case 0:
        break;
    default:
        cout << "Wrong option.\n";
        this->enter_menu();
        break;
    }
}
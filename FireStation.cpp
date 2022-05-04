#include "classes.hpp"

FireStation::FireStation()
{
    cout << "Enter the name of the fire station: ";
    getline(cin, name);
    cout << "Enter the address of the fire station: ";
    getline(cin, address);
    cout << "Enter the phone number of the fire station: ";
    getline(cin, phone);
    free_fire_brigades = 0;
    this->enter_menu();
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
    if (this->free_fire_brigades == 0)
    {
        cout << "There are no free fire brigades.\n";
        return;
    }
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
    if (this->free_fire_brigades == 0)
    {
        cout << "There are no free fire brigades.\n";
        return;
    }
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
    if (this->calls.size() == 0)
    {
        cout << "There are no calls.\n";
        return;
    }
    cout << "Choose the call to remove: ";
    this->print_calls();
    auto it_call = this->choose_call();
    this->free_fire_brigades += it_call->number_of_fire_brigades();
    it_call->remove_fire_brigades();
    this->calls.erase(it_call);
}

void FireStation::send_brigades()
{
    if (this->calls.size() == 0)
    {
        cout << "There are no calls.\n";
        return;
    }
    if (this->free_fire_brigades == 0)
    {
        cout << "There are no free fire brigades." << this->free_fire_brigades << endl;
        return;
    }
    cout << "Choose the call to send brigades: ";
    this->print_calls();
    auto it_call = this->choose_call();
    this->print_free_fire_brigades();
    cout << "Choose number of brigades to send: ";
    int brigades_number;
    cin >> brigades_number;
    while (brigades_number > this->free_fire_brigades || brigades_number < 0)
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
    {
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
    }
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

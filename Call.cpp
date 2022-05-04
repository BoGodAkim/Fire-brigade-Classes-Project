#include "classes.hpp"

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
         << "Priority: " << this->priority << endl
         << "Brigads assigned: " << this->number_of_fire_brigades() << endl;
}

int Call::number_of_fire_brigades()
{
    return fireBrigades.size();
}

void Call::print_fire_brigades()
{
    for (auto it_fire_brigade : this->fireBrigades)
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
    for (auto it_fire_brigade : this->fireBrigades)
    {
        it_fire_brigade->return_to_station();
    }
    this->fireBrigades.clear();
}
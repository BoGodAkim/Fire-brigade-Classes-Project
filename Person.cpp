#include "classes.hpp"

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
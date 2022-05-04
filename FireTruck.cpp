#include "classes.hpp"

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
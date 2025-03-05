/*
1. Imagine you are leading the development of a software system for a car rental agency.
   The system needs to manage various types of vehicles in the rental fleet, each with specific attributes and behaviors.
   Your task is to design and implement a C++ program that leverages inheritance to model these vehicles efficiently.
        (a)	Start by designing an abstract base class called 'Vehicle.'
            Define fundamental attributes that are common to all vehicles, such as 'make,' 'model,' and 'year.'
            Create a virtual function, 'calculateRentalCost,' which should be overridden in derived classes. (3 marks)
        (b)	Develop three derived classes: 'Car,' 'SUV,' and 'Truck.'
            Each derived class should inherit from the 'Vehicle' base class and introduce attributes and behaviors unique to their type.
            For example, 'Car' might have a 'numDoors' attribute, while 'Truck' may have a 'cargoCapacity' attribute. (3 marks)
*/

#include<iostream>
using namespace std;


class Vehicle {
    public:
        string make, model;
        int year;
    
        //A virtual function is a member function of a base class that can be overridden in a derived class.
        // It allows dynamic (runtime) polymorphism, i.e. the function that gets executed is determined at runtime based on the actual object type.
        virtual void calculateRentalCost(int days) = 0;    // Pure Virtual function declaration

        // Destructor for Vehicle class
        // After the programme runs successfully, run the destructor to clear memory
        // The ~Vehicle() destructor is called multiple times because each derived class (Car, SUV, Truck) calls the base class destructor (Vehicle's destructor) as part of its destruction process.
        virtual ~Vehicle() {
            // cout << "Vehicle Destructor Called!" << endl;
        }
};

// Derived class
// Car is a derived/child/sub class of the base/parent/super class Car
class Car : public Vehicle {

    private:
        int numDoors = 4;      // Number of doors the Car has

    public:
        // Constructor to initialize the car details
        // We overide the variable values in vehicle class if default values are placed
        Car() {
            make = "Toyota";
            model = "Corolla";
            year = 2020;
        }

       // Overriding the base class function to calculate rental cost based on number of doors for this class function
        void calculateRentalCost(int days) override {
            float costPerDay = 20.0f; // Cost per day for a car. f indicates the value is explicitly a float
            float totalCost = costPerDay * days * numDoors; // Number of doors affects cost
            cout << "Car Chosen! \nTotal Rental Cost: KES" << totalCost << " for " << days << " days." << endl;
            // cout << "Car Chosen!" << endl;
        }

        // Destructor for Car class
        // After the programme runs successfully, run the destructor to clear memory
        // The destructor for the derived class is called first, followed by the base class destructor. This ensures that all resources are properly released.
        ~Car() {
            // cout << "Car Destructor Called!" << endl;
        }
};


class SUV : public Vehicle {
    private:
     int peopleCapacity = 7;        // Number of people the SUV can carry

    public:
        // Constructor to initialize the SUV details
        // We overide the variable values in vehicle class if default values are placed
        SUV() {
            make = "Honda";
            model = "Pilot";
            year = 2022;
        }

        // Overriding the base class function to calculate rental cost based on number of people
        void calculateRentalCost(int days) override {
            float costPerDay = 30.0f; // Cost per day for an SUV.  f indicates the value is explicitly a float
            float totalCost = costPerDay * days * peopleCapacity; // Number of people affects cost
            cout << "SUV Chosen! \nTotal Rental Cost: KES" << totalCost << " for " << days << " days." << endl;
        }

        // Destructor for SUV class
        // After the programme runs successfully, run the destructor to clear memory
        // The destructor for the derived class is called first, followed by the base class destructor. This ensures that all resources are properly released.
        ~SUV() {
            // cout << "SUV Destructor Called!" << endl;
        }
};

class Truck : public Vehicle {    
    private:
     float cargoCapacity = 5000;   // Weight of the cargo the truck can carry in kilograms

    public:
        // Constructor to initialize the truck details
        // We overide the variable values in vehicle class if default values are placed
        Truck() {
            make = "Ford";
            model = "F-150";
            year = 2021;
        }

        // Overriding the base class function to calculate rental cost based on cargo capacity
        void calculateRentalCost(int days) override {
            float costPerDay = 50.0f; // Cost per day for a truck.  f indicates the value is explicitly a float
            float totalCost = costPerDay * days * cargoCapacity / 1000; // Cargo weight (in tons) affects cost
            cout << "Truck Chosen! \nTotal Rental Cost: KES" << totalCost << " for " << days << " days." << endl;
        }

        // Destructor for Truck class
        // After the programme runs successfully, run the destructor to clear memory
        // The destructor for the derived class is called first, followed by the base class destructor. This ensures that all resources are properly released.
        ~Truck() {
            // cout << "Truck Destructor Called!" << endl;
        }
};



int main() {
    // Create an object of the classes above
    Vehicle* baseVehicle;
    Car carObj;
    SUV suvObj;
    Truck truckObj;

    // Welcome message
    cout << "Welcome to Zetech Rental Information Management System (Zetech RIMS). \n" << endl;
    cout << "Which type of Vehicle would you like to Rent? \n" << endl;
    cout << "Type 1 for: \"Car\" \nType 2 for: \"SUV\" \nType 3 for: \"Truck\"" << endl;

    int vehicleChosen;
    int rentalDays;

    // Loop for valid vehicle choice
    // If user enters number other than 1, 2, or 3 keep looping
    while (true) {
        
        cin >> vehicleChosen;

        if (vehicleChosen == 1 || vehicleChosen == 2 || vehicleChosen == 3) {
            cout << "Please enter the number of days you want to rent the vehicle: ";
            cin >> rentalDays;      // Take rental days user enters after inputing the right number

            if (vehicleChosen == 1) { // Car Chosen
                carObj.calculateRentalCost(rentalDays);     // Overide the virtual function and calculate the total rental cost
                break;
            }
            else if (vehicleChosen == 2) { // SUV Chosen
                suvObj.calculateRentalCost(rentalDays);
                break;
            }
            else if (vehicleChosen == 3) { // Truck Chosen
                truckObj.calculateRentalCost(rentalDays);
                break;
            }
        } else { // Invalid input
            cout << vehicleChosen << " not recognized. Please follow the instructions above.\n" << endl;
        }
    }

    return 0;
}
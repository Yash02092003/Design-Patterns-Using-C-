#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Forward Declaration
class PersonBuilder;
class PersonJobBuilder;
class PersonAddressBuilder;

class Person {
    // address
    string street_address, post_code, city;
    string company_name, position;
    int annual_income;

    // Friend classes to allow them to modify Person's members
    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

public:
    // Static method to create a PersonBuilder
    static PersonBuilder create();
};

// Base class for building Person (using the builder pattern)
class PersonBuilderBase {
protected:
    Person& person; // Reference to the person object being built
public:
    PersonBuilderBase(Person& person) : person(person) {}

    // Method to start building the address part
    PersonAddressBuilder lives() const;

    // Method to start building the job part
    PersonJobBuilder works() const;
};

// PersonBuilder class (for chaining)
class PersonBuilder : public PersonBuilderBase {
    Person p; // Person object to be built
public:
    PersonBuilder() : PersonBuilderBase(p) {}
    
    // Convert PersonBuilder to a Person object when finished
    operator Person() {
        return move(p); // Transfer ownership of the person object
    }

    PersonAddressBuilder lives();// Start the address building
    PersonJobBuilder works();     // Start the job building
};

PersonBuilder Person::create() {
    return PersonBuilder();
}

// Address builder
class PersonAddressBuilder : public PersonBuilderBase {
    typedef PersonAddressBuilder Self;
public:
    PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

    // Methods to set address components
    Self& at(string street_address) {
        person.street_address = street_address;
        return *this;
    }

    Self& with_postcode(string post_code) {
        person.post_code = post_code;
        return *this;
    }

    Self& in(string city) {
        person.city = city;
        return *this;
    }
};

// Job builder
class PersonJobBuilder : public PersonBuilderBase {
    typedef PersonJobBuilder Self;
public:
    explicit PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

    // Methods to set job-related attributes
    Self& at(string company_name) {
        person.company_name = company_name;
        return *this;
    }

    Self& as_a(string position) {
        person.position = position;
        return *this;
    }

    Self& earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

// Method definitions for lives() and works()
PersonAddressBuilder PersonBuilder::lives() {
    return PersonAddressBuilder{person};  // Start building the address part
}

PersonJobBuilder PersonBuilder::works() {
    return PersonJobBuilder{person}; // Start building the job part
}

int main() {
    // Using the builder pattern to construct a Person object
    Person p = Person::create().lives()
        .at("123 London Road").with_postcode("SW1 1GB").in("London")
        .works().at("PragmaSoft").as_a("Consultant").earning(10e6);
    
    // Printing the final person data (for testing purpose)
    // Assuming you add print functions in the Person class.
    // cout << p;

    return 0;
}

#include <iostream>
#include <cmath>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace std;

class Address {
public:
    string street, city;
    int suite;

    Address() {}
    
    Address(const string &street, const string &city, int suite) 
        : street(street), city(city), suite(suite) {}

    Address(const Address &other) 
        : street(other.street), city(other.city), suite(other.suite) {}

    private:
        friend class boost::serialization::access;
        template<typename archive>
        void serialize(archive& ar , const unsigned version){
            ar & street;
            ar & city;
            ar & suite;
        }
};

class Contact {
public:
    string name;
    Address* address;

    Contact() {}

    Contact(const string &name, Address *address)
        : name(name), address(address) {}

    Contact(const Contact& other) : 
    name(other.name) , 
    address(new Address(other.address->street , other.address->city , other.address->suite)){

    }

    friend ostream& operator<<(ostream &os, const Contact &contact) {
        os << "Name : " << contact.name 
           << " Street : " << contact.address->street 
           << " City : " << contact.address->city 
           << " Suite : " << contact.address->suite;
        return os;
    }

    // Corrected copy constructor
    //Contact(const Contact &other)
        //: name(other.name), address(other.address) {}  // Directly use the Address copy constructor

    // Copy assignment operator
    Contact& operator=(const Contact& other) {
        if (this == &other) return *this;  // Self-assignment check
        name = other.name;
        address = other.address;  // Address copy assignment
        return *this;
    }
    private:
        friend class boost::serialization::access;
        template<typename archive>
        void serialize(archive& ar , const unsigned version){
            ar & name;
            ar & address;
        }
};

struct EmployeFactory{
    static unique_ptr<Contact> new_main_office_employee(const string& name , int suite){
       static Contact p ("" , new Address("123 East Dr", "London", 123));
       return new_employee(name , suite , p);
    }
    private:
        static unique_ptr<Contact> new_employee(const string& name , int suite , const Contact& prototype){
            auto result = make_unique<Contact>(prototype);
            result->name = name;
            result->address->suite = suite;
            return result;
        }
};

Contact global_contact("Global", new Address("123 East Dr", "London", 123));

int main() {
    Contact john("John Doe", new Address("123 East Dr", "London", 123));
    //Contact jane{"Jane Doe", Address("123 East Dr", "London", 123)};
    Contact jane(john);
    jane = john; // shallow copy
    jane.name = "Jane Smith";
    cout << john << endl << jane << endl;

    //Prototype Factory
    auto Doe = EmployeFactory::new_main_office_employee("Jane Doe" , 123);
    cout << *Doe << endl;

    auto clone = [](const Contact& c) {
        ostringstream oss;
        archive::text_oarchive oa(oss);
        oa << c;
        string s = oss.str();
        cout << s << endl;

        istringstream iss(s);
        archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    }

    auto jane_clone = clone(jane); 
    return 0;
}

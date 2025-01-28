#include <iostream>
#include <string>
using namespace std;
//pimpl implementation
class Person{
    public:
        string name;

        class PersonImpl{
            public: 
                void greet(Person* p){
                    cout<<"Hello"<<p->name<<"Good Morning"<<endl;
                }
        };

        PersonImpl* impl;

        Person() : impl(new PersonImpl){} 
        ~Person() { delete impl; }

        void greet(){
            impl->greet(this);
        }
};

int main(){

    return 0;
}


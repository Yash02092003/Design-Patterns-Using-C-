#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include <tuple>
using namespace std;

//A. High-level modules should not depend on low-level moduls.
//   Both should depend on abstraction
//B. Abstractions should not depend on details
//   Details should depend on abstractions

enum Relationship{
  Parent ,
  Child ,
  Siblings
};

struct Person{
  string name;
};

struct RelationshipBrowser{
  virtual vector<Person> browser(string name) = 0;
};

struct Relationships : public RelationshipBrowser{ // low level module
  vector<tuple<Person , Relationship , Person > > relationships;
  void add_parent_and_chid(const Person& parent , const Person &child){
    relationships.push_back(make_tuple(parent, Relationship::Parent , child));
    relationships.push_back(make_tuple(child, Relationship::Child , parent));
  }

  vector<Person> browser(string name) override{
    vector<Person> result;
    for(auto&& [first , relation , second] : this->relationships){
      if(first.name == name && relation == Relationship::Parent ){
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research{ // high level module
  //here the Research is not dependent on the low level module
  //and you need only need to change the base class
  Research(RelationshipBrowser* relationships){
    const auto& result = relationships->browser("Jhon");
    for(auto& item : result){
      cout << item.name << " is a child of Jhon" << endl;
    }
  }
  //Currently here the Research is dependent on the RealtionShips for doing the research but it should not happen
  //because if in near future the research changes it Data Strcuture then you have to implicitly
  // go at each place and change the each and every iteration logic
  Research(Relationships& relationships){
    auto& relations = relationships.relationships;
    for(auto&& [first , rel , second] : relations){
      if(first.name == "Jhon" && rel == Relationship::Parent ){
        cout << "Jhon has a child called" << second.name << endl;
      }
    }
  }
};

int main(){
  Relationships relationships;
  Person parent;
  parent.name = "Jhon";
  Person child;
  child.name = "Arav";
  relationships.add_parent_and_chid(parent, child);

  Research research(&relationships);

  return 0;
}


#include <iostream>


#include "HotDrinkFactory.h"
#include "HotDrink.h"
#include <map>
#include <functional>
#include <memory>

using namespace std;

class DrinkFactory{
  map<string , unique_ptr<HotDrinkFactory > > hot_factories;
 public:
   DrinkFactory(){
       hot_factories["coffee"] = make_unique<CoffeeHotDrinkFactory>();
       hot_factories["Tea"] = make_unique<TeaHotDrinkFactory>();
   }

   unique_ptr<HotDrink> make_drink(const string &drink_type){
     auto drink = hot_factories[drink_type]->createHotDrink();
     return drink;
   }
};

class DrinkWithVolumeFactory{
  map<string , function<unique_ptr<HotDrink>() > > factories;
public:
  DrinkWithVolumeFactory(){
    factories["tea"] = [] {
      auto tea = make_unique<Tea>();
      tea->prepare(200);
      return tea;
    };

    factories["coffee"] = [] {
      auto coffee = make_unique<Coffee>();
      coffee->prepare(200);
      return coffee;
    };

  }

  unique_ptr<HotDrink> make_drink(const string& name){
    return factories[name]();
  }
};

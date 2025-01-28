#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "HotDrinkFactory.h"
#include "DrinkFactory.h"

unique_ptr<HotDrink> make_drink(string type) {
  unique_ptr<HotDrink> dr;
  if( type == "Tea"){
    dr = make_unique<Tea>();
    dr->prepare(200);
  }
  else{
    dr = make_unique<Coffee>();
    dr->prepare(200);
  }
}


int main(){
  DrinkFactory factory;
  auto HotDrink = factory.make_drink("Tea");
  auto HotDrink = factory.make_drink("Coffee");
  return 0;
}
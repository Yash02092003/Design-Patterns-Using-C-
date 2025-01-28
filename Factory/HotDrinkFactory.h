#include "HotDrink.h"
#include <memory>
using namespace std;

struct HotDrinkFactory {
  virtual unique_ptr<HotDrink> createHotDrink() = 0;
};

struct TeaHotDrinkFactory : public HotDrinkFactory {
  unique_ptr<HotDrink> createHotDrink() override{
    return std::make_unique<Tea>();
  }
};

struct CoffeeHotDrinkFactory : public HotDrinkFactory {
  unique_ptr<HotDrink> createHotDrink() override{
    return make_unique<Coffee>();
  }
};


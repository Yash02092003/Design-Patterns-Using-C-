#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Open Close Principle Says that your priciple should be open for inhertiance
//But should be close for modification
//The code is open for extension
//But closed for modifying by inheritance

enum Color { RED , GREEN , BLUE } ;
enum Size { SMALL , MEDIUM , LARGE };

struct Product {
  Product(string n, Color c , Size s) : name(n) , color(c) , size(s) {}
  string name;
  Color color;
  Size size;
};

struct ProductFilter{
  vector<Product*> by_color(vector<Product*> &items , Color color){
    vector<Product*> result;
    for(auto& item : items){
      if(item->color == color){
        result.push_back(item);
     }
    }
    return result;
  }
};

//Specificaiotn Template for specifiying the Specification
template<typename T> struct Specification{
  virtual ~Specification() = default;
  virtual bool isSatisfies(T* item) = 0;
};

//filter template for filter the Objects
template<typename T> struct Filter{
  virtual vector<T*> filter(vector<T*> items , Specification<T>& spec) = 0;
};

template<typename T> struct AndSpecifcation : Specification<T> {
  Specification<T>& first;
  Specification<T>& second;
  AndSpecifcation( Specification<T>& spec1 , Specification<T>& spec2  ) : first(spec1), second(spec2){}
  bool isSatisfies(T* item) override {
    return first.isSatisfies(item) && second.isSatisfies(item);
  }
};

//implementing the filter template for Product
struct BetterFilter : Filter<Product> {
  vector<Product *> filter(vector<Product *> items, Specification<Product> &spec) override {
    vector<Product *> result;
    for(auto& item : items) {
      if (spec.isSatisfies(item))
        result.push_back(item);
    }
    return result;
  }
};

//implementing the ColorSpecification
struct ColorSpecification : Specification<Product> {
  Color color;
  ColorSpecification(Color color) : color(color) {}
  bool isSatisfies(Product* item) override{
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product> {
  Size size;
  SizeSpecification(Size s) : size(s) {}
  bool isSatisfies(Product* item) override {
    return item->size == size;
  }
};

int main(){
     Product apple("Apple" , Color::GREEN , Size::MEDIUM);
     Product tree("Tree" , Color::GREEN , Size::LARGE);
     ProductFilter filter;
     vector<Product*> items { &apple , &tree};
     filter.by_color(items , Color::GREEN);

     //Specification based filtering rather than modifying the base class
     ColorSpecification colors(Color::GREEN);
     BetterFilter better;
     for(auto& item :better.filter(items , colors)){
       cout << item->name << " : " << item->color << endl;
     }

     //And Specification
     SizeSpecification sizes(Size::LARGE);
     AndSpecifcation<Product> colors_sizes(colors , sizes);
     vector<Product*> result = better.filter(items , colors_sizes);
}
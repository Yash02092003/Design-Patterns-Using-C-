#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>

using namespace std;

enum class PointType{
  cartesian,
  polar
};

class Point{
  //Friend class for the factory to access private members
  friend class PointFactory;
  float x , y;
  Point(float x , float y) : x(x), y(y) {}
  //Inner Class for Factroy for better access
  class PointFactory{
    PointFactory(){}
  public:
    static Point NewCartesian(float x , float y){
      return {x , y};
    }

    static Point NewPolar(float r , float theta){
      return {r*cos(theta) , r*sin(theta)};
    }
  };

public:
  friend ostream& operator << (ostream& os , const Point& point){
    os << "X : " << point.x << " Y : " << point.y;
    return os;
  }
  static PointFactory factory;

//  Point(float a  , float b , PointType type = PointType::cartesian){
//    if(type == PointType::cartesian){
//      x = a;
//      y = b;
//    }
//    else{
//      x = a * cos(b);
//      y = a * sin(b);
//  }
};

//Outer Factory
class PointFactory{
  PointFactory(){}
public:
  static Point NewCartesian(float x , float y){
    return {x , y};
  }

  static Point NewPolar(float r , float theta){
    return {r*cos(theta) , r*sin(theta)};
  }
};

int main(){
  Point p1 = PointFactory::NewCartesian(1.0 , 1.0);
  Point p2 = PointFactory::NewPolar(2.0 , 3.0);
  cout << p1 << endl;
  cout << p2 << endl;

  Point p3 = Point::factory.NewCartesian(1.0 , 1.0);
  Point p4 = Point::factory.NewPolar(2.0 , 3.0);

  cout << p3 << endl;
  cout << p4 << endl;

  return 0;
}

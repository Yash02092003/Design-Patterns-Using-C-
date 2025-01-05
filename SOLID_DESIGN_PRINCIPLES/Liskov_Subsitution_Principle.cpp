#include <iostream>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

//liskov susbsitution principle states that Base class and
//child class can be used conversely anywhere for this you
//either you should create a bool flag inside the base class to
//denote whether it is a square or recatngle
//Or you can create a factory to generate objects on the fly
class Rectangle {
protected:
    int height;
    int width;
    int length;
public:
    Rectangle(int h , int w , int l) : height(h) , width(w) , length(l){}
    int getHeight() {
        return height;
    }
    int getWidth() {
        return width;
    }
    int getLength() {
        return length;
    }
    virtual int setHeight(int h) {
        height = h;
    }
    virtual int setWidth(int w) {
        width = w;
    }
    int setLength(int l) {
        length = l;
    }
    int getArea() {
        return width * height;
    }
};

void process(Rectangle& rectangle) {
    int w = rectangle.getWidth();;
    rectangle.setHeight(10);
    cout << rectangle.getHeight() << endl;
    cout << "expected area: " << w * 10 << " but we got is : " << rectangle.getArea();
}

class Square : public Rectangle {
    int size;
    Square(int size) : Rectangle(size , size , size) , size(size){}
public:
    int setWidth(int w) override {
        this->width = this->height = size;
    }
    int setHeight(int h) override {
        this->height = this->width = size;
    }
};

int main() {

}

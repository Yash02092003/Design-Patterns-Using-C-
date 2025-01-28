#include <iostream>
using namespace std;

struct Square{
    int side = 0;
    Square(int side) : side(side){}
};

struct Reactangle{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area(){
        return width() * height();
    }
};


struct SquareToRectangleAdapter : Reactangle{
    int width() const override{
        return w;
    }

    int height() const override{
        return h;
    }

    SquareToRectangleAdapter(Square& sq){
        w = h = sq.side;
    }

private:
    int w;
    int h;
};

int main(){
    Square sq(10);
    SquareToRectangleAdapter sra(sq);
    cout << sra.area() << endl;

    return 0;
}
#include <iostream>
#include <string>
using namespace std;

struct Renderer{
    virtual void render_circle(float x , float y , float radius) = 0;
};

struct vectorRenderer : Renderer{
    void render_circle(float x , float y , float radius) override{
        cout << "Drawing a vector circle of radius" << radius << endl;
    }
};

struct rasterRenderer : Renderer{

    void render_circle(float x , float y , float radius){
        cout << "Drawing a vector circle of radius" << radius << endl;
    }
};


struct Shape{
    protected:
        Renderer& renderer;
        Shape(Renderer &renderer) : renderer(renderer){}
    public:
        virtual void draw() = 0;
        virtual void resize(float factor) = 0;
};

struct Circle : Shape{
    Circle(Renderer& renderer , float x , float y , float radius) : Shape(renderer) , x(x) , y(y) , radius(radius) {}

    float x , y , radius;

    void draw() override{
        renderer.render_circle(x , y , radius);
    }

    void resize(float factor) override{
        radius *= factor;
    }
};


int main(){
    rasterRenderer rr;
    Circle raster_circle(rr , 5 , 5 , 5);
    raster_circle.draw();
    raster_circle.resize(5);
    raster_circle.draw();

    return 0;
}



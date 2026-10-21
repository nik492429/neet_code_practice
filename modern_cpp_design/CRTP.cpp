//Example of having static polymorphism using CRTP (Curiously Recurring Template Pattern)

#include <iostream>
using namespace std;

template <typename T>
concept Drawable = requires(T t) 
{
    t.draw_impl();
};

template <typename Derived>
class Shape
{
    public:
    void draw() requires Drawable<Derived>
    {
        static_cast<Derived*>(this)->draw_impl();
    }
};


class Circle : public Shape<Circle>
{
    public:
    void draw_impl() 
    {
        cout << "Drawing Circle" << endl;
    }
};


class Square : public Shape<Square>
{
    public:
    void draw_impl() 
    {
        cout << "Drawing Square" << endl;
    }
};

int main() {
    Circle c;
    Square s;
    c.draw();
    s.draw();
    return 0;
}
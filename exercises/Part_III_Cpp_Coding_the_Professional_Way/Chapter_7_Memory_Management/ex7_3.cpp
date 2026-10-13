#include <format>
#include <iostream>
#include <memory>

#define print(...)(std::cout << std::format(__VA_ARGS__))
#define println(...)(print(__VA_ARGS__) << '\n')


class Point3D
{

    public:

        Point3D(int x, int y, int z): x_ { x }, y_ { y }, z_ { z } { };

        void printCoord() { print("({}, {}, {})", x_, y_, z_); }

    private:
        int x_, y_, z_;
};

int main()
{

    auto p1 { std::make_unique<Point3D>(3, 4, 5) };

    p1->printCoord();
    println("");

}
#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include <iostream>
#include "fmt/core.h"

class Shape
{
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    Circle(int r) : radius(r) {}
    void draw() const override
    {
        fmt::print("draw a circle {}\n", pi * radius * radius);
    }

private:
    double radius;
    // 类内非静态成员不能声明为constexpr
    static constexpr double pi = 3.14;
};

class Rectangle : public Shape
{
public:
    Rectangle(int a, int b) : length(a), width(b) {}
    void draw() const override
    {
        fmt::print("draw a rectangle {}\n", length * width);
    }

private:
    int length;
    int width;
};

class ShapeFactory
{
public:
    virtual std::unique_ptr<Shape> createShape() const = 0;
    virtual ~ShapeFactory() = default;
};

class CircleFactory : public ShapeFactory
{
public:
    std::unique_ptr<Shape> createShape() const override
    {
        int r;
        fmt::print("请输入半径：\n");
        std::cin >> r;
        return std::make_unique<Circle>(r);
    }
};

class RectangleFactory : public ShapeFactory
{
public:
    std::unique_ptr<Shape> createShape() const override
    {
        fmt::print("请输入长和宽：\n");
        int a, b;
        std::cin >> a >> b;
        return std::make_unique<Rectangle>(a, b);
    }
};



#endif
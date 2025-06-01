#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <memory>
#include <iostream>
#include "fmt/core.h"
#include "Factory.h"

class Color {
public:
    virtual void fill() const = 0;
    virtual ~Color() = default;
};

class Red : public Color {
public:
    void fill() const override {
        fmt::print("filled red\n");
    }
};

class AbstractFactory {
public:
    virtual std::unique_ptr<Shape> createShape() const = 0;
    virtual std::unique_ptr<Color> createColor() const = 0;
    virtual ~AbstractFactory() = default;
};

class MordenFactory : public AbstractFactory {
public:
    std::unique_ptr<Shape> createShape() const override {
        return std::make_unique<Circle>(2);
    }

    std::unique_ptr<Color> createColor() const override {
        return std::make_unique<Red>();
    }
};

#endif
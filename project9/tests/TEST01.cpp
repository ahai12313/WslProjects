#include "fmt/core.h"
#include "CreationPattern/Singleton.h"
#include "CreationPattern/Factory.h"
#include "CreationPattern/AbstrctFactory.h"
#include "CreationPattern/Builder.h"

// 创建型
void TEST01()
{
int a;
std::cout << "请输入模块编号\n";
std::cin >> a;
switch(a)
{
case 1:
    {
        // 单例模式
        fmt::print("饿汉模式\n");
        Singleton& ins1 = Singleton::getInstance();
        fmt::print("{}\n", ins1.val);
        Singleton& ins2 = Singleton::getInstance();
        ins2.val++;
        fmt::print("{}\n", ins1.val);
        fmt::print("{}\n", ins2.val);

        fmt::print("懒汉模式\n");
        Singleton2& ins3 = Singleton2::getInstance();
        Singleton2& ins4 = Singleton2::getInstance();
        fmt::print("{}\n", ins3.val);
        ins4.val++;
        fmt::print("{}\n", ins3.val);
        return;
    }
case 2:
    {
        // 工厂模式
        fmt::print("工厂模式\n");
        std::unique_ptr<ShapeFactory> shapeFactory;
        shapeFactory = std::make_unique<CircleFactory>();
        auto circle = shapeFactory->createShape();
        circle->draw();

        shapeFactory = std::make_unique<RectangleFactory>();
        std::unique_ptr<Shape> rect = shapeFactory->createShape();
        rect->draw();
        return;
    }
case 3:
    {
        // 抽象工厂
        fmt::print("抽象工厂\n");
        std::unique_ptr<AbstractFactory> absFactory;
        absFactory = std::make_unique<MordenFactory>();
        auto shape = absFactory->createShape();
        auto color = absFactory->createColor();
        shape->draw();
        color->fill();
    }
case 4:
    {
        // 建造者模式
        fmt::print("建造者模式\n");
        
        GameingComputerBuilder g_builder;
        Director director;

        director.setBuilder(&g_builder);
        director.construct();
        auto gamePC = g_builder.getResult();
        gamePC->show();
        fmt::print("xxxxxxxxxxxxxxxxxxxxxxxx\n");
        OfficeComputerBuilder o_builder;
        director.setBuilder(&o_builder);
        director.construct();
        auto officePC = o_builder.getResult();
        officePC->show();

        fmt::print("链式调用\n");
        FluentBuilder f_bulder;
        auto PC = f_bulder.setCPU("CC").setGPU("GG").setMEM("MM").setSTOR("SS").getResult();
        PC->show();


        return;
    }
}
}

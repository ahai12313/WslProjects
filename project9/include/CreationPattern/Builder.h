#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include <memory>
#include <fmt/core.h>

class Computer {
public:
    void setCPU(std::string cpu) { cpu_ = cpu;}
    void setGPU(std::string gpu) { gpu_ = gpu;}
    void setMEM(std::string mem) { mem_ = mem;}
    void setSTOR(std::string storage) { storage_ = storage;}

    void show() {
        fmt::print(
            "cpu {}\n"
            "gpu {}\n"
            "mem {}\n"
            "storage {}\n",
            cpu_, gpu_, mem_, storage_
        );
    }

private:
    std::string cpu_;
    std::string gpu_;
    std::string mem_;
    std::string storage_;

};

// 抽象建造者
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;
    virtual void buildCPU() = 0;
    virtual void buildGPU() = 0;
    virtual void buildMEM() = 0;
    virtual void buildSTOR() = 0;
    virtual std::unique_ptr<Computer> getResult() = 0;
};

// 具体建造者
class GameingComputerBuilder : public ComputerBuilder {
public:
    GameingComputerBuilder() { computer_ = std::make_unique<Computer>(); }

    void buildCPU() override { computer_->setCPU("Intel Core i9-13900K");}
    void buildGPU() override { computer_->setGPU("32GB DDR5 5600MHz");}
    void buildMEM() override { computer_->setMEM("2TB NVMe SSD");}
    void buildSTOR() override { computer_->setSTOR("NVIDIA RTX 4090");}
    
    std::unique_ptr<Computer> getResult() override { return std::move(computer_);}

private:
    std::unique_ptr<Computer> computer_;
};

// 4. 具体建造者：办公电脑
class OfficeComputerBuilder : public ComputerBuilder {
    public:
        OfficeComputerBuilder() { computer_ = std::make_unique<Computer>(); }
    
        void buildCPU() override { computer_->setCPU("Intel Core i5-12400"); }
        void buildMEM() override { computer_->setMEM("16GB DDR4 3200MHz"); }
        void buildSTOR() override { computer_->setSTOR("512GB SSD"); }
        void buildGPU() override {} // 办公电脑不需要独立显卡
    
        std::unique_ptr<Computer> getResult() override { return std::move(computer_); }
    
    private:
        std::unique_ptr<Computer> computer_;
};

class Director {
public:
    void setBuilder(ComputerBuilder* builder) { builder_ = builder; }

    void construct() {
        builder_->buildCPU();
        builder_->buildGPU();
        builder_->buildMEM();
        builder_->buildSTOR();
    }

private:
    ComputerBuilder *builder_;
};

class FluentBuilder {
public:
    std::unique_ptr<Computer> getResult() { return std::move(computer_); }

    FluentBuilder& setCPU(std::string cpu) {
        computer_->setCPU(cpu);
        return *this;
    }
    FluentBuilder& setGPU(std::string gpu) {
        computer_->setGPU(gpu);
        return *this;
    }
    FluentBuilder& setMEM(std::string mem) {
        computer_->setMEM(mem);
        return *this;
    }
    FluentBuilder& setSTOR(std::string storage) {
        computer_->setSTOR(storage);
        return *this;
    }

    FluentBuilder() { computer_ = std::make_unique<Computer>(); }

private:
    std::unique_ptr<Computer> computer_;
};

#endif
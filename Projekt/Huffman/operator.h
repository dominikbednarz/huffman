#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>

// klasa bazowa 
class Operator
{
public:
    virtual ~Operator() {} // wirtualny destruktor
    virtual void run() = 0;
    virtual void clean_up() = 0;
};

// klasa do kompresji pliki
class Compressor : public Operator {
public:
    Compressor(std::unique_ptr<std::ifstream> input, std::unique_ptr<std::ofstream> output);
    void run() override;
    void clean_up() override;
private:
    std::unique_ptr<std::ifstream> input_;
    std::unique_ptr<std::ofstream> output_;

    static void compress(std::ifstream& input, std::ofstream& output);
};

// klasa do dekompresji pliki
class Decompressor : public Operator {
public:
    Decompressor(std::unique_ptr<std::ifstream> input, std::unique_ptr<std::ofstream> output);
    void run() override;
    void clean_up() override;
private:
    std::unique_ptr<std::ifstream> input_;
    std::unique_ptr<std::ofstream> output_;

    static void decompress(std::ifstream& input, std::ofstream& output);
};

#endif
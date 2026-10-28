#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <cassert>

class Product
{
private:
    std::string name;
    long price;

    static int totalCount;

public:
    Product(std::string n, long p);
    ~Product();

    static int getTotalCount();

    void printInfo() const;
};

#endif
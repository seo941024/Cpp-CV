#include "product.h"

using namespace std;

int Product::totalCount = 0;

Product::Product(string n, long p)
{
    assert(p >= 0);

    name = n;
    price = p;

    totalCount++;

    cout << "제품 등록 완료: "
         << name
         << endl;
}

Product::~Product()
{
    totalCount--;

    cout << "제품 삭제 완료: "
         << name
         << endl;
}

int Product::getTotalCount()
{
    return totalCount;
}

void Product::printInfo() const
{
    cout << "제품명: "
         << name
         << ", 가격: "
         << price
         << endl;
}
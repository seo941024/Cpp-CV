#include "product.h"

using namespace std;

int main()
{
     cout << "초기 제품 수: "
          << Product::getTotalCount()
          << endl;

     Product p1("노트북", 1500000);

     p1.printInfo();

     cout << "현재 총 제품 수: "
          << Product::getTotalCount()
          << endl
          << endl;

     cout << "--- 블록 진입 ---"
          << endl;

     {
          Product p2("마우스", 30000);

          p2.printInfo();

          cout << "블록 내부 제품 수: "
               << Product::getTotalCount()
               << endl;

          cout << "--- 블록 탈출 시도 ---"
               << endl;
     }

     cout << endl;

     cout << "블록 탈출 후 총 제품 수: "
          << Product::getTotalCount()
          << endl;

     return 0;
}
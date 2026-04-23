#include <iostream>
using namespace std;

int main()
{
    int n, x;
    bool success = false;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> x;

        if (x > 0)
        {
            success = true;
        }
    }

    if (success)
        cout << "Success\n";
    else
        cout << "Failure\n";

    return 0;
}

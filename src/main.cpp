#include <iostream>
#include <string>
using namespace std;

#include "./math/matrix.hpp"
using namespace math;

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        cout << "Too many arguments" << endl;
        return 1;
    }
    else if (argc < 2)
    {
        cout << "Too few arguments" << endl;
        return 1;
    }
    string configPath = argv[1];

    return 0;
}
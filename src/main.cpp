#include <iostream>
#include <string>
using namespace std;

i
using namespace std;
using namespace std;nt main(int argc, char **argv)
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
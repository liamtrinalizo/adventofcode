#include <string>
#include <iostream>
#include <fstream>

using namespace std;

main()
{
    ifstream input;
    string line;
    input.open("input");
    if (!input.is_open())
        return -1;

    int maxCal = 0;
    int elfCal = 0;

    while (getline(input, line))
    {
        if (line != "")
            elfCal += stoi(line);
        else
        {
            if (maxCal < elfCal)
                maxCal = elfCal;
            elfCal = 0;
        }

    }
    input.close();
    cout << "maxCal " << maxCal;
}

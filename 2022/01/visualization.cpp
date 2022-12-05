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
    int elfNum = 0;

    while (getline(input, line))
    {
        if (line != "")
            elfCal += stoi(line);
        else
        {
            if (maxCal < elfCal)
                maxCal = elfCal;
            elfNum ++;
            cout << "'elf1.png' binary filetype=png origin=(" << elfNum * 20 << ",0) dx=0.5 dy=" << elfCal / 73000.0 << " with rgbimage, ";
            elfCal = 0;
        }

    }
    input.close();
}

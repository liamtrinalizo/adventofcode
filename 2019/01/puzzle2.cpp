#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Module {
    int mass;
    Module(int m): mass(m) {}
    int evalFuel() {
        int fuelTot = 0;
        while (mass > 6)
        {
            mass = mass/3 - 2;
            fuelTot += mass;
        }
        return fuelTot;
    }
};

int main()
{
    ifstream input;
    string line;
    input.open("input");
    if (!input.is_open())
        return -1;

    int totalFuel = 0;

    while (getline(input,line))
    {
        Module *mod = new Module(stoi(line));
        totalFuel += mod->evalFuel();
        delete mod;
    }

    input.close();
    cout << totalFuel;

    return 0;
}

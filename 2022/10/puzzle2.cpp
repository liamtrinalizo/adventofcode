#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// { 20, 60, 100, 140, 180, 220 };

void incCycles(int &curCycle, int regVal, string &screen) {
    int cyclePos = curCycle - 1;
    if (cyclePos >= regVal - 1 && cyclePos <= regVal + 1)
        screen += "#";
    else
        screen += ".";

    // print and reset line
    if (curCycle % 40 == 0) {
        cout << screen << endl;
        screen = "";
        curCycle = 0;
    }

    curCycle++;
}

int main() {
    ifstream file("input");
    string line, screen;
    int regVal = 1, cycleVal = 1;

    while (getline(file, line)) {
        istringstream stream(line);
        string cmd;
        stream >> cmd;
        if (cmd == "addx") {
            int val;
            stream >> val;
            incCycles(cycleVal, regVal, screen);
            incCycles(cycleVal, regVal, screen);
            regVal += val;

        } else { //noop
            incCycles(cycleVal, regVal, screen);
        }
    }
}

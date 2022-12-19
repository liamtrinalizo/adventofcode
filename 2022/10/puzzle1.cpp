#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//array<int, 6> Cycles = { 20, 60, 100, 140, 180, 220 };

void incCycles(int &curCycle, int &signalStrg, int regVal) {
    if (curCycle >= 20 && curCycle <= 220 && (curCycle - 20) % 40 == 0)
        signalStrg += curCycle * regVal;
    curCycle++;
}

int main() {
    ifstream file("input");
    string line;
    int regVal = 1, cycleVal = 1, signalStrg = 0;

    while (getline(file, line)) {
        istringstream stream(line);
        string cmd;
        stream >> cmd;
        if (cmd == "addx") {
            int val;
            stream >> val;
            incCycles(cycleVal, signalStrg, regVal);
            incCycles(cycleVal, signalStrg, regVal);
            regVal += val;

        } else { //noop
            incCycles(cycleVal, signalStrg, regVal);
        }
    }
    cout << "signal strengh " << signalStrg;
}

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream input;
    string line;
    input.open("input");
    int priorityTot = 0;
    int count = 0;
    string rucksack[3];

    while (getline(input, line)) {
        if (count < 2) {
            rucksack[count] = line;
            count++;
        } else {
            rucksack[count] = line;
            count = 0;

            for (int i = 0; i < rucksack[0].size(); i++) {
                if (rucksack[1].find(rucksack[0][i]) != string::npos and
                    rucksack[2].find(rucksack[0][i]) != string::npos)
                {
                    cout << rucksack[0][i] << "\n";
                    if (rucksack[0][i] > int('Z'))
                        priorityTot += rucksack[0][i] - int('a') + 1;
                    else
                        priorityTot += rucksack[0][i] - int('A') + 27;
                    break;
                }
            }
        }
    }
    input.close();
    cout << "priority sum : " << priorityTot;
}

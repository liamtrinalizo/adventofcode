#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream input;
    string line;
    input.open("input");
    int priorityTot = 0;

    while (getline(input, line)) {
        int size = line.size();
        string compartment0 = line.substr(0, size/2);
        string compartment1 = line.substr(size/2, size - 1);
        for (int i = 0; i < size/2; i++) {
            if (compartment1.find(compartment0[i]) != string::npos)
            {
                if (compartment0[i] > int('Z'))
                    priorityTot += compartment0[i] - int('a') + 1;
                else
                    priorityTot += compartment0[i] - int('A') + 27;
                break;
            }
        }

    }
    input.close();
    cout << "priority sum : " << priorityTot;
}

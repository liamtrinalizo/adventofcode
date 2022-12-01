#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

main()
{
    ifstream input;
    string line;
    input.open("input");
    if (!input.is_open())
        return -1;

    vector<int> maxCal = {0};
    int elfCal = 0;
    bool endFile = false;

    while (getline(input, line) || ! endFile) {
        if (line != "")
            elfCal += stoi(line);
        else {
            //cout << "elf calories: " << elfCal << "\n";
            vector<int>::iterator iter = maxCal.begin();
            for (iter; iter < maxCal.end(); iter++) {
                //cout << "\ttest " << *iter << " vs " << elfCal << "\n";
                if (*iter < elfCal) {
                    //cout<< "insert " << elfCal << "\n";
                    maxCal.insert(iter, elfCal);

                    //for (int i = 0; i <maxCal.size(); i++)
                    //    cout << maxCal[i] << " ";
                    //cout << "\n";
                    elfCal = 0;
                    break;
                }
            }
            elfCal = 0;
            endFile = input.eof();
        }
    }
    input.close();

    cout << "top three cal " << maxCal[0] + maxCal[1] + maxCal[2] << "\n";
}

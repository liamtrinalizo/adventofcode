#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    ifstream file("input");
    string line;
    getline(file, line);

    // init cursor
    list<char> cursor;
    for (int i=0; i < 3; i++)
        cursor.push_back(line[i]);

    // search for start-of-packet
    int sop = 0;
    for (int i=3; i < line.size(); i++) {
        cursor.push_back(line[i]);
        list<char> tmp = cursor;
        tmp.sort();
        if (adjacent_find(tmp.begin(), tmp.end()) == tmp.end()) {
            sop = i;
            break;
        }

        cursor.pop_front();
    }
    cout << sop + 1 << "\n";
}

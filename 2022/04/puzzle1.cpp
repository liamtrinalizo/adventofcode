#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ifstream file("input");
    string line;
    int overlapCnt = 0;
    while (getline(file, line)) {
        unsigned int coor[4];
        istringstream stream(line);

        // parse input
        for (int i = 0; i < 4; i++) {
            char discard;
            stream >> coor[i];
            stream.get(discard);
        }

        // check for total overlap
        if ((coor[0] <= coor[2] && coor[1] >= coor[3]) ||
            (coor[2] <= coor[0] && coor[3] >= coor[1])) {
            overlapCnt++;
        }
    }
    cout << "overlap count: " << overlapCnt;
}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int main() {
    ifstream file("input");
    string line;

    vector<deque<char>> stacks;

    // get initial position
    while (getline(file, line)) {
        if (line[1] == '1')
            break;

        for (int i = 1; i < line.size(); i+= 4) {
            int crateStack = i/4;
            if (stacks.size() < crateStack + 1) {
                deque<char> tmp;
                stacks.push_back(tmp);
            }
            if (line[i] == ' ')
                continue;
            stacks[crateStack].push_front(line[i]);
        }
    }

    // get moves
    while (getline(file, line)) {
        if (line == "")
            continue;
        int moves[3] = {0};
        stringstream stream;
        stream << line;
        for (int i = 0; i < 3; i++) {
            string tmp;
            stream >> tmp;
            stringstream(tmp) >> tmp;
            stream >> tmp;
            stringstream(tmp) >> moves[i];
        }
        moves[1]--;
        moves[2]--;

        vector<char> tmp;
        for (int cnt=0; cnt < moves[0]; cnt++) {
            tmp.push_back(stacks[moves[1]].back());
            stacks[moves[1]].pop_back();
        }
        for (int cnt=0; cnt < moves[0]; cnt++) {
            stacks[moves[2]].push_back(tmp.back());
            tmp.pop_back();
        }
    }
    cout << "top crates ";
    for (deque<char> d : stacks)
        cout << d.back();
}

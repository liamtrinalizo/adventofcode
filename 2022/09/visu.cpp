#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <array>
#include <iomanip>
#include <cmath>

using namespace std;

int newPos(int prev, int curr, int offset) {
    return (abs(prev - curr) - offset) * (prev - curr > 0 ? 1 : -1);
}

int main() {
    ifstream file("input");
    string line;

    set<pair<int, int>> tailPos;
    set<pair<int, int>> tailPos2;
    array<array<int, 2>, 10> k{0};
    tailPos.insert(make_pair(0,0));
    tailPos2.insert(make_pair(0,0));

    while (getline(file, line)) {
        char way;
        int step;
        istringstream stream(line);
        stream >> way;
        stream >> step;
        for (int i = 0; i < step; i++) {
            switch (way) {
                case 'U': k[0][0]++; break;
                case 'D': k[0][0]--; break;
                case 'R': k[0][1]++; break;
                case 'L': k[0][1]--; break;
            }
            for (int j = 1; j < k.size(); j++) {
                // lookup head/tail distance
                array<int, 2> dist = { abs(k[j-1][0] - k[j][0]), abs(k[j-1][1] - k[j][1]) };
                if (dist[0] > 1 || dist[1] > 1) {
                    // move straight
                    if (k[j-1][0] == k[j][0] || k[j-1][1] == k[j][1]) {
                        if (k[j-1][0] == k[j][0]) {
                            k[j][1] = k[j][1] + newPos(k[j-1][1], k[j][1], 1);
                        } else
                            k[j][0] = k[j][0] + newPos(k[j-1][0], k[j][0], 1);
                        // move diagonal
                    } else {
                        for (int i = 0; i < 2; i++) {
                            if (dist[i] == 1 && dist[1 - i] > 1) {
                                k[j][i] = k[j][i] + newPos(k[j-1][i], k[j][i], 0);
                                k[j][1-i] = k[j][1-i] + newPos(k[j-1][1-i], k[j][1-i], 1);
                                break;
                            }
                        }
                        if (dist[0] == 2 && dist[1] == 2) {
                            k[j][0] = k[j][0] + newPos(k[j-1][0], k[j][0], 1);
                            k[j][1] = k[j][1] + newPos(k[j-1][1], k[j][1], 1);
                        }
                    }
                }
                tailPos.insert(make_pair(k.back()[0], k.back()[1]));
                tailPos2.insert(make_pair(k[8][0], k[8][1]));
            }
            for (int x = -25; x < 26; x++) {
                for (int y = -30; y < 40; y++) {
                    bool found = false;
                    for (int i = 0; i <  k.size(); i++) {
                        if (k[i][0] == -x && k[i][1] == y) {
                            cout << i;
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                        if (x == 0 && y == 0)
                            cout << "S";
                        else
                            cout << ".";
                }
                cout << endl;
            }
        }
    }
}

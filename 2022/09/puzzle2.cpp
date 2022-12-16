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
    ifstream file("input_test2");
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
        printf("=== %c %d ===\n", way, step);
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
                            }
                        }
                    }
                }
            }
            tailPos.insert(make_pair(k.back()[0], k.back()[1]));
            tailPos2.insert(make_pair(k[8][0], k[8][1]));
            //cout << k[0][0] << " " << k[0][1] << " - " << k.back()[0] << " " << k.back()[1] << "\n";
        }
    for (int x = -7; x < 10; x++) {
        for (int y = -17; y < 20; y++) {
            auto it = tailPos.find(make_pair(x, y));
            if (tailPos2.find(make_pair(x, y)) != tailPos2.end())
                cout << "8";
            else
                cout << ".";
        }
        cout << endl;
    }
    }
    cout << "visited positions " << tailPos.size();
}

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <array>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ifstream file("input");
    string line;

    set<pair<int, int>> tailPos;
    array<int, 2> h = {0}, t = {0};
    tailPos.insert(make_pair(t[0],t[1]));

    while (getline(file, line)) {
        char way;
        int step;
        istringstream stream(line);
        stream >> way;
        stream >> step;
        for (int i = 0; i < step; i++) {
            switch (way) {
                case 'U': h[0]++; break;
                case 'D': h[0]--; break;
                case 'R': h[1]++; break;
                case 'L': h[1]--; break;
            }
            // lookup head/tail distance
            array<int, 2> dist = { abs(h[0] - t[0]), abs(h[1] - t[1]) };
            if (dist[0] > 1 || dist[1] > 1) {
                // move straigt
                if (h[0] == t[0] || h[1] == t[1]) {
                    if (h[0] == t[0]) {
                        t[1] = t[1] + (dist[1]-1) * (h[1] - t[1] > 0 ? 1 : -1);
                    } else
                        t[0] = t[0] + (dist[0]-1) * (h[0] - t[0] > 0 ? 1 : -1);
                // move diagonal
                } else {
                    for (int i = 0; i < 2; i++) {
                        if (dist[i] == 1 && dist[1 - i] > 1)
                            t[i] = t[i] + dist[i] * (h[i] - t[i] > 0 ? 1 : -1);
                            t[1-i] = t[1-i] + (dist[1-i]-1) * (h[1-i] - t[1-i] > 0 ? 1 : -1);
                        }
                    }
                }
            tailPos.insert(make_pair(t[0],t[1]));
        }
    }
    cout << "visited positions " << tailPos.size();
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("input");
    string line;
    vector<string> trees;
    int visibleCnt = 0;

    while (getline(file, line)) {
        // add bottom and to row
        if (visibleCnt == 0)
            visibleCnt = 2 * line.size();

        // add left and right trees for every rows
        visibleCnt += 2;

        trees.push_back(line);
    }
    // remove corners counted twice
    visibleCnt -= 4;

    int ysize = trees.size();
    int xsize = trees[0].size();
    for (int y = 1; y < ysize - 1; y++) {
        for (int x = 1; x < xsize - 1; x++) {
            bool visible = true;
            // test left side
            for (int i=0; i < x; i++) {
                if (trees[y][i] >= trees[y][x]) {
                    visible = false;
                    break;
                }
            }
            // test right side
            if (!visible) {
                visible = true;
                for (int i=x+1; i < xsize; i++) {
                    if (trees[y][i] >= trees[y][x]) {
                        visible = false;
                        break;
                    }
                }
            }
            // test top side
            if (!visible) {
                visible = true;
                for (int i=0; i < y; i++) {
                    if (trees[i][x] >= trees[y][x]) {
                        visible = false;
                        break;
                    }
                }
            }
            // test bottom side
            if (!visible) {
                visible = true;
                for (int i=y+1; i < ysize; i++) {
                    if (trees[i][x] >= trees[y][x]) {
                        visible = false;
                        break;
                    }
                }
            }
            if (visible)
                visibleCnt++;
        }
    }

    cout << "visible trees " << visibleCnt;
}

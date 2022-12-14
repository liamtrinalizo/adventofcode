#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("input");
    string line;
    vector<string> trees;
    int maxScore = 0;

    while (getline(file, line))
        trees.push_back(line);

    int ysize = trees.size();
    int xsize = trees[0].size();

    // ignore edges of score 0
    for (int y = 1; y < ysize - 1; y++) {
        for (int x = 1; x < xsize - 1; x++) {
            int score = 1;

            // test left side
            int s = 0;
            for (int i=x-1; i >= 0; i--) {
                s++;
                if (trees[y][i] >= trees[y][x])
                    break;
            }
            score *= s;
            // test right side
            s = 0;
            for (int i=x+1; i < xsize; i++) {
                s++;
                if (trees[y][i] >= trees[y][x])
                    break;
            }
            score *= s;
            // test top side
            s = 0;
            for (int i=y-1; i >= 0; i--) {
                s++;
                if (trees[i][x] >= trees[y][x])
                    break;
            }
            score *= s;
            // test bottom side
            s = 0;
            for (int i=y+1; i < ysize; i++) {
                s++;
                if (trees[i][x] >= trees[y][x])
                    break;
            }
            score *= s;
            if (score > maxScore)
                maxScore = score;
        }
    }
    cout << "highest score " << maxScore;
}

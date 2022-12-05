#include <fstream>
#include <string>
#include <iostream>

/*
oppo  me  meaning   val
A     X   rock      1
B     Y   paper     2
C     Z   scissors  3
*/

using namespace std;

int handwin[3]  = { 1, 2, 0 };
int handlose[3] = { 2, 0, 1 };

enum ENDING {
    lose,
    draw,
    win
};

struct Round {
    int result = 0;
    int myHand = 0;

    Round(int oppo, int end) {
        // convert hand to value
        int oppoHand = oppo - int('A');
        ENDING ending = static_cast<ENDING>(end - int('X'));

        switch (ending) {
            case lose: myHand = handlose[oppoHand];
                       result = 0;
                       break;
            case win:  myHand = handwin[oppoHand];
                       result = 6;
                       break;
            case draw: myHand = oppoHand ;
                       result = 3;
                       break;
        }
        //cout << "oppo " << oppoHand << " myhand " << myHand + 1 << " result " << result << "\n";
    }

    int getScore() {
        return myHand + 1 + result;
    }
};

int main() {
    ifstream input;
    string line;
    input.open("input");
    int scoreTot = 0;

    while (getline(input,line)) {
        Round *round = new Round(line[0], line[2]);
        scoreTot += round->getScore();

        delete round;
    }
    cout << "score " << scoreTot;
}

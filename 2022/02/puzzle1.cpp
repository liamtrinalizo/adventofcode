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

int handmask[3] = { 0b011, 0b110, 0b101 };

struct Round {
    int result = 0;
    int myHand = 0;

    Round(int oppo, int me) {
        // convert hand to value
        int oppoHand = oppo - int('A');
        myHand = me - int('X');
        int winingHand = handmask[oppoHand] & handmask[myHand];
        if (winingHand & (1 << myHand))
            if (winingHand & (1 << oppoHand))
                result = 3; /// draw
            else
                result = 6; /// win
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

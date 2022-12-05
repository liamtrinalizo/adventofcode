#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int handwin[3]  = { 1, 2, 0 };
int handlose[3] = { 2, 0, 1 };
int oppoHandCnt[3] = {0};
int selfHandCnt[3] = {0};
int lossDrawWin[3] = {0};
float rounds = 0.0;

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
        rounds++;
        lossDrawWin[ending]++;
        switch (ending) {
            case win:  myHand = handwin[oppoHand];
                       result = 6;
                       break;
            case draw: myHand = oppoHand ;
                       selfHandCnt[myHand] ++;
                       result = 3;
                       break;
            case lose: myHand = handlose[oppoHand];
                       result = 0;
                       oppoHandCnt[oppoHand] ++;
                       break;
        }
        printf("%f      %f      %f\n",
               lossDrawWin[1]/rounds,
               lossDrawWin[0]/rounds,
               lossDrawWin[2]/rounds);
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

    puts("reset session\n" \
         "set terminal pngcairo  transparent enhanced font 'arial,12' fontscale 1.0 size 1000, 1200\n" \
         "set output 'visu.png'\n" \
         "$WINS << EOD\n" \
         "win      draw      loss");

    while (getline(input,line)) {
        Round *round = new Round(line[0], line[2]);
        scoreTot += round->getScore();
        delete round;
    }

    printf("EOD\n" \
           "$PLAYER << EOD\n" \
           "✊      ✌️      🤚\n" \
           "%d      %d      %d\n" \
           "EOD\n" \
           "$OPPONENT << EOD\n" \
           "✊      ✌️      🤚\n" \
           "%d      %d      %d\n" \
           "EOD\n" \
           "set style spiderplot fs solid 0.3 border lw 3.0\n" \
           "set key autotitle columnhead font ',9'\n" \
           "set multiplot layout 2,2 title 'Rock, Paper, Scisors study' font ',18' offset 0,1 \n" \
           "# ------------\n" \
           "set size 1,0.5\n" \
           "set origin 0,0.5\n" \
           "set title 'Win Draw Loss ratio evolution over rounds' offset 0,1\n" \
           "plot for [i=1:3] $WINS using i with filledcurves x1\n" \
           "# ------------\n" \
           "set spiderplot\n" \
           "set origin 0,0\n" \
           "set key autotitle columnhead font ',24'\n" \
           "set for [i=1:3] paxis i tics font ',9'\n" \
           "set title 'Player winning hand moves repartition' offset 0,1\n" \
           "set for [i=1:3] paxis i range [0:1000] \n" \
           "plot for [i=1:3] $PLAYER using i\n" \
           "# ------------\n" \
           "set origin 0.5,0\n" \
           "set title 'Opponent winning hand moves repartition' offset 0,1\n" \
           "set for [i=1:3] paxis i range [0:300] \n" \
           "plot for [i=1:3] $OPPONENT using i\n" \
           "unset multiplot",
           selfHandCnt[0], selfHandCnt[1], selfHandCnt[2],
           oppoHandCnt[0], oppoHandCnt[1], oppoHandCnt[2]);
}

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int main() {
    ifstream input;
    string line;
    input.open("input");
    int alpha[26];
    int upperCase[26];
    int lowerCase[26];
    fill_n(alpha, 26, 1);
    fill_n(upperCase, 26, 1);
    fill_n(lowerCase, 26, 1);

    while (getline(input, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] > int('Z'))
                alpha[line[i] - int('a')]++;
            else {
                alpha[line[i] - int('A')]++;
                upperCase[line[i] - int('A')]++;
            }
        }
    }
    input.close();

// Arrange coordinate like this:
// A B C D E F G
// H I J K L M N
// O P Q R S T U
//   V W X Y Z

    puts("#!/usr/local/bin/gnuplot -persist\n" \
         "set terminal pngcairo  background '#ffffff' enhanced fontscale 2.5 size 500, 500 \n" \
         "set output 'visu.png'\n" \
         "unset border\n" \
         "unset key\n" \
         "set datafile separator ' '\n" \
         "set size ratio 1 1,1\n" \
         "set style data lines\n" \
         "unset xtics\n" \
         "unset ytics\n" \
         "set colorbox vertical origin screen 0.9, 0.2 size screen 0.35, 0.3 front noinvert bdefault\n" \
         "set title 'Letters frequency analysis' offset 0,1 font ',8'\n" \
         "Scale(size) = 0.05*((column(size)))\n" \
         "Letter(String,Size) = sprintf('{/=%d %s}', Scale(Size), stringcolumn(String))\n" \
         "NO_ANIMATION = 1\n" \
         "save_encoding = 'utf8'\n" \
         "$DATA << EOD\n");

    int x = 6, y = 0;
    int cnt = 0;
    for (int i = 25; i >= 0; i--) {
        printf("%c %d %d %d %d\n", static_cast<char>(i + int('a')), alpha[i], upperCase[i]/lowerCase[i], x, y);
        if (x > 0)
            x--;
        else {
            if (y == 2)
                x = 5;
            else
                x = 6;
            y++;
        }
    }
    puts("EOD\n" \
         "plot $DATA using 4:5:(Letter(1,2)):3 with labels tc pal z");
}

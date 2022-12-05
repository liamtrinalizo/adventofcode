#include <string>
#include <iostream>
#include <fstream>

using namespace std;

main()
{
    ifstream input;
    string line;
    input.open("input");
    if (!input.is_open())
        return -1;

    int maxCal = 0;
    int elfCal = 0;
    int elfNum = 0;

    printf("set terminal pngcairo  transparent enhanced font 'arial,10' fontscale 1.0 size 6000, 300 \n" \
         "set output 'visu.png'\n" \
         "set grid nopolar\n" \
         "set grid noxtics nomxtics ytics nomytics noztics nomztics nortics nomrtics nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics\n" \
         "set grid layerdefault  lt 0 linecolor 0 linewidth 0.500,  lt 0 linecolor 0 linewidth 0.500\n" \
         "unset key\n" \
         "set xtics border in scale 0,0 mirror norotate  autojustify\n" \
         "set xtics 100\n" \
         "set y2tics border in scale 1,0.5 nomirror norotate  autojustify\n" \
         "set y2tics  norangelimit autofreq \n" \
         "set title 'Elf calories repartition' \n" \
         "set xrange [ 0 : 5100 ] noreverse writeback\n" \
         "set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault\n" \
         "set xlabel 'Elfs 🧝(in case that was not obvious)'\n" \
         "set ylabel 'Calorie ratio'\n" \
         "NO_ANIMATION = 1\n" \
         "unset xtics\n" \
         "unset ytics\n"
         "plot ");

    while (getline(input, line))
    {
        if (line != "")
            elfCal += stoi(line);
        else
        {
            if (maxCal < elfCal)
                maxCal = elfCal;
            elfNum ++;
            cout << "'elf1.png' binary filetype=png origin=(" << elfNum * 20 << ",0) dx=0.5 dy=" << elfCal / 73000.0 << " with rgbimage, ";
            elfCal = 0;
        }
    }
    input.close();
}

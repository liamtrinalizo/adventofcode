#include <stdio.h>

int main() {
    FILE *input = fopen("input", "r");
    int planeseat[872] = {0};

    while (!feof(input)) {
        int row_max = 127, row_min = 0;
        int column_max = 7, column_min = 0;
        char line[11];
        fscanf(input, "%s\n", line);

        for (int i = 0; i < 7; i++) {
            if (line[i] == 'F')
                row_max -= (row_max-row_min +1)/2;
            else if (line[i] == 'B')
                row_min += (row_max-row_min +1)/2;
            else
                puts("ERROR char not recognized");
            //printf("+++%d, %d, %d\n", i, row_min, row_max);
        }
        int row = -1;
        if (row_min == row_max)
            row = row_min;
        else
            printf("Not unique range, %d, %d\n", row_min, row_max);

        for (int i = 7; i < 10; i++) {
            if (line[i] == 'L')
                column_max -= (column_max-column_min +1)/2;
            else if (line[i] == 'R')
                column_min += (column_max-column_min +1)/2;
            else
                puts("ERROR char not recognized");
            //printf("---%d, %d, %d\n", i, column_min, column_max);
        }
        int column = -1;
        if (column_min == column_max)
            column = column_min;
        else
            printf("Not unique range, %d, %d\n", column_min, column_max);

        int currentseat = row*8 + column;
        planeseat[currentseat] = 1;

        //printf("%s, row: %d, column: %d, ID: %03d\n", line, row, column, currentseat);
    }

    for (int i = 0; i < 872; i++)
        if (planeseat[i] != 1)
            printf("Seat %d missing\n", i);

    return 0;
}

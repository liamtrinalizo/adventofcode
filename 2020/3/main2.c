#include <stdio.h>

#define SLOPES 5

int main() {
    FILE *input = fopen("input", "r");

    int treecount[SLOPES] = {0};
    int slopex[SLOPES] = {1, 3, 5, 7, 1};
    int slopey[SLOPES] = {1, 1, 1, 1, 2};

    for (int i = 0; i < SLOPES; i++) {
        int x = 0;
        char line[32];

        //Always start at first line
        fscanf(input, "%s\n", line);

        while (!feof(input)) {
            for (int j = 0; j < slopey[i]; j++) {
                fscanf(input, "%s\n", line);
            }

            x = (x + slopex[i]) % 31;
            if (line[x] == '#')
                treecount[i]++;

        }
        printf("Slope %d has %d trees\n", i+1, treecount[i]);
        rewind(input);
    }

    long tot = 1;
    for (int i = 0; i < SLOPES; i++)
        tot *= treecount[i];

    printf("%ld in total\n", tot);
}

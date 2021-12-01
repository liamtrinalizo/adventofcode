#include <stdio.h>

int main() {
    FILE *input = fopen("input", "r");

    int treecount = 0;
    int x = 0;
    while (!feof(input)) {
        char line[32];
        fscanf(input, "%s\n", line);
        if (line[x] == '#')
            treecount++;

        x = (x + 3) % 31;
    }
    rewind(input);

    printf("%d trees encountered\n", treecount);
}

#include <stdio.h>

int main() {
    FILE *input = fopen("input", "r");

    int a, b;
    while (!feof(input)) {
        fscanf(input, "%d\n", &a);

        fpos_t pos1;
        fgetpos(input, &pos1);
        while (!feof(input)) {
            fscanf(input, "%d\n", &b);
            if (a + b == 2020) {
                printf("result %d\n", a * b);
                return 0;
            }
        }
        fsetpos(input, &pos1);
    }
    puts("no results\n");
    return 0;
}

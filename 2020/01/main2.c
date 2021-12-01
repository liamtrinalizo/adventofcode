#include <stdio.h>
#include <sys/time.h>

int main() {
    FILE *input = fopen("input", "r");

    int a, b, c;
    while (!feof(input)) {
        fscanf(input, "%d\n", &a);

        fpos_t pos1;
        fgetpos(input, &pos1);
        while (!feof(input)) {
            fscanf(input, "%d\n", &b);
            if (a + b >= 2020)
                continue;

            fpos_t pos2;
            fgetpos(input, &pos2);
            while (!feof(input)) {
                fscanf(input, "%d\n", &c);
                if (a + b + c == 2020) {
                    printf("result %d\n", a * b * c);
                    return 0;
                }
            }
            fsetpos(input, &pos2);
        }
        fsetpos(input, &pos1);
    }
    puts("no results\n");
    return 0;
}

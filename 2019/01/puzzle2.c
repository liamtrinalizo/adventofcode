#include <stdio.h>

int main() {
    int tot = 0;
    FILE *input = fopen("input", "r");
    while (!feof(input)) {
        int i;
        fscanf(input, "%d\n", &i);
        tot += i/3 - 2;
    }
    printf("total %d", tot);
    return 0;
}

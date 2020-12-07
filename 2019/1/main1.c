#include <stdio.h>

int main() {
    int tot = 0;
    FILE *input = fopen("input", "r");
    while (!feof(input)) {
        int module;
        fscanf(input, "%d\n", &module);
        //TODO negativ is 0

        while (module > 2) {
            module = module/3-2;
            if (module < 0)
                module = 0;
            tot += module;
        }
    }

    printf("total %d", tot);
    return 0;
}

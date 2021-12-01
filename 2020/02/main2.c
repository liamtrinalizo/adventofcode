#include <stdio.h>

int main() {
    int validcount = 0;
    FILE *input = fopen("input", "r");

    while (!feof(input)) {
        int pos1, pos2;
        char letter, password[255];

        fscanf(input, "%d-", &pos1);
        fscanf(input, "%d ", &pos2);
        fscanf(input, "%c:", &letter);
        fscanf(input, "%s\n", password);

        if ((password[pos1 - 1] == letter) != (password[pos2 - 1] == letter))
            validcount++;
    }

    printf("valid count %d\n", validcount);
    return 0;
}

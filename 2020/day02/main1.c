#include <stdio.h>

int main() {
    int validcount = 0;
    FILE *input = fopen("input", "r");

    while (!feof(input)) {
        int min, max;
        char letter, password[255];

        fscanf(input, "%d-", &min);
        fscanf(input, "%d ", &max);
        fscanf(input, "%c:", &letter);
        fscanf(input, "%s\n", password);

        int i=0, charcount = 0;
        while (password[i]) {
            if (password[i] == letter)
                charcount++;
            i++;
        }
        if (charcount <= max && charcount >= min)
            validcount++;

        printf("%d, %d, %c, %d, %s, %s\n", min, max, letter, charcount, 
               charcount <= max && charcount >= min ? "OK" : "NO",
               password);
    }

    printf("valid count %d\n", validcount);
    return 0;
}

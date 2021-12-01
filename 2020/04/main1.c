#include <stdio.h>
#include <string.h>

int main() {
    FILE *input = fopen("input", "r");

    int validcount = 0;
    char fields[8][4] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    while (!feof(input)) {
        char *line = NULL;
        size_t linesize;
        int validatedfields = 0;

        do {
            int ret = getline(&line, &linesize, input);
            if (ret <= 1)
                break;
            printf("%s", line);

            int offset;
            char field[4];
            while (sscanf(line, "%[^:]%n", field, &offset) == 1) {
                line += offset;
                for (int i=0; i < 8; i++) {
                    if (!strcmp(field, fields[i])) {
                        validatedfields |= 1 << i;
                    }
                }
                sscanf(line, ":%s %n", field, &offset);
                line += offset;
            }

        } while (!feof(input));

        printf("--valid %x\n", validatedfields);

        if ((validatedfields & 0x7F) == 0x7F)
        {
            puts("VALID\n");
            validcount++;
        }
    }

    printf("There are %d valid passports\n", validcount);
    return 0;
}

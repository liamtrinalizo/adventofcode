#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int validate(int type, char *data) {
    switch (type) {
        case 0:
            if (atoi(data) >= 1920 && atoi(data) <= 2002)
                return 1;
            break;
        case 1:
            if (atoi(data) >= 2010 && atoi(data) <= 2020)
                return 1;
            break;
        case 2:
            if (atoi(data) >= 2020 && atoi(data) <= 2030)
                return 1;
            break;
        case 3:
            if (data[strlen(data)-1] == 'm') {
                if (atoi(data) >= 150 && atoi(data) <= 193)
                    return 1;
            } else if (data[strlen(data)-1] == 'n') {
                if (atoi(data) >= 59 && atoi(data) <= 76)
                    return 1;
            }
            break;
        case 4: {
            regex_t preg;
            regcomp(&preg, "#[0-9a-f]{6}", 0);
            if (strlen(data) == 7 && regexec(&preg, data, 0, NULL, 0))
                return 1;
            break;
                }
        case 5:
            if (!strcmp(data, "amb") || !strcmp(data, "blu") || !strcmp(data, "brn") || !strcmp(data, "gry") || !strcmp(data, "grn") || !strcmp(data, "hzl") || !strcmp(data, "oth"))
                return 1;
            break;
        case 6: {
            regex_t preg;
            regcomp(&preg, "#[0-9]{9}", 0);
            if (strlen(data) == 9 && regexec(&preg, data, 0, NULL, 0))
                return 1;
            break;
                }
        case 7:
            return 1;
    }
    return 0;
}

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

            int offset;
            char field[4], data[63];
            while (sscanf(line, "%[^:]%n", field, &offset) == 1) {
                line += offset;
                sscanf(line, ":%s %n", data, &offset);
                line += offset;
                for (int i=0; i < 8; i++) {
                    if (!strcmp(field, fields[i])) {
                        printf("field: %s, data: %-10s ", field, data);
                        if (validate(i, data))
                        {
                            puts("VALID");
                            validatedfields |= 1 << i;
                        } else
                            puts("NOK");
                    }
                }
            }

        } while (!feof(input));

        if ((validatedfields & 0x7F) == 0x7F)
            validcount++;
    }

    printf("There are %d valid passports\n", validcount);
    return 0;
}

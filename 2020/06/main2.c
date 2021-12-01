#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int groupsum = 0;
    FILE *input = fopen("input", "r");

    while (!feof(input)) {
        int commoncount = 0, personcount = 0;
        size_t size = 0;
        char *line = NULL, *questions[10], commonchar[255] = {0};

//        questions = malloc(sizeof(char *));
        while (getline(&line, &size, input) > 1) {
//            reallocarray(questions, personcount, sizeof(char *));
            questions[personcount] = calloc(1, strlen(line));
            strncat(questions[personcount], line, strlen(line) - 1);
            personcount++;
            printf("%s", line);
        }

        if (personcount == 1) 
            commoncount += strlen(questions[0]);
        else {
            for (int indexchar = 0; indexchar < strlen(questions[0]); indexchar++) {
                for (int indexmember = 1; indexmember < personcount; indexmember++) {
                    if (index(questions[indexmember], questions[0][indexchar])) {
                        if (indexmember == personcount - 1)
                        {
                            strncat(commonchar, &questions[0][indexchar], 1);
                            commoncount++;
                        }
                    }
                    else
                        break;
                }
            }
        }

        printf("Common count: %d, command chars: %s\n\n", commoncount, commonchar);
        groupsum += commoncount;

        for (int i = 0; i < personcount; i++)
            free(questions[i]);
        //free(questions);
    }

    printf("Count sum %d\n", groupsum);
    return 0;
}

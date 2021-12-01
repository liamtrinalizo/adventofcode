#include <stdio.h>
#include <string.h>

int main() {
    int groupsum = 0;
    FILE *input = fopen("input", "r");

    while (!feof(input)) {
        size_t size = 0;
        char *line = NULL, questions[255] = {0};
        while (getline(&line, &size, input) > 1) {
            for (int i = 0; i < strlen(line); i++) {
                if (line[i] != '\n' && !index(questions, line[i]))
                   strncat(questions, &line[i], 1);
            }
        }
        printf("Size: %d, Answer: %s\n",strlen(questions), questions);
        groupsum += strlen(questions);
    }

    printf("Count sum %d\n", groupsum);
    return 0;
}

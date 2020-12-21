#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *input = fopen("input", "r");
    int acc = 0;
    int correc_count = 0;

    while (!feof(input)) {
        int correc_index = 0;
        int already_exec_line = 0;
        int curr_line = 0;
        int exec_lines_count = 0;
        int *exec_lines = (int *) malloc(sizeof(int));
        acc = 0;
        printf("Correct test %d\n", correc_count);
        rewind(input);

        while (!already_exec_line && !feof(input)) {
            char cmd_text[10], cmd_num[10];
            fscanf(input, "%s %s\n", cmd_text, cmd_num);
            exec_lines_count++;
            exec_lines = reallocarray(exec_lines, exec_lines_count, sizeof(int));
            exec_lines[exec_lines_count - 1] = curr_line;

            if (!strcmp(cmd_text, "jmp") || !strcmp(cmd_text, "nop")) {
                if (correc_index == correc_count) {
                    if (!strcmp(cmd_text, "jmp"))
                        strcpy(cmd_text, "nop");
                    else
                        strcpy(cmd_text, "jmp");
                }
                correc_index++;
            }

            printf("curr line %s %s\n", cmd_text, cmd_num);
            if (!strcmp(cmd_text, "jmp")) {
                curr_line += atoi(cmd_num);
                if (atoi(cmd_num) >= 0) {
                    for (int i = 0; i < atoi(cmd_num) - 1; i++)
                        fscanf(input, "%s %s\n", cmd_text, cmd_text);
                } else {
                    for (int i = 0; i >= atoi(cmd_num) -1; i--) {
                        char c = 'c';
                        do {
                            fseek(input, -2, SEEK_CUR);
                            c = fgetc(input);
                        } while (c != '\n' && ftell(input) > 1);
                    }
                    fseek(input, -1, SEEK_CUR);
                    fscanf(input, "%s %s\n", cmd_text, cmd_text);
                }
            } else {
                curr_line++;
                if (!strcmp(cmd_text, "acc"))
                    acc += atoi(cmd_num);
            }

            //Check if next line was already executed
            for (int i = 0; i < exec_lines_count ; i++) {
                if (curr_line == exec_lines[i]) {
                    already_exec_line = 1;
                    break;
                }
            }
        }
        correc_count++;
        free(exec_lines);
    }
    printf("acc is %d\n", acc);
    return 0;
}

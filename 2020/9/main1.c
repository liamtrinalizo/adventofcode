#include <stdio.h>
#include <stdlib.h>

#define PREAMBLE_SIZE 25

struct list {
    int num;
    struct list *next;
    struct list *prev;
};

int main() {
    FILE *input = fopen("input", "r");
    int num, line_count = 0;
    struct list *prev_num = NULL;

    while (!feof(input)) {
        fscanf(input, "%d\n", &num);
        printf("Read  %d\n", num);

        int found_sum = 0;
        int prev_num_count = 0;
        struct list *prev_num_a = prev_num;
        while (prev_num_a) {
            // Keep linked list size to 25;
            if (prev_num_count == PREAMBLE_SIZE - 1) {
                prev_num_count--;
                free(prev_num_a->prev);
                prev_num_a->prev = NULL;
            }
            prev_num_count++;

            // Search sum of element
            struct list *prev_num_b = prev_num->prev;
            while (prev_num_b) {
                    //printf("test  %d + %d ? %d\n", prev_num_a->num, prev_num_b->num, num);
                if ((prev_num_a != prev_num_b) && (prev_num_a->num + prev_num_b->num == num)) {
                    printf("Match %d + %d = %d\n", prev_num_a->num, prev_num_b->num, num);
                    found_sum = 1;
                    break;
                } else {
                    prev_num_b = prev_num_b->prev;
                }
            }

            prev_num_a = prev_num_a->prev;
        }
        if (!found_sum && line_count >= PREAMBLE_SIZE)
            break;

        line_count++;

        // Add the curr num to linked list
        struct list *elem = (struct list *) malloc(sizeof(struct list));
        elem->num = num;
        elem->prev = prev_num;
        prev_num = elem;
        puts("-----------");
    }
    printf("Num %d does not have a sum\n", num);

    return 0;
}

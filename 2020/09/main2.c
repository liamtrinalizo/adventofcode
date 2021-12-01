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
    struct list *first_num = NULL;

    while (!feof(input)) {
        fscanf(input, "%d\n", &num);

        int found_sum = 0;
        struct list *prev_num_a = prev_num;
        if (line_count >= PREAMBLE_SIZE) {
            for (int i = 0; i < PREAMBLE_SIZE; i++) {
                // Search sum of element
                struct list *prev_num_b = prev_num;
                for (int j = 0; j < PREAMBLE_SIZE; j++) {
                        //printf("test  %d + %d ? %d\n", prev_num_a->num, prev_num_b->num, num);
                    if ((prev_num_a != prev_num_b) && (prev_num_a->num + prev_num_b->num == num)) {
                        //printf("Match %d + %d = %d\n", prev_num_a->num, prev_num_b->num, num);
                        found_sum = 1;
                        break;
                    } else
                        prev_num_b = prev_num_b->prev;
                }
                if (found_sum)
                    break;

                prev_num_a = prev_num_a->prev;
            }
            if (!found_sum)
                break;
        }
        // Add the curr num to linked list
        struct list *elem = (struct list *) malloc(sizeof(struct list));
        elem->num = num;
        elem->prev = prev_num;
        elem->next = NULL;
        if (prev_num)
            prev_num->next = elem;
        prev_num = elem;
        if (!line_count)
            first_num = prev_num;

        line_count++;
    }

    int min, max, sum = 0;
    struct list *elem, *start = first_num;
    while (start && sum != num) {
        sum = 0;
        elem = start;
        min  = start->num;
        max  = start->num;

        while (elem && (sum + elem->num <= num)) {
            if (elem->num < min)
                min = elem->num;
            if (elem->num > max)
                max = elem->num;
            printf("%d + ", elem->num);
            sum += elem->num;
            elem = elem->next;
        }
        printf("= %d", sum);
        printf(" with %d\n", num);
        if (sum == num)
            break;

        start = start->next;
    }
    if (!start)
        puts("Not found");

    printf("Sum of extrem numbers is %d\n", min + max);
    return 0;
}

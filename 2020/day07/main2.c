#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHINY_BAG "shiny gold"

struct bag {
    char *color;
    struct bag **parents;
    int parents_count;
    struct bag **children;
    int children_count;
    int *children_max;
};

struct queue {
    struct bag * data;
    struct queue * next;
};

int main() {
    FILE *input = fopen("input", "r");

    int bag_count, bag_index = 0, shiny_bag_index;
    struct bag head_bag;
    while (!feof(input)) {
        size_t size = 0;
        char *line = NULL, bag_color[255];
        int bag_max, offset;

        getline(&line, &size, input);
        sscanf(line, "%s%n", bag_color, &offset);
        line += offset;
        strcat(bag_color, " ");
        sscanf(line, "%s%n", bag_color + offset + 1, &offset);
        line += offset + strlen("bags contain");

        struct bag *curr_bag = (struct bag *) malloc(sizeof(struct bag));
        if (!bag_index)
            head_bag.children = malloc(sizeof(struct bag *));
        else
            head_bag.children = reallocarray(head_bag.children, bag_index + 1, sizeof(struct bag *));
        head_bag.children[bag_index] = curr_bag;
        curr_bag->parents_count = 0;
        curr_bag->children_count  = 0;
        curr_bag->children  = NULL;
        curr_bag->parents = NULL;
        curr_bag->children_max = NULL;

        curr_bag->color = (char *) malloc(sizeof(char)*(strlen(bag_color)));
        strcpy(curr_bag->color, bag_color);

        if (!strcmp(bag_color, SHINY_BAG))
            shiny_bag_index = bag_index;

        while (!feof(input) && sscanf(line, "%d %s%n", &bag_max, bag_color, &offset) == 2) {
            line += offset;
            strcat(bag_color, " ");
            sscanf(line, "%s%n", bag_color + strlen(bag_color), &offset);
            line += offset + strlen("bags,");
        }
        bag_index++;
    }
    bag_count = bag_index;
    rewind(input);

    bag_index = 0;
    while (!feof(input)) {
        size_t size = 0;
        char *line = NULL, bag_color[255];
        int bag_max, offset;

        getline(&line, &size, input);
        sscanf(line, "%s%n", bag_color, &offset);
        line += offset;
        strcat(bag_color, " ");
        sscanf(line, "%s%n", bag_color + offset + 1, &offset);
        line += offset + strlen("bags contain ");

        struct bag *curr_bag = head_bag.children[bag_index];

        while (!feof(input) && sscanf(line, "%d %s%n", &bag_max, bag_color, &offset) == 2) {
            line += offset;
            strcat(bag_color, " ");
            sscanf(line, "%s%n", bag_color + strlen(bag_color), &offset);
            line += offset + 1;

            while (*line != ' ' && *line != 0)
                line++;
            if (*line)
                line++;

            int sub_bag_index = 0;
            while ((sub_bag_index < bag_count) && strcmp(head_bag.children[sub_bag_index]->color, bag_color))
                sub_bag_index++;

            struct bag *curr_sub_bag = head_bag.children[sub_bag_index];
            if (!curr_bag->children)
                curr_bag->children  = (struct bag **) malloc(sizeof(struct bag *));
            else
                curr_bag->children = reallocarray(curr_bag->children, curr_bag->children_count + 1, sizeof(struct bag *));
            curr_bag->children[curr_bag->children_count] = curr_sub_bag;

            if (!curr_bag->children_max)
                curr_bag->children_max = (int *) malloc(sizeof(int));
            else
                curr_bag->children_max = reallocarray(curr_bag->children_max, curr_bag->children_count + 1, sizeof(int));
            curr_bag->children_max[curr_bag->children_count] = bag_max;

            if (!curr_sub_bag->parents)
                curr_sub_bag->parents = (struct bag **) malloc(sizeof(struct bag *));
            else
                curr_sub_bag->parents = reallocarray(curr_sub_bag->parents, curr_sub_bag->parents_count + 1, sizeof(struct bag *));
            curr_sub_bag->parents[curr_sub_bag->parents_count] = curr_bag;

            curr_bag->children_count++;
            curr_sub_bag->parents_count++;
        }
        bag_index++;
    }

    int inner_bag_count = -1;
    struct queue *bag_queue = (struct queue *)malloc(sizeof(struct queue));
    bag_queue->data = head_bag.children[shiny_bag_index];
    bag_queue->next = NULL;
    while (bag_queue) {
        struct bag * curr_bag = bag_queue->data;
        bag_queue = bag_queue->next;
        inner_bag_count++;

        printf("color %s\n", curr_bag->color, curr_bag->parents_count);

        for (int i=0; i < curr_bag->children_count; i++) {
            for (int j=0; j < curr_bag->children_max[i]; j++) {
                struct queue *tmp = bag_queue;
                bag_queue = (struct queue *)malloc(sizeof(struct queue));
                bag_queue->data = curr_bag->children[i];
                bag_queue->next = tmp;
            }
        }
    }
    printf("Outer bag count: %d\n", inner_bag_count);

    return 0;
}

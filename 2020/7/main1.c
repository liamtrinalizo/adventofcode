#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHINY_BAG "shiny gold"

struct bag {
    char *color;
    struct bag **parents;
    int parents_count;
    struct bag **childs;
    int childs_count;
    int *childs_max;
};

int main() {
    FILE *input = fopen("input", "r");

    int bag_index = 0, shiny_bag_index;
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
        line += offset + sizeof("bags contain");

        struct bag *curr_bag = (struct bag *) malloc(sizeof(struct bag));
        head_bag.childs = reallocarray(head_bag.childs, bag_index + 1, sizeof(struct bag *));
        head_bag.childs[bag_index] = curr_bag;
        curr_bag->parents_count = 0;
        curr_bag->childs_count  = 0;
        curr_bag->childs  = NULL;
        curr_bag->parents = NULL;

        curr_bag->color = (char *) malloc(sizeof(char)*(strlen(bag_color)));
        strcpy(curr_bag->color, bag_color);

        if (strcmp(bag_color, SHINY_BAG))
            shiny_bag_index = bag_index;

        while (!feof(input) && sscanf(line, "%d %s%n", &bag_max, bag_color, &offset) == 2) {
            line += offset;
            strcat(bag_color, " ");
            sscanf(line, "%s%n", bag_color + strlen(bag_color), &offset);
            line += offset + sizeof("bags,");
        }
        bag_index++;
    }
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
        line += offset + sizeof("bags contain");

        int child_count = 0;
        while (!feof(input) && sscanf(line, "%d %s%n", &bag_max, bag_color, &offset) == 2) {
            line += offset;
            strcat(bag_color, " ");
            sscanf(line, "%s%n", bag_color + strlen(bag_color), &offset);
            line += offset + sizeof("bags,");

            struct bag *curr_bag = head_bag.childs[bag_index];

            int sub_bag_index = 0;
            while (strcmp(head_bag.childs[sub_bag_index]->color, bag_color))
                sub_bag_index++;

            struct bag *curr_sub_bag = head_bag.childs[sub_bag_index];
            if (!curr_bag->childs)
                curr_bag->childs  = (struct bag **) malloc(sizeof(struct bag *));
            if (!curr_bag->parents)
                curr_bag->parents = (struct bag **) malloc(sizeof(struct bag *));
            curr_bag->childs = reallocarray(curr_bag->childs, child_count + 1, sizeof(struct bag *));
            curr_bag->childs[child_count] = curr_sub_bag;
            curr_sub_bag->parents = reallocarray(curr_sub_bag->parents, curr_sub_bag->parents_count + 1, sizeof(struct bag *));
            curr_sub_bag->parents[curr_sub_bag->parents_count] = curr_bag;

            curr_bag->childs_count++;
            curr_sub_bag->parents_count++;

            child_count++;
        }
        bag_index++;
    }

    int outer_bag_count = 0, bag_queue_count = 1;
    struct bag *curr_bag = head_bag->childs[shiny_bag_index];
    struct bag **bag_queue =
    while (curr_bag->parents) {
        outer_bag_count
        curr_bag = curr_bag;

    }
    printf("Bag count: %d\n", outer_bag_count);

    return 0;
}

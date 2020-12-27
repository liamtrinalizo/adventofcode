#include <stdio.h>
#include <string.h>

#define CYCLE_COUNT 6
#define INPUT_SIZE 8
#define Z_HIDDEN 5
#define X_SIZE 32
#define Y_SIZE 32
#define Z_SIZE 31

int active_neighbors(char map[X_SIZE][Y_SIZE][Z_SIZE], int pos_x, int pos_y, int pos_z) {
    int active_count = 0, count = 0;
    for (int index_x = pos_x > 0 ? pos_x - 1 : pos_x; index_x <= (pos_x < X_SIZE - 1 ? pos_x + 1 : pos_x); index_x++) {
        for (int index_y = pos_y > 0 ? pos_y - 1 : pos_y; index_y <= (pos_y < Y_SIZE - 1 ? pos_y + 1 : pos_y); index_y++) {
            for (int index_z = pos_z > 0 ? pos_z - 1 : pos_z; index_z <= (pos_z < Z_SIZE - 1 ? pos_z + 1 : pos_z); index_z++) {
                count++;
                if (index_x == pos_x && index_y == pos_y && index_z == pos_z)
                    continue;
                if (map[index_x][index_y][index_z] == '#')
                    active_count++;
            }
        }
    }
    return active_count;
}

int main() {
    FILE *input = fopen("input", "r");
    char map[X_SIZE][Y_SIZE][Z_SIZE]; // x y z
    char tmp[X_SIZE][Y_SIZE][Z_SIZE]; // x y z
    memset(map, '.', X_SIZE*Y_SIZE*Z_SIZE);
    memset(tmp, '.', X_SIZE*Y_SIZE*Z_SIZE);

    // Init array with input data
    int line_count = 0;
    while (!feof(input)) {
        char line[9];
        fscanf(input, "%s\n", line);
        for (int i = 0; i < INPUT_SIZE; i++)
            map[X_SIZE/2 - INPUT_SIZE/2 + i][Y_SIZE/2 - INPUT_SIZE/2 + line_count][Z_SIZE/2] = line[i];

        line_count++;
    }

    int active_count;
    for (int index_cycle = 0; index_cycle < CYCLE_COUNT; index_cycle++) {
        active_count = 0;
        printf("Cycle n %d\n", index_cycle + 1);
        for (int index_y = -1; index_y < Y_SIZE; index_y++) {
            for (int index_z = Z_HIDDEN; index_z < Z_SIZE - Z_HIDDEN; index_z++) {
                for (int index_x = 0; index_x < X_SIZE; index_x++) {
                    if (index_y == -1) {
                        printf("%d", index_x % 10);
                        continue;
                    }
                    int neighbors = active_neighbors(map, index_x, index_y, index_z);
                    if (map[index_x][index_y][index_z] == '#' && neighbors > 1 && neighbors < 4) {
                        tmp[index_x][index_y][index_z] = '#';
                        active_count++;
                    } else if (map[index_x][index_y][index_z] == '.' && neighbors == 3) {
                        tmp[index_x][index_y][index_z] = '#';
                        active_count++;
                    } else
                        tmp[index_x][index_y][index_z] = '.';
               //     if (neighbors)
               //         printf("%d", neighbors);
               //     else
               //         printf(".");
                    printf("%c", tmp[index_x][index_y][index_z]);
                }
                if (index_y >= 0)
                    printf("%2d",index_y);
                else
                    printf("  ");
            }
            puts("");
        }
        memcpy(map, tmp, X_SIZE*Y_SIZE*Z_SIZE);
    }

    printf("There %d active cubes\n", active_count);
    return 0;
}

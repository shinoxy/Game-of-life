#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define HEIGHT 25
#define WIDTH 80

void choose_column(int **map);
void speed(int *pause);
void render_map(int **map);
int get_neighbor_count(int **map, int row, int col);
void calculate(int **map);

int main() {
    int** map = malloc(HEIGHT * sizeof(int*));
        for (int i = 0; i < HEIGHT; i++) {
            map[i] = malloc(WIDTH * sizeof(int));
        }
    int pause;
    choose_column(map);
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("n/a");
    } else {
        speed(&pause);
        render_map(map);
        for (int i = 0; i < 100000; i++) {
            calculate(map);
            render_map(map);
            usleep(pause);
        }
    }
    for (int i = 0; i < HEIGHT; i++)
        free(map[i]);
    free(map);

    return 0;
}

void choose_column(int **map) {
    for (int rows = 0; rows < HEIGHT; rows++)
        for (int cols = 0; cols < WIDTH; cols++) {
            scanf("%d", &map[rows][cols]);
        }
}

void speed(int *pause) {
    int speed;
    printf("\nPlease, select game speed:\n\n");
    printf("1 - ultra slow\n2 - slow\n3 - normal\n");
    printf("4 - fast\n5 - ultra fast\n\n");
    scanf("%d", &speed);
    switch (speed) {
        case 1:
            *pause = 1500000;
            break;
        case 2:
            *pause = 1000000;
            break;
        case 3:
            *pause = 500000;
            break;
        case 4:
            *pause = 100000;
            break;
        case 5:
            *pause = 50000;
            break;
        default:
            *pause = 50000;
            printf("Incorrect value. Your speed set as extra fast by default.\n");
            usleep(2000000);
            break;
    }
}

void render_map(int **map) {
    for (int rows = 0; rows < HEIGHT; rows++) {
        for (int cols = 0; cols < WIDTH; cols++) {
            if (map[rows][cols] == 1) {
                printf("o");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int get_neighbor_count(int **map, int row, int col) {
    int neighbor = 0;
    neighbor += map[(row + HEIGHT - 1) % HEIGHT][(col + WIDTH - 1) % WIDTH];
    neighbor += map[(row + HEIGHT - 1) % HEIGHT][col];
    neighbor += map[(row + HEIGHT - 1) % HEIGHT][(col + WIDTH + 1) % WIDTH];
    neighbor += map[row][(col + WIDTH - 1) % WIDTH];
    neighbor += map[row][(col + WIDTH + 1) % WIDTH];
    neighbor += map[(row + HEIGHT + 1) % HEIGHT][(col + WIDTH - 1) % WIDTH];
    neighbor += map[(row + HEIGHT + 1) % HEIGHT][col];
    neighbor += map[(row + HEIGHT + 1) % HEIGHT][(col + WIDTH + 1) % WIDTH];
    return neighbor;
}



void calculate(int **map) {
    int map_1[HEIGHT][WIDTH];
    int neighbor;
    for (int height = 0; height < HEIGHT; height++) {
        for (int width = 0; width < WIDTH; width++) {
            neighbor = get_neighbor_count(map, height, width);
            if (neighbor == 3) {
                map_1[height][width] = 1;
            } else if (neighbor == 2 && map[height][width] == 1) {
                map_1[height][width] = 1;
            } else {
                map_1[height][width] = 0;
            }
        }
    }
    for (int height = 0; height < HEIGHT; height++) {
        for (int width = 0; width < WIDTH; width++) {
            map[height][width] = map_1[height][width];
        }
    }
}

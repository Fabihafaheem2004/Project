#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define V 21
#define H 75
#define N 100

typedef struct {
    int x, y; // initial position
    int movX, movY;
    char imagen;
} snake;

typedef struct {
    int x, y;
} fhe;

snake snk[N]; // maximum size
fhe fruit;

void begin(int* size, char map[V][H]);
void intro(char map[V][H]);
void intro_data(char map[V][H], int* size);
void gameLoop(char map[V][H], int* size, int* score);
void input(char map[V][H], int* size, int* dead, int* score);
void update(char map[V][H], int* size, int* score);
void intro_data2(char map[V][H], int* size);

void gotoxy(int x, int y);
void clearScreen();

void show(char map[V][H], int score);

int main() {
    int size, score = 0;
    char map[V][H];

    begin(&size, map);
    show(map, score);
    system("pause");
    gameLoop(map, &size, &score);

    system("pause");
    return 0;
}

void begin(int* size, char map[V][H]) {
    int i;

    // snake head
    snk[0].x = 32;
    snk[0].y = 10;

    // snake body
    *size = 4;

    srand(time(NULL));

    fruit.x = rand() % (H - 2) + 1;
    fruit.y = rand() % (V - 2) + 1;

    for (i = 0; i < *size; i++) {
        snk[i].movX = 1;
        snk[i].movY = 0;
    }

    intro(map);
    intro_data(map, size);
}

void show(char map[V][H], int score) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < H; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void intro(char map[V][H]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < H; j++) {
            if (i == 0 || i == V - 1 || i == 5 || i == V - 6) {
                map[i][j] = '-';
            } else if (j == 0 || j == H - 1 || j == 10 || j == H - 11) {
                map[i][j] = '|';
            } else {
                map[i][j] = ' ';
            }
        }
    }
}

void intro_data(char map[V][H], int* size) {
    int i;
    for (i = 1; i < *size; i++) {
        snk[i].x = snk[i - 1].x - 1;
        snk[i].y = snk[i - 1].y;
        snk[i].imagen = 'X';
    }
    snk[0].imagen = 'O';

    for (i = 0; i < *size; i++) {
        map[snk[i].y][snk[i].x] = snk[i].imagen;
    }

    map[fruit.y][fruit.x] = 'f';
}

void gameLoop(char map[V][H], int* size, int* score) {
    int dead = 0;
    do {
        clearScreen();
        show(map, *score);
        input(map, size, &dead, score);
        update(map, size, score);
    } while (!dead);
}

void input(char map[V][H], int* size, int* dead, int* score) {
    int i;
    char key;

    if (snk[0].x == 0 || snk[0].x == H - 1 || snk[0].y == 0 || snk[0].y == V - 1) {
        *dead = 1;
    }

    for (i = 1; i < *size && !*dead; i++) {
        if (snk[0].x == snk[i].x && snk[0].y == snk[i].y) {
            *dead = 1;
        }
    }

    if (snk[0].x == fruit.x && snk[0].y == fruit.y) {
        *size += 1;
        snk[*size - 1].imagen = 'X';
        fruit.x = rand() % (H - 2) + 1;
        fruit.y = rand() % (V - 2) + 1;
        *score += 10; // Increase the score when the snake eats a fruit
    }

    if (!*dead) {
        if (_kbhit()) {
            key = _getch();
            if (key == 's' && snk[0].movY != -1) {
                snk[0].movX = 0;
                snk[0].movY = 1;
            }
            if (key == 'w' && snk[0].movY != 1) {
                snk[0].movX = 0;
                snk[0].movY = -1;
            }
            if (key == 'a' && snk[0].movX != 1) {
                snk[0].movX = -1;
                snk[0].movY = 0;
            }
            if (key == 'd' && snk[0].movX != -1) {
                snk[0].movX = 1;
                snk[0].movY = 0;
            }
        }
    }
}

void update(char map[V][H], int* size, int* score) {
    intro(map);
    intro_data2(map, size);
}

void intro_data2(char map[V][H], int* size) {
    int i;
    for (i = *size - 1; i > 0; i--) {
        snk[i].x = snk[i - 1].x;
        snk[i].y = snk[i - 1].y;
    }
    snk[0].x += snk[0].movX;
    snk[0].y += snk[0].movY;

    for (i = 0; i < *size; i++) {
        map[snk[i].y][snk[i].x] = snk[i].imagen;
    }

    map[fruit.y][fruit.x] = 'f';
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    system("cls");
}
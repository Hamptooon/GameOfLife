#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WORLD_HEIGHT 25
#define WORLD_WIDTH 80
void displayWorld(char world[WORLD_HEIGHT][WORLD_WIDTH]);
void initialWorld(char world[WORLD_HEIGHT][WORLD_WIDTH]);
void update(char world[WORLD_HEIGHT][WORLD_WIDTH], char previous_world[WORLD_HEIGHT][WORLD_WIDTH],
            char liveCell, char deadCell);
void copyArray(char array[WORLD_HEIGHT][WORLD_WIDTH], char copyArray[WORLD_HEIGHT][WORLD_WIDTH]);
int neighoursCell(char world[WORLD_HEIGHT][WORLD_WIDTH], char liveCell, int i, int j);
int isDifffereWorlds(char world[WORLD_HEIGHT][WORLD_WIDTH], char previous_world[WORLD_HEIGHT][WORLD_WIDTH]);
int chooseInitialaState();
void displayStartMenu();
void clearInputBuffer();
int chooseSpeed();
void endGeneration();
int main(void) {
    char orirginWorld[WORLD_HEIGHT][WORLD_WIDTH];
    char world[WORLD_HEIGHT][WORLD_WIDTH];
    char previous_world[WORLD_HEIGHT][WORLD_WIDTH];
    char liveCell = '*';
    char deadCell = '.';
    int speed = 0;
    int isEnd = 1;
    printf("\033[H\033[J");
    while (isEnd == 1) {
        displayStartMenu();
        isEnd = chooseInitialaState();
    }
    printf("1");
    initialWorld(orirginWorld);
    while (speed == 0) {
        displayStartMenu();
        speed = chooseSpeed();
    }
    copyArray(orirginWorld, world);
    while (isEnd == 0) {
        displayWorld(world);
        usleep(speed);
        update(world, previous_world, liveCell, deadCell);
        if (!isDifffereWorlds(world, previous_world) || !isDifffereWorlds(orirginWorld, world)) {
            isEnd = 1;
        }
        usleep(speed);
    }
    endGeneration();
    return 0;
}
void displayWorld(char world[WORLD_HEIGHT][WORLD_WIDTH]) {
    system("clear");
    printf("\n");
    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            printf("\033[1m%c\033[1m", world[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void initialWorld(char world[WORLD_HEIGHT][WORLD_WIDTH]) {
    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            scanf("\t%c", &(world[i][j]));
            if (world[i][j] == '\n') {
                j--;
                ;
            }
        }
    }
    (void)freopen("/dev/tty", "r", stdin);
}

void update(char world[WORLD_HEIGHT][WORLD_WIDTH], char previous_world[WORLD_HEIGHT][WORLD_WIDTH],
            char liveCell, char deadCell) {
    char updateWorld[WORLD_HEIGHT][WORLD_WIDTH];
    copyArray(world, updateWorld);

    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            int liveNeighbours = neighoursCell(world, liveCell, i, j);
            if (world[i][j] == liveCell) {
                liveNeighbours--;
                if (liveNeighbours < 2 || liveNeighbours > 3) {
                    updateWorld[i][j] = deadCell;
                }

            } else {
                if (liveNeighbours == 3) {
                    updateWorld[i][j] = liveCell;
                }
            }
        }
    }
    copyArray(world, previous_world);
    copyArray(updateWorld, world);
}

void copyArray(char array[WORLD_HEIGHT][WORLD_WIDTH], char copyArray[WORLD_HEIGHT][WORLD_WIDTH]) {
    for (int i = 0; i < WORLD_HEIGHT; i++) {
        for (int j = 0; j < WORLD_WIDTH; j++) {
            copyArray[i][j] = array[i][j];
        }
    }
}

int neighoursCell(char world[WORLD_HEIGHT][WORLD_WIDTH], char liveCell, int i, int j) {
    int liveNeighbours = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            int ni = (i + y + WORLD_HEIGHT) % WORLD_HEIGHT;
            int nj = (j + x + WORLD_WIDTH) % WORLD_WIDTH;
            if (world[ni][nj] == liveCell) {
                liveNeighbours++;
            }
        }
    }
    return liveNeighbours;
}
int isDifffereWorlds(char world[WORLD_HEIGHT][WORLD_WIDTH], char previous_world[WORLD_HEIGHT][WORLD_WIDTH]) {
    int isDifferentWorlds = 0;
    for (int i = 0; i < WORLD_HEIGHT && !isDifferentWorlds; i++) {
        for (int j = 0; j < WORLD_WIDTH && !isDifferentWorlds; j++) {
            if (world[i][j] != previous_world[i][j]) {
                isDifferentWorlds = 1;
            }
        }
    }
    return isDifferentWorlds;
}

int chooseInitialaState() {
    printf("------------------------------------------------------------------------------------\n");
    printf("|                        ВЫБЕРИТЕ НАЧАЛЬНОЕ СОСТОЯНИЕ МИРА                         |\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("|  1 РУЖЬЕ v.1\t|  2 ГЛАЙДЕРЫ И Т.Д|  3 ПЧЕЛИНАЯ КОРОЛЕВА|  4 СТАТИЧЕСКОЕ\t|  5 РАНДОМНОЕ|\n");
    printf("------------------------------------------------------------------------------------\n");

    char initialStateNumber;
    char c;
    int isIncorrectInput = 0;

    if (scanf("%c%c", &initialStateNumber, &c) == 2 && initialStateNumber <= '5' &&
        initialStateNumber >= '1' && c == '\n') {
        if (initialStateNumber == '1') {
            (void)freopen("initialState1.txt", "r", stdin);
        }
        if (initialStateNumber == '2') {
            (void)freopen("initialState2.txt", "r", stdin);
        }
        if (initialStateNumber == '3')

        {
            (void)freopen("initialState3.txt", "r", stdin);
        }
        if (initialStateNumber == '4') {
            (void)freopen("initialState4.txt", "r", stdin);
        }
        if (initialStateNumber == '5') {
            (void)freopen("initialState5.txt", "r", stdin);
        }
    } else {
        isIncorrectInput = 1;
        clearInputBuffer();
    }

    return isIncorrectInput;
}

void displayStartMenu() {
    // system("clear");
    printf("\033[H\033[J");
    printf("\n\033[1m  GGGG   A    M     M  EEEEE       OOO    FFFFF        L          III  FFFFF  EEEEE\n");
    printf("\033[1m G       A A   MM   MM  E          O   O   F           L           I   F      E    \n");
    printf("\033[1m G  GGG A   A  M M M M  EEEE       O   O   FFFF        L           I   FFFF   EEEE \n");
    printf("\033[1m G   G  AAAAA  M  M  M  E          O   O   F           L           I   F      E    \n");
    printf("\033[1m  GGGG  A   A  M     M  EEEEE       OOO    F           LLLLL      III  F      EEEEE\n");
    printf("\n------------------------------------------------------------------------------------\n");
    printf("|                                   \033[1mИГРА «ЖИЗНЬ»                                   |\n");
}
int chooseSpeed() {
    char speedMode = 0;
    char c;
    int speed = 0;
    printf("------------------------------------------------------------------------------------\n");
    printf("|                             ВЫБЕРИТЕ СКОРОСТЬ ГЕНЕРАЦИИ                          |\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("|    1 : МЕДЛЕННАЯ       2 : СРЕДНЯЯ           3 БЫСТРАЯ          4 ОЧЕНЬ БЫСТРАЯ  |\n");
    printf("------------------------------------------------------------------------------------\n");

    if (scanf("%c%c", &speedMode, &c) == 2 && speedMode <= '5' && speedMode >= '1' && c == '\n') {
        if (speedMode == '1') {
            speed = 1000000;
        }
        if (speedMode == '2') {
            speed = 500000;
        }
        if (speedMode == '3') {
            speed = 150000;
        }
        if (speedMode == '4') {
            speed = 50000;
        }
    } else {
        speed = 0;
        clearInputBuffer();
    }
    return speed;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void endGeneration() {
    printf("\n\n");
    printf("╔═══╦╗─╔╦══╗\n");
    printf("║╔══╣╚═╝║╔╗╚╗\n");
    printf("║╚══╣╔╗─║║╚╗║\n");
    printf("║╔══╣║╚╗║║─║║\n");
    printf("║╚══╣║─║║╚═╝║\n");
    printf("╚═══╩╝─╚╩═══╝\n");
    printf("╔═══╦═══╦╗─╔╦═══╦═══╦══╦════╦══╦══╦╗─╔╗\n");
    printf("║╔══╣╔══╣╚═╝║╔══╣╔═╗║╔╗╠═╗╔═╩╗╔╣╔╗║╚═╝║\n");
    printf("║║╔═╣╚══╣╔╗─║╚══╣╚═╝║╚╝║─║║──║║║║║║╔╗─║\n");
    printf("║║╚╗║╔══╣║╚╗║╔══╣╔╗╔╣╔╗║─║║──║║║║║║║╚╗║\n");
    printf("║╚═╝║╚══╣║─║║╚══╣║║║║║║║─║║─╔╝╚╣╚╝║║─║║\n");
    printf("╚═══╩═══╩╝─╚╩═══╩╝╚╝╚╝╚╝─╚╝─╚══╩══╩╝─╚╝\n");
    printf("\n\n");
}
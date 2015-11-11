#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ROWS 50
#define COLS 70

#define STAT_EDITING 0
#define STAT_PLAYING 1

#define DELAY_MIN 10
#define DELAY_MAX 1000
#define DELAY_STEP 10

void board_draw(void);
void game_draw(void);
void game_exit(void);
void game_init(int, char*[]);
void game_loop(void);
void game_step(void);
void game_update(void);
void matrix_change(void);
int  matrix_count_neighbors(int, int);
void matrix_init(void);
void matrix_read(const char *, int, int);
void matrix_update(void);
bool matrix_valid_position(int, int);
void panel_draw(void);
void usage(const char*);

bool matrix[ROWS][COLS];
bool u_matrix[ROWS][COLS];
bool running;
static char *texts[] = {
    "p -> Play/Pause",
    "c -> Toggle cell",
    "C -> Clear Matrix",
    "i -> Increase speed",
    "d -> Decrease speed",
    "",
    "h -> Left",
    "j -> Down",
    "k -> Up",
    "l -> Right",
    "",
    "q -> Quit"
};
#define SIZE_TEXTS 12
int game_delay;
int stat;
struct timeval before;
struct timeval now;
WINDOW *main_window;
WINDOW *panel_window;

int main(int argc, char *argv[]) {
    game_init(argc, argv);
    while (running) game_loop();
    game_exit();
    return 0;
}

void board_draw(void) {
    int i, j;
    int x = getcurx(main_window);
    int y = getcury(main_window);
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++) {
            wmove(main_window, i, j*2);
            if (matrix[i][j]) waddch(main_window, 'X');
            else {
                waddch(main_window, ' ');
                waddch(main_window, '.');
            }
        }
    wmove(main_window, y, x);
    wrefresh(main_window);
}

void game_init(int argc, char *argv[]) {
    game_delay = (DELAY_MIN+DELAY_MAX)/2;
    stat = STAT_EDITING;
    running = true;

    int c;
    int x = 0;
    int y = 0;
    const char *path = NULL;
    while ((c = getopt(argc, argv, "hp:x:y:s:")) != -1) {
        switch (c) {
            case 'p': path = optarg; break;
            case 'x': x = atoi(optarg); break;
            case 'y': y = atoi(optarg); break;
            case 's': game_delay = DELAY_MAX - (atoi(optarg) - 1)*10; break;
            case 'h':
                usage(argv[0]);
                exit(-1);
                break;
        }
    }
    if (path) matrix_read(path, x, y);
    else matrix_init();

    initscr();

    noecho();
    cbreak();

    main_window = newwin(ROWS, COLS*2, 0, 0);
    panel_window = newwin(ROWS, COLS, 0, COLS*2+1);
    nodelay(main_window, true);
    nodelay(panel_window, true);
    panel_draw();
}

void game_exit(void) {
    endwin();
}

void game_loop(void) {
    game_update();
    game_draw();
    if (stat == STAT_PLAYING) game_step();
}

void game_update(void) {
    int ch = wgetch(main_window);
    while (ch != ERR) {
        switch (ch) {
            case 'q': running = false; break;
            case 'h': wmove(main_window, getcury(main_window), getcurx(main_window)-2); break;
            case 'j': wmove(main_window, getcury(main_window)+1, getcurx(main_window)); break;
            case 'k': wmove(main_window, getcury(main_window)-1, getcurx(main_window)); break;
            case 'l': wmove(main_window, getcury(main_window), getcurx(main_window)+2); break;
            case 'c': matrix_change(); break;
            case 'C': matrix_init(); break;
            case 'i': if (game_delay - DELAY_STEP > DELAY_MIN) game_delay -= DELAY_STEP; panel_draw(); break;
            case 'd': if (game_delay + DELAY_STEP < DELAY_MAX) game_delay += DELAY_STEP; panel_draw(); break;
            case 'p': stat = !stat; break;
        }
        ch = wgetch(main_window);
    }
}

void game_draw(void) {
    board_draw();
}

void game_step(void) {
    int x = getcurx(main_window);
    int y = getcury(main_window);
    wmove(panel_window, 0, 0);
    matrix_update();
    gettimeofday(&now, NULL);
    int time = game_delay - (now.tv_usec - before.tv_usec)/1000.0;
    if (time > 0) delay_output(time);
    gettimeofday(&before, NULL);
    wmove(main_window, y, x);
}

void matrix_init(void) {
    int i, j;
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            matrix[i][j] = false;
}

void matrix_change() {
    int j = getcurx(main_window)/2;
    int i = getcury(main_window);
    matrix[i][j] = !matrix[i][j];
}

bool matrix_valid_position(int i, int j) {
    return i >= 0 && i < ROWS &&
        j >= 0 && j < COLS;
}

int matrix_count_neighbors(int x, int y) {
    int count = 0;
    int i, j;
    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
            if (!(i==0 && j==0))
                if (matrix_valid_position(x+i, y+j) && matrix[x+i][y+j]) count++;
    return count;
}

void matrix_read(const char *path, int x, int y) {
    int i = 0;
    int j = 0;
    FILE *f = fopen(path, "r");
    while (!feof(f)) {
        int c = fgetc(f);
        switch (c) {
            case '1': matrix[y+i][x+j] = true;  j++; break;
            case '0': matrix[y+i][x+j] = false; j++; break;
            case '\n':
                      i++;
                      j = 0;
                      break;
        }
    }
    fclose(f);
}

void matrix_update(void) {
    memcpy(u_matrix, matrix, sizeof(bool)*COLS*ROWS);
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            int v = matrix_count_neighbors(i, j);
            if (matrix[i][j] && (v < 2 || v > 3)) u_matrix[i][j] = false;
            else if (v == 3 && !matrix[i][j]) u_matrix[i][j] = true;
        }
    }
    memcpy(matrix, u_matrix, sizeof(bool)*COLS*ROWS);
}

void panel_draw(void) {
    int i;
    for (i = 0; i < SIZE_TEXTS; i++) {
        wmove(panel_window, i, 0);
        waddstr(panel_window, texts[i]);
    }
    wmove(panel_window, SIZE_TEXTS+1, 0);
    char buff[24];
    sprintf(buff, "SPEED: %d    ",  (DELAY_MAX - game_delay)/10 + 1);
    waddstr(panel_window, buff);
    wrefresh(panel_window);
}

void usage(const char *name) {
    printf("USAGE:\n");
    printf("\t%s [-p preset [-x X] [-y Y]] [-s SPEED]\n", name);
    printf("where:\n");
    printf("\tpreset: File containing a preset with a matrix of 0's and 1's\n");
    printf("\tX: Read the preset file from coordinate X\n");
    printf("\tY: Read the preset file from coordinate Y\n");
    printf("\tSPEED: The speed between two steps in play mode\n");
}
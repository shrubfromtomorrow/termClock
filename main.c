#include <curses.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

void drawTime();

void getCurrentTime(char *str);

char Zero[9][49] = {"█████████████ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "█████████████ "};

char One[9][49] = {"████████      ",
                   "     ███      ",
                   "     ███      ",
                   "     ███      ",
                   "     ███      ",
                   "     ███      ",
                   "     ███      ",
                   "     ███      ",
                   "█████████████ "};

char Two[9][49] = {"█████████████ ",
                   "          ███ ",
                   "          ███ ",
                   "          ███ ",
                   "█████████████ ",
                   "███           ",
                   "███           ",
                   "███           ",
                   "█████████████ "};

char Three[9][49] = {"█████████████ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "  ███████████ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "█████████████ "};

char Four[9][49] = {"███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "█████████████ ",
                    "          ███ ",
                    "          ███ ",
                    "          ███ ",
                    "          ███ "};

char Five[9][49] = {"█████████████ ",
                    "███           ",
                    "███           ",
                    "███           ",
                    "█████████████ ",
                    "          ███ ",
                    "          ███ ",
                    "          ███ ",
                    "█████████████ "};

char Six[9][49] = {"█████████████ ",
                   "███           ",
                   "███           ",
                   "███           ",
                   "█████████████ ",
                   "███       ███ ",
                   "███       ███ ",
                   "███       ███ ",
                   "█████████████ "};
        
char Seven[9][49] = {"█████████████ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ ",
                     "          ███ "};

char Eight[9][49] = {"█████████████ ",
                     "███       ███ ",
                     "███       ███ ",
                     "███       ███ ",
                     "█████████████ ",
                     "███       ███ ",
                     "███       ███ ",
                     "███       ███ ",
                     "█████████████ ",};

char Nine[9][49] = {"█████████████ ",
                    "███       ███ ",
                    "███       ███ ",
                    "███       ███ ",
                    "█████████████ ",
                    "          ███ ",
                    "          ███ ",
                    "          ███ ",
                    "          ███ "};

char Colon[9][14] = {"     ",
                     "████ ",
                     "████ ",
                     "     ",
                     "     ",
                     "     ",
                     "████ ",
                     "████ ",
                     "     "};

char chars[9];

int main() {
    drawTime();
    return 0; 
}

void getCurrentTime(char *str) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(str, 10, "%H:%M:%S", tm_info);
}

void drawTime() {
    setlocale(LC_ALL, "");
    initscr(); /* Start curses mode 		  */
    // start_color();

    curs_set(0);

    while (true) {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        char whiteSpaceCol[w.ws_col / 2 - (94 / 2) + 1];

        for (int i = 0; i<w.ws_col / 2 - (94 / 2); i++) {
            whiteSpaceCol[i] = ' ';
        }

        char whiteSpaceRow[w.ws_row / 2 - 4 + 1];

        for (int i = 0; i<w.ws_row / 2 - 4; i++) {
            whiteSpaceRow[i] = '\n';
        }
        erase();
        char timeString[10];
        getCurrentTime(timeString);
        int len = strlen(timeString);

        for (int i = 0; i < len; i++) {
            char current = timeString[i];
            chars[i] = current;
        }

        printw("%.*s", w.ws_row / 2 - 4, whiteSpaceRow);
        for (int i = 0; i < 9; i++) {
            printw("%.*s", w.ws_col / 2 - (94 / 2),  whiteSpaceCol);
            for (int j = 0; j < 9; j++) {
                switch (chars[j]) {
                    case '0': printw("%s", Zero[i]); break;
                    case '1': printw("%s", One[i]); break;
                    case '2': printw("%s", Two[i]); break;
                    case '3': printw("%s", Three[i]); break;
                    case '4': printw("%s", Four[i]); break;
                    case '5': printw("%s", Five[i]); break;
                    case '6': printw("%s", Six[i]); break;
                    case '7': printw("%s", Seven[i]); break;
                    case '8': printw("%s", Eight[i]); break;
                    case '9': printw("%s", Nine[i]); break;
                    case ':': printw("%s", Colon[i]); break;
                }
            }
            printw("\n");
        }

        refresh();            /* Print it on to the real screen */
        sleep(1);
    }
    endwin();
    
}


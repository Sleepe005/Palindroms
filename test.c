#include <ncurses.h>

int main(){
    initscr();

    int key;
    key = getch();
    printf("%d", key);
    key = getch();
    printf("%d", key);
    key = getch();
    printf("%d", key);
}
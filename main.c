#include <ncurses.h>
#include <locale.h>
#include <string.h>

#define STR_SIZE 100

void printMenu(int cursePosition){
    char menu[2][75] = {
        "1. Строка",
        "2. Вывести палиндромы"
    };

    for(int i = 1; i <= 2; i++){
        printw("%s", menu[i-1]);
        if(i == cursePosition){
            printw("    <--");
        }
        printw("\n");
    }

    printw("\nВыход - esc x2\n");
}

void moveStrToRight(char *str, int *startPos, int ch){
    if(strlen(str) == STR_SIZE){return;}

    for(int i = strlen(str)-1; i >= *startPos; i--){
        str[i+1] = str[i];
    }
    str[*startPos] = ch;
    (*startPos)++;
}

void moveStrToLeft(char *str, int *startPos){
    if(*startPos == 0){return;}

    for(int i = *startPos - 1; i < strlen(str)-1; i++){
        str[i] = str[i+1];
    }
    str[strlen(str) - 1] = '\0';
    (*startPos)--;
}

void changeStr(char *str){
    init_pair(1, COLOR_BLACK, COLOR_WHITE);

    int cursePos = 0;
    bool isExit = false;
    int key;
    clear();
    while(!isExit){
        // Выводим строку
        clear();
        for(int i = 0; i < strlen(str); i++){
            if(i == cursePos){
                attron(COLOR_PAIR(1));
                printw("%c", str[i]);
                attroff(COLOR_PAIR(1));
            }else{
                printw("%c", str[i]);
            }
        }
        printw("\n");


        key = getch();
        if(key == 27){
            key = getch();
            if(key == 91){
                key = getch();
                if(key == 67){
                    if(cursePos < strlen(str)){
                        cursePos++;
                    }
                }else if(key == 68){
                    if(cursePos > 0){
                        cursePos--;
                    }
                }
            }
        }
        // insert 
        else if(key >= 32 && key <= 126){
            moveStrToRight(str, &cursePos, key);
        }
        // delete
        else if(key == 127){
            moveStrToLeft(str, &cursePos);
        }

        clear();
    }
}

int main(){
    setlocale(LC_ALL, "");
    initscr();
    start_color();

    char str[STR_SIZE+1] = "";
    // for(int i = 0; i < STR_SIZE-1; i++){
    //     str[i]='.';
    // }
    // int strCursePos = 0;

    int key;
    int menuCursePos = 1;

    bool isExit = false;
    while(!isExit){
        printMenu(menuCursePos);

        key = getch();
        if(key == 27){
            key = getch();
            if(key == 91){
                key = getch();
                if(key == 65){
                    menuCursePos--;
                    if(menuCursePos < 1){
                        menuCursePos = 2;
                    }
                }
                if(key == 66){
                    menuCursePos++;
                    if(menuCursePos > 2){
                        menuCursePos = 1;
                    }
                }
            }
            if (key == 27){
                isExit = true;
            }
        }else if(key == 49){
            changeStr(str);
        }

        clear();
    }

    return 0;
}
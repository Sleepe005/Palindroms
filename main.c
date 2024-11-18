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
        printw("Для выхода два раза нажмите esc\n\n");

        for(int i = 0; i < strlen(str); i++){
            if(i == cursePos){
                attron(COLOR_PAIR(1));
                printw("%c", str[i]);
                attroff(COLOR_PAIR(1));
            }else{
                printw("%c", str[i]);
            }
        }


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
            if(key == 27){
                isExit = true;
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

bool isPalindorm(const char str[STR_SIZE+1]){
    int iterCount = strlen(str) / 2;
    if(strlen(str) % 2 != 0){
        iterCount++;
    }

    bool isPal = true;
    for(int i = 0; i < iterCount; i++){
        if(str[i] != str[strlen(str)-i-1]){
            isPal = false;
        }
    }

    return isPal;
}

void printPalindorms(const char str[STR_SIZE+1]){
    clear();
    if(strlen(str) == 0){
        printw("Строка пустая. Палиндромы отсутствуют :(");
    }else{
        int palindormsCount = 0;

        for(int i = 0; i < strlen(str)-2; i++){
            for(int j = i+2; j < strlen(str); j++){
                char substr[STR_SIZE+1];
                strncpy(substr, str+i, j-i+1);

                if(isPalindorm(substr)){
                    printw("%s\n", substr);
                    palindormsCount++;
                }

                memset(substr, '\0', sizeof(substr));
            }
        }

        if(!palindormsCount){
            printw("Палиндромы не найдены");
        }
    }

    printw("\n\nДля выхода в главное меню нажмите любую кнопку\n");
    getch();
}

int main(){
    setlocale(LC_ALL, "");
    initscr();
    start_color();

    char str[STR_SIZE+1] = "";

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
        }else if(key == 50){
            printPalindorms(str);
        }else if(key == 10){
            if(menuCursePos == 1){changeStr(str);}
        }

        clear();
    }

    return 0;
}
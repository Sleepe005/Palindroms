// #include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STR_SIZE 100

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

int main(){

printf("%d", isPalindorm("1232"));
//    char str[100] = "Hello";
//    for(int i = 0; i < strlen(str)-2; i++){
//         for(int j = i+2; j < strlen(str); j++){
//             char substr[100];
//             // if(isPalindorm(strncpy(substr, str+i, j-i)));
//             strncpy(substr, str+i, j-i+1);
//             printf("%s\n", substr);
//             memset(substr, '\0', sizeof(substr));
//         }
//     }
}


// len 4
//  0 4-0-1 (3)
//  1 4-1-1 (2)
//  
//  len 5
//  0 5-0-1 (4)
//  1 5-1-1 (3)
//  2 5-2-1 (2)
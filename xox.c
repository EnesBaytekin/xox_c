#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void print_board(char* board,char selection) {
    for (char r=0;r<3;r++) {
        for (char c=0;c<3;c++) {
            _Bool selected = (r == selection/3 && c == selection%3);
            char letter = board[r*3+c];
            if (selected) printf("\033[41m");
            printf("[%c]",letter);
            if (selected) printf("\033[0m");
        }
        printf("\n");
    }
}

_Bool put(char* board,char selection,char letter) {
    if (board[selection] == ' ') {
        board[selection] = letter;
        return 1;
    }
    else return 0;
}

_Bool is_finished(char* board) {
    for (char i=0;i<3;i++) {
        if (board[i*3+0] != ' ' && board[i*3+0] == board[i*3+1] && board[i*3+1] == board[i*3+2]) return 1;
        if (board[0*3+i] != ' ' && board[0*3+i] == board[1*3+i] && board[1*3+i] == board[2*3+i]) return 1;
    }
    if (board[0*3+0] != ' ' && board[0*3+0] == board[1*3+1] && board[1*3+1] == board[2*3+2]) return 1;
    if (board[2*3+0] != ' ' && board[2*3+0] == board[1*3+1] && board[1*3+1] == board[0*3+2]) return 1;
    return 0;
}

int main() {
    char board[9] = "         ";
    char selection=0;
    char c;
    char turn = 0;
    do {
        system("cls");
        print_board(board,selection);
        if (turn == 9) {
            printf("Nobody wins.\n");
            exit(0);
        }
        c = getch();
        printf("%c",c);
        switch (c) {
            case 'w':
                if (selection/3 > 0) selection -= 3;
                break;
            case 's':
                if (selection/3 < 2) selection += 3;
                break;
            case 'a':
                if (selection%3 > 0) selection--;
                break;
            case 'd':
                if (selection%3 < 2) selection++;
                break;
            case ' ':
                if (put(board,selection,turn%2==0?'X':'O'))
                    turn++;
                break;
        }
    } while (c != 'q' && !is_finished(board));
    system("cls");
    print_board(board,selection);
    printf("%c won the game!\n",turn%2==1?'X':'O');
    return 0;
}
